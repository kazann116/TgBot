<#
.SYNOPSIS
  Создаёт иконку установщика TgBot (Source\Design\Icons\TgBot.ico) из PNG палитры 128 px.

.DESCRIPTION
  Масштабирует TTELEGRAMBOT128.png (белый самолётик на голубом круге, альфа-канал) до 16, 24, 32, 48, 64
  и 128 px и записывает их в один .ico (32 бита, BGRA + маска AND) — формат, который понимают Windows и
  Inno Setup (SetupIconFile). Используется Tools\Dist\TgBot.iss; MakeDist.ps1 вызывает скрипт, если
  иконки нет.

.EXAMPLE
  powershell -ExecutionPolicy Bypass -File Tools\Dist\MakeIco.ps1
#>
param(
    [string]$Png = '',
    [string]$OutFile = ''
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Drawing

$root = Split-Path -Parent (Split-Path -Parent $PSScriptRoot)
if (-not $Png) { $Png = Join-Path $root 'Source\Design\Icons\TTELEGRAMBOT128.png' }
if (-not $OutFile) { $OutFile = Join-Path $root 'Source\Design\Icons\TgBot.ico' }
$sizes = @(16, 24, 32, 48, 64, 128)

# Картинка S x S, 32 бита с альфой: строки сверху вниз, байты BGRA.
function Get-ScaledPixels {
    param([System.Drawing.Image]$Source, [int]$Size)
    $bmp = New-Object System.Drawing.Bitmap($Size, $Size, [System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
    try {
        $g = [System.Drawing.Graphics]::FromImage($bmp)
        $attr = New-Object System.Drawing.Imaging.ImageAttributes
        try {
            $g.Clear([System.Drawing.Color]::Transparent)
            $g.CompositingMode = [System.Drawing.Drawing2D.CompositingMode]::SourceCopy
            $g.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
            $g.PixelOffsetMode = [System.Drawing.Drawing2D.PixelOffsetMode]::HighQuality
            $g.SmoothingMode = [System.Drawing.Drawing2D.SmoothingMode]::HighQuality
            $attr.SetWrapMode([System.Drawing.Drawing2D.WrapMode]::TileFlipXY)
            $dst = New-Object System.Drawing.Rectangle(0, 0, $Size, $Size)
            $g.DrawImage($Source, $dst, 0, 0, $Source.Width, $Source.Height, [System.Drawing.GraphicsUnit]::Pixel, $attr)
        } finally {
            $attr.Dispose()
            $g.Dispose()
        }
        $rect = New-Object System.Drawing.Rectangle(0, 0, $Size, $Size)
        $data = $bmp.LockBits($rect, [System.Drawing.Imaging.ImageLockMode]::ReadOnly,
            [System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
        try {
            $bytes = New-Object byte[] ($Size * $Size * 4)
            for ($y = 0; $y -lt $Size; $y++) {
                $src = [IntPtr]($data.Scan0.ToInt64() + [int64]$y * $data.Stride)
                [Runtime.InteropServices.Marshal]::Copy($src, $bytes, $y * $Size * 4, $Size * 4)
            }
            return ,$bytes
        } finally {
            $bmp.UnlockBits($data)
        }
    } finally {
        $bmp.Dispose()
    }
}

# Образ иконки: BITMAPINFOHEADER + пиксели снизу вверх + маска AND (1 — прозрачный пиксель).
function New-IconImage {
    param([byte[]]$Pixels, [int]$Size)
    $maskStride = [int]([Math]::Ceiling($Size / 32.0) * 4)
    $ms = New-Object IO.MemoryStream
    $w = New-Object IO.BinaryWriter($ms)
    try {
        $w.Write([int32]40)
        $w.Write([int32]$Size)
        $w.Write([int32]($Size * 2))
        $w.Write([int16]1)
        $w.Write([int16]32)
        $w.Write([int32]0)
        $w.Write([int32]($Size * $Size * 4 + $maskStride * $Size))
        $w.Write([int32]0); $w.Write([int32]0); $w.Write([int32]0); $w.Write([int32]0)
        for ($y = $Size - 1; $y -ge 0; $y--) { $w.Write($Pixels, $y * $Size * 4, $Size * 4) }
        for ($y = $Size - 1; $y -ge 0; $y--) {
            $row = New-Object byte[] $maskStride
            for ($x = 0; $x -lt $Size; $x++) {
                if ($Pixels[($y * $Size + $x) * 4 + 3] -eq 0) {
                    $row[[int][Math]::Floor($x / 8)] = $row[[int][Math]::Floor($x / 8)] -bor (0x80 -shr ($x % 8))
                }
            }
            $w.Write($row)
        }
        $w.Flush()
        return ,$ms.ToArray()
    } finally {
        $w.Dispose()
    }
}

if (-not (Test-Path -LiteralPath $Png)) { throw "Нет исходного PNG: $Png" }
$image = [System.Drawing.Image]::FromFile($Png)
try {
    $images = @()
    foreach ($s in $sizes) { $images += ,(New-IconImage -Pixels (Get-ScaledPixels -Source $image -Size $s) -Size $s) }
} finally {
    $image.Dispose()
}

$out = New-Object IO.MemoryStream
$bw = New-Object IO.BinaryWriter($out)
try {
    $bw.Write([int16]0)
    $bw.Write([int16]1)
    $bw.Write([int16]$sizes.Count)
    $offset = 6 + 16 * $sizes.Count
    for ($i = 0; $i -lt $sizes.Count; $i++) {
        $bw.Write([byte]($sizes[$i] % 256))
        $bw.Write([byte]($sizes[$i] % 256))
        $bw.Write([byte]0)
        $bw.Write([byte]0)
        $bw.Write([int16]1)
        $bw.Write([int16]32)
        $bw.Write([int32]$images[$i].Length)
        $bw.Write([int32]$offset)
        $offset += $images[$i].Length
    }
    foreach ($img in $images) { $bw.Write($img) }
    $bw.Flush()
    [IO.File]::WriteAllBytes($OutFile, $out.ToArray())
} finally {
    $bw.Dispose()
}
Write-Host ('Иконка: {0} ({1} байт; {2} px)' -f $OutFile, (Get-Item -LiteralPath $OutFile).Length, ($sizes -join ', '))
