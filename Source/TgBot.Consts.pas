unit TgBot.Consts;

{
  TgBot — библиотека Telegram Bot API для Delphi.
  Ресурсные строки библиотеки: тексты исключений и сообщений (RU/EN),
  по образцу System.RTLConsts / System.SysConst.

  Служебный модуль: подключается только в разделах implementation модулей
  библиотеки. В прикладном коде его не подключайте — язык сообщений
  выбирается через TgSetLanguage, тексты возвращают TgText, TgTextFmt,
  TgUpdatesText, TgRouterText (фасад TgBot этот модуль не реэкспортирует).

  Устройство:
  - каждый текст — пара ресурсных строк рядом: SRu<Имя> (русский) и
    SEn<Имя> (английский); язык выбирает TgLangText из TgBot.Base;
  - секции по подсистемам с префиксами: ядро — без префикса (SRu<Имя>),
    JSON — SRuJson…, DTO — SRuDto…, обновления — SRuUpd…, маршрутизатор —
    SRuRoute…, TTgBot — SRuBot…, компонент — SRuComp…, webhook-сервер —
    SRuWhs…;
  - подстановки (%s, %d) сохраняйте в переводе в том же порядке и количестве.

  Перевод (Translation Manager / ITE): обе группы, SRu… и SEn…, —
  resourcestring и попадают в ресурсы пакета/программы. Чтобы получить
  третий язык, переведите в ресурсной DLL строки той группы, которая
  выбрана через TgSetLanguage (обычно SEn…). Имена модулей, методов
  и полей Telegram Bot API в тексты не переводятся.

  Модуль не использует другие модули и компилируется на всех платформах
  библиотеки (Win32, Win64, Linux64, Android/Android64).
}

interface

resourcestring

  { Ядро: тексты TTgText (TgText/TgTextFmt из TgBot.Base) }

  SRuTokenRequired = 'Не задан токен бота';
  SEnTokenRequired = 'Bot token is not specified';
  SRuOptionalEmpty = 'Опциональное значение не задано';
  SEnOptionalEmpty = 'Optional value is not set';
  SRuChatIdEmpty = 'Идентификатор чата не задан';
  SEnChatIdEmpty = 'Chat identifier is not specified';
  SRuChatIdNotNumeric = 'Идентификатор чата "%s" не является числом';
  SEnChatIdNotNumeric = 'Chat identifier "%s" is not numeric';
  SRuInputFileEmpty = 'Файл не задан';
  SEnInputFileEmpty = 'Input file is not specified';
  SRuInputFileNotUpload = 'Файл требует загрузки и не может быть передан строкой';
  SEnInputFileNotUpload = 'Input file must be uploaded and cannot be passed as a string';
  SRuInputFileStreamNil = 'Поток для загрузки файла не задан (nil)';
  SEnInputFileStreamNil = 'Upload stream is not assigned (nil)';
  SRuLocalPathNotAbsolute = 'Путь "%s" должен быть абсолютным';
  SEnLocalPathNotAbsolute = 'Path "%s" must be absolute';
  SRuParamNameEmpty = 'Имя параметра не задано';
  SEnParamNameEmpty = 'Parameter name is not specified';
  SRuInvalidJson = 'Некорректный JSON в параметре "%s"';
  SEnInvalidJson = 'Invalid JSON in parameter "%s"';
  SRuApiError = 'Ошибка Telegram Bot API в методе %s (код %d): %s';
  SEnApiError = 'Telegram Bot API error in method %s (code %d): %s';
  SRuNetworkError = 'Сетевая ошибка при вызове %s: %s';
  SEnNetworkError = 'Network error while calling %s: %s';
  SRuInvalidResponse = 'Некорректный ответ сервера при вызове %s (HTTP %d)';
  SEnInvalidResponse = 'Invalid server response while calling %s (HTTP %d)';
  SRuUnexpectedResult = 'Неожиданный формат результата метода %s';
  SEnUnexpectedResult = 'Unexpected result format of method %s';
  SRuCancelled = 'Операция прервана';
  SEnCancelled = 'Operation cancelled';
  SRuFilePathEmpty = 'Не задан путь к файлу на сервере (file_path)';
  SEnFilePathEmpty = 'Server file path (file_path) is not specified';
  SRuFilePathInvalid = 'Недопустимый путь к файлу на сервере: "%s"';
  SEnFilePathInvalid = 'Invalid server file path: "%s"';
  SRuDownloadFailed = 'Не удалось скачать файл (HTTP %d)';
  SEnDownloadFailed = 'File download failed (HTTP %d)';
  SRuTransportRequired = 'Не задан транспорт Bot API';
  SEnTransportRequired = 'Bot API transport is not specified';
  SRuConflict = 'Конфликт в методе %s (код %d): %s. Вероятно, запущен другой ' +
    'экземпляр бота с этим токеном или для getUpdates установлен webhook';
  SEnConflict = 'Conflict in method %s (code %d): %s. Another bot instance with ' +
    'this token is probably running, or a webhook is set while using getUpdates';
  SRuClientClosed = 'Клиент Bot API уничтожается: асинхронный вызов отменён';
  SEnClientClosed = 'Bot API client is being destroyed: asynchronous call cancelled';

  { Ядро: проверка аргументов (EArgumentNilException, EArgumentOutOfRangeException).
    Первая подстановка — имя параметра (не переводится). }

  SRuArgNil = 'Параметр %s не может быть nil';
  SEnArgNil = 'Parameter %s must not be nil';
  SRuArgOutOfRange = 'Параметр %s = %d вне допустимого диапазона (минимум %d)';
  SEnArgOutOfRange = 'Parameter %s = %d is out of range (minimum %d)';

implementation

end.
