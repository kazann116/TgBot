// Gen.ImplClasses.inc — скрытые классы реализации (implementation).
// Сгенерировано TgBotGen по Telegram Bot API 10.3 (August 24, 2026). Не редактируйте вручную.

type
  TTgUpdateImpl = class(TTgJsonDto, ITgUpdate)
  public
    function GetUpdateId: Int64;
    function GetMessage: ITgMessage;
    function GetEditedMessage: ITgMessage;
    function GetChannelPost: ITgMessage;
    function GetEditedChannelPost: ITgMessage;
    function GetBusinessConnection: ITgBusinessConnection;
    function GetBusinessMessage: ITgMessage;
    function GetEditedBusinessMessage: ITgMessage;
    function GetDeletedBusinessMessages: ITgBusinessMessagesDeleted;
    function GetGuestMessage: ITgMessage;
    function GetMessageReaction: ITgMessageReactionUpdated;
    function GetMessageReactionCount: ITgMessageReactionCountUpdated;
    function GetInlineQuery: ITgInlineQuery;
    function GetChosenInlineResult: ITgChosenInlineResult;
    function GetCallbackQuery: ITgCallbackQuery;
    function GetShippingQuery: ITgShippingQuery;
    function GetPreCheckoutQuery: ITgPreCheckoutQuery;
    function GetPurchasedPaidMedia: ITgPaidMediaPurchased;
    function GetPoll: ITgPoll;
    function GetPollAnswer: ITgPollAnswer;
    function GetMyChatMember: ITgChatMemberUpdated;
    function GetChatMember: ITgChatMemberUpdated;
    function GetChatJoinRequest: ITgChatJoinRequest;
    function GetChatBoost: ITgChatBoostUpdated;
    function GetRemovedChatBoost: ITgChatBoostRemoved;
    function GetManagedBot: ITgManagedBotUpdated;
    function GetSubscription: ITgBotSubscriptionUpdated;
    function GetStoppedMessageGeneration: ITgMessageGenerationStopped;
  end;

  TTgWebhookInfoImpl = class(TTgJsonDto, ITgWebhookInfo)
  public
    function GetUrl: string;
    function GetHasCustomCertificate: Boolean;
    function GetPendingUpdateCount: Integer;
    function GetIpAddress: string;
    function GetLastErrorDate: Int64;
    function GetHasLastErrorDate: Boolean;
    function GetLastErrorMessage: string;
    function GetLastSynchronizationErrorDate: Int64;
    function GetHasLastSynchronizationErrorDate: Boolean;
    function GetMaxConnections: Integer;
    function GetHasMaxConnections: Boolean;
    function GetAllowedUpdates: TArray<string>;
  end;

  TTgUserImpl = class(TTgJsonDto, ITgUser)
  public
    function GetId: Int64;
    function GetIsBot: Boolean;
    function GetFirstName: string;
    function GetLastName: string;
    function GetUsername: string;
    function GetLanguageCode: string;
    function GetIsPremium: Boolean;
    function GetAddedToAttachmentMenu: Boolean;
    function GetCanJoinGroups: Boolean;
    function GetHasCanJoinGroups: Boolean;
    function GetCanReadAllGroupMessages: Boolean;
    function GetHasCanReadAllGroupMessages: Boolean;
    function GetSupportsGuestQueries: Boolean;
    function GetHasSupportsGuestQueries: Boolean;
    function GetSupportsInlineQueries: Boolean;
    function GetHasSupportsInlineQueries: Boolean;
    function GetCanConnectToBusiness: Boolean;
    function GetHasCanConnectToBusiness: Boolean;
    function GetHasMainWebApp: Boolean;
    function GetHasTopicsEnabled: Boolean;
    function GetAllowsUsersToCreateTopics: Boolean;
    function GetHasAllowsUsersToCreateTopics: Boolean;
    function GetCanManageBots: Boolean;
    function GetHasCanManageBots: Boolean;
    function GetSupportsJoinRequestQueries: Boolean;
    function GetHasSupportsJoinRequestQueries: Boolean;
    function WithId(AValue: Int64): ITgUser;
    function WithIsBot(AValue: Boolean): ITgUser;
    function WithFirstName(const AValue: string): ITgUser;
    function WithLastName(const AValue: string): ITgUser;
    function WithUsername(const AValue: string): ITgUser;
    function WithLanguageCode(const AValue: string): ITgUser;
    function WithIsPremium(AValue: Boolean): ITgUser;
    function WithAddedToAttachmentMenu(AValue: Boolean): ITgUser;
    function WithCanJoinGroups(AValue: Boolean): ITgUser;
    function WithCanReadAllGroupMessages(AValue: Boolean): ITgUser;
    function WithSupportsGuestQueries(AValue: Boolean): ITgUser;
    function WithSupportsInlineQueries(AValue: Boolean): ITgUser;
    function WithCanConnectToBusiness(AValue: Boolean): ITgUser;
    function WithHasMainWebApp(AValue: Boolean): ITgUser;
    function WithHasTopicsEnabled(AValue: Boolean): ITgUser;
    function WithAllowsUsersToCreateTopics(AValue: Boolean): ITgUser;
    function WithCanManageBots(AValue: Boolean): ITgUser;
    function WithSupportsJoinRequestQueries(AValue: Boolean): ITgUser;
  end;

  TTgChatImpl = class(TTgJsonDto, ITgChat)
  public
    function GetId: Int64;
    function GetChatType: string;
    function GetTitle: string;
    function GetUsername: string;
    function GetFirstName: string;
    function GetLastName: string;
    function GetIsForum: Boolean;
    function GetIsDirectMessages: Boolean;
  end;

  TTgChatFullInfoImpl = class(TTgJsonDto, ITgChatFullInfo)
  public
    function GetId: Int64;
    function GetChatFullInfoType: string;
    function GetTitle: string;
    function GetUsername: string;
    function GetFirstName: string;
    function GetLastName: string;
    function GetIsForum: Boolean;
    function GetIsDirectMessages: Boolean;
    function GetAccentColorId: Int64;
    function GetMaxReactionCount: Integer;
    function GetPhoto: ITgChatPhoto;
    function GetActiveUsernames: TArray<string>;
    function GetBirthdate: ITgBirthdate;
    function GetBusinessIntro: ITgBusinessIntro;
    function GetBusinessLocation: ITgBusinessLocation;
    function GetBusinessOpeningHours: ITgBusinessOpeningHours;
    function GetPersonalChat: ITgChat;
    function GetParentChat: ITgChat;
    function GetAvailableReactions: TArray<ITgReactionType>;
    function GetBackgroundCustomEmojiId: string;
    function GetProfileAccentColorId: Int64;
    function GetHasProfileAccentColorId: Boolean;
    function GetProfileBackgroundCustomEmojiId: string;
    function GetEmojiStatusCustomEmojiId: string;
    function GetEmojiStatusExpirationDate: Int64;
    function GetHasEmojiStatusExpirationDate: Boolean;
    function GetBio: string;
    function GetHasPrivateForwards: Boolean;
    function GetHasRestrictedVoiceAndVideoMessages: Boolean;
    function GetJoinToSendMessages: Boolean;
    function GetJoinByRequest: Boolean;
    function GetDescription: string;
    function GetInviteLink: string;
    function GetPinnedMessage: ITgMessage;
    function GetPermissions: ITgChatPermissions;
    function GetAcceptedGiftTypes: ITgAcceptedGiftTypes;
    function GetCanSendPaidMedia: Boolean;
    function GetSlowModeDelay: Integer;
    function GetHasSlowModeDelay: Boolean;
    function GetUnrestrictBoostCount: Integer;
    function GetHasUnrestrictBoostCount: Boolean;
    function GetMessageAutoDeleteTime: Integer;
    function GetHasMessageAutoDeleteTime: Boolean;
    function GetHasAggressiveAntiSpamEnabled: Boolean;
    function GetHasHiddenMembers: Boolean;
    function GetHasProtectedContent: Boolean;
    function GetHasVisibleHistory: Boolean;
    function GetStickerSetName: string;
    function GetCanSetStickerSet: Boolean;
    function GetCustomEmojiStickerSetName: string;
    function GetLinkedChatId: Int64;
    function GetHasLinkedChatId: Boolean;
    function GetLocation: ITgChatLocation;
    function GetRating: ITgUserRating;
    function GetFirstProfileAudio: ITgAudio;
    function GetUniqueGiftColors: ITgUniqueGiftColors;
    function GetPaidMessageStarCount: Integer;
    function GetHasPaidMessageStarCount: Boolean;
    function GetGuardBot: ITgUser;
    function GetCommunity: ITgCommunity;
  end;

  TTgMaybeInaccessibleMessageImpl = class(TTgJsonDto, ITgMaybeInaccessibleMessage)
  public
    function GetKind: TTgMaybeInaccessibleMessageKind; virtual;
    function GetKindText: string;
    function GetMessageId: Int64;
    function GetDate: Int64;
    function GetChat: ITgChat;
    function AsMessage: ITgMessage;
    function AsInaccessibleMessage: ITgInaccessibleMessage;
  end;

  TTgMessageImpl = class(TTgMaybeInaccessibleMessageImpl, ITgMessage, ITgMaybeInaccessibleMessage)
  public
    function GetKind: TTgMaybeInaccessibleMessageKind; override;
    function GetMessageThreadId: Int64;
    function GetHasMessageThreadId: Boolean;
    function GetDirectMessagesTopic: ITgDirectMessagesTopic;
    function GetFrom: ITgUser;
    function GetSenderChat: ITgChat;
    function GetSenderBoostCount: Integer;
    function GetHasSenderBoostCount: Boolean;
    function GetSenderBusinessBot: ITgUser;
    function GetSenderTag: string;
    function GetReceiverUser: ITgUser;
    function GetEphemeralMessageId: Int64;
    function GetHasEphemeralMessageId: Boolean;
    function GetGuestQueryId: string;
    function GetBusinessConnectionId: string;
    function GetForwardOrigin: ITgMessageOrigin;
    function GetIsTopicMessage: Boolean;
    function GetIsAutomaticForward: Boolean;
    function GetReplyToMessage: ITgMessage;
    function GetExternalReply: ITgExternalReplyInfo;
    function GetQuote: ITgTextQuote;
    function GetReplyToStory: ITgStory;
    function GetReplyToChecklistTaskId: Int64;
    function GetHasReplyToChecklistTaskId: Boolean;
    function GetReplyToPollOptionId: string;
    function GetViaBot: ITgUser;
    function GetGuestBotCallerUser: ITgUser;
    function GetGuestBotCallerChat: ITgChat;
    function GetEditDate: Int64;
    function GetHasEditDate: Boolean;
    function GetHasProtectedContent: Boolean;
    function GetIsFromOffline: Boolean;
    function GetIsPaidPost: Boolean;
    function GetMediaGroupId: string;
    function GetAuthorSignature: string;
    function GetPaidStarCount: Integer;
    function GetHasPaidStarCount: Boolean;
    function GetText: string;
    function GetEntities: TArray<ITgMessageEntity>;
    function GetLinkPreviewOptions: ITgLinkPreviewOptions;
    function GetSuggestedPostInfo: ITgSuggestedPostInfo;
    function GetEffectId: string;
    function GetRichMessage: ITgRichMessage;
    function GetAnimation: ITgAnimation;
    function GetAudio: ITgAudio;
    function GetDocument: ITgDocument;
    function GetLivePhoto: ITgLivePhoto;
    function GetPaidMedia: ITgPaidMediaInfo;
    function GetPhoto: TArray<ITgPhotoSize>;
    function GetSticker: ITgSticker;
    function GetStory: ITgStory;
    function GetVideo: ITgVideo;
    function GetVideoNote: ITgVideoNote;
    function GetVoice: ITgVoice;
    function GetCaption: string;
    function GetCaptionEntities: TArray<ITgMessageEntity>;
    function GetShowCaptionAboveMedia: Boolean;
    function GetHasMediaSpoiler: Boolean;
    function GetChecklist: ITgChecklist;
    function GetContact: ITgContact;
    function GetDice: ITgDice;
    function GetGame: ITgGame;
    function GetPoll: ITgPoll;
    function GetVenue: ITgVenue;
    function GetLocation: ITgLocation;
    function GetNewChatMembers: TArray<ITgUser>;
    function GetLeftChatMember: ITgUser;
    function GetChatOwnerLeft: ITgChatOwnerLeft;
    function GetChatOwnerChanged: ITgChatOwnerChanged;
    function GetNewChatTitle: string;
    function GetNewChatPhoto: TArray<ITgPhotoSize>;
    function GetDeleteChatPhoto: Boolean;
    function GetGroupChatCreated: Boolean;
    function GetSupergroupChatCreated: Boolean;
    function GetChannelChatCreated: Boolean;
    function GetMessageAutoDeleteTimerChanged: ITgMessageAutoDeleteTimerChanged;
    function GetMigrateToChatId: Int64;
    function GetHasMigrateToChatId: Boolean;
    function GetMigrateFromChatId: Int64;
    function GetHasMigrateFromChatId: Boolean;
    function GetPinnedMessage: ITgMaybeInaccessibleMessage;
    function GetInvoice: ITgInvoice;
    function GetSuccessfulPayment: ITgSuccessfulPayment;
    function GetRefundedPayment: ITgRefundedPayment;
    function GetUsersShared: ITgUsersShared;
    function GetChatShared: ITgChatShared;
    function GetGift: ITgGiftInfo;
    function GetUniqueGift: ITgUniqueGiftInfo;
    function GetGiftUpgradeSent: ITgGiftInfo;
    function GetConnectedWebsite: string;
    function GetWriteAccessAllowed: ITgWriteAccessAllowed;
    function GetPassportData: ITgPassportData;
    function GetProximityAlertTriggered: ITgProximityAlertTriggered;
    function GetBoostAdded: ITgChatBoostAdded;
    function GetChatBackgroundSet: ITgChatBackground;
    function GetChecklistTasksDone: ITgChecklistTasksDone;
    function GetChecklistTasksAdded: ITgChecklistTasksAdded;
    function GetCommunityChatAdded: ITgCommunityChatAdded;
    function GetCommunityChatJoined: ITgCommunityChatJoined;
    function GetCommunityChatRemoved: ITgCommunityChatRemoved;
    function GetDirectMessagePriceChanged: ITgDirectMessagePriceChanged;
    function GetForumTopicCreated: ITgForumTopicCreated;
    function GetForumTopicEdited: ITgForumTopicEdited;
    function GetForumTopicClosed: ITgForumTopicClosed;
    function GetForumTopicReopened: ITgForumTopicReopened;
    function GetGeneralForumTopicHidden: ITgGeneralForumTopicHidden;
    function GetGeneralForumTopicUnhidden: ITgGeneralForumTopicUnhidden;
    function GetGiveawayCreated: ITgGiveawayCreated;
    function GetGiveaway: ITgGiveaway;
    function GetGiveawayWinners: ITgGiveawayWinners;
    function GetGiveawayCompleted: ITgGiveawayCompleted;
    function GetManagedBotCreated: ITgManagedBotCreated;
    function GetPaidMessagePriceChanged: ITgPaidMessagePriceChanged;
    function GetPollOptionAdded: ITgPollOptionAdded;
    function GetPollOptionDeleted: ITgPollOptionDeleted;
    function GetSuggestedPostApproved: ITgSuggestedPostApproved;
    function GetSuggestedPostApprovalFailed: ITgSuggestedPostApprovalFailed;
    function GetSuggestedPostDeclined: ITgSuggestedPostDeclined;
    function GetSuggestedPostPaid: ITgSuggestedPostPaid;
    function GetSuggestedPostRefunded: ITgSuggestedPostRefunded;
    function GetVideoChatScheduled: ITgVideoChatScheduled;
    function GetVideoChatStarted: ITgVideoChatStarted;
    function GetVideoChatEnded: ITgVideoChatEnded;
    function GetVideoChatParticipantsInvited: ITgVideoChatParticipantsInvited;
    function GetWebAppData: ITgWebAppData;
    function GetReplyMarkup: ITgInlineKeyboardMarkup;
  end;

  TTgMessageIdImpl = class(TTgJsonDto, ITgMessageId)
  public
    function GetMessageId: Int64;
  end;

  TTgInaccessibleMessageImpl = class(TTgMaybeInaccessibleMessageImpl, ITgInaccessibleMessage, ITgMaybeInaccessibleMessage)
  public
    function GetKind: TTgMaybeInaccessibleMessageKind; override;
  end;

  TTgMessageEntityImpl = class(TTgJsonDto, ITgMessageEntity)
  public
    function GetMessageEntityType: string;
    function GetOffset: Integer;
    function GetLength: Integer;
    function GetUrl: string;
    function GetUser: ITgUser;
    function GetLanguage: string;
    function GetCustomEmojiId: string;
    function GetUnixTime: Integer;
    function GetHasUnixTime: Boolean;
    function GetDateTimeFormat: string;
    function WithMessageEntityType(const AValue: string): ITgMessageEntity;
    function WithOffset(AValue: Integer): ITgMessageEntity;
    function WithLength(AValue: Integer): ITgMessageEntity;
    function WithUrl(const AValue: string): ITgMessageEntity;
    function WithUser(const AValue: ITgUser): ITgMessageEntity;
    function WithLanguage(const AValue: string): ITgMessageEntity;
    function WithCustomEmojiId(const AValue: string): ITgMessageEntity;
    function WithUnixTime(AValue: Integer): ITgMessageEntity;
    function WithDateTimeFormat(const AValue: string): ITgMessageEntity;
  end;

  TTgTextQuoteImpl = class(TTgJsonDto, ITgTextQuote)
  public
    function GetText: string;
    function GetEntities: TArray<ITgMessageEntity>;
    function GetPosition: Integer;
    function GetIsManual: Boolean;
  end;

  TTgExternalReplyInfoImpl = class(TTgJsonDto, ITgExternalReplyInfo)
  public
    function GetOrigin: ITgMessageOrigin;
    function GetChat: ITgChat;
    function GetMessageId: Int64;
    function GetHasMessageId: Boolean;
    function GetLinkPreviewOptions: ITgLinkPreviewOptions;
    function GetAnimation: ITgAnimation;
    function GetAudio: ITgAudio;
    function GetDocument: ITgDocument;
    function GetLivePhoto: ITgLivePhoto;
    function GetPaidMedia: ITgPaidMediaInfo;
    function GetPhoto: TArray<ITgPhotoSize>;
    function GetSticker: ITgSticker;
    function GetStory: ITgStory;
    function GetVideo: ITgVideo;
    function GetVideoNote: ITgVideoNote;
    function GetVoice: ITgVoice;
    function GetHasMediaSpoiler: Boolean;
    function GetChecklist: ITgChecklist;
    function GetContact: ITgContact;
    function GetDice: ITgDice;
    function GetGame: ITgGame;
    function GetGiveaway: ITgGiveaway;
    function GetGiveawayWinners: ITgGiveawayWinners;
    function GetInvoice: ITgInvoice;
    function GetLocation: ITgLocation;
    function GetPoll: ITgPoll;
    function GetVenue: ITgVenue;
  end;

  TTgReplyParametersImpl = class(TTgOutObject, ITgReplyParameters)
  public
    function WithMessageId(AValue: Int64): ITgReplyParameters;
    function WithChatId(const AValue: TTgChatId): ITgReplyParameters;
    function WithEphemeralMessageId(AValue: Int64): ITgReplyParameters;
    function WithAllowSendingWithoutReply(AValue: Boolean): ITgReplyParameters;
    function WithQuote(const AValue: string): ITgReplyParameters;
    function WithQuoteParseMode(const AValue: string): ITgReplyParameters;
    function WithQuoteEntities(const AValue: array of ITgMessageEntity): ITgReplyParameters;
    function WithQuotePosition(AValue: Integer): ITgReplyParameters;
    function WithChecklistTaskId(AValue: Int64): ITgReplyParameters;
    function WithPollOptionId(const AValue: string): ITgReplyParameters;
  end;

  TTgEphemeralMessageParametersImpl = class(TTgOutObject, ITgEphemeralMessageParameters)
  public
    function WithReceiverUserId(AValue: Int64): ITgEphemeralMessageParameters;
    function WithCallbackQueryId(const AValue: string): ITgEphemeralMessageParameters;
    function WithReplaceCallbackQueryMessage(AValue: Boolean): ITgEphemeralMessageParameters;
  end;

  TTgMessageOriginImpl = class(TTgJsonDto, ITgMessageOrigin)
  public
    function GetKind: TTgMessageOriginKind; virtual;
    function GetKindText: string;
    function GetDate: Int64;
    function AsUser: ITgMessageOriginUser;
    function AsHiddenUser: ITgMessageOriginHiddenUser;
    function AsChat: ITgMessageOriginChat;
    function AsChannel: ITgMessageOriginChannel;
  end;

  TTgMessageOriginUserImpl = class(TTgMessageOriginImpl, ITgMessageOriginUser, ITgMessageOrigin)
  public
    function GetKind: TTgMessageOriginKind; override;
    function GetSenderUser: ITgUser;
  end;

  TTgMessageOriginHiddenUserImpl = class(TTgMessageOriginImpl, ITgMessageOriginHiddenUser, ITgMessageOrigin)
  public
    function GetKind: TTgMessageOriginKind; override;
    function GetSenderUserName: string;
  end;

  TTgMessageOriginChatImpl = class(TTgMessageOriginImpl, ITgMessageOriginChat, ITgMessageOrigin)
  public
    function GetKind: TTgMessageOriginKind; override;
    function GetSenderChat: ITgChat;
    function GetAuthorSignature: string;
  end;

  TTgMessageOriginChannelImpl = class(TTgMessageOriginImpl, ITgMessageOriginChannel, ITgMessageOrigin)
  public
    function GetKind: TTgMessageOriginKind; override;
    function GetChat: ITgChat;
    function GetMessageId: Int64;
    function GetAuthorSignature: string;
  end;

  TTgPhotoSizeImpl = class(TTgJsonDto, ITgPhotoSize)
  public
    function GetFileId: string;
    function GetFileUniqueId: string;
    function GetWidth: Integer;
    function GetHeight: Integer;
    function GetFileSize: Int64;
    function GetHasFileSize: Boolean;
  end;

  TTgAnimationImpl = class(TTgJsonDto, ITgAnimation)
  public
    function GetFileId: string;
    function GetFileUniqueId: string;
    function GetWidth: Integer;
    function GetHeight: Integer;
    function GetDuration: Integer;
    function GetThumbnail: ITgPhotoSize;
    function GetFileName: string;
    function GetMimeType: string;
    function GetFileSize: Int64;
    function GetHasFileSize: Boolean;
  end;

  TTgAudioImpl = class(TTgJsonDto, ITgAudio)
  public
    function GetFileId: string;
    function GetFileUniqueId: string;
    function GetDuration: Integer;
    function GetPerformer: string;
    function GetTitle: string;
    function GetFileName: string;
    function GetMimeType: string;
    function GetFileSize: Int64;
    function GetHasFileSize: Boolean;
    function GetThumbnail: ITgPhotoSize;
  end;

  TTgDocumentImpl = class(TTgJsonDto, ITgDocument)
  public
    function GetFileId: string;
    function GetFileUniqueId: string;
    function GetThumbnail: ITgPhotoSize;
    function GetFileName: string;
    function GetMimeType: string;
    function GetFileSize: Int64;
    function GetHasFileSize: Boolean;
  end;

  TTgLivePhotoImpl = class(TTgJsonDto, ITgLivePhoto)
  public
    function GetPhoto: TArray<ITgPhotoSize>;
    function GetFileId: string;
    function GetFileUniqueId: string;
    function GetWidth: Integer;
    function GetHeight: Integer;
    function GetDuration: Integer;
    function GetMimeType: string;
    function GetFileSize: Int64;
    function GetHasFileSize: Boolean;
  end;

  TTgStoryImpl = class(TTgJsonDto, ITgStory)
  public
    function GetChat: ITgChat;
    function GetId: Int64;
  end;

  TTgVideoQualityImpl = class(TTgJsonDto, ITgVideoQuality)
  public
    function GetFileId: string;
    function GetFileUniqueId: string;
    function GetWidth: Integer;
    function GetHeight: Integer;
    function GetCodec: string;
    function GetFileSize: Int64;
    function GetHasFileSize: Boolean;
  end;

  TTgVideoImpl = class(TTgJsonDto, ITgVideo)
  public
    function GetFileId: string;
    function GetFileUniqueId: string;
    function GetWidth: Integer;
    function GetHeight: Integer;
    function GetDuration: Integer;
    function GetThumbnail: ITgPhotoSize;
    function GetCover: TArray<ITgPhotoSize>;
    function GetStartTimestamp: Integer;
    function GetHasStartTimestamp: Boolean;
    function GetQualities: TArray<ITgVideoQuality>;
    function GetFileName: string;
    function GetMimeType: string;
    function GetFileSize: Int64;
    function GetHasFileSize: Boolean;
  end;

  TTgVideoNoteImpl = class(TTgJsonDto, ITgVideoNote)
  public
    function GetFileId: string;
    function GetFileUniqueId: string;
    function GetLength: Integer;
    function GetDuration: Integer;
    function GetThumbnail: ITgPhotoSize;
    function GetFileSize: Int64;
    function GetHasFileSize: Boolean;
  end;

  TTgVoiceImpl = class(TTgJsonDto, ITgVoice)
  public
    function GetFileId: string;
    function GetFileUniqueId: string;
    function GetDuration: Integer;
    function GetMimeType: string;
    function GetFileSize: Int64;
    function GetHasFileSize: Boolean;
  end;

  TTgPaidMediaInfoImpl = class(TTgJsonDto, ITgPaidMediaInfo)
  public
    function GetStarCount: Integer;
    function GetPaidMedia: TArray<ITgPaidMedia>;
  end;

  TTgPaidMediaImpl = class(TTgJsonDto, ITgPaidMedia)
  public
    function GetKind: TTgPaidMediaKind; virtual;
    function GetKindText: string;
    function AsLivePhoto: ITgPaidMediaLivePhoto;
    function AsPhoto: ITgPaidMediaPhoto;
    function AsPreview: ITgPaidMediaPreview;
    function AsVideo: ITgPaidMediaVideo;
  end;

  TTgPaidMediaLivePhotoImpl = class(TTgPaidMediaImpl, ITgPaidMediaLivePhoto, ITgPaidMedia)
  public
    function GetKind: TTgPaidMediaKind; override;
    function GetLivePhoto: ITgLivePhoto;
  end;

  TTgPaidMediaPhotoImpl = class(TTgPaidMediaImpl, ITgPaidMediaPhoto, ITgPaidMedia)
  public
    function GetKind: TTgPaidMediaKind; override;
    function GetPhoto: TArray<ITgPhotoSize>;
  end;

  TTgPaidMediaPreviewImpl = class(TTgPaidMediaImpl, ITgPaidMediaPreview, ITgPaidMedia)
  public
    function GetKind: TTgPaidMediaKind; override;
    function GetWidth: Integer;
    function GetHasWidth: Boolean;
    function GetHeight: Integer;
    function GetHasHeight: Boolean;
    function GetDuration: Integer;
    function GetHasDuration: Boolean;
  end;

  TTgPaidMediaVideoImpl = class(TTgPaidMediaImpl, ITgPaidMediaVideo, ITgPaidMedia)
  public
    function GetKind: TTgPaidMediaKind; override;
    function GetVideo: ITgVideo;
  end;

  TTgContactImpl = class(TTgJsonDto, ITgContact)
  public
    function GetPhoneNumber: string;
    function GetFirstName: string;
    function GetLastName: string;
    function GetUserId: Int64;
    function GetHasUserId: Boolean;
    function GetVcard: string;
  end;

  TTgDiceImpl = class(TTgJsonDto, ITgDice)
  public
    function GetEmoji: string;
    function GetValue: Integer;
  end;

  TTgLinkImpl = class(TTgJsonDto, ITgLink)
  public
    function GetUrl: string;
  end;

  TTgPollMediaImpl = class(TTgJsonDto, ITgPollMedia)
  public
    function GetAnimation: ITgAnimation;
    function GetAudio: ITgAudio;
    function GetDocument: ITgDocument;
    function GetLink: ITgLink;
    function GetLivePhoto: ITgLivePhoto;
    function GetLocation: ITgLocation;
    function GetPhoto: TArray<ITgPhotoSize>;
    function GetSticker: ITgSticker;
    function GetVenue: ITgVenue;
    function GetVideo: ITgVideo;
  end;

  TTgPollOptionImpl = class(TTgJsonDto, ITgPollOption)
  public
    function GetPersistentId: string;
    function GetText: string;
    function GetTextEntities: TArray<ITgMessageEntity>;
    function GetMedia: ITgPollMedia;
    function GetVoterCount: Integer;
    function GetAddedByUser: ITgUser;
    function GetAddedByChat: ITgChat;
    function GetAdditionDate: Int64;
    function GetHasAdditionDate: Boolean;
  end;

  TTgInputPollOptionImpl = class(TTgOutObject, ITgInputPollOption)
  public
    function WithText(const AValue: string): ITgInputPollOption;
    function WithTextParseMode(const AValue: string): ITgInputPollOption;
    function WithTextEntities(const AValue: array of ITgMessageEntity): ITgInputPollOption;
    function WithMedia(const AValue: TTgInputPollOptionMedia): ITgInputPollOption;
  end;

  TTgPollAnswerImpl = class(TTgJsonDto, ITgPollAnswer)
  public
    function GetPollId: string;
    function GetVoterChat: ITgChat;
    function GetUser: ITgUser;
    function GetOptionIds: TArray<Int64>;
    function GetOptionPersistentIds: TArray<string>;
  end;

  TTgPollImpl = class(TTgJsonDto, ITgPoll)
  public
    function GetId: string;
    function GetQuestion: string;
    function GetQuestionEntities: TArray<ITgMessageEntity>;
    function GetOptions: TArray<ITgPollOption>;
    function GetTotalVoterCount: Integer;
    function GetIsClosed: Boolean;
    function GetIsAnonymous: Boolean;
    function GetPollType: string;
    function GetAllowsMultipleAnswers: Boolean;
    function GetAllowsRevoting: Boolean;
    function GetMembersOnly: Boolean;
    function GetCountryCodes: TArray<string>;
    function GetCorrectOptionIds: TArray<Int64>;
    function GetExplanation: string;
    function GetExplanationEntities: TArray<ITgMessageEntity>;
    function GetExplanationMedia: ITgPollMedia;
    function GetOpenPeriod: Integer;
    function GetHasOpenPeriod: Boolean;
    function GetCloseDate: Int64;
    function GetHasCloseDate: Boolean;
    function GetDescription: string;
    function GetDescriptionEntities: TArray<ITgMessageEntity>;
    function GetMedia: ITgPollMedia;
  end;

  TTgChecklistTaskImpl = class(TTgJsonDto, ITgChecklistTask)
  public
    function GetId: Int64;
    function GetText: string;
    function GetTextEntities: TArray<ITgMessageEntity>;
    function GetCompletedByUser: ITgUser;
    function GetCompletedByChat: ITgChat;
    function GetCompletionDate: Int64;
    function GetHasCompletionDate: Boolean;
  end;

  TTgChecklistImpl = class(TTgJsonDto, ITgChecklist)
  public
    function GetTitle: string;
    function GetTitleEntities: TArray<ITgMessageEntity>;
    function GetTasks: TArray<ITgChecklistTask>;
    function GetOthersCanAddTasks: Boolean;
    function GetOthersCanMarkTasksAsDone: Boolean;
  end;

  TTgInputChecklistTaskImpl = class(TTgOutObject, ITgInputChecklistTask)
  public
    function WithId(AValue: Int64): ITgInputChecklistTask;
    function WithText(const AValue: string): ITgInputChecklistTask;
    function WithParseMode(const AValue: string): ITgInputChecklistTask;
    function WithTextEntities(const AValue: array of ITgMessageEntity): ITgInputChecklistTask;
  end;

  TTgInputChecklistImpl = class(TTgOutObject, ITgInputChecklist)
  public
    function WithTitle(const AValue: string): ITgInputChecklist;
    function WithParseMode(const AValue: string): ITgInputChecklist;
    function WithTitleEntities(const AValue: array of ITgMessageEntity): ITgInputChecklist;
    function WithTasks(const AValue: array of ITgInputChecklistTask): ITgInputChecklist;
    function WithOthersCanAddTasks(AValue: Boolean): ITgInputChecklist;
    function WithOthersCanMarkTasksAsDone(AValue: Boolean): ITgInputChecklist;
  end;

  TTgLocationImpl = class(TTgJsonDto, ITgLocation)
  public
    function GetLatitude: Double;
    function GetLongitude: Double;
    function GetHorizontalAccuracy: Double;
    function GetHasHorizontalAccuracy: Boolean;
    function GetLivePeriod: Integer;
    function GetHasLivePeriod: Boolean;
    function GetHeading: Integer;
    function GetHasHeading: Boolean;
    function GetProximityAlertRadius: Integer;
    function GetHasProximityAlertRadius: Boolean;
    function WithLatitude(AValue: Double): ITgLocation;
    function WithLongitude(AValue: Double): ITgLocation;
    function WithHorizontalAccuracy(AValue: Double): ITgLocation;
    function WithLivePeriod(AValue: Integer): ITgLocation;
    function WithHeading(AValue: Integer): ITgLocation;
    function WithProximityAlertRadius(AValue: Integer): ITgLocation;
  end;

  TTgVenueImpl = class(TTgJsonDto, ITgVenue)
  public
    function GetLocation: ITgLocation;
    function GetTitle: string;
    function GetAddress: string;
    function GetFoursquareId: string;
    function GetFoursquareType: string;
    function GetGooglePlaceId: string;
    function GetGooglePlaceType: string;
  end;

  TTgWebAppDataImpl = class(TTgJsonDto, ITgWebAppData)
  public
    function GetData: string;
    function GetButtonText: string;
  end;

  TTgProximityAlertTriggeredImpl = class(TTgJsonDto, ITgProximityAlertTriggered)
  public
    function GetTraveler: ITgUser;
    function GetWatcher: ITgUser;
    function GetDistance: Integer;
  end;

  TTgMessageAutoDeleteTimerChangedImpl = class(TTgJsonDto, ITgMessageAutoDeleteTimerChanged)
  public
    function GetMessageAutoDeleteTime: Integer;
  end;

  TTgManagedBotCreatedImpl = class(TTgJsonDto, ITgManagedBotCreated)
  public
    function GetBot: ITgUser;
  end;

  TTgManagedBotUpdatedImpl = class(TTgJsonDto, ITgManagedBotUpdated)
  public
    function GetUser: ITgUser;
    function GetBot: ITgUser;
  end;

  TTgBotSubscriptionUpdatedImpl = class(TTgJsonDto, ITgBotSubscriptionUpdated)
  public
    function GetUser: ITgUser;
    function GetInvoicePayload: string;
    function GetState: string;
  end;

  TTgMessageGenerationStoppedImpl = class(TTgJsonDto, ITgMessageGenerationStopped)
  public
    function GetChat: ITgChat;
    function GetMessageThreadId: Int64;
    function GetHasMessageThreadId: Boolean;
    function GetDraftId: Int64;
  end;

  TTgPollOptionAddedImpl = class(TTgJsonDto, ITgPollOptionAdded)
  public
    function GetPollMessage: ITgMaybeInaccessibleMessage;
    function GetOptionPersistentId: string;
    function GetOptionText: string;
    function GetOptionTextEntities: TArray<ITgMessageEntity>;
  end;

  TTgPollOptionDeletedImpl = class(TTgJsonDto, ITgPollOptionDeleted)
  public
    function GetPollMessage: ITgMaybeInaccessibleMessage;
    function GetOptionPersistentId: string;
    function GetOptionText: string;
    function GetOptionTextEntities: TArray<ITgMessageEntity>;
  end;

  TTgChatBoostAddedImpl = class(TTgJsonDto, ITgChatBoostAdded)
  public
    function GetBoostCount: Integer;
  end;

  TTgBackgroundFillImpl = class(TTgJsonDto, ITgBackgroundFill)
  public
    function GetKind: TTgBackgroundFillKind; virtual;
    function GetKindText: string;
    function AsSolid: ITgBackgroundFillSolid;
    function AsGradient: ITgBackgroundFillGradient;
    function AsFreeformGradient: ITgBackgroundFillFreeformGradient;
  end;

  TTgBackgroundFillSolidImpl = class(TTgBackgroundFillImpl, ITgBackgroundFillSolid, ITgBackgroundFill)
  public
    function GetKind: TTgBackgroundFillKind; override;
    function GetColor: Integer;
  end;

  TTgBackgroundFillGradientImpl = class(TTgBackgroundFillImpl, ITgBackgroundFillGradient, ITgBackgroundFill)
  public
    function GetKind: TTgBackgroundFillKind; override;
    function GetTopColor: Integer;
    function GetBottomColor: Integer;
    function GetRotationAngle: Integer;
  end;

  TTgBackgroundFillFreeformGradientImpl = class(TTgBackgroundFillImpl, ITgBackgroundFillFreeformGradient, ITgBackgroundFill)
  public
    function GetKind: TTgBackgroundFillKind; override;
    function GetColors: TArray<Integer>;
  end;

  TTgBackgroundTypeImpl = class(TTgJsonDto, ITgBackgroundType)
  public
    function GetKind: TTgBackgroundTypeKind; virtual;
    function GetKindText: string;
    function AsFill: ITgBackgroundTypeFill;
    function AsWallpaper: ITgBackgroundTypeWallpaper;
    function AsPattern: ITgBackgroundTypePattern;
    function AsChatTheme: ITgBackgroundTypeChatTheme;
  end;

  TTgBackgroundTypeFillImpl = class(TTgBackgroundTypeImpl, ITgBackgroundTypeFill, ITgBackgroundType)
  public
    function GetKind: TTgBackgroundTypeKind; override;
    function GetFill: ITgBackgroundFill;
    function GetDarkThemeDimming: Integer;
  end;

  TTgBackgroundTypeWallpaperImpl = class(TTgBackgroundTypeImpl, ITgBackgroundTypeWallpaper, ITgBackgroundType)
  public
    function GetKind: TTgBackgroundTypeKind; override;
    function GetDocument: ITgDocument;
    function GetDarkThemeDimming: Integer;
    function GetIsBlurred: Boolean;
    function GetIsMoving: Boolean;
  end;

  TTgBackgroundTypePatternImpl = class(TTgBackgroundTypeImpl, ITgBackgroundTypePattern, ITgBackgroundType)
  public
    function GetKind: TTgBackgroundTypeKind; override;
    function GetDocument: ITgDocument;
    function GetFill: ITgBackgroundFill;
    function GetIntensity: Integer;
    function GetIsInverted: Boolean;
    function GetIsMoving: Boolean;
  end;

  TTgBackgroundTypeChatThemeImpl = class(TTgBackgroundTypeImpl, ITgBackgroundTypeChatTheme, ITgBackgroundType)
  public
    function GetKind: TTgBackgroundTypeKind; override;
    function GetThemeName: string;
  end;

  TTgChatBackgroundImpl = class(TTgJsonDto, ITgChatBackground)
  public
    function GetChatBackgroundType: ITgBackgroundType;
  end;

  TTgChecklistTasksDoneImpl = class(TTgJsonDto, ITgChecklistTasksDone)
  public
    function GetChecklistMessage: ITgMessage;
    function GetMarkedAsDoneTaskIds: TArray<Int64>;
    function GetMarkedAsNotDoneTaskIds: TArray<Int64>;
  end;

  TTgChecklistTasksAddedImpl = class(TTgJsonDto, ITgChecklistTasksAdded)
  public
    function GetChecklistMessage: ITgMessage;
    function GetTasks: TArray<ITgChecklistTask>;
  end;

  TTgCommunityChatAddedImpl = class(TTgJsonDto, ITgCommunityChatAdded)
  public
    function GetCommunity: ITgCommunity;
  end;

  TTgCommunityChatJoinedImpl = class(TTgJsonDto, ITgCommunityChatJoined)
  public
    function GetCommunity: ITgCommunity;
  end;

  TTgCommunityChatRemovedImpl = class(TTgJsonDto, ITgCommunityChatRemoved)
  public
  end;

  TTgForumTopicCreatedImpl = class(TTgJsonDto, ITgForumTopicCreated)
  public
    function GetName: string;
    function GetIconColor: Integer;
    function GetIconCustomEmojiId: string;
    function GetIsNameImplicit: Boolean;
  end;

  TTgForumTopicClosedImpl = class(TTgJsonDto, ITgForumTopicClosed)
  public
  end;

  TTgForumTopicEditedImpl = class(TTgJsonDto, ITgForumTopicEdited)
  public
    function GetName: string;
    function GetIconCustomEmojiId: string;
  end;

  TTgForumTopicReopenedImpl = class(TTgJsonDto, ITgForumTopicReopened)
  public
  end;

  TTgGeneralForumTopicHiddenImpl = class(TTgJsonDto, ITgGeneralForumTopicHidden)
  public
  end;

  TTgGeneralForumTopicUnhiddenImpl = class(TTgJsonDto, ITgGeneralForumTopicUnhidden)
  public
  end;

  TTgSharedUserImpl = class(TTgJsonDto, ITgSharedUser)
  public
    function GetUserId: Int64;
    function GetFirstName: string;
    function GetLastName: string;
    function GetUsername: string;
    function GetPhoto: TArray<ITgPhotoSize>;
  end;

  TTgUsersSharedImpl = class(TTgJsonDto, ITgUsersShared)
  public
    function GetRequestId: Int64;
    function GetUsers: TArray<ITgSharedUser>;
  end;

  TTgChatSharedImpl = class(TTgJsonDto, ITgChatShared)
  public
    function GetRequestId: Int64;
    function GetChatId: Int64;
    function GetTitle: string;
    function GetUsername: string;
    function GetPhoto: TArray<ITgPhotoSize>;
  end;

  TTgWriteAccessAllowedImpl = class(TTgJsonDto, ITgWriteAccessAllowed)
  public
    function GetFromRequest: Boolean;
    function GetHasFromRequest: Boolean;
    function GetWebAppName: string;
    function GetFromAttachmentMenu: Boolean;
    function GetHasFromAttachmentMenu: Boolean;
  end;

  TTgVideoChatScheduledImpl = class(TTgJsonDto, ITgVideoChatScheduled)
  public
    function GetStartDate: Int64;
  end;

  TTgVideoChatStartedImpl = class(TTgJsonDto, ITgVideoChatStarted)
  public
  end;

  TTgVideoChatEndedImpl = class(TTgJsonDto, ITgVideoChatEnded)
  public
    function GetDuration: Integer;
  end;

  TTgVideoChatParticipantsInvitedImpl = class(TTgJsonDto, ITgVideoChatParticipantsInvited)
  public
    function GetUsers: TArray<ITgUser>;
  end;

  TTgPaidMessagePriceChangedImpl = class(TTgJsonDto, ITgPaidMessagePriceChanged)
  public
    function GetPaidMessageStarCount: Integer;
  end;

  TTgDirectMessagePriceChangedImpl = class(TTgJsonDto, ITgDirectMessagePriceChanged)
  public
    function GetAreDirectMessagesEnabled: Boolean;
    function GetDirectMessageStarCount: Integer;
    function GetHasDirectMessageStarCount: Boolean;
  end;

  TTgSuggestedPostApprovedImpl = class(TTgJsonDto, ITgSuggestedPostApproved)
  public
    function GetSuggestedPostMessage: ITgMessage;
    function GetPrice: ITgSuggestedPostPrice;
    function GetSendDate: Int64;
  end;

  TTgSuggestedPostApprovalFailedImpl = class(TTgJsonDto, ITgSuggestedPostApprovalFailed)
  public
    function GetSuggestedPostMessage: ITgMessage;
    function GetPrice: ITgSuggestedPostPrice;
  end;

  TTgSuggestedPostDeclinedImpl = class(TTgJsonDto, ITgSuggestedPostDeclined)
  public
    function GetSuggestedPostMessage: ITgMessage;
    function GetComment: string;
  end;

  TTgSuggestedPostPaidImpl = class(TTgJsonDto, ITgSuggestedPostPaid)
  public
    function GetSuggestedPostMessage: ITgMessage;
    function GetCurrency: string;
    function GetAmount: Integer;
    function GetHasAmount: Boolean;
    function GetStarAmount: ITgStarAmount;
  end;

  TTgSuggestedPostRefundedImpl = class(TTgJsonDto, ITgSuggestedPostRefunded)
  public
    function GetSuggestedPostMessage: ITgMessage;
    function GetReason: string;
  end;

  TTgGiveawayCreatedImpl = class(TTgJsonDto, ITgGiveawayCreated)
  public
    function GetPrizeStarCount: Integer;
    function GetHasPrizeStarCount: Boolean;
  end;

  TTgGiveawayImpl = class(TTgJsonDto, ITgGiveaway)
  public
    function GetChats: TArray<ITgChat>;
    function GetWinnersSelectionDate: Int64;
    function GetWinnerCount: Integer;
    function GetOnlyNewMembers: Boolean;
    function GetHasPublicWinners: Boolean;
    function GetPrizeDescription: string;
    function GetCountryCodes: TArray<string>;
    function GetPrizeStarCount: Integer;
    function GetHasPrizeStarCount: Boolean;
    function GetPremiumSubscriptionMonthCount: Integer;
    function GetHasPremiumSubscriptionMonthCount: Boolean;
  end;

  TTgGiveawayWinnersImpl = class(TTgJsonDto, ITgGiveawayWinners)
  public
    function GetChat: ITgChat;
    function GetGiveawayMessageId: Int64;
    function GetWinnersSelectionDate: Int64;
    function GetWinnerCount: Integer;
    function GetWinners: TArray<ITgUser>;
    function GetAdditionalChatCount: Integer;
    function GetHasAdditionalChatCount: Boolean;
    function GetPrizeStarCount: Integer;
    function GetHasPrizeStarCount: Boolean;
    function GetPremiumSubscriptionMonthCount: Integer;
    function GetHasPremiumSubscriptionMonthCount: Boolean;
    function GetUnclaimedPrizeCount: Integer;
    function GetHasUnclaimedPrizeCount: Boolean;
    function GetOnlyNewMembers: Boolean;
    function GetWasRefunded: Boolean;
    function GetPrizeDescription: string;
  end;

  TTgGiveawayCompletedImpl = class(TTgJsonDto, ITgGiveawayCompleted)
  public
    function GetWinnerCount: Integer;
    function GetUnclaimedPrizeCount: Integer;
    function GetHasUnclaimedPrizeCount: Boolean;
    function GetGiveawayMessage: ITgMessage;
    function GetIsStarGiveaway: Boolean;
  end;

  TTgLinkPreviewOptionsImpl = class(TTgJsonDto, ITgLinkPreviewOptions)
  public
    function GetIsDisabled: Boolean;
    function GetHasIsDisabled: Boolean;
    function GetUrl: string;
    function GetPreferSmallMedia: Boolean;
    function GetHasPreferSmallMedia: Boolean;
    function GetPreferLargeMedia: Boolean;
    function GetHasPreferLargeMedia: Boolean;
    function GetShowAboveText: Boolean;
    function GetHasShowAboveText: Boolean;
    function WithIsDisabled(AValue: Boolean): ITgLinkPreviewOptions;
    function WithUrl(const AValue: string): ITgLinkPreviewOptions;
    function WithPreferSmallMedia(AValue: Boolean): ITgLinkPreviewOptions;
    function WithPreferLargeMedia(AValue: Boolean): ITgLinkPreviewOptions;
    function WithShowAboveText(AValue: Boolean): ITgLinkPreviewOptions;
  end;

  TTgSuggestedPostPriceImpl = class(TTgJsonDto, ITgSuggestedPostPrice)
  public
    function GetCurrency: string;
    function GetAmount: Integer;
    function WithCurrency(const AValue: string): ITgSuggestedPostPrice;
    function WithAmount(AValue: Integer): ITgSuggestedPostPrice;
  end;

  TTgSuggestedPostInfoImpl = class(TTgJsonDto, ITgSuggestedPostInfo)
  public
    function GetState: string;
    function GetPrice: ITgSuggestedPostPrice;
    function GetSendDate: Int64;
    function GetHasSendDate: Boolean;
  end;

  TTgSuggestedPostParametersImpl = class(TTgOutObject, ITgSuggestedPostParameters)
  public
    function WithPrice(const AValue: ITgSuggestedPostPrice): ITgSuggestedPostParameters;
    function WithSendDate(AValue: Int64): ITgSuggestedPostParameters;
  end;

  TTgDirectMessagesTopicImpl = class(TTgJsonDto, ITgDirectMessagesTopic)
  public
    function GetTopicId: Int64;
    function GetUser: ITgUser;
  end;

  TTgUserProfilePhotosImpl = class(TTgJsonDto, ITgUserProfilePhotos)
  public
    function GetTotalCount: Integer;
    function GetPhotos: TArray<TArray<ITgPhotoSize>>;
  end;

  TTgUserProfileAudiosImpl = class(TTgJsonDto, ITgUserProfileAudios)
  public
    function GetTotalCount: Integer;
    function GetAudios: TArray<ITgAudio>;
  end;

  TTgFileImpl = class(TTgJsonDto, ITgFile)
  public
    function GetFileId: string;
    function GetFileUniqueId: string;
    function GetFileSize: Int64;
    function GetHasFileSize: Boolean;
    function GetFilePath: string;
  end;

  TTgWebAppInfoImpl = class(TTgJsonDto, ITgWebAppInfo)
  public
    function GetUrl: string;
    function WithUrl(const AValue: string): ITgWebAppInfo;
  end;

  TTgReplyKeyboardMarkupImpl = class(TTgOutObject, ITgReplyKeyboardMarkup)
  public
    function WithKeyboard(const AValue: array of TArray<ITgKeyboardButton>): ITgReplyKeyboardMarkup;
    function WithKeyboardRow(const ARow: array of ITgKeyboardButton): ITgReplyKeyboardMarkup;
    function WithIsPersistent(AValue: Boolean): ITgReplyKeyboardMarkup;
    function WithResizeKeyboard(AValue: Boolean): ITgReplyKeyboardMarkup;
    function WithOneTimeKeyboard(AValue: Boolean): ITgReplyKeyboardMarkup;
    function WithInputFieldPlaceholder(const AValue: string): ITgReplyKeyboardMarkup;
    function WithSelective(AValue: Boolean): ITgReplyKeyboardMarkup;
    function WithForceReply(AValue: Boolean): ITgReplyKeyboardMarkup;
  end;

  TTgKeyboardButtonImpl = class(TTgOutObject, ITgKeyboardButton)
  public
    function WithText(const AValue: string): ITgKeyboardButton;
    function WithIconCustomEmojiId(const AValue: string): ITgKeyboardButton;
    function WithStyle(const AValue: string): ITgKeyboardButton;
    function WithRequestUsers(const AValue: ITgKeyboardButtonRequestUsers): ITgKeyboardButton;
    function WithRequestChat(const AValue: ITgKeyboardButtonRequestChat): ITgKeyboardButton;
    function WithRequestManagedBot(const AValue: ITgKeyboardButtonRequestManagedBot): ITgKeyboardButton;
    function WithRequestContact(AValue: Boolean): ITgKeyboardButton;
    function WithRequestLocation(AValue: Boolean): ITgKeyboardButton;
    function WithRequestPoll(const AValue: ITgKeyboardButtonPollType): ITgKeyboardButton;
    function WithWebApp(const AValue: ITgWebAppInfo): ITgKeyboardButton;
  end;

  TTgKeyboardButtonRequestUsersImpl = class(TTgOutObject, ITgKeyboardButtonRequestUsers)
  public
    function WithRequestId(AValue: Int64): ITgKeyboardButtonRequestUsers;
    function WithUserIsBot(AValue: Boolean): ITgKeyboardButtonRequestUsers;
    function WithUserIsPremium(AValue: Boolean): ITgKeyboardButtonRequestUsers;
    function WithMaxQuantity(AValue: Integer): ITgKeyboardButtonRequestUsers;
    function WithRequestName(AValue: Boolean): ITgKeyboardButtonRequestUsers;
    function WithRequestUsername(AValue: Boolean): ITgKeyboardButtonRequestUsers;
    function WithRequestPhoto(AValue: Boolean): ITgKeyboardButtonRequestUsers;
  end;

  TTgKeyboardButtonRequestChatImpl = class(TTgOutObject, ITgKeyboardButtonRequestChat)
  public
    function WithRequestId(AValue: Int64): ITgKeyboardButtonRequestChat;
    function WithChatIsChannel(AValue: Boolean): ITgKeyboardButtonRequestChat;
    function WithChatIsForum(AValue: Boolean): ITgKeyboardButtonRequestChat;
    function WithChatHasUsername(AValue: Boolean): ITgKeyboardButtonRequestChat;
    function WithChatIsCreated(AValue: Boolean): ITgKeyboardButtonRequestChat;
    function WithUserAdministratorRights(const AValue: ITgChatAdministratorRights): ITgKeyboardButtonRequestChat;
    function WithBotAdministratorRights(const AValue: ITgChatAdministratorRights): ITgKeyboardButtonRequestChat;
    function WithBotIsMember(AValue: Boolean): ITgKeyboardButtonRequestChat;
    function WithRequestTitle(AValue: Boolean): ITgKeyboardButtonRequestChat;
    function WithRequestUsername(AValue: Boolean): ITgKeyboardButtonRequestChat;
    function WithRequestPhoto(AValue: Boolean): ITgKeyboardButtonRequestChat;
  end;

  TTgKeyboardButtonRequestManagedBotImpl = class(TTgOutObject, ITgKeyboardButtonRequestManagedBot)
  public
    function WithRequestId(AValue: Int64): ITgKeyboardButtonRequestManagedBot;
    function WithSuggestedName(const AValue: string): ITgKeyboardButtonRequestManagedBot;
    function WithSuggestedUsername(const AValue: string): ITgKeyboardButtonRequestManagedBot;
  end;

  TTgKeyboardButtonPollTypeImpl = class(TTgOutObject, ITgKeyboardButtonPollType)
  public
    function WithKeyboardButtonPollTypeType(const AValue: string): ITgKeyboardButtonPollType;
  end;

  TTgReplyKeyboardRemoveImpl = class(TTgOutObject, ITgReplyKeyboardRemove)
  public
    function WithSelective(AValue: Boolean): ITgReplyKeyboardRemove;
  end;

  TTgInlineKeyboardMarkupImpl = class(TTgJsonDto, ITgInlineKeyboardMarkup)
  public
    function GetInlineKeyboard: TArray<TArray<ITgInlineKeyboardButton>>;
    function GetForceReply: Boolean;
    function GetHasForceReply: Boolean;
    function WithInlineKeyboard(const AValue: array of TArray<ITgInlineKeyboardButton>): ITgInlineKeyboardMarkup;
    function WithInlineKeyboardRow(const ARow: array of ITgInlineKeyboardButton): ITgInlineKeyboardMarkup;
    function WithForceReply(AValue: Boolean): ITgInlineKeyboardMarkup;
  end;

  TTgInlineKeyboardButtonImpl = class(TTgJsonDto, ITgInlineKeyboardButton)
  public
    function GetText: string;
    function GetIconCustomEmojiId: string;
    function GetStyle: string;
    function GetUrl: string;
    function GetCallbackData: string;
    function GetWebApp: ITgWebAppInfo;
    function GetLoginUrl: ITgLoginUrl;
    function GetSwitchInlineQuery: string;
    function GetSwitchInlineQueryCurrentChat: string;
    function GetSwitchInlineQueryChosenChat: ITgSwitchInlineQueryChosenChat;
    function GetCopyText: ITgCopyTextButton;
    function GetCallbackGame: ITgCallbackGame;
    function GetPay: Boolean;
    function GetHasPay: Boolean;
    function GetDisabled: ITgDisabledButton;
    function WithText(const AValue: string): ITgInlineKeyboardButton;
    function WithIconCustomEmojiId(const AValue: string): ITgInlineKeyboardButton;
    function WithStyle(const AValue: string): ITgInlineKeyboardButton;
    function WithUrl(const AValue: string): ITgInlineKeyboardButton;
    function WithCallbackData(const AValue: string): ITgInlineKeyboardButton;
    function WithWebApp(const AValue: ITgWebAppInfo): ITgInlineKeyboardButton;
    function WithLoginUrl(const AValue: ITgLoginUrl): ITgInlineKeyboardButton;
    function WithSwitchInlineQuery(const AValue: string): ITgInlineKeyboardButton;
    function WithSwitchInlineQueryCurrentChat(const AValue: string): ITgInlineKeyboardButton;
    function WithSwitchInlineQueryChosenChat(const AValue: ITgSwitchInlineQueryChosenChat): ITgInlineKeyboardButton;
    function WithCopyText(const AValue: ITgCopyTextButton): ITgInlineKeyboardButton;
    function WithCallbackGame(const AValue: ITgCallbackGame): ITgInlineKeyboardButton;
    function WithPay(AValue: Boolean): ITgInlineKeyboardButton;
    function WithDisabled(const AValue: ITgDisabledButton): ITgInlineKeyboardButton;
  end;

  TTgLoginUrlImpl = class(TTgJsonDto, ITgLoginUrl)
  public
    function GetUrl: string;
    function GetForwardText: string;
    function GetBotUsername: string;
    function GetRequestWriteAccess: Boolean;
    function GetHasRequestWriteAccess: Boolean;
    function WithUrl(const AValue: string): ITgLoginUrl;
    function WithForwardText(const AValue: string): ITgLoginUrl;
    function WithBotUsername(const AValue: string): ITgLoginUrl;
    function WithRequestWriteAccess(AValue: Boolean): ITgLoginUrl;
  end;

  TTgSwitchInlineQueryChosenChatImpl = class(TTgJsonDto, ITgSwitchInlineQueryChosenChat)
  public
    function GetQuery: string;
    function GetAllowUserChats: Boolean;
    function GetHasAllowUserChats: Boolean;
    function GetAllowBotChats: Boolean;
    function GetHasAllowBotChats: Boolean;
    function GetAllowGroupChats: Boolean;
    function GetHasAllowGroupChats: Boolean;
    function GetAllowChannelChats: Boolean;
    function GetHasAllowChannelChats: Boolean;
    function WithQuery(const AValue: string): ITgSwitchInlineQueryChosenChat;
    function WithAllowUserChats(AValue: Boolean): ITgSwitchInlineQueryChosenChat;
    function WithAllowBotChats(AValue: Boolean): ITgSwitchInlineQueryChosenChat;
    function WithAllowGroupChats(AValue: Boolean): ITgSwitchInlineQueryChosenChat;
    function WithAllowChannelChats(AValue: Boolean): ITgSwitchInlineQueryChosenChat;
  end;

  TTgCopyTextButtonImpl = class(TTgJsonDto, ITgCopyTextButton)
  public
    function GetText: string;
    function WithText(const AValue: string): ITgCopyTextButton;
  end;

  TTgDisabledButtonImpl = class(TTgJsonDto, ITgDisabledButton)
  public
  end;

  TTgCallbackQueryImpl = class(TTgJsonDto, ITgCallbackQuery)
  public
    function GetId: string;
    function GetFrom: ITgUser;
    function GetMessage: ITgMaybeInaccessibleMessage;
    function GetInlineMessageId: string;
    function GetChatInstance: string;
    function GetData: string;
    function GetGameShortName: string;
  end;

  TTgForceReplyImpl = class(TTgOutObject, ITgForceReply)
  public
    function WithInputFieldPlaceholder(const AValue: string): ITgForceReply;
    function WithSelective(AValue: Boolean): ITgForceReply;
  end;

  TTgCommunityImpl = class(TTgJsonDto, ITgCommunity)
  public
    function GetId: Int64;
    function GetName: string;
  end;

  TTgChatPhotoImpl = class(TTgJsonDto, ITgChatPhoto)
  public
    function GetSmallFileId: string;
    function GetSmallFileUniqueId: string;
    function GetBigFileId: string;
    function GetBigFileUniqueId: string;
  end;

  TTgChatInviteLinkImpl = class(TTgJsonDto, ITgChatInviteLink)
  public
    function GetInviteLink: string;
    function GetCreator: ITgUser;
    function GetCreatesJoinRequest: Boolean;
    function GetIsPrimary: Boolean;
    function GetIsRevoked: Boolean;
    function GetName: string;
    function GetExpireDate: Int64;
    function GetHasExpireDate: Boolean;
    function GetMemberLimit: Integer;
    function GetHasMemberLimit: Boolean;
    function GetPendingJoinRequestCount: Integer;
    function GetHasPendingJoinRequestCount: Boolean;
    function GetSubscriptionPeriod: Integer;
    function GetHasSubscriptionPeriod: Boolean;
    function GetSubscriptionPrice: Integer;
    function GetHasSubscriptionPrice: Boolean;
  end;

  TTgChatAdministratorRightsImpl = class(TTgJsonDto, ITgChatAdministratorRights)
  public
    function GetIsAnonymous: Boolean;
    function GetCanManageChat: Boolean;
    function GetCanDeleteMessages: Boolean;
    function GetCanManageVideoChats: Boolean;
    function GetCanRestrictMembers: Boolean;
    function GetCanPromoteMembers: Boolean;
    function GetCanChangeInfo: Boolean;
    function GetCanInviteUsers: Boolean;
    function GetCanPostStories: Boolean;
    function GetCanEditStories: Boolean;
    function GetCanDeleteStories: Boolean;
    function GetCanPostMessages: Boolean;
    function GetHasCanPostMessages: Boolean;
    function GetCanEditMessages: Boolean;
    function GetHasCanEditMessages: Boolean;
    function GetCanPinMessages: Boolean;
    function GetHasCanPinMessages: Boolean;
    function GetCanManageTopics: Boolean;
    function GetHasCanManageTopics: Boolean;
    function GetCanManageDirectMessages: Boolean;
    function GetHasCanManageDirectMessages: Boolean;
    function GetCanManageTags: Boolean;
    function GetHasCanManageTags: Boolean;
    function GetCanSendWelcomeMessages: Boolean;
    function WithIsAnonymous(AValue: Boolean): ITgChatAdministratorRights;
    function WithCanManageChat(AValue: Boolean): ITgChatAdministratorRights;
    function WithCanDeleteMessages(AValue: Boolean): ITgChatAdministratorRights;
    function WithCanManageVideoChats(AValue: Boolean): ITgChatAdministratorRights;
    function WithCanRestrictMembers(AValue: Boolean): ITgChatAdministratorRights;
    function WithCanPromoteMembers(AValue: Boolean): ITgChatAdministratorRights;
    function WithCanChangeInfo(AValue: Boolean): ITgChatAdministratorRights;
    function WithCanInviteUsers(AValue: Boolean): ITgChatAdministratorRights;
    function WithCanPostStories(AValue: Boolean): ITgChatAdministratorRights;
    function WithCanEditStories(AValue: Boolean): ITgChatAdministratorRights;
    function WithCanDeleteStories(AValue: Boolean): ITgChatAdministratorRights;
    function WithCanPostMessages(AValue: Boolean): ITgChatAdministratorRights;
    function WithCanEditMessages(AValue: Boolean): ITgChatAdministratorRights;
    function WithCanPinMessages(AValue: Boolean): ITgChatAdministratorRights;
    function WithCanManageTopics(AValue: Boolean): ITgChatAdministratorRights;
    function WithCanManageDirectMessages(AValue: Boolean): ITgChatAdministratorRights;
    function WithCanManageTags(AValue: Boolean): ITgChatAdministratorRights;
    function WithCanSendWelcomeMessages(AValue: Boolean): ITgChatAdministratorRights;
  end;

  TTgChatMemberUpdatedImpl = class(TTgJsonDto, ITgChatMemberUpdated)
  public
    function GetChat: ITgChat;
    function GetFrom: ITgUser;
    function GetDate: Int64;
    function GetOldChatMember: ITgChatMember;
    function GetNewChatMember: ITgChatMember;
    function GetInviteLink: ITgChatInviteLink;
    function GetViaJoinRequest: Boolean;
    function GetHasViaJoinRequest: Boolean;
    function GetViaChatFolderInviteLink: Boolean;
    function GetHasViaChatFolderInviteLink: Boolean;
  end;

  TTgChatMemberImpl = class(TTgJsonDto, ITgChatMember)
  public
    function GetKind: TTgChatMemberKind; virtual;
    function GetKindText: string;
    function GetStatus: string;
    function GetUser: ITgUser;
    function AsOwner: ITgChatMemberOwner;
    function AsAdministrator: ITgChatMemberAdministrator;
    function AsMember: ITgChatMemberMember;
    function AsRestricted: ITgChatMemberRestricted;
    function AsLeft: ITgChatMemberLeft;
    function AsBanned: ITgChatMemberBanned;
  end;

  TTgChatMemberOwnerImpl = class(TTgChatMemberImpl, ITgChatMemberOwner, ITgChatMember)
  public
    function GetKind: TTgChatMemberKind; override;
    function GetIsAnonymous: Boolean;
    function GetCustomTitle: string;
  end;

  TTgChatMemberAdministratorImpl = class(TTgChatMemberImpl, ITgChatMemberAdministrator, ITgChatMember)
  public
    function GetKind: TTgChatMemberKind; override;
    function GetCanBeEdited: Boolean;
    function GetIsAnonymous: Boolean;
    function GetCanManageChat: Boolean;
    function GetCanDeleteMessages: Boolean;
    function GetCanManageVideoChats: Boolean;
    function GetCanRestrictMembers: Boolean;
    function GetCanPromoteMembers: Boolean;
    function GetCanChangeInfo: Boolean;
    function GetCanInviteUsers: Boolean;
    function GetCanPostStories: Boolean;
    function GetCanEditStories: Boolean;
    function GetCanDeleteStories: Boolean;
    function GetCanPostMessages: Boolean;
    function GetHasCanPostMessages: Boolean;
    function GetCanEditMessages: Boolean;
    function GetHasCanEditMessages: Boolean;
    function GetCanPinMessages: Boolean;
    function GetHasCanPinMessages: Boolean;
    function GetCanManageTopics: Boolean;
    function GetHasCanManageTopics: Boolean;
    function GetCanManageDirectMessages: Boolean;
    function GetHasCanManageDirectMessages: Boolean;
    function GetCanManageTags: Boolean;
    function GetHasCanManageTags: Boolean;
    function GetCanSendWelcomeMessages: Boolean;
    function GetCustomTitle: string;
  end;

  TTgChatMemberMemberImpl = class(TTgChatMemberImpl, ITgChatMemberMember, ITgChatMember)
  public
    function GetKind: TTgChatMemberKind; override;
    function GetTag: string;
    function GetUntilDate: Int64;
    function GetHasUntilDate: Boolean;
  end;

  TTgChatMemberRestrictedImpl = class(TTgChatMemberImpl, ITgChatMemberRestricted, ITgChatMember)
  public
    function GetKind: TTgChatMemberKind; override;
    function GetTag: string;
    function GetIsMember: Boolean;
    function GetCanSendMessages: Boolean;
    function GetCanSendAudios: Boolean;
    function GetCanSendDocuments: Boolean;
    function GetCanSendPhotos: Boolean;
    function GetCanSendVideos: Boolean;
    function GetCanSendVideoNotes: Boolean;
    function GetCanSendVoiceNotes: Boolean;
    function GetCanSendPolls: Boolean;
    function GetCanSendOtherMessages: Boolean;
    function GetCanAddWebPagePreviews: Boolean;
    function GetCanReactToMessages: Boolean;
    function GetCanEditTag: Boolean;
    function GetCanChangeInfo: Boolean;
    function GetCanInviteUsers: Boolean;
    function GetCanPinMessages: Boolean;
    function GetCanManageTopics: Boolean;
    function GetUntilDate: Int64;
  end;

  TTgChatMemberLeftImpl = class(TTgChatMemberImpl, ITgChatMemberLeft, ITgChatMember)
  public
    function GetKind: TTgChatMemberKind; override;
  end;

  TTgChatMemberBannedImpl = class(TTgChatMemberImpl, ITgChatMemberBanned, ITgChatMember)
  public
    function GetKind: TTgChatMemberKind; override;
    function GetUntilDate: Int64;
  end;

  TTgChatJoinRequestImpl = class(TTgJsonDto, ITgChatJoinRequest)
  public
    function GetChat: ITgChat;
    function GetFrom: ITgUser;
    function GetUserChatId: Int64;
    function GetDate: Int64;
    function GetBio: string;
    function GetInviteLink: ITgChatInviteLink;
    function GetQueryId: string;
  end;

  TTgChatPermissionsImpl = class(TTgJsonDto, ITgChatPermissions)
  public
    function GetCanSendMessages: Boolean;
    function GetHasCanSendMessages: Boolean;
    function GetCanSendAudios: Boolean;
    function GetHasCanSendAudios: Boolean;
    function GetCanSendDocuments: Boolean;
    function GetHasCanSendDocuments: Boolean;
    function GetCanSendPhotos: Boolean;
    function GetHasCanSendPhotos: Boolean;
    function GetCanSendVideos: Boolean;
    function GetHasCanSendVideos: Boolean;
    function GetCanSendVideoNotes: Boolean;
    function GetHasCanSendVideoNotes: Boolean;
    function GetCanSendVoiceNotes: Boolean;
    function GetHasCanSendVoiceNotes: Boolean;
    function GetCanSendPolls: Boolean;
    function GetHasCanSendPolls: Boolean;
    function GetCanSendOtherMessages: Boolean;
    function GetHasCanSendOtherMessages: Boolean;
    function GetCanAddWebPagePreviews: Boolean;
    function GetHasCanAddWebPagePreviews: Boolean;
    function GetCanReactToMessages: Boolean;
    function GetHasCanReactToMessages: Boolean;
    function GetCanEditTag: Boolean;
    function GetHasCanEditTag: Boolean;
    function GetCanChangeInfo: Boolean;
    function GetHasCanChangeInfo: Boolean;
    function GetCanInviteUsers: Boolean;
    function GetHasCanInviteUsers: Boolean;
    function GetCanPinMessages: Boolean;
    function GetHasCanPinMessages: Boolean;
    function GetCanManageTopics: Boolean;
    function GetHasCanManageTopics: Boolean;
    function WithCanSendMessages(AValue: Boolean): ITgChatPermissions;
    function WithCanSendAudios(AValue: Boolean): ITgChatPermissions;
    function WithCanSendDocuments(AValue: Boolean): ITgChatPermissions;
    function WithCanSendPhotos(AValue: Boolean): ITgChatPermissions;
    function WithCanSendVideos(AValue: Boolean): ITgChatPermissions;
    function WithCanSendVideoNotes(AValue: Boolean): ITgChatPermissions;
    function WithCanSendVoiceNotes(AValue: Boolean): ITgChatPermissions;
    function WithCanSendPolls(AValue: Boolean): ITgChatPermissions;
    function WithCanSendOtherMessages(AValue: Boolean): ITgChatPermissions;
    function WithCanAddWebPagePreviews(AValue: Boolean): ITgChatPermissions;
    function WithCanReactToMessages(AValue: Boolean): ITgChatPermissions;
    function WithCanEditTag(AValue: Boolean): ITgChatPermissions;
    function WithCanChangeInfo(AValue: Boolean): ITgChatPermissions;
    function WithCanInviteUsers(AValue: Boolean): ITgChatPermissions;
    function WithCanPinMessages(AValue: Boolean): ITgChatPermissions;
    function WithCanManageTopics(AValue: Boolean): ITgChatPermissions;
  end;

  TTgBirthdateImpl = class(TTgJsonDto, ITgBirthdate)
  public
    function GetDay: Integer;
    function GetMonth: Integer;
    function GetYear: Integer;
    function GetHasYear: Boolean;
  end;

  TTgBusinessIntroImpl = class(TTgJsonDto, ITgBusinessIntro)
  public
    function GetTitle: string;
    function GetMessage: string;
    function GetSticker: ITgSticker;
  end;

  TTgBusinessLocationImpl = class(TTgJsonDto, ITgBusinessLocation)
  public
    function GetAddress: string;
    function GetLocation: ITgLocation;
  end;

  TTgBusinessOpeningHoursIntervalImpl = class(TTgJsonDto, ITgBusinessOpeningHoursInterval)
  public
    function GetOpeningMinute: Integer;
    function GetClosingMinute: Integer;
  end;

  TTgBusinessOpeningHoursImpl = class(TTgJsonDto, ITgBusinessOpeningHours)
  public
    function GetTimeZoneName: string;
    function GetOpeningHours: TArray<ITgBusinessOpeningHoursInterval>;
  end;

  TTgUserRatingImpl = class(TTgJsonDto, ITgUserRating)
  public
    function GetLevel: Integer;
    function GetRating: Integer;
    function GetCurrentLevelRating: Integer;
    function GetNextLevelRating: Integer;
    function GetHasNextLevelRating: Boolean;
  end;

  TTgStoryAreaPositionImpl = class(TTgOutObject, ITgStoryAreaPosition)
  public
    function WithXPercentage(AValue: Double): ITgStoryAreaPosition;
    function WithYPercentage(AValue: Double): ITgStoryAreaPosition;
    function WithWidthPercentage(AValue: Double): ITgStoryAreaPosition;
    function WithHeightPercentage(AValue: Double): ITgStoryAreaPosition;
    function WithRotationAngle(AValue: Double): ITgStoryAreaPosition;
    function WithCornerRadiusPercentage(AValue: Double): ITgStoryAreaPosition;
  end;

  TTgLocationAddressImpl = class(TTgOutObject, ITgLocationAddress)
  public
    function WithCountryCode(const AValue: string): ITgLocationAddress;
    function WithState(const AValue: string): ITgLocationAddress;
    function WithCity(const AValue: string): ITgLocationAddress;
    function WithStreet(const AValue: string): ITgLocationAddress;
  end;

  TTgStoryAreaTypeLocationImpl = class(TTgOutObject, ITgStoryAreaTypeLocation)
  public
    function WithLatitude(AValue: Double): ITgStoryAreaTypeLocation;
    function WithLongitude(AValue: Double): ITgStoryAreaTypeLocation;
    function WithAddress(const AValue: ITgLocationAddress): ITgStoryAreaTypeLocation;
  end;

  TTgStoryAreaTypeSuggestedReactionImpl = class(TTgOutObject, ITgStoryAreaTypeSuggestedReaction)
  public
    function WithReactionType(const AValue: ITgReactionType): ITgStoryAreaTypeSuggestedReaction;
    function WithIsDark(AValue: Boolean): ITgStoryAreaTypeSuggestedReaction;
    function WithIsFlipped(AValue: Boolean): ITgStoryAreaTypeSuggestedReaction;
  end;

  TTgStoryAreaTypeLinkImpl = class(TTgOutObject, ITgStoryAreaTypeLink)
  public
    function WithUrl(const AValue: string): ITgStoryAreaTypeLink;
  end;

  TTgStoryAreaTypeWeatherImpl = class(TTgOutObject, ITgStoryAreaTypeWeather)
  public
    function WithTemperature(AValue: Double): ITgStoryAreaTypeWeather;
    function WithEmoji(const AValue: string): ITgStoryAreaTypeWeather;
    function WithBackgroundColor(AValue: Integer): ITgStoryAreaTypeWeather;
  end;

  TTgStoryAreaTypeUniqueGiftImpl = class(TTgOutObject, ITgStoryAreaTypeUniqueGift)
  public
    function WithName(const AValue: string): ITgStoryAreaTypeUniqueGift;
  end;

  TTgStoryAreaImpl = class(TTgOutObject, ITgStoryArea)
  public
    function WithPosition(const AValue: ITgStoryAreaPosition): ITgStoryArea;
    function WithStoryAreaType(const AValue: TTgStoryAreaType): ITgStoryArea;
  end;

  TTgChatLocationImpl = class(TTgJsonDto, ITgChatLocation)
  public
    function GetLocation: ITgLocation;
    function GetAddress: string;
  end;

  TTgReactionTypeImpl = class(TTgJsonDto, ITgReactionType)
  public
    function GetKind: TTgReactionTypeKind; virtual;
    function GetKindText: string;
    function AsEmoji: ITgReactionTypeEmoji;
    function AsCustomEmoji: ITgReactionTypeCustomEmoji;
    function AsPaid: ITgReactionTypePaid;
  end;

  TTgReactionTypeEmojiImpl = class(TTgReactionTypeImpl, ITgReactionTypeEmoji, ITgReactionType)
  public
    function GetKind: TTgReactionTypeKind; override;
    function GetEmoji: string;
    function WithEmoji(const AValue: string): ITgReactionTypeEmoji;
  end;

  TTgReactionTypeCustomEmojiImpl = class(TTgReactionTypeImpl, ITgReactionTypeCustomEmoji, ITgReactionType)
  public
    function GetKind: TTgReactionTypeKind; override;
    function GetCustomEmojiId: string;
    function WithCustomEmojiId(const AValue: string): ITgReactionTypeCustomEmoji;
  end;

  TTgReactionTypePaidImpl = class(TTgReactionTypeImpl, ITgReactionTypePaid, ITgReactionType)
  public
    function GetKind: TTgReactionTypeKind; override;
  end;

  TTgReactionCountImpl = class(TTgJsonDto, ITgReactionCount)
  public
    function GetReactionCountType: ITgReactionType;
    function GetTotalCount: Integer;
  end;

  TTgMessageReactionUpdatedImpl = class(TTgJsonDto, ITgMessageReactionUpdated)
  public
    function GetChat: ITgChat;
    function GetMessageId: Int64;
    function GetUser: ITgUser;
    function GetActorChat: ITgChat;
    function GetDate: Int64;
    function GetOldReaction: TArray<ITgReactionType>;
    function GetNewReaction: TArray<ITgReactionType>;
  end;

  TTgMessageReactionCountUpdatedImpl = class(TTgJsonDto, ITgMessageReactionCountUpdated)
  public
    function GetChat: ITgChat;
    function GetMessageId: Int64;
    function GetDate: Int64;
    function GetReactions: TArray<ITgReactionCount>;
  end;

  TTgForumTopicImpl = class(TTgJsonDto, ITgForumTopic)
  public
    function GetMessageThreadId: Int64;
    function GetName: string;
    function GetIconColor: Integer;
    function GetIconCustomEmojiId: string;
    function GetIsNameImplicit: Boolean;
  end;

  TTgGiftBackgroundImpl = class(TTgJsonDto, ITgGiftBackground)
  public
    function GetCenterColor: Integer;
    function GetEdgeColor: Integer;
    function GetTextColor: Integer;
  end;

  TTgGiftImpl = class(TTgJsonDto, ITgGift)
  public
    function GetId: string;
    function GetSticker: ITgSticker;
    function GetStarCount: Integer;
    function GetUpgradeStarCount: Integer;
    function GetHasUpgradeStarCount: Boolean;
    function GetIsPremium: Boolean;
    function GetHasColors: Boolean;
    function GetTotalCount: Integer;
    function GetHasTotalCount: Boolean;
    function GetRemainingCount: Integer;
    function GetHasRemainingCount: Boolean;
    function GetPersonalTotalCount: Integer;
    function GetHasPersonalTotalCount: Boolean;
    function GetPersonalRemainingCount: Integer;
    function GetHasPersonalRemainingCount: Boolean;
    function GetBackground: ITgGiftBackground;
    function GetUniqueGiftVariantCount: Integer;
    function GetHasUniqueGiftVariantCount: Boolean;
    function GetPublisherChat: ITgChat;
  end;

  TTgGiftsImpl = class(TTgJsonDto, ITgGifts)
  public
    function GetGifts: TArray<ITgGift>;
  end;

  TTgUniqueGiftModelImpl = class(TTgJsonDto, ITgUniqueGiftModel)
  public
    function GetName: string;
    function GetSticker: ITgSticker;
    function GetRarityPerMille: Integer;
    function GetRarity: string;
  end;

  TTgUniqueGiftSymbolImpl = class(TTgJsonDto, ITgUniqueGiftSymbol)
  public
    function GetName: string;
    function GetSticker: ITgSticker;
    function GetRarityPerMille: Integer;
  end;

  TTgUniqueGiftBackdropColorsImpl = class(TTgJsonDto, ITgUniqueGiftBackdropColors)
  public
    function GetCenterColor: Integer;
    function GetEdgeColor: Integer;
    function GetSymbolColor: Integer;
    function GetTextColor: Integer;
  end;

  TTgUniqueGiftBackdropImpl = class(TTgJsonDto, ITgUniqueGiftBackdrop)
  public
    function GetName: string;
    function GetColors: ITgUniqueGiftBackdropColors;
    function GetRarityPerMille: Integer;
  end;

  TTgUniqueGiftColorsImpl = class(TTgJsonDto, ITgUniqueGiftColors)
  public
    function GetModelCustomEmojiId: string;
    function GetSymbolCustomEmojiId: string;
    function GetLightThemeMainColor: Integer;
    function GetLightThemeOtherColors: TArray<Integer>;
    function GetDarkThemeMainColor: Integer;
    function GetDarkThemeOtherColors: TArray<Integer>;
  end;

  TTgUniqueGiftImpl = class(TTgJsonDto, ITgUniqueGift)
  public
    function GetGiftId: string;
    function GetBaseName: string;
    function GetName: string;
    function GetNumber: Integer;
    function GetModel: ITgUniqueGiftModel;
    function GetSymbol: ITgUniqueGiftSymbol;
    function GetBackdrop: ITgUniqueGiftBackdrop;
    function GetIsPremium: Boolean;
    function GetIsBurned: Boolean;
    function GetIsFromBlockchain: Boolean;
    function GetColors: ITgUniqueGiftColors;
    function GetPublisherChat: ITgChat;
  end;

  TTgGiftInfoImpl = class(TTgJsonDto, ITgGiftInfo)
  public
    function GetGift: ITgGift;
    function GetOwnedGiftId: string;
    function GetConvertStarCount: Integer;
    function GetHasConvertStarCount: Boolean;
    function GetPrepaidUpgradeStarCount: Integer;
    function GetHasPrepaidUpgradeStarCount: Boolean;
    function GetIsUpgradeSeparate: Boolean;
    function GetCanBeUpgraded: Boolean;
    function GetText: string;
    function GetEntities: TArray<ITgMessageEntity>;
    function GetIsPrivate: Boolean;
    function GetUniqueGiftNumber: Integer;
    function GetHasUniqueGiftNumber: Boolean;
  end;

  TTgUniqueGiftInfoImpl = class(TTgJsonDto, ITgUniqueGiftInfo)
  public
    function GetGift: ITgUniqueGift;
    function GetOrigin: string;
    function GetText: string;
    function GetEntities: TArray<ITgMessageEntity>;
    function GetIsPrivate: Boolean;
    function GetLastResaleCurrency: string;
    function GetLastResaleAmount: Integer;
    function GetHasLastResaleAmount: Boolean;
    function GetOwnedGiftId: string;
    function GetTransferStarCount: Integer;
    function GetHasTransferStarCount: Boolean;
    function GetNextTransferDate: Int64;
    function GetHasNextTransferDate: Boolean;
  end;

  TTgOwnedGiftImpl = class(TTgJsonDto, ITgOwnedGift)
  public
    function GetKind: TTgOwnedGiftKind; virtual;
    function GetKindText: string;
    function GetOwnedGiftId: string;
    function GetSenderUser: ITgUser;
    function GetSendDate: Int64;
    function GetIsSaved: Boolean;
    function AsRegular: ITgOwnedGiftRegular;
    function AsUnique: ITgOwnedGiftUnique;
  end;

  TTgOwnedGiftRegularImpl = class(TTgOwnedGiftImpl, ITgOwnedGiftRegular, ITgOwnedGift)
  public
    function GetKind: TTgOwnedGiftKind; override;
    function GetGift: ITgGift;
    function GetText: string;
    function GetEntities: TArray<ITgMessageEntity>;
    function GetIsPrivate: Boolean;
    function GetCanBeUpgraded: Boolean;
    function GetWasRefunded: Boolean;
    function GetConvertStarCount: Integer;
    function GetHasConvertStarCount: Boolean;
    function GetPrepaidUpgradeStarCount: Integer;
    function GetHasPrepaidUpgradeStarCount: Boolean;
    function GetIsUpgradeSeparate: Boolean;
    function GetUniqueGiftNumber: Integer;
    function GetHasUniqueGiftNumber: Boolean;
  end;

  TTgOwnedGiftUniqueImpl = class(TTgOwnedGiftImpl, ITgOwnedGiftUnique, ITgOwnedGift)
  public
    function GetKind: TTgOwnedGiftKind; override;
    function GetGift: ITgUniqueGift;
    function GetCanBeTransferred: Boolean;
    function GetTransferStarCount: Integer;
    function GetHasTransferStarCount: Boolean;
    function GetNextTransferDate: Int64;
    function GetHasNextTransferDate: Boolean;
  end;

  TTgOwnedGiftsImpl = class(TTgJsonDto, ITgOwnedGifts)
  public
    function GetTotalCount: Integer;
    function GetGifts: TArray<ITgOwnedGift>;
    function GetNextOffset: string;
  end;

  TTgBotAccessSettingsImpl = class(TTgJsonDto, ITgBotAccessSettings)
  public
    function GetIsAccessRestricted: Boolean;
    function GetAddedUsers: TArray<ITgUser>;
  end;

  TTgAcceptedGiftTypesImpl = class(TTgJsonDto, ITgAcceptedGiftTypes)
  public
    function GetUnlimitedGifts: Boolean;
    function GetLimitedGifts: Boolean;
    function GetUniqueGifts: Boolean;
    function GetPremiumSubscription: Boolean;
    function GetGiftsFromChannels: Boolean;
    function WithUnlimitedGifts(AValue: Boolean): ITgAcceptedGiftTypes;
    function WithLimitedGifts(AValue: Boolean): ITgAcceptedGiftTypes;
    function WithUniqueGifts(AValue: Boolean): ITgAcceptedGiftTypes;
    function WithPremiumSubscription(AValue: Boolean): ITgAcceptedGiftTypes;
    function WithGiftsFromChannels(AValue: Boolean): ITgAcceptedGiftTypes;
  end;

  TTgStarAmountImpl = class(TTgJsonDto, ITgStarAmount)
  public
    function GetAmount: Integer;
    function GetNanostarAmount: Integer;
    function GetHasNanostarAmount: Boolean;
  end;

  TTgBotCommandImpl = class(TTgJsonDto, ITgBotCommand)
  public
    function GetCommand: string;
    function GetDescription: string;
    function GetIsEphemeral: Boolean;
    function GetHasIsEphemeral: Boolean;
    function WithCommand(const AValue: string): ITgBotCommand;
    function WithDescription(const AValue: string): ITgBotCommand;
    function WithIsEphemeral(AValue: Boolean): ITgBotCommand;
  end;

  TTgBotCommandScopeDefaultImpl = class(TTgOutObject, ITgBotCommandScopeDefault)
  public
  end;

  TTgBotCommandScopeAllPrivateChatsImpl = class(TTgOutObject, ITgBotCommandScopeAllPrivateChats)
  public
  end;

  TTgBotCommandScopeAllGroupChatsImpl = class(TTgOutObject, ITgBotCommandScopeAllGroupChats)
  public
  end;

  TTgBotCommandScopeAllChatAdministratorsImpl = class(TTgOutObject, ITgBotCommandScopeAllChatAdministrators)
  public
  end;

  TTgBotCommandScopeChatImpl = class(TTgOutObject, ITgBotCommandScopeChat)
  public
    function WithChatId(const AValue: TTgChatId): ITgBotCommandScopeChat;
  end;

  TTgBotCommandScopeChatAdministratorsImpl = class(TTgOutObject, ITgBotCommandScopeChatAdministrators)
  public
    function WithChatId(const AValue: TTgChatId): ITgBotCommandScopeChatAdministrators;
  end;

  TTgBotCommandScopeChatMemberImpl = class(TTgOutObject, ITgBotCommandScopeChatMember)
  public
    function WithChatId(const AValue: TTgChatId): ITgBotCommandScopeChatMember;
    function WithUserId(AValue: Int64): ITgBotCommandScopeChatMember;
  end;

  TTgBotNameImpl = class(TTgJsonDto, ITgBotName)
  public
    function GetName: string;
  end;

  TTgBotDescriptionImpl = class(TTgJsonDto, ITgBotDescription)
  public
    function GetDescription: string;
  end;

  TTgBotShortDescriptionImpl = class(TTgJsonDto, ITgBotShortDescription)
  public
    function GetShortDescription: string;
  end;

  TTgMenuButtonImpl = class(TTgJsonDto, ITgMenuButton)
  public
    function GetKind: TTgMenuButtonKind; virtual;
    function GetKindText: string;
    function AsCommands: ITgMenuButtonCommands;
    function AsWebApp: ITgMenuButtonWebApp;
    function AsDefault: ITgMenuButtonDefault;
  end;

  TTgMenuButtonCommandsImpl = class(TTgMenuButtonImpl, ITgMenuButtonCommands, ITgMenuButton)
  public
    function GetKind: TTgMenuButtonKind; override;
  end;

  TTgMenuButtonWebAppImpl = class(TTgMenuButtonImpl, ITgMenuButtonWebApp, ITgMenuButton)
  public
    function GetKind: TTgMenuButtonKind; override;
    function GetText: string;
    function GetWebApp: ITgWebAppInfo;
    function WithText(const AValue: string): ITgMenuButtonWebApp;
    function WithWebApp(const AValue: ITgWebAppInfo): ITgMenuButtonWebApp;
  end;

  TTgMenuButtonDefaultImpl = class(TTgMenuButtonImpl, ITgMenuButtonDefault, ITgMenuButton)
  public
    function GetKind: TTgMenuButtonKind; override;
  end;

  TTgChatBoostSourceImpl = class(TTgJsonDto, ITgChatBoostSource)
  public
    function GetKind: TTgChatBoostSourceKind; virtual;
    function GetKindText: string;
    function GetSource: string;
    function GetUser: ITgUser;
    function AsPremium: ITgChatBoostSourcePremium;
    function AsGiftCode: ITgChatBoostSourceGiftCode;
    function AsGiveaway: ITgChatBoostSourceGiveaway;
  end;

  TTgChatBoostSourcePremiumImpl = class(TTgChatBoostSourceImpl, ITgChatBoostSourcePremium, ITgChatBoostSource)
  public
    function GetKind: TTgChatBoostSourceKind; override;
  end;

  TTgChatBoostSourceGiftCodeImpl = class(TTgChatBoostSourceImpl, ITgChatBoostSourceGiftCode, ITgChatBoostSource)
  public
    function GetKind: TTgChatBoostSourceKind; override;
  end;

  TTgChatBoostSourceGiveawayImpl = class(TTgChatBoostSourceImpl, ITgChatBoostSourceGiveaway, ITgChatBoostSource)
  public
    function GetKind: TTgChatBoostSourceKind; override;
    function GetGiveawayMessageId: Int64;
    function GetPrizeStarCount: Integer;
    function GetHasPrizeStarCount: Boolean;
    function GetIsUnclaimed: Boolean;
  end;

  TTgChatBoostImpl = class(TTgJsonDto, ITgChatBoost)
  public
    function GetBoostId: string;
    function GetAddDate: Int64;
    function GetExpirationDate: Int64;
    function GetSource: ITgChatBoostSource;
  end;

  TTgChatBoostUpdatedImpl = class(TTgJsonDto, ITgChatBoostUpdated)
  public
    function GetChat: ITgChat;
    function GetBoost: ITgChatBoost;
  end;

  TTgChatBoostRemovedImpl = class(TTgJsonDto, ITgChatBoostRemoved)
  public
    function GetChat: ITgChat;
    function GetBoostId: string;
    function GetRemoveDate: Int64;
    function GetSource: ITgChatBoostSource;
  end;

  TTgChatOwnerLeftImpl = class(TTgJsonDto, ITgChatOwnerLeft)
  public
    function GetNewOwner: ITgUser;
  end;

  TTgChatOwnerChangedImpl = class(TTgJsonDto, ITgChatOwnerChanged)
  public
    function GetNewOwner: ITgUser;
  end;

  TTgUserChatBoostsImpl = class(TTgJsonDto, ITgUserChatBoosts)
  public
    function GetBoosts: TArray<ITgChatBoost>;
  end;

  TTgBusinessBotRightsImpl = class(TTgJsonDto, ITgBusinessBotRights)
  public
    function GetCanReply: Boolean;
    function GetCanReadMessages: Boolean;
    function GetCanDeleteSentMessages: Boolean;
    function GetCanDeleteAllMessages: Boolean;
    function GetCanEditName: Boolean;
    function GetCanEditBio: Boolean;
    function GetCanEditProfilePhoto: Boolean;
    function GetCanEditUsername: Boolean;
    function GetCanChangeGiftSettings: Boolean;
    function GetCanViewGiftsAndStars: Boolean;
    function GetCanConvertGiftsToStars: Boolean;
    function GetCanTransferAndUpgradeGifts: Boolean;
    function GetCanTransferStars: Boolean;
    function GetCanManageStories: Boolean;
  end;

  TTgBusinessConnectionImpl = class(TTgJsonDto, ITgBusinessConnection)
  public
    function GetId: string;
    function GetUser: ITgUser;
    function GetUserChatId: Int64;
    function GetDate: Int64;
    function GetRights: ITgBusinessBotRights;
    function GetIsEnabled: Boolean;
  end;

  TTgBusinessMessagesDeletedImpl = class(TTgJsonDto, ITgBusinessMessagesDeleted)
  public
    function GetBusinessConnectionId: string;
    function GetChat: ITgChat;
    function GetMessageIds: TArray<Int64>;
  end;

  TTgSentWebAppMessageImpl = class(TTgJsonDto, ITgSentWebAppMessage)
  public
    function GetInlineMessageId: string;
  end;

  TTgSentGuestMessageImpl = class(TTgJsonDto, ITgSentGuestMessage)
  public
    function GetInlineMessageId: string;
  end;

  TTgPreparedInlineMessageImpl = class(TTgJsonDto, ITgPreparedInlineMessage)
  public
    function GetId: string;
    function GetExpirationDate: Int64;
  end;

  TTgPreparedKeyboardButtonImpl = class(TTgJsonDto, ITgPreparedKeyboardButton)
  public
    function GetId: string;
  end;

  TTgResponseParametersImpl = class(TTgJsonDto, ITgResponseParameters)
  public
    function GetMigrateToChatId: Int64;
    function GetHasMigrateToChatId: Boolean;
    function GetRetryAfter: Integer;
    function GetHasRetryAfter: Boolean;
  end;

  TTgInputMediaAnimationImpl = class(TTgOutObject, ITgInputMediaAnimation)
  public
    function WithMedia(const AValue: TTgInputFile): ITgInputMediaAnimation;
    function WithThumbnail(const AValue: TTgInputFile): ITgInputMediaAnimation;
    function WithCaption(const AValue: string): ITgInputMediaAnimation;
    function WithParseMode(const AValue: string): ITgInputMediaAnimation;
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInputMediaAnimation;
    function WithShowCaptionAboveMedia(AValue: Boolean): ITgInputMediaAnimation;
    function WithWidth(AValue: Integer): ITgInputMediaAnimation;
    function WithHeight(AValue: Integer): ITgInputMediaAnimation;
    function WithDuration(AValue: Integer): ITgInputMediaAnimation;
    function WithHasSpoiler(AValue: Boolean): ITgInputMediaAnimation;
  end;

  TTgInputMediaAudioImpl = class(TTgOutObject, ITgInputMediaAudio)
  public
    function WithMedia(const AValue: TTgInputFile): ITgInputMediaAudio;
    function WithThumbnail(const AValue: TTgInputFile): ITgInputMediaAudio;
    function WithCaption(const AValue: string): ITgInputMediaAudio;
    function WithParseMode(const AValue: string): ITgInputMediaAudio;
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInputMediaAudio;
    function WithDuration(AValue: Integer): ITgInputMediaAudio;
    function WithPerformer(const AValue: string): ITgInputMediaAudio;
    function WithTitle(const AValue: string): ITgInputMediaAudio;
  end;

  TTgInputMediaDocumentImpl = class(TTgOutObject, ITgInputMediaDocument)
  public
    function WithMedia(const AValue: TTgInputFile): ITgInputMediaDocument;
    function WithThumbnail(const AValue: TTgInputFile): ITgInputMediaDocument;
    function WithCaption(const AValue: string): ITgInputMediaDocument;
    function WithParseMode(const AValue: string): ITgInputMediaDocument;
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInputMediaDocument;
    function WithDisableContentTypeDetection(AValue: Boolean): ITgInputMediaDocument;
  end;

  TTgInputMediaLinkImpl = class(TTgOutObject, ITgInputMediaLink)
  public
    function WithUrl(const AValue: string): ITgInputMediaLink;
  end;

  TTgInputMediaLivePhotoImpl = class(TTgOutObject, ITgInputMediaLivePhoto)
  public
    function WithMedia(const AValue: TTgInputFile): ITgInputMediaLivePhoto;
    function WithPhoto(const AValue: TTgInputFile): ITgInputMediaLivePhoto;
    function WithCaption(const AValue: string): ITgInputMediaLivePhoto;
    function WithParseMode(const AValue: string): ITgInputMediaLivePhoto;
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInputMediaLivePhoto;
    function WithShowCaptionAboveMedia(AValue: Boolean): ITgInputMediaLivePhoto;
    function WithHasSpoiler(AValue: Boolean): ITgInputMediaLivePhoto;
  end;

  TTgInputMediaLocationImpl = class(TTgOutObject, ITgInputMediaLocation)
  public
    function WithLatitude(AValue: Double): ITgInputMediaLocation;
    function WithLongitude(AValue: Double): ITgInputMediaLocation;
    function WithHorizontalAccuracy(AValue: Double): ITgInputMediaLocation;
  end;

  TTgInputMediaPhotoImpl = class(TTgOutObject, ITgInputMediaPhoto)
  public
    function WithMedia(const AValue: TTgInputFile): ITgInputMediaPhoto;
    function WithCaption(const AValue: string): ITgInputMediaPhoto;
    function WithParseMode(const AValue: string): ITgInputMediaPhoto;
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInputMediaPhoto;
    function WithShowCaptionAboveMedia(AValue: Boolean): ITgInputMediaPhoto;
    function WithHasSpoiler(AValue: Boolean): ITgInputMediaPhoto;
  end;

  TTgInputMediaStickerImpl = class(TTgOutObject, ITgInputMediaSticker)
  public
    function WithMedia(const AValue: TTgInputFile): ITgInputMediaSticker;
    function WithEmoji(const AValue: string): ITgInputMediaSticker;
  end;

  TTgInputMediaVenueImpl = class(TTgOutObject, ITgInputMediaVenue)
  public
    function WithLatitude(AValue: Double): ITgInputMediaVenue;
    function WithLongitude(AValue: Double): ITgInputMediaVenue;
    function WithTitle(const AValue: string): ITgInputMediaVenue;
    function WithAddress(const AValue: string): ITgInputMediaVenue;
    function WithFoursquareId(const AValue: string): ITgInputMediaVenue;
    function WithFoursquareType(const AValue: string): ITgInputMediaVenue;
    function WithGooglePlaceId(const AValue: string): ITgInputMediaVenue;
    function WithGooglePlaceType(const AValue: string): ITgInputMediaVenue;
  end;

  TTgInputMediaVideoImpl = class(TTgOutObject, ITgInputMediaVideo)
  public
    function WithMedia(const AValue: TTgInputFile): ITgInputMediaVideo;
    function WithThumbnail(const AValue: TTgInputFile): ITgInputMediaVideo;
    function WithCover(const AValue: TTgInputFile): ITgInputMediaVideo;
    function WithStartTimestamp(AValue: Integer): ITgInputMediaVideo;
    function WithCaption(const AValue: string): ITgInputMediaVideo;
    function WithParseMode(const AValue: string): ITgInputMediaVideo;
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInputMediaVideo;
    function WithShowCaptionAboveMedia(AValue: Boolean): ITgInputMediaVideo;
    function WithWidth(AValue: Integer): ITgInputMediaVideo;
    function WithHeight(AValue: Integer): ITgInputMediaVideo;
    function WithDuration(AValue: Integer): ITgInputMediaVideo;
    function WithSupportsStreaming(AValue: Boolean): ITgInputMediaVideo;
    function WithHasSpoiler(AValue: Boolean): ITgInputMediaVideo;
  end;

  TTgInputMediaVoiceNoteImpl = class(TTgOutObject, ITgInputMediaVoiceNote)
  public
    function WithMedia(const AValue: TTgInputFile): ITgInputMediaVoiceNote;
    function WithCaption(const AValue: string): ITgInputMediaVoiceNote;
    function WithParseMode(const AValue: string): ITgInputMediaVoiceNote;
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInputMediaVoiceNote;
    function WithDuration(AValue: Integer): ITgInputMediaVoiceNote;
  end;

  TTgInputPaidMediaLivePhotoImpl = class(TTgOutObject, ITgInputPaidMediaLivePhoto)
  public
    function WithMedia(const AValue: TTgInputFile): ITgInputPaidMediaLivePhoto;
    function WithPhoto(const AValue: TTgInputFile): ITgInputPaidMediaLivePhoto;
  end;

  TTgInputPaidMediaPhotoImpl = class(TTgOutObject, ITgInputPaidMediaPhoto)
  public
    function WithMedia(const AValue: TTgInputFile): ITgInputPaidMediaPhoto;
  end;

  TTgInputPaidMediaVideoImpl = class(TTgOutObject, ITgInputPaidMediaVideo)
  public
    function WithMedia(const AValue: TTgInputFile): ITgInputPaidMediaVideo;
    function WithThumbnail(const AValue: TTgInputFile): ITgInputPaidMediaVideo;
    function WithCover(const AValue: TTgInputFile): ITgInputPaidMediaVideo;
    function WithStartTimestamp(AValue: Integer): ITgInputPaidMediaVideo;
    function WithWidth(AValue: Integer): ITgInputPaidMediaVideo;
    function WithHeight(AValue: Integer): ITgInputPaidMediaVideo;
    function WithDuration(AValue: Integer): ITgInputPaidMediaVideo;
    function WithSupportsStreaming(AValue: Boolean): ITgInputPaidMediaVideo;
  end;

  TTgInputProfilePhotoStaticImpl = class(TTgOutObject, ITgInputProfilePhotoStatic)
  public
    function WithPhoto(const AValue: TTgInputFile): ITgInputProfilePhotoStatic;
  end;

  TTgInputProfilePhotoAnimatedImpl = class(TTgOutObject, ITgInputProfilePhotoAnimated)
  public
    function WithAnimation(const AValue: TTgInputFile): ITgInputProfilePhotoAnimated;
    function WithMainFrameTimestamp(AValue: Double): ITgInputProfilePhotoAnimated;
  end;

  TTgInputStoryContentPhotoImpl = class(TTgOutObject, ITgInputStoryContentPhoto)
  public
    function WithPhoto(const AValue: TTgInputFile): ITgInputStoryContentPhoto;
  end;

  TTgInputStoryContentVideoImpl = class(TTgOutObject, ITgInputStoryContentVideo)
  public
    function WithVideo(const AValue: TTgInputFile): ITgInputStoryContentVideo;
    function WithDuration(AValue: Double): ITgInputStoryContentVideo;
    function WithCoverFrameTimestamp(AValue: Double): ITgInputStoryContentVideo;
    function WithIsAnimation(AValue: Boolean): ITgInputStoryContentVideo;
  end;

  TTgStickerImpl = class(TTgJsonDto, ITgSticker)
  public
    function GetFileId: string;
    function GetFileUniqueId: string;
    function GetStickerType: string;
    function GetWidth: Integer;
    function GetHeight: Integer;
    function GetIsAnimated: Boolean;
    function GetIsVideo: Boolean;
    function GetThumbnail: ITgPhotoSize;
    function GetEmoji: string;
    function GetSetName: string;
    function GetPremiumAnimation: ITgFile;
    function GetMaskPosition: ITgMaskPosition;
    function GetCustomEmojiId: string;
    function GetNeedsRepainting: Boolean;
    function GetFileSize: Int64;
    function GetHasFileSize: Boolean;
  end;

  TTgStickerSetImpl = class(TTgJsonDto, ITgStickerSet)
  public
    function GetName: string;
    function GetTitle: string;
    function GetStickerType: string;
    function GetStickers: TArray<ITgSticker>;
    function GetThumbnail: ITgPhotoSize;
  end;

  TTgMaskPositionImpl = class(TTgJsonDto, ITgMaskPosition)
  public
    function GetPoint: string;
    function GetXShift: Double;
    function GetYShift: Double;
    function GetScale: Double;
    function WithPoint(const AValue: string): ITgMaskPosition;
    function WithXShift(AValue: Double): ITgMaskPosition;
    function WithYShift(AValue: Double): ITgMaskPosition;
    function WithScale(AValue: Double): ITgMaskPosition;
  end;

  TTgInputStickerImpl = class(TTgOutObject, ITgInputSticker)
  public
    function WithSticker(const AValue: TTgInputFile): ITgInputSticker;
    function WithFormat(const AValue: string): ITgInputSticker;
    function WithEmojiList(const AValue: TArray<string>): ITgInputSticker;
    function WithMaskPosition(const AValue: ITgMaskPosition): ITgInputSticker;
    function WithKeywords(const AValue: TArray<string>): ITgInputSticker;
  end;

  TTgRichMessageImpl = class(TTgJsonDto, ITgRichMessage)
  public
    function GetBlocks: TArray<ITgRichBlock>;
    function GetIsRtl: Boolean;
    function GetHasIsRtl: Boolean;
  end;

  TTgInputRichMessageImpl = class(TTgOutObject, ITgInputRichMessage)
  public
    function WithBlocks(const AValue: array of TTgInputRichBlock): ITgInputRichMessage;
    function WithHtml(const AValue: string): ITgInputRichMessage;
    function WithMarkdown(const AValue: string): ITgInputRichMessage;
    function WithMedia(const AValue: array of ITgInputRichMessageMedia): ITgInputRichMessage;
    function WithIsRtl(AValue: Boolean): ITgInputRichMessage;
    function WithSkipEntityDetection(AValue: Boolean): ITgInputRichMessage;
  end;

  TTgInputRichMessageMediaImpl = class(TTgOutObject, ITgInputRichMessageMedia)
  public
    function WithId(const AValue: string): ITgInputRichMessageMedia;
    function WithMedia(const AValue: TTgInputRichMedia): ITgInputRichMessageMedia;
  end;

  TTgRichMessageButtonImpl = class(TTgJsonDto, ITgRichMessageButton)
  public
    function GetText: ITgRichText;
    function GetStyle: string;
    function GetUrl: string;
    function GetCallbackData: string;
    function GetWebApp: ITgWebAppInfo;
    function GetLoginUrl: ITgLoginUrl;
    function GetSwitchInlineQuery: string;
    function GetSwitchInlineQueryCurrentChat: string;
    function GetSwitchInlineQueryChosenChat: ITgSwitchInlineQueryChosenChat;
    function GetCopyText: ITgCopyTextButton;
    function GetDisabled: ITgDisabledButton;
    function WithText(const AValue: ITgRichText): ITgRichMessageButton;
    function WithStyle(const AValue: string): ITgRichMessageButton;
    function WithUrl(const AValue: string): ITgRichMessageButton;
    function WithCallbackData(const AValue: string): ITgRichMessageButton;
    function WithWebApp(const AValue: ITgWebAppInfo): ITgRichMessageButton;
    function WithLoginUrl(const AValue: ITgLoginUrl): ITgRichMessageButton;
    function WithSwitchInlineQuery(const AValue: string): ITgRichMessageButton;
    function WithSwitchInlineQueryCurrentChat(const AValue: string): ITgRichMessageButton;
    function WithSwitchInlineQueryChosenChat(const AValue: ITgSwitchInlineQueryChosenChat): ITgRichMessageButton;
    function WithCopyText(const AValue: ITgCopyTextButton): ITgRichMessageButton;
    function WithDisabled(const AValue: ITgDisabledButton): ITgRichMessageButton;
  end;

  TTgRichTextImpl = class(TTgJsonDto, ITgRichText)
  public
    function GetKind: TTgRichTextKind; virtual;
    function GetKindText: string;
    function AsBold: ITgRichTextBold;
    function AsItalic: ITgRichTextItalic;
    function AsUnderline: ITgRichTextUnderline;
    function AsStrikethrough: ITgRichTextStrikethrough;
    function AsSpoiler: ITgRichTextSpoiler;
    function AsDateTime: ITgRichTextDateTime;
    function AsTextMention: ITgRichTextTextMention;
    function AsSubscript: ITgRichTextSubscript;
    function AsSuperscript: ITgRichTextSuperscript;
    function AsMarked: ITgRichTextMarked;
    function AsCode: ITgRichTextCode;
    function AsCustomEmoji: ITgRichTextCustomEmoji;
    function AsMathematicalExpression: ITgRichTextMathematicalExpression;
    function AsUrl: ITgRichTextUrl;
    function AsEmailAddress: ITgRichTextEmailAddress;
    function AsPhoneNumber: ITgRichTextPhoneNumber;
    function AsBankCardNumber: ITgRichTextBankCardNumber;
    function AsMention: ITgRichTextMention;
    function AsHashtag: ITgRichTextHashtag;
    function AsCashtag: ITgRichTextCashtag;
    function AsBotCommand: ITgRichTextBotCommand;
    function AsButton: ITgRichTextButton;
    function AsAnchor: ITgRichTextAnchor;
    function AsAnchorLink: ITgRichTextAnchorLink;
    function AsReference: ITgRichTextReference;
    function AsReferenceLink: ITgRichTextReferenceLink;
    function AsPlain: ITgRichTextPlain;
    function AsList: ITgRichTextList;
  end;

  TTgRichTextPlainImpl = class(TTgRichTextImpl, ITgRichTextPlain, ITgRichText)
  public
    function GetKind: TTgRichTextKind; override;
    function GetText: string;
  end;

  TTgRichTextListImpl = class(TTgRichTextImpl, ITgRichTextList, ITgRichText)
  public
    function GetKind: TTgRichTextKind; override;
    function GetItems: TArray<ITgRichText>;
  end;

  TTgRichTextBoldImpl = class(TTgRichTextImpl, ITgRichTextBold, ITgRichText)
  public
    function GetKind: TTgRichTextKind; override;
    function GetText: ITgRichText;
    function WithText(const AValue: ITgRichText): ITgRichTextBold;
  end;

  TTgRichTextItalicImpl = class(TTgRichTextImpl, ITgRichTextItalic, ITgRichText)
  public
    function GetKind: TTgRichTextKind; override;
    function GetText: ITgRichText;
    function WithText(const AValue: ITgRichText): ITgRichTextItalic;
  end;

  TTgRichTextUnderlineImpl = class(TTgRichTextImpl, ITgRichTextUnderline, ITgRichText)
  public
    function GetKind: TTgRichTextKind; override;
    function GetText: ITgRichText;
    function WithText(const AValue: ITgRichText): ITgRichTextUnderline;
  end;

  TTgRichTextStrikethroughImpl = class(TTgRichTextImpl, ITgRichTextStrikethrough, ITgRichText)
  public
    function GetKind: TTgRichTextKind; override;
    function GetText: ITgRichText;
    function WithText(const AValue: ITgRichText): ITgRichTextStrikethrough;
  end;

  TTgRichTextSpoilerImpl = class(TTgRichTextImpl, ITgRichTextSpoiler, ITgRichText)
  public
    function GetKind: TTgRichTextKind; override;
    function GetText: ITgRichText;
    function WithText(const AValue: ITgRichText): ITgRichTextSpoiler;
  end;

  TTgRichTextDateTimeImpl = class(TTgRichTextImpl, ITgRichTextDateTime, ITgRichText)
  public
    function GetKind: TTgRichTextKind; override;
    function GetText: ITgRichText;
    function GetUnixTime: Integer;
    function GetDateTimeFormat: string;
    function WithText(const AValue: ITgRichText): ITgRichTextDateTime;
    function WithUnixTime(AValue: Integer): ITgRichTextDateTime;
    function WithDateTimeFormat(const AValue: string): ITgRichTextDateTime;
  end;

  TTgRichTextTextMentionImpl = class(TTgRichTextImpl, ITgRichTextTextMention, ITgRichText)
  public
    function GetKind: TTgRichTextKind; override;
    function GetText: ITgRichText;
    function GetUser: ITgUser;
    function WithText(const AValue: ITgRichText): ITgRichTextTextMention;
    function WithUser(const AValue: ITgUser): ITgRichTextTextMention;
  end;

  TTgRichTextSubscriptImpl = class(TTgRichTextImpl, ITgRichTextSubscript, ITgRichText)
  public
    function GetKind: TTgRichTextKind; override;
    function GetText: ITgRichText;
    function WithText(const AValue: ITgRichText): ITgRichTextSubscript;
  end;

  TTgRichTextSuperscriptImpl = class(TTgRichTextImpl, ITgRichTextSuperscript, ITgRichText)
  public
    function GetKind: TTgRichTextKind; override;
    function GetText: ITgRichText;
    function WithText(const AValue: ITgRichText): ITgRichTextSuperscript;
  end;

  TTgRichTextMarkedImpl = class(TTgRichTextImpl, ITgRichTextMarked, ITgRichText)
  public
    function GetKind: TTgRichTextKind; override;
    function GetText: ITgRichText;
    function WithText(const AValue: ITgRichText): ITgRichTextMarked;
  end;

  TTgRichTextCodeImpl = class(TTgRichTextImpl, ITgRichTextCode, ITgRichText)
  public
    function GetKind: TTgRichTextKind; override;
    function GetText: ITgRichText;
    function WithText(const AValue: ITgRichText): ITgRichTextCode;
  end;

  TTgRichTextCustomEmojiImpl = class(TTgRichTextImpl, ITgRichTextCustomEmoji, ITgRichText)
  public
    function GetKind: TTgRichTextKind; override;
    function GetCustomEmojiId: string;
    function GetAlternativeText: string;
    function WithCustomEmojiId(const AValue: string): ITgRichTextCustomEmoji;
    function WithAlternativeText(const AValue: string): ITgRichTextCustomEmoji;
  end;

  TTgRichTextMathematicalExpressionImpl = class(TTgRichTextImpl, ITgRichTextMathematicalExpression, ITgRichText)
  public
    function GetKind: TTgRichTextKind; override;
    function GetExpression: string;
    function WithExpression(const AValue: string): ITgRichTextMathematicalExpression;
  end;

  TTgRichTextUrlImpl = class(TTgRichTextImpl, ITgRichTextUrl, ITgRichText)
  public
    function GetKind: TTgRichTextKind; override;
    function GetText: ITgRichText;
    function GetUrl: string;
    function WithText(const AValue: ITgRichText): ITgRichTextUrl;
    function WithUrl(const AValue: string): ITgRichTextUrl;
  end;

  TTgRichTextEmailAddressImpl = class(TTgRichTextImpl, ITgRichTextEmailAddress, ITgRichText)
  public
    function GetKind: TTgRichTextKind; override;
    function GetText: ITgRichText;
    function GetEmailAddress: string;
    function WithText(const AValue: ITgRichText): ITgRichTextEmailAddress;
    function WithEmailAddress(const AValue: string): ITgRichTextEmailAddress;
  end;

  TTgRichTextPhoneNumberImpl = class(TTgRichTextImpl, ITgRichTextPhoneNumber, ITgRichText)
  public
    function GetKind: TTgRichTextKind; override;
    function GetText: ITgRichText;
    function GetPhoneNumber: string;
    function WithText(const AValue: ITgRichText): ITgRichTextPhoneNumber;
    function WithPhoneNumber(const AValue: string): ITgRichTextPhoneNumber;
  end;

  TTgRichTextBankCardNumberImpl = class(TTgRichTextImpl, ITgRichTextBankCardNumber, ITgRichText)
  public
    function GetKind: TTgRichTextKind; override;
    function GetText: ITgRichText;
    function GetBankCardNumber: string;
    function WithText(const AValue: ITgRichText): ITgRichTextBankCardNumber;
    function WithBankCardNumber(const AValue: string): ITgRichTextBankCardNumber;
  end;

  TTgRichTextMentionImpl = class(TTgRichTextImpl, ITgRichTextMention, ITgRichText)
  public
    function GetKind: TTgRichTextKind; override;
    function GetText: ITgRichText;
    function GetUsername: string;
    function WithText(const AValue: ITgRichText): ITgRichTextMention;
    function WithUsername(const AValue: string): ITgRichTextMention;
  end;

  TTgRichTextHashtagImpl = class(TTgRichTextImpl, ITgRichTextHashtag, ITgRichText)
  public
    function GetKind: TTgRichTextKind; override;
    function GetText: ITgRichText;
    function GetHashtag: string;
    function WithText(const AValue: ITgRichText): ITgRichTextHashtag;
    function WithHashtag(const AValue: string): ITgRichTextHashtag;
  end;

  TTgRichTextCashtagImpl = class(TTgRichTextImpl, ITgRichTextCashtag, ITgRichText)
  public
    function GetKind: TTgRichTextKind; override;
    function GetText: ITgRichText;
    function GetCashtag: string;
    function WithText(const AValue: ITgRichText): ITgRichTextCashtag;
    function WithCashtag(const AValue: string): ITgRichTextCashtag;
  end;

  TTgRichTextBotCommandImpl = class(TTgRichTextImpl, ITgRichTextBotCommand, ITgRichText)
  public
    function GetKind: TTgRichTextKind; override;
    function GetText: ITgRichText;
    function GetBotCommand: string;
    function WithText(const AValue: ITgRichText): ITgRichTextBotCommand;
    function WithBotCommand(const AValue: string): ITgRichTextBotCommand;
  end;

  TTgRichTextButtonImpl = class(TTgRichTextImpl, ITgRichTextButton, ITgRichText)
  public
    function GetKind: TTgRichTextKind; override;
    function GetButton: ITgRichMessageButton;
    function WithButton(const AValue: ITgRichMessageButton): ITgRichTextButton;
  end;

  TTgRichTextAnchorImpl = class(TTgRichTextImpl, ITgRichTextAnchor, ITgRichText)
  public
    function GetKind: TTgRichTextKind; override;
    function GetName: string;
    function WithName(const AValue: string): ITgRichTextAnchor;
  end;

  TTgRichTextAnchorLinkImpl = class(TTgRichTextImpl, ITgRichTextAnchorLink, ITgRichText)
  public
    function GetKind: TTgRichTextKind; override;
    function GetText: ITgRichText;
    function GetAnchorName: string;
    function WithText(const AValue: ITgRichText): ITgRichTextAnchorLink;
    function WithAnchorName(const AValue: string): ITgRichTextAnchorLink;
  end;

  TTgRichTextReferenceImpl = class(TTgRichTextImpl, ITgRichTextReference, ITgRichText)
  public
    function GetKind: TTgRichTextKind; override;
    function GetText: ITgRichText;
    function GetName: string;
    function WithText(const AValue: ITgRichText): ITgRichTextReference;
    function WithName(const AValue: string): ITgRichTextReference;
  end;

  TTgRichTextReferenceLinkImpl = class(TTgRichTextImpl, ITgRichTextReferenceLink, ITgRichText)
  public
    function GetKind: TTgRichTextKind; override;
    function GetText: ITgRichText;
    function GetReferenceName: string;
    function WithText(const AValue: ITgRichText): ITgRichTextReferenceLink;
    function WithReferenceName(const AValue: string): ITgRichTextReferenceLink;
  end;

  TTgRichBlockCaptionImpl = class(TTgJsonDto, ITgRichBlockCaption)
  public
    function GetText: ITgRichText;
    function GetCredit: ITgRichText;
    function WithText(const AValue: ITgRichText): ITgRichBlockCaption;
    function WithCredit(const AValue: ITgRichText): ITgRichBlockCaption;
  end;

  TTgRichBlockTableCellImpl = class(TTgJsonDto, ITgRichBlockTableCell)
  public
    function GetText: ITgRichText;
    function GetIsHeader: Boolean;
    function GetColspan: Integer;
    function GetHasColspan: Boolean;
    function GetRowspan: Integer;
    function GetHasRowspan: Boolean;
    function GetAlign: string;
    function GetValign: string;
    function WithText(const AValue: ITgRichText): ITgRichBlockTableCell;
    function WithIsHeader(AValue: Boolean): ITgRichBlockTableCell;
    function WithColspan(AValue: Integer): ITgRichBlockTableCell;
    function WithRowspan(AValue: Integer): ITgRichBlockTableCell;
    function WithAlign(const AValue: string): ITgRichBlockTableCell;
    function WithValign(const AValue: string): ITgRichBlockTableCell;
  end;

  TTgRichBlockListItemImpl = class(TTgJsonDto, ITgRichBlockListItem)
  public
    function GetRichBlockListItemLabel: string;
    function GetBlocks: TArray<ITgRichBlock>;
    function GetHasCheckbox: Boolean;
    function GetIsChecked: Boolean;
    function GetValue: Integer;
    function GetHasValue: Boolean;
    function GetRichBlockListItemType: string;
  end;

  TTgRichBlockImpl = class(TTgJsonDto, ITgRichBlock)
  public
    function GetKind: TTgRichBlockKind; virtual;
    function GetKindText: string;
    function AsParagraph: ITgRichBlockParagraph;
    function AsSectionHeading: ITgRichBlockSectionHeading;
    function AsPreformatted: ITgRichBlockPreformatted;
    function AsFooter: ITgRichBlockFooter;
    function AsDivider: ITgRichBlockDivider;
    function AsMathematicalExpression: ITgRichBlockMathematicalExpression;
    function AsAnchor: ITgRichBlockAnchor;
    function AsList: ITgRichBlockList;
    function AsBlockQuotation: ITgRichBlockBlockQuotation;
    function AsExpandableBlockQuotation: ITgRichBlockExpandableBlockQuotation;
    function AsPullQuotation: ITgRichBlockPullQuotation;
    function AsCollage: ITgRichBlockCollage;
    function AsSlideshow: ITgRichBlockSlideshow;
    function AsTable: ITgRichBlockTable;
    function AsDetails: ITgRichBlockDetails;
    function AsMap: ITgRichBlockMap;
    function AsButtons: ITgRichBlockButtons;
    function AsAnimation: ITgRichBlockAnimation;
    function AsAudio: ITgRichBlockAudio;
    function AsDocument: ITgRichBlockDocument;
    function AsPhoto: ITgRichBlockPhoto;
    function AsVideo: ITgRichBlockVideo;
    function AsVoiceNote: ITgRichBlockVoiceNote;
    function AsThinking: ITgRichBlockThinking;
  end;

  TTgRichBlockParagraphImpl = class(TTgRichBlockImpl, ITgRichBlockParagraph, ITgRichBlock)
  public
    function GetKind: TTgRichBlockKind; override;
    function GetText: ITgRichText;
  end;

  TTgRichBlockSectionHeadingImpl = class(TTgRichBlockImpl, ITgRichBlockSectionHeading, ITgRichBlock)
  public
    function GetKind: TTgRichBlockKind; override;
    function GetText: ITgRichText;
    function GetSize: Integer;
  end;

  TTgRichBlockPreformattedImpl = class(TTgRichBlockImpl, ITgRichBlockPreformatted, ITgRichBlock)
  public
    function GetKind: TTgRichBlockKind; override;
    function GetText: ITgRichText;
    function GetLanguage: string;
  end;

  TTgRichBlockFooterImpl = class(TTgRichBlockImpl, ITgRichBlockFooter, ITgRichBlock)
  public
    function GetKind: TTgRichBlockKind; override;
    function GetText: ITgRichText;
  end;

  TTgRichBlockDividerImpl = class(TTgRichBlockImpl, ITgRichBlockDivider, ITgRichBlock)
  public
    function GetKind: TTgRichBlockKind; override;
  end;

  TTgRichBlockMathematicalExpressionImpl = class(TTgRichBlockImpl, ITgRichBlockMathematicalExpression, ITgRichBlock)
  public
    function GetKind: TTgRichBlockKind; override;
    function GetExpression: string;
  end;

  TTgRichBlockAnchorImpl = class(TTgRichBlockImpl, ITgRichBlockAnchor, ITgRichBlock)
  public
    function GetKind: TTgRichBlockKind; override;
    function GetName: string;
  end;

  TTgRichBlockListImpl = class(TTgRichBlockImpl, ITgRichBlockList, ITgRichBlock)
  public
    function GetKind: TTgRichBlockKind; override;
    function GetItems: TArray<ITgRichBlockListItem>;
  end;

  TTgRichBlockBlockQuotationImpl = class(TTgRichBlockImpl, ITgRichBlockBlockQuotation, ITgRichBlock)
  public
    function GetKind: TTgRichBlockKind; override;
    function GetBlocks: TArray<ITgRichBlock>;
    function GetCredit: ITgRichText;
  end;

  TTgRichBlockExpandableBlockQuotationImpl = class(TTgRichBlockImpl, ITgRichBlockExpandableBlockQuotation, ITgRichBlock)
  public
    function GetKind: TTgRichBlockKind; override;
    function GetText: ITgRichText;
    function GetCredit: ITgRichText;
  end;

  TTgRichBlockPullQuotationImpl = class(TTgRichBlockImpl, ITgRichBlockPullQuotation, ITgRichBlock)
  public
    function GetKind: TTgRichBlockKind; override;
    function GetText: ITgRichText;
    function GetCredit: ITgRichText;
  end;

  TTgRichBlockCollageImpl = class(TTgRichBlockImpl, ITgRichBlockCollage, ITgRichBlock)
  public
    function GetKind: TTgRichBlockKind; override;
    function GetBlocks: TArray<ITgRichBlock>;
    function GetCaption: ITgRichBlockCaption;
  end;

  TTgRichBlockSlideshowImpl = class(TTgRichBlockImpl, ITgRichBlockSlideshow, ITgRichBlock)
  public
    function GetKind: TTgRichBlockKind; override;
    function GetBlocks: TArray<ITgRichBlock>;
    function GetCaption: ITgRichBlockCaption;
  end;

  TTgRichBlockTableImpl = class(TTgRichBlockImpl, ITgRichBlockTable, ITgRichBlock)
  public
    function GetKind: TTgRichBlockKind; override;
    function GetCells: TArray<TArray<ITgRichBlockTableCell>>;
    function GetIsBordered: Boolean;
    function GetIsStriped: Boolean;
    function GetIsCompact: Boolean;
    function GetCaption: ITgRichText;
  end;

  TTgRichBlockDetailsImpl = class(TTgRichBlockImpl, ITgRichBlockDetails, ITgRichBlock)
  public
    function GetKind: TTgRichBlockKind; override;
    function GetSummary: ITgRichText;
    function GetBlocks: TArray<ITgRichBlock>;
    function GetIsOpen: Boolean;
  end;

  TTgRichBlockMapImpl = class(TTgRichBlockImpl, ITgRichBlockMap, ITgRichBlock)
  public
    function GetKind: TTgRichBlockKind; override;
    function GetLocation: ITgLocation;
    function GetZoom: Integer;
    function GetWidth: Integer;
    function GetHeight: Integer;
    function GetCaption: ITgRichBlockCaption;
  end;

  TTgRichBlockButtonsImpl = class(TTgRichBlockImpl, ITgRichBlockButtons, ITgRichBlock)
  public
    function GetKind: TTgRichBlockKind; override;
    function GetButtons: TArray<ITgRichMessageButton>;
    function GetAlign: string;
  end;

  TTgRichBlockAnimationImpl = class(TTgRichBlockImpl, ITgRichBlockAnimation, ITgRichBlock)
  public
    function GetKind: TTgRichBlockKind; override;
    function GetAnimation: ITgAnimation;
    function GetHasSpoiler: Boolean;
    function GetCaption: ITgRichBlockCaption;
  end;

  TTgRichBlockAudioImpl = class(TTgRichBlockImpl, ITgRichBlockAudio, ITgRichBlock)
  public
    function GetKind: TTgRichBlockKind; override;
    function GetAudio: ITgAudio;
    function GetCaption: ITgRichBlockCaption;
  end;

  TTgRichBlockDocumentImpl = class(TTgRichBlockImpl, ITgRichBlockDocument, ITgRichBlock)
  public
    function GetKind: TTgRichBlockKind; override;
    function GetDocument: ITgDocument;
    function GetCaption: ITgRichBlockCaption;
  end;

  TTgRichBlockPhotoImpl = class(TTgRichBlockImpl, ITgRichBlockPhoto, ITgRichBlock)
  public
    function GetKind: TTgRichBlockKind; override;
    function GetPhoto: TArray<ITgPhotoSize>;
    function GetHasSpoiler: Boolean;
    function GetCaption: ITgRichBlockCaption;
  end;

  TTgRichBlockVideoImpl = class(TTgRichBlockImpl, ITgRichBlockVideo, ITgRichBlock)
  public
    function GetKind: TTgRichBlockKind; override;
    function GetVideo: ITgVideo;
    function GetHasSpoiler: Boolean;
    function GetCaption: ITgRichBlockCaption;
  end;

  TTgRichBlockVoiceNoteImpl = class(TTgRichBlockImpl, ITgRichBlockVoiceNote, ITgRichBlock)
  public
    function GetKind: TTgRichBlockKind; override;
    function GetVoiceNote: ITgVoice;
    function GetCaption: ITgRichBlockCaption;
  end;

  TTgRichBlockThinkingImpl = class(TTgRichBlockImpl, ITgRichBlockThinking, ITgRichBlock)
  public
    function GetKind: TTgRichBlockKind; override;
    function GetText: ITgRichText;
  end;

  TTgInputRichBlockListItemImpl = class(TTgOutObject, ITgInputRichBlockListItem)
  public
    function WithBlocks(const AValue: array of TTgInputRichBlock): ITgInputRichBlockListItem;
    function WithHasCheckbox(AValue: Boolean): ITgInputRichBlockListItem;
    function WithIsChecked(AValue: Boolean): ITgInputRichBlockListItem;
    function WithValue(AValue: Integer): ITgInputRichBlockListItem;
    function WithInputRichBlockListItemType(const AValue: string): ITgInputRichBlockListItem;
  end;

  TTgInputRichBlockParagraphImpl = class(TTgOutObject, ITgInputRichBlockParagraph)
  public
    function WithText(const AValue: ITgRichText): ITgInputRichBlockParagraph;
  end;

  TTgInputRichBlockSectionHeadingImpl = class(TTgOutObject, ITgInputRichBlockSectionHeading)
  public
    function WithText(const AValue: ITgRichText): ITgInputRichBlockSectionHeading;
    function WithSize(AValue: Integer): ITgInputRichBlockSectionHeading;
  end;

  TTgInputRichBlockPreformattedImpl = class(TTgOutObject, ITgInputRichBlockPreformatted)
  public
    function WithText(const AValue: ITgRichText): ITgInputRichBlockPreformatted;
    function WithLanguage(const AValue: string): ITgInputRichBlockPreformatted;
  end;

  TTgInputRichBlockFooterImpl = class(TTgOutObject, ITgInputRichBlockFooter)
  public
    function WithText(const AValue: ITgRichText): ITgInputRichBlockFooter;
  end;

  TTgInputRichBlockDividerImpl = class(TTgOutObject, ITgInputRichBlockDivider)
  public
  end;

  TTgInputRichBlockMathematicalExpressionImpl = class(TTgOutObject, ITgInputRichBlockMathematicalExpression)
  public
    function WithExpression(const AValue: string): ITgInputRichBlockMathematicalExpression;
  end;

  TTgInputRichBlockAnchorImpl = class(TTgOutObject, ITgInputRichBlockAnchor)
  public
    function WithName(const AValue: string): ITgInputRichBlockAnchor;
  end;

  TTgInputRichBlockListImpl = class(TTgOutObject, ITgInputRichBlockList)
  public
    function WithItems(const AValue: array of ITgInputRichBlockListItem): ITgInputRichBlockList;
  end;

  TTgInputRichBlockBlockQuotationImpl = class(TTgOutObject, ITgInputRichBlockBlockQuotation)
  public
    function WithBlocks(const AValue: array of TTgInputRichBlock): ITgInputRichBlockBlockQuotation;
    function WithCredit(const AValue: ITgRichText): ITgInputRichBlockBlockQuotation;
  end;

  TTgInputRichBlockExpandableBlockQuotationImpl = class(TTgOutObject, ITgInputRichBlockExpandableBlockQuotation)
  public
    function WithText(const AValue: ITgRichText): ITgInputRichBlockExpandableBlockQuotation;
    function WithCredit(const AValue: ITgRichText): ITgInputRichBlockExpandableBlockQuotation;
  end;

  TTgInputRichBlockPullQuotationImpl = class(TTgOutObject, ITgInputRichBlockPullQuotation)
  public
    function WithText(const AValue: ITgRichText): ITgInputRichBlockPullQuotation;
    function WithCredit(const AValue: ITgRichText): ITgInputRichBlockPullQuotation;
  end;

  TTgInputRichBlockCollageImpl = class(TTgOutObject, ITgInputRichBlockCollage)
  public
    function WithBlocks(const AValue: array of TTgInputRichBlock): ITgInputRichBlockCollage;
    function WithCaption(const AValue: ITgRichBlockCaption): ITgInputRichBlockCollage;
  end;

  TTgInputRichBlockSlideshowImpl = class(TTgOutObject, ITgInputRichBlockSlideshow)
  public
    function WithBlocks(const AValue: array of TTgInputRichBlock): ITgInputRichBlockSlideshow;
    function WithCaption(const AValue: ITgRichBlockCaption): ITgInputRichBlockSlideshow;
  end;

  TTgInputRichBlockTableImpl = class(TTgOutObject, ITgInputRichBlockTable)
  public
    function WithCells(const AValue: array of TArray<ITgRichBlockTableCell>): ITgInputRichBlockTable;
    function WithCellsRow(const ARow: array of ITgRichBlockTableCell): ITgInputRichBlockTable;
    function WithIsBordered(AValue: Boolean): ITgInputRichBlockTable;
    function WithIsStriped(AValue: Boolean): ITgInputRichBlockTable;
    function WithIsCompact(AValue: Boolean): ITgInputRichBlockTable;
    function WithCaption(const AValue: ITgRichText): ITgInputRichBlockTable;
  end;

  TTgInputRichBlockDetailsImpl = class(TTgOutObject, ITgInputRichBlockDetails)
  public
    function WithSummary(const AValue: ITgRichText): ITgInputRichBlockDetails;
    function WithBlocks(const AValue: array of TTgInputRichBlock): ITgInputRichBlockDetails;
    function WithIsOpen(AValue: Boolean): ITgInputRichBlockDetails;
  end;

  TTgInputRichBlockMapImpl = class(TTgOutObject, ITgInputRichBlockMap)
  public
    function WithLocation(const AValue: ITgLocation): ITgInputRichBlockMap;
    function WithZoom(AValue: Integer): ITgInputRichBlockMap;
    function WithWidth(AValue: Integer): ITgInputRichBlockMap;
    function WithHeight(AValue: Integer): ITgInputRichBlockMap;
    function WithCaption(const AValue: ITgRichBlockCaption): ITgInputRichBlockMap;
  end;

  TTgInputRichBlockButtonsImpl = class(TTgOutObject, ITgInputRichBlockButtons)
  public
    function WithButtons(const AValue: array of ITgRichMessageButton): ITgInputRichBlockButtons;
    function WithAlign(const AValue: string): ITgInputRichBlockButtons;
  end;

  TTgInputRichBlockAnimationImpl = class(TTgOutObject, ITgInputRichBlockAnimation)
  public
    function WithAnimation(const AValue: ITgInputMediaAnimation): ITgInputRichBlockAnimation;
    function WithCaption(const AValue: ITgRichBlockCaption): ITgInputRichBlockAnimation;
  end;

  TTgInputRichBlockAudioImpl = class(TTgOutObject, ITgInputRichBlockAudio)
  public
    function WithAudio(const AValue: ITgInputMediaAudio): ITgInputRichBlockAudio;
    function WithCaption(const AValue: ITgRichBlockCaption): ITgInputRichBlockAudio;
  end;

  TTgInputRichBlockDocumentImpl = class(TTgOutObject, ITgInputRichBlockDocument)
  public
    function WithDocument(const AValue: ITgInputMediaDocument): ITgInputRichBlockDocument;
    function WithCaption(const AValue: ITgRichBlockCaption): ITgInputRichBlockDocument;
  end;

  TTgInputRichBlockPhotoImpl = class(TTgOutObject, ITgInputRichBlockPhoto)
  public
    function WithPhoto(const AValue: ITgInputMediaPhoto): ITgInputRichBlockPhoto;
    function WithCaption(const AValue: ITgRichBlockCaption): ITgInputRichBlockPhoto;
  end;

  TTgInputRichBlockVideoImpl = class(TTgOutObject, ITgInputRichBlockVideo)
  public
    function WithVideo(const AValue: ITgInputMediaVideo): ITgInputRichBlockVideo;
    function WithCaption(const AValue: ITgRichBlockCaption): ITgInputRichBlockVideo;
  end;

  TTgInputRichBlockVoiceNoteImpl = class(TTgOutObject, ITgInputRichBlockVoiceNote)
  public
    function WithVoiceNote(const AValue: ITgInputMediaVoiceNote): ITgInputRichBlockVoiceNote;
    function WithCaption(const AValue: ITgRichBlockCaption): ITgInputRichBlockVoiceNote;
  end;

  TTgInputRichBlockThinkingImpl = class(TTgOutObject, ITgInputRichBlockThinking)
  public
    function WithText(const AValue: ITgRichText): ITgInputRichBlockThinking;
  end;

  TTgInlineQueryImpl = class(TTgJsonDto, ITgInlineQuery)
  public
    function GetId: string;
    function GetFrom: ITgUser;
    function GetQuery: string;
    function GetOffset: string;
    function GetChatType: string;
    function GetLocation: ITgLocation;
  end;

  TTgInlineQueryResultsButtonImpl = class(TTgOutObject, ITgInlineQueryResultsButton)
  public
    function WithText(const AValue: string): ITgInlineQueryResultsButton;
    function WithWebApp(const AValue: ITgWebAppInfo): ITgInlineQueryResultsButton;
    function WithStartParameter(const AValue: string): ITgInlineQueryResultsButton;
  end;

  TTgInlineQueryResultArticleImpl = class(TTgOutObject, ITgInlineQueryResultArticle)
  public
    function WithId(const AValue: string): ITgInlineQueryResultArticle;
    function WithTitle(const AValue: string): ITgInlineQueryResultArticle;
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultArticle;
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultArticle;
    function WithUrl(const AValue: string): ITgInlineQueryResultArticle;
    function WithDescription(const AValue: string): ITgInlineQueryResultArticle;
    function WithThumbnailUrl(const AValue: string): ITgInlineQueryResultArticle;
    function WithThumbnailWidth(AValue: Integer): ITgInlineQueryResultArticle;
    function WithThumbnailHeight(AValue: Integer): ITgInlineQueryResultArticle;
  end;

  TTgInlineQueryResultPhotoImpl = class(TTgOutObject, ITgInlineQueryResultPhoto)
  public
    function WithId(const AValue: string): ITgInlineQueryResultPhoto;
    function WithPhotoUrl(const AValue: string): ITgInlineQueryResultPhoto;
    function WithThumbnailUrl(const AValue: string): ITgInlineQueryResultPhoto;
    function WithPhotoWidth(AValue: Integer): ITgInlineQueryResultPhoto;
    function WithPhotoHeight(AValue: Integer): ITgInlineQueryResultPhoto;
    function WithTitle(const AValue: string): ITgInlineQueryResultPhoto;
    function WithDescription(const AValue: string): ITgInlineQueryResultPhoto;
    function WithCaption(const AValue: string): ITgInlineQueryResultPhoto;
    function WithParseMode(const AValue: string): ITgInlineQueryResultPhoto;
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultPhoto;
    function WithShowCaptionAboveMedia(AValue: Boolean): ITgInlineQueryResultPhoto;
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultPhoto;
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultPhoto;
  end;

  TTgInlineQueryResultGifImpl = class(TTgOutObject, ITgInlineQueryResultGif)
  public
    function WithId(const AValue: string): ITgInlineQueryResultGif;
    function WithGifUrl(const AValue: string): ITgInlineQueryResultGif;
    function WithGifWidth(AValue: Integer): ITgInlineQueryResultGif;
    function WithGifHeight(AValue: Integer): ITgInlineQueryResultGif;
    function WithGifDuration(AValue: Integer): ITgInlineQueryResultGif;
    function WithThumbnailUrl(const AValue: string): ITgInlineQueryResultGif;
    function WithThumbnailMimeType(const AValue: string): ITgInlineQueryResultGif;
    function WithTitle(const AValue: string): ITgInlineQueryResultGif;
    function WithCaption(const AValue: string): ITgInlineQueryResultGif;
    function WithParseMode(const AValue: string): ITgInlineQueryResultGif;
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultGif;
    function WithShowCaptionAboveMedia(AValue: Boolean): ITgInlineQueryResultGif;
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultGif;
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultGif;
  end;

  TTgInlineQueryResultMpeg4GifImpl = class(TTgOutObject, ITgInlineQueryResultMpeg4Gif)
  public
    function WithId(const AValue: string): ITgInlineQueryResultMpeg4Gif;
    function WithMpeg4Url(const AValue: string): ITgInlineQueryResultMpeg4Gif;
    function WithMpeg4Width(AValue: Integer): ITgInlineQueryResultMpeg4Gif;
    function WithMpeg4Height(AValue: Integer): ITgInlineQueryResultMpeg4Gif;
    function WithMpeg4Duration(AValue: Integer): ITgInlineQueryResultMpeg4Gif;
    function WithThumbnailUrl(const AValue: string): ITgInlineQueryResultMpeg4Gif;
    function WithThumbnailMimeType(const AValue: string): ITgInlineQueryResultMpeg4Gif;
    function WithTitle(const AValue: string): ITgInlineQueryResultMpeg4Gif;
    function WithCaption(const AValue: string): ITgInlineQueryResultMpeg4Gif;
    function WithParseMode(const AValue: string): ITgInlineQueryResultMpeg4Gif;
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultMpeg4Gif;
    function WithShowCaptionAboveMedia(AValue: Boolean): ITgInlineQueryResultMpeg4Gif;
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultMpeg4Gif;
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultMpeg4Gif;
  end;

  TTgInlineQueryResultVideoImpl = class(TTgOutObject, ITgInlineQueryResultVideo)
  public
    function WithId(const AValue: string): ITgInlineQueryResultVideo;
    function WithVideoUrl(const AValue: string): ITgInlineQueryResultVideo;
    function WithMimeType(const AValue: string): ITgInlineQueryResultVideo;
    function WithThumbnailUrl(const AValue: string): ITgInlineQueryResultVideo;
    function WithTitle(const AValue: string): ITgInlineQueryResultVideo;
    function WithCaption(const AValue: string): ITgInlineQueryResultVideo;
    function WithParseMode(const AValue: string): ITgInlineQueryResultVideo;
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultVideo;
    function WithShowCaptionAboveMedia(AValue: Boolean): ITgInlineQueryResultVideo;
    function WithVideoWidth(AValue: Integer): ITgInlineQueryResultVideo;
    function WithVideoHeight(AValue: Integer): ITgInlineQueryResultVideo;
    function WithVideoDuration(AValue: Integer): ITgInlineQueryResultVideo;
    function WithDescription(const AValue: string): ITgInlineQueryResultVideo;
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultVideo;
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultVideo;
  end;

  TTgInlineQueryResultAudioImpl = class(TTgOutObject, ITgInlineQueryResultAudio)
  public
    function WithId(const AValue: string): ITgInlineQueryResultAudio;
    function WithAudioUrl(const AValue: string): ITgInlineQueryResultAudio;
    function WithTitle(const AValue: string): ITgInlineQueryResultAudio;
    function WithCaption(const AValue: string): ITgInlineQueryResultAudio;
    function WithParseMode(const AValue: string): ITgInlineQueryResultAudio;
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultAudio;
    function WithPerformer(const AValue: string): ITgInlineQueryResultAudio;
    function WithAudioDuration(AValue: Integer): ITgInlineQueryResultAudio;
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultAudio;
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultAudio;
  end;

  TTgInlineQueryResultVoiceImpl = class(TTgOutObject, ITgInlineQueryResultVoice)
  public
    function WithId(const AValue: string): ITgInlineQueryResultVoice;
    function WithVoiceUrl(const AValue: string): ITgInlineQueryResultVoice;
    function WithTitle(const AValue: string): ITgInlineQueryResultVoice;
    function WithCaption(const AValue: string): ITgInlineQueryResultVoice;
    function WithParseMode(const AValue: string): ITgInlineQueryResultVoice;
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultVoice;
    function WithVoiceDuration(AValue: Integer): ITgInlineQueryResultVoice;
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultVoice;
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultVoice;
  end;

  TTgInlineQueryResultDocumentImpl = class(TTgOutObject, ITgInlineQueryResultDocument)
  public
    function WithId(const AValue: string): ITgInlineQueryResultDocument;
    function WithTitle(const AValue: string): ITgInlineQueryResultDocument;
    function WithCaption(const AValue: string): ITgInlineQueryResultDocument;
    function WithParseMode(const AValue: string): ITgInlineQueryResultDocument;
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultDocument;
    function WithDocumentUrl(const AValue: string): ITgInlineQueryResultDocument;
    function WithMimeType(const AValue: string): ITgInlineQueryResultDocument;
    function WithDescription(const AValue: string): ITgInlineQueryResultDocument;
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultDocument;
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultDocument;
    function WithThumbnailUrl(const AValue: string): ITgInlineQueryResultDocument;
    function WithThumbnailWidth(AValue: Integer): ITgInlineQueryResultDocument;
    function WithThumbnailHeight(AValue: Integer): ITgInlineQueryResultDocument;
  end;

  TTgInlineQueryResultLocationImpl = class(TTgOutObject, ITgInlineQueryResultLocation)
  public
    function WithId(const AValue: string): ITgInlineQueryResultLocation;
    function WithLatitude(AValue: Double): ITgInlineQueryResultLocation;
    function WithLongitude(AValue: Double): ITgInlineQueryResultLocation;
    function WithTitle(const AValue: string): ITgInlineQueryResultLocation;
    function WithHorizontalAccuracy(AValue: Double): ITgInlineQueryResultLocation;
    function WithLivePeriod(AValue: Integer): ITgInlineQueryResultLocation;
    function WithHeading(AValue: Integer): ITgInlineQueryResultLocation;
    function WithProximityAlertRadius(AValue: Integer): ITgInlineQueryResultLocation;
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultLocation;
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultLocation;
    function WithThumbnailUrl(const AValue: string): ITgInlineQueryResultLocation;
    function WithThumbnailWidth(AValue: Integer): ITgInlineQueryResultLocation;
    function WithThumbnailHeight(AValue: Integer): ITgInlineQueryResultLocation;
  end;

  TTgInlineQueryResultVenueImpl = class(TTgOutObject, ITgInlineQueryResultVenue)
  public
    function WithId(const AValue: string): ITgInlineQueryResultVenue;
    function WithLatitude(AValue: Double): ITgInlineQueryResultVenue;
    function WithLongitude(AValue: Double): ITgInlineQueryResultVenue;
    function WithTitle(const AValue: string): ITgInlineQueryResultVenue;
    function WithAddress(const AValue: string): ITgInlineQueryResultVenue;
    function WithFoursquareId(const AValue: string): ITgInlineQueryResultVenue;
    function WithFoursquareType(const AValue: string): ITgInlineQueryResultVenue;
    function WithGooglePlaceId(const AValue: string): ITgInlineQueryResultVenue;
    function WithGooglePlaceType(const AValue: string): ITgInlineQueryResultVenue;
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultVenue;
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultVenue;
    function WithThumbnailUrl(const AValue: string): ITgInlineQueryResultVenue;
    function WithThumbnailWidth(AValue: Integer): ITgInlineQueryResultVenue;
    function WithThumbnailHeight(AValue: Integer): ITgInlineQueryResultVenue;
  end;

  TTgInlineQueryResultContactImpl = class(TTgOutObject, ITgInlineQueryResultContact)
  public
    function WithId(const AValue: string): ITgInlineQueryResultContact;
    function WithPhoneNumber(const AValue: string): ITgInlineQueryResultContact;
    function WithFirstName(const AValue: string): ITgInlineQueryResultContact;
    function WithLastName(const AValue: string): ITgInlineQueryResultContact;
    function WithVcard(const AValue: string): ITgInlineQueryResultContact;
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultContact;
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultContact;
    function WithThumbnailUrl(const AValue: string): ITgInlineQueryResultContact;
    function WithThumbnailWidth(AValue: Integer): ITgInlineQueryResultContact;
    function WithThumbnailHeight(AValue: Integer): ITgInlineQueryResultContact;
  end;

  TTgInlineQueryResultGameImpl = class(TTgOutObject, ITgInlineQueryResultGame)
  public
    function WithId(const AValue: string): ITgInlineQueryResultGame;
    function WithGameShortName(const AValue: string): ITgInlineQueryResultGame;
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultGame;
  end;

  TTgInlineQueryResultCachedPhotoImpl = class(TTgOutObject, ITgInlineQueryResultCachedPhoto)
  public
    function WithId(const AValue: string): ITgInlineQueryResultCachedPhoto;
    function WithPhotoFileId(const AValue: string): ITgInlineQueryResultCachedPhoto;
    function WithTitle(const AValue: string): ITgInlineQueryResultCachedPhoto;
    function WithDescription(const AValue: string): ITgInlineQueryResultCachedPhoto;
    function WithCaption(const AValue: string): ITgInlineQueryResultCachedPhoto;
    function WithParseMode(const AValue: string): ITgInlineQueryResultCachedPhoto;
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultCachedPhoto;
    function WithShowCaptionAboveMedia(AValue: Boolean): ITgInlineQueryResultCachedPhoto;
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultCachedPhoto;
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultCachedPhoto;
  end;

  TTgInlineQueryResultCachedGifImpl = class(TTgOutObject, ITgInlineQueryResultCachedGif)
  public
    function WithId(const AValue: string): ITgInlineQueryResultCachedGif;
    function WithGifFileId(const AValue: string): ITgInlineQueryResultCachedGif;
    function WithTitle(const AValue: string): ITgInlineQueryResultCachedGif;
    function WithCaption(const AValue: string): ITgInlineQueryResultCachedGif;
    function WithParseMode(const AValue: string): ITgInlineQueryResultCachedGif;
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultCachedGif;
    function WithShowCaptionAboveMedia(AValue: Boolean): ITgInlineQueryResultCachedGif;
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultCachedGif;
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultCachedGif;
  end;

  TTgInlineQueryResultCachedMpeg4GifImpl = class(TTgOutObject, ITgInlineQueryResultCachedMpeg4Gif)
  public
    function WithId(const AValue: string): ITgInlineQueryResultCachedMpeg4Gif;
    function WithMpeg4FileId(const AValue: string): ITgInlineQueryResultCachedMpeg4Gif;
    function WithTitle(const AValue: string): ITgInlineQueryResultCachedMpeg4Gif;
    function WithCaption(const AValue: string): ITgInlineQueryResultCachedMpeg4Gif;
    function WithParseMode(const AValue: string): ITgInlineQueryResultCachedMpeg4Gif;
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultCachedMpeg4Gif;
    function WithShowCaptionAboveMedia(AValue: Boolean): ITgInlineQueryResultCachedMpeg4Gif;
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultCachedMpeg4Gif;
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultCachedMpeg4Gif;
  end;

  TTgInlineQueryResultCachedStickerImpl = class(TTgOutObject, ITgInlineQueryResultCachedSticker)
  public
    function WithId(const AValue: string): ITgInlineQueryResultCachedSticker;
    function WithStickerFileId(const AValue: string): ITgInlineQueryResultCachedSticker;
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultCachedSticker;
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultCachedSticker;
  end;

  TTgInlineQueryResultCachedDocumentImpl = class(TTgOutObject, ITgInlineQueryResultCachedDocument)
  public
    function WithId(const AValue: string): ITgInlineQueryResultCachedDocument;
    function WithTitle(const AValue: string): ITgInlineQueryResultCachedDocument;
    function WithDocumentFileId(const AValue: string): ITgInlineQueryResultCachedDocument;
    function WithDescription(const AValue: string): ITgInlineQueryResultCachedDocument;
    function WithCaption(const AValue: string): ITgInlineQueryResultCachedDocument;
    function WithParseMode(const AValue: string): ITgInlineQueryResultCachedDocument;
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultCachedDocument;
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultCachedDocument;
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultCachedDocument;
  end;

  TTgInlineQueryResultCachedVideoImpl = class(TTgOutObject, ITgInlineQueryResultCachedVideo)
  public
    function WithId(const AValue: string): ITgInlineQueryResultCachedVideo;
    function WithVideoFileId(const AValue: string): ITgInlineQueryResultCachedVideo;
    function WithTitle(const AValue: string): ITgInlineQueryResultCachedVideo;
    function WithDescription(const AValue: string): ITgInlineQueryResultCachedVideo;
    function WithCaption(const AValue: string): ITgInlineQueryResultCachedVideo;
    function WithParseMode(const AValue: string): ITgInlineQueryResultCachedVideo;
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultCachedVideo;
    function WithShowCaptionAboveMedia(AValue: Boolean): ITgInlineQueryResultCachedVideo;
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultCachedVideo;
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultCachedVideo;
  end;

  TTgInlineQueryResultCachedVoiceImpl = class(TTgOutObject, ITgInlineQueryResultCachedVoice)
  public
    function WithId(const AValue: string): ITgInlineQueryResultCachedVoice;
    function WithVoiceFileId(const AValue: string): ITgInlineQueryResultCachedVoice;
    function WithTitle(const AValue: string): ITgInlineQueryResultCachedVoice;
    function WithCaption(const AValue: string): ITgInlineQueryResultCachedVoice;
    function WithParseMode(const AValue: string): ITgInlineQueryResultCachedVoice;
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultCachedVoice;
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultCachedVoice;
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultCachedVoice;
  end;

  TTgInlineQueryResultCachedAudioImpl = class(TTgOutObject, ITgInlineQueryResultCachedAudio)
  public
    function WithId(const AValue: string): ITgInlineQueryResultCachedAudio;
    function WithAudioFileId(const AValue: string): ITgInlineQueryResultCachedAudio;
    function WithCaption(const AValue: string): ITgInlineQueryResultCachedAudio;
    function WithParseMode(const AValue: string): ITgInlineQueryResultCachedAudio;
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultCachedAudio;
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultCachedAudio;
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultCachedAudio;
  end;

  TTgInputTextMessageContentImpl = class(TTgOutObject, ITgInputTextMessageContent)
  public
    function WithMessageText(const AValue: string): ITgInputTextMessageContent;
    function WithParseMode(const AValue: string): ITgInputTextMessageContent;
    function WithEntities(const AValue: array of ITgMessageEntity): ITgInputTextMessageContent;
    function WithLinkPreviewOptions(const AValue: ITgLinkPreviewOptions): ITgInputTextMessageContent;
  end;

  TTgInputRichMessageContentImpl = class(TTgOutObject, ITgInputRichMessageContent)
  public
    function WithRichMessage(const AValue: ITgInputRichMessage): ITgInputRichMessageContent;
  end;

  TTgInputLocationMessageContentImpl = class(TTgOutObject, ITgInputLocationMessageContent)
  public
    function WithLatitude(AValue: Double): ITgInputLocationMessageContent;
    function WithLongitude(AValue: Double): ITgInputLocationMessageContent;
    function WithHorizontalAccuracy(AValue: Double): ITgInputLocationMessageContent;
    function WithLivePeriod(AValue: Integer): ITgInputLocationMessageContent;
    function WithHeading(AValue: Integer): ITgInputLocationMessageContent;
    function WithProximityAlertRadius(AValue: Integer): ITgInputLocationMessageContent;
  end;

  TTgInputVenueMessageContentImpl = class(TTgOutObject, ITgInputVenueMessageContent)
  public
    function WithLatitude(AValue: Double): ITgInputVenueMessageContent;
    function WithLongitude(AValue: Double): ITgInputVenueMessageContent;
    function WithTitle(const AValue: string): ITgInputVenueMessageContent;
    function WithAddress(const AValue: string): ITgInputVenueMessageContent;
    function WithFoursquareId(const AValue: string): ITgInputVenueMessageContent;
    function WithFoursquareType(const AValue: string): ITgInputVenueMessageContent;
    function WithGooglePlaceId(const AValue: string): ITgInputVenueMessageContent;
    function WithGooglePlaceType(const AValue: string): ITgInputVenueMessageContent;
  end;

  TTgInputContactMessageContentImpl = class(TTgOutObject, ITgInputContactMessageContent)
  public
    function WithPhoneNumber(const AValue: string): ITgInputContactMessageContent;
    function WithFirstName(const AValue: string): ITgInputContactMessageContent;
    function WithLastName(const AValue: string): ITgInputContactMessageContent;
    function WithVcard(const AValue: string): ITgInputContactMessageContent;
  end;

  TTgInputInvoiceMessageContentImpl = class(TTgOutObject, ITgInputInvoiceMessageContent)
  public
    function WithTitle(const AValue: string): ITgInputInvoiceMessageContent;
    function WithDescription(const AValue: string): ITgInputInvoiceMessageContent;
    function WithPayload(const AValue: string): ITgInputInvoiceMessageContent;
    function WithProviderToken(const AValue: string): ITgInputInvoiceMessageContent;
    function WithCurrency(const AValue: string): ITgInputInvoiceMessageContent;
    function WithPrices(const AValue: array of ITgLabeledPrice): ITgInputInvoiceMessageContent;
    function WithMaxTipAmount(AValue: Integer): ITgInputInvoiceMessageContent;
    function WithSuggestedTipAmounts(const AValue: TArray<Integer>): ITgInputInvoiceMessageContent;
    function WithProviderData(const AValue: string): ITgInputInvoiceMessageContent;
    function WithPhotoUrl(const AValue: string): ITgInputInvoiceMessageContent;
    function WithPhotoSize(AValue: Integer): ITgInputInvoiceMessageContent;
    function WithPhotoWidth(AValue: Integer): ITgInputInvoiceMessageContent;
    function WithPhotoHeight(AValue: Integer): ITgInputInvoiceMessageContent;
    function WithNeedName(AValue: Boolean): ITgInputInvoiceMessageContent;
    function WithNeedPhoneNumber(AValue: Boolean): ITgInputInvoiceMessageContent;
    function WithNeedEmail(AValue: Boolean): ITgInputInvoiceMessageContent;
    function WithNeedShippingAddress(AValue: Boolean): ITgInputInvoiceMessageContent;
    function WithSendPhoneNumberToProvider(AValue: Boolean): ITgInputInvoiceMessageContent;
    function WithSendEmailToProvider(AValue: Boolean): ITgInputInvoiceMessageContent;
    function WithIsFlexible(AValue: Boolean): ITgInputInvoiceMessageContent;
  end;

  TTgChosenInlineResultImpl = class(TTgJsonDto, ITgChosenInlineResult)
  public
    function GetResultId: string;
    function GetFrom: ITgUser;
    function GetLocation: ITgLocation;
    function GetInlineMessageId: string;
    function GetQuery: string;
  end;

  TTgLabeledPriceImpl = class(TTgOutObject, ITgLabeledPrice)
  public
    function WithLabeledPriceLabel(const AValue: string): ITgLabeledPrice;
    function WithAmount(AValue: Integer): ITgLabeledPrice;
  end;

  TTgInvoiceImpl = class(TTgJsonDto, ITgInvoice)
  public
    function GetTitle: string;
    function GetDescription: string;
    function GetStartParameter: string;
    function GetCurrency: string;
    function GetTotalAmount: Integer;
  end;

  TTgShippingAddressImpl = class(TTgJsonDto, ITgShippingAddress)
  public
    function GetCountryCode: string;
    function GetState: string;
    function GetCity: string;
    function GetStreetLine1: string;
    function GetStreetLine2: string;
    function GetPostCode: string;
  end;

  TTgOrderInfoImpl = class(TTgJsonDto, ITgOrderInfo)
  public
    function GetName: string;
    function GetPhoneNumber: string;
    function GetEmail: string;
    function GetShippingAddress: ITgShippingAddress;
  end;

  TTgShippingOptionImpl = class(TTgOutObject, ITgShippingOption)
  public
    function WithId(const AValue: string): ITgShippingOption;
    function WithTitle(const AValue: string): ITgShippingOption;
    function WithPrices(const AValue: array of ITgLabeledPrice): ITgShippingOption;
  end;

  TTgSuccessfulPaymentImpl = class(TTgJsonDto, ITgSuccessfulPayment)
  public
    function GetCurrency: string;
    function GetTotalAmount: Integer;
    function GetInvoicePayload: string;
    function GetSubscriptionExpirationDate: Int64;
    function GetHasSubscriptionExpirationDate: Boolean;
    function GetIsRecurring: Boolean;
    function GetIsFirstRecurring: Boolean;
    function GetShippingOptionId: string;
    function GetOrderInfo: ITgOrderInfo;
    function GetTelegramPaymentChargeId: string;
    function GetProviderPaymentChargeId: string;
  end;

  TTgRefundedPaymentImpl = class(TTgJsonDto, ITgRefundedPayment)
  public
    function GetCurrency: string;
    function GetTotalAmount: Integer;
    function GetInvoicePayload: string;
    function GetTelegramPaymentChargeId: string;
    function GetProviderPaymentChargeId: string;
  end;

  TTgShippingQueryImpl = class(TTgJsonDto, ITgShippingQuery)
  public
    function GetId: string;
    function GetFrom: ITgUser;
    function GetInvoicePayload: string;
    function GetShippingAddress: ITgShippingAddress;
  end;

  TTgPreCheckoutQueryImpl = class(TTgJsonDto, ITgPreCheckoutQuery)
  public
    function GetId: string;
    function GetFrom: ITgUser;
    function GetCurrency: string;
    function GetTotalAmount: Integer;
    function GetInvoicePayload: string;
    function GetShippingOptionId: string;
    function GetOrderInfo: ITgOrderInfo;
  end;

  TTgPaidMediaPurchasedImpl = class(TTgJsonDto, ITgPaidMediaPurchased)
  public
    function GetFrom: ITgUser;
    function GetPaidMediaPayload: string;
  end;

  TTgRevenueWithdrawalStateImpl = class(TTgJsonDto, ITgRevenueWithdrawalState)
  public
    function GetKind: TTgRevenueWithdrawalStateKind; virtual;
    function GetKindText: string;
    function AsPending: ITgRevenueWithdrawalStatePending;
    function AsSucceeded: ITgRevenueWithdrawalStateSucceeded;
    function AsFailed: ITgRevenueWithdrawalStateFailed;
  end;

  TTgRevenueWithdrawalStatePendingImpl = class(TTgRevenueWithdrawalStateImpl, ITgRevenueWithdrawalStatePending, ITgRevenueWithdrawalState)
  public
    function GetKind: TTgRevenueWithdrawalStateKind; override;
  end;

  TTgRevenueWithdrawalStateSucceededImpl = class(TTgRevenueWithdrawalStateImpl, ITgRevenueWithdrawalStateSucceeded, ITgRevenueWithdrawalState)
  public
    function GetKind: TTgRevenueWithdrawalStateKind; override;
    function GetDate: Int64;
    function GetUrl: string;
  end;

  TTgRevenueWithdrawalStateFailedImpl = class(TTgRevenueWithdrawalStateImpl, ITgRevenueWithdrawalStateFailed, ITgRevenueWithdrawalState)
  public
    function GetKind: TTgRevenueWithdrawalStateKind; override;
  end;

  TTgAffiliateInfoImpl = class(TTgJsonDto, ITgAffiliateInfo)
  public
    function GetAffiliateUser: ITgUser;
    function GetAffiliateChat: ITgChat;
    function GetCommissionPerMille: Integer;
    function GetAmount: Integer;
    function GetNanostarAmount: Integer;
    function GetHasNanostarAmount: Boolean;
  end;

  TTgTransactionPartnerImpl = class(TTgJsonDto, ITgTransactionPartner)
  public
    function GetKind: TTgTransactionPartnerKind; virtual;
    function GetKindText: string;
    function AsUser: ITgTransactionPartnerUser;
    function AsChat: ITgTransactionPartnerChat;
    function AsAffiliateProgram: ITgTransactionPartnerAffiliateProgram;
    function AsFragment: ITgTransactionPartnerFragment;
    function AsTelegramAds: ITgTransactionPartnerTelegramAds;
    function AsTelegramApi: ITgTransactionPartnerTelegramApi;
    function AsOther: ITgTransactionPartnerOther;
  end;

  TTgTransactionPartnerUserImpl = class(TTgTransactionPartnerImpl, ITgTransactionPartnerUser, ITgTransactionPartner)
  public
    function GetKind: TTgTransactionPartnerKind; override;
    function GetTransactionType: string;
    function GetUser: ITgUser;
    function GetAffiliate: ITgAffiliateInfo;
    function GetInvoicePayload: string;
    function GetSubscriptionPeriod: Integer;
    function GetHasSubscriptionPeriod: Boolean;
    function GetPaidMedia: TArray<ITgPaidMedia>;
    function GetPaidMediaPayload: string;
    function GetGift: ITgGift;
    function GetPremiumSubscriptionDuration: Integer;
    function GetHasPremiumSubscriptionDuration: Boolean;
  end;

  TTgTransactionPartnerChatImpl = class(TTgTransactionPartnerImpl, ITgTransactionPartnerChat, ITgTransactionPartner)
  public
    function GetKind: TTgTransactionPartnerKind; override;
    function GetChat: ITgChat;
    function GetGift: ITgGift;
  end;

  TTgTransactionPartnerAffiliateProgramImpl = class(TTgTransactionPartnerImpl, ITgTransactionPartnerAffiliateProgram, ITgTransactionPartner)
  public
    function GetKind: TTgTransactionPartnerKind; override;
    function GetSponsorUser: ITgUser;
    function GetCommissionPerMille: Integer;
  end;

  TTgTransactionPartnerFragmentImpl = class(TTgTransactionPartnerImpl, ITgTransactionPartnerFragment, ITgTransactionPartner)
  public
    function GetKind: TTgTransactionPartnerKind; override;
    function GetWithdrawalState: ITgRevenueWithdrawalState;
  end;

  TTgTransactionPartnerTelegramAdsImpl = class(TTgTransactionPartnerImpl, ITgTransactionPartnerTelegramAds, ITgTransactionPartner)
  public
    function GetKind: TTgTransactionPartnerKind; override;
  end;

  TTgTransactionPartnerTelegramApiImpl = class(TTgTransactionPartnerImpl, ITgTransactionPartnerTelegramApi, ITgTransactionPartner)
  public
    function GetKind: TTgTransactionPartnerKind; override;
    function GetRequestCount: Integer;
  end;

  TTgTransactionPartnerOtherImpl = class(TTgTransactionPartnerImpl, ITgTransactionPartnerOther, ITgTransactionPartner)
  public
    function GetKind: TTgTransactionPartnerKind; override;
  end;

  TTgStarTransactionImpl = class(TTgJsonDto, ITgStarTransaction)
  public
    function GetId: string;
    function GetAmount: Integer;
    function GetNanostarAmount: Integer;
    function GetHasNanostarAmount: Boolean;
    function GetDate: Int64;
    function GetSource: ITgTransactionPartner;
    function GetReceiver: ITgTransactionPartner;
  end;

  TTgStarTransactionsImpl = class(TTgJsonDto, ITgStarTransactions)
  public
    function GetTransactions: TArray<ITgStarTransaction>;
  end;

  TTgPassportDataImpl = class(TTgJsonDto, ITgPassportData)
  public
    function GetData: TArray<ITgEncryptedPassportElement>;
    function GetCredentials: ITgEncryptedCredentials;
  end;

  TTgPassportFileImpl = class(TTgJsonDto, ITgPassportFile)
  public
    function GetFileId: string;
    function GetFileUniqueId: string;
    function GetFileSize: Int64;
    function GetFileDate: Int64;
  end;

  TTgEncryptedPassportElementImpl = class(TTgJsonDto, ITgEncryptedPassportElement)
  public
    function GetEncryptedPassportElementType: string;
    function GetData: string;
    function GetPhoneNumber: string;
    function GetEmail: string;
    function GetFiles: TArray<ITgPassportFile>;
    function GetFrontSide: ITgPassportFile;
    function GetReverseSide: ITgPassportFile;
    function GetSelfie: ITgPassportFile;
    function GetTranslation: TArray<ITgPassportFile>;
    function GetHash: string;
  end;

  TTgEncryptedCredentialsImpl = class(TTgJsonDto, ITgEncryptedCredentials)
  public
    function GetData: string;
    function GetHash: string;
    function GetSecret: string;
  end;

  TTgPassportElementErrorDataFieldImpl = class(TTgOutObject, ITgPassportElementErrorDataField)
  public
    function WithPassportElementErrorDataFieldType(const AValue: string): ITgPassportElementErrorDataField;
    function WithFieldName(const AValue: string): ITgPassportElementErrorDataField;
    function WithDataHash(const AValue: string): ITgPassportElementErrorDataField;
    function WithMessage(const AValue: string): ITgPassportElementErrorDataField;
  end;

  TTgPassportElementErrorFrontSideImpl = class(TTgOutObject, ITgPassportElementErrorFrontSide)
  public
    function WithPassportElementErrorFrontSideType(const AValue: string): ITgPassportElementErrorFrontSide;
    function WithFileHash(const AValue: string): ITgPassportElementErrorFrontSide;
    function WithMessage(const AValue: string): ITgPassportElementErrorFrontSide;
  end;

  TTgPassportElementErrorReverseSideImpl = class(TTgOutObject, ITgPassportElementErrorReverseSide)
  public
    function WithPassportElementErrorReverseSideType(const AValue: string): ITgPassportElementErrorReverseSide;
    function WithFileHash(const AValue: string): ITgPassportElementErrorReverseSide;
    function WithMessage(const AValue: string): ITgPassportElementErrorReverseSide;
  end;

  TTgPassportElementErrorSelfieImpl = class(TTgOutObject, ITgPassportElementErrorSelfie)
  public
    function WithPassportElementErrorSelfieType(const AValue: string): ITgPassportElementErrorSelfie;
    function WithFileHash(const AValue: string): ITgPassportElementErrorSelfie;
    function WithMessage(const AValue: string): ITgPassportElementErrorSelfie;
  end;

  TTgPassportElementErrorFileImpl = class(TTgOutObject, ITgPassportElementErrorFile)
  public
    function WithPassportElementErrorFileType(const AValue: string): ITgPassportElementErrorFile;
    function WithFileHash(const AValue: string): ITgPassportElementErrorFile;
    function WithMessage(const AValue: string): ITgPassportElementErrorFile;
  end;

  TTgPassportElementErrorFilesImpl = class(TTgOutObject, ITgPassportElementErrorFiles)
  public
    function WithPassportElementErrorFilesType(const AValue: string): ITgPassportElementErrorFiles;
    function WithFileHashes(const AValue: TArray<string>): ITgPassportElementErrorFiles;
    function WithMessage(const AValue: string): ITgPassportElementErrorFiles;
  end;

  TTgPassportElementErrorTranslationFileImpl = class(TTgOutObject, ITgPassportElementErrorTranslationFile)
  public
    function WithPassportElementErrorTranslationFileType(const AValue: string): ITgPassportElementErrorTranslationFile;
    function WithFileHash(const AValue: string): ITgPassportElementErrorTranslationFile;
    function WithMessage(const AValue: string): ITgPassportElementErrorTranslationFile;
  end;

  TTgPassportElementErrorTranslationFilesImpl = class(TTgOutObject, ITgPassportElementErrorTranslationFiles)
  public
    function WithPassportElementErrorTranslationFilesType(const AValue: string): ITgPassportElementErrorTranslationFiles;
    function WithFileHashes(const AValue: TArray<string>): ITgPassportElementErrorTranslationFiles;
    function WithMessage(const AValue: string): ITgPassportElementErrorTranslationFiles;
  end;

  TTgPassportElementErrorUnspecifiedImpl = class(TTgOutObject, ITgPassportElementErrorUnspecified)
  public
    function WithPassportElementErrorUnspecifiedType(const AValue: string): ITgPassportElementErrorUnspecified;
    function WithElementHash(const AValue: string): ITgPassportElementErrorUnspecified;
    function WithMessage(const AValue: string): ITgPassportElementErrorUnspecified;
  end;

  TTgGameImpl = class(TTgJsonDto, ITgGame)
  public
    function GetTitle: string;
    function GetDescription: string;
    function GetPhoto: TArray<ITgPhotoSize>;
    function GetText: string;
    function GetTextEntities: TArray<ITgMessageEntity>;
    function GetAnimation: ITgAnimation;
  end;

  TTgCallbackGameImpl = class(TTgJsonDto, ITgCallbackGame)
  public
  end;

  TTgGameHighScoreImpl = class(TTgJsonDto, ITgGameHighScore)
  public
    function GetPosition: Integer;
    function GetUser: ITgUser;
    function GetScore: Integer;
  end;

