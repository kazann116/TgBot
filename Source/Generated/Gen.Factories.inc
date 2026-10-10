// Gen.Factories.inc — record-фабрики TTg<Name>: Create (исходящие), FromJson (входящие).
// Сгенерировано TgBotGen по Telegram Bot API 10.3 (August 24, 2026). Не редактируйте вручную.

  /// <summary>Создание ITgUpdate.</summary>
  TTgUpdate = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgUpdate; static;
  end;

  /// <summary>Создание ITgWebhookInfo.</summary>
  TTgWebhookInfo = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgWebhookInfo; static;
  end;

  /// <summary>Создание ITgUser.</summary>
  TTgUser = record
  public
    /// <summary>
    ///   Новый объект User с обязательными полями: id is_bot first_name. Необязательные поля
    ///   задаются методами With*. Аргументы копируются в момент вызова: последующие изменения
    ///   переданных объектов на этот не влияют.
    /// </summary>
    class function Create(AId: Int64; AIsBot: Boolean; const AFirstName: string): ITgUser; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgUser; static;
  end;

  /// <summary>Создание ITgChat.</summary>
  TTgChat = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChat; static;
  end;

  /// <summary>Создание ITgChatFullInfo.</summary>
  TTgChatFullInfo = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChatFullInfo; static;
  end;

  /// <summary>Создание ITgMaybeInaccessibleMessage.</summary>
  TTgMaybeInaccessibleMessage = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgMaybeInaccessibleMessage; static;
  end;

  /// <summary>Создание ITgMessage.</summary>
  TTgMessage = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgMessage; static;
  end;

  /// <summary>Создание ITgMessageId.</summary>
  TTgMessageId = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgMessageId; static;
  end;

  /// <summary>Создание ITgInaccessibleMessage.</summary>
  TTgInaccessibleMessage = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgInaccessibleMessage; static;
  end;

  /// <summary>Создание ITgMessageEntity.</summary>
  TTgMessageEntity = record
  public
    /// <summary>
    ///   Новый объект MessageEntity с обязательными полями: type offset length. Необязательные поля
    ///   задаются методами With*. Аргументы копируются в момент вызова: последующие изменения
    ///   переданных объектов на этот не влияют.
    /// </summary>
    class function Create(const AMessageEntityType: string; AOffset: Integer;
      ALength: Integer): ITgMessageEntity; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgMessageEntity; static;
  end;

  /// <summary>Создание ITgTextQuote.</summary>
  TTgTextQuote = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgTextQuote; static;
  end;

  /// <summary>Создание ITgExternalReplyInfo.</summary>
  TTgExternalReplyInfo = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgExternalReplyInfo; static;
  end;

  /// <summary>Создание ITgReplyParameters.</summary>
  TTgReplyParameters = record
  public
    /// <summary>
    ///   Новый объект ReplyParameters. Необязательные поля задаются методами With*.
    /// </summary>
    class function Create: ITgReplyParameters; static;
  end;

  /// <summary>Создание ITgEphemeralMessageParameters.</summary>
  TTgEphemeralMessageParameters = record
  public
    /// <summary>
    ///   Новый объект EphemeralMessageParameters с обязательными полями: receiver_user_id.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(AReceiverUserId: Int64): ITgEphemeralMessageParameters; static;
  end;

  /// <summary>Создание ITgMessageOrigin.</summary>
  TTgMessageOrigin = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgMessageOrigin; static;
  end;

  /// <summary>Создание ITgMessageOriginUser.</summary>
  TTgMessageOriginUser = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgMessageOriginUser; static;
  end;

  /// <summary>Создание ITgMessageOriginHiddenUser.</summary>
  TTgMessageOriginHiddenUser = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgMessageOriginHiddenUser; static;
  end;

  /// <summary>Создание ITgMessageOriginChat.</summary>
  TTgMessageOriginChat = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgMessageOriginChat; static;
  end;

  /// <summary>Создание ITgMessageOriginChannel.</summary>
  TTgMessageOriginChannel = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgMessageOriginChannel; static;
  end;

  /// <summary>Создание ITgPhotoSize.</summary>
  TTgPhotoSize = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgPhotoSize; static;
  end;

  /// <summary>Создание ITgAnimation.</summary>
  TTgAnimation = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgAnimation; static;
  end;

  /// <summary>Создание ITgAudio.</summary>
  TTgAudio = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgAudio; static;
  end;

  /// <summary>Создание ITgDocument.</summary>
  TTgDocument = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgDocument; static;
  end;

  /// <summary>Создание ITgLivePhoto.</summary>
  TTgLivePhoto = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgLivePhoto; static;
  end;

  /// <summary>Создание ITgStory.</summary>
  TTgStory = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgStory; static;
  end;

  /// <summary>Создание ITgVideoQuality.</summary>
  TTgVideoQuality = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgVideoQuality; static;
  end;

  /// <summary>Создание ITgVideo.</summary>
  TTgVideo = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgVideo; static;
  end;

  /// <summary>Создание ITgVideoNote.</summary>
  TTgVideoNote = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgVideoNote; static;
  end;

  /// <summary>Создание ITgVoice.</summary>
  TTgVoice = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgVoice; static;
  end;

  /// <summary>Создание ITgPaidMediaInfo.</summary>
  TTgPaidMediaInfo = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgPaidMediaInfo; static;
  end;

  /// <summary>Создание ITgPaidMedia.</summary>
  TTgPaidMedia = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgPaidMedia; static;
  end;

  /// <summary>Создание ITgPaidMediaLivePhoto.</summary>
  TTgPaidMediaLivePhoto = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgPaidMediaLivePhoto; static;
  end;

  /// <summary>Создание ITgPaidMediaPhoto.</summary>
  TTgPaidMediaPhoto = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgPaidMediaPhoto; static;
  end;

  /// <summary>Создание ITgPaidMediaPreview.</summary>
  TTgPaidMediaPreview = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgPaidMediaPreview; static;
  end;

  /// <summary>Создание ITgPaidMediaVideo.</summary>
  TTgPaidMediaVideo = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgPaidMediaVideo; static;
  end;

  /// <summary>Создание ITgContact.</summary>
  TTgContact = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgContact; static;
  end;

  /// <summary>Создание ITgDice.</summary>
  TTgDice = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgDice; static;
  end;

  /// <summary>Создание ITgLink.</summary>
  TTgLink = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgLink; static;
  end;

  /// <summary>Создание ITgPollMedia.</summary>
  TTgPollMedia = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgPollMedia; static;
  end;

  /// <summary>Создание ITgPollOption.</summary>
  TTgPollOption = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgPollOption; static;
  end;

  /// <summary>Создание ITgInputPollOption.</summary>
  TTgInputPollOption = record
  public
    /// <summary>
    ///   Новый объект InputPollOption с обязательными полями: text. Необязательные поля задаются
    ///   методами With*.
    /// </summary>
    class function Create(const AText: string): ITgInputPollOption; static;
  end;

  /// <summary>Создание ITgPollAnswer.</summary>
  TTgPollAnswer = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgPollAnswer; static;
  end;

  /// <summary>Создание ITgPoll.</summary>
  TTgPoll = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgPoll; static;
  end;

  /// <summary>Создание ITgChecklistTask.</summary>
  TTgChecklistTask = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChecklistTask; static;
  end;

  /// <summary>Создание ITgChecklist.</summary>
  TTgChecklist = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChecklist; static;
  end;

  /// <summary>Создание ITgInputChecklistTask.</summary>
  TTgInputChecklistTask = record
  public
    /// <summary>
    ///   Новый объект InputChecklistTask с обязательными полями: id text. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(AId: Int64; const AText: string): ITgInputChecklistTask; static;
  end;

  /// <summary>Создание ITgInputChecklist.</summary>
  TTgInputChecklist = record
  public
    /// <summary>
    ///   Новый объект InputChecklist с обязательными полями: title tasks. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const ATitle: string;
      const ATasks: array of ITgInputChecklistTask): ITgInputChecklist; static;
  end;

  /// <summary>Создание ITgLocation.</summary>
  TTgLocation = record
  public
    /// <summary>
    ///   Новый объект Location с обязательными полями: latitude longitude. Необязательные поля
    ///   задаются методами With*. Аргументы копируются в момент вызова: последующие изменения
    ///   переданных объектов на этот не влияют.
    /// </summary>
    class function Create(ALatitude: Double; ALongitude: Double): ITgLocation; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgLocation; static;
  end;

  /// <summary>Создание ITgVenue.</summary>
  TTgVenue = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgVenue; static;
  end;

  /// <summary>Создание ITgWebAppData.</summary>
  TTgWebAppData = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgWebAppData; static;
  end;

  /// <summary>Создание ITgProximityAlertTriggered.</summary>
  TTgProximityAlertTriggered = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgProximityAlertTriggered; static;
  end;

  /// <summary>Создание ITgMessageAutoDeleteTimerChanged.</summary>
  TTgMessageAutoDeleteTimerChanged = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgMessageAutoDeleteTimerChanged; static;
  end;

  /// <summary>Создание ITgManagedBotCreated.</summary>
  TTgManagedBotCreated = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgManagedBotCreated; static;
  end;

  /// <summary>Создание ITgManagedBotUpdated.</summary>
  TTgManagedBotUpdated = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgManagedBotUpdated; static;
  end;

  /// <summary>Создание ITgBotSubscriptionUpdated.</summary>
  TTgBotSubscriptionUpdated = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgBotSubscriptionUpdated; static;
  end;

  /// <summary>Создание ITgMessageGenerationStopped.</summary>
  TTgMessageGenerationStopped = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgMessageGenerationStopped; static;
  end;

  /// <summary>Создание ITgPollOptionAdded.</summary>
  TTgPollOptionAdded = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgPollOptionAdded; static;
  end;

  /// <summary>Создание ITgPollOptionDeleted.</summary>
  TTgPollOptionDeleted = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgPollOptionDeleted; static;
  end;

  /// <summary>Создание ITgChatBoostAdded.</summary>
  TTgChatBoostAdded = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChatBoostAdded; static;
  end;

  /// <summary>Создание ITgBackgroundFill.</summary>
  TTgBackgroundFill = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgBackgroundFill; static;
  end;

  /// <summary>Создание ITgBackgroundFillSolid.</summary>
  TTgBackgroundFillSolid = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgBackgroundFillSolid; static;
  end;

  /// <summary>Создание ITgBackgroundFillGradient.</summary>
  TTgBackgroundFillGradient = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgBackgroundFillGradient; static;
  end;

  /// <summary>Создание ITgBackgroundFillFreeformGradient.</summary>
  TTgBackgroundFillFreeformGradient = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgBackgroundFillFreeformGradient; static;
  end;

  /// <summary>Создание ITgBackgroundType.</summary>
  TTgBackgroundType = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgBackgroundType; static;
  end;

  /// <summary>Создание ITgBackgroundTypeFill.</summary>
  TTgBackgroundTypeFill = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgBackgroundTypeFill; static;
  end;

  /// <summary>Создание ITgBackgroundTypeWallpaper.</summary>
  TTgBackgroundTypeWallpaper = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgBackgroundTypeWallpaper; static;
  end;

  /// <summary>Создание ITgBackgroundTypePattern.</summary>
  TTgBackgroundTypePattern = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgBackgroundTypePattern; static;
  end;

  /// <summary>Создание ITgBackgroundTypeChatTheme.</summary>
  TTgBackgroundTypeChatTheme = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgBackgroundTypeChatTheme; static;
  end;

  /// <summary>Создание ITgChatBackground.</summary>
  TTgChatBackground = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChatBackground; static;
  end;

  /// <summary>Создание ITgChecklistTasksDone.</summary>
  TTgChecklistTasksDone = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChecklistTasksDone; static;
  end;

  /// <summary>Создание ITgChecklistTasksAdded.</summary>
  TTgChecklistTasksAdded = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChecklistTasksAdded; static;
  end;

  /// <summary>Создание ITgCommunityChatAdded.</summary>
  TTgCommunityChatAdded = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgCommunityChatAdded; static;
  end;

  /// <summary>Создание ITgCommunityChatJoined.</summary>
  TTgCommunityChatJoined = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgCommunityChatJoined; static;
  end;

  /// <summary>Создание ITgCommunityChatRemoved.</summary>
  TTgCommunityChatRemoved = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgCommunityChatRemoved; static;
  end;

  /// <summary>Создание ITgForumTopicCreated.</summary>
  TTgForumTopicCreated = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgForumTopicCreated; static;
  end;

  /// <summary>Создание ITgForumTopicClosed.</summary>
  TTgForumTopicClosed = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgForumTopicClosed; static;
  end;

  /// <summary>Создание ITgForumTopicEdited.</summary>
  TTgForumTopicEdited = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgForumTopicEdited; static;
  end;

  /// <summary>Создание ITgForumTopicReopened.</summary>
  TTgForumTopicReopened = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgForumTopicReopened; static;
  end;

  /// <summary>Создание ITgGeneralForumTopicHidden.</summary>
  TTgGeneralForumTopicHidden = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgGeneralForumTopicHidden; static;
  end;

  /// <summary>Создание ITgGeneralForumTopicUnhidden.</summary>
  TTgGeneralForumTopicUnhidden = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgGeneralForumTopicUnhidden; static;
  end;

  /// <summary>Создание ITgSharedUser.</summary>
  TTgSharedUser = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgSharedUser; static;
  end;

  /// <summary>Создание ITgUsersShared.</summary>
  TTgUsersShared = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgUsersShared; static;
  end;

  /// <summary>Создание ITgChatShared.</summary>
  TTgChatShared = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChatShared; static;
  end;

  /// <summary>Создание ITgWriteAccessAllowed.</summary>
  TTgWriteAccessAllowed = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgWriteAccessAllowed; static;
  end;

  /// <summary>Создание ITgVideoChatScheduled.</summary>
  TTgVideoChatScheduled = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgVideoChatScheduled; static;
  end;

  /// <summary>Создание ITgVideoChatStarted.</summary>
  TTgVideoChatStarted = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgVideoChatStarted; static;
  end;

  /// <summary>Создание ITgVideoChatEnded.</summary>
  TTgVideoChatEnded = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgVideoChatEnded; static;
  end;

  /// <summary>Создание ITgVideoChatParticipantsInvited.</summary>
  TTgVideoChatParticipantsInvited = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgVideoChatParticipantsInvited; static;
  end;

  /// <summary>Создание ITgPaidMessagePriceChanged.</summary>
  TTgPaidMessagePriceChanged = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgPaidMessagePriceChanged; static;
  end;

  /// <summary>Создание ITgDirectMessagePriceChanged.</summary>
  TTgDirectMessagePriceChanged = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgDirectMessagePriceChanged; static;
  end;

  /// <summary>Создание ITgSuggestedPostApproved.</summary>
  TTgSuggestedPostApproved = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgSuggestedPostApproved; static;
  end;

  /// <summary>Создание ITgSuggestedPostApprovalFailed.</summary>
  TTgSuggestedPostApprovalFailed = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgSuggestedPostApprovalFailed; static;
  end;

  /// <summary>Создание ITgSuggestedPostDeclined.</summary>
  TTgSuggestedPostDeclined = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgSuggestedPostDeclined; static;
  end;

  /// <summary>Создание ITgSuggestedPostPaid.</summary>
  TTgSuggestedPostPaid = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgSuggestedPostPaid; static;
  end;

  /// <summary>Создание ITgSuggestedPostRefunded.</summary>
  TTgSuggestedPostRefunded = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgSuggestedPostRefunded; static;
  end;

  /// <summary>Создание ITgGiveawayCreated.</summary>
  TTgGiveawayCreated = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgGiveawayCreated; static;
  end;

  /// <summary>Создание ITgGiveaway.</summary>
  TTgGiveaway = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgGiveaway; static;
  end;

  /// <summary>Создание ITgGiveawayWinners.</summary>
  TTgGiveawayWinners = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgGiveawayWinners; static;
  end;

  /// <summary>Создание ITgGiveawayCompleted.</summary>
  TTgGiveawayCompleted = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgGiveawayCompleted; static;
  end;

  /// <summary>Создание ITgLinkPreviewOptions.</summary>
  TTgLinkPreviewOptions = record
  public
    /// <summary>
    ///   Новый объект LinkPreviewOptions. Необязательные поля задаются методами With*. Аргументы
    ///   копируются в момент вызова: последующие изменения переданных объектов на этот не влияют.
    /// </summary>
    class function Create: ITgLinkPreviewOptions; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgLinkPreviewOptions; static;
  end;

  /// <summary>Создание ITgSuggestedPostPrice.</summary>
  TTgSuggestedPostPrice = record
  public
    /// <summary>
    ///   Новый объект SuggestedPostPrice с обязательными полями: currency amount. Необязательные
    ///   поля задаются методами With*. Аргументы копируются в момент вызова: последующие изменения
    ///   переданных объектов на этот не влияют.
    /// </summary>
    class function Create(const ACurrency: string; AAmount: Integer): ITgSuggestedPostPrice; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgSuggestedPostPrice; static;
  end;

  /// <summary>Создание ITgSuggestedPostInfo.</summary>
  TTgSuggestedPostInfo = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgSuggestedPostInfo; static;
  end;

  /// <summary>Создание ITgSuggestedPostParameters.</summary>
  TTgSuggestedPostParameters = record
  public
    /// <summary>
    ///   Новый объект SuggestedPostParameters. Необязательные поля задаются методами With*.
    /// </summary>
    class function Create: ITgSuggestedPostParameters; static;
  end;

  /// <summary>Создание ITgDirectMessagesTopic.</summary>
  TTgDirectMessagesTopic = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgDirectMessagesTopic; static;
  end;

  /// <summary>Создание ITgUserProfilePhotos.</summary>
  TTgUserProfilePhotos = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgUserProfilePhotos; static;
  end;

  /// <summary>Создание ITgUserProfileAudios.</summary>
  TTgUserProfileAudios = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgUserProfileAudios; static;
  end;

  /// <summary>Создание ITgFile.</summary>
  TTgFile = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgFile; static;
  end;

  /// <summary>Создание ITgWebAppInfo.</summary>
  TTgWebAppInfo = record
  public
    /// <summary>
    ///   Новый объект WebAppInfo с обязательными полями: url. Необязательные поля задаются методами
    ///   With*. Аргументы копируются в момент вызова: последующие изменения переданных объектов на
    ///   этот не влияют.
    /// </summary>
    class function Create(const AUrl: string): ITgWebAppInfo; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgWebAppInfo; static;
  end;

  /// <summary>Создание ITgReplyKeyboardMarkup.</summary>
  TTgReplyKeyboardMarkup = record
  public
    /// <summary>
    ///   Новый объект ReplyKeyboardMarkup с обязательными полями: keyboard. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const AKeyboard: array of TArray<ITgKeyboardButton>): ITgReplyKeyboardMarkup; static;
  end;

  /// <summary>Создание ITgKeyboardButton.</summary>
  TTgKeyboardButton = record
  public
    /// <summary>
    ///   Новый объект KeyboardButton с обязательными полями: text. Необязательные поля задаются
    ///   методами With*.
    /// </summary>
    class function Create(const AText: string): ITgKeyboardButton; static;
  end;

  /// <summary>Создание ITgKeyboardButtonRequestUsers.</summary>
  TTgKeyboardButtonRequestUsers = record
  public
    /// <summary>
    ///   Новый объект KeyboardButtonRequestUsers с обязательными полями: request_id. Необязательные
    ///   поля задаются методами With*.
    /// </summary>
    class function Create(ARequestId: Int64): ITgKeyboardButtonRequestUsers; static;
  end;

  /// <summary>Создание ITgKeyboardButtonRequestChat.</summary>
  TTgKeyboardButtonRequestChat = record
  public
    /// <summary>
    ///   Новый объект KeyboardButtonRequestChat с обязательными полями: request_id chat_is_channel.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(ARequestId: Int64; AChatIsChannel: Boolean): ITgKeyboardButtonRequestChat;
      static;
  end;

  /// <summary>Создание ITgKeyboardButtonRequestManagedBot.</summary>
  TTgKeyboardButtonRequestManagedBot = record
  public
    /// <summary>
    ///   Новый объект KeyboardButtonRequestManagedBot с обязательными полями: request_id.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(ARequestId: Int64): ITgKeyboardButtonRequestManagedBot; static;
  end;

  /// <summary>Создание ITgKeyboardButtonPollType.</summary>
  TTgKeyboardButtonPollType = record
  public
    /// <summary>
    ///   Новый объект KeyboardButtonPollType. Необязательные поля задаются методами With*.
    /// </summary>
    class function Create: ITgKeyboardButtonPollType; static;
  end;

  /// <summary>Создание ITgReplyKeyboardRemove.</summary>
  TTgReplyKeyboardRemove = record
  public
    /// <summary>
    ///   Новый объект ReplyKeyboardRemove. Необязательные поля задаются методами With*.
    /// </summary>
    class function Create: ITgReplyKeyboardRemove; static;
  end;

  /// <summary>Создание ITgInlineKeyboardMarkup.</summary>
  TTgInlineKeyboardMarkup = record
  public
    /// <summary>
    ///   Новый объект InlineKeyboardMarkup с обязательными полями: inline_keyboard. Необязательные
    ///   поля задаются методами With*. Аргументы копируются в момент вызова: последующие изменения
    ///   переданных объектов на этот не влияют.
    /// </summary>
    class function Create(const AInlineKeyboard: array of TArray<ITgInlineKeyboardButton>): ITgInlineKeyboardMarkup; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgInlineKeyboardMarkup; static;
  end;

  /// <summary>Создание ITgInlineKeyboardButton.</summary>
  TTgInlineKeyboardButton = record
  public
    /// <summary>
    ///   Новый объект InlineKeyboardButton с обязательными полями: text. Необязательные поля
    ///   задаются методами With*. Аргументы копируются в момент вызова: последующие изменения
    ///   переданных объектов на этот не влияют.
    /// </summary>
    class function Create(const AText: string): ITgInlineKeyboardButton; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgInlineKeyboardButton; static;
  end;

  /// <summary>Создание ITgLoginUrl.</summary>
  TTgLoginUrl = record
  public
    /// <summary>
    ///   Новый объект LoginUrl с обязательными полями: url. Необязательные поля задаются методами
    ///   With*. Аргументы копируются в момент вызова: последующие изменения переданных объектов на
    ///   этот не влияют.
    /// </summary>
    class function Create(const AUrl: string): ITgLoginUrl; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgLoginUrl; static;
  end;

  /// <summary>Создание ITgSwitchInlineQueryChosenChat.</summary>
  TTgSwitchInlineQueryChosenChat = record
  public
    /// <summary>
    ///   Новый объект SwitchInlineQueryChosenChat. Необязательные поля задаются методами With*.
    ///   Аргументы копируются в момент вызова: последующие изменения переданных объектов на этот не
    ///   влияют.
    /// </summary>
    class function Create: ITgSwitchInlineQueryChosenChat; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgSwitchInlineQueryChosenChat; static;
  end;

  /// <summary>Создание ITgCopyTextButton.</summary>
  TTgCopyTextButton = record
  public
    /// <summary>
    ///   Новый объект CopyTextButton с обязательными полями: text. Необязательные поля задаются
    ///   методами With*. Аргументы копируются в момент вызова: последующие изменения переданных
    ///   объектов на этот не влияют.
    /// </summary>
    class function Create(const AText: string): ITgCopyTextButton; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgCopyTextButton; static;
  end;

  /// <summary>Создание ITgDisabledButton.</summary>
  TTgDisabledButton = record
  public
    /// <summary>
    ///   Новый объект DisabledButton. Необязательные поля задаются методами With*. Аргументы
    ///   копируются в момент вызова: последующие изменения переданных объектов на этот не влияют.
    /// </summary>
    class function Create: ITgDisabledButton; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgDisabledButton; static;
  end;

  /// <summary>Создание ITgCallbackQuery.</summary>
  TTgCallbackQuery = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgCallbackQuery; static;
  end;

  /// <summary>Создание ITgForceReply.</summary>
  TTgForceReply = record
  public
    /// <summary>
    ///   Новый объект ForceReply. Необязательные поля задаются методами With*.
    /// </summary>
    class function Create: ITgForceReply; static;
  end;

  /// <summary>Создание ITgCommunity.</summary>
  TTgCommunity = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgCommunity; static;
  end;

  /// <summary>Создание ITgChatPhoto.</summary>
  TTgChatPhoto = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChatPhoto; static;
  end;

  /// <summary>Создание ITgChatInviteLink.</summary>
  TTgChatInviteLink = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChatInviteLink; static;
  end;

  /// <summary>Создание ITgChatAdministratorRights.</summary>
  TTgChatAdministratorRights = record
  public
    /// <summary>
    ///   Новый объект ChatAdministratorRights с обязательными полями: is_anonymous can_manage_chat
    ///   can_delete_messages can_manage_video_chats can_restrict_members can_promote_members
    ///   can_change_info can_invite_users can_post_stories can_edit_stories can_delete_stories
    ///   can_send_welcome_messages. Необязательные поля задаются методами With*. Аргументы
    ///   копируются в момент вызова: последующие изменения переданных объектов на этот не влияют.
    /// </summary>
    class function Create(AIsAnonymous: Boolean; ACanManageChat: Boolean;
      ACanDeleteMessages: Boolean; ACanManageVideoChats: Boolean; ACanRestrictMembers: Boolean;
      ACanPromoteMembers: Boolean; ACanChangeInfo: Boolean; ACanInviteUsers: Boolean;
      ACanPostStories: Boolean; ACanEditStories: Boolean; ACanDeleteStories: Boolean;
      ACanSendWelcomeMessages: Boolean): ITgChatAdministratorRights; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChatAdministratorRights; static;
  end;

  /// <summary>Создание ITgChatMemberUpdated.</summary>
  TTgChatMemberUpdated = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChatMemberUpdated; static;
  end;

  /// <summary>Создание ITgChatMember.</summary>
  TTgChatMember = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChatMember; static;
  end;

  /// <summary>Создание ITgChatMemberOwner.</summary>
  TTgChatMemberOwner = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChatMemberOwner; static;
  end;

  /// <summary>Создание ITgChatMemberAdministrator.</summary>
  TTgChatMemberAdministrator = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChatMemberAdministrator; static;
  end;

  /// <summary>Создание ITgChatMemberMember.</summary>
  TTgChatMemberMember = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChatMemberMember; static;
  end;

  /// <summary>Создание ITgChatMemberRestricted.</summary>
  TTgChatMemberRestricted = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChatMemberRestricted; static;
  end;

  /// <summary>Создание ITgChatMemberLeft.</summary>
  TTgChatMemberLeft = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChatMemberLeft; static;
  end;

  /// <summary>Создание ITgChatMemberBanned.</summary>
  TTgChatMemberBanned = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChatMemberBanned; static;
  end;

  /// <summary>Создание ITgChatJoinRequest.</summary>
  TTgChatJoinRequest = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChatJoinRequest; static;
  end;

  /// <summary>Создание ITgChatPermissions.</summary>
  TTgChatPermissions = record
  public
    /// <summary>
    ///   Новый объект ChatPermissions. Необязательные поля задаются методами With*. Аргументы
    ///   копируются в момент вызова: последующие изменения переданных объектов на этот не влияют.
    /// </summary>
    class function Create: ITgChatPermissions; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChatPermissions; static;
  end;

  /// <summary>Создание ITgBirthdate.</summary>
  TTgBirthdate = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgBirthdate; static;
  end;

  /// <summary>Создание ITgBusinessIntro.</summary>
  TTgBusinessIntro = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgBusinessIntro; static;
  end;

  /// <summary>Создание ITgBusinessLocation.</summary>
  TTgBusinessLocation = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgBusinessLocation; static;
  end;

  /// <summary>Создание ITgBusinessOpeningHoursInterval.</summary>
  TTgBusinessOpeningHoursInterval = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgBusinessOpeningHoursInterval; static;
  end;

  /// <summary>Создание ITgBusinessOpeningHours.</summary>
  TTgBusinessOpeningHours = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgBusinessOpeningHours; static;
  end;

  /// <summary>Создание ITgUserRating.</summary>
  TTgUserRating = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgUserRating; static;
  end;

  /// <summary>Создание ITgStoryAreaPosition.</summary>
  TTgStoryAreaPosition = record
  public
    /// <summary>
    ///   Новый объект StoryAreaPosition с обязательными полями: x_percentage y_percentage
    ///   width_percentage height_percentage rotation_angle corner_radius_percentage. Необязательные
    ///   поля задаются методами With*.
    /// </summary>
    class function Create(AXPercentage: Double; AYPercentage: Double; AWidthPercentage: Double;
      AHeightPercentage: Double; ARotationAngle: Double;
      ACornerRadiusPercentage: Double): ITgStoryAreaPosition; static;
  end;

  /// <summary>Создание ITgLocationAddress.</summary>
  TTgLocationAddress = record
  public
    /// <summary>
    ///   Новый объект LocationAddress с обязательными полями: country_code. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const ACountryCode: string): ITgLocationAddress; static;
  end;

  /// <summary>Создание ITgStoryAreaTypeLocation.</summary>
  TTgStoryAreaTypeLocation = record
  public
    /// <summary>
    ///   Новый объект StoryAreaTypeLocation с обязательными полями: latitude longitude.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(ALatitude: Double; ALongitude: Double): ITgStoryAreaTypeLocation; static;
  end;

  /// <summary>Создание ITgStoryAreaTypeSuggestedReaction.</summary>
  TTgStoryAreaTypeSuggestedReaction = record
  public
    /// <summary>
    ///   Новый объект StoryAreaTypeSuggestedReaction с обязательными полями: reaction_type.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const AReactionType: ITgReactionType): ITgStoryAreaTypeSuggestedReaction;
      static;
  end;

  /// <summary>Создание ITgStoryAreaTypeLink.</summary>
  TTgStoryAreaTypeLink = record
  public
    /// <summary>
    ///   Новый объект StoryAreaTypeLink с обязательными полями: url. Необязательные поля задаются
    ///   методами With*.
    /// </summary>
    class function Create(const AUrl: string): ITgStoryAreaTypeLink; static;
  end;

  /// <summary>Создание ITgStoryAreaTypeWeather.</summary>
  TTgStoryAreaTypeWeather = record
  public
    /// <summary>
    ///   Новый объект StoryAreaTypeWeather с обязательными полями: temperature emoji
    ///   background_color. Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(ATemperature: Double; const AEmoji: string;
      ABackgroundColor: Integer): ITgStoryAreaTypeWeather; static;
  end;

  /// <summary>Создание ITgStoryAreaTypeUniqueGift.</summary>
  TTgStoryAreaTypeUniqueGift = record
  public
    /// <summary>
    ///   Новый объект StoryAreaTypeUniqueGift с обязательными полями: name. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const AName: string): ITgStoryAreaTypeUniqueGift; static;
  end;

  /// <summary>Создание ITgStoryArea.</summary>
  TTgStoryArea = record
  public
    /// <summary>
    ///   Новый объект StoryArea с обязательными полями: position type. Необязательные поля задаются
    ///   методами With*.
    /// </summary>
    class function Create(const APosition: ITgStoryAreaPosition;
      const AStoryAreaType: TTgStoryAreaType): ITgStoryArea; static;
  end;

  /// <summary>Создание ITgChatLocation.</summary>
  TTgChatLocation = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChatLocation; static;
  end;

  /// <summary>Создание ITgReactionType.</summary>
  TTgReactionType = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgReactionType; static;
  end;

  /// <summary>Создание ITgReactionTypeEmoji.</summary>
  TTgReactionTypeEmoji = record
  public
    /// <summary>
    ///   Новый объект ReactionTypeEmoji с обязательными полями: emoji. Необязательные поля задаются
    ///   методами With*. Аргументы копируются в момент вызова: последующие изменения переданных
    ///   объектов на этот не влияют.
    /// </summary>
    class function Create(const AEmoji: string): ITgReactionTypeEmoji; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgReactionTypeEmoji; static;
  end;

  /// <summary>Создание ITgReactionTypeCustomEmoji.</summary>
  TTgReactionTypeCustomEmoji = record
  public
    /// <summary>
    ///   Новый объект ReactionTypeCustomEmoji с обязательными полями: custom_emoji_id.
    ///   Необязательные поля задаются методами With*. Аргументы копируются в момент вызова:
    ///   последующие изменения переданных объектов на этот не влияют.
    /// </summary>
    class function Create(const ACustomEmojiId: string): ITgReactionTypeCustomEmoji; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgReactionTypeCustomEmoji; static;
  end;

  /// <summary>Создание ITgReactionTypePaid.</summary>
  TTgReactionTypePaid = record
  public
    /// <summary>
    ///   Новый объект ReactionTypePaid. Необязательные поля задаются методами With*. Аргументы
    ///   копируются в момент вызова: последующие изменения переданных объектов на этот не влияют.
    /// </summary>
    class function Create: ITgReactionTypePaid; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgReactionTypePaid; static;
  end;

  /// <summary>Создание ITgReactionCount.</summary>
  TTgReactionCount = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgReactionCount; static;
  end;

  /// <summary>Создание ITgMessageReactionUpdated.</summary>
  TTgMessageReactionUpdated = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgMessageReactionUpdated; static;
  end;

  /// <summary>Создание ITgMessageReactionCountUpdated.</summary>
  TTgMessageReactionCountUpdated = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgMessageReactionCountUpdated; static;
  end;

  /// <summary>Создание ITgForumTopic.</summary>
  TTgForumTopic = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgForumTopic; static;
  end;

  /// <summary>Создание ITgGiftBackground.</summary>
  TTgGiftBackground = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgGiftBackground; static;
  end;

  /// <summary>Создание ITgGift.</summary>
  TTgGift = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgGift; static;
  end;

  /// <summary>Создание ITgGifts.</summary>
  TTgGifts = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgGifts; static;
  end;

  /// <summary>Создание ITgUniqueGiftModel.</summary>
  TTgUniqueGiftModel = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgUniqueGiftModel; static;
  end;

  /// <summary>Создание ITgUniqueGiftSymbol.</summary>
  TTgUniqueGiftSymbol = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgUniqueGiftSymbol; static;
  end;

  /// <summary>Создание ITgUniqueGiftBackdropColors.</summary>
  TTgUniqueGiftBackdropColors = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgUniqueGiftBackdropColors; static;
  end;

  /// <summary>Создание ITgUniqueGiftBackdrop.</summary>
  TTgUniqueGiftBackdrop = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgUniqueGiftBackdrop; static;
  end;

  /// <summary>Создание ITgUniqueGiftColors.</summary>
  TTgUniqueGiftColors = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgUniqueGiftColors; static;
  end;

  /// <summary>Создание ITgUniqueGift.</summary>
  TTgUniqueGift = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgUniqueGift; static;
  end;

  /// <summary>Создание ITgGiftInfo.</summary>
  TTgGiftInfo = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgGiftInfo; static;
  end;

  /// <summary>Создание ITgUniqueGiftInfo.</summary>
  TTgUniqueGiftInfo = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgUniqueGiftInfo; static;
  end;

  /// <summary>Создание ITgOwnedGift.</summary>
  TTgOwnedGift = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgOwnedGift; static;
  end;

  /// <summary>Создание ITgOwnedGiftRegular.</summary>
  TTgOwnedGiftRegular = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgOwnedGiftRegular; static;
  end;

  /// <summary>Создание ITgOwnedGiftUnique.</summary>
  TTgOwnedGiftUnique = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgOwnedGiftUnique; static;
  end;

  /// <summary>Создание ITgOwnedGifts.</summary>
  TTgOwnedGifts = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgOwnedGifts; static;
  end;

  /// <summary>Создание ITgBotAccessSettings.</summary>
  TTgBotAccessSettings = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgBotAccessSettings; static;
  end;

  /// <summary>Создание ITgAcceptedGiftTypes.</summary>
  TTgAcceptedGiftTypes = record
  public
    /// <summary>
    ///   Новый объект AcceptedGiftTypes с обязательными полями: unlimited_gifts limited_gifts
    ///   unique_gifts premium_subscription gifts_from_channels. Необязательные поля задаются
    ///   методами With*. Аргументы копируются в момент вызова: последующие изменения переданных
    ///   объектов на этот не влияют.
    /// </summary>
    class function Create(AUnlimitedGifts: Boolean; ALimitedGifts: Boolean; AUniqueGifts: Boolean;
      APremiumSubscription: Boolean; AGiftsFromChannels: Boolean): ITgAcceptedGiftTypes; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgAcceptedGiftTypes; static;
  end;

  /// <summary>Создание ITgStarAmount.</summary>
  TTgStarAmount = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgStarAmount; static;
  end;

  /// <summary>Создание ITgBotCommand.</summary>
  TTgBotCommand = record
  public
    /// <summary>
    ///   Новый объект BotCommand с обязательными полями: command description. Необязательные поля
    ///   задаются методами With*. Аргументы копируются в момент вызова: последующие изменения
    ///   переданных объектов на этот не влияют.
    /// </summary>
    class function Create(const ACommand: string; const ADescription: string): ITgBotCommand;
      static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgBotCommand; static;
  end;

  /// <summary>Создание ITgBotCommandScopeDefault.</summary>
  TTgBotCommandScopeDefault = record
  public
    /// <summary>
    ///   Новый объект BotCommandScopeDefault. Необязательные поля задаются методами With*.
    /// </summary>
    class function Create: ITgBotCommandScopeDefault; static;
  end;

  /// <summary>Создание ITgBotCommandScopeAllPrivateChats.</summary>
  TTgBotCommandScopeAllPrivateChats = record
  public
    /// <summary>
    ///   Новый объект BotCommandScopeAllPrivateChats. Необязательные поля задаются методами With*.
    /// </summary>
    class function Create: ITgBotCommandScopeAllPrivateChats; static;
  end;

  /// <summary>Создание ITgBotCommandScopeAllGroupChats.</summary>
  TTgBotCommandScopeAllGroupChats = record
  public
    /// <summary>
    ///   Новый объект BotCommandScopeAllGroupChats. Необязательные поля задаются методами With*.
    /// </summary>
    class function Create: ITgBotCommandScopeAllGroupChats; static;
  end;

  /// <summary>Создание ITgBotCommandScopeAllChatAdministrators.</summary>
  TTgBotCommandScopeAllChatAdministrators = record
  public
    /// <summary>
    ///   Новый объект BotCommandScopeAllChatAdministrators. Необязательные поля задаются методами
    ///   With*.
    /// </summary>
    class function Create: ITgBotCommandScopeAllChatAdministrators; static;
  end;

  /// <summary>Создание ITgBotCommandScopeChat.</summary>
  TTgBotCommandScopeChat = record
  public
    /// <summary>
    ///   Новый объект BotCommandScopeChat с обязательными полями: chat_id. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const AChatId: TTgChatId): ITgBotCommandScopeChat; static;
  end;

  /// <summary>Создание ITgBotCommandScopeChatAdministrators.</summary>
  TTgBotCommandScopeChatAdministrators = record
  public
    /// <summary>
    ///   Новый объект BotCommandScopeChatAdministrators с обязательными полями: chat_id.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const AChatId: TTgChatId): ITgBotCommandScopeChatAdministrators; static;
  end;

  /// <summary>Создание ITgBotCommandScopeChatMember.</summary>
  TTgBotCommandScopeChatMember = record
  public
    /// <summary>
    ///   Новый объект BotCommandScopeChatMember с обязательными полями: chat_id user_id.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const AChatId: TTgChatId; AUserId: Int64): ITgBotCommandScopeChatMember;
      static;
  end;

  /// <summary>Создание ITgBotName.</summary>
  TTgBotName = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgBotName; static;
  end;

  /// <summary>Создание ITgBotDescription.</summary>
  TTgBotDescription = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgBotDescription; static;
  end;

  /// <summary>Создание ITgBotShortDescription.</summary>
  TTgBotShortDescription = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgBotShortDescription; static;
  end;

  /// <summary>Создание ITgMenuButton.</summary>
  TTgMenuButton = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgMenuButton; static;
  end;

  /// <summary>Создание ITgMenuButtonCommands.</summary>
  TTgMenuButtonCommands = record
  public
    /// <summary>
    ///   Новый объект MenuButtonCommands. Необязательные поля задаются методами With*. Аргументы
    ///   копируются в момент вызова: последующие изменения переданных объектов на этот не влияют.
    /// </summary>
    class function Create: ITgMenuButtonCommands; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgMenuButtonCommands; static;
  end;

  /// <summary>Создание ITgMenuButtonWebApp.</summary>
  TTgMenuButtonWebApp = record
  public
    /// <summary>
    ///   Новый объект MenuButtonWebApp с обязательными полями: text web_app. Необязательные поля
    ///   задаются методами With*. Аргументы копируются в момент вызова: последующие изменения
    ///   переданных объектов на этот не влияют.
    /// </summary>
    class function Create(const AText: string; const AWebApp: ITgWebAppInfo): ITgMenuButtonWebApp;
      static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgMenuButtonWebApp; static;
  end;

  /// <summary>Создание ITgMenuButtonDefault.</summary>
  TTgMenuButtonDefault = record
  public
    /// <summary>
    ///   Новый объект MenuButtonDefault. Необязательные поля задаются методами With*. Аргументы
    ///   копируются в момент вызова: последующие изменения переданных объектов на этот не влияют.
    /// </summary>
    class function Create: ITgMenuButtonDefault; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgMenuButtonDefault; static;
  end;

  /// <summary>Создание ITgChatBoostSource.</summary>
  TTgChatBoostSource = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChatBoostSource; static;
  end;

  /// <summary>Создание ITgChatBoostSourcePremium.</summary>
  TTgChatBoostSourcePremium = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChatBoostSourcePremium; static;
  end;

  /// <summary>Создание ITgChatBoostSourceGiftCode.</summary>
  TTgChatBoostSourceGiftCode = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChatBoostSourceGiftCode; static;
  end;

  /// <summary>Создание ITgChatBoostSourceGiveaway.</summary>
  TTgChatBoostSourceGiveaway = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChatBoostSourceGiveaway; static;
  end;

  /// <summary>Создание ITgChatBoost.</summary>
  TTgChatBoost = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChatBoost; static;
  end;

  /// <summary>Создание ITgChatBoostUpdated.</summary>
  TTgChatBoostUpdated = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChatBoostUpdated; static;
  end;

  /// <summary>Создание ITgChatBoostRemoved.</summary>
  TTgChatBoostRemoved = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChatBoostRemoved; static;
  end;

  /// <summary>Создание ITgChatOwnerLeft.</summary>
  TTgChatOwnerLeft = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChatOwnerLeft; static;
  end;

  /// <summary>Создание ITgChatOwnerChanged.</summary>
  TTgChatOwnerChanged = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChatOwnerChanged; static;
  end;

  /// <summary>Создание ITgUserChatBoosts.</summary>
  TTgUserChatBoosts = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgUserChatBoosts; static;
  end;

  /// <summary>Создание ITgBusinessBotRights.</summary>
  TTgBusinessBotRights = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgBusinessBotRights; static;
  end;

  /// <summary>Создание ITgBusinessConnection.</summary>
  TTgBusinessConnection = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgBusinessConnection; static;
  end;

  /// <summary>Создание ITgBusinessMessagesDeleted.</summary>
  TTgBusinessMessagesDeleted = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgBusinessMessagesDeleted; static;
  end;

  /// <summary>Создание ITgSentWebAppMessage.</summary>
  TTgSentWebAppMessage = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgSentWebAppMessage; static;
  end;

  /// <summary>Создание ITgSentGuestMessage.</summary>
  TTgSentGuestMessage = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgSentGuestMessage; static;
  end;

  /// <summary>Создание ITgPreparedInlineMessage.</summary>
  TTgPreparedInlineMessage = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgPreparedInlineMessage; static;
  end;

  /// <summary>Создание ITgPreparedKeyboardButton.</summary>
  TTgPreparedKeyboardButton = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgPreparedKeyboardButton; static;
  end;

  /// <summary>Создание ITgResponseParameters.</summary>
  TTgResponseParameters = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgResponseParameters; static;
  end;

  /// <summary>Создание ITgInputMediaAnimation.</summary>
  TTgInputMediaAnimation = record
  public
    /// <summary>
    ///   Новый объект InputMediaAnimation с обязательными полями: media. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const AMedia: TTgInputFile): ITgInputMediaAnimation; static;
  end;

  /// <summary>Создание ITgInputMediaAudio.</summary>
  TTgInputMediaAudio = record
  public
    /// <summary>
    ///   Новый объект InputMediaAudio с обязательными полями: media. Необязательные поля задаются
    ///   методами With*.
    /// </summary>
    class function Create(const AMedia: TTgInputFile): ITgInputMediaAudio; static;
  end;

  /// <summary>Создание ITgInputMediaDocument.</summary>
  TTgInputMediaDocument = record
  public
    /// <summary>
    ///   Новый объект InputMediaDocument с обязательными полями: media. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const AMedia: TTgInputFile): ITgInputMediaDocument; static;
  end;

  /// <summary>Создание ITgInputMediaLink.</summary>
  TTgInputMediaLink = record
  public
    /// <summary>
    ///   Новый объект InputMediaLink с обязательными полями: url. Необязательные поля задаются
    ///   методами With*.
    /// </summary>
    class function Create(const AUrl: string): ITgInputMediaLink; static;
  end;

  /// <summary>Создание ITgInputMediaLivePhoto.</summary>
  TTgInputMediaLivePhoto = record
  public
    /// <summary>
    ///   Новый объект InputMediaLivePhoto с обязательными полями: media photo. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const AMedia: TTgInputFile;
      const APhoto: TTgInputFile): ITgInputMediaLivePhoto; static;
  end;

  /// <summary>Создание ITgInputMediaLocation.</summary>
  TTgInputMediaLocation = record
  public
    /// <summary>
    ///   Новый объект InputMediaLocation с обязательными полями: latitude longitude. Необязательные
    ///   поля задаются методами With*.
    /// </summary>
    class function Create(ALatitude: Double; ALongitude: Double): ITgInputMediaLocation; static;
  end;

  /// <summary>Создание ITgInputMediaPhoto.</summary>
  TTgInputMediaPhoto = record
  public
    /// <summary>
    ///   Новый объект InputMediaPhoto с обязательными полями: media. Необязательные поля задаются
    ///   методами With*.
    /// </summary>
    class function Create(const AMedia: TTgInputFile): ITgInputMediaPhoto; static;
  end;

  /// <summary>Создание ITgInputMediaSticker.</summary>
  TTgInputMediaSticker = record
  public
    /// <summary>
    ///   Новый объект InputMediaSticker с обязательными полями: media. Необязательные поля задаются
    ///   методами With*.
    /// </summary>
    class function Create(const AMedia: TTgInputFile): ITgInputMediaSticker; static;
  end;

  /// <summary>Создание ITgInputMediaVenue.</summary>
  TTgInputMediaVenue = record
  public
    /// <summary>
    ///   Новый объект InputMediaVenue с обязательными полями: latitude longitude title address.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(ALatitude: Double; ALongitude: Double; const ATitle: string;
      const AAddress: string): ITgInputMediaVenue; static;
  end;

  /// <summary>Создание ITgInputMediaVideo.</summary>
  TTgInputMediaVideo = record
  public
    /// <summary>
    ///   Новый объект InputMediaVideo с обязательными полями: media. Необязательные поля задаются
    ///   методами With*.
    /// </summary>
    class function Create(const AMedia: TTgInputFile): ITgInputMediaVideo; static;
  end;

  /// <summary>Создание ITgInputMediaVoiceNote.</summary>
  TTgInputMediaVoiceNote = record
  public
    /// <summary>
    ///   Новый объект InputMediaVoiceNote с обязательными полями: media. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const AMedia: TTgInputFile): ITgInputMediaVoiceNote; static;
  end;

  /// <summary>Создание ITgInputPaidMediaLivePhoto.</summary>
  TTgInputPaidMediaLivePhoto = record
  public
    /// <summary>
    ///   Новый объект InputPaidMediaLivePhoto с обязательными полями: media photo. Необязательные
    ///   поля задаются методами With*.
    /// </summary>
    class function Create(const AMedia: TTgInputFile;
      const APhoto: TTgInputFile): ITgInputPaidMediaLivePhoto; static;
  end;

  /// <summary>Создание ITgInputPaidMediaPhoto.</summary>
  TTgInputPaidMediaPhoto = record
  public
    /// <summary>
    ///   Новый объект InputPaidMediaPhoto с обязательными полями: media. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const AMedia: TTgInputFile): ITgInputPaidMediaPhoto; static;
  end;

  /// <summary>Создание ITgInputPaidMediaVideo.</summary>
  TTgInputPaidMediaVideo = record
  public
    /// <summary>
    ///   Новый объект InputPaidMediaVideo с обязательными полями: media. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const AMedia: TTgInputFile): ITgInputPaidMediaVideo; static;
  end;

  /// <summary>Создание ITgInputProfilePhotoStatic.</summary>
  TTgInputProfilePhotoStatic = record
  public
    /// <summary>
    ///   Новый объект InputProfilePhotoStatic с обязательными полями: photo. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const APhoto: TTgInputFile): ITgInputProfilePhotoStatic; static;
  end;

  /// <summary>Создание ITgInputProfilePhotoAnimated.</summary>
  TTgInputProfilePhotoAnimated = record
  public
    /// <summary>
    ///   Новый объект InputProfilePhotoAnimated с обязательными полями: animation. Необязательные
    ///   поля задаются методами With*.
    /// </summary>
    class function Create(const AAnimation: TTgInputFile): ITgInputProfilePhotoAnimated; static;
  end;

  /// <summary>Создание ITgInputStoryContentPhoto.</summary>
  TTgInputStoryContentPhoto = record
  public
    /// <summary>
    ///   Новый объект InputStoryContentPhoto с обязательными полями: photo. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const APhoto: TTgInputFile): ITgInputStoryContentPhoto; static;
  end;

  /// <summary>Создание ITgInputStoryContentVideo.</summary>
  TTgInputStoryContentVideo = record
  public
    /// <summary>
    ///   Новый объект InputStoryContentVideo с обязательными полями: video. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const AVideo: TTgInputFile): ITgInputStoryContentVideo; static;
  end;

  /// <summary>Создание ITgSticker.</summary>
  TTgSticker = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgSticker; static;
  end;

  /// <summary>Создание ITgStickerSet.</summary>
  TTgStickerSet = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgStickerSet; static;
  end;

  /// <summary>Создание ITgMaskPosition.</summary>
  TTgMaskPosition = record
  public
    /// <summary>
    ///   Новый объект MaskPosition с обязательными полями: point x_shift y_shift scale.
    ///   Необязательные поля задаются методами With*. Аргументы копируются в момент вызова:
    ///   последующие изменения переданных объектов на этот не влияют.
    /// </summary>
    class function Create(const APoint: string; AXShift: Double; AYShift: Double;
      AScale: Double): ITgMaskPosition; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgMaskPosition; static;
  end;

  /// <summary>Создание ITgInputSticker.</summary>
  TTgInputSticker = record
  public
    /// <summary>
    ///   Новый объект InputSticker с обязательными полями: sticker format emoji_list.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const ASticker: TTgInputFile; const AFormat: string;
      const AEmojiList: TArray<string>): ITgInputSticker; static;
  end;

  /// <summary>Создание ITgRichMessage.</summary>
  TTgRichMessage = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichMessage; static;
  end;

  /// <summary>Создание ITgInputRichMessage.</summary>
  TTgInputRichMessage = record
  public
    /// <summary>
    ///   Новый объект InputRichMessage. Необязательные поля задаются методами With*.
    /// </summary>
    class function Create: ITgInputRichMessage; static;
  end;

  /// <summary>Создание ITgInputRichMessageMedia.</summary>
  TTgInputRichMessageMedia = record
  public
    /// <summary>
    ///   Новый объект InputRichMessageMedia с обязательными полями: id media. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const AId: string;
      const AMedia: TTgInputRichMedia): ITgInputRichMessageMedia; static;
  end;

  /// <summary>Создание ITgRichMessageButton.</summary>
  TTgRichMessageButton = record
  public
    /// <summary>
    ///   Новый объект RichMessageButton с обязательными полями: text. Необязательные поля задаются
    ///   методами With*. Аргументы копируются в момент вызова: последующие изменения переданных
    ///   объектов на этот не влияют.
    /// </summary>
    class function Create(const AText: ITgRichText): ITgRichMessageButton; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichMessageButton; static;
  end;

  /// <summary>Создание ITgRichText.</summary>
  TTgRichText = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichText; static;
  end;

  /// <summary>Создание ITgRichTextPlain.</summary>
  TTgRichTextPlain = record
  public
    /// <summary>
    ///   Новый объект RichTextPlain. Необязательные поля задаются методами With*. Аргументы
    ///   копируются в момент вызова: последующие изменения переданных объектов на этот не влияют.
    /// </summary>
    class function Create(const AText: string): ITgRichTextPlain; static;
  end;

  /// <summary>Создание ITgRichTextList.</summary>
  TTgRichTextList = record
  public
    /// <summary>
    ///   Новый объект RichTextList. Необязательные поля задаются методами With*. Аргументы
    ///   копируются в момент вызова: последующие изменения переданных объектов на этот не влияют.
    /// </summary>
    class function Create(const AItems: array of ITgRichText): ITgRichTextList; static;
  end;

  /// <summary>Создание ITgRichTextBold.</summary>
  TTgRichTextBold = record
  public
    /// <summary>
    ///   Новый объект RichTextBold с обязательными полями: text. Необязательные поля задаются
    ///   методами With*. Аргументы копируются в момент вызова: последующие изменения переданных
    ///   объектов на этот не влияют.
    /// </summary>
    class function Create(const AText: ITgRichText): ITgRichTextBold; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichTextBold; static;
  end;

  /// <summary>Создание ITgRichTextItalic.</summary>
  TTgRichTextItalic = record
  public
    /// <summary>
    ///   Новый объект RichTextItalic с обязательными полями: text. Необязательные поля задаются
    ///   методами With*. Аргументы копируются в момент вызова: последующие изменения переданных
    ///   объектов на этот не влияют.
    /// </summary>
    class function Create(const AText: ITgRichText): ITgRichTextItalic; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichTextItalic; static;
  end;

  /// <summary>Создание ITgRichTextUnderline.</summary>
  TTgRichTextUnderline = record
  public
    /// <summary>
    ///   Новый объект RichTextUnderline с обязательными полями: text. Необязательные поля задаются
    ///   методами With*. Аргументы копируются в момент вызова: последующие изменения переданных
    ///   объектов на этот не влияют.
    /// </summary>
    class function Create(const AText: ITgRichText): ITgRichTextUnderline; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichTextUnderline; static;
  end;

  /// <summary>Создание ITgRichTextStrikethrough.</summary>
  TTgRichTextStrikethrough = record
  public
    /// <summary>
    ///   Новый объект RichTextStrikethrough с обязательными полями: text. Необязательные поля
    ///   задаются методами With*. Аргументы копируются в момент вызова: последующие изменения
    ///   переданных объектов на этот не влияют.
    /// </summary>
    class function Create(const AText: ITgRichText): ITgRichTextStrikethrough; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichTextStrikethrough; static;
  end;

  /// <summary>Создание ITgRichTextSpoiler.</summary>
  TTgRichTextSpoiler = record
  public
    /// <summary>
    ///   Новый объект RichTextSpoiler с обязательными полями: text. Необязательные поля задаются
    ///   методами With*. Аргументы копируются в момент вызова: последующие изменения переданных
    ///   объектов на этот не влияют.
    /// </summary>
    class function Create(const AText: ITgRichText): ITgRichTextSpoiler; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichTextSpoiler; static;
  end;

  /// <summary>Создание ITgRichTextDateTime.</summary>
  TTgRichTextDateTime = record
  public
    /// <summary>
    ///   Новый объект RichTextDateTime с обязательными полями: text unix_time date_time_format.
    ///   Необязательные поля задаются методами With*. Аргументы копируются в момент вызова:
    ///   последующие изменения переданных объектов на этот не влияют.
    /// </summary>
    class function Create(const AText: ITgRichText; AUnixTime: Integer;
      const ADateTimeFormat: string): ITgRichTextDateTime; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichTextDateTime; static;
  end;

  /// <summary>Создание ITgRichTextTextMention.</summary>
  TTgRichTextTextMention = record
  public
    /// <summary>
    ///   Новый объект RichTextTextMention с обязательными полями: text user. Необязательные поля
    ///   задаются методами With*. Аргументы копируются в момент вызова: последующие изменения
    ///   переданных объектов на этот не влияют.
    /// </summary>
    class function Create(const AText: ITgRichText; const AUser: ITgUser): ITgRichTextTextMention;
      static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichTextTextMention; static;
  end;

  /// <summary>Создание ITgRichTextSubscript.</summary>
  TTgRichTextSubscript = record
  public
    /// <summary>
    ///   Новый объект RichTextSubscript с обязательными полями: text. Необязательные поля задаются
    ///   методами With*. Аргументы копируются в момент вызова: последующие изменения переданных
    ///   объектов на этот не влияют.
    /// </summary>
    class function Create(const AText: ITgRichText): ITgRichTextSubscript; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichTextSubscript; static;
  end;

  /// <summary>Создание ITgRichTextSuperscript.</summary>
  TTgRichTextSuperscript = record
  public
    /// <summary>
    ///   Новый объект RichTextSuperscript с обязательными полями: text. Необязательные поля
    ///   задаются методами With*. Аргументы копируются в момент вызова: последующие изменения
    ///   переданных объектов на этот не влияют.
    /// </summary>
    class function Create(const AText: ITgRichText): ITgRichTextSuperscript; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichTextSuperscript; static;
  end;

  /// <summary>Создание ITgRichTextMarked.</summary>
  TTgRichTextMarked = record
  public
    /// <summary>
    ///   Новый объект RichTextMarked с обязательными полями: text. Необязательные поля задаются
    ///   методами With*. Аргументы копируются в момент вызова: последующие изменения переданных
    ///   объектов на этот не влияют.
    /// </summary>
    class function Create(const AText: ITgRichText): ITgRichTextMarked; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichTextMarked; static;
  end;

  /// <summary>Создание ITgRichTextCode.</summary>
  TTgRichTextCode = record
  public
    /// <summary>
    ///   Новый объект RichTextCode с обязательными полями: text. Необязательные поля задаются
    ///   методами With*. Аргументы копируются в момент вызова: последующие изменения переданных
    ///   объектов на этот не влияют.
    /// </summary>
    class function Create(const AText: ITgRichText): ITgRichTextCode; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichTextCode; static;
  end;

  /// <summary>Создание ITgRichTextCustomEmoji.</summary>
  TTgRichTextCustomEmoji = record
  public
    /// <summary>
    ///   Новый объект RichTextCustomEmoji с обязательными полями: custom_emoji_id alternative_text.
    ///   Необязательные поля задаются методами With*. Аргументы копируются в момент вызова:
    ///   последующие изменения переданных объектов на этот не влияют.
    /// </summary>
    class function Create(const ACustomEmojiId: string;
      const AAlternativeText: string): ITgRichTextCustomEmoji; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichTextCustomEmoji; static;
  end;

  /// <summary>Создание ITgRichTextMathematicalExpression.</summary>
  TTgRichTextMathematicalExpression = record
  public
    /// <summary>
    ///   Новый объект RichTextMathematicalExpression с обязательными полями: expression.
    ///   Необязательные поля задаются методами With*. Аргументы копируются в момент вызова:
    ///   последующие изменения переданных объектов на этот не влияют.
    /// </summary>
    class function Create(const AExpression: string): ITgRichTextMathematicalExpression; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichTextMathematicalExpression; static;
  end;

  /// <summary>Создание ITgRichTextUrl.</summary>
  TTgRichTextUrl = record
  public
    /// <summary>
    ///   Новый объект RichTextUrl с обязательными полями: text url. Необязательные поля задаются
    ///   методами With*. Аргументы копируются в момент вызова: последующие изменения переданных
    ///   объектов на этот не влияют.
    /// </summary>
    class function Create(const AText: ITgRichText; const AUrl: string): ITgRichTextUrl; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichTextUrl; static;
  end;

  /// <summary>Создание ITgRichTextEmailAddress.</summary>
  TTgRichTextEmailAddress = record
  public
    /// <summary>
    ///   Новый объект RichTextEmailAddress с обязательными полями: text email_address.
    ///   Необязательные поля задаются методами With*. Аргументы копируются в момент вызова:
    ///   последующие изменения переданных объектов на этот не влияют.
    /// </summary>
    class function Create(const AText: ITgRichText;
      const AEmailAddress: string): ITgRichTextEmailAddress; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichTextEmailAddress; static;
  end;

  /// <summary>Создание ITgRichTextPhoneNumber.</summary>
  TTgRichTextPhoneNumber = record
  public
    /// <summary>
    ///   Новый объект RichTextPhoneNumber с обязательными полями: text phone_number. Необязательные
    ///   поля задаются методами With*. Аргументы копируются в момент вызова: последующие изменения
    ///   переданных объектов на этот не влияют.
    /// </summary>
    class function Create(const AText: ITgRichText;
      const APhoneNumber: string): ITgRichTextPhoneNumber; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichTextPhoneNumber; static;
  end;

  /// <summary>Создание ITgRichTextBankCardNumber.</summary>
  TTgRichTextBankCardNumber = record
  public
    /// <summary>
    ///   Новый объект RichTextBankCardNumber с обязательными полями: text bank_card_number.
    ///   Необязательные поля задаются методами With*. Аргументы копируются в момент вызова:
    ///   последующие изменения переданных объектов на этот не влияют.
    /// </summary>
    class function Create(const AText: ITgRichText;
      const ABankCardNumber: string): ITgRichTextBankCardNumber; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichTextBankCardNumber; static;
  end;

  /// <summary>Создание ITgRichTextMention.</summary>
  TTgRichTextMention = record
  public
    /// <summary>
    ///   Новый объект RichTextMention с обязательными полями: text username. Необязательные поля
    ///   задаются методами With*. Аргументы копируются в момент вызова: последующие изменения
    ///   переданных объектов на этот не влияют.
    /// </summary>
    class function Create(const AText: ITgRichText; const AUsername: string): ITgRichTextMention;
      static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichTextMention; static;
  end;

  /// <summary>Создание ITgRichTextHashtag.</summary>
  TTgRichTextHashtag = record
  public
    /// <summary>
    ///   Новый объект RichTextHashtag с обязательными полями: text hashtag. Необязательные поля
    ///   задаются методами With*. Аргументы копируются в момент вызова: последующие изменения
    ///   переданных объектов на этот не влияют.
    /// </summary>
    class function Create(const AText: ITgRichText; const AHashtag: string): ITgRichTextHashtag;
      static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichTextHashtag; static;
  end;

  /// <summary>Создание ITgRichTextCashtag.</summary>
  TTgRichTextCashtag = record
  public
    /// <summary>
    ///   Новый объект RichTextCashtag с обязательными полями: text cashtag. Необязательные поля
    ///   задаются методами With*. Аргументы копируются в момент вызова: последующие изменения
    ///   переданных объектов на этот не влияют.
    /// </summary>
    class function Create(const AText: ITgRichText; const ACashtag: string): ITgRichTextCashtag;
      static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichTextCashtag; static;
  end;

  /// <summary>Создание ITgRichTextBotCommand.</summary>
  TTgRichTextBotCommand = record
  public
    /// <summary>
    ///   Новый объект RichTextBotCommand с обязательными полями: text bot_command. Необязательные
    ///   поля задаются методами With*. Аргументы копируются в момент вызова: последующие изменения
    ///   переданных объектов на этот не влияют.
    /// </summary>
    class function Create(const AText: ITgRichText;
      const ABotCommand: string): ITgRichTextBotCommand; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichTextBotCommand; static;
  end;

  /// <summary>Создание ITgRichTextButton.</summary>
  TTgRichTextButton = record
  public
    /// <summary>
    ///   Новый объект RichTextButton с обязательными полями: button. Необязательные поля задаются
    ///   методами With*. Аргументы копируются в момент вызова: последующие изменения переданных
    ///   объектов на этот не влияют.
    /// </summary>
    class function Create(const AButton: ITgRichMessageButton): ITgRichTextButton; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichTextButton; static;
  end;

  /// <summary>Создание ITgRichTextAnchor.</summary>
  TTgRichTextAnchor = record
  public
    /// <summary>
    ///   Новый объект RichTextAnchor с обязательными полями: name. Необязательные поля задаются
    ///   методами With*. Аргументы копируются в момент вызова: последующие изменения переданных
    ///   объектов на этот не влияют.
    /// </summary>
    class function Create(const AName: string): ITgRichTextAnchor; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichTextAnchor; static;
  end;

  /// <summary>Создание ITgRichTextAnchorLink.</summary>
  TTgRichTextAnchorLink = record
  public
    /// <summary>
    ///   Новый объект RichTextAnchorLink с обязательными полями: text anchor_name. Необязательные
    ///   поля задаются методами With*. Аргументы копируются в момент вызова: последующие изменения
    ///   переданных объектов на этот не влияют.
    /// </summary>
    class function Create(const AText: ITgRichText;
      const AAnchorName: string): ITgRichTextAnchorLink; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichTextAnchorLink; static;
  end;

  /// <summary>Создание ITgRichTextReference.</summary>
  TTgRichTextReference = record
  public
    /// <summary>
    ///   Новый объект RichTextReference с обязательными полями: text name. Необязательные поля
    ///   задаются методами With*. Аргументы копируются в момент вызова: последующие изменения
    ///   переданных объектов на этот не влияют.
    /// </summary>
    class function Create(const AText: ITgRichText; const AName: string): ITgRichTextReference;
      static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichTextReference; static;
  end;

  /// <summary>Создание ITgRichTextReferenceLink.</summary>
  TTgRichTextReferenceLink = record
  public
    /// <summary>
    ///   Новый объект RichTextReferenceLink с обязательными полями: text reference_name.
    ///   Необязательные поля задаются методами With*. Аргументы копируются в момент вызова:
    ///   последующие изменения переданных объектов на этот не влияют.
    /// </summary>
    class function Create(const AText: ITgRichText;
      const AReferenceName: string): ITgRichTextReferenceLink; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichTextReferenceLink; static;
  end;

  /// <summary>Создание ITgRichBlockCaption.</summary>
  TTgRichBlockCaption = record
  public
    /// <summary>
    ///   Новый объект RichBlockCaption с обязательными полями: text. Необязательные поля задаются
    ///   методами With*. Аргументы копируются в момент вызова: последующие изменения переданных
    ///   объектов на этот не влияют.
    /// </summary>
    class function Create(const AText: ITgRichText): ITgRichBlockCaption; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichBlockCaption; static;
  end;

  /// <summary>Создание ITgRichBlockTableCell.</summary>
  TTgRichBlockTableCell = record
  public
    /// <summary>
    ///   Новый объект RichBlockTableCell с обязательными полями: align valign. Необязательные поля
    ///   задаются методами With*. Аргументы копируются в момент вызова: последующие изменения
    ///   переданных объектов на этот не влияют.
    /// </summary>
    class function Create(const AAlign: string; const AValign: string): ITgRichBlockTableCell;
      static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichBlockTableCell; static;
  end;

  /// <summary>Создание ITgRichBlockListItem.</summary>
  TTgRichBlockListItem = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichBlockListItem; static;
  end;

  /// <summary>Создание ITgRichBlock.</summary>
  TTgRichBlock = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichBlock; static;
  end;

  /// <summary>Создание ITgRichBlockParagraph.</summary>
  TTgRichBlockParagraph = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichBlockParagraph; static;
  end;

  /// <summary>Создание ITgRichBlockSectionHeading.</summary>
  TTgRichBlockSectionHeading = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichBlockSectionHeading; static;
  end;

  /// <summary>Создание ITgRichBlockPreformatted.</summary>
  TTgRichBlockPreformatted = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichBlockPreformatted; static;
  end;

  /// <summary>Создание ITgRichBlockFooter.</summary>
  TTgRichBlockFooter = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichBlockFooter; static;
  end;

  /// <summary>Создание ITgRichBlockDivider.</summary>
  TTgRichBlockDivider = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichBlockDivider; static;
  end;

  /// <summary>Создание ITgRichBlockMathematicalExpression.</summary>
  TTgRichBlockMathematicalExpression = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichBlockMathematicalExpression; static;
  end;

  /// <summary>Создание ITgRichBlockAnchor.</summary>
  TTgRichBlockAnchor = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichBlockAnchor; static;
  end;

  /// <summary>Создание ITgRichBlockList.</summary>
  TTgRichBlockList = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichBlockList; static;
  end;

  /// <summary>Создание ITgRichBlockBlockQuotation.</summary>
  TTgRichBlockBlockQuotation = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichBlockBlockQuotation; static;
  end;

  /// <summary>Создание ITgRichBlockExpandableBlockQuotation.</summary>
  TTgRichBlockExpandableBlockQuotation = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichBlockExpandableBlockQuotation; static;
  end;

  /// <summary>Создание ITgRichBlockPullQuotation.</summary>
  TTgRichBlockPullQuotation = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichBlockPullQuotation; static;
  end;

  /// <summary>Создание ITgRichBlockCollage.</summary>
  TTgRichBlockCollage = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichBlockCollage; static;
  end;

  /// <summary>Создание ITgRichBlockSlideshow.</summary>
  TTgRichBlockSlideshow = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichBlockSlideshow; static;
  end;

  /// <summary>Создание ITgRichBlockTable.</summary>
  TTgRichBlockTable = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichBlockTable; static;
  end;

  /// <summary>Создание ITgRichBlockDetails.</summary>
  TTgRichBlockDetails = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichBlockDetails; static;
  end;

  /// <summary>Создание ITgRichBlockMap.</summary>
  TTgRichBlockMap = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichBlockMap; static;
  end;

  /// <summary>Создание ITgRichBlockButtons.</summary>
  TTgRichBlockButtons = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichBlockButtons; static;
  end;

  /// <summary>Создание ITgRichBlockAnimation.</summary>
  TTgRichBlockAnimation = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichBlockAnimation; static;
  end;

  /// <summary>Создание ITgRichBlockAudio.</summary>
  TTgRichBlockAudio = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichBlockAudio; static;
  end;

  /// <summary>Создание ITgRichBlockDocument.</summary>
  TTgRichBlockDocument = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichBlockDocument; static;
  end;

  /// <summary>Создание ITgRichBlockPhoto.</summary>
  TTgRichBlockPhoto = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichBlockPhoto; static;
  end;

  /// <summary>Создание ITgRichBlockVideo.</summary>
  TTgRichBlockVideo = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichBlockVideo; static;
  end;

  /// <summary>Создание ITgRichBlockVoiceNote.</summary>
  TTgRichBlockVoiceNote = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichBlockVoiceNote; static;
  end;

  /// <summary>Создание ITgRichBlockThinking.</summary>
  TTgRichBlockThinking = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRichBlockThinking; static;
  end;

  /// <summary>Создание ITgInputRichBlockListItem.</summary>
  TTgInputRichBlockListItem = record
  public
    /// <summary>
    ///   Новый объект InputRichBlockListItem с обязательными полями: blocks. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const ABlocks: array of TTgInputRichBlock): ITgInputRichBlockListItem;
      static;
  end;

  /// <summary>Создание ITgInputRichBlockParagraph.</summary>
  TTgInputRichBlockParagraph = record
  public
    /// <summary>
    ///   Новый объект InputRichBlockParagraph с обязательными полями: text. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const AText: ITgRichText): ITgInputRichBlockParagraph; static;
  end;

  /// <summary>Создание ITgInputRichBlockSectionHeading.</summary>
  TTgInputRichBlockSectionHeading = record
  public
    /// <summary>
    ///   Новый объект InputRichBlockSectionHeading с обязательными полями: text size.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const AText: ITgRichText;
      ASize: Integer): ITgInputRichBlockSectionHeading; static;
  end;

  /// <summary>Создание ITgInputRichBlockPreformatted.</summary>
  TTgInputRichBlockPreformatted = record
  public
    /// <summary>
    ///   Новый объект InputRichBlockPreformatted с обязательными полями: text. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const AText: ITgRichText): ITgInputRichBlockPreformatted; static;
  end;

  /// <summary>Создание ITgInputRichBlockFooter.</summary>
  TTgInputRichBlockFooter = record
  public
    /// <summary>
    ///   Новый объект InputRichBlockFooter с обязательными полями: text. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const AText: ITgRichText): ITgInputRichBlockFooter; static;
  end;

  /// <summary>Создание ITgInputRichBlockDivider.</summary>
  TTgInputRichBlockDivider = record
  public
    /// <summary>
    ///   Новый объект InputRichBlockDivider. Необязательные поля задаются методами With*.
    /// </summary>
    class function Create: ITgInputRichBlockDivider; static;
  end;

  /// <summary>Создание ITgInputRichBlockMathematicalExpression.</summary>
  TTgInputRichBlockMathematicalExpression = record
  public
    /// <summary>
    ///   Новый объект InputRichBlockMathematicalExpression с обязательными полями: expression.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const AExpression: string): ITgInputRichBlockMathematicalExpression;
      static;
  end;

  /// <summary>Создание ITgInputRichBlockAnchor.</summary>
  TTgInputRichBlockAnchor = record
  public
    /// <summary>
    ///   Новый объект InputRichBlockAnchor с обязательными полями: name. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const AName: string): ITgInputRichBlockAnchor; static;
  end;

  /// <summary>Создание ITgInputRichBlockList.</summary>
  TTgInputRichBlockList = record
  public
    /// <summary>
    ///   Новый объект InputRichBlockList с обязательными полями: items. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const AItems: array of ITgInputRichBlockListItem): ITgInputRichBlockList;
      static;
  end;

  /// <summary>Создание ITgInputRichBlockBlockQuotation.</summary>
  TTgInputRichBlockBlockQuotation = record
  public
    /// <summary>
    ///   Новый объект InputRichBlockBlockQuotation с обязательными полями: blocks. Необязательные
    ///   поля задаются методами With*.
    /// </summary>
    class function Create(const ABlocks: array of TTgInputRichBlock): ITgInputRichBlockBlockQuotation; static;
  end;

  /// <summary>Создание ITgInputRichBlockExpandableBlockQuotation.</summary>
  TTgInputRichBlockExpandableBlockQuotation = record
  public
    /// <summary>
    ///   Новый объект InputRichBlockExpandableBlockQuotation с обязательными полями: text.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const AText: ITgRichText): ITgInputRichBlockExpandableBlockQuotation;
      static;
  end;

  /// <summary>Создание ITgInputRichBlockPullQuotation.</summary>
  TTgInputRichBlockPullQuotation = record
  public
    /// <summary>
    ///   Новый объект InputRichBlockPullQuotation с обязательными полями: text. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const AText: ITgRichText): ITgInputRichBlockPullQuotation; static;
  end;

  /// <summary>Создание ITgInputRichBlockCollage.</summary>
  TTgInputRichBlockCollage = record
  public
    /// <summary>
    ///   Новый объект InputRichBlockCollage с обязательными полями: blocks. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const ABlocks: array of TTgInputRichBlock): ITgInputRichBlockCollage;
      static;
  end;

  /// <summary>Создание ITgInputRichBlockSlideshow.</summary>
  TTgInputRichBlockSlideshow = record
  public
    /// <summary>
    ///   Новый объект InputRichBlockSlideshow с обязательными полями: blocks. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const ABlocks: array of TTgInputRichBlock): ITgInputRichBlockSlideshow;
      static;
  end;

  /// <summary>Создание ITgInputRichBlockTable.</summary>
  TTgInputRichBlockTable = record
  public
    /// <summary>
    ///   Новый объект InputRichBlockTable с обязательными полями: cells. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const ACells: array of TArray<ITgRichBlockTableCell>): ITgInputRichBlockTable; static;
  end;

  /// <summary>Создание ITgInputRichBlockDetails.</summary>
  TTgInputRichBlockDetails = record
  public
    /// <summary>
    ///   Новый объект InputRichBlockDetails с обязательными полями: summary blocks. Необязательные
    ///   поля задаются методами With*.
    /// </summary>
    class function Create(const ASummary: ITgRichText;
      const ABlocks: array of TTgInputRichBlock): ITgInputRichBlockDetails; static;
  end;

  /// <summary>Создание ITgInputRichBlockMap.</summary>
  TTgInputRichBlockMap = record
  public
    /// <summary>
    ///   Новый объект InputRichBlockMap с обязательными полями: location. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const ALocation: ITgLocation): ITgInputRichBlockMap; static;
  end;

  /// <summary>Создание ITgInputRichBlockButtons.</summary>
  TTgInputRichBlockButtons = record
  public
    /// <summary>
    ///   Новый объект InputRichBlockButtons с обязательными полями: buttons. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const AButtons: array of ITgRichMessageButton): ITgInputRichBlockButtons;
      static;
  end;

  /// <summary>Создание ITgInputRichBlockAnimation.</summary>
  TTgInputRichBlockAnimation = record
  public
    /// <summary>
    ///   Новый объект InputRichBlockAnimation с обязательными полями: animation. Необязательные
    ///   поля задаются методами With*.
    /// </summary>
    class function Create(const AAnimation: ITgInputMediaAnimation): ITgInputRichBlockAnimation;
      static;
  end;

  /// <summary>Создание ITgInputRichBlockAudio.</summary>
  TTgInputRichBlockAudio = record
  public
    /// <summary>
    ///   Новый объект InputRichBlockAudio с обязательными полями: audio. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const AAudio: ITgInputMediaAudio): ITgInputRichBlockAudio; static;
  end;

  /// <summary>Создание ITgInputRichBlockDocument.</summary>
  TTgInputRichBlockDocument = record
  public
    /// <summary>
    ///   Новый объект InputRichBlockDocument с обязательными полями: document. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const ADocument: ITgInputMediaDocument): ITgInputRichBlockDocument;
      static;
  end;

  /// <summary>Создание ITgInputRichBlockPhoto.</summary>
  TTgInputRichBlockPhoto = record
  public
    /// <summary>
    ///   Новый объект InputRichBlockPhoto с обязательными полями: photo. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const APhoto: ITgInputMediaPhoto): ITgInputRichBlockPhoto; static;
  end;

  /// <summary>Создание ITgInputRichBlockVideo.</summary>
  TTgInputRichBlockVideo = record
  public
    /// <summary>
    ///   Новый объект InputRichBlockVideo с обязательными полями: video. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const AVideo: ITgInputMediaVideo): ITgInputRichBlockVideo; static;
  end;

  /// <summary>Создание ITgInputRichBlockVoiceNote.</summary>
  TTgInputRichBlockVoiceNote = record
  public
    /// <summary>
    ///   Новый объект InputRichBlockVoiceNote с обязательными полями: voice_note. Необязательные
    ///   поля задаются методами With*.
    /// </summary>
    class function Create(const AVoiceNote: ITgInputMediaVoiceNote): ITgInputRichBlockVoiceNote;
      static;
  end;

  /// <summary>Создание ITgInputRichBlockThinking.</summary>
  TTgInputRichBlockThinking = record
  public
    /// <summary>
    ///   Новый объект InputRichBlockThinking с обязательными полями: text. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const AText: ITgRichText): ITgInputRichBlockThinking; static;
  end;

  /// <summary>Создание ITgInlineQuery.</summary>
  TTgInlineQuery = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgInlineQuery; static;
  end;

  /// <summary>Создание ITgInlineQueryResultsButton.</summary>
  TTgInlineQueryResultsButton = record
  public
    /// <summary>
    ///   Новый объект InlineQueryResultsButton с обязательными полями: text. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const AText: string): ITgInlineQueryResultsButton; static;
  end;

  /// <summary>Создание ITgInlineQueryResultArticle.</summary>
  TTgInlineQueryResultArticle = record
  public
    /// <summary>
    ///   Новый объект InlineQueryResultArticle с обязательными полями: id title
    ///   input_message_content. Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const AId: string; const ATitle: string;
      const AInputMessageContent: TTgInputMessageContent): ITgInlineQueryResultArticle; static;
  end;

  /// <summary>Создание ITgInlineQueryResultPhoto.</summary>
  TTgInlineQueryResultPhoto = record
  public
    /// <summary>
    ///   Новый объект InlineQueryResultPhoto с обязательными полями: id photo_url thumbnail_url.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const AId: string; const APhotoUrl: string;
      const AThumbnailUrl: string): ITgInlineQueryResultPhoto; static;
  end;

  /// <summary>Создание ITgInlineQueryResultGif.</summary>
  TTgInlineQueryResultGif = record
  public
    /// <summary>
    ///   Новый объект InlineQueryResultGif с обязательными полями: id gif_url thumbnail_url.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const AId: string; const AGifUrl: string;
      const AThumbnailUrl: string): ITgInlineQueryResultGif; static;
  end;

  /// <summary>Создание ITgInlineQueryResultMpeg4Gif.</summary>
  TTgInlineQueryResultMpeg4Gif = record
  public
    /// <summary>
    ///   Новый объект InlineQueryResultMpeg4Gif с обязательными полями: id mpeg4_url thumbnail_url.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const AId: string; const AMpeg4Url: string;
      const AThumbnailUrl: string): ITgInlineQueryResultMpeg4Gif; static;
  end;

  /// <summary>Создание ITgInlineQueryResultVideo.</summary>
  TTgInlineQueryResultVideo = record
  public
    /// <summary>
    ///   Новый объект InlineQueryResultVideo с обязательными полями: id video_url mime_type
    ///   thumbnail_url title. Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const AId: string; const AVideoUrl: string; const AMimeType: string;
      const AThumbnailUrl: string; const ATitle: string): ITgInlineQueryResultVideo; static;
  end;

  /// <summary>Создание ITgInlineQueryResultAudio.</summary>
  TTgInlineQueryResultAudio = record
  public
    /// <summary>
    ///   Новый объект InlineQueryResultAudio с обязательными полями: id audio_url title.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const AId: string; const AAudioUrl: string;
      const ATitle: string): ITgInlineQueryResultAudio; static;
  end;

  /// <summary>Создание ITgInlineQueryResultVoice.</summary>
  TTgInlineQueryResultVoice = record
  public
    /// <summary>
    ///   Новый объект InlineQueryResultVoice с обязательными полями: id voice_url title.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const AId: string; const AVoiceUrl: string;
      const ATitle: string): ITgInlineQueryResultVoice; static;
  end;

  /// <summary>Создание ITgInlineQueryResultDocument.</summary>
  TTgInlineQueryResultDocument = record
  public
    /// <summary>
    ///   Новый объект InlineQueryResultDocument с обязательными полями: id title document_url
    ///   mime_type. Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const AId: string; const ATitle: string; const ADocumentUrl: string;
      const AMimeType: string): ITgInlineQueryResultDocument; static;
  end;

  /// <summary>Создание ITgInlineQueryResultLocation.</summary>
  TTgInlineQueryResultLocation = record
  public
    /// <summary>
    ///   Новый объект InlineQueryResultLocation с обязательными полями: id latitude longitude
    ///   title. Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const AId: string; ALatitude: Double; ALongitude: Double;
      const ATitle: string): ITgInlineQueryResultLocation; static;
  end;

  /// <summary>Создание ITgInlineQueryResultVenue.</summary>
  TTgInlineQueryResultVenue = record
  public
    /// <summary>
    ///   Новый объект InlineQueryResultVenue с обязательными полями: id latitude longitude title
    ///   address. Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const AId: string; ALatitude: Double; ALongitude: Double;
      const ATitle: string; const AAddress: string): ITgInlineQueryResultVenue; static;
  end;

  /// <summary>Создание ITgInlineQueryResultContact.</summary>
  TTgInlineQueryResultContact = record
  public
    /// <summary>
    ///   Новый объект InlineQueryResultContact с обязательными полями: id phone_number first_name.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const AId: string; const APhoneNumber: string;
      const AFirstName: string): ITgInlineQueryResultContact; static;
  end;

  /// <summary>Создание ITgInlineQueryResultGame.</summary>
  TTgInlineQueryResultGame = record
  public
    /// <summary>
    ///   Новый объект InlineQueryResultGame с обязательными полями: id game_short_name.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const AId: string;
      const AGameShortName: string): ITgInlineQueryResultGame; static;
  end;

  /// <summary>Создание ITgInlineQueryResultCachedPhoto.</summary>
  TTgInlineQueryResultCachedPhoto = record
  public
    /// <summary>
    ///   Новый объект InlineQueryResultCachedPhoto с обязательными полями: id photo_file_id.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const AId: string;
      const APhotoFileId: string): ITgInlineQueryResultCachedPhoto; static;
  end;

  /// <summary>Создание ITgInlineQueryResultCachedGif.</summary>
  TTgInlineQueryResultCachedGif = record
  public
    /// <summary>
    ///   Новый объект InlineQueryResultCachedGif с обязательными полями: id gif_file_id.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const AId: string;
      const AGifFileId: string): ITgInlineQueryResultCachedGif; static;
  end;

  /// <summary>Создание ITgInlineQueryResultCachedMpeg4Gif.</summary>
  TTgInlineQueryResultCachedMpeg4Gif = record
  public
    /// <summary>
    ///   Новый объект InlineQueryResultCachedMpeg4Gif с обязательными полями: id mpeg4_file_id.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const AId: string;
      const AMpeg4FileId: string): ITgInlineQueryResultCachedMpeg4Gif; static;
  end;

  /// <summary>Создание ITgInlineQueryResultCachedSticker.</summary>
  TTgInlineQueryResultCachedSticker = record
  public
    /// <summary>
    ///   Новый объект InlineQueryResultCachedSticker с обязательными полями: id sticker_file_id.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const AId: string;
      const AStickerFileId: string): ITgInlineQueryResultCachedSticker; static;
  end;

  /// <summary>Создание ITgInlineQueryResultCachedDocument.</summary>
  TTgInlineQueryResultCachedDocument = record
  public
    /// <summary>
    ///   Новый объект InlineQueryResultCachedDocument с обязательными полями: id title
    ///   document_file_id. Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const AId: string; const ATitle: string;
      const ADocumentFileId: string): ITgInlineQueryResultCachedDocument; static;
  end;

  /// <summary>Создание ITgInlineQueryResultCachedVideo.</summary>
  TTgInlineQueryResultCachedVideo = record
  public
    /// <summary>
    ///   Новый объект InlineQueryResultCachedVideo с обязательными полями: id video_file_id title.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const AId: string; const AVideoFileId: string;
      const ATitle: string): ITgInlineQueryResultCachedVideo; static;
  end;

  /// <summary>Создание ITgInlineQueryResultCachedVoice.</summary>
  TTgInlineQueryResultCachedVoice = record
  public
    /// <summary>
    ///   Новый объект InlineQueryResultCachedVoice с обязательными полями: id voice_file_id title.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const AId: string; const AVoiceFileId: string;
      const ATitle: string): ITgInlineQueryResultCachedVoice; static;
  end;

  /// <summary>Создание ITgInlineQueryResultCachedAudio.</summary>
  TTgInlineQueryResultCachedAudio = record
  public
    /// <summary>
    ///   Новый объект InlineQueryResultCachedAudio с обязательными полями: id audio_file_id.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const AId: string;
      const AAudioFileId: string): ITgInlineQueryResultCachedAudio; static;
  end;

  /// <summary>Создание ITgInputTextMessageContent.</summary>
  TTgInputTextMessageContent = record
  public
    /// <summary>
    ///   Новый объект InputTextMessageContent с обязательными полями: message_text. Необязательные
    ///   поля задаются методами With*.
    /// </summary>
    class function Create(const AMessageText: string): ITgInputTextMessageContent; static;
  end;

  /// <summary>Создание ITgInputRichMessageContent.</summary>
  TTgInputRichMessageContent = record
  public
    /// <summary>
    ///   Новый объект InputRichMessageContent с обязательными полями: rich_message. Необязательные
    ///   поля задаются методами With*.
    /// </summary>
    class function Create(const ARichMessage: ITgInputRichMessage): ITgInputRichMessageContent;
      static;
  end;

  /// <summary>Создание ITgInputLocationMessageContent.</summary>
  TTgInputLocationMessageContent = record
  public
    /// <summary>
    ///   Новый объект InputLocationMessageContent с обязательными полями: latitude longitude.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(ALatitude: Double; ALongitude: Double): ITgInputLocationMessageContent;
      static;
  end;

  /// <summary>Создание ITgInputVenueMessageContent.</summary>
  TTgInputVenueMessageContent = record
  public
    /// <summary>
    ///   Новый объект InputVenueMessageContent с обязательными полями: latitude longitude title
    ///   address. Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(ALatitude: Double; ALongitude: Double; const ATitle: string;
      const AAddress: string): ITgInputVenueMessageContent; static;
  end;

  /// <summary>Создание ITgInputContactMessageContent.</summary>
  TTgInputContactMessageContent = record
  public
    /// <summary>
    ///   Новый объект InputContactMessageContent с обязательными полями: phone_number first_name.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const APhoneNumber: string;
      const AFirstName: string): ITgInputContactMessageContent; static;
  end;

  /// <summary>Создание ITgInputInvoiceMessageContent.</summary>
  TTgInputInvoiceMessageContent = record
  public
    /// <summary>
    ///   Новый объект InputInvoiceMessageContent с обязательными полями: title description payload
    ///   currency prices. Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const ATitle: string; const ADescription: string; const APayload: string;
      const ACurrency: string;
      const APrices: array of ITgLabeledPrice): ITgInputInvoiceMessageContent; static;
  end;

  /// <summary>Создание ITgChosenInlineResult.</summary>
  TTgChosenInlineResult = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgChosenInlineResult; static;
  end;

  /// <summary>Создание ITgLabeledPrice.</summary>
  TTgLabeledPrice = record
  public
    /// <summary>
    ///   Новый объект LabeledPrice с обязательными полями: label amount. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const ALabeledPriceLabel: string; AAmount: Integer): ITgLabeledPrice;
      static;
  end;

  /// <summary>Создание ITgInvoice.</summary>
  TTgInvoice = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgInvoice; static;
  end;

  /// <summary>Создание ITgShippingAddress.</summary>
  TTgShippingAddress = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgShippingAddress; static;
  end;

  /// <summary>Создание ITgOrderInfo.</summary>
  TTgOrderInfo = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgOrderInfo; static;
  end;

  /// <summary>Создание ITgShippingOption.</summary>
  TTgShippingOption = record
  public
    /// <summary>
    ///   Новый объект ShippingOption с обязательными полями: id title prices. Необязательные поля
    ///   задаются методами With*.
    /// </summary>
    class function Create(const AId: string; const ATitle: string;
      const APrices: array of ITgLabeledPrice): ITgShippingOption; static;
  end;

  /// <summary>Создание ITgSuccessfulPayment.</summary>
  TTgSuccessfulPayment = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgSuccessfulPayment; static;
  end;

  /// <summary>Создание ITgRefundedPayment.</summary>
  TTgRefundedPayment = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRefundedPayment; static;
  end;

  /// <summary>Создание ITgShippingQuery.</summary>
  TTgShippingQuery = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgShippingQuery; static;
  end;

  /// <summary>Создание ITgPreCheckoutQuery.</summary>
  TTgPreCheckoutQuery = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgPreCheckoutQuery; static;
  end;

  /// <summary>Создание ITgPaidMediaPurchased.</summary>
  TTgPaidMediaPurchased = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgPaidMediaPurchased; static;
  end;

  /// <summary>Создание ITgRevenueWithdrawalState.</summary>
  TTgRevenueWithdrawalState = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRevenueWithdrawalState; static;
  end;

  /// <summary>Создание ITgRevenueWithdrawalStatePending.</summary>
  TTgRevenueWithdrawalStatePending = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRevenueWithdrawalStatePending; static;
  end;

  /// <summary>Создание ITgRevenueWithdrawalStateSucceeded.</summary>
  TTgRevenueWithdrawalStateSucceeded = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRevenueWithdrawalStateSucceeded; static;
  end;

  /// <summary>Создание ITgRevenueWithdrawalStateFailed.</summary>
  TTgRevenueWithdrawalStateFailed = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgRevenueWithdrawalStateFailed; static;
  end;

  /// <summary>Создание ITgAffiliateInfo.</summary>
  TTgAffiliateInfo = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgAffiliateInfo; static;
  end;

  /// <summary>Создание ITgTransactionPartner.</summary>
  TTgTransactionPartner = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgTransactionPartner; static;
  end;

  /// <summary>Создание ITgTransactionPartnerUser.</summary>
  TTgTransactionPartnerUser = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgTransactionPartnerUser; static;
  end;

  /// <summary>Создание ITgTransactionPartnerChat.</summary>
  TTgTransactionPartnerChat = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgTransactionPartnerChat; static;
  end;

  /// <summary>Создание ITgTransactionPartnerAffiliateProgram.</summary>
  TTgTransactionPartnerAffiliateProgram = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgTransactionPartnerAffiliateProgram; static;
  end;

  /// <summary>Создание ITgTransactionPartnerFragment.</summary>
  TTgTransactionPartnerFragment = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgTransactionPartnerFragment; static;
  end;

  /// <summary>Создание ITgTransactionPartnerTelegramAds.</summary>
  TTgTransactionPartnerTelegramAds = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgTransactionPartnerTelegramAds; static;
  end;

  /// <summary>Создание ITgTransactionPartnerTelegramApi.</summary>
  TTgTransactionPartnerTelegramApi = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgTransactionPartnerTelegramApi; static;
  end;

  /// <summary>Создание ITgTransactionPartnerOther.</summary>
  TTgTransactionPartnerOther = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgTransactionPartnerOther; static;
  end;

  /// <summary>Создание ITgStarTransaction.</summary>
  TTgStarTransaction = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgStarTransaction; static;
  end;

  /// <summary>Создание ITgStarTransactions.</summary>
  TTgStarTransactions = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgStarTransactions; static;
  end;

  /// <summary>Создание ITgPassportData.</summary>
  TTgPassportData = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgPassportData; static;
  end;

  /// <summary>Создание ITgPassportFile.</summary>
  TTgPassportFile = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgPassportFile; static;
  end;

  /// <summary>Создание ITgEncryptedPassportElement.</summary>
  TTgEncryptedPassportElement = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgEncryptedPassportElement; static;
  end;

  /// <summary>Создание ITgEncryptedCredentials.</summary>
  TTgEncryptedCredentials = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgEncryptedCredentials; static;
  end;

  /// <summary>Создание ITgPassportElementErrorDataField.</summary>
  TTgPassportElementErrorDataField = record
  public
    /// <summary>
    ///   Новый объект PassportElementErrorDataField с обязательными полями: type field_name
    ///   data_hash message. Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const APassportElementErrorDataFieldType: string;
      const AFieldName: string; const ADataHash: string;
      const AMessage: string): ITgPassportElementErrorDataField; static;
  end;

  /// <summary>Создание ITgPassportElementErrorFrontSide.</summary>
  TTgPassportElementErrorFrontSide = record
  public
    /// <summary>
    ///   Новый объект PassportElementErrorFrontSide с обязательными полями: type file_hash message.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const APassportElementErrorFrontSideType: string; const AFileHash: string;
      const AMessage: string): ITgPassportElementErrorFrontSide; static;
  end;

  /// <summary>Создание ITgPassportElementErrorReverseSide.</summary>
  TTgPassportElementErrorReverseSide = record
  public
    /// <summary>
    ///   Новый объект PassportElementErrorReverseSide с обязательными полями: type file_hash
    ///   message. Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const APassportElementErrorReverseSideType: string;
      const AFileHash: string; const AMessage: string): ITgPassportElementErrorReverseSide; static;
  end;

  /// <summary>Создание ITgPassportElementErrorSelfie.</summary>
  TTgPassportElementErrorSelfie = record
  public
    /// <summary>
    ///   Новый объект PassportElementErrorSelfie с обязательными полями: type file_hash message.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const APassportElementErrorSelfieType: string; const AFileHash: string;
      const AMessage: string): ITgPassportElementErrorSelfie; static;
  end;

  /// <summary>Создание ITgPassportElementErrorFile.</summary>
  TTgPassportElementErrorFile = record
  public
    /// <summary>
    ///   Новый объект PassportElementErrorFile с обязательными полями: type file_hash message.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const APassportElementErrorFileType: string; const AFileHash: string;
      const AMessage: string): ITgPassportElementErrorFile; static;
  end;

  /// <summary>Создание ITgPassportElementErrorFiles.</summary>
  TTgPassportElementErrorFiles = record
  public
    /// <summary>
    ///   Новый объект PassportElementErrorFiles с обязательными полями: type file_hashes message.
    ///   Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const APassportElementErrorFilesType: string;
      const AFileHashes: TArray<string>;
      const AMessage: string): ITgPassportElementErrorFiles; static;
  end;

  /// <summary>Создание ITgPassportElementErrorTranslationFile.</summary>
  TTgPassportElementErrorTranslationFile = record
  public
    /// <summary>
    ///   Новый объект PassportElementErrorTranslationFile с обязательными полями: type file_hash
    ///   message. Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const APassportElementErrorTranslationFileType: string;
      const AFileHash: string;
      const AMessage: string): ITgPassportElementErrorTranslationFile; static;
  end;

  /// <summary>Создание ITgPassportElementErrorTranslationFiles.</summary>
  TTgPassportElementErrorTranslationFiles = record
  public
    /// <summary>
    ///   Новый объект PassportElementErrorTranslationFiles с обязательными полями: type file_hashes
    ///   message. Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const APassportElementErrorTranslationFilesType: string;
      const AFileHashes: TArray<string>;
      const AMessage: string): ITgPassportElementErrorTranslationFiles; static;
  end;

  /// <summary>Создание ITgPassportElementErrorUnspecified.</summary>
  TTgPassportElementErrorUnspecified = record
  public
    /// <summary>
    ///   Новый объект PassportElementErrorUnspecified с обязательными полями: type element_hash
    ///   message. Необязательные поля задаются методами With*.
    /// </summary>
    class function Create(const APassportElementErrorUnspecifiedType: string;
      const AElementHash: string;
      const AMessage: string): ITgPassportElementErrorUnspecified; static;
  end;

  /// <summary>Создание ITgGame.</summary>
  TTgGame = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgGame; static;
  end;

  /// <summary>Создание ITgCallbackGame.</summary>
  TTgCallbackGame = record
  public
    /// <summary>
    ///   Новый объект CallbackGame. Необязательные поля задаются методами With*. Аргументы
    ///   копируются в момент вызова: последующие изменения переданных объектов на этот не влияют.
    /// </summary>
    class function Create: ITgCallbackGame; static;
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgCallbackGame; static;
  end;

  /// <summary>Создание ITgGameHighScore.</summary>
  TTgGameHighScore = record
  public
    /// <summary>Разбор JSON-текста (например, тела webhook); ошибка — nil.</summary>
    class function FromJson(const AJsonText: string): ITgGameHighScore; static;
  end;

