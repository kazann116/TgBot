// Gen.Methods.inc — методы Bot API (внутри класса TTgApi: private-хелперы, public-методы).
// Сгенерировано TgBotGen по Telegram Bot API 10.3 (August 24, 2026). Не редактируйте вручную.

  private
    function BuildGetUpdatesParams(const AOptions: TTgGetUpdatesOptions): TTgParams;
    function ExecGetUpdates(AParams: TTgParams): TArray<ITgUpdate>;
    function BuildSetWebhookParams(const AUrl: string;
      const AOptions: TTgSetWebhookOptions): TTgParams;
    function ExecSetWebhook(AParams: TTgParams): Boolean;
    function BuildDeleteWebhookParams(const AOptions: TTgDeleteWebhookOptions): TTgParams;
    function ExecDeleteWebhook(AParams: TTgParams): Boolean;
    function ExecGetWebhookInfo(AParams: TTgParams): ITgWebhookInfo;
    function ExecGetMe(AParams: TTgParams): ITgUser;
    function ExecLogOut(AParams: TTgParams): Boolean;
    function ExecClose(AParams: TTgParams): Boolean;
    function BuildSendMessageParams(const AChatId: TTgChatId; const AText: string;
      const AOptions: TTgSendMessageOptions): TTgParams;
    function ExecSendMessage(AParams: TTgParams): ITgMessage;
    function BuildSendMessageVariant1Params(const AChatId: TTgChatId; const AText: string;
      const AReplyMarkup: TTgReplyMarkup; const AOptions: TTgSendMessageOptions): TTgParams;
    function BuildForwardMessageParams(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
      AMessageId: Int64; const AOptions: TTgForwardMessageOptions): TTgParams;
    function ExecForwardMessage(AParams: TTgParams): ITgMessage;
    function BuildForwardMessagesParams(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
      const AMessageIds: TArray<Int64>; const AOptions: TTgForwardMessagesOptions): TTgParams;
    function ExecForwardMessages(AParams: TTgParams): TArray<ITgMessageId>;
    function BuildCopyMessageParams(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
      AMessageId: Int64; const AOptions: TTgCopyMessageOptions): TTgParams;
    function ExecCopyMessage(AParams: TTgParams): ITgMessageId;
    function BuildCopyMessagesParams(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
      const AMessageIds: TArray<Int64>; const AOptions: TTgCopyMessagesOptions): TTgParams;
    function ExecCopyMessages(AParams: TTgParams): TArray<ITgMessageId>;
    function BuildSendPhotoParams(const AChatId: TTgChatId; const APhoto: TTgInputFile;
      const AOptions: TTgSendPhotoOptions): TTgParams;
    function ExecSendPhoto(AParams: TTgParams): ITgMessage;
    function BuildSendPhotoVariant1Params(const AChatId: TTgChatId; const APhoto: TTgInputFile;
      const ACaption: string; const AOptions: TTgSendPhotoOptions): TTgParams;
    function BuildSendLivePhotoParams(const AChatId: TTgChatId; const ALivePhoto: TTgInputFile;
      const APhoto: TTgInputFile; const AOptions: TTgSendLivePhotoOptions): TTgParams;
    function ExecSendLivePhoto(AParams: TTgParams): ITgMessage;
    function BuildSendAudioParams(const AChatId: TTgChatId; const AAudio: TTgInputFile;
      const AOptions: TTgSendAudioOptions): TTgParams;
    function ExecSendAudio(AParams: TTgParams): ITgMessage;
    function BuildSendDocumentParams(const AChatId: TTgChatId; const ADocument: TTgInputFile;
      const AOptions: TTgSendDocumentOptions): TTgParams;
    function ExecSendDocument(AParams: TTgParams): ITgMessage;
    function BuildSendDocumentVariant1Params(const AChatId: TTgChatId;
      const ADocument: TTgInputFile; const ACaption: string;
      const AOptions: TTgSendDocumentOptions): TTgParams;
    function BuildSendVideoParams(const AChatId: TTgChatId; const AVideo: TTgInputFile;
      const AOptions: TTgSendVideoOptions): TTgParams;
    function ExecSendVideo(AParams: TTgParams): ITgMessage;
    function BuildSendAnimationParams(const AChatId: TTgChatId; const AAnimation: TTgInputFile;
      const AOptions: TTgSendAnimationOptions): TTgParams;
    function ExecSendAnimation(AParams: TTgParams): ITgMessage;
    function BuildSendVoiceParams(const AChatId: TTgChatId; const AVoice: TTgInputFile;
      const AOptions: TTgSendVoiceOptions): TTgParams;
    function ExecSendVoice(AParams: TTgParams): ITgMessage;
    function BuildSendVideoNoteParams(const AChatId: TTgChatId; const AVideoNote: TTgInputFile;
      const AOptions: TTgSendVideoNoteOptions): TTgParams;
    function ExecSendVideoNote(AParams: TTgParams): ITgMessage;
    function BuildSendPaidMediaParams(const AChatId: TTgChatId; AStarCount: Integer;
      const AMedia: array of TTgInputPaidMedia; const AOptions: TTgSendPaidMediaOptions): TTgParams;
    function ExecSendPaidMedia(AParams: TTgParams): ITgMessage;
    function BuildSendMediaGroupParams(const AChatId: TTgChatId;
      const AMedia: array of TTgMediaGroupItem;
      const AOptions: TTgSendMediaGroupOptions): TTgParams;
    function ExecSendMediaGroup(AParams: TTgParams): TArray<ITgMessage>;
    function BuildSendLocationParams(const AChatId: TTgChatId; ALatitude: Double;
      ALongitude: Double; const AOptions: TTgSendLocationOptions): TTgParams;
    function ExecSendLocation(AParams: TTgParams): ITgMessage;
    function BuildSendVenueParams(const AChatId: TTgChatId; ALatitude: Double; ALongitude: Double;
      const ATitle: string; const AAddress: string; const AOptions: TTgSendVenueOptions): TTgParams;
    function ExecSendVenue(AParams: TTgParams): ITgMessage;
    function BuildSendContactParams(const AChatId: TTgChatId; const APhoneNumber: string;
      const AFirstName: string; const AOptions: TTgSendContactOptions): TTgParams;
    function ExecSendContact(AParams: TTgParams): ITgMessage;
    function BuildSendPollParams(const AChatId: TTgChatId; const AQuestion: string;
      const APollOptions: array of ITgInputPollOption;
      const AOptions: TTgSendPollOptions): TTgParams;
    function ExecSendPoll(AParams: TTgParams): ITgMessage;
    function BuildSendChecklistParams(const ABusinessConnectionId: string; const AChatId: TTgChatId;
      const AChecklist: ITgInputChecklist; const AOptions: TTgSendChecklistOptions): TTgParams;
    function ExecSendChecklist(AParams: TTgParams): ITgMessage;
    function BuildSendDiceParams(const AChatId: TTgChatId;
      const AOptions: TTgSendDiceOptions): TTgParams;
    function ExecSendDice(AParams: TTgParams): ITgMessage;
    function BuildSendMessageDraftParams(AChatId: Int64; ADraftId: Int64;
      const AOptions: TTgSendMessageDraftOptions): TTgParams;
    function ExecSendMessageDraft(AParams: TTgParams): Boolean;
    function BuildSendChatActionParams(const AChatId: TTgChatId; const AAction: string;
      const AOptions: TTgSendChatActionOptions): TTgParams;
    function ExecSendChatAction(AParams: TTgParams): Boolean;
    function BuildSetMessageReactionParams(const AChatId: TTgChatId; AMessageId: Int64;
      const AOptions: TTgSetMessageReactionOptions): TTgParams;
    function ExecSetMessageReaction(AParams: TTgParams): Boolean;
    function BuildGetUserProfilePhotosParams(AUserId: Int64;
      const AOptions: TTgGetUserProfilePhotosOptions): TTgParams;
    function ExecGetUserProfilePhotos(AParams: TTgParams): ITgUserProfilePhotos;
    function BuildGetUserProfileAudiosParams(AUserId: Int64;
      const AOptions: TTgGetUserProfileAudiosOptions): TTgParams;
    function ExecGetUserProfileAudios(AParams: TTgParams): ITgUserProfileAudios;
    function BuildSetUserEmojiStatusParams(AUserId: Int64;
      const AOptions: TTgSetUserEmojiStatusOptions): TTgParams;
    function ExecSetUserEmojiStatus(AParams: TTgParams): Boolean;
    function BuildGetFileParams(const AFileId: string): TTgParams;
    function ExecGetFile(AParams: TTgParams): ITgFile;
    function BuildBanChatMemberParams(const AChatId: TTgChatId; AUserId: Int64;
      const AOptions: TTgBanChatMemberOptions): TTgParams;
    function ExecBanChatMember(AParams: TTgParams): Boolean;
    function BuildUnbanChatMemberParams(const AChatId: TTgChatId; AUserId: Int64;
      const AOptions: TTgUnbanChatMemberOptions): TTgParams;
    function ExecUnbanChatMember(AParams: TTgParams): Boolean;
    function BuildRestrictChatMemberParams(const AChatId: TTgChatId; AUserId: Int64;
      const APermissions: ITgChatPermissions;
      const AOptions: TTgRestrictChatMemberOptions): TTgParams;
    function ExecRestrictChatMember(AParams: TTgParams): Boolean;
    function BuildPromoteChatMemberParams(const AChatId: TTgChatId; AUserId: Int64;
      const AOptions: TTgPromoteChatMemberOptions): TTgParams;
    function ExecPromoteChatMember(AParams: TTgParams): Boolean;
    function BuildSetChatAdministratorCustomTitleParams(const AChatId: TTgChatId; AUserId: Int64;
      const ACustomTitle: string): TTgParams;
    function ExecSetChatAdministratorCustomTitle(AParams: TTgParams): Boolean;
    function BuildSetChatMemberTagParams(const AChatId: TTgChatId; AUserId: Int64;
      const AOptions: TTgSetChatMemberTagOptions): TTgParams;
    function ExecSetChatMemberTag(AParams: TTgParams): Boolean;
    function BuildBanChatSenderChatParams(const AChatId: TTgChatId;
      ASenderChatId: Int64): TTgParams;
    function ExecBanChatSenderChat(AParams: TTgParams): Boolean;
    function BuildUnbanChatSenderChatParams(const AChatId: TTgChatId;
      ASenderChatId: Int64): TTgParams;
    function ExecUnbanChatSenderChat(AParams: TTgParams): Boolean;
    function BuildSetChatPermissionsParams(const AChatId: TTgChatId;
      const APermissions: ITgChatPermissions;
      const AOptions: TTgSetChatPermissionsOptions): TTgParams;
    function ExecSetChatPermissions(AParams: TTgParams): Boolean;
    function BuildExportChatInviteLinkParams(const AChatId: TTgChatId): TTgParams;
    function ExecExportChatInviteLink(AParams: TTgParams): string;
    function BuildCreateChatInviteLinkParams(const AChatId: TTgChatId;
      const AOptions: TTgCreateChatInviteLinkOptions): TTgParams;
    function ExecCreateChatInviteLink(AParams: TTgParams): ITgChatInviteLink;
    function BuildEditChatInviteLinkParams(const AChatId: TTgChatId; const AInviteLink: string;
      const AOptions: TTgEditChatInviteLinkOptions): TTgParams;
    function ExecEditChatInviteLink(AParams: TTgParams): ITgChatInviteLink;
    function BuildCreateChatSubscriptionInviteLinkParams(const AChatId: TTgChatId;
      ASubscriptionPeriod: Integer; ASubscriptionPrice: Integer;
      const AOptions: TTgCreateChatSubscriptionInviteLinkOptions): TTgParams;
    function ExecCreateChatSubscriptionInviteLink(AParams: TTgParams): ITgChatInviteLink;
    function BuildEditChatSubscriptionInviteLinkParams(const AChatId: TTgChatId;
      const AInviteLink: string;
      const AOptions: TTgEditChatSubscriptionInviteLinkOptions): TTgParams;
    function ExecEditChatSubscriptionInviteLink(AParams: TTgParams): ITgChatInviteLink;
    function BuildRevokeChatInviteLinkParams(const AChatId: TTgChatId;
      const AInviteLink: string): TTgParams;
    function ExecRevokeChatInviteLink(AParams: TTgParams): ITgChatInviteLink;
    function BuildApproveChatJoinRequestParams(const AChatId: TTgChatId; AUserId: Int64): TTgParams;
    function ExecApproveChatJoinRequest(AParams: TTgParams): Boolean;
    function BuildDeclineChatJoinRequestParams(const AChatId: TTgChatId; AUserId: Int64): TTgParams;
    function ExecDeclineChatJoinRequest(AParams: TTgParams): Boolean;
    function BuildAnswerChatJoinRequestQueryParams(const AChatJoinRequestQueryId: string;
      const AChatJoinRequestQueryResult: string): TTgParams;
    function ExecAnswerChatJoinRequestQuery(AParams: TTgParams): Boolean;
    function BuildSendChatJoinRequestWebAppParams(const AChatJoinRequestQueryId: string;
      const AWebAppUrl: string): TTgParams;
    function ExecSendChatJoinRequestWebApp(AParams: TTgParams): Boolean;
    function BuildSetChatPhotoParams(const AChatId: TTgChatId;
      const APhoto: TTgInputFile): TTgParams;
    function ExecSetChatPhoto(AParams: TTgParams): Boolean;
    function BuildDeleteChatPhotoParams(const AChatId: TTgChatId): TTgParams;
    function ExecDeleteChatPhoto(AParams: TTgParams): Boolean;
    function BuildSetChatTitleParams(const AChatId: TTgChatId; const ATitle: string): TTgParams;
    function ExecSetChatTitle(AParams: TTgParams): Boolean;
    function BuildSetChatDescriptionParams(const AChatId: TTgChatId;
      const AOptions: TTgSetChatDescriptionOptions): TTgParams;
    function ExecSetChatDescription(AParams: TTgParams): Boolean;
    function BuildPinChatMessageParams(const AChatId: TTgChatId; AMessageId: Int64;
      const AOptions: TTgPinChatMessageOptions): TTgParams;
    function ExecPinChatMessage(AParams: TTgParams): Boolean;
    function BuildUnpinChatMessageParams(const AChatId: TTgChatId;
      const AOptions: TTgUnpinChatMessageOptions): TTgParams;
    function ExecUnpinChatMessage(AParams: TTgParams): Boolean;
    function BuildUnpinAllChatMessagesParams(const AChatId: TTgChatId): TTgParams;
    function ExecUnpinAllChatMessages(AParams: TTgParams): Boolean;
    function BuildLeaveChatParams(const AChatId: TTgChatId): TTgParams;
    function ExecLeaveChat(AParams: TTgParams): Boolean;
    function BuildGetChatParams(const AChatId: TTgChatId): TTgParams;
    function ExecGetChat(AParams: TTgParams): ITgChatFullInfo;
    function BuildGetChatAdministratorsParams(const AChatId: TTgChatId;
      const AOptions: TTgGetChatAdministratorsOptions): TTgParams;
    function ExecGetChatAdministrators(AParams: TTgParams): TArray<ITgChatMember>;
    function BuildGetChatMemberCountParams(const AChatId: TTgChatId): TTgParams;
    function ExecGetChatMemberCount(AParams: TTgParams): Integer;
    function BuildGetChatMemberParams(const AChatId: TTgChatId; AUserId: Int64): TTgParams;
    function ExecGetChatMember(AParams: TTgParams): ITgChatMember;
    function BuildGetUserPersonalChatMessagesParams(AUserId: Int64; ALimit: Integer): TTgParams;
    function ExecGetUserPersonalChatMessages(AParams: TTgParams): TArray<ITgMessage>;
    function BuildSetChatStickerSetParams(const AChatId: TTgChatId;
      const AStickerSetName: string): TTgParams;
    function ExecSetChatStickerSet(AParams: TTgParams): Boolean;
    function BuildDeleteChatStickerSetParams(const AChatId: TTgChatId): TTgParams;
    function ExecDeleteChatStickerSet(AParams: TTgParams): Boolean;
    function ExecGetForumTopicIconStickers(AParams: TTgParams): TArray<ITgSticker>;
    function BuildCreateForumTopicParams(const AChatId: TTgChatId; const AName: string;
      const AOptions: TTgCreateForumTopicOptions): TTgParams;
    function ExecCreateForumTopic(AParams: TTgParams): ITgForumTopic;
    function BuildEditForumTopicParams(const AChatId: TTgChatId; AMessageThreadId: Int64;
      const AOptions: TTgEditForumTopicOptions): TTgParams;
    function ExecEditForumTopic(AParams: TTgParams): Boolean;
    function BuildCloseForumTopicParams(const AChatId: TTgChatId;
      AMessageThreadId: Int64): TTgParams;
    function ExecCloseForumTopic(AParams: TTgParams): Boolean;
    function BuildReopenForumTopicParams(const AChatId: TTgChatId;
      AMessageThreadId: Int64): TTgParams;
    function ExecReopenForumTopic(AParams: TTgParams): Boolean;
    function BuildDeleteForumTopicParams(const AChatId: TTgChatId;
      AMessageThreadId: Int64): TTgParams;
    function ExecDeleteForumTopic(AParams: TTgParams): Boolean;
    function BuildUnpinAllForumTopicMessagesParams(const AChatId: TTgChatId;
      AMessageThreadId: Int64): TTgParams;
    function ExecUnpinAllForumTopicMessages(AParams: TTgParams): Boolean;
    function BuildEditGeneralForumTopicParams(const AChatId: TTgChatId;
      const AName: string): TTgParams;
    function ExecEditGeneralForumTopic(AParams: TTgParams): Boolean;
    function BuildCloseGeneralForumTopicParams(const AChatId: TTgChatId): TTgParams;
    function ExecCloseGeneralForumTopic(AParams: TTgParams): Boolean;
    function BuildReopenGeneralForumTopicParams(const AChatId: TTgChatId): TTgParams;
    function ExecReopenGeneralForumTopic(AParams: TTgParams): Boolean;
    function BuildHideGeneralForumTopicParams(const AChatId: TTgChatId): TTgParams;
    function ExecHideGeneralForumTopic(AParams: TTgParams): Boolean;
    function BuildUnhideGeneralForumTopicParams(const AChatId: TTgChatId): TTgParams;
    function ExecUnhideGeneralForumTopic(AParams: TTgParams): Boolean;
    function BuildUnpinAllGeneralForumTopicMessagesParams(const AChatId: TTgChatId): TTgParams;
    function ExecUnpinAllGeneralForumTopicMessages(AParams: TTgParams): Boolean;
    function BuildAnswerCallbackQueryParams(const ACallbackQueryId: string;
      const AOptions: TTgAnswerCallbackQueryOptions): TTgParams;
    function ExecAnswerCallbackQuery(AParams: TTgParams): Boolean;
    function BuildAnswerCallbackQueryVariant1Params(const ACallbackQueryId: string;
      const AText: string; const AOptions: TTgAnswerCallbackQueryOptions): TTgParams;
    function BuildAnswerCallbackQueryVariant2Params(const ACallbackQueryId: string;
      const AText: string; AShowAlert: Boolean;
      const AOptions: TTgAnswerCallbackQueryOptions): TTgParams;
    function BuildAnswerGuestQueryParams(const AGuestQueryId: string;
      const AGuestQueryResult: TTgInlineQueryResult): TTgParams;
    function ExecAnswerGuestQuery(AParams: TTgParams): ITgSentGuestMessage;
    function BuildGetUserChatBoostsParams(const AChatId: TTgChatId; AUserId: Int64): TTgParams;
    function ExecGetUserChatBoosts(AParams: TTgParams): ITgUserChatBoosts;
    function BuildGetBusinessConnectionParams(const ABusinessConnectionId: string): TTgParams;
    function ExecGetBusinessConnection(AParams: TTgParams): ITgBusinessConnection;
    function BuildGetManagedBotTokenParams(AUserId: Int64): TTgParams;
    function ExecGetManagedBotToken(AParams: TTgParams): string;
    function BuildReplaceManagedBotTokenParams(AUserId: Int64): TTgParams;
    function ExecReplaceManagedBotToken(AParams: TTgParams): string;
    function BuildGetManagedBotAccessSettingsParams(AUserId: Int64): TTgParams;
    function ExecGetManagedBotAccessSettings(AParams: TTgParams): ITgBotAccessSettings;
    function BuildSetManagedBotAccessSettingsParams(AUserId: Int64; AIsAccessRestricted: Boolean;
      const AOptions: TTgSetManagedBotAccessSettingsOptions): TTgParams;
    function ExecSetManagedBotAccessSettings(AParams: TTgParams): Boolean;
    function BuildSetMyCommandsParams(const ACommands: array of ITgBotCommand;
      const AOptions: TTgSetMyCommandsOptions): TTgParams;
    function ExecSetMyCommands(AParams: TTgParams): Boolean;
    function BuildDeleteMyCommandsParams(const AOptions: TTgDeleteMyCommandsOptions): TTgParams;
    function ExecDeleteMyCommands(AParams: TTgParams): Boolean;
    function BuildGetMyCommandsParams(const AOptions: TTgGetMyCommandsOptions): TTgParams;
    function ExecGetMyCommands(AParams: TTgParams): TArray<ITgBotCommand>;
    function BuildSetMyNameParams(const AOptions: TTgSetMyNameOptions): TTgParams;
    function ExecSetMyName(AParams: TTgParams): Boolean;
    function BuildGetMyNameParams(const AOptions: TTgGetMyNameOptions): TTgParams;
    function ExecGetMyName(AParams: TTgParams): ITgBotName;
    function BuildSetMyDescriptionParams(const AOptions: TTgSetMyDescriptionOptions): TTgParams;
    function ExecSetMyDescription(AParams: TTgParams): Boolean;
    function BuildGetMyDescriptionParams(const AOptions: TTgGetMyDescriptionOptions): TTgParams;
    function ExecGetMyDescription(AParams: TTgParams): ITgBotDescription;
    function BuildSetMyShortDescriptionParams(const AOptions: TTgSetMyShortDescriptionOptions): TTgParams;
    function ExecSetMyShortDescription(AParams: TTgParams): Boolean;
    function BuildGetMyShortDescriptionParams(const AOptions: TTgGetMyShortDescriptionOptions): TTgParams;
    function ExecGetMyShortDescription(AParams: TTgParams): ITgBotShortDescription;
    function BuildSetMyProfilePhotoParams(const APhoto: TTgInputProfilePhoto): TTgParams;
    function ExecSetMyProfilePhoto(AParams: TTgParams): Boolean;
    function ExecRemoveMyProfilePhoto(AParams: TTgParams): Boolean;
    function BuildSetChatMenuButtonParams(const AOptions: TTgSetChatMenuButtonOptions): TTgParams;
    function ExecSetChatMenuButton(AParams: TTgParams): Boolean;
    function BuildGetChatMenuButtonParams(const AOptions: TTgGetChatMenuButtonOptions): TTgParams;
    function ExecGetChatMenuButton(AParams: TTgParams): ITgMenuButton;
    function BuildSetMyDefaultAdministratorRightsParams(const AOptions: TTgSetMyDefaultAdministratorRightsOptions): TTgParams;
    function ExecSetMyDefaultAdministratorRights(AParams: TTgParams): Boolean;
    function BuildGetMyDefaultAdministratorRightsParams(const AOptions: TTgGetMyDefaultAdministratorRightsOptions): TTgParams;
    function ExecGetMyDefaultAdministratorRights(AParams: TTgParams): ITgChatAdministratorRights;
    function ExecGetAvailableGifts(AParams: TTgParams): ITgGifts;
    function BuildSendGiftParams(const AGiftId: string;
      const AOptions: TTgSendGiftOptions): TTgParams;
    function ExecSendGift(AParams: TTgParams): Boolean;
    function BuildGiftPremiumSubscriptionParams(AUserId: Int64; AMonthCount: Integer;
      AStarCount: Integer; const AOptions: TTgGiftPremiumSubscriptionOptions): TTgParams;
    function ExecGiftPremiumSubscription(AParams: TTgParams): Boolean;
    function BuildVerifyUserParams(AUserId: Int64; const AOptions: TTgVerifyUserOptions): TTgParams;
    function ExecVerifyUser(AParams: TTgParams): Boolean;
    function BuildVerifyChatParams(const AChatId: TTgChatId;
      const AOptions: TTgVerifyChatOptions): TTgParams;
    function ExecVerifyChat(AParams: TTgParams): Boolean;
    function BuildRemoveUserVerificationParams(AUserId: Int64): TTgParams;
    function ExecRemoveUserVerification(AParams: TTgParams): Boolean;
    function BuildRemoveChatVerificationParams(const AChatId: TTgChatId): TTgParams;
    function ExecRemoveChatVerification(AParams: TTgParams): Boolean;
    function BuildReadBusinessMessageParams(const ABusinessConnectionId: string; AChatId: Int64;
      AMessageId: Int64): TTgParams;
    function ExecReadBusinessMessage(AParams: TTgParams): Boolean;
    function BuildDeleteBusinessMessagesParams(const ABusinessConnectionId: string;
      const AMessageIds: TArray<Int64>): TTgParams;
    function ExecDeleteBusinessMessages(AParams: TTgParams): Boolean;
    function BuildSetBusinessAccountNameParams(const ABusinessConnectionId: string;
      const AFirstName: string; const AOptions: TTgSetBusinessAccountNameOptions): TTgParams;
    function ExecSetBusinessAccountName(AParams: TTgParams): Boolean;
    function BuildSetBusinessAccountUsernameParams(const ABusinessConnectionId: string;
      const AOptions: TTgSetBusinessAccountUsernameOptions): TTgParams;
    function ExecSetBusinessAccountUsername(AParams: TTgParams): Boolean;
    function BuildSetBusinessAccountBioParams(const ABusinessConnectionId: string;
      const AOptions: TTgSetBusinessAccountBioOptions): TTgParams;
    function ExecSetBusinessAccountBio(AParams: TTgParams): Boolean;
    function BuildSetBusinessAccountProfilePhotoParams(const ABusinessConnectionId: string;
      const APhoto: TTgInputProfilePhoto;
      const AOptions: TTgSetBusinessAccountProfilePhotoOptions): TTgParams;
    function ExecSetBusinessAccountProfilePhoto(AParams: TTgParams): Boolean;
    function BuildRemoveBusinessAccountProfilePhotoParams(const ABusinessConnectionId: string;
      const AOptions: TTgRemoveBusinessAccountProfilePhotoOptions): TTgParams;
    function ExecRemoveBusinessAccountProfilePhoto(AParams: TTgParams): Boolean;
    function BuildSetBusinessAccountGiftSettingsParams(const ABusinessConnectionId: string;
      AShowGiftButton: Boolean; const AAcceptedGiftTypes: ITgAcceptedGiftTypes): TTgParams;
    function ExecSetBusinessAccountGiftSettings(AParams: TTgParams): Boolean;
    function BuildGetBusinessAccountStarBalanceParams(const ABusinessConnectionId: string): TTgParams;
    function ExecGetBusinessAccountStarBalance(AParams: TTgParams): ITgStarAmount;
    function BuildTransferBusinessAccountStarsParams(const ABusinessConnectionId: string;
      AStarCount: Integer): TTgParams;
    function ExecTransferBusinessAccountStars(AParams: TTgParams): Boolean;
    function BuildGetBusinessAccountGiftsParams(const ABusinessConnectionId: string;
      const AOptions: TTgGetBusinessAccountGiftsOptions): TTgParams;
    function ExecGetBusinessAccountGifts(AParams: TTgParams): ITgOwnedGifts;
    function BuildGetUserGiftsParams(AUserId: Int64;
      const AOptions: TTgGetUserGiftsOptions): TTgParams;
    function ExecGetUserGifts(AParams: TTgParams): ITgOwnedGifts;
    function BuildGetChatGiftsParams(const AChatId: TTgChatId;
      const AOptions: TTgGetChatGiftsOptions): TTgParams;
    function ExecGetChatGifts(AParams: TTgParams): ITgOwnedGifts;
    function BuildConvertGiftToStarsParams(const ABusinessConnectionId: string;
      const AOwnedGiftId: string): TTgParams;
    function ExecConvertGiftToStars(AParams: TTgParams): Boolean;
    function BuildUpgradeGiftParams(const ABusinessConnectionId: string; const AOwnedGiftId: string;
      const AOptions: TTgUpgradeGiftOptions): TTgParams;
    function ExecUpgradeGift(AParams: TTgParams): Boolean;
    function BuildTransferGiftParams(const ABusinessConnectionId: string;
      const AOwnedGiftId: string; ANewOwnerChatId: Int64;
      const AOptions: TTgTransferGiftOptions): TTgParams;
    function ExecTransferGift(AParams: TTgParams): Boolean;
    function BuildPostStoryParams(const ABusinessConnectionId: string;
      const AContent: TTgInputStoryContent; AActivePeriod: Integer;
      const AOptions: TTgPostStoryOptions): TTgParams;
    function ExecPostStory(AParams: TTgParams): ITgStory;
    function BuildRepostStoryParams(const ABusinessConnectionId: string; AFromChatId: Int64;
      AFromStoryId: Int64; AActivePeriod: Integer;
      const AOptions: TTgRepostStoryOptions): TTgParams;
    function ExecRepostStory(AParams: TTgParams): ITgStory;
    function BuildEditStoryParams(const ABusinessConnectionId: string; AStoryId: Int64;
      const AContent: TTgInputStoryContent; const AOptions: TTgEditStoryOptions): TTgParams;
    function ExecEditStory(AParams: TTgParams): ITgStory;
    function BuildDeleteStoryParams(const ABusinessConnectionId: string;
      AStoryId: Int64): TTgParams;
    function ExecDeleteStory(AParams: TTgParams): Boolean;
    function BuildAnswerWebAppQueryParams(const AWebAppQueryId: string;
      const AWebAppQueryResult: TTgInlineQueryResult): TTgParams;
    function ExecAnswerWebAppQuery(AParams: TTgParams): ITgSentWebAppMessage;
    function BuildSavePreparedInlineMessageParams(AUserId: Int64;
      const APreparedInlineMessageResult: TTgInlineQueryResult;
      const AOptions: TTgSavePreparedInlineMessageOptions): TTgParams;
    function ExecSavePreparedInlineMessage(AParams: TTgParams): ITgPreparedInlineMessage;
    function BuildSavePreparedKeyboardButtonParams(AUserId: Int64;
      const AButton: ITgKeyboardButton): TTgParams;
    function ExecSavePreparedKeyboardButton(AParams: TTgParams): ITgPreparedKeyboardButton;
    function BuildEditMessageTextParams(const AOptions: TTgEditMessageTextOptions): TTgParams;
    function ExecEditMessageText(AParams: TTgParams): ITgMessage;
    function BuildEditMessageTextVariant1Params(const AChatId: TTgChatId; AMessageId: Int64;
      const AText: string; const AOptions: TTgEditMessageTextOptions): TTgParams;
    function BuildEditMessageTextVariant2Params(const AInlineMessageId: string; const AText: string;
      const AOptions: TTgEditMessageTextOptions): TTgParams;
    function ExecEditMessageTextVariant2(AParams: TTgParams): Boolean;
    function BuildEditMessageCaptionParams(const AOptions: TTgEditMessageCaptionOptions): TTgParams;
    function ExecEditMessageCaption(AParams: TTgParams): ITgMessage;
    function BuildEditMessageCaptionVariant1Params(const AChatId: TTgChatId; AMessageId: Int64;
      const ACaption: string; const AOptions: TTgEditMessageCaptionOptions): TTgParams;
    function BuildEditMessageCaptionVariant2Params(const AInlineMessageId: string;
      const ACaption: string; const AOptions: TTgEditMessageCaptionOptions): TTgParams;
    function ExecEditMessageCaptionVariant2(AParams: TTgParams): Boolean;
    function BuildEditMessageMediaParams(const AMedia: TTgInputMedia;
      const AOptions: TTgEditMessageMediaOptions): TTgParams;
    function ExecEditMessageMedia(AParams: TTgParams): ITgMessage;
    function BuildEditMessageMediaVariant1Params(const AChatId: TTgChatId; AMessageId: Int64;
      const AMedia: TTgInputMedia; const AOptions: TTgEditMessageMediaOptions): TTgParams;
    function BuildEditMessageMediaVariant2Params(const AInlineMessageId: string;
      const AMedia: TTgInputMedia; const AOptions: TTgEditMessageMediaOptions): TTgParams;
    function ExecEditMessageMediaVariant2(AParams: TTgParams): Boolean;
    function BuildEditMessageLiveLocationParams(ALatitude: Double; ALongitude: Double;
      const AOptions: TTgEditMessageLiveLocationOptions): TTgParams;
    function ExecEditMessageLiveLocation(AParams: TTgParams): ITgMessage;
    function BuildEditMessageLiveLocationVariant1Params(const AChatId: TTgChatId; AMessageId: Int64;
      ALatitude: Double; ALongitude: Double;
      const AOptions: TTgEditMessageLiveLocationOptions): TTgParams;
    function BuildEditMessageLiveLocationVariant2Params(const AInlineMessageId: string;
      ALatitude: Double; ALongitude: Double;
      const AOptions: TTgEditMessageLiveLocationOptions): TTgParams;
    function ExecEditMessageLiveLocationVariant2(AParams: TTgParams): Boolean;
    function BuildStopMessageLiveLocationParams(const AOptions: TTgStopMessageLiveLocationOptions): TTgParams;
    function ExecStopMessageLiveLocation(AParams: TTgParams): ITgMessage;
    function BuildStopMessageLiveLocationVariant1Params(const AChatId: TTgChatId; AMessageId: Int64;
      const AOptions: TTgStopMessageLiveLocationOptions): TTgParams;
    function BuildStopMessageLiveLocationVariant2Params(const AInlineMessageId: string;
      const AOptions: TTgStopMessageLiveLocationOptions): TTgParams;
    function ExecStopMessageLiveLocationVariant2(AParams: TTgParams): Boolean;
    function BuildEditMessageChecklistParams(const ABusinessConnectionId: string;
      const AChatId: TTgChatId; AMessageId: Int64; const AChecklist: ITgInputChecklist;
      const AOptions: TTgEditMessageChecklistOptions): TTgParams;
    function ExecEditMessageChecklist(AParams: TTgParams): ITgMessage;
    function BuildEditMessageReplyMarkupParams(const AOptions: TTgEditMessageReplyMarkupOptions): TTgParams;
    function ExecEditMessageReplyMarkup(AParams: TTgParams): ITgMessage;
    function BuildEditMessageReplyMarkupVariant1Params(const AChatId: TTgChatId; AMessageId: Int64;
      const AReplyMarkup: ITgInlineKeyboardMarkup;
      const AOptions: TTgEditMessageReplyMarkupOptions): TTgParams;
    function BuildEditMessageReplyMarkupVariant2Params(const AInlineMessageId: string;
      const AReplyMarkup: ITgInlineKeyboardMarkup;
      const AOptions: TTgEditMessageReplyMarkupOptions): TTgParams;
    function ExecEditMessageReplyMarkupVariant2(AParams: TTgParams): Boolean;
    function BuildStopPollParams(const AChatId: TTgChatId; AMessageId: Int64;
      const AOptions: TTgStopPollOptions): TTgParams;
    function ExecStopPoll(AParams: TTgParams): ITgPoll;
    function BuildEditEphemeralMessageTextParams(const AChatId: TTgChatId; AReceiverUserId: Int64;
      AEphemeralMessageId: Int64; const AOptions: TTgEditEphemeralMessageTextOptions): TTgParams;
    function ExecEditEphemeralMessageText(AParams: TTgParams): Boolean;
    function BuildEditEphemeralMessageMediaParams(const AChatId: TTgChatId; AReceiverUserId: Int64;
      AEphemeralMessageId: Int64; const AMedia: TTgInputMedia;
      const AOptions: TTgEditEphemeralMessageMediaOptions): TTgParams;
    function ExecEditEphemeralMessageMedia(AParams: TTgParams): Boolean;
    function BuildEditEphemeralMessageCaptionParams(const AChatId: TTgChatId;
      AReceiverUserId: Int64; AEphemeralMessageId: Int64;
      const AOptions: TTgEditEphemeralMessageCaptionOptions): TTgParams;
    function ExecEditEphemeralMessageCaption(AParams: TTgParams): Boolean;
    function BuildEditEphemeralMessageReplyMarkupParams(const AChatId: TTgChatId;
      AReceiverUserId: Int64; AEphemeralMessageId: Int64;
      const AOptions: TTgEditEphemeralMessageReplyMarkupOptions): TTgParams;
    function ExecEditEphemeralMessageReplyMarkup(AParams: TTgParams): Boolean;
    function BuildApproveSuggestedPostParams(AChatId: Int64; AMessageId: Int64;
      const AOptions: TTgApproveSuggestedPostOptions): TTgParams;
    function ExecApproveSuggestedPost(AParams: TTgParams): Boolean;
    function BuildDeclineSuggestedPostParams(AChatId: Int64; AMessageId: Int64;
      const AOptions: TTgDeclineSuggestedPostOptions): TTgParams;
    function ExecDeclineSuggestedPost(AParams: TTgParams): Boolean;
    function BuildDeleteMessageParams(const AChatId: TTgChatId; AMessageId: Int64): TTgParams;
    function ExecDeleteMessage(AParams: TTgParams): Boolean;
    function BuildDeleteMessagesParams(const AChatId: TTgChatId;
      const AMessageIds: TArray<Int64>): TTgParams;
    function ExecDeleteMessages(AParams: TTgParams): Boolean;
    function BuildDeleteEphemeralMessageParams(const AChatId: TTgChatId; AReceiverUserId: Int64;
      AEphemeralMessageId: Int64): TTgParams;
    function ExecDeleteEphemeralMessage(AParams: TTgParams): Boolean;
    function BuildDeleteMessageReactionParams(const AChatId: TTgChatId; AMessageId: Int64;
      const AOptions: TTgDeleteMessageReactionOptions): TTgParams;
    function ExecDeleteMessageReaction(AParams: TTgParams): Boolean;
    function BuildDeleteAllMessageReactionsParams(const AChatId: TTgChatId;
      const AOptions: TTgDeleteAllMessageReactionsOptions): TTgParams;
    function ExecDeleteAllMessageReactions(AParams: TTgParams): Boolean;
    function BuildSendStickerParams(const AChatId: TTgChatId; const ASticker: TTgInputFile;
      const AOptions: TTgSendStickerOptions): TTgParams;
    function ExecSendSticker(AParams: TTgParams): ITgMessage;
    function BuildGetStickerSetParams(const AName: string): TTgParams;
    function ExecGetStickerSet(AParams: TTgParams): ITgStickerSet;
    function BuildGetCustomEmojiStickersParams(const ACustomEmojiIds: TArray<string>): TTgParams;
    function ExecGetCustomEmojiStickers(AParams: TTgParams): TArray<ITgSticker>;
    function BuildUploadStickerFileParams(AUserId: Int64; const ASticker: TTgInputFile;
      const AStickerFormat: string): TTgParams;
    function ExecUploadStickerFile(AParams: TTgParams): ITgFile;
    function BuildCreateNewStickerSetParams(AUserId: Int64; const AName: string;
      const ATitle: string; const AStickers: array of ITgInputSticker;
      const AOptions: TTgCreateNewStickerSetOptions): TTgParams;
    function ExecCreateNewStickerSet(AParams: TTgParams): Boolean;
    function BuildAddStickerToSetParams(AUserId: Int64; const AName: string;
      const ASticker: ITgInputSticker): TTgParams;
    function ExecAddStickerToSet(AParams: TTgParams): Boolean;
    function BuildSetStickerPositionInSetParams(const ASticker: string;
      APosition: Integer): TTgParams;
    function ExecSetStickerPositionInSet(AParams: TTgParams): Boolean;
    function BuildDeleteStickerFromSetParams(const ASticker: string): TTgParams;
    function ExecDeleteStickerFromSet(AParams: TTgParams): Boolean;
    function BuildReplaceStickerInSetParams(AUserId: Int64; const AName: string;
      const AOldSticker: string; const ASticker: ITgInputSticker): TTgParams;
    function ExecReplaceStickerInSet(AParams: TTgParams): Boolean;
    function BuildSetStickerEmojiListParams(const ASticker: string;
      const AEmojiList: TArray<string>): TTgParams;
    function ExecSetStickerEmojiList(AParams: TTgParams): Boolean;
    function BuildSetStickerKeywordsParams(const ASticker: string;
      const AOptions: TTgSetStickerKeywordsOptions): TTgParams;
    function ExecSetStickerKeywords(AParams: TTgParams): Boolean;
    function BuildSetStickerMaskPositionParams(const ASticker: string;
      const AOptions: TTgSetStickerMaskPositionOptions): TTgParams;
    function ExecSetStickerMaskPosition(AParams: TTgParams): Boolean;
    function BuildSetStickerSetTitleParams(const AName: string; const ATitle: string): TTgParams;
    function ExecSetStickerSetTitle(AParams: TTgParams): Boolean;
    function BuildSetStickerSetThumbnailParams(const AName: string; AUserId: Int64;
      const AFormat: string; const AOptions: TTgSetStickerSetThumbnailOptions): TTgParams;
    function ExecSetStickerSetThumbnail(AParams: TTgParams): Boolean;
    function BuildSetCustomEmojiStickerSetThumbnailParams(const AName: string;
      const AOptions: TTgSetCustomEmojiStickerSetThumbnailOptions): TTgParams;
    function ExecSetCustomEmojiStickerSetThumbnail(AParams: TTgParams): Boolean;
    function BuildDeleteStickerSetParams(const AName: string): TTgParams;
    function ExecDeleteStickerSet(AParams: TTgParams): Boolean;
    function BuildSendRichMessageParams(const AChatId: TTgChatId;
      const ARichMessage: ITgInputRichMessage;
      const AOptions: TTgSendRichMessageOptions): TTgParams;
    function ExecSendRichMessage(AParams: TTgParams): ITgMessage;
    function BuildSendRichMessageDraftParams(AChatId: Int64; ADraftId: Int64;
      const ARichMessage: ITgInputRichMessage;
      const AOptions: TTgSendRichMessageDraftOptions): TTgParams;
    function ExecSendRichMessageDraft(AParams: TTgParams): Boolean;
    function BuildAnswerInlineQueryParams(const AInlineQueryId: string;
      const AResults: array of TTgInlineQueryResult;
      const AOptions: TTgAnswerInlineQueryOptions): TTgParams;
    function ExecAnswerInlineQuery(AParams: TTgParams): Boolean;
    function BuildSendInvoiceParams(const AChatId: TTgChatId; const ATitle: string;
      const ADescription: string; const APayload: string; const ACurrency: string;
      const APrices: array of ITgLabeledPrice; const AOptions: TTgSendInvoiceOptions): TTgParams;
    function ExecSendInvoice(AParams: TTgParams): ITgMessage;
    function BuildCreateInvoiceLinkParams(const ATitle: string; const ADescription: string;
      const APayload: string; const ACurrency: string; const APrices: array of ITgLabeledPrice;
      const AOptions: TTgCreateInvoiceLinkOptions): TTgParams;
    function ExecCreateInvoiceLink(AParams: TTgParams): string;
    function BuildAnswerShippingQueryParams(const AShippingQueryId: string; AOk: Boolean;
      const AOptions: TTgAnswerShippingQueryOptions): TTgParams;
    function ExecAnswerShippingQuery(AParams: TTgParams): Boolean;
    function BuildAnswerPreCheckoutQueryParams(const APreCheckoutQueryId: string; AOk: Boolean;
      const AOptions: TTgAnswerPreCheckoutQueryOptions): TTgParams;
    function ExecAnswerPreCheckoutQuery(AParams: TTgParams): Boolean;
    function ExecGetMyStarBalance(AParams: TTgParams): ITgStarAmount;
    function BuildGetStarTransactionsParams(const AOptions: TTgGetStarTransactionsOptions): TTgParams;
    function ExecGetStarTransactions(AParams: TTgParams): ITgStarTransactions;
    function BuildRefundStarPaymentParams(AUserId: Int64;
      const ATelegramPaymentChargeId: string): TTgParams;
    function ExecRefundStarPayment(AParams: TTgParams): Boolean;
    function BuildEditUserStarSubscriptionParams(AUserId: Int64;
      const ATelegramPaymentChargeId: string; AIsCanceled: Boolean): TTgParams;
    function ExecEditUserStarSubscription(AParams: TTgParams): Boolean;
    function BuildSetPassportDataErrorsParams(AUserId: Int64;
      const AErrors: array of TTgPassportElementError): TTgParams;
    function ExecSetPassportDataErrors(AParams: TTgParams): Boolean;
    function BuildSendGameParams(const AChatId: TTgChatId; const AGameShortName: string;
      const AOptions: TTgSendGameOptions): TTgParams;
    function ExecSendGame(AParams: TTgParams): ITgMessage;
    function BuildSetGameScoreParams(AUserId: Int64; AScore: Integer;
      const AOptions: TTgSetGameScoreOptions): TTgParams;
    function ExecSetGameScore(AParams: TTgParams): ITgMessage;
    function BuildSetGameScoreVariant1Params(AUserId: Int64; AScore: Integer; AChatId: Int64;
      AMessageId: Int64; const AOptions: TTgSetGameScoreOptions): TTgParams;
    function BuildSetGameScoreVariant2Params(AUserId: Int64; AScore: Integer;
      const AInlineMessageId: string; const AOptions: TTgSetGameScoreOptions): TTgParams;
    function ExecSetGameScoreVariant2(AParams: TTgParams): Boolean;
    function BuildGetGameHighScoresParams(AUserId: Int64;
      const AOptions: TTgGetGameHighScoresOptions): TTgParams;
    function ExecGetGameHighScores(AParams: TTgParams): TArray<ITgGameHighScore>;
    function BuildGetGameHighScoresVariant1Params(AUserId: Int64; AChatId: Int64; AMessageId: Int64;
      const AOptions: TTgGetGameHighScoresOptions): TTgParams;
    function BuildGetGameHighScoresVariant2Params(AUserId: Int64; const AInlineMessageId: string;
      const AOptions: TTgGetGameHighScoresOptions): TTgParams;
  public
    /// <summary>
    ///   getUpdates: Use this method to receive incoming updates using long polling (wiki). Returns
    ///   an Array of Update objects. Элементы результата разделяют JSON всего ответа и удерживают
    ///   его; для длительного хранения отдельных элементов используйте TTgDto.Detach.
    /// </summary>
    function GetUpdates: TArray<ITgUpdate>; overload;
    function GetUpdates(const AOptions: TTgGetUpdatesOptions): TArray<ITgUpdate>; overload;
    /// <summary>
    ///   Асинхронный getUpdates: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetUpdatesAsync(const AOnSuccess: TProc<TArray<ITgUpdate>>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function GetUpdatesAsync(const AOptions: TTgGetUpdatesOptions;
      const AOnSuccess: TProc<TArray<ITgUpdate>>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>getUpdates без исключений: False и сведения об ошибке в AError.</summary>
    function TryGetUpdates(out AResult: TArray<ITgUpdate>; out AError: TTgErrorInfo): Boolean;
      overload;
    function TryGetUpdates(const AOptions: TTgGetUpdatesOptions; out AResult: TArray<ITgUpdate>;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setWebhook: Use this method to specify a URL and receive incoming updates via an outgoing
    ///   webhook. Whenever there is an update for the bot, we will send an HTTPS POST request to
    ///   the specified URL, containing a JSON-serialized Update. In case of an unsuccessful request
    ///   (a request with response HTTP status code different from 2XY), we will repeat the request
    ///   and give up after a reasonable amount of attempts. Returns True on success.
    /// </summary>
    function SetWebhook(const AUrl: string): Boolean; overload;
    function SetWebhook(const AUrl: string; const AOptions: TTgSetWebhookOptions): Boolean;
      overload;
    /// <summary>
    ///   Асинхронный setWebhook: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetWebhookAsync(const AUrl: string; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function SetWebhookAsync(const AUrl: string; const AOptions: TTgSetWebhookOptions;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>setWebhook без исключений: False и сведения об ошибке в AError.</summary>
    function TrySetWebhook(const AUrl: string; out AError: TTgErrorInfo): Boolean; overload;
    function TrySetWebhook(const AUrl: string; const AOptions: TTgSetWebhookOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   deleteWebhook: Use this method to remove webhook integration if you decide to switch back
    ///   to getUpdates. Returns True on success.
    /// </summary>
    function DeleteWebhook: Boolean; overload;
    function DeleteWebhook(const AOptions: TTgDeleteWebhookOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный deleteWebhook: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function DeleteWebhookAsync(const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function DeleteWebhookAsync(const AOptions: TTgDeleteWebhookOptions;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   deleteWebhook без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryDeleteWebhook(out AError: TTgErrorInfo): Boolean; overload;
    function TryDeleteWebhook(const AOptions: TTgDeleteWebhookOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   getWebhookInfo: Use this method to get current webhook status. Requires no parameters. On
    ///   success, returns a WebhookInfo object. If the bot is using getUpdates, will return an
    ///   object with the url field empty.
    /// </summary>
    function GetWebhookInfo: ITgWebhookInfo; overload;
    /// <summary>
    ///   Асинхронный getWebhookInfo: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetWebhookInfoAsync(const AOnSuccess: TProc<ITgWebhookInfo>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   getWebhookInfo без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryGetWebhookInfo(out AResult: ITgWebhookInfo; out AError: TTgErrorInfo): Boolean;
      overload;

    /// <summary>
    ///   getMe: A simple method for testing your bot's authentication token. Requires no
    ///   parameters. Returns basic information about the bot in form of a User object.
    /// </summary>
    function GetMe: ITgUser; overload;
    /// <summary>
    ///   Асинхронный getMe: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetMeAsync(const AOnSuccess: TProc<ITgUser>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>getMe без исключений: False и сведения об ошибке в AError.</summary>
    function TryGetMe(out AResult: ITgUser; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   logOut: Use this method to log out from the cloud Bot API server before launching the bot
    ///   locally. You must log out the bot before running it locally, otherwise there is no
    ///   guarantee that the bot will receive updates. After a successful call, you can immediately
    ///   log in on a local server, but will not be able to log in back to the cloud Bot API server
    ///   for 10 minutes. Returns True on success. Requires no parameters.
    /// </summary>
    function LogOut: Boolean; overload;
    /// <summary>
    ///   Асинхронный logOut: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function LogOutAsync(const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>logOut без исключений: False и сведения об ошибке в AError.</summary>
    function TryLogOut(out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   close: Use this method to close the bot instance before moving it from one local server to
    ///   another. You need to delete the webhook before calling this method to ensure that the bot
    ///   isn't launched again after server restart. The method will return error 429 in the first
    ///   10 minutes after the bot is launched. Returns True on success. Requires no parameters.
    /// </summary>
    function Close: Boolean; overload;
    /// <summary>
    ///   Асинхронный close: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function CloseAsync(const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>close без исключений: False и сведения об ошибке в AError.</summary>
    function TryClose(out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   sendMessage: Use this method to send text messages. On success, the sent Message is
    ///   returned.
    /// </summary>
    function SendMessage(const AChatId: TTgChatId; const AText: string): ITgMessage; overload;
    function SendMessage(const AChatId: TTgChatId; const AText: string;
      const AOptions: TTgSendMessageOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный sendMessage: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SendMessageAsync(const AChatId: TTgChatId; const AText: string;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function SendMessageAsync(const AChatId: TTgChatId; const AText: string;
      const AOptions: TTgSendMessageOptions; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>sendMessage без исключений: False и сведения об ошибке в AError.</summary>
    function TrySendMessage(const AChatId: TTgChatId; const AText: string; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;
    function TrySendMessage(const AChatId: TTgChatId; const AText: string;
      const AOptions: TTgSendMessageOptions; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   sendMessage (вариант: chat_id, text, reply_markup). Сообщение с клавиатурой. Поля AOptions
    ///   (ReplyMarkup) заменяются значениями параметров.
    /// </summary>
    function SendMessage(const AChatId: TTgChatId; const AText: string;
      const AReplyMarkup: TTgReplyMarkup): ITgMessage; overload;
    function SendMessage(const AChatId: TTgChatId; const AText: string;
      const AReplyMarkup: TTgReplyMarkup;
      const AOptions: TTgSendMessageOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный SendMessage (sendMessage, вариант): параметры проверяются и строятся в
    ///   вызывающем потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SendMessageAsync(const AChatId: TTgChatId; const AText: string;
      const AReplyMarkup: TTgReplyMarkup; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function SendMessageAsync(const AChatId: TTgChatId; const AText: string;
      const AReplyMarkup: TTgReplyMarkup; const AOptions: TTgSendMessageOptions;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   SendMessage (sendMessage, вариант) без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySendMessage(const AChatId: TTgChatId; const AText: string;
      const AReplyMarkup: TTgReplyMarkup; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;
    function TrySendMessage(const AChatId: TTgChatId; const AText: string;
      const AReplyMarkup: TTgReplyMarkup; const AOptions: TTgSendMessageOptions;
      out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   forwardMessage: Use this method to forward messages of any kind. Service messages and
    ///   messages with protected content can't be forwarded. On success, the sent Message is
    ///   returned.
    /// </summary>
    function ForwardMessage(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
      AMessageId: Int64): ITgMessage; overload;
    function ForwardMessage(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
      AMessageId: Int64; const AOptions: TTgForwardMessageOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный forwardMessage: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function ForwardMessageAsync(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
      AMessageId: Int64; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function ForwardMessageAsync(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
      AMessageId: Int64; const AOptions: TTgForwardMessageOptions;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   forwardMessage без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryForwardMessage(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
      AMessageId: Int64; out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;
    function TryForwardMessage(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
      AMessageId: Int64; const AOptions: TTgForwardMessageOptions; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   forwardMessages: Use this method to forward multiple messages of any kind. If some of the
    ///   specified messages can't be found or forwarded, they are skipped. Service messages and
    ///   messages with protected content can't be forwarded. Album grouping is kept for forwarded
    ///   messages. On success, an Array of MessageId of the sent messages is returned. Элементы
    ///   результата разделяют JSON всего ответа и удерживают его; для длительного хранения
    ///   отдельных элементов используйте TTgDto.Detach.
    /// </summary>
    function ForwardMessages(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
      const AMessageIds: TArray<Int64>): TArray<ITgMessageId>; overload;
    function ForwardMessages(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
      const AMessageIds: TArray<Int64>;
      const AOptions: TTgForwardMessagesOptions): TArray<ITgMessageId>; overload;
    /// <summary>
    ///   Асинхронный forwardMessages: параметры проверяются и строятся в вызывающем потоке (ошибки
    ///   — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function ForwardMessagesAsync(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
      const AMessageIds: TArray<Int64>; const AOnSuccess: TProc<TArray<ITgMessageId>>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function ForwardMessagesAsync(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
      const AMessageIds: TArray<Int64>; const AOptions: TTgForwardMessagesOptions;
      const AOnSuccess: TProc<TArray<ITgMessageId>>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   forwardMessages без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryForwardMessages(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
      const AMessageIds: TArray<Int64>; out AResult: TArray<ITgMessageId>;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryForwardMessages(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
      const AMessageIds: TArray<Int64>; const AOptions: TTgForwardMessagesOptions;
      out AResult: TArray<ITgMessageId>; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   copyMessage: Use this method to copy messages of any kind. Service messages, paid media
    ///   messages, giveaway messages, giveaway winners messages, and invoice messages can't be
    ///   copied. A quiz poll can be copied only if the value of the field correct_option_ids is
    ///   known to the bot. The method is analogous to the method forwardMessage, but the copied
    ///   message doesn't have a link to the original message. Returns the MessageId of the sent
    ///   message on success.
    /// </summary>
    function CopyMessage(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
      AMessageId: Int64): ITgMessageId; overload;
    function CopyMessage(const AChatId: TTgChatId; const AFromChatId: TTgChatId; AMessageId: Int64;
      const AOptions: TTgCopyMessageOptions): ITgMessageId; overload;
    /// <summary>
    ///   Асинхронный copyMessage: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function CopyMessageAsync(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
      AMessageId: Int64; const AOnSuccess: TProc<ITgMessageId>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function CopyMessageAsync(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
      AMessageId: Int64; const AOptions: TTgCopyMessageOptions;
      const AOnSuccess: TProc<ITgMessageId>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>copyMessage без исключений: False и сведения об ошибке в AError.</summary>
    function TryCopyMessage(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
      AMessageId: Int64; out AResult: ITgMessageId; out AError: TTgErrorInfo): Boolean; overload;
    function TryCopyMessage(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
      AMessageId: Int64; const AOptions: TTgCopyMessageOptions; out AResult: ITgMessageId;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   copyMessages: Use this method to copy messages of any kind. If some of the specified
    ///   messages can't be found or copied, they are skipped. Service messages, paid media
    ///   messages, giveaway messages, giveaway winners messages, and invoice messages can't be
    ///   copied. A quiz poll can be copied only if the value of the field correct_option_ids is
    ///   known to the bot. The method is analogous to the method forwardMessages, but the copied
    ///   messages don't have a link to the original message. Album grouping is kept for copied
    ///   messages. On success, an Array of MessageId of the sent messages is returned. Элементы
    ///   результата разделяют JSON всего ответа и удерживают его; для длительного хранения
    ///   отдельных элементов используйте TTgDto.Detach.
    /// </summary>
    function CopyMessages(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
      const AMessageIds: TArray<Int64>): TArray<ITgMessageId>; overload;
    function CopyMessages(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
      const AMessageIds: TArray<Int64>;
      const AOptions: TTgCopyMessagesOptions): TArray<ITgMessageId>; overload;
    /// <summary>
    ///   Асинхронный copyMessages: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function CopyMessagesAsync(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
      const AMessageIds: TArray<Int64>; const AOnSuccess: TProc<TArray<ITgMessageId>>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function CopyMessagesAsync(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
      const AMessageIds: TArray<Int64>; const AOptions: TTgCopyMessagesOptions;
      const AOnSuccess: TProc<TArray<ITgMessageId>>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>copyMessages без исключений: False и сведения об ошибке в AError.</summary>
    function TryCopyMessages(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
      const AMessageIds: TArray<Int64>; out AResult: TArray<ITgMessageId>;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryCopyMessages(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
      const AMessageIds: TArray<Int64>; const AOptions: TTgCopyMessagesOptions;
      out AResult: TArray<ITgMessageId>; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   sendPhoto: Use this method to send photos. On success, the sent Message is returned.
    /// </summary>
    function SendPhoto(const AChatId: TTgChatId; const APhoto: TTgInputFile): ITgMessage; overload;
    function SendPhoto(const AChatId: TTgChatId; const APhoto: TTgInputFile;
      const AOptions: TTgSendPhotoOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный sendPhoto: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SendPhotoAsync(const AChatId: TTgChatId; const APhoto: TTgInputFile;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function SendPhotoAsync(const AChatId: TTgChatId; const APhoto: TTgInputFile;
      const AOptions: TTgSendPhotoOptions; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>sendPhoto без исключений: False и сведения об ошибке в AError.</summary>
    function TrySendPhoto(const AChatId: TTgChatId; const APhoto: TTgInputFile;
      out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;
    function TrySendPhoto(const AChatId: TTgChatId; const APhoto: TTgInputFile;
      const AOptions: TTgSendPhotoOptions; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   sendPhoto (вариант: chat_id, photo, caption). Фото с подписью. Поля AOptions (Caption)
    ///   заменяются значениями параметров.
    /// </summary>
    function SendPhoto(const AChatId: TTgChatId; const APhoto: TTgInputFile;
      const ACaption: string): ITgMessage; overload;
    function SendPhoto(const AChatId: TTgChatId; const APhoto: TTgInputFile; const ACaption: string;
      const AOptions: TTgSendPhotoOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный SendPhoto (sendPhoto, вариант): параметры проверяются и строятся в вызывающем
    ///   потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SendPhotoAsync(const AChatId: TTgChatId; const APhoto: TTgInputFile;
      const ACaption: string; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function SendPhotoAsync(const AChatId: TTgChatId; const APhoto: TTgInputFile;
      const ACaption: string; const AOptions: TTgSendPhotoOptions;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   SendPhoto (sendPhoto, вариант) без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySendPhoto(const AChatId: TTgChatId; const APhoto: TTgInputFile;
      const ACaption: string; out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;
    function TrySendPhoto(const AChatId: TTgChatId; const APhoto: TTgInputFile;
      const ACaption: string; const AOptions: TTgSendPhotoOptions; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   sendLivePhoto: Use this method to send live photos. On success, the sent Message is
    ///   returned.
    /// </summary>
    function SendLivePhoto(const AChatId: TTgChatId; const ALivePhoto: TTgInputFile;
      const APhoto: TTgInputFile): ITgMessage; overload;
    function SendLivePhoto(const AChatId: TTgChatId; const ALivePhoto: TTgInputFile;
      const APhoto: TTgInputFile; const AOptions: TTgSendLivePhotoOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный sendLivePhoto: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SendLivePhotoAsync(const AChatId: TTgChatId; const ALivePhoto: TTgInputFile;
      const APhoto: TTgInputFile; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function SendLivePhotoAsync(const AChatId: TTgChatId; const ALivePhoto: TTgInputFile;
      const APhoto: TTgInputFile; const AOptions: TTgSendLivePhotoOptions;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   sendLivePhoto без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySendLivePhoto(const AChatId: TTgChatId; const ALivePhoto: TTgInputFile;
      const APhoto: TTgInputFile; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;
    function TrySendLivePhoto(const AChatId: TTgChatId; const ALivePhoto: TTgInputFile;
      const APhoto: TTgInputFile; const AOptions: TTgSendLivePhotoOptions; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   sendAudio: Use this method to send audio files, if you want Telegram clients to display
    ///   them in the music player. Your audio must be in the .MP3 or .M4A format. On success, the
    ///   sent Message is returned. Bots can currently send audio files of up to 50 MB in size, this
    ///   limit may be changed in the future.
    /// </summary>
    function SendAudio(const AChatId: TTgChatId; const AAudio: TTgInputFile): ITgMessage; overload;
    function SendAudio(const AChatId: TTgChatId; const AAudio: TTgInputFile;
      const AOptions: TTgSendAudioOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный sendAudio: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SendAudioAsync(const AChatId: TTgChatId; const AAudio: TTgInputFile;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function SendAudioAsync(const AChatId: TTgChatId; const AAudio: TTgInputFile;
      const AOptions: TTgSendAudioOptions; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>sendAudio без исключений: False и сведения об ошибке в AError.</summary>
    function TrySendAudio(const AChatId: TTgChatId; const AAudio: TTgInputFile;
      out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;
    function TrySendAudio(const AChatId: TTgChatId; const AAudio: TTgInputFile;
      const AOptions: TTgSendAudioOptions; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   sendDocument: Use this method to send general files. On success, the sent Message is
    ///   returned. Bots can currently send files of any type of up to 50 MB in size, this limit may
    ///   be changed in the future.
    /// </summary>
    function SendDocument(const AChatId: TTgChatId; const ADocument: TTgInputFile): ITgMessage;
      overload;
    function SendDocument(const AChatId: TTgChatId; const ADocument: TTgInputFile;
      const AOptions: TTgSendDocumentOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный sendDocument: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SendDocumentAsync(const AChatId: TTgChatId; const ADocument: TTgInputFile;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function SendDocumentAsync(const AChatId: TTgChatId; const ADocument: TTgInputFile;
      const AOptions: TTgSendDocumentOptions; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>sendDocument без исключений: False и сведения об ошибке в AError.</summary>
    function TrySendDocument(const AChatId: TTgChatId; const ADocument: TTgInputFile;
      out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;
    function TrySendDocument(const AChatId: TTgChatId; const ADocument: TTgInputFile;
      const AOptions: TTgSendDocumentOptions; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   sendDocument (вариант: chat_id, document, caption). Документ с подписью. Поля AOptions
    ///   (Caption) заменяются значениями параметров.
    /// </summary>
    function SendDocument(const AChatId: TTgChatId; const ADocument: TTgInputFile;
      const ACaption: string): ITgMessage; overload;
    function SendDocument(const AChatId: TTgChatId; const ADocument: TTgInputFile;
      const ACaption: string; const AOptions: TTgSendDocumentOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный SendDocument (sendDocument, вариант): параметры проверяются и строятся в
    ///   вызывающем потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SendDocumentAsync(const AChatId: TTgChatId; const ADocument: TTgInputFile;
      const ACaption: string; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function SendDocumentAsync(const AChatId: TTgChatId; const ADocument: TTgInputFile;
      const ACaption: string; const AOptions: TTgSendDocumentOptions;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   SendDocument (sendDocument, вариант) без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySendDocument(const AChatId: TTgChatId; const ADocument: TTgInputFile;
      const ACaption: string; out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;
    function TrySendDocument(const AChatId: TTgChatId; const ADocument: TTgInputFile;
      const ACaption: string; const AOptions: TTgSendDocumentOptions; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   sendVideo: Use this method to send video files, Telegram clients support MPEG4 videos
    ///   (other formats may be sent as Document). On success, the sent Message is returned. Bots
    ///   can currently send video files of up to 50 MB in size, this limit may be changed in the
    ///   future.
    /// </summary>
    function SendVideo(const AChatId: TTgChatId; const AVideo: TTgInputFile): ITgMessage; overload;
    function SendVideo(const AChatId: TTgChatId; const AVideo: TTgInputFile;
      const AOptions: TTgSendVideoOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный sendVideo: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SendVideoAsync(const AChatId: TTgChatId; const AVideo: TTgInputFile;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function SendVideoAsync(const AChatId: TTgChatId; const AVideo: TTgInputFile;
      const AOptions: TTgSendVideoOptions; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>sendVideo без исключений: False и сведения об ошибке в AError.</summary>
    function TrySendVideo(const AChatId: TTgChatId; const AVideo: TTgInputFile;
      out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;
    function TrySendVideo(const AChatId: TTgChatId; const AVideo: TTgInputFile;
      const AOptions: TTgSendVideoOptions; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   sendAnimation: Use this method to send animation files (GIF or H.264/MPEG-4 AVC video
    ///   without sound). On success, the sent Message is returned. Bots can currently send
    ///   animation files of up to 50 MB in size, this limit may be changed in the future.
    /// </summary>
    function SendAnimation(const AChatId: TTgChatId; const AAnimation: TTgInputFile): ITgMessage;
      overload;
    function SendAnimation(const AChatId: TTgChatId; const AAnimation: TTgInputFile;
      const AOptions: TTgSendAnimationOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный sendAnimation: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SendAnimationAsync(const AChatId: TTgChatId; const AAnimation: TTgInputFile;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function SendAnimationAsync(const AChatId: TTgChatId; const AAnimation: TTgInputFile;
      const AOptions: TTgSendAnimationOptions; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   sendAnimation без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySendAnimation(const AChatId: TTgChatId; const AAnimation: TTgInputFile;
      out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;
    function TrySendAnimation(const AChatId: TTgChatId; const AAnimation: TTgInputFile;
      const AOptions: TTgSendAnimationOptions; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   sendVoice: Use this method to send audio files, if you want Telegram clients to display
    ///   the file as a playable voice message. For this to work, your audio must be in an .OGG file
    ///   encoded with OPUS, or in .MP3 format, or in .M4A format (other formats may be sent as
    ///   Audio or Document). On success, the sent Message is returned. Bots can currently send
    ///   voice messages of up to 50 MB in size, this limit may be changed in the future.
    /// </summary>
    function SendVoice(const AChatId: TTgChatId; const AVoice: TTgInputFile): ITgMessage; overload;
    function SendVoice(const AChatId: TTgChatId; const AVoice: TTgInputFile;
      const AOptions: TTgSendVoiceOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный sendVoice: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SendVoiceAsync(const AChatId: TTgChatId; const AVoice: TTgInputFile;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function SendVoiceAsync(const AChatId: TTgChatId; const AVoice: TTgInputFile;
      const AOptions: TTgSendVoiceOptions; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>sendVoice без исключений: False и сведения об ошибке в AError.</summary>
    function TrySendVoice(const AChatId: TTgChatId; const AVoice: TTgInputFile;
      out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;
    function TrySendVoice(const AChatId: TTgChatId; const AVoice: TTgInputFile;
      const AOptions: TTgSendVoiceOptions; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   sendVideoNote: Use this method to send a rounded square MPEG4 video of up to 1 minute
    ///   long. On success, the sent Message is returned.
    /// </summary>
    function SendVideoNote(const AChatId: TTgChatId; const AVideoNote: TTgInputFile): ITgMessage;
      overload;
    function SendVideoNote(const AChatId: TTgChatId; const AVideoNote: TTgInputFile;
      const AOptions: TTgSendVideoNoteOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный sendVideoNote: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SendVideoNoteAsync(const AChatId: TTgChatId; const AVideoNote: TTgInputFile;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function SendVideoNoteAsync(const AChatId: TTgChatId; const AVideoNote: TTgInputFile;
      const AOptions: TTgSendVideoNoteOptions; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   sendVideoNote без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySendVideoNote(const AChatId: TTgChatId; const AVideoNote: TTgInputFile;
      out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;
    function TrySendVideoNote(const AChatId: TTgChatId; const AVideoNote: TTgInputFile;
      const AOptions: TTgSendVideoNoteOptions; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   sendPaidMedia: Use this method to send paid media. On success, the sent Message is
    ///   returned.
    /// </summary>
    function SendPaidMedia(const AChatId: TTgChatId; AStarCount: Integer;
      const AMedia: array of TTgInputPaidMedia): ITgMessage; overload;
    function SendPaidMedia(const AChatId: TTgChatId; AStarCount: Integer;
      const AMedia: array of TTgInputPaidMedia;
      const AOptions: TTgSendPaidMediaOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный sendPaidMedia: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SendPaidMediaAsync(const AChatId: TTgChatId; AStarCount: Integer;
      const AMedia: array of TTgInputPaidMedia; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function SendPaidMediaAsync(const AChatId: TTgChatId; AStarCount: Integer;
      const AMedia: array of TTgInputPaidMedia; const AOptions: TTgSendPaidMediaOptions;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   sendPaidMedia без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySendPaidMedia(const AChatId: TTgChatId; AStarCount: Integer;
      const AMedia: array of TTgInputPaidMedia; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;
    function TrySendPaidMedia(const AChatId: TTgChatId; AStarCount: Integer;
      const AMedia: array of TTgInputPaidMedia; const AOptions: TTgSendPaidMediaOptions;
      out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   sendMediaGroup: Use this method to send a group of photos, live photos, videos, documents
    ///   or audios as an album. Documents and audio files can be only grouped in an album with
    ///   messages of the same type. On success, an Array of Message objects that were sent is
    ///   returned. Элементы результата разделяют JSON всего ответа и удерживают его; для
    ///   длительного хранения отдельных элементов используйте TTgDto.Detach.
    /// </summary>
    function SendMediaGroup(const AChatId: TTgChatId;
      const AMedia: array of TTgMediaGroupItem): TArray<ITgMessage>; overload;
    function SendMediaGroup(const AChatId: TTgChatId; const AMedia: array of TTgMediaGroupItem;
      const AOptions: TTgSendMediaGroupOptions): TArray<ITgMessage>; overload;
    /// <summary>
    ///   Асинхронный sendMediaGroup: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SendMediaGroupAsync(const AChatId: TTgChatId; const AMedia: array of TTgMediaGroupItem;
      const AOnSuccess: TProc<TArray<ITgMessage>>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function SendMediaGroupAsync(const AChatId: TTgChatId; const AMedia: array of TTgMediaGroupItem;
      const AOptions: TTgSendMediaGroupOptions; const AOnSuccess: TProc<TArray<ITgMessage>>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   sendMediaGroup без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySendMediaGroup(const AChatId: TTgChatId; const AMedia: array of TTgMediaGroupItem;
      out AResult: TArray<ITgMessage>; out AError: TTgErrorInfo): Boolean; overload;
    function TrySendMediaGroup(const AChatId: TTgChatId; const AMedia: array of TTgMediaGroupItem;
      const AOptions: TTgSendMediaGroupOptions; out AResult: TArray<ITgMessage>;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   sendLocation: Use this method to send point on the map. On success, the sent Message is
    ///   returned.
    /// </summary>
    function SendLocation(const AChatId: TTgChatId; ALatitude: Double;
      ALongitude: Double): ITgMessage; overload;
    function SendLocation(const AChatId: TTgChatId; ALatitude: Double; ALongitude: Double;
      const AOptions: TTgSendLocationOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный sendLocation: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SendLocationAsync(const AChatId: TTgChatId; ALatitude: Double; ALongitude: Double;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function SendLocationAsync(const AChatId: TTgChatId; ALatitude: Double; ALongitude: Double;
      const AOptions: TTgSendLocationOptions; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>sendLocation без исключений: False и сведения об ошибке в AError.</summary>
    function TrySendLocation(const AChatId: TTgChatId; ALatitude: Double; ALongitude: Double;
      out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;
    function TrySendLocation(const AChatId: TTgChatId; ALatitude: Double; ALongitude: Double;
      const AOptions: TTgSendLocationOptions; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   sendVenue: Use this method to send information about a venue. On success, the sent Message
    ///   is returned.
    /// </summary>
    function SendVenue(const AChatId: TTgChatId; ALatitude: Double; ALongitude: Double;
      const ATitle: string; const AAddress: string): ITgMessage; overload;
    function SendVenue(const AChatId: TTgChatId; ALatitude: Double; ALongitude: Double;
      const ATitle: string; const AAddress: string;
      const AOptions: TTgSendVenueOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный sendVenue: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SendVenueAsync(const AChatId: TTgChatId; ALatitude: Double; ALongitude: Double;
      const ATitle: string; const AAddress: string; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function SendVenueAsync(const AChatId: TTgChatId; ALatitude: Double; ALongitude: Double;
      const ATitle: string; const AAddress: string; const AOptions: TTgSendVenueOptions;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>sendVenue без исключений: False и сведения об ошибке в AError.</summary>
    function TrySendVenue(const AChatId: TTgChatId; ALatitude: Double; ALongitude: Double;
      const ATitle: string; const AAddress: string; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;
    function TrySendVenue(const AChatId: TTgChatId; ALatitude: Double; ALongitude: Double;
      const ATitle: string; const AAddress: string; const AOptions: TTgSendVenueOptions;
      out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   sendContact: Use this method to send phone contacts. On success, the sent Message is
    ///   returned.
    /// </summary>
    function SendContact(const AChatId: TTgChatId; const APhoneNumber: string;
      const AFirstName: string): ITgMessage; overload;
    function SendContact(const AChatId: TTgChatId; const APhoneNumber: string;
      const AFirstName: string; const AOptions: TTgSendContactOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный sendContact: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SendContactAsync(const AChatId: TTgChatId; const APhoneNumber: string;
      const AFirstName: string; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function SendContactAsync(const AChatId: TTgChatId; const APhoneNumber: string;
      const AFirstName: string; const AOptions: TTgSendContactOptions;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>sendContact без исключений: False и сведения об ошибке в AError.</summary>
    function TrySendContact(const AChatId: TTgChatId; const APhoneNumber: string;
      const AFirstName: string; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;
    function TrySendContact(const AChatId: TTgChatId; const APhoneNumber: string;
      const AFirstName: string; const AOptions: TTgSendContactOptions; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   sendPoll: Use this method to send a native poll. On success, the sent Message is returned.
    /// </summary>
    function SendPoll(const AChatId: TTgChatId; const AQuestion: string;
      const APollOptions: array of ITgInputPollOption): ITgMessage; overload;
    function SendPoll(const AChatId: TTgChatId; const AQuestion: string;
      const APollOptions: array of ITgInputPollOption;
      const AOptions: TTgSendPollOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный sendPoll: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SendPollAsync(const AChatId: TTgChatId; const AQuestion: string;
      const APollOptions: array of ITgInputPollOption; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function SendPollAsync(const AChatId: TTgChatId; const AQuestion: string;
      const APollOptions: array of ITgInputPollOption; const AOptions: TTgSendPollOptions;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>sendPoll без исключений: False и сведения об ошибке в AError.</summary>
    function TrySendPoll(const AChatId: TTgChatId; const AQuestion: string;
      const APollOptions: array of ITgInputPollOption; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;
    function TrySendPoll(const AChatId: TTgChatId; const AQuestion: string;
      const APollOptions: array of ITgInputPollOption; const AOptions: TTgSendPollOptions;
      out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   sendChecklist: Use this method to send a checklist on behalf of a connected business
    ///   account. On success, the sent Message is returned.
    /// </summary>
    function SendChecklist(const ABusinessConnectionId: string; const AChatId: TTgChatId;
      const AChecklist: ITgInputChecklist): ITgMessage; overload;
    function SendChecklist(const ABusinessConnectionId: string; const AChatId: TTgChatId;
      const AChecklist: ITgInputChecklist;
      const AOptions: TTgSendChecklistOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный sendChecklist: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SendChecklistAsync(const ABusinessConnectionId: string; const AChatId: TTgChatId;
      const AChecklist: ITgInputChecklist; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function SendChecklistAsync(const ABusinessConnectionId: string; const AChatId: TTgChatId;
      const AChecklist: ITgInputChecklist; const AOptions: TTgSendChecklistOptions;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   sendChecklist без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySendChecklist(const ABusinessConnectionId: string; const AChatId: TTgChatId;
      const AChecklist: ITgInputChecklist; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;
    function TrySendChecklist(const ABusinessConnectionId: string; const AChatId: TTgChatId;
      const AChecklist: ITgInputChecklist; const AOptions: TTgSendChecklistOptions;
      out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   sendDice: Use this method to send an animated emoji that will display a random value. On
    ///   success, the sent Message is returned.
    /// </summary>
    function SendDice(const AChatId: TTgChatId): ITgMessage; overload;
    function SendDice(const AChatId: TTgChatId; const AOptions: TTgSendDiceOptions): ITgMessage;
      overload;
    /// <summary>
    ///   Асинхронный sendDice: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SendDiceAsync(const AChatId: TTgChatId; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function SendDiceAsync(const AChatId: TTgChatId; const AOptions: TTgSendDiceOptions;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>sendDice без исключений: False и сведения об ошибке в AError.</summary>
    function TrySendDice(const AChatId: TTgChatId; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;
    function TrySendDice(const AChatId: TTgChatId; const AOptions: TTgSendDiceOptions;
      out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   sendMessageDraft: Use this method to stream a partial message to a user while the message
    ///   is being generated. Note that the streamed draft is ephemeral and acts as a temporary
    ///   30-second preview - once the output is finalized, you must call sendMessage with the
    ///   complete message to persist it in the user's chat. Returns True on success.
    /// </summary>
    function SendMessageDraft(AChatId: Int64; ADraftId: Int64): Boolean; overload;
    function SendMessageDraft(AChatId: Int64; ADraftId: Int64;
      const AOptions: TTgSendMessageDraftOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный sendMessageDraft: параметры проверяются и строятся в вызывающем потоке (ошибки
    ///   — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SendMessageDraftAsync(AChatId: Int64; ADraftId: Int64;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function SendMessageDraftAsync(AChatId: Int64; ADraftId: Int64;
      const AOptions: TTgSendMessageDraftOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   sendMessageDraft без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySendMessageDraft(AChatId: Int64; ADraftId: Int64;
      out AError: TTgErrorInfo): Boolean; overload;
    function TrySendMessageDraft(AChatId: Int64; ADraftId: Int64;
      const AOptions: TTgSendMessageDraftOptions; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   sendChatAction: Use this method when you need to tell the user that something is happening
    ///   on the bot's side. The status is set for 5 seconds or less (when a message arrives from
    ///   your bot, Telegram clients clear its typing status). Returns True on success.
    /// </summary>
    function SendChatAction(const AChatId: TTgChatId; const AAction: string): Boolean; overload;
    function SendChatAction(const AChatId: TTgChatId; const AAction: string;
      const AOptions: TTgSendChatActionOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный sendChatAction: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SendChatActionAsync(const AChatId: TTgChatId; const AAction: string;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function SendChatActionAsync(const AChatId: TTgChatId; const AAction: string;
      const AOptions: TTgSendChatActionOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   sendChatAction без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySendChatAction(const AChatId: TTgChatId; const AAction: string;
      out AError: TTgErrorInfo): Boolean; overload;
    function TrySendChatAction(const AChatId: TTgChatId; const AAction: string;
      const AOptions: TTgSendChatActionOptions; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setMessageReaction: Use this method to change the chosen reactions on a message. Service
    ///   messages of some types can't be reacted to. Automatically forwarded messages from a
    ///   channel to its discussion group have the same available reactions as messages in the
    ///   channel. Bots can't use paid reactions. Returns True on success.
    /// </summary>
    function SetMessageReaction(const AChatId: TTgChatId; AMessageId: Int64): Boolean; overload;
    function SetMessageReaction(const AChatId: TTgChatId; AMessageId: Int64;
      const AOptions: TTgSetMessageReactionOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный setMessageReaction: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetMessageReactionAsync(const AChatId: TTgChatId; AMessageId: Int64;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function SetMessageReactionAsync(const AChatId: TTgChatId; AMessageId: Int64;
      const AOptions: TTgSetMessageReactionOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   setMessageReaction без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySetMessageReaction(const AChatId: TTgChatId; AMessageId: Int64;
      out AError: TTgErrorInfo): Boolean; overload;
    function TrySetMessageReaction(const AChatId: TTgChatId; AMessageId: Int64;
      const AOptions: TTgSetMessageReactionOptions; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   getUserProfilePhotos: Use this method to get a list of profile pictures for a user.
    ///   Returns a UserProfilePhotos object.
    /// </summary>
    function GetUserProfilePhotos(AUserId: Int64): ITgUserProfilePhotos; overload;
    function GetUserProfilePhotos(AUserId: Int64;
      const AOptions: TTgGetUserProfilePhotosOptions): ITgUserProfilePhotos; overload;
    /// <summary>
    ///   Асинхронный getUserProfilePhotos: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetUserProfilePhotosAsync(AUserId: Int64;
      const AOnSuccess: TProc<ITgUserProfilePhotos>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function GetUserProfilePhotosAsync(AUserId: Int64;
      const AOptions: TTgGetUserProfilePhotosOptions; const AOnSuccess: TProc<ITgUserProfilePhotos>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   getUserProfilePhotos без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryGetUserProfilePhotos(AUserId: Int64; out AResult: ITgUserProfilePhotos;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryGetUserProfilePhotos(AUserId: Int64; const AOptions: TTgGetUserProfilePhotosOptions;
      out AResult: ITgUserProfilePhotos; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   getUserProfileAudios: Use this method to get a list of profile audios for a user. Returns
    ///   a UserProfileAudios object.
    /// </summary>
    function GetUserProfileAudios(AUserId: Int64): ITgUserProfileAudios; overload;
    function GetUserProfileAudios(AUserId: Int64;
      const AOptions: TTgGetUserProfileAudiosOptions): ITgUserProfileAudios; overload;
    /// <summary>
    ///   Асинхронный getUserProfileAudios: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetUserProfileAudiosAsync(AUserId: Int64;
      const AOnSuccess: TProc<ITgUserProfileAudios>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function GetUserProfileAudiosAsync(AUserId: Int64;
      const AOptions: TTgGetUserProfileAudiosOptions; const AOnSuccess: TProc<ITgUserProfileAudios>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   getUserProfileAudios без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryGetUserProfileAudios(AUserId: Int64; out AResult: ITgUserProfileAudios;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryGetUserProfileAudios(AUserId: Int64; const AOptions: TTgGetUserProfileAudiosOptions;
      out AResult: ITgUserProfileAudios; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setUserEmojiStatus: Changes the emoji status for a given user that previously allowed the
    ///   bot to manage their emoji status via the Mini App method requestEmojiStatusAccess. Returns
    ///   True on success.
    /// </summary>
    function SetUserEmojiStatus(AUserId: Int64): Boolean; overload;
    function SetUserEmojiStatus(AUserId: Int64;
      const AOptions: TTgSetUserEmojiStatusOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный setUserEmojiStatus: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetUserEmojiStatusAsync(AUserId: Int64; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function SetUserEmojiStatusAsync(AUserId: Int64; const AOptions: TTgSetUserEmojiStatusOptions;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   setUserEmojiStatus без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySetUserEmojiStatus(AUserId: Int64; out AError: TTgErrorInfo): Boolean; overload;
    function TrySetUserEmojiStatus(AUserId: Int64; const AOptions: TTgSetUserEmojiStatusOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   getFile: Use this method to get basic information about a file and prepare it for
    ///   downloading. For the moment, bots can download files of up to 20MB in size. On success, a
    ///   File object is returned. The file can then be downloaded via the link
    ///   https://api.telegram.org/file/bot&lt;token&gt;/&lt;file_path&gt;, where &lt;file_path&gt;
    ///   is taken from the response. It is guaranteed that the link will be valid for at least 1
    ///   hour. When the link expires, a new one can be requested by calling getFile again.
    /// </summary>
    function GetFile(const AFileId: string): ITgFile; overload;
    /// <summary>
    ///   Асинхронный getFile: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetFileAsync(const AFileId: string; const AOnSuccess: TProc<ITgFile>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>getFile без исключений: False и сведения об ошибке в AError.</summary>
    function TryGetFile(const AFileId: string; out AResult: ITgFile;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   banChatMember: Use this method to ban a user in a group, a supergroup or a channel. In the
    ///   case of supergroups and channels, the user will not be able to return to the chat on their
    ///   own using invite links, etc., unless unbanned first. The bot must be an administrator in
    ///   the chat for this to work and must have the appropriate administrator rights. Returns True
    ///   on success.
    /// </summary>
    function BanChatMember(const AChatId: TTgChatId; AUserId: Int64): Boolean; overload;
    function BanChatMember(const AChatId: TTgChatId; AUserId: Int64;
      const AOptions: TTgBanChatMemberOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный banChatMember: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function BanChatMemberAsync(const AChatId: TTgChatId; AUserId: Int64;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function BanChatMemberAsync(const AChatId: TTgChatId; AUserId: Int64;
      const AOptions: TTgBanChatMemberOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   banChatMember без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryBanChatMember(const AChatId: TTgChatId; AUserId: Int64;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryBanChatMember(const AChatId: TTgChatId; AUserId: Int64;
      const AOptions: TTgBanChatMemberOptions; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   unbanChatMember: Use this method to unban a previously banned user in a supergroup or
    ///   channel. The user will not return to the group or channel automatically, but will be able
    ///   to join via link, etc. The bot must be an administrator for this to work. By default, this
    ///   method guarantees that after the call the user is not a member of the chat, but will be
    ///   able to join it. So if the user is a member of the chat they will also be removed from the
    ///   chat. If you don't want this, use the parameter only_if_banned. Returns True on success.
    /// </summary>
    function UnbanChatMember(const AChatId: TTgChatId; AUserId: Int64): Boolean; overload;
    function UnbanChatMember(const AChatId: TTgChatId; AUserId: Int64;
      const AOptions: TTgUnbanChatMemberOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный unbanChatMember: параметры проверяются и строятся в вызывающем потоке (ошибки
    ///   — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function UnbanChatMemberAsync(const AChatId: TTgChatId; AUserId: Int64;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function UnbanChatMemberAsync(const AChatId: TTgChatId; AUserId: Int64;
      const AOptions: TTgUnbanChatMemberOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   unbanChatMember без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryUnbanChatMember(const AChatId: TTgChatId; AUserId: Int64;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryUnbanChatMember(const AChatId: TTgChatId; AUserId: Int64;
      const AOptions: TTgUnbanChatMemberOptions; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   restrictChatMember: Use this method to restrict a user in a supergroup. The bot must be an
    ///   administrator in the supergroup for this to work and must have the appropriate
    ///   administrator rights. Pass True for all permissions to lift restrictions from a user.
    ///   Returns True on success.
    /// </summary>
    function RestrictChatMember(const AChatId: TTgChatId; AUserId: Int64;
      const APermissions: ITgChatPermissions): Boolean; overload;
    function RestrictChatMember(const AChatId: TTgChatId; AUserId: Int64;
      const APermissions: ITgChatPermissions;
      const AOptions: TTgRestrictChatMemberOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный restrictChatMember: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function RestrictChatMemberAsync(const AChatId: TTgChatId; AUserId: Int64;
      const APermissions: ITgChatPermissions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function RestrictChatMemberAsync(const AChatId: TTgChatId; AUserId: Int64;
      const APermissions: ITgChatPermissions; const AOptions: TTgRestrictChatMemberOptions;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   restrictChatMember без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryRestrictChatMember(const AChatId: TTgChatId; AUserId: Int64;
      const APermissions: ITgChatPermissions; out AError: TTgErrorInfo): Boolean; overload;
    function TryRestrictChatMember(const AChatId: TTgChatId; AUserId: Int64;
      const APermissions: ITgChatPermissions; const AOptions: TTgRestrictChatMemberOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   promoteChatMember: Use this method to promote or demote a user in a supergroup or a
    ///   channel. The bot must be an administrator in the chat for this to work and must have the
    ///   appropriate administrator rights. Pass False for all boolean parameters to demote a user.
    ///   Returns True on success.
    /// </summary>
    function PromoteChatMember(const AChatId: TTgChatId; AUserId: Int64): Boolean; overload;
    function PromoteChatMember(const AChatId: TTgChatId; AUserId: Int64;
      const AOptions: TTgPromoteChatMemberOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный promoteChatMember: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function PromoteChatMemberAsync(const AChatId: TTgChatId; AUserId: Int64;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function PromoteChatMemberAsync(const AChatId: TTgChatId; AUserId: Int64;
      const AOptions: TTgPromoteChatMemberOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   promoteChatMember без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryPromoteChatMember(const AChatId: TTgChatId; AUserId: Int64;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryPromoteChatMember(const AChatId: TTgChatId; AUserId: Int64;
      const AOptions: TTgPromoteChatMemberOptions; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setChatAdministratorCustomTitle: Use this method to set a custom title for an
    ///   administrator in a supergroup promoted by the bot. Returns True on success.
    /// </summary>
    function SetChatAdministratorCustomTitle(const AChatId: TTgChatId; AUserId: Int64;
      const ACustomTitle: string): Boolean; overload;
    /// <summary>
    ///   Асинхронный setChatAdministratorCustomTitle: параметры проверяются и строятся в вызывающем
    ///   потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetChatAdministratorCustomTitleAsync(const AChatId: TTgChatId; AUserId: Int64;
      const ACustomTitle: string; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   setChatAdministratorCustomTitle без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySetChatAdministratorCustomTitle(const AChatId: TTgChatId; AUserId: Int64;
      const ACustomTitle: string; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setChatMemberTag: Use this method to set a tag for a regular member in a group or a
    ///   supergroup. The bot must be an administrator in the chat for this to work and must have
    ///   the can_manage_tags administrator right. Returns True on success.
    /// </summary>
    function SetChatMemberTag(const AChatId: TTgChatId; AUserId: Int64): Boolean; overload;
    function SetChatMemberTag(const AChatId: TTgChatId; AUserId: Int64;
      const AOptions: TTgSetChatMemberTagOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный setChatMemberTag: параметры проверяются и строятся в вызывающем потоке (ошибки
    ///   — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetChatMemberTagAsync(const AChatId: TTgChatId; AUserId: Int64;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function SetChatMemberTagAsync(const AChatId: TTgChatId; AUserId: Int64;
      const AOptions: TTgSetChatMemberTagOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   setChatMemberTag без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySetChatMemberTag(const AChatId: TTgChatId; AUserId: Int64;
      out AError: TTgErrorInfo): Boolean; overload;
    function TrySetChatMemberTag(const AChatId: TTgChatId; AUserId: Int64;
      const AOptions: TTgSetChatMemberTagOptions; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   banChatSenderChat: Use this method to ban a channel chat in a supergroup or a channel.
    ///   Until the chat is unbanned, the owner of the banned chat won't be able to send messages on
    ///   behalf of any of their channels. The bot must be an administrator in the supergroup or
    ///   channel for this to work and must have the appropriate administrator rights. Returns True
    ///   on success.
    /// </summary>
    function BanChatSenderChat(const AChatId: TTgChatId; ASenderChatId: Int64): Boolean; overload;
    /// <summary>
    ///   Асинхронный banChatSenderChat: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function BanChatSenderChatAsync(const AChatId: TTgChatId; ASenderChatId: Int64;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   banChatSenderChat без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryBanChatSenderChat(const AChatId: TTgChatId; ASenderChatId: Int64;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   unbanChatSenderChat: Use this method to unban a previously banned channel chat in a
    ///   supergroup or channel. The bot must be an administrator for this to work and must have the
    ///   appropriate administrator rights. Returns True on success.
    /// </summary>
    function UnbanChatSenderChat(const AChatId: TTgChatId; ASenderChatId: Int64): Boolean; overload;
    /// <summary>
    ///   Асинхронный unbanChatSenderChat: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function UnbanChatSenderChatAsync(const AChatId: TTgChatId; ASenderChatId: Int64;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   unbanChatSenderChat без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryUnbanChatSenderChat(const AChatId: TTgChatId; ASenderChatId: Int64;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setChatPermissions: Use this method to set default chat permissions for all members. The
    ///   bot must be an administrator in the group or a supergroup for this to work and must have
    ///   the can_restrict_members administrator rights. Returns True on success.
    /// </summary>
    function SetChatPermissions(const AChatId: TTgChatId;
      const APermissions: ITgChatPermissions): Boolean; overload;
    function SetChatPermissions(const AChatId: TTgChatId; const APermissions: ITgChatPermissions;
      const AOptions: TTgSetChatPermissionsOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный setChatPermissions: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetChatPermissionsAsync(const AChatId: TTgChatId;
      const APermissions: ITgChatPermissions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function SetChatPermissionsAsync(const AChatId: TTgChatId;
      const APermissions: ITgChatPermissions; const AOptions: TTgSetChatPermissionsOptions;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   setChatPermissions без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySetChatPermissions(const AChatId: TTgChatId; const APermissions: ITgChatPermissions;
      out AError: TTgErrorInfo): Boolean; overload;
    function TrySetChatPermissions(const AChatId: TTgChatId; const APermissions: ITgChatPermissions;
      const AOptions: TTgSetChatPermissionsOptions; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   exportChatInviteLink: Use this method to generate a new primary invite link for a chat;
    ///   any previously generated primary link is revoked. The bot must be an administrator in the
    ///   chat for this to work and must have the appropriate administrator rights. Returns the new
    ///   invite link as String on success.
    /// </summary>
    function ExportChatInviteLink(const AChatId: TTgChatId): string; overload;
    /// <summary>
    ///   Асинхронный exportChatInviteLink: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function ExportChatInviteLinkAsync(const AChatId: TTgChatId; const AOnSuccess: TProc<string>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   exportChatInviteLink без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryExportChatInviteLink(const AChatId: TTgChatId; out AResult: string;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   createChatInviteLink: Use this method to create an additional invite link for a chat. The
    ///   bot must be an administrator in the chat for this to work and must have the appropriate
    ///   administrator rights. The link can be revoked using the method revokeChatInviteLink.
    ///   Returns the new invite link as ChatInviteLink object.
    /// </summary>
    function CreateChatInviteLink(const AChatId: TTgChatId): ITgChatInviteLink; overload;
    function CreateChatInviteLink(const AChatId: TTgChatId;
      const AOptions: TTgCreateChatInviteLinkOptions): ITgChatInviteLink; overload;
    /// <summary>
    ///   Асинхронный createChatInviteLink: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function CreateChatInviteLinkAsync(const AChatId: TTgChatId;
      const AOnSuccess: TProc<ITgChatInviteLink>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function CreateChatInviteLinkAsync(const AChatId: TTgChatId;
      const AOptions: TTgCreateChatInviteLinkOptions; const AOnSuccess: TProc<ITgChatInviteLink>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   createChatInviteLink без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryCreateChatInviteLink(const AChatId: TTgChatId; out AResult: ITgChatInviteLink;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryCreateChatInviteLink(const AChatId: TTgChatId;
      const AOptions: TTgCreateChatInviteLinkOptions; out AResult: ITgChatInviteLink;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   editChatInviteLink: Use this method to edit a non-primary invite link created by the bot.
    ///   The bot must be an administrator in the chat for this to work and must have the
    ///   appropriate administrator rights. Returns the edited invite link as a ChatInviteLink
    ///   object.
    /// </summary>
    function EditChatInviteLink(const AChatId: TTgChatId;
      const AInviteLink: string): ITgChatInviteLink; overload;
    function EditChatInviteLink(const AChatId: TTgChatId; const AInviteLink: string;
      const AOptions: TTgEditChatInviteLinkOptions): ITgChatInviteLink; overload;
    /// <summary>
    ///   Асинхронный editChatInviteLink: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function EditChatInviteLinkAsync(const AChatId: TTgChatId; const AInviteLink: string;
      const AOnSuccess: TProc<ITgChatInviteLink>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function EditChatInviteLinkAsync(const AChatId: TTgChatId; const AInviteLink: string;
      const AOptions: TTgEditChatInviteLinkOptions; const AOnSuccess: TProc<ITgChatInviteLink>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   editChatInviteLink без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryEditChatInviteLink(const AChatId: TTgChatId; const AInviteLink: string;
      out AResult: ITgChatInviteLink; out AError: TTgErrorInfo): Boolean; overload;
    function TryEditChatInviteLink(const AChatId: TTgChatId; const AInviteLink: string;
      const AOptions: TTgEditChatInviteLinkOptions; out AResult: ITgChatInviteLink;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   createChatSubscriptionInviteLink: Use this method to create a subscription invite link for
    ///   a channel chat. The bot must have the can_invite_users administrator rights. The link can
    ///   be edited using the method editChatSubscriptionInviteLink or revoked using the method
    ///   revokeChatInviteLink. Returns the new invite link as a ChatInviteLink object.
    /// </summary>
    function CreateChatSubscriptionInviteLink(const AChatId: TTgChatId;
      ASubscriptionPeriod: Integer; ASubscriptionPrice: Integer): ITgChatInviteLink; overload;
    function CreateChatSubscriptionInviteLink(const AChatId: TTgChatId;
      ASubscriptionPeriod: Integer; ASubscriptionPrice: Integer;
      const AOptions: TTgCreateChatSubscriptionInviteLinkOptions): ITgChatInviteLink; overload;
    /// <summary>
    ///   Асинхронный createChatSubscriptionInviteLink: параметры проверяются и строятся в
    ///   вызывающем потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function CreateChatSubscriptionInviteLinkAsync(const AChatId: TTgChatId;
      ASubscriptionPeriod: Integer; ASubscriptionPrice: Integer;
      const AOnSuccess: TProc<ITgChatInviteLink>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function CreateChatSubscriptionInviteLinkAsync(const AChatId: TTgChatId;
      ASubscriptionPeriod: Integer; ASubscriptionPrice: Integer;
      const AOptions: TTgCreateChatSubscriptionInviteLinkOptions;
      const AOnSuccess: TProc<ITgChatInviteLink>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   createChatSubscriptionInviteLink без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryCreateChatSubscriptionInviteLink(const AChatId: TTgChatId;
      ASubscriptionPeriod: Integer; ASubscriptionPrice: Integer; out AResult: ITgChatInviteLink;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryCreateChatSubscriptionInviteLink(const AChatId: TTgChatId;
      ASubscriptionPeriod: Integer; ASubscriptionPrice: Integer;
      const AOptions: TTgCreateChatSubscriptionInviteLinkOptions; out AResult: ITgChatInviteLink;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   editChatSubscriptionInviteLink: Use this method to edit a subscription invite link created
    ///   by the bot. The bot must have the can_invite_users administrator rights. Returns the
    ///   edited invite link as a ChatInviteLink object.
    /// </summary>
    function EditChatSubscriptionInviteLink(const AChatId: TTgChatId;
      const AInviteLink: string): ITgChatInviteLink; overload;
    function EditChatSubscriptionInviteLink(const AChatId: TTgChatId; const AInviteLink: string;
      const AOptions: TTgEditChatSubscriptionInviteLinkOptions): ITgChatInviteLink; overload;
    /// <summary>
    ///   Асинхронный editChatSubscriptionInviteLink: параметры проверяются и строятся в вызывающем
    ///   потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function EditChatSubscriptionInviteLinkAsync(const AChatId: TTgChatId;
      const AInviteLink: string; const AOnSuccess: TProc<ITgChatInviteLink>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function EditChatSubscriptionInviteLinkAsync(const AChatId: TTgChatId;
      const AInviteLink: string; const AOptions: TTgEditChatSubscriptionInviteLinkOptions;
      const AOnSuccess: TProc<ITgChatInviteLink>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   editChatSubscriptionInviteLink без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryEditChatSubscriptionInviteLink(const AChatId: TTgChatId; const AInviteLink: string;
      out AResult: ITgChatInviteLink; out AError: TTgErrorInfo): Boolean; overload;
    function TryEditChatSubscriptionInviteLink(const AChatId: TTgChatId; const AInviteLink: string;
      const AOptions: TTgEditChatSubscriptionInviteLinkOptions; out AResult: ITgChatInviteLink;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   revokeChatInviteLink: Use this method to revoke an invite link created by the bot. If the
    ///   primary link is revoked, a new link is automatically generated. The bot must be an
    ///   administrator in the chat for this to work and must have the appropriate administrator
    ///   rights. Returns the revoked invite link as ChatInviteLink object.
    /// </summary>
    function RevokeChatInviteLink(const AChatId: TTgChatId;
      const AInviteLink: string): ITgChatInviteLink; overload;
    /// <summary>
    ///   Асинхронный revokeChatInviteLink: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function RevokeChatInviteLinkAsync(const AChatId: TTgChatId; const AInviteLink: string;
      const AOnSuccess: TProc<ITgChatInviteLink>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   revokeChatInviteLink без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryRevokeChatInviteLink(const AChatId: TTgChatId; const AInviteLink: string;
      out AResult: ITgChatInviteLink; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   approveChatJoinRequest: Use this method to approve a chat join request. The bot must be an
    ///   administrator in the chat for this to work and must have the can_invite_users
    ///   administrator right. Returns True on success.
    /// </summary>
    function ApproveChatJoinRequest(const AChatId: TTgChatId; AUserId: Int64): Boolean; overload;
    /// <summary>
    ///   Асинхронный approveChatJoinRequest: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function ApproveChatJoinRequestAsync(const AChatId: TTgChatId; AUserId: Int64;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   approveChatJoinRequest без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryApproveChatJoinRequest(const AChatId: TTgChatId; AUserId: Int64;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   declineChatJoinRequest: Use this method to decline a chat join request. The bot must be an
    ///   administrator in the chat for this to work and must have the can_invite_users
    ///   administrator right. Returns True on success.
    /// </summary>
    function DeclineChatJoinRequest(const AChatId: TTgChatId; AUserId: Int64): Boolean; overload;
    /// <summary>
    ///   Асинхронный declineChatJoinRequest: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function DeclineChatJoinRequestAsync(const AChatId: TTgChatId; AUserId: Int64;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   declineChatJoinRequest без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryDeclineChatJoinRequest(const AChatId: TTgChatId; AUserId: Int64;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   answerChatJoinRequestQuery: Use this method to process a received chat join request query.
    ///   Returns True on success.
    /// </summary>
    function AnswerChatJoinRequestQuery(const AChatJoinRequestQueryId: string;
      const AChatJoinRequestQueryResult: string): Boolean; overload;
    /// <summary>
    ///   Асинхронный answerChatJoinRequestQuery: параметры проверяются и строятся в вызывающем
    ///   потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function AnswerChatJoinRequestQueryAsync(const AChatJoinRequestQueryId: string;
      const AChatJoinRequestQueryResult: string; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   answerChatJoinRequestQuery без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryAnswerChatJoinRequestQuery(const AChatJoinRequestQueryId: string;
      const AChatJoinRequestQueryResult: string; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   sendChatJoinRequestWebApp: Use this method to process a received chat join request query
    ///   by showing a Mini App to the user before deciding the outcome. Call
    ///   answerChatJoinRequestQuery to resolve the join request query based on the user interaction
    ///   with the Mini App. Returns True on success.
    /// </summary>
    function SendChatJoinRequestWebApp(const AChatJoinRequestQueryId: string;
      const AWebAppUrl: string): Boolean; overload;
    /// <summary>
    ///   Асинхронный sendChatJoinRequestWebApp: параметры проверяются и строятся в вызывающем
    ///   потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SendChatJoinRequestWebAppAsync(const AChatJoinRequestQueryId: string;
      const AWebAppUrl: string; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   sendChatJoinRequestWebApp без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySendChatJoinRequestWebApp(const AChatJoinRequestQueryId: string;
      const AWebAppUrl: string; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setChatPhoto: Use this method to set a new profile photo for the chat. Photos can't be
    ///   changed for private chats. The bot must be an administrator in the chat for this to work
    ///   and must have the appropriate administrator rights. Returns True on success.
    /// </summary>
    function SetChatPhoto(const AChatId: TTgChatId; const APhoto: TTgInputFile): Boolean; overload;
    /// <summary>
    ///   Асинхронный setChatPhoto: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetChatPhotoAsync(const AChatId: TTgChatId; const APhoto: TTgInputFile;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>setChatPhoto без исключений: False и сведения об ошибке в AError.</summary>
    function TrySetChatPhoto(const AChatId: TTgChatId; const APhoto: TTgInputFile;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   deleteChatPhoto: Use this method to delete a chat photo. Photos can't be changed for
    ///   private chats. The bot must be an administrator in the chat for this to work and must have
    ///   the appropriate administrator rights. Returns True on success.
    /// </summary>
    function DeleteChatPhoto(const AChatId: TTgChatId): Boolean; overload;
    /// <summary>
    ///   Асинхронный deleteChatPhoto: параметры проверяются и строятся в вызывающем потоке (ошибки
    ///   — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function DeleteChatPhotoAsync(const AChatId: TTgChatId; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   deleteChatPhoto без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryDeleteChatPhoto(const AChatId: TTgChatId; out AError: TTgErrorInfo): Boolean;
      overload;

    /// <summary>
    ///   setChatTitle: Use this method to change the title of a chat. Titles can't be changed for
    ///   private chats. The bot must be an administrator in the chat for this to work and must have
    ///   the appropriate administrator rights. Returns True on success.
    /// </summary>
    function SetChatTitle(const AChatId: TTgChatId; const ATitle: string): Boolean; overload;
    /// <summary>
    ///   Асинхронный setChatTitle: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetChatTitleAsync(const AChatId: TTgChatId; const ATitle: string;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>setChatTitle без исключений: False и сведения об ошибке в AError.</summary>
    function TrySetChatTitle(const AChatId: TTgChatId; const ATitle: string;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setChatDescription: Use this method to change the description of a group, a supergroup or
    ///   a channel. The bot must be an administrator in the chat for this to work and must have the
    ///   appropriate administrator rights. Returns True on success.
    /// </summary>
    function SetChatDescription(const AChatId: TTgChatId): Boolean; overload;
    function SetChatDescription(const AChatId: TTgChatId;
      const AOptions: TTgSetChatDescriptionOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный setChatDescription: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetChatDescriptionAsync(const AChatId: TTgChatId; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function SetChatDescriptionAsync(const AChatId: TTgChatId;
      const AOptions: TTgSetChatDescriptionOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   setChatDescription без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySetChatDescription(const AChatId: TTgChatId; out AError: TTgErrorInfo): Boolean;
      overload;
    function TrySetChatDescription(const AChatId: TTgChatId;
      const AOptions: TTgSetChatDescriptionOptions; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   pinChatMessage: Use this method to add a message to the list of pinned messages in a chat.
    ///   In private chats and channel direct messages chats, all non-service messages can be
    ///   pinned. Conversely, the bot must be an administrator with the 'can_pin_messages' right or
    ///   the 'can_edit_messages' right to pin messages in groups and channels respectively. Returns
    ///   True on success.
    /// </summary>
    function PinChatMessage(const AChatId: TTgChatId; AMessageId: Int64): Boolean; overload;
    function PinChatMessage(const AChatId: TTgChatId; AMessageId: Int64;
      const AOptions: TTgPinChatMessageOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный pinChatMessage: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function PinChatMessageAsync(const AChatId: TTgChatId; AMessageId: Int64;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function PinChatMessageAsync(const AChatId: TTgChatId; AMessageId: Int64;
      const AOptions: TTgPinChatMessageOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   pinChatMessage без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryPinChatMessage(const AChatId: TTgChatId; AMessageId: Int64;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryPinChatMessage(const AChatId: TTgChatId; AMessageId: Int64;
      const AOptions: TTgPinChatMessageOptions; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   unpinChatMessage: Use this method to remove a message from the list of pinned messages in
    ///   a chat. In private chats and channel direct messages chats, all messages can be unpinned.
    ///   Conversely, the bot must be an administrator with the 'can_pin_messages' right or the
    ///   'can_edit_messages' right to unpin messages in groups and channels respectively. Returns
    ///   True on success.
    /// </summary>
    function UnpinChatMessage(const AChatId: TTgChatId): Boolean; overload;
    function UnpinChatMessage(const AChatId: TTgChatId;
      const AOptions: TTgUnpinChatMessageOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный unpinChatMessage: параметры проверяются и строятся в вызывающем потоке (ошибки
    ///   — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function UnpinChatMessageAsync(const AChatId: TTgChatId; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function UnpinChatMessageAsync(const AChatId: TTgChatId;
      const AOptions: TTgUnpinChatMessageOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   unpinChatMessage без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryUnpinChatMessage(const AChatId: TTgChatId; out AError: TTgErrorInfo): Boolean;
      overload;
    function TryUnpinChatMessage(const AChatId: TTgChatId;
      const AOptions: TTgUnpinChatMessageOptions; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   unpinAllChatMessages: Use this method to clear the list of pinned messages in a chat. In
    ///   private chats and channel direct messages chats, no additional rights are required to
    ///   unpin all pinned messages. Conversely, the bot must be an administrator with the
    ///   'can_pin_messages' right or the 'can_edit_messages' right to unpin all pinned messages in
    ///   groups and channels respectively. Returns True on success.
    /// </summary>
    function UnpinAllChatMessages(const AChatId: TTgChatId): Boolean; overload;
    /// <summary>
    ///   Асинхронный unpinAllChatMessages: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function UnpinAllChatMessagesAsync(const AChatId: TTgChatId; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   unpinAllChatMessages без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryUnpinAllChatMessages(const AChatId: TTgChatId; out AError: TTgErrorInfo): Boolean;
      overload;

    /// <summary>
    ///   leaveChat: Use this method for your bot to leave a group, supergroup or channel. Returns
    ///   True on success.
    /// </summary>
    function LeaveChat(const AChatId: TTgChatId): Boolean; overload;
    /// <summary>
    ///   Асинхронный leaveChat: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function LeaveChatAsync(const AChatId: TTgChatId; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>leaveChat без исключений: False и сведения об ошибке в AError.</summary>
    function TryLeaveChat(const AChatId: TTgChatId; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   getChat: Use this method to get up-to-date information about the chat. Returns a
    ///   ChatFullInfo object on success.
    /// </summary>
    function GetChat(const AChatId: TTgChatId): ITgChatFullInfo; overload;
    /// <summary>
    ///   Асинхронный getChat: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetChatAsync(const AChatId: TTgChatId; const AOnSuccess: TProc<ITgChatFullInfo>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>getChat без исключений: False и сведения об ошибке в AError.</summary>
    function TryGetChat(const AChatId: TTgChatId; out AResult: ITgChatFullInfo;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   getChatAdministrators: Use this method to get a list of administrators in a chat. Returns
    ///   an Array of ChatMember objects. Элементы результата разделяют JSON всего ответа и
    ///   удерживают его; для длительного хранения отдельных элементов используйте TTgDto.Detach.
    /// </summary>
    function GetChatAdministrators(const AChatId: TTgChatId): TArray<ITgChatMember>; overload;
    function GetChatAdministrators(const AChatId: TTgChatId;
      const AOptions: TTgGetChatAdministratorsOptions): TArray<ITgChatMember>; overload;
    /// <summary>
    ///   Асинхронный getChatAdministrators: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetChatAdministratorsAsync(const AChatId: TTgChatId;
      const AOnSuccess: TProc<TArray<ITgChatMember>>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function GetChatAdministratorsAsync(const AChatId: TTgChatId;
      const AOptions: TTgGetChatAdministratorsOptions;
      const AOnSuccess: TProc<TArray<ITgChatMember>>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   getChatAdministrators без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryGetChatAdministrators(const AChatId: TTgChatId; out AResult: TArray<ITgChatMember>;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryGetChatAdministrators(const AChatId: TTgChatId;
      const AOptions: TTgGetChatAdministratorsOptions; out AResult: TArray<ITgChatMember>;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   getChatMemberCount: Use this method to get the number of members in a chat. Returns
    ///   Integer on success.
    /// </summary>
    function GetChatMemberCount(const AChatId: TTgChatId): Integer; overload;
    /// <summary>
    ///   Асинхронный getChatMemberCount: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetChatMemberCountAsync(const AChatId: TTgChatId; const AOnSuccess: TProc<Integer>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   getChatMemberCount без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryGetChatMemberCount(const AChatId: TTgChatId; out AResult: Integer;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   getChatMember: Use this method to get information about a member of a chat. The method is
    ///   only guaranteed to work for other users if the bot is an administrator in the chat.
    ///   Returns a ChatMember object on success.
    /// </summary>
    function GetChatMember(const AChatId: TTgChatId; AUserId: Int64): ITgChatMember; overload;
    /// <summary>
    ///   Асинхронный getChatMember: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetChatMemberAsync(const AChatId: TTgChatId; AUserId: Int64;
      const AOnSuccess: TProc<ITgChatMember>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   getChatMember без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryGetChatMember(const AChatId: TTgChatId; AUserId: Int64; out AResult: ITgChatMember;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   getUserPersonalChatMessages: Use this method to get the last messages from the personal
    ///   chat (i.e., the chat currently added to their profile) of a given user. On success, an
    ///   Array of Message objects is returned. Элементы результата разделяют JSON всего ответа и
    ///   удерживают его; для длительного хранения отдельных элементов используйте TTgDto.Detach.
    /// </summary>
    function GetUserPersonalChatMessages(AUserId: Int64; ALimit: Integer): TArray<ITgMessage>;
      overload;
    /// <summary>
    ///   Асинхронный getUserPersonalChatMessages: параметры проверяются и строятся в вызывающем
    ///   потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetUserPersonalChatMessagesAsync(AUserId: Int64; ALimit: Integer;
      const AOnSuccess: TProc<TArray<ITgMessage>>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   getUserPersonalChatMessages без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryGetUserPersonalChatMessages(AUserId: Int64; ALimit: Integer;
      out AResult: TArray<ITgMessage>; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setChatStickerSet: Use this method to set a new group sticker set for a supergroup. The
    ///   bot must be an administrator in the chat for this to work and must have the appropriate
    ///   administrator rights. Use the field can_set_sticker_set optionally returned in getChat
    ///   requests to check if the bot can use this method. Returns True on success.
    /// </summary>
    function SetChatStickerSet(const AChatId: TTgChatId; const AStickerSetName: string): Boolean;
      overload;
    /// <summary>
    ///   Асинхронный setChatStickerSet: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetChatStickerSetAsync(const AChatId: TTgChatId; const AStickerSetName: string;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   setChatStickerSet без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySetChatStickerSet(const AChatId: TTgChatId; const AStickerSetName: string;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   deleteChatStickerSet: Use this method to delete a group sticker set from a supergroup. The
    ///   bot must be an administrator in the chat for this to work and must have the appropriate
    ///   administrator rights. Use the field can_set_sticker_set optionally returned in getChat
    ///   requests to check if the bot can use this method. Returns True on success.
    /// </summary>
    function DeleteChatStickerSet(const AChatId: TTgChatId): Boolean; overload;
    /// <summary>
    ///   Асинхронный deleteChatStickerSet: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function DeleteChatStickerSetAsync(const AChatId: TTgChatId; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   deleteChatStickerSet без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryDeleteChatStickerSet(const AChatId: TTgChatId; out AError: TTgErrorInfo): Boolean;
      overload;

    /// <summary>
    ///   getForumTopicIconStickers: Use this method to get custom emoji stickers, which can be used
    ///   as a forum topic icon by any user. Requires no parameters. Returns an Array of Sticker
    ///   objects. Элементы результата разделяют JSON всего ответа и удерживают его; для длительного
    ///   хранения отдельных элементов используйте TTgDto.Detach.
    /// </summary>
    function GetForumTopicIconStickers: TArray<ITgSticker>; overload;
    /// <summary>
    ///   Асинхронный getForumTopicIconStickers: параметры проверяются и строятся в вызывающем
    ///   потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetForumTopicIconStickersAsync(const AOnSuccess: TProc<TArray<ITgSticker>>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   getForumTopicIconStickers без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryGetForumTopicIconStickers(out AResult: TArray<ITgSticker>;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   createForumTopic: Use this method to create a topic in a forum supergroup chat or a
    ///   private chat with a user. In the case of a supergroup chat the bot must be an
    ///   administrator in the chat for this to work and must have the can_manage_topics
    ///   administrator right. Returns information about the created topic as a ForumTopic object.
    /// </summary>
    function CreateForumTopic(const AChatId: TTgChatId; const AName: string): ITgForumTopic;
      overload;
    function CreateForumTopic(const AChatId: TTgChatId; const AName: string;
      const AOptions: TTgCreateForumTopicOptions): ITgForumTopic; overload;
    /// <summary>
    ///   Асинхронный createForumTopic: параметры проверяются и строятся в вызывающем потоке (ошибки
    ///   — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function CreateForumTopicAsync(const AChatId: TTgChatId; const AName: string;
      const AOnSuccess: TProc<ITgForumTopic>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function CreateForumTopicAsync(const AChatId: TTgChatId; const AName: string;
      const AOptions: TTgCreateForumTopicOptions; const AOnSuccess: TProc<ITgForumTopic>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   createForumTopic без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryCreateForumTopic(const AChatId: TTgChatId; const AName: string;
      out AResult: ITgForumTopic; out AError: TTgErrorInfo): Boolean; overload;
    function TryCreateForumTopic(const AChatId: TTgChatId; const AName: string;
      const AOptions: TTgCreateForumTopicOptions; out AResult: ITgForumTopic;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   editForumTopic: Use this method to edit name and icon of a topic in a forum supergroup
    ///   chat or a private chat with a user. In the case of a supergroup chat the bot must be an
    ///   administrator in the chat for this to work and must have the can_manage_topics
    ///   administrator rights, unless it is the creator of the topic. Returns True on success.
    /// </summary>
    function EditForumTopic(const AChatId: TTgChatId; AMessageThreadId: Int64): Boolean; overload;
    function EditForumTopic(const AChatId: TTgChatId; AMessageThreadId: Int64;
      const AOptions: TTgEditForumTopicOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный editForumTopic: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function EditForumTopicAsync(const AChatId: TTgChatId; AMessageThreadId: Int64;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function EditForumTopicAsync(const AChatId: TTgChatId; AMessageThreadId: Int64;
      const AOptions: TTgEditForumTopicOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   editForumTopic без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryEditForumTopic(const AChatId: TTgChatId; AMessageThreadId: Int64;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryEditForumTopic(const AChatId: TTgChatId; AMessageThreadId: Int64;
      const AOptions: TTgEditForumTopicOptions; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   closeForumTopic: Use this method to close an open topic in a forum supergroup chat. The
    ///   bot must be an administrator in the chat for this to work and must have the
    ///   can_manage_topics administrator rights, unless it is the creator of the topic. Returns
    ///   True on success.
    /// </summary>
    function CloseForumTopic(const AChatId: TTgChatId; AMessageThreadId: Int64): Boolean; overload;
    /// <summary>
    ///   Асинхронный closeForumTopic: параметры проверяются и строятся в вызывающем потоке (ошибки
    ///   — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function CloseForumTopicAsync(const AChatId: TTgChatId; AMessageThreadId: Int64;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   closeForumTopic без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryCloseForumTopic(const AChatId: TTgChatId; AMessageThreadId: Int64;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   reopenForumTopic: Use this method to reopen a closed topic in a forum supergroup chat. The
    ///   bot must be an administrator in the chat for this to work and must have the
    ///   can_manage_topics administrator rights, unless it is the creator of the topic. Returns
    ///   True on success.
    /// </summary>
    function ReopenForumTopic(const AChatId: TTgChatId; AMessageThreadId: Int64): Boolean; overload;
    /// <summary>
    ///   Асинхронный reopenForumTopic: параметры проверяются и строятся в вызывающем потоке (ошибки
    ///   — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function ReopenForumTopicAsync(const AChatId: TTgChatId; AMessageThreadId: Int64;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   reopenForumTopic без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryReopenForumTopic(const AChatId: TTgChatId; AMessageThreadId: Int64;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   deleteForumTopic: Use this method to delete a forum topic along with all its messages in a
    ///   forum supergroup chat or a private chat with a user. In the case of a supergroup chat the
    ///   bot must be an administrator in the chat for this to work and must have the
    ///   can_delete_messages administrator rights. Returns True on success.
    /// </summary>
    function DeleteForumTopic(const AChatId: TTgChatId; AMessageThreadId: Int64): Boolean; overload;
    /// <summary>
    ///   Асинхронный deleteForumTopic: параметры проверяются и строятся в вызывающем потоке (ошибки
    ///   — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function DeleteForumTopicAsync(const AChatId: TTgChatId; AMessageThreadId: Int64;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   deleteForumTopic без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryDeleteForumTopic(const AChatId: TTgChatId; AMessageThreadId: Int64;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   unpinAllForumTopicMessages: Use this method to clear the list of pinned messages in a
    ///   forum topic in a forum supergroup chat or a private chat with a user. In the case of a
    ///   supergroup chat the bot must be an administrator in the chat for this to work and must
    ///   have the can_pin_messages administrator right in the supergroup. Returns True on success.
    /// </summary>
    function UnpinAllForumTopicMessages(const AChatId: TTgChatId; AMessageThreadId: Int64): Boolean;
      overload;
    /// <summary>
    ///   Асинхронный unpinAllForumTopicMessages: параметры проверяются и строятся в вызывающем
    ///   потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function UnpinAllForumTopicMessagesAsync(const AChatId: TTgChatId; AMessageThreadId: Int64;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   unpinAllForumTopicMessages без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryUnpinAllForumTopicMessages(const AChatId: TTgChatId; AMessageThreadId: Int64;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   editGeneralForumTopic: Use this method to edit the name of the 'General' topic in a forum
    ///   supergroup chat. The bot must be an administrator in the chat for this to work and must
    ///   have the can_manage_topics administrator rights. Returns True on success.
    /// </summary>
    function EditGeneralForumTopic(const AChatId: TTgChatId; const AName: string): Boolean;
      overload;
    /// <summary>
    ///   Асинхронный editGeneralForumTopic: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function EditGeneralForumTopicAsync(const AChatId: TTgChatId; const AName: string;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   editGeneralForumTopic без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryEditGeneralForumTopic(const AChatId: TTgChatId; const AName: string;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   closeGeneralForumTopic: Use this method to close an open 'General' topic in a forum
    ///   supergroup chat. The bot must be an administrator in the chat for this to work and must
    ///   have the can_manage_topics administrator rights. Returns True on success.
    /// </summary>
    function CloseGeneralForumTopic(const AChatId: TTgChatId): Boolean; overload;
    /// <summary>
    ///   Асинхронный closeGeneralForumTopic: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function CloseGeneralForumTopicAsync(const AChatId: TTgChatId; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   closeGeneralForumTopic без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryCloseGeneralForumTopic(const AChatId: TTgChatId; out AError: TTgErrorInfo): Boolean;
      overload;

    /// <summary>
    ///   reopenGeneralForumTopic: Use this method to reopen a closed 'General' topic in a forum
    ///   supergroup chat. The bot must be an administrator in the chat for this to work and must
    ///   have the can_manage_topics administrator rights. The topic will be automatically unhidden
    ///   if it was hidden. Returns True on success.
    /// </summary>
    function ReopenGeneralForumTopic(const AChatId: TTgChatId): Boolean; overload;
    /// <summary>
    ///   Асинхронный reopenGeneralForumTopic: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function ReopenGeneralForumTopicAsync(const AChatId: TTgChatId;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   reopenGeneralForumTopic без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryReopenGeneralForumTopic(const AChatId: TTgChatId;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   hideGeneralForumTopic: Use this method to hide the 'General' topic in a forum supergroup
    ///   chat. The bot must be an administrator in the chat for this to work and must have the
    ///   can_manage_topics administrator rights. The topic will be automatically closed if it was
    ///   open. Returns True on success.
    /// </summary>
    function HideGeneralForumTopic(const AChatId: TTgChatId): Boolean; overload;
    /// <summary>
    ///   Асинхронный hideGeneralForumTopic: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function HideGeneralForumTopicAsync(const AChatId: TTgChatId; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   hideGeneralForumTopic без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryHideGeneralForumTopic(const AChatId: TTgChatId; out AError: TTgErrorInfo): Boolean;
      overload;

    /// <summary>
    ///   unhideGeneralForumTopic: Use this method to unhide the 'General' topic in a forum
    ///   supergroup chat. The bot must be an administrator in the chat for this to work and must
    ///   have the can_manage_topics administrator rights. Returns True on success.
    /// </summary>
    function UnhideGeneralForumTopic(const AChatId: TTgChatId): Boolean; overload;
    /// <summary>
    ///   Асинхронный unhideGeneralForumTopic: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function UnhideGeneralForumTopicAsync(const AChatId: TTgChatId;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   unhideGeneralForumTopic без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryUnhideGeneralForumTopic(const AChatId: TTgChatId;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   unpinAllGeneralForumTopicMessages: Use this method to clear the list of pinned messages in
    ///   a General forum topic. The bot must be an administrator in the chat for this to work and
    ///   must have the can_pin_messages administrator right in the supergroup. Returns True on
    ///   success.
    /// </summary>
    function UnpinAllGeneralForumTopicMessages(const AChatId: TTgChatId): Boolean; overload;
    /// <summary>
    ///   Асинхронный unpinAllGeneralForumTopicMessages: параметры проверяются и строятся в
    ///   вызывающем потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function UnpinAllGeneralForumTopicMessagesAsync(const AChatId: TTgChatId;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   unpinAllGeneralForumTopicMessages без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryUnpinAllGeneralForumTopicMessages(const AChatId: TTgChatId;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   answerCallbackQuery: Use this method to send answers to callback queries sent from inline
    ///   keyboards. The answer will be displayed to the user as a notification at the top of the
    ///   chat screen or as an alert. On success, True is returned.
    /// </summary>
    function AnswerCallbackQuery(const ACallbackQueryId: string): Boolean; overload;
    function AnswerCallbackQuery(const ACallbackQueryId: string;
      const AOptions: TTgAnswerCallbackQueryOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный answerCallbackQuery: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function AnswerCallbackQueryAsync(const ACallbackQueryId: string;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function AnswerCallbackQueryAsync(const ACallbackQueryId: string;
      const AOptions: TTgAnswerCallbackQueryOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   answerCallbackQuery без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryAnswerCallbackQuery(const ACallbackQueryId: string;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryAnswerCallbackQuery(const ACallbackQueryId: string;
      const AOptions: TTgAnswerCallbackQueryOptions; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   answerCallbackQuery (вариант: callback_query_id, text). Уведомление с текстом. Поля
    ///   AOptions (Text) заменяются значениями параметров.
    /// </summary>
    function AnswerCallbackQuery(const ACallbackQueryId: string; const AText: string): Boolean;
      overload;
    function AnswerCallbackQuery(const ACallbackQueryId: string; const AText: string;
      const AOptions: TTgAnswerCallbackQueryOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный AnswerCallbackQuery (answerCallbackQuery, вариант): параметры проверяются и
    ///   строятся в вызывающем потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем
    ///   потоке.
    /// </summary>
    function AnswerCallbackQueryAsync(const ACallbackQueryId: string; const AText: string;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function AnswerCallbackQueryAsync(const ACallbackQueryId: string; const AText: string;
      const AOptions: TTgAnswerCallbackQueryOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   AnswerCallbackQuery (answerCallbackQuery, вариант) без исключений: False и сведения об
    ///   ошибке в AError.
    /// </summary>
    function TryAnswerCallbackQuery(const ACallbackQueryId: string; const AText: string;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryAnswerCallbackQuery(const ACallbackQueryId: string; const AText: string;
      const AOptions: TTgAnswerCallbackQueryOptions; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   answerCallbackQuery (вариант: callback_query_id, text, show_alert). Текст уведомлением или
    ///   окном (AShowAlert = True). Поля AOptions (Text, ShowAlert) заменяются значениями
    ///   параметров.
    /// </summary>
    function AnswerCallbackQuery(const ACallbackQueryId: string; const AText: string;
      AShowAlert: Boolean): Boolean; overload;
    function AnswerCallbackQuery(const ACallbackQueryId: string; const AText: string;
      AShowAlert: Boolean; const AOptions: TTgAnswerCallbackQueryOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный AnswerCallbackQuery (answerCallbackQuery, вариант): параметры проверяются и
    ///   строятся в вызывающем потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем
    ///   потоке.
    /// </summary>
    function AnswerCallbackQueryAsync(const ACallbackQueryId: string; const AText: string;
      AShowAlert: Boolean; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function AnswerCallbackQueryAsync(const ACallbackQueryId: string; const AText: string;
      AShowAlert: Boolean; const AOptions: TTgAnswerCallbackQueryOptions;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   AnswerCallbackQuery (answerCallbackQuery, вариант) без исключений: False и сведения об
    ///   ошибке в AError.
    /// </summary>
    function TryAnswerCallbackQuery(const ACallbackQueryId: string; const AText: string;
      AShowAlert: Boolean; out AError: TTgErrorInfo): Boolean; overload;
    function TryAnswerCallbackQuery(const ACallbackQueryId: string; const AText: string;
      AShowAlert: Boolean; const AOptions: TTgAnswerCallbackQueryOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   answerGuestQuery: Use this method to reply to a received guest message. On success, a
    ///   SentGuestMessage object is returned.
    /// </summary>
    function AnswerGuestQuery(const AGuestQueryId: string;
      const AGuestQueryResult: TTgInlineQueryResult): ITgSentGuestMessage; overload;
    /// <summary>
    ///   Асинхронный answerGuestQuery: параметры проверяются и строятся в вызывающем потоке (ошибки
    ///   — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function AnswerGuestQueryAsync(const AGuestQueryId: string;
      const AGuestQueryResult: TTgInlineQueryResult; const AOnSuccess: TProc<ITgSentGuestMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   answerGuestQuery без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryAnswerGuestQuery(const AGuestQueryId: string;
      const AGuestQueryResult: TTgInlineQueryResult; out AResult: ITgSentGuestMessage;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   getUserChatBoosts: Use this method to get the list of boosts added to a chat by a user.
    ///   Requires administrator rights in the chat. Returns a UserChatBoosts object.
    /// </summary>
    function GetUserChatBoosts(const AChatId: TTgChatId; AUserId: Int64): ITgUserChatBoosts;
      overload;
    /// <summary>
    ///   Асинхронный getUserChatBoosts: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetUserChatBoostsAsync(const AChatId: TTgChatId; AUserId: Int64;
      const AOnSuccess: TProc<ITgUserChatBoosts>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   getUserChatBoosts без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryGetUserChatBoosts(const AChatId: TTgChatId; AUserId: Int64;
      out AResult: ITgUserChatBoosts; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   getBusinessConnection: Use this method to get information about the connection of the bot
    ///   with a business account. Returns a BusinessConnection object on success.
    /// </summary>
    function GetBusinessConnection(const ABusinessConnectionId: string): ITgBusinessConnection;
      overload;
    /// <summary>
    ///   Асинхронный getBusinessConnection: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetBusinessConnectionAsync(const ABusinessConnectionId: string;
      const AOnSuccess: TProc<ITgBusinessConnection>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   getBusinessConnection без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryGetBusinessConnection(const ABusinessConnectionId: string;
      out AResult: ITgBusinessConnection; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   getManagedBotToken: Use this method to get the token of a managed bot. Returns the token
    ///   as String on success.
    /// </summary>
    function GetManagedBotToken(AUserId: Int64): string; overload;
    /// <summary>
    ///   Асинхронный getManagedBotToken: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetManagedBotTokenAsync(AUserId: Int64; const AOnSuccess: TProc<string>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   getManagedBotToken без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryGetManagedBotToken(AUserId: Int64; out AResult: string;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   replaceManagedBotToken: Use this method to revoke the current token of a managed bot and
    ///   generate a new one. Returns the new token as String on success.
    /// </summary>
    function ReplaceManagedBotToken(AUserId: Int64): string; overload;
    /// <summary>
    ///   Асинхронный replaceManagedBotToken: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function ReplaceManagedBotTokenAsync(AUserId: Int64; const AOnSuccess: TProc<string>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   replaceManagedBotToken без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryReplaceManagedBotToken(AUserId: Int64; out AResult: string;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   getManagedBotAccessSettings: Use this method to get the access settings of a managed bot.
    ///   Returns a BotAccessSettings object on success.
    /// </summary>
    function GetManagedBotAccessSettings(AUserId: Int64): ITgBotAccessSettings; overload;
    /// <summary>
    ///   Асинхронный getManagedBotAccessSettings: параметры проверяются и строятся в вызывающем
    ///   потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetManagedBotAccessSettingsAsync(AUserId: Int64;
      const AOnSuccess: TProc<ITgBotAccessSettings>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   getManagedBotAccessSettings без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryGetManagedBotAccessSettings(AUserId: Int64; out AResult: ITgBotAccessSettings;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setManagedBotAccessSettings: Use this method to change the access settings of a managed
    ///   bot. Returns True on success.
    /// </summary>
    function SetManagedBotAccessSettings(AUserId: Int64; AIsAccessRestricted: Boolean): Boolean;
      overload;
    function SetManagedBotAccessSettings(AUserId: Int64; AIsAccessRestricted: Boolean;
      const AOptions: TTgSetManagedBotAccessSettingsOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный setManagedBotAccessSettings: параметры проверяются и строятся в вызывающем
    ///   потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetManagedBotAccessSettingsAsync(AUserId: Int64; AIsAccessRestricted: Boolean;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function SetManagedBotAccessSettingsAsync(AUserId: Int64; AIsAccessRestricted: Boolean;
      const AOptions: TTgSetManagedBotAccessSettingsOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   setManagedBotAccessSettings без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySetManagedBotAccessSettings(AUserId: Int64; AIsAccessRestricted: Boolean;
      out AError: TTgErrorInfo): Boolean; overload;
    function TrySetManagedBotAccessSettings(AUserId: Int64; AIsAccessRestricted: Boolean;
      const AOptions: TTgSetManagedBotAccessSettingsOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setMyCommands: Use this method to change the list of the bot's commands. See this manual
    ///   for more details about bot commands. Returns True on success.
    /// </summary>
    function SetMyCommands(const ACommands: array of ITgBotCommand): Boolean; overload;
    function SetMyCommands(const ACommands: array of ITgBotCommand;
      const AOptions: TTgSetMyCommandsOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный setMyCommands: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetMyCommandsAsync(const ACommands: array of ITgBotCommand;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function SetMyCommandsAsync(const ACommands: array of ITgBotCommand;
      const AOptions: TTgSetMyCommandsOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   setMyCommands без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySetMyCommands(const ACommands: array of ITgBotCommand;
      out AError: TTgErrorInfo): Boolean; overload;
    function TrySetMyCommands(const ACommands: array of ITgBotCommand;
      const AOptions: TTgSetMyCommandsOptions; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   deleteMyCommands: Use this method to delete the list of the bot's commands for the given
    ///   scope and user language. After deletion, higher level commands will be shown to affected
    ///   users. Returns True on success.
    /// </summary>
    function DeleteMyCommands: Boolean; overload;
    function DeleteMyCommands(const AOptions: TTgDeleteMyCommandsOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный deleteMyCommands: параметры проверяются и строятся в вызывающем потоке (ошибки
    ///   — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function DeleteMyCommandsAsync(const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function DeleteMyCommandsAsync(const AOptions: TTgDeleteMyCommandsOptions;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   deleteMyCommands без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryDeleteMyCommands(out AError: TTgErrorInfo): Boolean; overload;
    function TryDeleteMyCommands(const AOptions: TTgDeleteMyCommandsOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   getMyCommands: Use this method to get the current list of the bot's commands for the given
    ///   scope and user language. Returns an Array of BotCommand objects. If commands aren't set,
    ///   an empty list is returned. Элементы результата разделяют JSON всего ответа и удерживают
    ///   его; для длительного хранения отдельных элементов используйте TTgDto.Detach.
    /// </summary>
    function GetMyCommands: TArray<ITgBotCommand>; overload;
    function GetMyCommands(const AOptions: TTgGetMyCommandsOptions): TArray<ITgBotCommand>;
      overload;
    /// <summary>
    ///   Асинхронный getMyCommands: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetMyCommandsAsync(const AOnSuccess: TProc<TArray<ITgBotCommand>>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function GetMyCommandsAsync(const AOptions: TTgGetMyCommandsOptions;
      const AOnSuccess: TProc<TArray<ITgBotCommand>>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   getMyCommands без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryGetMyCommands(out AResult: TArray<ITgBotCommand>;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryGetMyCommands(const AOptions: TTgGetMyCommandsOptions;
      out AResult: TArray<ITgBotCommand>; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setMyName: Use this method to change the bot's name. Returns True on success.
    /// </summary>
    function SetMyName: Boolean; overload;
    function SetMyName(const AOptions: TTgSetMyNameOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный setMyName: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetMyNameAsync(const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function SetMyNameAsync(const AOptions: TTgSetMyNameOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>setMyName без исключений: False и сведения об ошибке в AError.</summary>
    function TrySetMyName(out AError: TTgErrorInfo): Boolean; overload;
    function TrySetMyName(const AOptions: TTgSetMyNameOptions; out AError: TTgErrorInfo): Boolean;
      overload;

    /// <summary>
    ///   getMyName: Use this method to get the current bot name for the given user language.
    ///   Returns BotName on success.
    /// </summary>
    function GetMyName: ITgBotName; overload;
    function GetMyName(const AOptions: TTgGetMyNameOptions): ITgBotName; overload;
    /// <summary>
    ///   Асинхронный getMyName: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetMyNameAsync(const AOnSuccess: TProc<ITgBotName>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function GetMyNameAsync(const AOptions: TTgGetMyNameOptions;
      const AOnSuccess: TProc<ITgBotName>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>getMyName без исключений: False и сведения об ошибке в AError.</summary>
    function TryGetMyName(out AResult: ITgBotName; out AError: TTgErrorInfo): Boolean; overload;
    function TryGetMyName(const AOptions: TTgGetMyNameOptions; out AResult: ITgBotName;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setMyDescription: Use this method to change the bot's description, which is shown in the
    ///   chat with the bot if the chat is empty. Returns True on success.
    /// </summary>
    function SetMyDescription: Boolean; overload;
    function SetMyDescription(const AOptions: TTgSetMyDescriptionOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный setMyDescription: параметры проверяются и строятся в вызывающем потоке (ошибки
    ///   — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetMyDescriptionAsync(const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function SetMyDescriptionAsync(const AOptions: TTgSetMyDescriptionOptions;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   setMyDescription без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySetMyDescription(out AError: TTgErrorInfo): Boolean; overload;
    function TrySetMyDescription(const AOptions: TTgSetMyDescriptionOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   getMyDescription: Use this method to get the current bot description for the given user
    ///   language. Returns BotDescription on success.
    /// </summary>
    function GetMyDescription: ITgBotDescription; overload;
    function GetMyDescription(const AOptions: TTgGetMyDescriptionOptions): ITgBotDescription;
      overload;
    /// <summary>
    ///   Асинхронный getMyDescription: параметры проверяются и строятся в вызывающем потоке (ошибки
    ///   — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetMyDescriptionAsync(const AOnSuccess: TProc<ITgBotDescription>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function GetMyDescriptionAsync(const AOptions: TTgGetMyDescriptionOptions;
      const AOnSuccess: TProc<ITgBotDescription>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   getMyDescription без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryGetMyDescription(out AResult: ITgBotDescription; out AError: TTgErrorInfo): Boolean;
      overload;
    function TryGetMyDescription(const AOptions: TTgGetMyDescriptionOptions;
      out AResult: ITgBotDescription; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setMyShortDescription: Use this method to change the bot's short description, which is
    ///   shown on the bot's profile page and is sent together with the link when users share the
    ///   bot. Returns True on success.
    /// </summary>
    function SetMyShortDescription: Boolean; overload;
    function SetMyShortDescription(const AOptions: TTgSetMyShortDescriptionOptions): Boolean;
      overload;
    /// <summary>
    ///   Асинхронный setMyShortDescription: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetMyShortDescriptionAsync(const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function SetMyShortDescriptionAsync(const AOptions: TTgSetMyShortDescriptionOptions;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   setMyShortDescription без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySetMyShortDescription(out AError: TTgErrorInfo): Boolean; overload;
    function TrySetMyShortDescription(const AOptions: TTgSetMyShortDescriptionOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   getMyShortDescription: Use this method to get the current bot short description for the
    ///   given user language. Returns BotShortDescription on success.
    /// </summary>
    function GetMyShortDescription: ITgBotShortDescription; overload;
    function GetMyShortDescription(const AOptions: TTgGetMyShortDescriptionOptions): ITgBotShortDescription; overload;
    /// <summary>
    ///   Асинхронный getMyShortDescription: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetMyShortDescriptionAsync(const AOnSuccess: TProc<ITgBotShortDescription>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function GetMyShortDescriptionAsync(const AOptions: TTgGetMyShortDescriptionOptions;
      const AOnSuccess: TProc<ITgBotShortDescription>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   getMyShortDescription без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryGetMyShortDescription(out AResult: ITgBotShortDescription;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryGetMyShortDescription(const AOptions: TTgGetMyShortDescriptionOptions;
      out AResult: ITgBotShortDescription; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setMyProfilePhoto: Changes the profile photo of the bot. Returns True on success.
    /// </summary>
    function SetMyProfilePhoto(const APhoto: TTgInputProfilePhoto): Boolean; overload;
    /// <summary>
    ///   Асинхронный setMyProfilePhoto: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetMyProfilePhotoAsync(const APhoto: TTgInputProfilePhoto;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   setMyProfilePhoto без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySetMyProfilePhoto(const APhoto: TTgInputProfilePhoto;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   removeMyProfilePhoto: Removes the profile photo of the bot. Requires no parameters.
    ///   Returns True on success.
    /// </summary>
    function RemoveMyProfilePhoto: Boolean; overload;
    /// <summary>
    ///   Асинхронный removeMyProfilePhoto: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function RemoveMyProfilePhotoAsync(const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   removeMyProfilePhoto без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryRemoveMyProfilePhoto(out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setChatMenuButton: Use this method to change the bot's menu button in a private chat, or
    ///   the default menu button. Returns True on success.
    /// </summary>
    function SetChatMenuButton: Boolean; overload;
    function SetChatMenuButton(const AOptions: TTgSetChatMenuButtonOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный setChatMenuButton: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetChatMenuButtonAsync(const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function SetChatMenuButtonAsync(const AOptions: TTgSetChatMenuButtonOptions;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   setChatMenuButton без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySetChatMenuButton(out AError: TTgErrorInfo): Boolean; overload;
    function TrySetChatMenuButton(const AOptions: TTgSetChatMenuButtonOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   getChatMenuButton: Use this method to get the current value of the bot's menu button in a
    ///   private chat, or the default menu button. Returns MenuButton on success.
    /// </summary>
    function GetChatMenuButton: ITgMenuButton; overload;
    function GetChatMenuButton(const AOptions: TTgGetChatMenuButtonOptions): ITgMenuButton;
      overload;
    /// <summary>
    ///   Асинхронный getChatMenuButton: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetChatMenuButtonAsync(const AOnSuccess: TProc<ITgMenuButton>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function GetChatMenuButtonAsync(const AOptions: TTgGetChatMenuButtonOptions;
      const AOnSuccess: TProc<ITgMenuButton>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   getChatMenuButton без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryGetChatMenuButton(out AResult: ITgMenuButton; out AError: TTgErrorInfo): Boolean;
      overload;
    function TryGetChatMenuButton(const AOptions: TTgGetChatMenuButtonOptions;
      out AResult: ITgMenuButton; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setMyDefaultAdministratorRights: Use this method to change the default administrator
    ///   rights requested by the bot when it's added as an administrator to groups or channels.
    ///   These rights will be suggested to users, but they are free to modify the list before
    ///   adding the bot. Returns True on success.
    /// </summary>
    function SetMyDefaultAdministratorRights: Boolean; overload;
    function SetMyDefaultAdministratorRights(const AOptions: TTgSetMyDefaultAdministratorRightsOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный setMyDefaultAdministratorRights: параметры проверяются и строятся в вызывающем
    ///   потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetMyDefaultAdministratorRightsAsync(const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function SetMyDefaultAdministratorRightsAsync(const AOptions: TTgSetMyDefaultAdministratorRightsOptions; const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   setMyDefaultAdministratorRights без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySetMyDefaultAdministratorRights(out AError: TTgErrorInfo): Boolean; overload;
    function TrySetMyDefaultAdministratorRights(const AOptions: TTgSetMyDefaultAdministratorRightsOptions; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   getMyDefaultAdministratorRights: Use this method to get the current default administrator
    ///   rights of the bot. Returns ChatAdministratorRights on success.
    /// </summary>
    function GetMyDefaultAdministratorRights: ITgChatAdministratorRights; overload;
    function GetMyDefaultAdministratorRights(const AOptions: TTgGetMyDefaultAdministratorRightsOptions): ITgChatAdministratorRights; overload;
    /// <summary>
    ///   Асинхронный getMyDefaultAdministratorRights: параметры проверяются и строятся в вызывающем
    ///   потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetMyDefaultAdministratorRightsAsync(const AOnSuccess: TProc<ITgChatAdministratorRights>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function GetMyDefaultAdministratorRightsAsync(const AOptions: TTgGetMyDefaultAdministratorRightsOptions; const AOnSuccess: TProc<ITgChatAdministratorRights>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   getMyDefaultAdministratorRights без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryGetMyDefaultAdministratorRights(out AResult: ITgChatAdministratorRights;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryGetMyDefaultAdministratorRights(const AOptions: TTgGetMyDefaultAdministratorRightsOptions; out AResult: ITgChatAdministratorRights; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   getAvailableGifts: Returns the list of gifts that can be sent by the bot to users and
    ///   channel chats. Requires no parameters. Returns a Gifts object.
    /// </summary>
    function GetAvailableGifts: ITgGifts; overload;
    /// <summary>
    ///   Асинхронный getAvailableGifts: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetAvailableGiftsAsync(const AOnSuccess: TProc<ITgGifts>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   getAvailableGifts без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryGetAvailableGifts(out AResult: ITgGifts; out AError: TTgErrorInfo): Boolean;
      overload;

    /// <summary>
    ///   sendGift: Sends a gift to the given user or channel chat. The gift can't be converted to
    ///   Telegram Stars by the receiver. Returns True on success.
    /// </summary>
    function SendGift(const AGiftId: string): Boolean; overload;
    function SendGift(const AGiftId: string; const AOptions: TTgSendGiftOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный sendGift: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SendGiftAsync(const AGiftId: string; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function SendGiftAsync(const AGiftId: string; const AOptions: TTgSendGiftOptions;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>sendGift без исключений: False и сведения об ошибке в AError.</summary>
    function TrySendGift(const AGiftId: string; out AError: TTgErrorInfo): Boolean; overload;
    function TrySendGift(const AGiftId: string; const AOptions: TTgSendGiftOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   giftPremiumSubscription: Gifts a Telegram Premium subscription to the given user. Returns
    ///   True on success.
    /// </summary>
    function GiftPremiumSubscription(AUserId: Int64; AMonthCount: Integer;
      AStarCount: Integer): Boolean; overload;
    function GiftPremiumSubscription(AUserId: Int64; AMonthCount: Integer; AStarCount: Integer;
      const AOptions: TTgGiftPremiumSubscriptionOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный giftPremiumSubscription: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GiftPremiumSubscriptionAsync(AUserId: Int64; AMonthCount: Integer; AStarCount: Integer;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function GiftPremiumSubscriptionAsync(AUserId: Int64; AMonthCount: Integer; AStarCount: Integer;
      const AOptions: TTgGiftPremiumSubscriptionOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   giftPremiumSubscription без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryGiftPremiumSubscription(AUserId: Int64; AMonthCount: Integer; AStarCount: Integer;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryGiftPremiumSubscription(AUserId: Int64; AMonthCount: Integer; AStarCount: Integer;
      const AOptions: TTgGiftPremiumSubscriptionOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   verifyUser: Verifies a user on behalf of the organization which is represented by the bot.
    ///   Returns True on success.
    /// </summary>
    function VerifyUser(AUserId: Int64): Boolean; overload;
    function VerifyUser(AUserId: Int64; const AOptions: TTgVerifyUserOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный verifyUser: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function VerifyUserAsync(AUserId: Int64; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function VerifyUserAsync(AUserId: Int64; const AOptions: TTgVerifyUserOptions;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>verifyUser без исключений: False и сведения об ошибке в AError.</summary>
    function TryVerifyUser(AUserId: Int64; out AError: TTgErrorInfo): Boolean; overload;
    function TryVerifyUser(AUserId: Int64; const AOptions: TTgVerifyUserOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   verifyChat: Verifies a chat on behalf of the organization which is represented by the bot.
    ///   Returns True on success.
    /// </summary>
    function VerifyChat(const AChatId: TTgChatId): Boolean; overload;
    function VerifyChat(const AChatId: TTgChatId; const AOptions: TTgVerifyChatOptions): Boolean;
      overload;
    /// <summary>
    ///   Асинхронный verifyChat: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function VerifyChatAsync(const AChatId: TTgChatId; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function VerifyChatAsync(const AChatId: TTgChatId; const AOptions: TTgVerifyChatOptions;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>verifyChat без исключений: False и сведения об ошибке в AError.</summary>
    function TryVerifyChat(const AChatId: TTgChatId; out AError: TTgErrorInfo): Boolean; overload;
    function TryVerifyChat(const AChatId: TTgChatId; const AOptions: TTgVerifyChatOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   removeUserVerification: Removes verification from a user who is currently verified on
    ///   behalf of the organization represented by the bot. Returns True on success.
    /// </summary>
    function RemoveUserVerification(AUserId: Int64): Boolean; overload;
    /// <summary>
    ///   Асинхронный removeUserVerification: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function RemoveUserVerificationAsync(AUserId: Int64; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   removeUserVerification без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryRemoveUserVerification(AUserId: Int64; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   removeChatVerification: Removes verification from a chat that is currently verified on
    ///   behalf of the organization represented by the bot. Returns True on success.
    /// </summary>
    function RemoveChatVerification(const AChatId: TTgChatId): Boolean; overload;
    /// <summary>
    ///   Асинхронный removeChatVerification: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function RemoveChatVerificationAsync(const AChatId: TTgChatId; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   removeChatVerification без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryRemoveChatVerification(const AChatId: TTgChatId; out AError: TTgErrorInfo): Boolean;
      overload;

    /// <summary>
    ///   readBusinessMessage: Marks incoming message as read on behalf of a business account.
    ///   Requires the can_read_messages business bot right. Returns True on success.
    /// </summary>
    function ReadBusinessMessage(const ABusinessConnectionId: string; AChatId: Int64;
      AMessageId: Int64): Boolean; overload;
    /// <summary>
    ///   Асинхронный readBusinessMessage: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function ReadBusinessMessageAsync(const ABusinessConnectionId: string; AChatId: Int64;
      AMessageId: Int64; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   readBusinessMessage без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryReadBusinessMessage(const ABusinessConnectionId: string; AChatId: Int64;
      AMessageId: Int64; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   deleteBusinessMessages: Delete messages on behalf of a business account. Requires the
    ///   can_delete_sent_messages business bot right to delete messages sent by the bot itself, or
    ///   the can_delete_all_messages business bot right to delete any message. Returns True on
    ///   success.
    /// </summary>
    function DeleteBusinessMessages(const ABusinessConnectionId: string;
      const AMessageIds: TArray<Int64>): Boolean; overload;
    /// <summary>
    ///   Асинхронный deleteBusinessMessages: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function DeleteBusinessMessagesAsync(const ABusinessConnectionId: string;
      const AMessageIds: TArray<Int64>; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   deleteBusinessMessages без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryDeleteBusinessMessages(const ABusinessConnectionId: string;
      const AMessageIds: TArray<Int64>; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setBusinessAccountName: Changes the first and last name of a managed business account.
    ///   Requires the can_change_name business bot right. Returns True on success.
    /// </summary>
    function SetBusinessAccountName(const ABusinessConnectionId: string;
      const AFirstName: string): Boolean; overload;
    function SetBusinessAccountName(const ABusinessConnectionId: string; const AFirstName: string;
      const AOptions: TTgSetBusinessAccountNameOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный setBusinessAccountName: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetBusinessAccountNameAsync(const ABusinessConnectionId: string;
      const AFirstName: string; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function SetBusinessAccountNameAsync(const ABusinessConnectionId: string;
      const AFirstName: string; const AOptions: TTgSetBusinessAccountNameOptions;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   setBusinessAccountName без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySetBusinessAccountName(const ABusinessConnectionId: string;
      const AFirstName: string; out AError: TTgErrorInfo): Boolean; overload;
    function TrySetBusinessAccountName(const ABusinessConnectionId: string;
      const AFirstName: string; const AOptions: TTgSetBusinessAccountNameOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setBusinessAccountUsername: Changes the username of a managed business account. Requires
    ///   the can_change_username business bot right. Returns True on success.
    /// </summary>
    function SetBusinessAccountUsername(const ABusinessConnectionId: string): Boolean; overload;
    function SetBusinessAccountUsername(const ABusinessConnectionId: string;
      const AOptions: TTgSetBusinessAccountUsernameOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный setBusinessAccountUsername: параметры проверяются и строятся в вызывающем
    ///   потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetBusinessAccountUsernameAsync(const ABusinessConnectionId: string;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function SetBusinessAccountUsernameAsync(const ABusinessConnectionId: string;
      const AOptions: TTgSetBusinessAccountUsernameOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   setBusinessAccountUsername без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySetBusinessAccountUsername(const ABusinessConnectionId: string;
      out AError: TTgErrorInfo): Boolean; overload;
    function TrySetBusinessAccountUsername(const ABusinessConnectionId: string;
      const AOptions: TTgSetBusinessAccountUsernameOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setBusinessAccountBio: Changes the bio of a managed business account. Requires the
    ///   can_change_bio business bot right. Returns True on success.
    /// </summary>
    function SetBusinessAccountBio(const ABusinessConnectionId: string): Boolean; overload;
    function SetBusinessAccountBio(const ABusinessConnectionId: string;
      const AOptions: TTgSetBusinessAccountBioOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный setBusinessAccountBio: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetBusinessAccountBioAsync(const ABusinessConnectionId: string;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function SetBusinessAccountBioAsync(const ABusinessConnectionId: string;
      const AOptions: TTgSetBusinessAccountBioOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   setBusinessAccountBio без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySetBusinessAccountBio(const ABusinessConnectionId: string;
      out AError: TTgErrorInfo): Boolean; overload;
    function TrySetBusinessAccountBio(const ABusinessConnectionId: string;
      const AOptions: TTgSetBusinessAccountBioOptions; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setBusinessAccountProfilePhoto: Changes the profile photo of a managed business account.
    ///   Requires the can_edit_profile_photo business bot right. Returns True on success.
    /// </summary>
    function SetBusinessAccountProfilePhoto(const ABusinessConnectionId: string;
      const APhoto: TTgInputProfilePhoto): Boolean; overload;
    function SetBusinessAccountProfilePhoto(const ABusinessConnectionId: string;
      const APhoto: TTgInputProfilePhoto;
      const AOptions: TTgSetBusinessAccountProfilePhotoOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный setBusinessAccountProfilePhoto: параметры проверяются и строятся в вызывающем
    ///   потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetBusinessAccountProfilePhotoAsync(const ABusinessConnectionId: string;
      const APhoto: TTgInputProfilePhoto; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function SetBusinessAccountProfilePhotoAsync(const ABusinessConnectionId: string;
      const APhoto: TTgInputProfilePhoto; const AOptions: TTgSetBusinessAccountProfilePhotoOptions;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   setBusinessAccountProfilePhoto без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySetBusinessAccountProfilePhoto(const ABusinessConnectionId: string;
      const APhoto: TTgInputProfilePhoto; out AError: TTgErrorInfo): Boolean; overload;
    function TrySetBusinessAccountProfilePhoto(const ABusinessConnectionId: string;
      const APhoto: TTgInputProfilePhoto; const AOptions: TTgSetBusinessAccountProfilePhotoOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   removeBusinessAccountProfilePhoto: Removes the current profile photo of a managed business
    ///   account. Requires the can_edit_profile_photo business bot right. Returns True on success.
    /// </summary>
    function RemoveBusinessAccountProfilePhoto(const ABusinessConnectionId: string): Boolean;
      overload;
    function RemoveBusinessAccountProfilePhoto(const ABusinessConnectionId: string;
      const AOptions: TTgRemoveBusinessAccountProfilePhotoOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный removeBusinessAccountProfilePhoto: параметры проверяются и строятся в
    ///   вызывающем потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function RemoveBusinessAccountProfilePhotoAsync(const ABusinessConnectionId: string;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function RemoveBusinessAccountProfilePhotoAsync(const ABusinessConnectionId: string;
      const AOptions: TTgRemoveBusinessAccountProfilePhotoOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   removeBusinessAccountProfilePhoto без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryRemoveBusinessAccountProfilePhoto(const ABusinessConnectionId: string;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryRemoveBusinessAccountProfilePhoto(const ABusinessConnectionId: string;
      const AOptions: TTgRemoveBusinessAccountProfilePhotoOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setBusinessAccountGiftSettings: Changes the privacy settings pertaining to incoming gifts
    ///   in a managed business account. Requires the can_change_gift_settings business bot right.
    ///   Returns True on success.
    /// </summary>
    function SetBusinessAccountGiftSettings(const ABusinessConnectionId: string;
      AShowGiftButton: Boolean; const AAcceptedGiftTypes: ITgAcceptedGiftTypes): Boolean; overload;
    /// <summary>
    ///   Асинхронный setBusinessAccountGiftSettings: параметры проверяются и строятся в вызывающем
    ///   потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetBusinessAccountGiftSettingsAsync(const ABusinessConnectionId: string;
      AShowGiftButton: Boolean; const AAcceptedGiftTypes: ITgAcceptedGiftTypes;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   setBusinessAccountGiftSettings без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySetBusinessAccountGiftSettings(const ABusinessConnectionId: string;
      AShowGiftButton: Boolean; const AAcceptedGiftTypes: ITgAcceptedGiftTypes;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   getBusinessAccountStarBalance: Returns the amount of Telegram Stars owned by a managed
    ///   business account. Requires the can_view_gifts_and_stars business bot right. Returns
    ///   StarAmount on success.
    /// </summary>
    function GetBusinessAccountStarBalance(const ABusinessConnectionId: string): ITgStarAmount;
      overload;
    /// <summary>
    ///   Асинхронный getBusinessAccountStarBalance: параметры проверяются и строятся в вызывающем
    ///   потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetBusinessAccountStarBalanceAsync(const ABusinessConnectionId: string;
      const AOnSuccess: TProc<ITgStarAmount>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   getBusinessAccountStarBalance без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryGetBusinessAccountStarBalance(const ABusinessConnectionId: string;
      out AResult: ITgStarAmount; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   transferBusinessAccountStars: Transfers Telegram Stars from the business account balance
    ///   to the bot's balance. Requires the can_transfer_stars business bot right. Returns True on
    ///   success.
    /// </summary>
    function TransferBusinessAccountStars(const ABusinessConnectionId: string;
      AStarCount: Integer): Boolean; overload;
    /// <summary>
    ///   Асинхронный transferBusinessAccountStars: параметры проверяются и строятся в вызывающем
    ///   потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function TransferBusinessAccountStarsAsync(const ABusinessConnectionId: string;
      AStarCount: Integer; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   transferBusinessAccountStars без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryTransferBusinessAccountStars(const ABusinessConnectionId: string;
      AStarCount: Integer; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   getBusinessAccountGifts: Returns the gifts received and owned by a managed business
    ///   account. Requires the can_view_gifts_and_stars business bot right. Returns OwnedGifts on
    ///   success.
    /// </summary>
    function GetBusinessAccountGifts(const ABusinessConnectionId: string): ITgOwnedGifts; overload;
    function GetBusinessAccountGifts(const ABusinessConnectionId: string;
      const AOptions: TTgGetBusinessAccountGiftsOptions): ITgOwnedGifts; overload;
    /// <summary>
    ///   Асинхронный getBusinessAccountGifts: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetBusinessAccountGiftsAsync(const ABusinessConnectionId: string;
      const AOnSuccess: TProc<ITgOwnedGifts>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function GetBusinessAccountGiftsAsync(const ABusinessConnectionId: string;
      const AOptions: TTgGetBusinessAccountGiftsOptions; const AOnSuccess: TProc<ITgOwnedGifts>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   getBusinessAccountGifts без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryGetBusinessAccountGifts(const ABusinessConnectionId: string;
      out AResult: ITgOwnedGifts; out AError: TTgErrorInfo): Boolean; overload;
    function TryGetBusinessAccountGifts(const ABusinessConnectionId: string;
      const AOptions: TTgGetBusinessAccountGiftsOptions; out AResult: ITgOwnedGifts;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   getUserGifts: Returns the gifts owned and hosted by a user. Returns OwnedGifts on success.
    /// </summary>
    function GetUserGifts(AUserId: Int64): ITgOwnedGifts; overload;
    function GetUserGifts(AUserId: Int64; const AOptions: TTgGetUserGiftsOptions): ITgOwnedGifts;
      overload;
    /// <summary>
    ///   Асинхронный getUserGifts: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetUserGiftsAsync(AUserId: Int64; const AOnSuccess: TProc<ITgOwnedGifts>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function GetUserGiftsAsync(AUserId: Int64; const AOptions: TTgGetUserGiftsOptions;
      const AOnSuccess: TProc<ITgOwnedGifts>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>getUserGifts без исключений: False и сведения об ошибке в AError.</summary>
    function TryGetUserGifts(AUserId: Int64; out AResult: ITgOwnedGifts;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryGetUserGifts(AUserId: Int64; const AOptions: TTgGetUserGiftsOptions;
      out AResult: ITgOwnedGifts; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   getChatGifts: Returns the gifts owned by a chat. Returns OwnedGifts on success.
    /// </summary>
    function GetChatGifts(const AChatId: TTgChatId): ITgOwnedGifts; overload;
    function GetChatGifts(const AChatId: TTgChatId;
      const AOptions: TTgGetChatGiftsOptions): ITgOwnedGifts; overload;
    /// <summary>
    ///   Асинхронный getChatGifts: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetChatGiftsAsync(const AChatId: TTgChatId; const AOnSuccess: TProc<ITgOwnedGifts>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function GetChatGiftsAsync(const AChatId: TTgChatId; const AOptions: TTgGetChatGiftsOptions;
      const AOnSuccess: TProc<ITgOwnedGifts>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>getChatGifts без исключений: False и сведения об ошибке в AError.</summary>
    function TryGetChatGifts(const AChatId: TTgChatId; out AResult: ITgOwnedGifts;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryGetChatGifts(const AChatId: TTgChatId; const AOptions: TTgGetChatGiftsOptions;
      out AResult: ITgOwnedGifts; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   convertGiftToStars: Converts a given regular gift to Telegram Stars. Requires the
    ///   can_convert_gifts_to_stars business bot right. Returns True on success.
    /// </summary>
    function ConvertGiftToStars(const ABusinessConnectionId: string;
      const AOwnedGiftId: string): Boolean; overload;
    /// <summary>
    ///   Асинхронный convertGiftToStars: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function ConvertGiftToStarsAsync(const ABusinessConnectionId: string;
      const AOwnedGiftId: string; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   convertGiftToStars без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryConvertGiftToStars(const ABusinessConnectionId: string; const AOwnedGiftId: string;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   upgradeGift: Upgrades a given regular gift to a unique gift. Requires the
    ///   can_transfer_and_upgrade_gifts business bot right. Additionally requires the
    ///   can_transfer_stars business bot right if the upgrade is paid. Returns True on success.
    /// </summary>
    function UpgradeGift(const ABusinessConnectionId: string; const AOwnedGiftId: string): Boolean;
      overload;
    function UpgradeGift(const ABusinessConnectionId: string; const AOwnedGiftId: string;
      const AOptions: TTgUpgradeGiftOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный upgradeGift: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function UpgradeGiftAsync(const ABusinessConnectionId: string; const AOwnedGiftId: string;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function UpgradeGiftAsync(const ABusinessConnectionId: string; const AOwnedGiftId: string;
      const AOptions: TTgUpgradeGiftOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>upgradeGift без исключений: False и сведения об ошибке в AError.</summary>
    function TryUpgradeGift(const ABusinessConnectionId: string; const AOwnedGiftId: string;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryUpgradeGift(const ABusinessConnectionId: string; const AOwnedGiftId: string;
      const AOptions: TTgUpgradeGiftOptions; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   transferGift: Transfers an owned unique gift to another user. Requires the
    ///   can_transfer_and_upgrade_gifts business bot right. Requires can_transfer_stars business
    ///   bot right if the transfer is paid. Returns True on success.
    /// </summary>
    function TransferGift(const ABusinessConnectionId: string; const AOwnedGiftId: string;
      ANewOwnerChatId: Int64): Boolean; overload;
    function TransferGift(const ABusinessConnectionId: string; const AOwnedGiftId: string;
      ANewOwnerChatId: Int64; const AOptions: TTgTransferGiftOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный transferGift: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function TransferGiftAsync(const ABusinessConnectionId: string; const AOwnedGiftId: string;
      ANewOwnerChatId: Int64; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function TransferGiftAsync(const ABusinessConnectionId: string; const AOwnedGiftId: string;
      ANewOwnerChatId: Int64; const AOptions: TTgTransferGiftOptions;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>transferGift без исключений: False и сведения об ошибке в AError.</summary>
    function TryTransferGift(const ABusinessConnectionId: string; const AOwnedGiftId: string;
      ANewOwnerChatId: Int64; out AError: TTgErrorInfo): Boolean; overload;
    function TryTransferGift(const ABusinessConnectionId: string; const AOwnedGiftId: string;
      ANewOwnerChatId: Int64; const AOptions: TTgTransferGiftOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   postStory: Posts a story on behalf of a managed business account. Requires the
    ///   can_manage_stories business bot right. Returns Story on success.
    /// </summary>
    function PostStory(const ABusinessConnectionId: string; const AContent: TTgInputStoryContent;
      AActivePeriod: Integer): ITgStory; overload;
    function PostStory(const ABusinessConnectionId: string; const AContent: TTgInputStoryContent;
      AActivePeriod: Integer; const AOptions: TTgPostStoryOptions): ITgStory; overload;
    /// <summary>
    ///   Асинхронный postStory: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function PostStoryAsync(const ABusinessConnectionId: string;
      const AContent: TTgInputStoryContent; AActivePeriod: Integer;
      const AOnSuccess: TProc<ITgStory>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function PostStoryAsync(const ABusinessConnectionId: string;
      const AContent: TTgInputStoryContent; AActivePeriod: Integer;
      const AOptions: TTgPostStoryOptions; const AOnSuccess: TProc<ITgStory>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>postStory без исключений: False и сведения об ошибке в AError.</summary>
    function TryPostStory(const ABusinessConnectionId: string; const AContent: TTgInputStoryContent;
      AActivePeriod: Integer; out AResult: ITgStory; out AError: TTgErrorInfo): Boolean; overload;
    function TryPostStory(const ABusinessConnectionId: string; const AContent: TTgInputStoryContent;
      AActivePeriod: Integer; const AOptions: TTgPostStoryOptions; out AResult: ITgStory;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   repostStory: Reposts a story on behalf of a business account from another business
    ///   account. Both business accounts must be managed by the same bot, and the story on the
    ///   source account must have been posted (or reposted) by the bot. Requires the
    ///   can_manage_stories business bot right for both business accounts. Returns Story on
    ///   success.
    /// </summary>
    function RepostStory(const ABusinessConnectionId: string; AFromChatId: Int64;
      AFromStoryId: Int64; AActivePeriod: Integer): ITgStory; overload;
    function RepostStory(const ABusinessConnectionId: string; AFromChatId: Int64;
      AFromStoryId: Int64; AActivePeriod: Integer;
      const AOptions: TTgRepostStoryOptions): ITgStory; overload;
    /// <summary>
    ///   Асинхронный repostStory: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function RepostStoryAsync(const ABusinessConnectionId: string; AFromChatId: Int64;
      AFromStoryId: Int64; AActivePeriod: Integer; const AOnSuccess: TProc<ITgStory>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function RepostStoryAsync(const ABusinessConnectionId: string; AFromChatId: Int64;
      AFromStoryId: Int64; AActivePeriod: Integer; const AOptions: TTgRepostStoryOptions;
      const AOnSuccess: TProc<ITgStory>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>repostStory без исключений: False и сведения об ошибке в AError.</summary>
    function TryRepostStory(const ABusinessConnectionId: string; AFromChatId: Int64;
      AFromStoryId: Int64; AActivePeriod: Integer; out AResult: ITgStory;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryRepostStory(const ABusinessConnectionId: string; AFromChatId: Int64;
      AFromStoryId: Int64; AActivePeriod: Integer; const AOptions: TTgRepostStoryOptions;
      out AResult: ITgStory; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   editStory: Edits a story previously posted by the bot on behalf of a managed business
    ///   account. Requires the can_manage_stories business bot right. Returns Story on success.
    /// </summary>
    function EditStory(const ABusinessConnectionId: string; AStoryId: Int64;
      const AContent: TTgInputStoryContent): ITgStory; overload;
    function EditStory(const ABusinessConnectionId: string; AStoryId: Int64;
      const AContent: TTgInputStoryContent;
      const AOptions: TTgEditStoryOptions): ITgStory; overload;
    /// <summary>
    ///   Асинхронный editStory: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function EditStoryAsync(const ABusinessConnectionId: string; AStoryId: Int64;
      const AContent: TTgInputStoryContent; const AOnSuccess: TProc<ITgStory>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function EditStoryAsync(const ABusinessConnectionId: string; AStoryId: Int64;
      const AContent: TTgInputStoryContent; const AOptions: TTgEditStoryOptions;
      const AOnSuccess: TProc<ITgStory>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>editStory без исключений: False и сведения об ошибке в AError.</summary>
    function TryEditStory(const ABusinessConnectionId: string; AStoryId: Int64;
      const AContent: TTgInputStoryContent; out AResult: ITgStory;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryEditStory(const ABusinessConnectionId: string; AStoryId: Int64;
      const AContent: TTgInputStoryContent; const AOptions: TTgEditStoryOptions;
      out AResult: ITgStory; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   deleteStory: Deletes a story previously posted by the bot on behalf of a managed business
    ///   account. Requires the can_manage_stories business bot right. Returns True on success.
    /// </summary>
    function DeleteStory(const ABusinessConnectionId: string; AStoryId: Int64): Boolean; overload;
    /// <summary>
    ///   Асинхронный deleteStory: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function DeleteStoryAsync(const ABusinessConnectionId: string; AStoryId: Int64;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>deleteStory без исключений: False и сведения об ошибке в AError.</summary>
    function TryDeleteStory(const ABusinessConnectionId: string; AStoryId: Int64;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   answerWebAppQuery: Use this method to set the result of an interaction with a Web App and
    ///   send a corresponding message on behalf of the user to the chat from which the query
    ///   originated. On success, a SentWebAppMessage object is returned.
    /// </summary>
    function AnswerWebAppQuery(const AWebAppQueryId: string;
      const AWebAppQueryResult: TTgInlineQueryResult): ITgSentWebAppMessage; overload;
    /// <summary>
    ///   Асинхронный answerWebAppQuery: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function AnswerWebAppQueryAsync(const AWebAppQueryId: string;
      const AWebAppQueryResult: TTgInlineQueryResult; const AOnSuccess: TProc<ITgSentWebAppMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   answerWebAppQuery без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryAnswerWebAppQuery(const AWebAppQueryId: string;
      const AWebAppQueryResult: TTgInlineQueryResult; out AResult: ITgSentWebAppMessage;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   savePreparedInlineMessage: Stores a message that can be sent by a user of a Mini App.
    ///   Returns a PreparedInlineMessage object.
    /// </summary>
    function SavePreparedInlineMessage(AUserId: Int64;
      const APreparedInlineMessageResult: TTgInlineQueryResult): ITgPreparedInlineMessage; overload;
    function SavePreparedInlineMessage(AUserId: Int64;
      const APreparedInlineMessageResult: TTgInlineQueryResult;
      const AOptions: TTgSavePreparedInlineMessageOptions): ITgPreparedInlineMessage; overload;
    /// <summary>
    ///   Асинхронный savePreparedInlineMessage: параметры проверяются и строятся в вызывающем
    ///   потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SavePreparedInlineMessageAsync(AUserId: Int64;
      const APreparedInlineMessageResult: TTgInlineQueryResult;
      const AOnSuccess: TProc<ITgPreparedInlineMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function SavePreparedInlineMessageAsync(AUserId: Int64;
      const APreparedInlineMessageResult: TTgInlineQueryResult;
      const AOptions: TTgSavePreparedInlineMessageOptions;
      const AOnSuccess: TProc<ITgPreparedInlineMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   savePreparedInlineMessage без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySavePreparedInlineMessage(AUserId: Int64;
      const APreparedInlineMessageResult: TTgInlineQueryResult;
      out AResult: ITgPreparedInlineMessage; out AError: TTgErrorInfo): Boolean; overload;
    function TrySavePreparedInlineMessage(AUserId: Int64;
      const APreparedInlineMessageResult: TTgInlineQueryResult;
      const AOptions: TTgSavePreparedInlineMessageOptions; out AResult: ITgPreparedInlineMessage;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   savePreparedKeyboardButton: Stores a keyboard button that can be used by a user within a
    ///   Mini App. Returns a PreparedKeyboardButton object.
    /// </summary>
    function SavePreparedKeyboardButton(AUserId: Int64;
      const AButton: ITgKeyboardButton): ITgPreparedKeyboardButton; overload;
    /// <summary>
    ///   Асинхронный savePreparedKeyboardButton: параметры проверяются и строятся в вызывающем
    ///   потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SavePreparedKeyboardButtonAsync(AUserId: Int64; const AButton: ITgKeyboardButton;
      const AOnSuccess: TProc<ITgPreparedKeyboardButton>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   savePreparedKeyboardButton без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySavePreparedKeyboardButton(AUserId: Int64; const AButton: ITgKeyboardButton;
      out AResult: ITgPreparedKeyboardButton; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   editMessageText: Use this method to edit text, rich and game messages. On success, if the
    ///   edited message is not an inline message, the edited Message is returned, otherwise True is
    ///   returned. Note that business messages that were not sent by the bot and do not contain an
    ///   inline keyboard can only be edited within 48 hours from the time they were sent.
    /// </summary>
    function EditMessageText: ITgMessage; overload;
    function EditMessageText(const AOptions: TTgEditMessageTextOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный editMessageText: параметры проверяются и строятся в вызывающем потоке (ошибки
    ///   — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function EditMessageTextAsync(const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function EditMessageTextAsync(const AOptions: TTgEditMessageTextOptions;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   editMessageText без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryEditMessageText(out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
      overload;
    function TryEditMessageText(const AOptions: TTgEditMessageTextOptions; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   editMessageText (вариант: chat_id, message_id, text). Сообщение, отправленное от имени
    ///   бота (не inline). Поля AOptions (ChatId, MessageId, Text) заменяются значениями
    ///   параметров.
    /// </summary>
    function EditMessageText(const AChatId: TTgChatId; AMessageId: Int64;
      const AText: string): ITgMessage; overload;
    function EditMessageText(const AChatId: TTgChatId; AMessageId: Int64; const AText: string;
      const AOptions: TTgEditMessageTextOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный EditMessageText (editMessageText, вариант): параметры проверяются и строятся в
    ///   вызывающем потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function EditMessageTextAsync(const AChatId: TTgChatId; AMessageId: Int64; const AText: string;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function EditMessageTextAsync(const AChatId: TTgChatId; AMessageId: Int64; const AText: string;
      const AOptions: TTgEditMessageTextOptions; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   EditMessageText (editMessageText, вариант) без исключений: False и сведения об ошибке в
    ///   AError.
    /// </summary>
    function TryEditMessageText(const AChatId: TTgChatId; AMessageId: Int64; const AText: string;
      out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;
    function TryEditMessageText(const AChatId: TTgChatId; AMessageId: Int64; const AText: string;
      const AOptions: TTgEditMessageTextOptions; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   editMessageText (вариант: inline_message_id, text). Inline-сообщение (отправленное через
    ///   inline-режим). Результат True — запрос выполнен (Bot API вернул true). Поля AOptions
    ///   (InlineMessageId, Text) заменяются значениями параметров.
    /// </summary>
    function EditInlineMessageText(const AInlineMessageId: string; const AText: string): Boolean;
      overload;
    function EditInlineMessageText(const AInlineMessageId: string; const AText: string;
      const AOptions: TTgEditMessageTextOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный EditInlineMessageText (editMessageText, вариант): параметры проверяются и
    ///   строятся в вызывающем потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем
    ///   потоке.
    /// </summary>
    function EditInlineMessageTextAsync(const AInlineMessageId: string; const AText: string;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function EditInlineMessageTextAsync(const AInlineMessageId: string; const AText: string;
      const AOptions: TTgEditMessageTextOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   EditInlineMessageText (editMessageText, вариант) без исключений: False и сведения об
    ///   ошибке в AError.
    /// </summary>
    function TryEditInlineMessageText(const AInlineMessageId: string; const AText: string;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryEditInlineMessageText(const AInlineMessageId: string; const AText: string;
      const AOptions: TTgEditMessageTextOptions; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   editMessageCaption: Use this method to edit captions of messages. On success, if the
    ///   edited message is not an inline message, the edited Message is returned, otherwise True is
    ///   returned. Note that business messages that were not sent by the bot and do not contain an
    ///   inline keyboard can only be edited within 48 hours from the time they were sent.
    /// </summary>
    function EditMessageCaption: ITgMessage; overload;
    function EditMessageCaption(const AOptions: TTgEditMessageCaptionOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный editMessageCaption: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function EditMessageCaptionAsync(const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function EditMessageCaptionAsync(const AOptions: TTgEditMessageCaptionOptions;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   editMessageCaption без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryEditMessageCaption(out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
      overload;
    function TryEditMessageCaption(const AOptions: TTgEditMessageCaptionOptions;
      out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   editMessageCaption (вариант: chat_id, message_id, caption). Сообщение, отправленное от
    ///   имени бота (не inline). Поля AOptions (ChatId, MessageId, Caption) заменяются значениями
    ///   параметров.
    /// </summary>
    function EditMessageCaption(const AChatId: TTgChatId; AMessageId: Int64;
      const ACaption: string): ITgMessage; overload;
    function EditMessageCaption(const AChatId: TTgChatId; AMessageId: Int64; const ACaption: string;
      const AOptions: TTgEditMessageCaptionOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный EditMessageCaption (editMessageCaption, вариант): параметры проверяются и
    ///   строятся в вызывающем потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем
    ///   потоке.
    /// </summary>
    function EditMessageCaptionAsync(const AChatId: TTgChatId; AMessageId: Int64;
      const ACaption: string; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function EditMessageCaptionAsync(const AChatId: TTgChatId; AMessageId: Int64;
      const ACaption: string; const AOptions: TTgEditMessageCaptionOptions;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   EditMessageCaption (editMessageCaption, вариант) без исключений: False и сведения об
    ///   ошибке в AError.
    /// </summary>
    function TryEditMessageCaption(const AChatId: TTgChatId; AMessageId: Int64;
      const ACaption: string; out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;
    function TryEditMessageCaption(const AChatId: TTgChatId; AMessageId: Int64;
      const ACaption: string; const AOptions: TTgEditMessageCaptionOptions; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   editMessageCaption (вариант: inline_message_id, caption). Inline-сообщение (отправленное
    ///   через inline-режим). Результат True — запрос выполнен (Bot API вернул true). Поля AOptions
    ///   (InlineMessageId, Caption) заменяются значениями параметров.
    /// </summary>
    function EditInlineMessageCaption(const AInlineMessageId: string;
      const ACaption: string): Boolean; overload;
    function EditInlineMessageCaption(const AInlineMessageId: string; const ACaption: string;
      const AOptions: TTgEditMessageCaptionOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный EditInlineMessageCaption (editMessageCaption, вариант): параметры проверяются
    ///   и строятся в вызывающем потоке (ошибки — исключением здесь же), колбэки вызываются в
    ///   рабочем потоке.
    /// </summary>
    function EditInlineMessageCaptionAsync(const AInlineMessageId: string; const ACaption: string;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function EditInlineMessageCaptionAsync(const AInlineMessageId: string; const ACaption: string;
      const AOptions: TTgEditMessageCaptionOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   EditInlineMessageCaption (editMessageCaption, вариант) без исключений: False и сведения об
    ///   ошибке в AError.
    /// </summary>
    function TryEditInlineMessageCaption(const AInlineMessageId: string; const ACaption: string;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryEditInlineMessageCaption(const AInlineMessageId: string; const ACaption: string;
      const AOptions: TTgEditMessageCaptionOptions; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   editMessageMedia: Use this method to edit animation, audio, document, live photo, photo,
    ///   or video messages, or to replace a text or a rich message with a media. If a message is
    ///   part of a message album, then it can be edited only to an audio for audio albums, only to
    ///   a document for document albums and to a photo, a live photo, or a video otherwise. When an
    ///   inline message is edited, a new file can't be uploaded; use a previously uploaded file via
    ///   its file_id or specify a URL. On success, if the edited message is not an inline message,
    ///   the edited Message is returned, otherwise True is returned. Note that business messages
    ///   that were not sent by the bot and do not contain an inline keyboard can only be edited
    ///   within 48 hours from the time they were sent.
    /// </summary>
    function EditMessageMedia(const AMedia: TTgInputMedia): ITgMessage; overload;
    function EditMessageMedia(const AMedia: TTgInputMedia;
      const AOptions: TTgEditMessageMediaOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный editMessageMedia: параметры проверяются и строятся в вызывающем потоке (ошибки
    ///   — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function EditMessageMediaAsync(const AMedia: TTgInputMedia; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function EditMessageMediaAsync(const AMedia: TTgInputMedia;
      const AOptions: TTgEditMessageMediaOptions; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   editMessageMedia без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryEditMessageMedia(const AMedia: TTgInputMedia; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryEditMessageMedia(const AMedia: TTgInputMedia;
      const AOptions: TTgEditMessageMediaOptions; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   editMessageMedia (вариант: chat_id, message_id, media). Сообщение, отправленное от имени
    ///   бота (не inline). Поля AOptions (ChatId, MessageId) заменяются значениями параметров.
    /// </summary>
    function EditMessageMedia(const AChatId: TTgChatId; AMessageId: Int64;
      const AMedia: TTgInputMedia): ITgMessage; overload;
    function EditMessageMedia(const AChatId: TTgChatId; AMessageId: Int64;
      const AMedia: TTgInputMedia;
      const AOptions: TTgEditMessageMediaOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный EditMessageMedia (editMessageMedia, вариант): параметры проверяются и строятся
    ///   в вызывающем потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function EditMessageMediaAsync(const AChatId: TTgChatId; AMessageId: Int64;
      const AMedia: TTgInputMedia; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function EditMessageMediaAsync(const AChatId: TTgChatId; AMessageId: Int64;
      const AMedia: TTgInputMedia; const AOptions: TTgEditMessageMediaOptions;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   EditMessageMedia (editMessageMedia, вариант) без исключений: False и сведения об ошибке в
    ///   AError.
    /// </summary>
    function TryEditMessageMedia(const AChatId: TTgChatId; AMessageId: Int64;
      const AMedia: TTgInputMedia; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryEditMessageMedia(const AChatId: TTgChatId; AMessageId: Int64;
      const AMedia: TTgInputMedia; const AOptions: TTgEditMessageMediaOptions;
      out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   editMessageMedia (вариант: inline_message_id, media). Inline-сообщение (отправленное через
    ///   inline-режим). Результат True — запрос выполнен (Bot API вернул true). Поля AOptions
    ///   (InlineMessageId) заменяются значениями параметров.
    /// </summary>
    function EditInlineMessageMedia(const AInlineMessageId: string;
      const AMedia: TTgInputMedia): Boolean; overload;
    function EditInlineMessageMedia(const AInlineMessageId: string; const AMedia: TTgInputMedia;
      const AOptions: TTgEditMessageMediaOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный EditInlineMessageMedia (editMessageMedia, вариант): параметры проверяются и
    ///   строятся в вызывающем потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем
    ///   потоке.
    /// </summary>
    function EditInlineMessageMediaAsync(const AInlineMessageId: string;
      const AMedia: TTgInputMedia; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function EditInlineMessageMediaAsync(const AInlineMessageId: string;
      const AMedia: TTgInputMedia; const AOptions: TTgEditMessageMediaOptions;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   EditInlineMessageMedia (editMessageMedia, вариант) без исключений: False и сведения об
    ///   ошибке в AError.
    /// </summary>
    function TryEditInlineMessageMedia(const AInlineMessageId: string; const AMedia: TTgInputMedia;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryEditInlineMessageMedia(const AInlineMessageId: string; const AMedia: TTgInputMedia;
      const AOptions: TTgEditMessageMediaOptions; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   editMessageLiveLocation: Use this method to edit live location messages. A location can be
    ///   edited until its live_period expires or editing is explicitly disabled by a call to
    ///   stopMessageLiveLocation. On success, if the edited message is not an inline message, the
    ///   edited Message is returned, otherwise True is returned.
    /// </summary>
    function EditMessageLiveLocation(ALatitude: Double; ALongitude: Double): ITgMessage; overload;
    function EditMessageLiveLocation(ALatitude: Double; ALongitude: Double;
      const AOptions: TTgEditMessageLiveLocationOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный editMessageLiveLocation: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function EditMessageLiveLocationAsync(ALatitude: Double; ALongitude: Double;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function EditMessageLiveLocationAsync(ALatitude: Double; ALongitude: Double;
      const AOptions: TTgEditMessageLiveLocationOptions; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   editMessageLiveLocation без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryEditMessageLiveLocation(ALatitude: Double; ALongitude: Double;
      out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;
    function TryEditMessageLiveLocation(ALatitude: Double; ALongitude: Double;
      const AOptions: TTgEditMessageLiveLocationOptions; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   editMessageLiveLocation (вариант: chat_id, message_id, latitude, longitude). Сообщение,
    ///   отправленное от имени бота (не inline). Поля AOptions (ChatId, MessageId) заменяются
    ///   значениями параметров.
    /// </summary>
    function EditMessageLiveLocation(const AChatId: TTgChatId; AMessageId: Int64; ALatitude: Double;
      ALongitude: Double): ITgMessage; overload;
    function EditMessageLiveLocation(const AChatId: TTgChatId; AMessageId: Int64; ALatitude: Double;
      ALongitude: Double; const AOptions: TTgEditMessageLiveLocationOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный EditMessageLiveLocation (editMessageLiveLocation, вариант): параметры
    ///   проверяются и строятся в вызывающем потоке (ошибки — исключением здесь же), колбэки
    ///   вызываются в рабочем потоке.
    /// </summary>
    function EditMessageLiveLocationAsync(const AChatId: TTgChatId; AMessageId: Int64;
      ALatitude: Double; ALongitude: Double; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function EditMessageLiveLocationAsync(const AChatId: TTgChatId; AMessageId: Int64;
      ALatitude: Double; ALongitude: Double; const AOptions: TTgEditMessageLiveLocationOptions;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   EditMessageLiveLocation (editMessageLiveLocation, вариант) без исключений: False и
    ///   сведения об ошибке в AError.
    /// </summary>
    function TryEditMessageLiveLocation(const AChatId: TTgChatId; AMessageId: Int64;
      ALatitude: Double; ALongitude: Double; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryEditMessageLiveLocation(const AChatId: TTgChatId; AMessageId: Int64;
      ALatitude: Double; ALongitude: Double; const AOptions: TTgEditMessageLiveLocationOptions;
      out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   editMessageLiveLocation (вариант: inline_message_id, latitude, longitude).
    ///   Inline-сообщение (отправленное через inline-режим). Результат True — запрос выполнен (Bot
    ///   API вернул true). Поля AOptions (InlineMessageId) заменяются значениями параметров.
    /// </summary>
    function EditInlineMessageLiveLocation(const AInlineMessageId: string; ALatitude: Double;
      ALongitude: Double): Boolean; overload;
    function EditInlineMessageLiveLocation(const AInlineMessageId: string; ALatitude: Double;
      ALongitude: Double; const AOptions: TTgEditMessageLiveLocationOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный EditInlineMessageLiveLocation (editMessageLiveLocation, вариант): параметры
    ///   проверяются и строятся в вызывающем потоке (ошибки — исключением здесь же), колбэки
    ///   вызываются в рабочем потоке.
    /// </summary>
    function EditInlineMessageLiveLocationAsync(const AInlineMessageId: string; ALatitude: Double;
      ALongitude: Double; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function EditInlineMessageLiveLocationAsync(const AInlineMessageId: string; ALatitude: Double;
      ALongitude: Double; const AOptions: TTgEditMessageLiveLocationOptions;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   EditInlineMessageLiveLocation (editMessageLiveLocation, вариант) без исключений: False и
    ///   сведения об ошибке в AError.
    /// </summary>
    function TryEditInlineMessageLiveLocation(const AInlineMessageId: string; ALatitude: Double;
      ALongitude: Double; out AError: TTgErrorInfo): Boolean; overload;
    function TryEditInlineMessageLiveLocation(const AInlineMessageId: string; ALatitude: Double;
      ALongitude: Double; const AOptions: TTgEditMessageLiveLocationOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   stopMessageLiveLocation: Use this method to stop updating a live location message before
    ///   live_period expires. On success, if the message is not an inline message, the edited
    ///   Message is returned, otherwise True is returned.
    /// </summary>
    function StopMessageLiveLocation: ITgMessage; overload;
    function StopMessageLiveLocation(const AOptions: TTgStopMessageLiveLocationOptions): ITgMessage;
      overload;
    /// <summary>
    ///   Асинхронный stopMessageLiveLocation: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function StopMessageLiveLocationAsync(const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function StopMessageLiveLocationAsync(const AOptions: TTgStopMessageLiveLocationOptions;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   stopMessageLiveLocation без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryStopMessageLiveLocation(out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
      overload;
    function TryStopMessageLiveLocation(const AOptions: TTgStopMessageLiveLocationOptions;
      out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   stopMessageLiveLocation (вариант: chat_id, message_id). Сообщение, отправленное от имени
    ///   бота (не inline). Поля AOptions (ChatId, MessageId) заменяются значениями параметров.
    /// </summary>
    function StopMessageLiveLocation(const AChatId: TTgChatId; AMessageId: Int64): ITgMessage;
      overload;
    function StopMessageLiveLocation(const AChatId: TTgChatId; AMessageId: Int64;
      const AOptions: TTgStopMessageLiveLocationOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный StopMessageLiveLocation (stopMessageLiveLocation, вариант): параметры
    ///   проверяются и строятся в вызывающем потоке (ошибки — исключением здесь же), колбэки
    ///   вызываются в рабочем потоке.
    /// </summary>
    function StopMessageLiveLocationAsync(const AChatId: TTgChatId; AMessageId: Int64;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function StopMessageLiveLocationAsync(const AChatId: TTgChatId; AMessageId: Int64;
      const AOptions: TTgStopMessageLiveLocationOptions; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   StopMessageLiveLocation (stopMessageLiveLocation, вариант) без исключений: False и
    ///   сведения об ошибке в AError.
    /// </summary>
    function TryStopMessageLiveLocation(const AChatId: TTgChatId; AMessageId: Int64;
      out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;
    function TryStopMessageLiveLocation(const AChatId: TTgChatId; AMessageId: Int64;
      const AOptions: TTgStopMessageLiveLocationOptions; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   stopMessageLiveLocation (вариант: inline_message_id). Inline-сообщение (отправленное через
    ///   inline-режим). Результат True — запрос выполнен (Bot API вернул true). Поля AOptions
    ///   (InlineMessageId) заменяются значениями параметров.
    /// </summary>
    function StopInlineMessageLiveLocation(const AInlineMessageId: string): Boolean; overload;
    function StopInlineMessageLiveLocation(const AInlineMessageId: string;
      const AOptions: TTgStopMessageLiveLocationOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный StopInlineMessageLiveLocation (stopMessageLiveLocation, вариант): параметры
    ///   проверяются и строятся в вызывающем потоке (ошибки — исключением здесь же), колбэки
    ///   вызываются в рабочем потоке.
    /// </summary>
    function StopInlineMessageLiveLocationAsync(const AInlineMessageId: string;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function StopInlineMessageLiveLocationAsync(const AInlineMessageId: string;
      const AOptions: TTgStopMessageLiveLocationOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   StopInlineMessageLiveLocation (stopMessageLiveLocation, вариант) без исключений: False и
    ///   сведения об ошибке в AError.
    /// </summary>
    function TryStopInlineMessageLiveLocation(const AInlineMessageId: string;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryStopInlineMessageLiveLocation(const AInlineMessageId: string;
      const AOptions: TTgStopMessageLiveLocationOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   editMessageChecklist: Use this method to edit a checklist on behalf of a connected
    ///   business account. On success, the edited Message is returned.
    /// </summary>
    function EditMessageChecklist(const ABusinessConnectionId: string; const AChatId: TTgChatId;
      AMessageId: Int64; const AChecklist: ITgInputChecklist): ITgMessage; overload;
    function EditMessageChecklist(const ABusinessConnectionId: string; const AChatId: TTgChatId;
      AMessageId: Int64; const AChecklist: ITgInputChecklist;
      const AOptions: TTgEditMessageChecklistOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный editMessageChecklist: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function EditMessageChecklistAsync(const ABusinessConnectionId: string;
      const AChatId: TTgChatId; AMessageId: Int64; const AChecklist: ITgInputChecklist;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function EditMessageChecklistAsync(const ABusinessConnectionId: string;
      const AChatId: TTgChatId; AMessageId: Int64; const AChecklist: ITgInputChecklist;
      const AOptions: TTgEditMessageChecklistOptions; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   editMessageChecklist без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryEditMessageChecklist(const ABusinessConnectionId: string; const AChatId: TTgChatId;
      AMessageId: Int64; const AChecklist: ITgInputChecklist; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryEditMessageChecklist(const ABusinessConnectionId: string; const AChatId: TTgChatId;
      AMessageId: Int64; const AChecklist: ITgInputChecklist;
      const AOptions: TTgEditMessageChecklistOptions; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   editMessageReplyMarkup: Use this method to edit only the reply markup of messages. On
    ///   success, if the edited message is not an inline message, the edited Message is returned,
    ///   otherwise True is returned. Note that business messages that were not sent by the bot and
    ///   do not contain an inline keyboard can only be edited within 48 hours from the time they
    ///   were sent.
    /// </summary>
    function EditMessageReplyMarkup: ITgMessage; overload;
    function EditMessageReplyMarkup(const AOptions: TTgEditMessageReplyMarkupOptions): ITgMessage;
      overload;
    /// <summary>
    ///   Асинхронный editMessageReplyMarkup: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function EditMessageReplyMarkupAsync(const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function EditMessageReplyMarkupAsync(const AOptions: TTgEditMessageReplyMarkupOptions;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   editMessageReplyMarkup без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryEditMessageReplyMarkup(out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
      overload;
    function TryEditMessageReplyMarkup(const AOptions: TTgEditMessageReplyMarkupOptions;
      out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   editMessageReplyMarkup (вариант: chat_id, message_id, reply_markup). Сообщение,
    ///   отправленное от имени бота (не inline); AReplyMarkup = nil убирает клавиатуру. Поля
    ///   AOptions (ChatId, MessageId, ReplyMarkup) заменяются значениями параметров.
    /// </summary>
    function EditMessageReplyMarkup(const AChatId: TTgChatId; AMessageId: Int64;
      const AReplyMarkup: ITgInlineKeyboardMarkup): ITgMessage; overload;
    function EditMessageReplyMarkup(const AChatId: TTgChatId; AMessageId: Int64;
      const AReplyMarkup: ITgInlineKeyboardMarkup;
      const AOptions: TTgEditMessageReplyMarkupOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный EditMessageReplyMarkup (editMessageReplyMarkup, вариант): параметры
    ///   проверяются и строятся в вызывающем потоке (ошибки — исключением здесь же), колбэки
    ///   вызываются в рабочем потоке.
    /// </summary>
    function EditMessageReplyMarkupAsync(const AChatId: TTgChatId; AMessageId: Int64;
      const AReplyMarkup: ITgInlineKeyboardMarkup; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function EditMessageReplyMarkupAsync(const AChatId: TTgChatId; AMessageId: Int64;
      const AReplyMarkup: ITgInlineKeyboardMarkup; const AOptions: TTgEditMessageReplyMarkupOptions;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   EditMessageReplyMarkup (editMessageReplyMarkup, вариант) без исключений: False и сведения
    ///   об ошибке в AError.
    /// </summary>
    function TryEditMessageReplyMarkup(const AChatId: TTgChatId; AMessageId: Int64;
      const AReplyMarkup: ITgInlineKeyboardMarkup; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryEditMessageReplyMarkup(const AChatId: TTgChatId; AMessageId: Int64;
      const AReplyMarkup: ITgInlineKeyboardMarkup; const AOptions: TTgEditMessageReplyMarkupOptions;
      out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   editMessageReplyMarkup (вариант: inline_message_id, reply_markup). Inline-сообщение
    ///   (отправленное через inline-режим); AReplyMarkup = nil убирает клавиатуру. Результат True —
    ///   запрос выполнен (Bot API вернул true). Поля AOptions (InlineMessageId, ReplyMarkup)
    ///   заменяются значениями параметров.
    /// </summary>
    function EditInlineMessageReplyMarkup(const AInlineMessageId: string;
      const AReplyMarkup: ITgInlineKeyboardMarkup): Boolean; overload;
    function EditInlineMessageReplyMarkup(const AInlineMessageId: string;
      const AReplyMarkup: ITgInlineKeyboardMarkup;
      const AOptions: TTgEditMessageReplyMarkupOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный EditInlineMessageReplyMarkup (editMessageReplyMarkup, вариант): параметры
    ///   проверяются и строятся в вызывающем потоке (ошибки — исключением здесь же), колбэки
    ///   вызываются в рабочем потоке.
    /// </summary>
    function EditInlineMessageReplyMarkupAsync(const AInlineMessageId: string;
      const AReplyMarkup: ITgInlineKeyboardMarkup; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function EditInlineMessageReplyMarkupAsync(const AInlineMessageId: string;
      const AReplyMarkup: ITgInlineKeyboardMarkup; const AOptions: TTgEditMessageReplyMarkupOptions;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   EditInlineMessageReplyMarkup (editMessageReplyMarkup, вариант) без исключений: False и
    ///   сведения об ошибке в AError.
    /// </summary>
    function TryEditInlineMessageReplyMarkup(const AInlineMessageId: string;
      const AReplyMarkup: ITgInlineKeyboardMarkup; out AError: TTgErrorInfo): Boolean; overload;
    function TryEditInlineMessageReplyMarkup(const AInlineMessageId: string;
      const AReplyMarkup: ITgInlineKeyboardMarkup; const AOptions: TTgEditMessageReplyMarkupOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   stopPoll: Use this method to stop a poll which was sent by the bot. On success, the
    ///   stopped Poll is returned.
    /// </summary>
    function StopPoll(const AChatId: TTgChatId; AMessageId: Int64): ITgPoll; overload;
    function StopPoll(const AChatId: TTgChatId; AMessageId: Int64;
      const AOptions: TTgStopPollOptions): ITgPoll; overload;
    /// <summary>
    ///   Асинхронный stopPoll: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function StopPollAsync(const AChatId: TTgChatId; AMessageId: Int64;
      const AOnSuccess: TProc<ITgPoll>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function StopPollAsync(const AChatId: TTgChatId; AMessageId: Int64;
      const AOptions: TTgStopPollOptions; const AOnSuccess: TProc<ITgPoll>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>stopPoll без исключений: False и сведения об ошибке в AError.</summary>
    function TryStopPoll(const AChatId: TTgChatId; AMessageId: Int64; out AResult: ITgPoll;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryStopPoll(const AChatId: TTgChatId; AMessageId: Int64;
      const AOptions: TTgStopPollOptions; out AResult: ITgPoll;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   editEphemeralMessageText: Use this method to edit an ephemeral text or rich message. Note
    ///   that it is not guaranteed that the user will receive the message edit event, especially if
    ///   they are offline. On success, True is returned.
    /// </summary>
    function EditEphemeralMessageText(const AChatId: TTgChatId; AReceiverUserId: Int64;
      AEphemeralMessageId: Int64): Boolean; overload;
    function EditEphemeralMessageText(const AChatId: TTgChatId; AReceiverUserId: Int64;
      AEphemeralMessageId: Int64;
      const AOptions: TTgEditEphemeralMessageTextOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный editEphemeralMessageText: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function EditEphemeralMessageTextAsync(const AChatId: TTgChatId; AReceiverUserId: Int64;
      AEphemeralMessageId: Int64; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function EditEphemeralMessageTextAsync(const AChatId: TTgChatId; AReceiverUserId: Int64;
      AEphemeralMessageId: Int64; const AOptions: TTgEditEphemeralMessageTextOptions;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   editEphemeralMessageText без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryEditEphemeralMessageText(const AChatId: TTgChatId; AReceiverUserId: Int64;
      AEphemeralMessageId: Int64; out AError: TTgErrorInfo): Boolean; overload;
    function TryEditEphemeralMessageText(const AChatId: TTgChatId; AReceiverUserId: Int64;
      AEphemeralMessageId: Int64; const AOptions: TTgEditEphemeralMessageTextOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   editEphemeralMessageMedia: Use this method to edit the media of an ephemeral message. Note
    ///   that it is not guaranteed that the user will receive the message edit event, especially if
    ///   they are offline. On success, True is returned.
    /// </summary>
    function EditEphemeralMessageMedia(const AChatId: TTgChatId; AReceiverUserId: Int64;
      AEphemeralMessageId: Int64; const AMedia: TTgInputMedia): Boolean; overload;
    function EditEphemeralMessageMedia(const AChatId: TTgChatId; AReceiverUserId: Int64;
      AEphemeralMessageId: Int64; const AMedia: TTgInputMedia;
      const AOptions: TTgEditEphemeralMessageMediaOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный editEphemeralMessageMedia: параметры проверяются и строятся в вызывающем
    ///   потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function EditEphemeralMessageMediaAsync(const AChatId: TTgChatId; AReceiverUserId: Int64;
      AEphemeralMessageId: Int64; const AMedia: TTgInputMedia; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function EditEphemeralMessageMediaAsync(const AChatId: TTgChatId; AReceiverUserId: Int64;
      AEphemeralMessageId: Int64; const AMedia: TTgInputMedia;
      const AOptions: TTgEditEphemeralMessageMediaOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   editEphemeralMessageMedia без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryEditEphemeralMessageMedia(const AChatId: TTgChatId; AReceiverUserId: Int64;
      AEphemeralMessageId: Int64; const AMedia: TTgInputMedia;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryEditEphemeralMessageMedia(const AChatId: TTgChatId; AReceiverUserId: Int64;
      AEphemeralMessageId: Int64; const AMedia: TTgInputMedia;
      const AOptions: TTgEditEphemeralMessageMediaOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   editEphemeralMessageCaption: Use this method to edit the caption of an ephemeral message.
    ///   Note that it is not guaranteed that the user will receive the message edit event,
    ///   especially if they are offline. On success, True is returned.
    /// </summary>
    function EditEphemeralMessageCaption(const AChatId: TTgChatId; AReceiverUserId: Int64;
      AEphemeralMessageId: Int64): Boolean; overload;
    function EditEphemeralMessageCaption(const AChatId: TTgChatId; AReceiverUserId: Int64;
      AEphemeralMessageId: Int64;
      const AOptions: TTgEditEphemeralMessageCaptionOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный editEphemeralMessageCaption: параметры проверяются и строятся в вызывающем
    ///   потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function EditEphemeralMessageCaptionAsync(const AChatId: TTgChatId; AReceiverUserId: Int64;
      AEphemeralMessageId: Int64; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function EditEphemeralMessageCaptionAsync(const AChatId: TTgChatId; AReceiverUserId: Int64;
      AEphemeralMessageId: Int64; const AOptions: TTgEditEphemeralMessageCaptionOptions;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   editEphemeralMessageCaption без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryEditEphemeralMessageCaption(const AChatId: TTgChatId; AReceiverUserId: Int64;
      AEphemeralMessageId: Int64; out AError: TTgErrorInfo): Boolean; overload;
    function TryEditEphemeralMessageCaption(const AChatId: TTgChatId; AReceiverUserId: Int64;
      AEphemeralMessageId: Int64; const AOptions: TTgEditEphemeralMessageCaptionOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   editEphemeralMessageReplyMarkup: Use this method to edit only the reply markup of an
    ///   ephemeral message. Note that it is not guaranteed that the user will receive the message
    ///   edit event, especially if they are offline. On success, True is returned.
    /// </summary>
    function EditEphemeralMessageReplyMarkup(const AChatId: TTgChatId; AReceiverUserId: Int64;
      AEphemeralMessageId: Int64): Boolean; overload;
    function EditEphemeralMessageReplyMarkup(const AChatId: TTgChatId; AReceiverUserId: Int64;
      AEphemeralMessageId: Int64;
      const AOptions: TTgEditEphemeralMessageReplyMarkupOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный editEphemeralMessageReplyMarkup: параметры проверяются и строятся в вызывающем
    ///   потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function EditEphemeralMessageReplyMarkupAsync(const AChatId: TTgChatId; AReceiverUserId: Int64;
      AEphemeralMessageId: Int64; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function EditEphemeralMessageReplyMarkupAsync(const AChatId: TTgChatId; AReceiverUserId: Int64;
      AEphemeralMessageId: Int64; const AOptions: TTgEditEphemeralMessageReplyMarkupOptions;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   editEphemeralMessageReplyMarkup без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryEditEphemeralMessageReplyMarkup(const AChatId: TTgChatId; AReceiverUserId: Int64;
      AEphemeralMessageId: Int64; out AError: TTgErrorInfo): Boolean; overload;
    function TryEditEphemeralMessageReplyMarkup(const AChatId: TTgChatId; AReceiverUserId: Int64;
      AEphemeralMessageId: Int64; const AOptions: TTgEditEphemeralMessageReplyMarkupOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   approveSuggestedPost: Use this method to approve a suggested post in a direct messages
    ///   chat. The bot must have the 'can_post_messages' administrator right in the corresponding
    ///   channel chat. Returns True on success.
    /// </summary>
    function ApproveSuggestedPost(AChatId: Int64; AMessageId: Int64): Boolean; overload;
    function ApproveSuggestedPost(AChatId: Int64; AMessageId: Int64;
      const AOptions: TTgApproveSuggestedPostOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный approveSuggestedPost: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function ApproveSuggestedPostAsync(AChatId: Int64; AMessageId: Int64;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function ApproveSuggestedPostAsync(AChatId: Int64; AMessageId: Int64;
      const AOptions: TTgApproveSuggestedPostOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   approveSuggestedPost без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryApproveSuggestedPost(AChatId: Int64; AMessageId: Int64;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryApproveSuggestedPost(AChatId: Int64; AMessageId: Int64;
      const AOptions: TTgApproveSuggestedPostOptions; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   declineSuggestedPost: Use this method to decline a suggested post in a direct messages
    ///   chat. The bot must have the 'can_manage_direct_messages' administrator right in the
    ///   corresponding channel chat. Returns True on success.
    /// </summary>
    function DeclineSuggestedPost(AChatId: Int64; AMessageId: Int64): Boolean; overload;
    function DeclineSuggestedPost(AChatId: Int64; AMessageId: Int64;
      const AOptions: TTgDeclineSuggestedPostOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный declineSuggestedPost: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function DeclineSuggestedPostAsync(AChatId: Int64; AMessageId: Int64;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function DeclineSuggestedPostAsync(AChatId: Int64; AMessageId: Int64;
      const AOptions: TTgDeclineSuggestedPostOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   declineSuggestedPost без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryDeclineSuggestedPost(AChatId: Int64; AMessageId: Int64;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryDeclineSuggestedPost(AChatId: Int64; AMessageId: Int64;
      const AOptions: TTgDeclineSuggestedPostOptions; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   deleteMessage: Use this method to delete a message, including service messages, with the
    ///   following limitations:
    /// </summary>
    function DeleteMessage(const AChatId: TTgChatId; AMessageId: Int64): Boolean; overload;
    /// <summary>
    ///   Асинхронный deleteMessage: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function DeleteMessageAsync(const AChatId: TTgChatId; AMessageId: Int64;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   deleteMessage без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryDeleteMessage(const AChatId: TTgChatId; AMessageId: Int64;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   deleteMessages: Use this method to delete multiple messages simultaneously. If some of the
    ///   specified messages can't be found, they are skipped. Returns True on success.
    /// </summary>
    function DeleteMessages(const AChatId: TTgChatId; const AMessageIds: TArray<Int64>): Boolean;
      overload;
    /// <summary>
    ///   Асинхронный deleteMessages: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function DeleteMessagesAsync(const AChatId: TTgChatId; const AMessageIds: TArray<Int64>;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   deleteMessages без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryDeleteMessages(const AChatId: TTgChatId; const AMessageIds: TArray<Int64>;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   deleteEphemeralMessage: Use this method to delete an ephemeral message. Note that it is
    ///   not guaranteed that the user will receive the message deletion event, especially if they
    ///   are offline. Returns True on success.
    /// </summary>
    function DeleteEphemeralMessage(const AChatId: TTgChatId; AReceiverUserId: Int64;
      AEphemeralMessageId: Int64): Boolean; overload;
    /// <summary>
    ///   Асинхронный deleteEphemeralMessage: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function DeleteEphemeralMessageAsync(const AChatId: TTgChatId; AReceiverUserId: Int64;
      AEphemeralMessageId: Int64; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   deleteEphemeralMessage без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryDeleteEphemeralMessage(const AChatId: TTgChatId; AReceiverUserId: Int64;
      AEphemeralMessageId: Int64; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   deleteMessageReaction: Use this method to remove a reaction from a message in a group or a
    ///   supergroup chat. The bot must have the 'can_delete_messages' administrator right in the
    ///   chat. Returns True on success.
    /// </summary>
    function DeleteMessageReaction(const AChatId: TTgChatId; AMessageId: Int64): Boolean; overload;
    function DeleteMessageReaction(const AChatId: TTgChatId; AMessageId: Int64;
      const AOptions: TTgDeleteMessageReactionOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный deleteMessageReaction: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function DeleteMessageReactionAsync(const AChatId: TTgChatId; AMessageId: Int64;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function DeleteMessageReactionAsync(const AChatId: TTgChatId; AMessageId: Int64;
      const AOptions: TTgDeleteMessageReactionOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   deleteMessageReaction без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryDeleteMessageReaction(const AChatId: TTgChatId; AMessageId: Int64;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryDeleteMessageReaction(const AChatId: TTgChatId; AMessageId: Int64;
      const AOptions: TTgDeleteMessageReactionOptions; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   deleteAllMessageReactions: Use this method to remove up to 10000 recent reactions in a
    ///   group or a supergroup chat added by a given user or chat. The bot must have the
    ///   'can_delete_messages' administrator right in the chat. Returns True on success.
    /// </summary>
    function DeleteAllMessageReactions(const AChatId: TTgChatId): Boolean; overload;
    function DeleteAllMessageReactions(const AChatId: TTgChatId;
      const AOptions: TTgDeleteAllMessageReactionsOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный deleteAllMessageReactions: параметры проверяются и строятся в вызывающем
    ///   потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function DeleteAllMessageReactionsAsync(const AChatId: TTgChatId;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function DeleteAllMessageReactionsAsync(const AChatId: TTgChatId;
      const AOptions: TTgDeleteAllMessageReactionsOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   deleteAllMessageReactions без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryDeleteAllMessageReactions(const AChatId: TTgChatId;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryDeleteAllMessageReactions(const AChatId: TTgChatId;
      const AOptions: TTgDeleteAllMessageReactionsOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   sendSticker: Use this method to send static .WEBP, animated .TGS, or video .WEBM stickers.
    ///   On success, the sent Message is returned.
    /// </summary>
    function SendSticker(const AChatId: TTgChatId; const ASticker: TTgInputFile): ITgMessage;
      overload;
    function SendSticker(const AChatId: TTgChatId; const ASticker: TTgInputFile;
      const AOptions: TTgSendStickerOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный sendSticker: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SendStickerAsync(const AChatId: TTgChatId; const ASticker: TTgInputFile;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function SendStickerAsync(const AChatId: TTgChatId; const ASticker: TTgInputFile;
      const AOptions: TTgSendStickerOptions; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>sendSticker без исключений: False и сведения об ошибке в AError.</summary>
    function TrySendSticker(const AChatId: TTgChatId; const ASticker: TTgInputFile;
      out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;
    function TrySendSticker(const AChatId: TTgChatId; const ASticker: TTgInputFile;
      const AOptions: TTgSendStickerOptions; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   getStickerSet: Use this method to get a sticker set. On success, a StickerSet object is
    ///   returned.
    /// </summary>
    function GetStickerSet(const AName: string): ITgStickerSet; overload;
    /// <summary>
    ///   Асинхронный getStickerSet: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetStickerSetAsync(const AName: string; const AOnSuccess: TProc<ITgStickerSet>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   getStickerSet без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryGetStickerSet(const AName: string; out AResult: ITgStickerSet;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   getCustomEmojiStickers: Use this method to get information about custom emoji stickers by
    ///   their identifiers. Returns an Array of Sticker objects. Элементы результата разделяют JSON
    ///   всего ответа и удерживают его; для длительного хранения отдельных элементов используйте
    ///   TTgDto.Detach.
    /// </summary>
    function GetCustomEmojiStickers(const ACustomEmojiIds: TArray<string>): TArray<ITgSticker>;
      overload;
    /// <summary>
    ///   Асинхронный getCustomEmojiStickers: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetCustomEmojiStickersAsync(const ACustomEmojiIds: TArray<string>;
      const AOnSuccess: TProc<TArray<ITgSticker>>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   getCustomEmojiStickers без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryGetCustomEmojiStickers(const ACustomEmojiIds: TArray<string>;
      out AResult: TArray<ITgSticker>; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   uploadStickerFile: Use this method to upload a file with a sticker for later use in the
    ///   createNewStickerSet, addStickerToSet, or replaceStickerInSet methods (the file can be used
    ///   multiple times). Returns the uploaded File on success.
    /// </summary>
    function UploadStickerFile(AUserId: Int64; const ASticker: TTgInputFile;
      const AStickerFormat: string): ITgFile; overload;
    /// <summary>
    ///   Асинхронный uploadStickerFile: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function UploadStickerFileAsync(AUserId: Int64; const ASticker: TTgInputFile;
      const AStickerFormat: string; const AOnSuccess: TProc<ITgFile>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   uploadStickerFile без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryUploadStickerFile(AUserId: Int64; const ASticker: TTgInputFile;
      const AStickerFormat: string; out AResult: ITgFile;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   createNewStickerSet: Use this method to create a new sticker set owned by a user. The bot
    ///   will be able to edit the sticker set thus created. Returns True on success.
    /// </summary>
    function CreateNewStickerSet(AUserId: Int64; const AName: string; const ATitle: string;
      const AStickers: array of ITgInputSticker): Boolean; overload;
    function CreateNewStickerSet(AUserId: Int64; const AName: string; const ATitle: string;
      const AStickers: array of ITgInputSticker;
      const AOptions: TTgCreateNewStickerSetOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный createNewStickerSet: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function CreateNewStickerSetAsync(AUserId: Int64; const AName: string; const ATitle: string;
      const AStickers: array of ITgInputSticker; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function CreateNewStickerSetAsync(AUserId: Int64; const AName: string; const ATitle: string;
      const AStickers: array of ITgInputSticker; const AOptions: TTgCreateNewStickerSetOptions;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   createNewStickerSet без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryCreateNewStickerSet(AUserId: Int64; const AName: string; const ATitle: string;
      const AStickers: array of ITgInputSticker; out AError: TTgErrorInfo): Boolean; overload;
    function TryCreateNewStickerSet(AUserId: Int64; const AName: string; const ATitle: string;
      const AStickers: array of ITgInputSticker; const AOptions: TTgCreateNewStickerSetOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   addStickerToSet: Use this method to add a new sticker to a set created by the bot. Emoji
    ///   sticker sets can have up to 200 stickers. Other sticker sets can have up to 120 stickers.
    ///   Returns True on success.
    /// </summary>
    function AddStickerToSet(AUserId: Int64; const AName: string;
      const ASticker: ITgInputSticker): Boolean; overload;
    /// <summary>
    ///   Асинхронный addStickerToSet: параметры проверяются и строятся в вызывающем потоке (ошибки
    ///   — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function AddStickerToSetAsync(AUserId: Int64; const AName: string;
      const ASticker: ITgInputSticker; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   addStickerToSet без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryAddStickerToSet(AUserId: Int64; const AName: string;
      const ASticker: ITgInputSticker; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setStickerPositionInSet: Use this method to move a sticker in a set created by the bot to
    ///   a specific position. Returns True on success.
    /// </summary>
    function SetStickerPositionInSet(const ASticker: string; APosition: Integer): Boolean; overload;
    /// <summary>
    ///   Асинхронный setStickerPositionInSet: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetStickerPositionInSetAsync(const ASticker: string; APosition: Integer;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   setStickerPositionInSet без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySetStickerPositionInSet(const ASticker: string; APosition: Integer;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   deleteStickerFromSet: Use this method to delete a sticker from a set created by the bot.
    ///   Returns True on success.
    /// </summary>
    function DeleteStickerFromSet(const ASticker: string): Boolean; overload;
    /// <summary>
    ///   Асинхронный deleteStickerFromSet: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function DeleteStickerFromSetAsync(const ASticker: string; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   deleteStickerFromSet без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryDeleteStickerFromSet(const ASticker: string; out AError: TTgErrorInfo): Boolean;
      overload;

    /// <summary>
    ///   replaceStickerInSet: Use this method to replace an existing sticker in a sticker set with
    ///   a new one. The method is equivalent to calling deleteStickerFromSet, then addStickerToSet,
    ///   then setStickerPositionInSet. Returns True on success.
    /// </summary>
    function ReplaceStickerInSet(AUserId: Int64; const AName: string; const AOldSticker: string;
      const ASticker: ITgInputSticker): Boolean; overload;
    /// <summary>
    ///   Асинхронный replaceStickerInSet: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function ReplaceStickerInSetAsync(AUserId: Int64; const AName: string;
      const AOldSticker: string; const ASticker: ITgInputSticker; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   replaceStickerInSet без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryReplaceStickerInSet(AUserId: Int64; const AName: string; const AOldSticker: string;
      const ASticker: ITgInputSticker; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setStickerEmojiList: Use this method to change the list of emoji assigned to a regular or
    ///   custom emoji sticker. The sticker must belong to a sticker set created by the bot. Returns
    ///   True on success.
    /// </summary>
    function SetStickerEmojiList(const ASticker: string; const AEmojiList: TArray<string>): Boolean;
      overload;
    /// <summary>
    ///   Асинхронный setStickerEmojiList: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetStickerEmojiListAsync(const ASticker: string; const AEmojiList: TArray<string>;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   setStickerEmojiList без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySetStickerEmojiList(const ASticker: string; const AEmojiList: TArray<string>;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setStickerKeywords: Use this method to change search keywords assigned to a regular or
    ///   custom emoji sticker. The sticker must belong to a sticker set created by the bot. Returns
    ///   True on success.
    /// </summary>
    function SetStickerKeywords(const ASticker: string): Boolean; overload;
    function SetStickerKeywords(const ASticker: string;
      const AOptions: TTgSetStickerKeywordsOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный setStickerKeywords: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetStickerKeywordsAsync(const ASticker: string; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function SetStickerKeywordsAsync(const ASticker: string;
      const AOptions: TTgSetStickerKeywordsOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   setStickerKeywords без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySetStickerKeywords(const ASticker: string; out AError: TTgErrorInfo): Boolean;
      overload;
    function TrySetStickerKeywords(const ASticker: string;
      const AOptions: TTgSetStickerKeywordsOptions; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setStickerMaskPosition: Use this method to change the mask position of a mask sticker. The
    ///   sticker must belong to a sticker set that was created by the bot. Returns True on success.
    /// </summary>
    function SetStickerMaskPosition(const ASticker: string): Boolean; overload;
    function SetStickerMaskPosition(const ASticker: string;
      const AOptions: TTgSetStickerMaskPositionOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный setStickerMaskPosition: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetStickerMaskPositionAsync(const ASticker: string; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function SetStickerMaskPositionAsync(const ASticker: string;
      const AOptions: TTgSetStickerMaskPositionOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   setStickerMaskPosition без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySetStickerMaskPosition(const ASticker: string; out AError: TTgErrorInfo): Boolean;
      overload;
    function TrySetStickerMaskPosition(const ASticker: string;
      const AOptions: TTgSetStickerMaskPositionOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setStickerSetTitle: Use this method to set the title of a created sticker set. Returns
    ///   True on success.
    /// </summary>
    function SetStickerSetTitle(const AName: string; const ATitle: string): Boolean; overload;
    /// <summary>
    ///   Асинхронный setStickerSetTitle: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetStickerSetTitleAsync(const AName: string; const ATitle: string;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   setStickerSetTitle без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySetStickerSetTitle(const AName: string; const ATitle: string;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setStickerSetThumbnail: Use this method to set the thumbnail of a regular or mask sticker
    ///   set. The format of the thumbnail file must match the format of the stickers in the set.
    ///   Returns True on success.
    /// </summary>
    function SetStickerSetThumbnail(const AName: string; AUserId: Int64;
      const AFormat: string): Boolean; overload;
    function SetStickerSetThumbnail(const AName: string; AUserId: Int64; const AFormat: string;
      const AOptions: TTgSetStickerSetThumbnailOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный setStickerSetThumbnail: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetStickerSetThumbnailAsync(const AName: string; AUserId: Int64; const AFormat: string;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function SetStickerSetThumbnailAsync(const AName: string; AUserId: Int64; const AFormat: string;
      const AOptions: TTgSetStickerSetThumbnailOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   setStickerSetThumbnail без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySetStickerSetThumbnail(const AName: string; AUserId: Int64; const AFormat: string;
      out AError: TTgErrorInfo): Boolean; overload;
    function TrySetStickerSetThumbnail(const AName: string; AUserId: Int64; const AFormat: string;
      const AOptions: TTgSetStickerSetThumbnailOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setCustomEmojiStickerSetThumbnail: Use this method to set the thumbnail of a custom emoji
    ///   sticker set. Returns True on success.
    /// </summary>
    function SetCustomEmojiStickerSetThumbnail(const AName: string): Boolean; overload;
    function SetCustomEmojiStickerSetThumbnail(const AName: string;
      const AOptions: TTgSetCustomEmojiStickerSetThumbnailOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный setCustomEmojiStickerSetThumbnail: параметры проверяются и строятся в
    ///   вызывающем потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetCustomEmojiStickerSetThumbnailAsync(const AName: string;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function SetCustomEmojiStickerSetThumbnailAsync(const AName: string;
      const AOptions: TTgSetCustomEmojiStickerSetThumbnailOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   setCustomEmojiStickerSetThumbnail без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySetCustomEmojiStickerSetThumbnail(const AName: string;
      out AError: TTgErrorInfo): Boolean; overload;
    function TrySetCustomEmojiStickerSetThumbnail(const AName: string;
      const AOptions: TTgSetCustomEmojiStickerSetThumbnailOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   deleteStickerSet: Use this method to delete a sticker set that was created by the bot.
    ///   Returns True on success.
    /// </summary>
    function DeleteStickerSet(const AName: string): Boolean; overload;
    /// <summary>
    ///   Асинхронный deleteStickerSet: параметры проверяются и строятся в вызывающем потоке (ошибки
    ///   — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function DeleteStickerSetAsync(const AName: string; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   deleteStickerSet без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryDeleteStickerSet(const AName: string; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   sendRichMessage: Use this method to send rich messages. If the message contains a block
    ///   with a media element, then the bot must have the right to send the media to the chat. On
    ///   success, the sent Message is returned.
    /// </summary>
    function SendRichMessage(const AChatId: TTgChatId;
      const ARichMessage: ITgInputRichMessage): ITgMessage; overload;
    function SendRichMessage(const AChatId: TTgChatId; const ARichMessage: ITgInputRichMessage;
      const AOptions: TTgSendRichMessageOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный sendRichMessage: параметры проверяются и строятся в вызывающем потоке (ошибки
    ///   — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SendRichMessageAsync(const AChatId: TTgChatId; const ARichMessage: ITgInputRichMessage;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function SendRichMessageAsync(const AChatId: TTgChatId; const ARichMessage: ITgInputRichMessage;
      const AOptions: TTgSendRichMessageOptions; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   sendRichMessage без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySendRichMessage(const AChatId: TTgChatId; const ARichMessage: ITgInputRichMessage;
      out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;
    function TrySendRichMessage(const AChatId: TTgChatId; const ARichMessage: ITgInputRichMessage;
      const AOptions: TTgSendRichMessageOptions; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   sendRichMessageDraft: Use this method to stream a partial rich message to a user while the
    ///   message is being generated. Note that the streamed draft is ephemeral and acts as a
    ///   temporary 30-second preview - once the output is finalized, you must call sendRichMessage
    ///   with the complete message to persist it in the user's chat. Returns True on success.
    /// </summary>
    function SendRichMessageDraft(AChatId: Int64; ADraftId: Int64;
      const ARichMessage: ITgInputRichMessage): Boolean; overload;
    function SendRichMessageDraft(AChatId: Int64; ADraftId: Int64;
      const ARichMessage: ITgInputRichMessage;
      const AOptions: TTgSendRichMessageDraftOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный sendRichMessageDraft: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SendRichMessageDraftAsync(AChatId: Int64; ADraftId: Int64;
      const ARichMessage: ITgInputRichMessage; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function SendRichMessageDraftAsync(AChatId: Int64; ADraftId: Int64;
      const ARichMessage: ITgInputRichMessage; const AOptions: TTgSendRichMessageDraftOptions;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   sendRichMessageDraft без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySendRichMessageDraft(AChatId: Int64; ADraftId: Int64;
      const ARichMessage: ITgInputRichMessage; out AError: TTgErrorInfo): Boolean; overload;
    function TrySendRichMessageDraft(AChatId: Int64; ADraftId: Int64;
      const ARichMessage: ITgInputRichMessage; const AOptions: TTgSendRichMessageDraftOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   answerInlineQuery: Use this method to send answers to an inline query. On success, True is
    ///   returned.
    /// </summary>
    function AnswerInlineQuery(const AInlineQueryId: string;
      const AResults: array of TTgInlineQueryResult): Boolean; overload;
    function AnswerInlineQuery(const AInlineQueryId: string;
      const AResults: array of TTgInlineQueryResult;
      const AOptions: TTgAnswerInlineQueryOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный answerInlineQuery: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function AnswerInlineQueryAsync(const AInlineQueryId: string;
      const AResults: array of TTgInlineQueryResult; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function AnswerInlineQueryAsync(const AInlineQueryId: string;
      const AResults: array of TTgInlineQueryResult; const AOptions: TTgAnswerInlineQueryOptions;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   answerInlineQuery без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryAnswerInlineQuery(const AInlineQueryId: string;
      const AResults: array of TTgInlineQueryResult; out AError: TTgErrorInfo): Boolean; overload;
    function TryAnswerInlineQuery(const AInlineQueryId: string;
      const AResults: array of TTgInlineQueryResult; const AOptions: TTgAnswerInlineQueryOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   sendInvoice: Use this method to send invoices. On success, the sent Message is returned.
    /// </summary>
    function SendInvoice(const AChatId: TTgChatId; const ATitle: string; const ADescription: string;
      const APayload: string; const ACurrency: string;
      const APrices: array of ITgLabeledPrice): ITgMessage; overload;
    function SendInvoice(const AChatId: TTgChatId; const ATitle: string; const ADescription: string;
      const APayload: string; const ACurrency: string; const APrices: array of ITgLabeledPrice;
      const AOptions: TTgSendInvoiceOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный sendInvoice: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SendInvoiceAsync(const AChatId: TTgChatId; const ATitle: string;
      const ADescription: string; const APayload: string; const ACurrency: string;
      const APrices: array of ITgLabeledPrice; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function SendInvoiceAsync(const AChatId: TTgChatId; const ATitle: string;
      const ADescription: string; const APayload: string; const ACurrency: string;
      const APrices: array of ITgLabeledPrice; const AOptions: TTgSendInvoiceOptions;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>sendInvoice без исключений: False и сведения об ошибке в AError.</summary>
    function TrySendInvoice(const AChatId: TTgChatId; const ATitle: string;
      const ADescription: string; const APayload: string; const ACurrency: string;
      const APrices: array of ITgLabeledPrice; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;
    function TrySendInvoice(const AChatId: TTgChatId; const ATitle: string;
      const ADescription: string; const APayload: string; const ACurrency: string;
      const APrices: array of ITgLabeledPrice; const AOptions: TTgSendInvoiceOptions;
      out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   createInvoiceLink: Use this method to create a link for an invoice. Returns the created
    ///   invoice link as String on success.
    /// </summary>
    function CreateInvoiceLink(const ATitle: string; const ADescription: string;
      const APayload: string; const ACurrency: string;
      const APrices: array of ITgLabeledPrice): string; overload;
    function CreateInvoiceLink(const ATitle: string; const ADescription: string;
      const APayload: string; const ACurrency: string; const APrices: array of ITgLabeledPrice;
      const AOptions: TTgCreateInvoiceLinkOptions): string; overload;
    /// <summary>
    ///   Асинхронный createInvoiceLink: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function CreateInvoiceLinkAsync(const ATitle: string; const ADescription: string;
      const APayload: string; const ACurrency: string; const APrices: array of ITgLabeledPrice;
      const AOnSuccess: TProc<string>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function CreateInvoiceLinkAsync(const ATitle: string; const ADescription: string;
      const APayload: string; const ACurrency: string; const APrices: array of ITgLabeledPrice;
      const AOptions: TTgCreateInvoiceLinkOptions; const AOnSuccess: TProc<string>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   createInvoiceLink без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryCreateInvoiceLink(const ATitle: string; const ADescription: string;
      const APayload: string; const ACurrency: string; const APrices: array of ITgLabeledPrice;
      out AResult: string; out AError: TTgErrorInfo): Boolean; overload;
    function TryCreateInvoiceLink(const ATitle: string; const ADescription: string;
      const APayload: string; const ACurrency: string; const APrices: array of ITgLabeledPrice;
      const AOptions: TTgCreateInvoiceLinkOptions; out AResult: string;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   answerShippingQuery: If you sent an invoice requesting a shipping address and the
    ///   parameter is_flexible was specified, the Bot API will send an Update with a shipping_query
    ///   field to the bot. Use this method to reply to shipping queries. On success, True is
    ///   returned.
    /// </summary>
    function AnswerShippingQuery(const AShippingQueryId: string; AOk: Boolean): Boolean; overload;
    function AnswerShippingQuery(const AShippingQueryId: string; AOk: Boolean;
      const AOptions: TTgAnswerShippingQueryOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный answerShippingQuery: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function AnswerShippingQueryAsync(const AShippingQueryId: string; AOk: Boolean;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function AnswerShippingQueryAsync(const AShippingQueryId: string; AOk: Boolean;
      const AOptions: TTgAnswerShippingQueryOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   answerShippingQuery без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryAnswerShippingQuery(const AShippingQueryId: string; AOk: Boolean;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryAnswerShippingQuery(const AShippingQueryId: string; AOk: Boolean;
      const AOptions: TTgAnswerShippingQueryOptions; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   answerPreCheckoutQuery: Once the user has confirmed their payment and shipping details,
    ///   the Bot API sends the final confirmation in the form of an Update with the field
    ///   pre_checkout_query. Use this method to respond to such pre-checkout queries. On success,
    ///   True is returned. Note: The Bot API must receive an answer within 10 seconds after the
    ///   pre-checkout query was sent.
    /// </summary>
    function AnswerPreCheckoutQuery(const APreCheckoutQueryId: string; AOk: Boolean): Boolean;
      overload;
    function AnswerPreCheckoutQuery(const APreCheckoutQueryId: string; AOk: Boolean;
      const AOptions: TTgAnswerPreCheckoutQueryOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный answerPreCheckoutQuery: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function AnswerPreCheckoutQueryAsync(const APreCheckoutQueryId: string; AOk: Boolean;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function AnswerPreCheckoutQueryAsync(const APreCheckoutQueryId: string; AOk: Boolean;
      const AOptions: TTgAnswerPreCheckoutQueryOptions; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   answerPreCheckoutQuery без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryAnswerPreCheckoutQuery(const APreCheckoutQueryId: string; AOk: Boolean;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryAnswerPreCheckoutQuery(const APreCheckoutQueryId: string; AOk: Boolean;
      const AOptions: TTgAnswerPreCheckoutQueryOptions;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   getMyStarBalance: A method to get the current Telegram Stars balance of the bot. Requires
    ///   no parameters. On success, returns a StarAmount object.
    /// </summary>
    function GetMyStarBalance: ITgStarAmount; overload;
    /// <summary>
    ///   Асинхронный getMyStarBalance: параметры проверяются и строятся в вызывающем потоке (ошибки
    ///   — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetMyStarBalanceAsync(const AOnSuccess: TProc<ITgStarAmount>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   getMyStarBalance без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryGetMyStarBalance(out AResult: ITgStarAmount; out AError: TTgErrorInfo): Boolean;
      overload;

    /// <summary>
    ///   getStarTransactions: Returns the bot's Telegram Star transactions in chronological order.
    ///   On success, returns a StarTransactions object.
    /// </summary>
    function GetStarTransactions: ITgStarTransactions; overload;
    function GetStarTransactions(const AOptions: TTgGetStarTransactionsOptions): ITgStarTransactions; overload;
    /// <summary>
    ///   Асинхронный getStarTransactions: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetStarTransactionsAsync(const AOnSuccess: TProc<ITgStarTransactions>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function GetStarTransactionsAsync(const AOptions: TTgGetStarTransactionsOptions;
      const AOnSuccess: TProc<ITgStarTransactions>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   getStarTransactions без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryGetStarTransactions(out AResult: ITgStarTransactions;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryGetStarTransactions(const AOptions: TTgGetStarTransactionsOptions;
      out AResult: ITgStarTransactions; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   refundStarPayment: Refunds a successful payment in Telegram Stars. Returns True on
    ///   success.
    /// </summary>
    function RefundStarPayment(AUserId: Int64; const ATelegramPaymentChargeId: string): Boolean;
      overload;
    /// <summary>
    ///   Асинхронный refundStarPayment: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function RefundStarPaymentAsync(AUserId: Int64; const ATelegramPaymentChargeId: string;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   refundStarPayment без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryRefundStarPayment(AUserId: Int64; const ATelegramPaymentChargeId: string;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   editUserStarSubscription: Allows the bot to cancel or re-enable extension of a
    ///   subscription paid in Telegram Stars. Returns True on success.
    /// </summary>
    function EditUserStarSubscription(AUserId: Int64; const ATelegramPaymentChargeId: string;
      AIsCanceled: Boolean): Boolean; overload;
    /// <summary>
    ///   Асинхронный editUserStarSubscription: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function EditUserStarSubscriptionAsync(AUserId: Int64; const ATelegramPaymentChargeId: string;
      AIsCanceled: Boolean; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   editUserStarSubscription без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryEditUserStarSubscription(AUserId: Int64; const ATelegramPaymentChargeId: string;
      AIsCanceled: Boolean; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setPassportDataErrors: Informs a user that some of the Telegram Passport elements they
    ///   provided contains errors. The user will not be able to re-submit their Passport to you
    ///   until the errors are fixed (the contents of the field for which you returned the error
    ///   must change). Returns True on success.
    /// </summary>
    function SetPassportDataErrors(AUserId: Int64;
      const AErrors: array of TTgPassportElementError): Boolean; overload;
    /// <summary>
    ///   Асинхронный setPassportDataErrors: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetPassportDataErrorsAsync(AUserId: Int64;
      const AErrors: array of TTgPassportElementError; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   setPassportDataErrors без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySetPassportDataErrors(AUserId: Int64;
      const AErrors: array of TTgPassportElementError; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   sendGame: Use this method to send a game. On success, the sent Message is returned.
    /// </summary>
    function SendGame(const AChatId: TTgChatId; const AGameShortName: string): ITgMessage; overload;
    function SendGame(const AChatId: TTgChatId; const AGameShortName: string;
      const AOptions: TTgSendGameOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный sendGame: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SendGameAsync(const AChatId: TTgChatId; const AGameShortName: string;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function SendGameAsync(const AChatId: TTgChatId; const AGameShortName: string;
      const AOptions: TTgSendGameOptions; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>sendGame без исключений: False и сведения об ошибке в AError.</summary>
    function TrySendGame(const AChatId: TTgChatId; const AGameShortName: string;
      out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;
    function TrySendGame(const AChatId: TTgChatId; const AGameShortName: string;
      const AOptions: TTgSendGameOptions; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setGameScore: Use this method to set the score of the specified user in a game message. On
    ///   success, if the message is not an inline message, the Message is returned, otherwise True
    ///   is returned. Returns an error, if the new score is not greater than the user's current
    ///   score in the chat and force is False.
    /// </summary>
    function SetGameScore(AUserId: Int64; AScore: Integer): ITgMessage; overload;
    function SetGameScore(AUserId: Int64; AScore: Integer;
      const AOptions: TTgSetGameScoreOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный setGameScore: параметры проверяются и строятся в вызывающем потоке (ошибки —
    ///   исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetGameScoreAsync(AUserId: Int64; AScore: Integer; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function SetGameScoreAsync(AUserId: Int64; AScore: Integer;
      const AOptions: TTgSetGameScoreOptions; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>setGameScore без исключений: False и сведения об ошибке в AError.</summary>
    function TrySetGameScore(AUserId: Int64; AScore: Integer; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;
    function TrySetGameScore(AUserId: Int64; AScore: Integer;
      const AOptions: TTgSetGameScoreOptions; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setGameScore (вариант: user_id, score, chat_id, message_id). Игра в сообщении,
    ///   отправленном от имени бота (не inline). Поля AOptions (ChatId, MessageId) заменяются
    ///   значениями параметров.
    /// </summary>
    function SetGameScore(AUserId: Int64; AScore: Integer; AChatId: Int64;
      AMessageId: Int64): ITgMessage; overload;
    function SetGameScore(AUserId: Int64; AScore: Integer; AChatId: Int64; AMessageId: Int64;
      const AOptions: TTgSetGameScoreOptions): ITgMessage; overload;
    /// <summary>
    ///   Асинхронный SetGameScore (setGameScore, вариант): параметры проверяются и строятся в
    ///   вызывающем потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetGameScoreAsync(AUserId: Int64; AScore: Integer; AChatId: Int64; AMessageId: Int64;
      const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception> = nil): ITask; overload;
    function SetGameScoreAsync(AUserId: Int64; AScore: Integer; AChatId: Int64; AMessageId: Int64;
      const AOptions: TTgSetGameScoreOptions; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   SetGameScore (setGameScore, вариант) без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TrySetGameScore(AUserId: Int64; AScore: Integer; AChatId: Int64; AMessageId: Int64;
      out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;
    function TrySetGameScore(AUserId: Int64; AScore: Integer; AChatId: Int64; AMessageId: Int64;
      const AOptions: TTgSetGameScoreOptions; out AResult: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   setGameScore (вариант: user_id, score, inline_message_id). Игра в inline-сообщении.
    ///   Результат True — запрос выполнен (Bot API вернул true). Поля AOptions (InlineMessageId)
    ///   заменяются значениями параметров.
    /// </summary>
    function SetInlineGameScore(AUserId: Int64; AScore: Integer;
      const AInlineMessageId: string): Boolean; overload;
    function SetInlineGameScore(AUserId: Int64; AScore: Integer; const AInlineMessageId: string;
      const AOptions: TTgSetGameScoreOptions): Boolean; overload;
    /// <summary>
    ///   Асинхронный SetInlineGameScore (setGameScore, вариант): параметры проверяются и строятся в
    ///   вызывающем потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function SetInlineGameScoreAsync(AUserId: Int64; AScore: Integer;
      const AInlineMessageId: string; const AOnSuccess: TProc<Boolean>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function SetInlineGameScoreAsync(AUserId: Int64; AScore: Integer;
      const AInlineMessageId: string; const AOptions: TTgSetGameScoreOptions;
      const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   SetInlineGameScore (setGameScore, вариант) без исключений: False и сведения об ошибке в
    ///   AError.
    /// </summary>
    function TrySetInlineGameScore(AUserId: Int64; AScore: Integer; const AInlineMessageId: string;
      out AError: TTgErrorInfo): Boolean; overload;
    function TrySetInlineGameScore(AUserId: Int64; AScore: Integer; const AInlineMessageId: string;
      const AOptions: TTgSetGameScoreOptions; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   getGameHighScores: Use this method to get data for high score tables. Will return the
    ///   score of the specified user and several of their neighbors in a game. Returns an Array of
    ///   GameHighScore objects. Элементы результата разделяют JSON всего ответа и удерживают его;
    ///   для длительного хранения отдельных элементов используйте TTgDto.Detach.
    /// </summary>
    function GetGameHighScores(AUserId: Int64): TArray<ITgGameHighScore>; overload;
    function GetGameHighScores(AUserId: Int64;
      const AOptions: TTgGetGameHighScoresOptions): TArray<ITgGameHighScore>; overload;
    /// <summary>
    ///   Асинхронный getGameHighScores: параметры проверяются и строятся в вызывающем потоке
    ///   (ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.
    /// </summary>
    function GetGameHighScoresAsync(AUserId: Int64;
      const AOnSuccess: TProc<TArray<ITgGameHighScore>>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function GetGameHighScoresAsync(AUserId: Int64; const AOptions: TTgGetGameHighScoresOptions;
      const AOnSuccess: TProc<TArray<ITgGameHighScore>>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   getGameHighScores без исключений: False и сведения об ошибке в AError.
    /// </summary>
    function TryGetGameHighScores(AUserId: Int64; out AResult: TArray<ITgGameHighScore>;
      out AError: TTgErrorInfo): Boolean; overload;
    function TryGetGameHighScores(AUserId: Int64; const AOptions: TTgGetGameHighScoresOptions;
      out AResult: TArray<ITgGameHighScore>; out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   getGameHighScores (вариант: user_id, chat_id, message_id). Игра в сообщении, отправленном
    ///   от имени бота (не inline). Поля AOptions (ChatId, MessageId) заменяются значениями
    ///   параметров.
    /// </summary>
    function GetGameHighScores(AUserId: Int64; AChatId: Int64;
      AMessageId: Int64): TArray<ITgGameHighScore>; overload;
    function GetGameHighScores(AUserId: Int64; AChatId: Int64; AMessageId: Int64;
      const AOptions: TTgGetGameHighScoresOptions): TArray<ITgGameHighScore>; overload;
    /// <summary>
    ///   Асинхронный GetGameHighScores (getGameHighScores, вариант): параметры проверяются и
    ///   строятся в вызывающем потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем
    ///   потоке.
    /// </summary>
    function GetGameHighScoresAsync(AUserId: Int64; AChatId: Int64; AMessageId: Int64;
      const AOnSuccess: TProc<TArray<ITgGameHighScore>>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function GetGameHighScoresAsync(AUserId: Int64; AChatId: Int64; AMessageId: Int64;
      const AOptions: TTgGetGameHighScoresOptions;
      const AOnSuccess: TProc<TArray<ITgGameHighScore>>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   GetGameHighScores (getGameHighScores, вариант) без исключений: False и сведения об ошибке
    ///   в AError.
    /// </summary>
    function TryGetGameHighScores(AUserId: Int64; AChatId: Int64; AMessageId: Int64;
      out AResult: TArray<ITgGameHighScore>; out AError: TTgErrorInfo): Boolean; overload;
    function TryGetGameHighScores(AUserId: Int64; AChatId: Int64; AMessageId: Int64;
      const AOptions: TTgGetGameHighScoresOptions; out AResult: TArray<ITgGameHighScore>;
      out AError: TTgErrorInfo): Boolean; overload;

    /// <summary>
    ///   getGameHighScores (вариант: user_id, inline_message_id). Игра в inline-сообщении. Поля
    ///   AOptions (InlineMessageId) заменяются значениями параметров.
    /// </summary>
    function GetInlineGameHighScores(AUserId: Int64;
      const AInlineMessageId: string): TArray<ITgGameHighScore>; overload;
    function GetInlineGameHighScores(AUserId: Int64; const AInlineMessageId: string;
      const AOptions: TTgGetGameHighScoresOptions): TArray<ITgGameHighScore>; overload;
    /// <summary>
    ///   Асинхронный GetInlineGameHighScores (getGameHighScores, вариант): параметры проверяются и
    ///   строятся в вызывающем потоке (ошибки — исключением здесь же), колбэки вызываются в рабочем
    ///   потоке.
    /// </summary>
    function GetInlineGameHighScoresAsync(AUserId: Int64; const AInlineMessageId: string;
      const AOnSuccess: TProc<TArray<ITgGameHighScore>>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    function GetInlineGameHighScoresAsync(AUserId: Int64; const AInlineMessageId: string;
      const AOptions: TTgGetGameHighScoresOptions;
      const AOnSuccess: TProc<TArray<ITgGameHighScore>>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>
    ///   GetInlineGameHighScores (getGameHighScores, вариант) без исключений: False и сведения об
    ///   ошибке в AError.
    /// </summary>
    function TryGetInlineGameHighScores(AUserId: Int64; const AInlineMessageId: string;
      out AResult: TArray<ITgGameHighScore>; out AError: TTgErrorInfo): Boolean; overload;
    function TryGetInlineGameHighScores(AUserId: Int64; const AInlineMessageId: string;
      const AOptions: TTgGetGameHighScoresOptions; out AResult: TArray<ITgGameHighScore>;
      out AError: TTgErrorInfo): Boolean; overload;

