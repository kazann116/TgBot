param([string]$OutDir)
# Иконка палитры TTelegramBot: белый «бумажный самолётик» на голубом круге #2AABEE.
# BMP 24 бита (16/24/32 px), левый нижний пиксель — цвет прозрачности (фуксия);
# PNG 128 px с альфа-каналом (RCDATA TTELEGRAMBOT128_PNG).
Add-Type -AssemblyName System.Drawing
$ErrorActionPreference = 'Stop'
New-Item -ItemType Directory -Force -Path $OutDir | Out-Null

$Blue  = [System.Drawing.Color]::FromArgb(255, 0x2A, 0xAB, 0xEE)
$FoldColor = [System.Drawing.Color]::FromArgb(255, 0xC8, 0xDA, 0xEA)
$Trans = [System.Drawing.Color]::FromArgb(255, 255, 0, 255)
# TTgWebhookServer: тот же самолётик + значок сервера (тёмная стойка, зелёные индикаторы).
$RackColor = [System.Drawing.Color]::FromArgb(255, 0x26, 0x32, 0x38)
$SlotColor = [System.Drawing.Color]::FromArgb(255, 0x60, 0x7D, 0x8B)
$LedColor  = [System.Drawing.Color]::FromArgb(255, 0x4C, 0xDF, 0x50)
$script:Server = $false

function New-Master([int]$S) {
  # Рисует в квадрате S x S (32 бита с альфой, сглаживание).
  $bmp = New-Object System.Drawing.Bitmap($S, $S, [System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
  $g = [System.Drawing.Graphics]::FromImage($bmp)
  $g.SmoothingMode = [System.Drawing.Drawing2D.SmoothingMode]::AntiAlias
  $g.Clear([System.Drawing.Color]::Transparent)
  $m = $S * 0.02
  $g.FillEllipse((New-Object System.Drawing.SolidBrush($Blue)), [single]$m, [single]$m, [single]($S - 2*$m), [single]($S - 2*$m))
  function P([double]$x, [double]$y) { New-Object System.Drawing.PointF([single]($x*$S), [single]($y*$S)) }
  # Силуэт самолётика (нормированные координаты).
  [System.Drawing.PointF[]]$plane = @(
    (P 0.20 0.495), (P 0.755 0.275), (P 0.665 0.735),
    (P 0.495 0.615), (P 0.425 0.725), (P 0.405 0.585))
  $g.FillPolygon((New-Object System.Drawing.SolidBrush([System.Drawing.Color]::White)), $plane)
  # Сгиб крыла.
  [System.Drawing.PointF[]]$foldPts = @((P 0.405 0.585), (P 0.425 0.725), (P 0.495 0.615), (P 0.655 0.375))
  $g.FillPolygon((New-Object System.Drawing.SolidBrush($FoldColor)), $foldPts)
  if ($script:Server) {
    # TTgWebhookServer: значок сервера (два блока стойки) в правом нижнем углу.
    $rack = New-Object System.Drawing.SolidBrush($RackColor)
    $slot = New-Object System.Drawing.SolidBrush($SlotColor)
    $led  = New-Object System.Drawing.SolidBrush($LedColor)
    $g.FillRectangle($rack, [single](0.50*$S), [single](0.50*$S), [single](0.50*$S), [single](0.50*$S))
    foreach ($y in 0.56, 0.77) {
      $g.FillRectangle($slot, [single](0.55*$S), [single]($y*$S), [single](0.40*$S), [single](0.17*$S))
      $g.FillRectangle($led, [single](0.84*$S), [single](($y + 0.05)*$S), [single](0.07*$S), [single](0.07*$S))
    }
  }
  $g.Dispose()
  return $bmp
}

function Save-Png([int]$S, [string]$Path) {
  $big = New-Master ($S * 4)
  $bmp = New-Object System.Drawing.Bitmap($S, $S, [System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
  $g = [System.Drawing.Graphics]::FromImage($bmp)
  $g.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
  $g.PixelOffsetMode = [System.Drawing.Drawing2D.PixelOffsetMode]::HighQuality
  $g.DrawImage($big, 0, 0, $S, $S)
  $g.Dispose(); $big.Dispose()
  $bmp.Save($Path, [System.Drawing.Imaging.ImageFormat]::Png)
  $bmp.Dispose()
}

function Save-Bmp([int]$S, [string]$Path) {
  $big = New-Master ($S * 8)
  $small = New-Object System.Drawing.Bitmap($S, $S, [System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
  $g = [System.Drawing.Graphics]::FromImage($small)
  $g.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::HighQualityBilinear
  $g.PixelOffsetMode = [System.Drawing.Drawing2D.PixelOffsetMode]::HighQuality
  $g.DrawImage($big, 0, 0, $S, $S)
  $g.Dispose(); $big.Dispose()
  $out = New-Object System.Drawing.Bitmap($S, $S, [System.Drawing.Imaging.PixelFormat]::Format24bppRgb)
  for ($y = 0; $y -lt $S; $y++) {
    for ($x = 0; $x -lt $S; $x++) {
      $c = $small.GetPixel($x, $y)
      if ($c.A -lt 128) {
        $out.SetPixel($x, $y, $Trans)
      } else {
        # Полупрозрачная кромка круга -> непрозрачный цвет (без розовой каймы).
        $out.SetPixel($x, $y, [System.Drawing.Color]::FromArgb(255, $c.R, $c.G, $c.B))
      }
    }
  }
  # Левый нижний пиксель — цвет прозрачности (IDE берёт его как прозрачный).
  $out.SetPixel(0, $S - 1, $Trans)
  $small.Dispose()
  $out.Save($Path, [System.Drawing.Imaging.ImageFormat]::Bmp)
  $out.Dispose()
}

Save-Bmp 16 (Join-Path $OutDir 'TTELEGRAMBOT16.bmp')
Save-Bmp 24 (Join-Path $OutDir 'TTELEGRAMBOT.bmp')
Save-Bmp 32 (Join-Path $OutDir 'TTELEGRAMBOT32.bmp')
Save-Png 128 (Join-Path $OutDir 'TTELEGRAMBOT128.png')
$script:Server = $true
Save-Bmp 16 (Join-Path $OutDir 'TTGWEBHOOKSERVER16.bmp')
Save-Bmp 24 (Join-Path $OutDir 'TTGWEBHOOKSERVER.bmp')
Save-Bmp 32 (Join-Path $OutDir 'TTGWEBHOOKSERVER32.bmp')
Save-Png 128 (Join-Path $OutDir 'TTGWEBHOOKSERVER128.png')
$script:Server = $false
# Увеличенные копии для визуальной проверки (без сглаживания).
foreach ($n in 'TTELEGRAMBOT16', 'TTELEGRAMBOT', 'TTELEGRAMBOT32',
    'TTGWEBHOOKSERVER16', 'TTGWEBHOOKSERVER', 'TTGWEBHOOKSERVER32') {
  $src = [System.Drawing.Image]::FromFile((Join-Path $OutDir "$n.bmp"))
  $z = New-Object System.Drawing.Bitmap(256, 256)
  $g = [System.Drawing.Graphics]::FromImage($z)
  $g.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::NearestNeighbor
  $g.PixelOffsetMode = [System.Drawing.Drawing2D.PixelOffsetMode]::Half
  $g.DrawImage($src, 0, 0, 256, 256)
  $g.Dispose(); $src.Dispose()
  $z.Save((Join-Path $OutDir "preview_$n.png"), [System.Drawing.Imaging.ImageFormat]::Png)
  $z.Dispose()
}
Write-Output 'OK'
