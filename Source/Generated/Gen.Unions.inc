// Gen.Unions.inc — записи-объединения исходящих типов.
// Сгенерировано TgBotGen по Telegram Bot API 10.3 (August 24, 2026). Не редактируйте вручную.

  /// <summary>
  ///   This object represents the content of a poll description or a quiz explanation to be sent.
  ///   Принимает (неявное приведение): ITgInputMediaAnimation, ITgInputMediaAudio,
  ///   ITgInputMediaDocument, ITgInputMediaLivePhoto, ITgInputMediaLocation, ITgInputMediaPhoto,
  ///   ITgInputMediaVenue, ITgInputMediaVideo.
  /// </summary>
  TTgInputPollMedia = record
  private
    FValue: IInterface;
  public
    class operator Implicit(const AValue: ITgInputMediaAnimation): TTgInputPollMedia;
    class operator Implicit(const AValue: ITgInputMediaAudio): TTgInputPollMedia;
    class operator Implicit(const AValue: ITgInputMediaDocument): TTgInputPollMedia;
    class operator Implicit(const AValue: ITgInputMediaLivePhoto): TTgInputPollMedia;
    class operator Implicit(const AValue: ITgInputMediaLocation): TTgInputPollMedia;
    class operator Implicit(const AValue: ITgInputMediaPhoto): TTgInputPollMedia;
    class operator Implicit(const AValue: ITgInputMediaVenue): TTgInputPollMedia;
    class operator Implicit(const AValue: ITgInputMediaVideo): TTgInputPollMedia;
    /// <summary>Значения элементов массива (для сериализации).</summary>
    class function Values(const AItems: array of TTgInputPollMedia): TArray<IInterface>; static;
    /// <summary>Значение не задано.</summary>
    function IsEmpty: Boolean;
    /// <summary>Объект-вариант (ITgOutObject или ITgJsonObject).</summary>
    property Value: IInterface read FValue;
  end;

  /// <summary>
  ///   This object represents the content of a poll option to be sent. Принимает (неявное
  ///   приведение): ITgInputMediaAnimation, ITgInputMediaLink, ITgInputMediaLivePhoto,
  ///   ITgInputMediaLocation, ITgInputMediaPhoto, ITgInputMediaSticker, ITgInputMediaVenue,
  ///   ITgInputMediaVideo.
  /// </summary>
  TTgInputPollOptionMedia = record
  private
    FValue: IInterface;
  public
    class operator Implicit(const AValue: ITgInputMediaAnimation): TTgInputPollOptionMedia;
    class operator Implicit(const AValue: ITgInputMediaLink): TTgInputPollOptionMedia;
    class operator Implicit(const AValue: ITgInputMediaLivePhoto): TTgInputPollOptionMedia;
    class operator Implicit(const AValue: ITgInputMediaLocation): TTgInputPollOptionMedia;
    class operator Implicit(const AValue: ITgInputMediaPhoto): TTgInputPollOptionMedia;
    class operator Implicit(const AValue: ITgInputMediaSticker): TTgInputPollOptionMedia;
    class operator Implicit(const AValue: ITgInputMediaVenue): TTgInputPollOptionMedia;
    class operator Implicit(const AValue: ITgInputMediaVideo): TTgInputPollOptionMedia;
    /// <summary>Значения элементов массива (для сериализации).</summary>
    class function Values(const AItems: array of TTgInputPollOptionMedia): TArray<IInterface>; static;
    /// <summary>Значение не задано.</summary>
    function IsEmpty: Boolean;
    /// <summary>Объект-вариант (ITgOutObject или ITgJsonObject).</summary>
    property Value: IInterface read FValue;
  end;

  /// <summary>
  ///   Describes the type of a clickable area on a story. Принимает (неявное приведение):
  ///   ITgStoryAreaTypeLocation, ITgStoryAreaTypeSuggestedReaction, ITgStoryAreaTypeLink,
  ///   ITgStoryAreaTypeWeather, ITgStoryAreaTypeUniqueGift.
  /// </summary>
  TTgStoryAreaType = record
  private
    FValue: IInterface;
  public
    class operator Implicit(const AValue: ITgStoryAreaTypeLocation): TTgStoryAreaType;
    class operator Implicit(const AValue: ITgStoryAreaTypeSuggestedReaction): TTgStoryAreaType;
    class operator Implicit(const AValue: ITgStoryAreaTypeLink): TTgStoryAreaType;
    class operator Implicit(const AValue: ITgStoryAreaTypeWeather): TTgStoryAreaType;
    class operator Implicit(const AValue: ITgStoryAreaTypeUniqueGift): TTgStoryAreaType;
    /// <summary>Значения элементов массива (для сериализации).</summary>
    class function Values(const AItems: array of TTgStoryAreaType): TArray<IInterface>; static;
    /// <summary>Значение не задано.</summary>
    function IsEmpty: Boolean;
    /// <summary>Объект-вариант (ITgOutObject или ITgJsonObject).</summary>
    property Value: IInterface read FValue;
  end;

  /// <summary>
  ///   This object represents the scope to which bot commands are applied. Currently, the following
  ///   7 scopes are supported: Принимает (неявное приведение): ITgBotCommandScopeDefault,
  ///   ITgBotCommandScopeAllPrivateChats, ITgBotCommandScopeAllGroupChats,
  ///   ITgBotCommandScopeAllChatAdministrators, ITgBotCommandScopeChat,
  ///   ITgBotCommandScopeChatAdministrators, ITgBotCommandScopeChatMember.
  /// </summary>
  TTgBotCommandScope = record
  private
    FValue: IInterface;
  public
    class operator Implicit(const AValue: ITgBotCommandScopeDefault): TTgBotCommandScope;
    class operator Implicit(const AValue: ITgBotCommandScopeAllPrivateChats): TTgBotCommandScope;
    class operator Implicit(const AValue: ITgBotCommandScopeAllGroupChats): TTgBotCommandScope;
    class operator Implicit(const AValue: ITgBotCommandScopeAllChatAdministrators): TTgBotCommandScope;
    class operator Implicit(const AValue: ITgBotCommandScopeChat): TTgBotCommandScope;
    class operator Implicit(const AValue: ITgBotCommandScopeChatAdministrators): TTgBotCommandScope;
    class operator Implicit(const AValue: ITgBotCommandScopeChatMember): TTgBotCommandScope;
    /// <summary>Значения элементов массива (для сериализации).</summary>
    class function Values(const AItems: array of TTgBotCommandScope): TArray<IInterface>; static;
    /// <summary>Значение не задано.</summary>
    function IsEmpty: Boolean;
    /// <summary>Объект-вариант (ITgOutObject или ITgJsonObject).</summary>
    property Value: IInterface read FValue;
  end;

  /// <summary>
  ///   This object represents the content of a media message to be sent. Принимает (неявное
  ///   приведение): ITgInputMediaAnimation, ITgInputMediaAudio, ITgInputMediaDocument,
  ///   ITgInputMediaLivePhoto, ITgInputMediaPhoto, ITgInputMediaVideo.
  /// </summary>
  TTgInputMedia = record
  private
    FValue: IInterface;
  public
    class operator Implicit(const AValue: ITgInputMediaAnimation): TTgInputMedia;
    class operator Implicit(const AValue: ITgInputMediaAudio): TTgInputMedia;
    class operator Implicit(const AValue: ITgInputMediaDocument): TTgInputMedia;
    class operator Implicit(const AValue: ITgInputMediaLivePhoto): TTgInputMedia;
    class operator Implicit(const AValue: ITgInputMediaPhoto): TTgInputMedia;
    class operator Implicit(const AValue: ITgInputMediaVideo): TTgInputMedia;
    /// <summary>Значения элементов массива (для сериализации).</summary>
    class function Values(const AItems: array of TTgInputMedia): TArray<IInterface>; static;
    /// <summary>Значение не задано.</summary>
    function IsEmpty: Boolean;
    /// <summary>Объект-вариант (ITgOutObject или ITgJsonObject).</summary>
    property Value: IInterface read FValue;
  end;

  /// <summary>
  ///   This object describes the paid media to be sent. Принимает (неявное приведение):
  ///   ITgInputPaidMediaLivePhoto, ITgInputPaidMediaPhoto, ITgInputPaidMediaVideo.
  /// </summary>
  TTgInputPaidMedia = record
  private
    FValue: IInterface;
  public
    class operator Implicit(const AValue: ITgInputPaidMediaLivePhoto): TTgInputPaidMedia;
    class operator Implicit(const AValue: ITgInputPaidMediaPhoto): TTgInputPaidMedia;
    class operator Implicit(const AValue: ITgInputPaidMediaVideo): TTgInputPaidMedia;
    /// <summary>Значения элементов массива (для сериализации).</summary>
    class function Values(const AItems: array of TTgInputPaidMedia): TArray<IInterface>; static;
    /// <summary>Значение не задано.</summary>
    function IsEmpty: Boolean;
    /// <summary>Объект-вариант (ITgOutObject или ITgJsonObject).</summary>
    property Value: IInterface read FValue;
  end;

  /// <summary>
  ///   This object describes a profile photo to set. Принимает (неявное приведение):
  ///   ITgInputProfilePhotoStatic, ITgInputProfilePhotoAnimated.
  /// </summary>
  TTgInputProfilePhoto = record
  private
    FValue: IInterface;
  public
    class operator Implicit(const AValue: ITgInputProfilePhotoStatic): TTgInputProfilePhoto;
    class operator Implicit(const AValue: ITgInputProfilePhotoAnimated): TTgInputProfilePhoto;
    /// <summary>Значения элементов массива (для сериализации).</summary>
    class function Values(const AItems: array of TTgInputProfilePhoto): TArray<IInterface>; static;
    /// <summary>Значение не задано.</summary>
    function IsEmpty: Boolean;
    /// <summary>Объект-вариант (ITgOutObject или ITgJsonObject).</summary>
    property Value: IInterface read FValue;
  end;

  /// <summary>
  ///   This object describes the content of a story to post. Принимает (неявное приведение):
  ///   ITgInputStoryContentPhoto, ITgInputStoryContentVideo.
  /// </summary>
  TTgInputStoryContent = record
  private
    FValue: IInterface;
  public
    class operator Implicit(const AValue: ITgInputStoryContentPhoto): TTgInputStoryContent;
    class operator Implicit(const AValue: ITgInputStoryContentVideo): TTgInputStoryContent;
    /// <summary>Значения элементов массива (для сериализации).</summary>
    class function Values(const AItems: array of TTgInputStoryContent): TArray<IInterface>; static;
    /// <summary>Значение не задано.</summary>
    function IsEmpty: Boolean;
    /// <summary>Объект-вариант (ITgOutObject или ITgJsonObject).</summary>
    property Value: IInterface read FValue;
  end;

  /// <summary>
  ///   This object represents a block in a rich formatted message to be sent. Currently, it can be
  ///   any of the following types: Принимает (неявное приведение): ITgInputRichBlockParagraph,
  ///   ITgInputRichBlockSectionHeading, ITgInputRichBlockPreformatted, ITgInputRichBlockFooter,
  ///   ITgInputRichBlockDivider, ITgInputRichBlockMathematicalExpression, ITgInputRichBlockAnchor,
  ///   ITgInputRichBlockList, ITgInputRichBlockBlockQuotation,
  ///   ITgInputRichBlockExpandableBlockQuotation, ITgInputRichBlockPullQuotation,
  ///   ITgInputRichBlockCollage, ITgInputRichBlockSlideshow, ITgInputRichBlockTable,
  ///   ITgInputRichBlockDetails, ITgInputRichBlockMap, ITgInputRichBlockButtons,
  ///   ITgInputRichBlockAnimation, ITgInputRichBlockAudio, ITgInputRichBlockDocument,
  ///   ITgInputRichBlockPhoto, ITgInputRichBlockVideo, ITgInputRichBlockVoiceNote,
  ///   ITgInputRichBlockThinking.
  /// </summary>
  TTgInputRichBlock = record
  private
    FValue: IInterface;
  public
    class operator Implicit(const AValue: ITgInputRichBlockParagraph): TTgInputRichBlock;
    class operator Implicit(const AValue: ITgInputRichBlockSectionHeading): TTgInputRichBlock;
    class operator Implicit(const AValue: ITgInputRichBlockPreformatted): TTgInputRichBlock;
    class operator Implicit(const AValue: ITgInputRichBlockFooter): TTgInputRichBlock;
    class operator Implicit(const AValue: ITgInputRichBlockDivider): TTgInputRichBlock;
    class operator Implicit(const AValue: ITgInputRichBlockMathematicalExpression): TTgInputRichBlock;
    class operator Implicit(const AValue: ITgInputRichBlockAnchor): TTgInputRichBlock;
    class operator Implicit(const AValue: ITgInputRichBlockList): TTgInputRichBlock;
    class operator Implicit(const AValue: ITgInputRichBlockBlockQuotation): TTgInputRichBlock;
    class operator Implicit(const AValue: ITgInputRichBlockExpandableBlockQuotation): TTgInputRichBlock;
    class operator Implicit(const AValue: ITgInputRichBlockPullQuotation): TTgInputRichBlock;
    class operator Implicit(const AValue: ITgInputRichBlockCollage): TTgInputRichBlock;
    class operator Implicit(const AValue: ITgInputRichBlockSlideshow): TTgInputRichBlock;
    class operator Implicit(const AValue: ITgInputRichBlockTable): TTgInputRichBlock;
    class operator Implicit(const AValue: ITgInputRichBlockDetails): TTgInputRichBlock;
    class operator Implicit(const AValue: ITgInputRichBlockMap): TTgInputRichBlock;
    class operator Implicit(const AValue: ITgInputRichBlockButtons): TTgInputRichBlock;
    class operator Implicit(const AValue: ITgInputRichBlockAnimation): TTgInputRichBlock;
    class operator Implicit(const AValue: ITgInputRichBlockAudio): TTgInputRichBlock;
    class operator Implicit(const AValue: ITgInputRichBlockDocument): TTgInputRichBlock;
    class operator Implicit(const AValue: ITgInputRichBlockPhoto): TTgInputRichBlock;
    class operator Implicit(const AValue: ITgInputRichBlockVideo): TTgInputRichBlock;
    class operator Implicit(const AValue: ITgInputRichBlockVoiceNote): TTgInputRichBlock;
    class operator Implicit(const AValue: ITgInputRichBlockThinking): TTgInputRichBlock;
    /// <summary>Значения элементов массива (для сериализации).</summary>
    class function Values(const AItems: array of TTgInputRichBlock): TArray<IInterface>; static;
    /// <summary>Значение не задано.</summary>
    function IsEmpty: Boolean;
    /// <summary>Объект-вариант (ITgOutObject или ITgJsonObject).</summary>
    property Value: IInterface read FValue;
  end;

  /// <summary>
  ///   This object represents one result of an inline query. Telegram clients currently support
  ///   results of the following 20 types: Принимает (неявное приведение):
  ///   ITgInlineQueryResultCachedAudio, ITgInlineQueryResultCachedDocument,
  ///   ITgInlineQueryResultCachedGif, ITgInlineQueryResultCachedMpeg4Gif,
  ///   ITgInlineQueryResultCachedPhoto, ITgInlineQueryResultCachedSticker,
  ///   ITgInlineQueryResultCachedVideo, ITgInlineQueryResultCachedVoice,
  ///   ITgInlineQueryResultArticle, ITgInlineQueryResultAudio, ITgInlineQueryResultContact,
  ///   ITgInlineQueryResultGame, ITgInlineQueryResultDocument, ITgInlineQueryResultGif,
  ///   ITgInlineQueryResultLocation, ITgInlineQueryResultMpeg4Gif, ITgInlineQueryResultPhoto,
  ///   ITgInlineQueryResultVenue, ITgInlineQueryResultVideo, ITgInlineQueryResultVoice.
  /// </summary>
  TTgInlineQueryResult = record
  private
    FValue: IInterface;
  public
    class operator Implicit(const AValue: ITgInlineQueryResultCachedAudio): TTgInlineQueryResult;
    class operator Implicit(const AValue: ITgInlineQueryResultCachedDocument): TTgInlineQueryResult;
    class operator Implicit(const AValue: ITgInlineQueryResultCachedGif): TTgInlineQueryResult;
    class operator Implicit(const AValue: ITgInlineQueryResultCachedMpeg4Gif): TTgInlineQueryResult;
    class operator Implicit(const AValue: ITgInlineQueryResultCachedPhoto): TTgInlineQueryResult;
    class operator Implicit(const AValue: ITgInlineQueryResultCachedSticker): TTgInlineQueryResult;
    class operator Implicit(const AValue: ITgInlineQueryResultCachedVideo): TTgInlineQueryResult;
    class operator Implicit(const AValue: ITgInlineQueryResultCachedVoice): TTgInlineQueryResult;
    class operator Implicit(const AValue: ITgInlineQueryResultArticle): TTgInlineQueryResult;
    class operator Implicit(const AValue: ITgInlineQueryResultAudio): TTgInlineQueryResult;
    class operator Implicit(const AValue: ITgInlineQueryResultContact): TTgInlineQueryResult;
    class operator Implicit(const AValue: ITgInlineQueryResultGame): TTgInlineQueryResult;
    class operator Implicit(const AValue: ITgInlineQueryResultDocument): TTgInlineQueryResult;
    class operator Implicit(const AValue: ITgInlineQueryResultGif): TTgInlineQueryResult;
    class operator Implicit(const AValue: ITgInlineQueryResultLocation): TTgInlineQueryResult;
    class operator Implicit(const AValue: ITgInlineQueryResultMpeg4Gif): TTgInlineQueryResult;
    class operator Implicit(const AValue: ITgInlineQueryResultPhoto): TTgInlineQueryResult;
    class operator Implicit(const AValue: ITgInlineQueryResultVenue): TTgInlineQueryResult;
    class operator Implicit(const AValue: ITgInlineQueryResultVideo): TTgInlineQueryResult;
    class operator Implicit(const AValue: ITgInlineQueryResultVoice): TTgInlineQueryResult;
    /// <summary>Значения элементов массива (для сериализации).</summary>
    class function Values(const AItems: array of TTgInlineQueryResult): TArray<IInterface>; static;
    /// <summary>Значение не задано.</summary>
    function IsEmpty: Boolean;
    /// <summary>Объект-вариант (ITgOutObject или ITgJsonObject).</summary>
    property Value: IInterface read FValue;
  end;

  /// <summary>
  ///   This object represents the content of a message to be sent as a result of an inline query.
  ///   Telegram clients currently support the following types: Принимает (неявное приведение):
  ///   ITgInputTextMessageContent, ITgInputRichMessageContent, ITgInputLocationMessageContent,
  ///   ITgInputVenueMessageContent, ITgInputContactMessageContent, ITgInputInvoiceMessageContent.
  /// </summary>
  TTgInputMessageContent = record
  private
    FValue: IInterface;
  public
    class operator Implicit(const AValue: ITgInputTextMessageContent): TTgInputMessageContent;
    class operator Implicit(const AValue: ITgInputRichMessageContent): TTgInputMessageContent;
    class operator Implicit(const AValue: ITgInputLocationMessageContent): TTgInputMessageContent;
    class operator Implicit(const AValue: ITgInputVenueMessageContent): TTgInputMessageContent;
    class operator Implicit(const AValue: ITgInputContactMessageContent): TTgInputMessageContent;
    class operator Implicit(const AValue: ITgInputInvoiceMessageContent): TTgInputMessageContent;
    /// <summary>Значения элементов массива (для сериализации).</summary>
    class function Values(const AItems: array of TTgInputMessageContent): TArray<IInterface>; static;
    /// <summary>Значение не задано.</summary>
    function IsEmpty: Boolean;
    /// <summary>Объект-вариант (ITgOutObject или ITgJsonObject).</summary>
    property Value: IInterface read FValue;
  end;

  /// <summary>
  ///   This object represents an error in the Telegram Passport element which was submitted that
  ///   should be resolved by the user. Принимает (неявное приведение):
  ///   ITgPassportElementErrorDataField, ITgPassportElementErrorFrontSide,
  ///   ITgPassportElementErrorReverseSide, ITgPassportElementErrorSelfie,
  ///   ITgPassportElementErrorFile, ITgPassportElementErrorFiles,
  ///   ITgPassportElementErrorTranslationFile, ITgPassportElementErrorTranslationFiles,
  ///   ITgPassportElementErrorUnspecified.
  /// </summary>
  TTgPassportElementError = record
  private
    FValue: IInterface;
  public
    class operator Implicit(const AValue: ITgPassportElementErrorDataField): TTgPassportElementError;
    class operator Implicit(const AValue: ITgPassportElementErrorFrontSide): TTgPassportElementError;
    class operator Implicit(const AValue: ITgPassportElementErrorReverseSide): TTgPassportElementError;
    class operator Implicit(const AValue: ITgPassportElementErrorSelfie): TTgPassportElementError;
    class operator Implicit(const AValue: ITgPassportElementErrorFile): TTgPassportElementError;
    class operator Implicit(const AValue: ITgPassportElementErrorFiles): TTgPassportElementError;
    class operator Implicit(const AValue: ITgPassportElementErrorTranslationFile): TTgPassportElementError;
    class operator Implicit(const AValue: ITgPassportElementErrorTranslationFiles): TTgPassportElementError;
    class operator Implicit(const AValue: ITgPassportElementErrorUnspecified): TTgPassportElementError;
    /// <summary>Значения элементов массива (для сериализации).</summary>
    class function Values(const AItems: array of TTgPassportElementError): TArray<IInterface>; static;
    /// <summary>Значение не задано.</summary>
    function IsEmpty: Boolean;
    /// <summary>Объект-вариант (ITgOutObject или ITgJsonObject).</summary>
    property Value: IInterface read FValue;
  end;

  /// <summary>
  ///   Медиа rich-сообщения: анимация, аудио, документ, фото, видео или голосовое сообщение.
  ///   Принимает (неявное приведение): ITgInputMediaAnimation, ITgInputMediaAudio,
  ///   ITgInputMediaDocument, ITgInputMediaPhoto, ITgInputMediaVideo, ITgInputMediaVoiceNote.
  /// </summary>
  TTgInputRichMedia = record
  private
    FValue: IInterface;
  public
    class operator Implicit(const AValue: ITgInputMediaAnimation): TTgInputRichMedia;
    class operator Implicit(const AValue: ITgInputMediaAudio): TTgInputRichMedia;
    class operator Implicit(const AValue: ITgInputMediaDocument): TTgInputRichMedia;
    class operator Implicit(const AValue: ITgInputMediaPhoto): TTgInputRichMedia;
    class operator Implicit(const AValue: ITgInputMediaVideo): TTgInputRichMedia;
    class operator Implicit(const AValue: ITgInputMediaVoiceNote): TTgInputRichMedia;
    /// <summary>Значения элементов массива (для сериализации).</summary>
    class function Values(const AItems: array of TTgInputRichMedia): TArray<IInterface>; static;
    /// <summary>Значение не задано.</summary>
    function IsEmpty: Boolean;
    /// <summary>Объект-вариант (ITgOutObject или ITgJsonObject).</summary>
    property Value: IInterface read FValue;
  end;

  /// <summary>
  ///   Разметка ответа: инлайн-клавиатура, обычная клавиатура, удаление клавиатуры или
  ///   принудительный ответ. Принимает (неявное приведение): ITgInlineKeyboardMarkup,
  ///   ITgReplyKeyboardMarkup, ITgReplyKeyboardRemove, ITgForceReply.
  /// </summary>
  TTgReplyMarkup = record
  private
    FValue: IInterface;
  public
    class operator Implicit(const AValue: ITgInlineKeyboardMarkup): TTgReplyMarkup;
    class operator Implicit(const AValue: ITgReplyKeyboardMarkup): TTgReplyMarkup;
    class operator Implicit(const AValue: ITgReplyKeyboardRemove): TTgReplyMarkup;
    class operator Implicit(const AValue: ITgForceReply): TTgReplyMarkup;
    /// <summary>Значения элементов массива (для сериализации).</summary>
    class function Values(const AItems: array of TTgReplyMarkup): TArray<IInterface>; static;
    /// <summary>Значение не задано.</summary>
    function IsEmpty: Boolean;
    /// <summary>Объект-вариант (ITgOutObject или ITgJsonObject).</summary>
    property Value: IInterface read FValue;
  end;

  /// <summary>
  ///   Элемент медиагруппы (sendMediaGroup): аудио, документ, live-фото, фото или видео. Принимает
  ///   (неявное приведение): ITgInputMediaAudio, ITgInputMediaDocument, ITgInputMediaLivePhoto,
  ///   ITgInputMediaPhoto, ITgInputMediaVideo.
  /// </summary>
  TTgMediaGroupItem = record
  private
    FValue: IInterface;
  public
    class operator Implicit(const AValue: ITgInputMediaAudio): TTgMediaGroupItem;
    class operator Implicit(const AValue: ITgInputMediaDocument): TTgMediaGroupItem;
    class operator Implicit(const AValue: ITgInputMediaLivePhoto): TTgMediaGroupItem;
    class operator Implicit(const AValue: ITgInputMediaPhoto): TTgMediaGroupItem;
    class operator Implicit(const AValue: ITgInputMediaVideo): TTgMediaGroupItem;
    /// <summary>Значения элементов массива (для сериализации).</summary>
    class function Values(const AItems: array of TTgMediaGroupItem): TArray<IInterface>; static;
    /// <summary>Значение не задано.</summary>
    function IsEmpty: Boolean;
    /// <summary>Объект-вариант (ITgOutObject или ITgJsonObject).</summary>
    property Value: IInterface read FValue;
  end;

