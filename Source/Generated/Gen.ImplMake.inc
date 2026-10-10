// Gen.ImplMake.inc — фабрики DTO из JSON (implementation). nil — значение не подходит.
// Сгенерировано TgBotGen по Telegram Bot API 10.3 (August 24, 2026). Не редактируйте вручную.

function TgMakeUpdate(AJson: TJSONValue; const AOwner: IInterface): ITgUpdate;
begin
  if AJson is TJSONObject then
    Result := TTgUpdateImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeWebhookInfo(AJson: TJSONValue; const AOwner: IInterface): ITgWebhookInfo;
begin
  if AJson is TJSONObject then
    Result := TTgWebhookInfoImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeUser(AJson: TJSONValue; const AOwner: IInterface): ITgUser;
begin
  if AJson is TJSONObject then
    Result := TTgUserImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChat(AJson: TJSONValue; const AOwner: IInterface): ITgChat;
begin
  if AJson is TJSONObject then
    Result := TTgChatImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChatFullInfo(AJson: TJSONValue; const AOwner: IInterface): ITgChatFullInfo;
begin
  if AJson is TJSONObject then
    Result := TTgChatFullInfoImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeMaybeInaccessibleMessage(AJson: TJSONValue; const AOwner: IInterface): ITgMaybeInaccessibleMessage;
var
  LValue: string;
begin
  if not (AJson is TJSONObject) then
    Exit(nil);
  LValue := TTgJson.GetStr(TJSONObject(AJson), 'date');
  if LValue = '0' then
    Result := TTgInaccessibleMessageImpl.Create(AJson, AOwner)
  else
    Result := TTgMessageImpl.Create(AJson, AOwner);
end;

function TgMakeMessage(AJson: TJSONValue; const AOwner: IInterface): ITgMessage;
begin
  if AJson is TJSONObject then
    Result := TTgMessageImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeMessageId(AJson: TJSONValue; const AOwner: IInterface): ITgMessageId;
begin
  if AJson is TJSONObject then
    Result := TTgMessageIdImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeInaccessibleMessage(AJson: TJSONValue; const AOwner: IInterface): ITgInaccessibleMessage;
begin
  if AJson is TJSONObject then
    Result := TTgInaccessibleMessageImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeMessageEntity(AJson: TJSONValue; const AOwner: IInterface): ITgMessageEntity;
begin
  if AJson is TJSONObject then
    Result := TTgMessageEntityImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeTextQuote(AJson: TJSONValue; const AOwner: IInterface): ITgTextQuote;
begin
  if AJson is TJSONObject then
    Result := TTgTextQuoteImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeExternalReplyInfo(AJson: TJSONValue; const AOwner: IInterface): ITgExternalReplyInfo;
begin
  if AJson is TJSONObject then
    Result := TTgExternalReplyInfoImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeMessageOrigin(AJson: TJSONValue; const AOwner: IInterface): ITgMessageOrigin;
begin
  if not (AJson is TJSONObject) then
    Exit(nil);
  case TTgDto.IndexOfValue(TJSONObject(AJson), 'type', [
    'user',
    'hidden_user',
    'chat',
    'channel']) of
    0: Result := TTgMessageOriginUserImpl.Create(AJson, AOwner);
    1: Result := TTgMessageOriginHiddenUserImpl.Create(AJson, AOwner);
    2: Result := TTgMessageOriginChatImpl.Create(AJson, AOwner);
    3: Result := TTgMessageOriginChannelImpl.Create(AJson, AOwner);
  else
    Result := TTgMessageOriginImpl.Create(AJson, AOwner);
  end;
end;

function TgMakeMessageOriginUser(AJson: TJSONValue; const AOwner: IInterface): ITgMessageOriginUser;
begin
  if AJson is TJSONObject then
    Result := TTgMessageOriginUserImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeMessageOriginHiddenUser(AJson: TJSONValue; const AOwner: IInterface): ITgMessageOriginHiddenUser;
begin
  if AJson is TJSONObject then
    Result := TTgMessageOriginHiddenUserImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeMessageOriginChat(AJson: TJSONValue; const AOwner: IInterface): ITgMessageOriginChat;
begin
  if AJson is TJSONObject then
    Result := TTgMessageOriginChatImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeMessageOriginChannel(AJson: TJSONValue; const AOwner: IInterface): ITgMessageOriginChannel;
begin
  if AJson is TJSONObject then
    Result := TTgMessageOriginChannelImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakePhotoSize(AJson: TJSONValue; const AOwner: IInterface): ITgPhotoSize;
begin
  if AJson is TJSONObject then
    Result := TTgPhotoSizeImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeAnimation(AJson: TJSONValue; const AOwner: IInterface): ITgAnimation;
begin
  if AJson is TJSONObject then
    Result := TTgAnimationImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeAudio(AJson: TJSONValue; const AOwner: IInterface): ITgAudio;
begin
  if AJson is TJSONObject then
    Result := TTgAudioImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeDocument(AJson: TJSONValue; const AOwner: IInterface): ITgDocument;
begin
  if AJson is TJSONObject then
    Result := TTgDocumentImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeLivePhoto(AJson: TJSONValue; const AOwner: IInterface): ITgLivePhoto;
begin
  if AJson is TJSONObject then
    Result := TTgLivePhotoImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeStory(AJson: TJSONValue; const AOwner: IInterface): ITgStory;
begin
  if AJson is TJSONObject then
    Result := TTgStoryImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeVideoQuality(AJson: TJSONValue; const AOwner: IInterface): ITgVideoQuality;
begin
  if AJson is TJSONObject then
    Result := TTgVideoQualityImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeVideo(AJson: TJSONValue; const AOwner: IInterface): ITgVideo;
begin
  if AJson is TJSONObject then
    Result := TTgVideoImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeVideoNote(AJson: TJSONValue; const AOwner: IInterface): ITgVideoNote;
begin
  if AJson is TJSONObject then
    Result := TTgVideoNoteImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeVoice(AJson: TJSONValue; const AOwner: IInterface): ITgVoice;
begin
  if AJson is TJSONObject then
    Result := TTgVoiceImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakePaidMediaInfo(AJson: TJSONValue; const AOwner: IInterface): ITgPaidMediaInfo;
begin
  if AJson is TJSONObject then
    Result := TTgPaidMediaInfoImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakePaidMedia(AJson: TJSONValue; const AOwner: IInterface): ITgPaidMedia;
begin
  if not (AJson is TJSONObject) then
    Exit(nil);
  case TTgDto.IndexOfValue(TJSONObject(AJson), 'type', [
    'live_photo',
    'photo',
    'preview',
    'video']) of
    0: Result := TTgPaidMediaLivePhotoImpl.Create(AJson, AOwner);
    1: Result := TTgPaidMediaPhotoImpl.Create(AJson, AOwner);
    2: Result := TTgPaidMediaPreviewImpl.Create(AJson, AOwner);
    3: Result := TTgPaidMediaVideoImpl.Create(AJson, AOwner);
  else
    Result := TTgPaidMediaImpl.Create(AJson, AOwner);
  end;
end;

function TgMakePaidMediaLivePhoto(AJson: TJSONValue; const AOwner: IInterface): ITgPaidMediaLivePhoto;
begin
  if AJson is TJSONObject then
    Result := TTgPaidMediaLivePhotoImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakePaidMediaPhoto(AJson: TJSONValue; const AOwner: IInterface): ITgPaidMediaPhoto;
begin
  if AJson is TJSONObject then
    Result := TTgPaidMediaPhotoImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakePaidMediaPreview(AJson: TJSONValue; const AOwner: IInterface): ITgPaidMediaPreview;
begin
  if AJson is TJSONObject then
    Result := TTgPaidMediaPreviewImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakePaidMediaVideo(AJson: TJSONValue; const AOwner: IInterface): ITgPaidMediaVideo;
begin
  if AJson is TJSONObject then
    Result := TTgPaidMediaVideoImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeContact(AJson: TJSONValue; const AOwner: IInterface): ITgContact;
begin
  if AJson is TJSONObject then
    Result := TTgContactImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeDice(AJson: TJSONValue; const AOwner: IInterface): ITgDice;
begin
  if AJson is TJSONObject then
    Result := TTgDiceImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeLink(AJson: TJSONValue; const AOwner: IInterface): ITgLink;
begin
  if AJson is TJSONObject then
    Result := TTgLinkImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakePollMedia(AJson: TJSONValue; const AOwner: IInterface): ITgPollMedia;
begin
  if AJson is TJSONObject then
    Result := TTgPollMediaImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakePollOption(AJson: TJSONValue; const AOwner: IInterface): ITgPollOption;
begin
  if AJson is TJSONObject then
    Result := TTgPollOptionImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakePollAnswer(AJson: TJSONValue; const AOwner: IInterface): ITgPollAnswer;
begin
  if AJson is TJSONObject then
    Result := TTgPollAnswerImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakePoll(AJson: TJSONValue; const AOwner: IInterface): ITgPoll;
begin
  if AJson is TJSONObject then
    Result := TTgPollImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChecklistTask(AJson: TJSONValue; const AOwner: IInterface): ITgChecklistTask;
begin
  if AJson is TJSONObject then
    Result := TTgChecklistTaskImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChecklist(AJson: TJSONValue; const AOwner: IInterface): ITgChecklist;
begin
  if AJson is TJSONObject then
    Result := TTgChecklistImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeLocation(AJson: TJSONValue; const AOwner: IInterface): ITgLocation;
begin
  if AJson is TJSONObject then
    Result := TTgLocationImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeVenue(AJson: TJSONValue; const AOwner: IInterface): ITgVenue;
begin
  if AJson is TJSONObject then
    Result := TTgVenueImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeWebAppData(AJson: TJSONValue; const AOwner: IInterface): ITgWebAppData;
begin
  if AJson is TJSONObject then
    Result := TTgWebAppDataImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeProximityAlertTriggered(AJson: TJSONValue; const AOwner: IInterface): ITgProximityAlertTriggered;
begin
  if AJson is TJSONObject then
    Result := TTgProximityAlertTriggeredImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeMessageAutoDeleteTimerChanged(AJson: TJSONValue; const AOwner: IInterface): ITgMessageAutoDeleteTimerChanged;
begin
  if AJson is TJSONObject then
    Result := TTgMessageAutoDeleteTimerChangedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeManagedBotCreated(AJson: TJSONValue; const AOwner: IInterface): ITgManagedBotCreated;
begin
  if AJson is TJSONObject then
    Result := TTgManagedBotCreatedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeManagedBotUpdated(AJson: TJSONValue; const AOwner: IInterface): ITgManagedBotUpdated;
begin
  if AJson is TJSONObject then
    Result := TTgManagedBotUpdatedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeBotSubscriptionUpdated(AJson: TJSONValue; const AOwner: IInterface): ITgBotSubscriptionUpdated;
begin
  if AJson is TJSONObject then
    Result := TTgBotSubscriptionUpdatedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeMessageGenerationStopped(AJson: TJSONValue; const AOwner: IInterface): ITgMessageGenerationStopped;
begin
  if AJson is TJSONObject then
    Result := TTgMessageGenerationStoppedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakePollOptionAdded(AJson: TJSONValue; const AOwner: IInterface): ITgPollOptionAdded;
begin
  if AJson is TJSONObject then
    Result := TTgPollOptionAddedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakePollOptionDeleted(AJson: TJSONValue; const AOwner: IInterface): ITgPollOptionDeleted;
begin
  if AJson is TJSONObject then
    Result := TTgPollOptionDeletedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChatBoostAdded(AJson: TJSONValue; const AOwner: IInterface): ITgChatBoostAdded;
begin
  if AJson is TJSONObject then
    Result := TTgChatBoostAddedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeBackgroundFill(AJson: TJSONValue; const AOwner: IInterface): ITgBackgroundFill;
begin
  if not (AJson is TJSONObject) then
    Exit(nil);
  case TTgDto.IndexOfValue(TJSONObject(AJson), 'type', [
    'solid',
    'gradient',
    'freeform_gradient']) of
    0: Result := TTgBackgroundFillSolidImpl.Create(AJson, AOwner);
    1: Result := TTgBackgroundFillGradientImpl.Create(AJson, AOwner);
    2: Result := TTgBackgroundFillFreeformGradientImpl.Create(AJson, AOwner);
  else
    Result := TTgBackgroundFillImpl.Create(AJson, AOwner);
  end;
end;

function TgMakeBackgroundFillSolid(AJson: TJSONValue; const AOwner: IInterface): ITgBackgroundFillSolid;
begin
  if AJson is TJSONObject then
    Result := TTgBackgroundFillSolidImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeBackgroundFillGradient(AJson: TJSONValue; const AOwner: IInterface): ITgBackgroundFillGradient;
begin
  if AJson is TJSONObject then
    Result := TTgBackgroundFillGradientImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeBackgroundFillFreeformGradient(AJson: TJSONValue; const AOwner: IInterface): ITgBackgroundFillFreeformGradient;
begin
  if AJson is TJSONObject then
    Result := TTgBackgroundFillFreeformGradientImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeBackgroundType(AJson: TJSONValue; const AOwner: IInterface): ITgBackgroundType;
begin
  if not (AJson is TJSONObject) then
    Exit(nil);
  case TTgDto.IndexOfValue(TJSONObject(AJson), 'type', [
    'fill',
    'wallpaper',
    'pattern',
    'chat_theme']) of
    0: Result := TTgBackgroundTypeFillImpl.Create(AJson, AOwner);
    1: Result := TTgBackgroundTypeWallpaperImpl.Create(AJson, AOwner);
    2: Result := TTgBackgroundTypePatternImpl.Create(AJson, AOwner);
    3: Result := TTgBackgroundTypeChatThemeImpl.Create(AJson, AOwner);
  else
    Result := TTgBackgroundTypeImpl.Create(AJson, AOwner);
  end;
end;

function TgMakeBackgroundTypeFill(AJson: TJSONValue; const AOwner: IInterface): ITgBackgroundTypeFill;
begin
  if AJson is TJSONObject then
    Result := TTgBackgroundTypeFillImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeBackgroundTypeWallpaper(AJson: TJSONValue; const AOwner: IInterface): ITgBackgroundTypeWallpaper;
begin
  if AJson is TJSONObject then
    Result := TTgBackgroundTypeWallpaperImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeBackgroundTypePattern(AJson: TJSONValue; const AOwner: IInterface): ITgBackgroundTypePattern;
begin
  if AJson is TJSONObject then
    Result := TTgBackgroundTypePatternImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeBackgroundTypeChatTheme(AJson: TJSONValue; const AOwner: IInterface): ITgBackgroundTypeChatTheme;
begin
  if AJson is TJSONObject then
    Result := TTgBackgroundTypeChatThemeImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChatBackground(AJson: TJSONValue; const AOwner: IInterface): ITgChatBackground;
begin
  if AJson is TJSONObject then
    Result := TTgChatBackgroundImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChecklistTasksDone(AJson: TJSONValue; const AOwner: IInterface): ITgChecklistTasksDone;
begin
  if AJson is TJSONObject then
    Result := TTgChecklistTasksDoneImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChecklistTasksAdded(AJson: TJSONValue; const AOwner: IInterface): ITgChecklistTasksAdded;
begin
  if AJson is TJSONObject then
    Result := TTgChecklistTasksAddedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeCommunityChatAdded(AJson: TJSONValue; const AOwner: IInterface): ITgCommunityChatAdded;
begin
  if AJson is TJSONObject then
    Result := TTgCommunityChatAddedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeCommunityChatJoined(AJson: TJSONValue; const AOwner: IInterface): ITgCommunityChatJoined;
begin
  if AJson is TJSONObject then
    Result := TTgCommunityChatJoinedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeCommunityChatRemoved(AJson: TJSONValue; const AOwner: IInterface): ITgCommunityChatRemoved;
begin
  if AJson is TJSONObject then
    Result := TTgCommunityChatRemovedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeForumTopicCreated(AJson: TJSONValue; const AOwner: IInterface): ITgForumTopicCreated;
begin
  if AJson is TJSONObject then
    Result := TTgForumTopicCreatedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeForumTopicClosed(AJson: TJSONValue; const AOwner: IInterface): ITgForumTopicClosed;
begin
  if AJson is TJSONObject then
    Result := TTgForumTopicClosedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeForumTopicEdited(AJson: TJSONValue; const AOwner: IInterface): ITgForumTopicEdited;
begin
  if AJson is TJSONObject then
    Result := TTgForumTopicEditedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeForumTopicReopened(AJson: TJSONValue; const AOwner: IInterface): ITgForumTopicReopened;
begin
  if AJson is TJSONObject then
    Result := TTgForumTopicReopenedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeGeneralForumTopicHidden(AJson: TJSONValue; const AOwner: IInterface): ITgGeneralForumTopicHidden;
begin
  if AJson is TJSONObject then
    Result := TTgGeneralForumTopicHiddenImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeGeneralForumTopicUnhidden(AJson: TJSONValue; const AOwner: IInterface): ITgGeneralForumTopicUnhidden;
begin
  if AJson is TJSONObject then
    Result := TTgGeneralForumTopicUnhiddenImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeSharedUser(AJson: TJSONValue; const AOwner: IInterface): ITgSharedUser;
begin
  if AJson is TJSONObject then
    Result := TTgSharedUserImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeUsersShared(AJson: TJSONValue; const AOwner: IInterface): ITgUsersShared;
begin
  if AJson is TJSONObject then
    Result := TTgUsersSharedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChatShared(AJson: TJSONValue; const AOwner: IInterface): ITgChatShared;
begin
  if AJson is TJSONObject then
    Result := TTgChatSharedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeWriteAccessAllowed(AJson: TJSONValue; const AOwner: IInterface): ITgWriteAccessAllowed;
begin
  if AJson is TJSONObject then
    Result := TTgWriteAccessAllowedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeVideoChatScheduled(AJson: TJSONValue; const AOwner: IInterface): ITgVideoChatScheduled;
begin
  if AJson is TJSONObject then
    Result := TTgVideoChatScheduledImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeVideoChatStarted(AJson: TJSONValue; const AOwner: IInterface): ITgVideoChatStarted;
begin
  if AJson is TJSONObject then
    Result := TTgVideoChatStartedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeVideoChatEnded(AJson: TJSONValue; const AOwner: IInterface): ITgVideoChatEnded;
begin
  if AJson is TJSONObject then
    Result := TTgVideoChatEndedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeVideoChatParticipantsInvited(AJson: TJSONValue; const AOwner: IInterface): ITgVideoChatParticipantsInvited;
begin
  if AJson is TJSONObject then
    Result := TTgVideoChatParticipantsInvitedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakePaidMessagePriceChanged(AJson: TJSONValue; const AOwner: IInterface): ITgPaidMessagePriceChanged;
begin
  if AJson is TJSONObject then
    Result := TTgPaidMessagePriceChangedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeDirectMessagePriceChanged(AJson: TJSONValue; const AOwner: IInterface): ITgDirectMessagePriceChanged;
begin
  if AJson is TJSONObject then
    Result := TTgDirectMessagePriceChangedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeSuggestedPostApproved(AJson: TJSONValue; const AOwner: IInterface): ITgSuggestedPostApproved;
begin
  if AJson is TJSONObject then
    Result := TTgSuggestedPostApprovedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeSuggestedPostApprovalFailed(AJson: TJSONValue; const AOwner: IInterface): ITgSuggestedPostApprovalFailed;
begin
  if AJson is TJSONObject then
    Result := TTgSuggestedPostApprovalFailedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeSuggestedPostDeclined(AJson: TJSONValue; const AOwner: IInterface): ITgSuggestedPostDeclined;
begin
  if AJson is TJSONObject then
    Result := TTgSuggestedPostDeclinedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeSuggestedPostPaid(AJson: TJSONValue; const AOwner: IInterface): ITgSuggestedPostPaid;
begin
  if AJson is TJSONObject then
    Result := TTgSuggestedPostPaidImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeSuggestedPostRefunded(AJson: TJSONValue; const AOwner: IInterface): ITgSuggestedPostRefunded;
begin
  if AJson is TJSONObject then
    Result := TTgSuggestedPostRefundedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeGiveawayCreated(AJson: TJSONValue; const AOwner: IInterface): ITgGiveawayCreated;
begin
  if AJson is TJSONObject then
    Result := TTgGiveawayCreatedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeGiveaway(AJson: TJSONValue; const AOwner: IInterface): ITgGiveaway;
begin
  if AJson is TJSONObject then
    Result := TTgGiveawayImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeGiveawayWinners(AJson: TJSONValue; const AOwner: IInterface): ITgGiveawayWinners;
begin
  if AJson is TJSONObject then
    Result := TTgGiveawayWinnersImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeGiveawayCompleted(AJson: TJSONValue; const AOwner: IInterface): ITgGiveawayCompleted;
begin
  if AJson is TJSONObject then
    Result := TTgGiveawayCompletedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeLinkPreviewOptions(AJson: TJSONValue; const AOwner: IInterface): ITgLinkPreviewOptions;
begin
  if AJson is TJSONObject then
    Result := TTgLinkPreviewOptionsImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeSuggestedPostPrice(AJson: TJSONValue; const AOwner: IInterface): ITgSuggestedPostPrice;
begin
  if AJson is TJSONObject then
    Result := TTgSuggestedPostPriceImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeSuggestedPostInfo(AJson: TJSONValue; const AOwner: IInterface): ITgSuggestedPostInfo;
begin
  if AJson is TJSONObject then
    Result := TTgSuggestedPostInfoImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeDirectMessagesTopic(AJson: TJSONValue; const AOwner: IInterface): ITgDirectMessagesTopic;
begin
  if AJson is TJSONObject then
    Result := TTgDirectMessagesTopicImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeUserProfilePhotos(AJson: TJSONValue; const AOwner: IInterface): ITgUserProfilePhotos;
begin
  if AJson is TJSONObject then
    Result := TTgUserProfilePhotosImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeUserProfileAudios(AJson: TJSONValue; const AOwner: IInterface): ITgUserProfileAudios;
begin
  if AJson is TJSONObject then
    Result := TTgUserProfileAudiosImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeFile(AJson: TJSONValue; const AOwner: IInterface): ITgFile;
begin
  if AJson is TJSONObject then
    Result := TTgFileImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeWebAppInfo(AJson: TJSONValue; const AOwner: IInterface): ITgWebAppInfo;
begin
  if AJson is TJSONObject then
    Result := TTgWebAppInfoImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeInlineKeyboardMarkup(AJson: TJSONValue; const AOwner: IInterface): ITgInlineKeyboardMarkup;
begin
  if AJson is TJSONObject then
    Result := TTgInlineKeyboardMarkupImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeInlineKeyboardButton(AJson: TJSONValue; const AOwner: IInterface): ITgInlineKeyboardButton;
begin
  if AJson is TJSONObject then
    Result := TTgInlineKeyboardButtonImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeLoginUrl(AJson: TJSONValue; const AOwner: IInterface): ITgLoginUrl;
begin
  if AJson is TJSONObject then
    Result := TTgLoginUrlImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeSwitchInlineQueryChosenChat(AJson: TJSONValue; const AOwner: IInterface): ITgSwitchInlineQueryChosenChat;
begin
  if AJson is TJSONObject then
    Result := TTgSwitchInlineQueryChosenChatImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeCopyTextButton(AJson: TJSONValue; const AOwner: IInterface): ITgCopyTextButton;
begin
  if AJson is TJSONObject then
    Result := TTgCopyTextButtonImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeDisabledButton(AJson: TJSONValue; const AOwner: IInterface): ITgDisabledButton;
begin
  if AJson is TJSONObject then
    Result := TTgDisabledButtonImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeCallbackQuery(AJson: TJSONValue; const AOwner: IInterface): ITgCallbackQuery;
begin
  if AJson is TJSONObject then
    Result := TTgCallbackQueryImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeCommunity(AJson: TJSONValue; const AOwner: IInterface): ITgCommunity;
begin
  if AJson is TJSONObject then
    Result := TTgCommunityImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChatPhoto(AJson: TJSONValue; const AOwner: IInterface): ITgChatPhoto;
begin
  if AJson is TJSONObject then
    Result := TTgChatPhotoImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChatInviteLink(AJson: TJSONValue; const AOwner: IInterface): ITgChatInviteLink;
begin
  if AJson is TJSONObject then
    Result := TTgChatInviteLinkImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChatAdministratorRights(AJson: TJSONValue; const AOwner: IInterface): ITgChatAdministratorRights;
begin
  if AJson is TJSONObject then
    Result := TTgChatAdministratorRightsImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChatMemberUpdated(AJson: TJSONValue; const AOwner: IInterface): ITgChatMemberUpdated;
begin
  if AJson is TJSONObject then
    Result := TTgChatMemberUpdatedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChatMember(AJson: TJSONValue; const AOwner: IInterface): ITgChatMember;
begin
  if not (AJson is TJSONObject) then
    Exit(nil);
  case TTgDto.IndexOfValue(TJSONObject(AJson), 'status', [
    'creator',
    'administrator',
    'member',
    'restricted',
    'left',
    'kicked']) of
    0: Result := TTgChatMemberOwnerImpl.Create(AJson, AOwner);
    1: Result := TTgChatMemberAdministratorImpl.Create(AJson, AOwner);
    2: Result := TTgChatMemberMemberImpl.Create(AJson, AOwner);
    3: Result := TTgChatMemberRestrictedImpl.Create(AJson, AOwner);
    4: Result := TTgChatMemberLeftImpl.Create(AJson, AOwner);
    5: Result := TTgChatMemberBannedImpl.Create(AJson, AOwner);
  else
    Result := TTgChatMemberImpl.Create(AJson, AOwner);
  end;
end;

function TgMakeChatMemberOwner(AJson: TJSONValue; const AOwner: IInterface): ITgChatMemberOwner;
begin
  if AJson is TJSONObject then
    Result := TTgChatMemberOwnerImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChatMemberAdministrator(AJson: TJSONValue; const AOwner: IInterface): ITgChatMemberAdministrator;
begin
  if AJson is TJSONObject then
    Result := TTgChatMemberAdministratorImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChatMemberMember(AJson: TJSONValue; const AOwner: IInterface): ITgChatMemberMember;
begin
  if AJson is TJSONObject then
    Result := TTgChatMemberMemberImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChatMemberRestricted(AJson: TJSONValue; const AOwner: IInterface): ITgChatMemberRestricted;
begin
  if AJson is TJSONObject then
    Result := TTgChatMemberRestrictedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChatMemberLeft(AJson: TJSONValue; const AOwner: IInterface): ITgChatMemberLeft;
begin
  if AJson is TJSONObject then
    Result := TTgChatMemberLeftImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChatMemberBanned(AJson: TJSONValue; const AOwner: IInterface): ITgChatMemberBanned;
begin
  if AJson is TJSONObject then
    Result := TTgChatMemberBannedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChatJoinRequest(AJson: TJSONValue; const AOwner: IInterface): ITgChatJoinRequest;
begin
  if AJson is TJSONObject then
    Result := TTgChatJoinRequestImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChatPermissions(AJson: TJSONValue; const AOwner: IInterface): ITgChatPermissions;
begin
  if AJson is TJSONObject then
    Result := TTgChatPermissionsImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeBirthdate(AJson: TJSONValue; const AOwner: IInterface): ITgBirthdate;
begin
  if AJson is TJSONObject then
    Result := TTgBirthdateImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeBusinessIntro(AJson: TJSONValue; const AOwner: IInterface): ITgBusinessIntro;
begin
  if AJson is TJSONObject then
    Result := TTgBusinessIntroImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeBusinessLocation(AJson: TJSONValue; const AOwner: IInterface): ITgBusinessLocation;
begin
  if AJson is TJSONObject then
    Result := TTgBusinessLocationImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeBusinessOpeningHoursInterval(AJson: TJSONValue; const AOwner: IInterface): ITgBusinessOpeningHoursInterval;
begin
  if AJson is TJSONObject then
    Result := TTgBusinessOpeningHoursIntervalImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeBusinessOpeningHours(AJson: TJSONValue; const AOwner: IInterface): ITgBusinessOpeningHours;
begin
  if AJson is TJSONObject then
    Result := TTgBusinessOpeningHoursImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeUserRating(AJson: TJSONValue; const AOwner: IInterface): ITgUserRating;
begin
  if AJson is TJSONObject then
    Result := TTgUserRatingImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChatLocation(AJson: TJSONValue; const AOwner: IInterface): ITgChatLocation;
begin
  if AJson is TJSONObject then
    Result := TTgChatLocationImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeReactionType(AJson: TJSONValue; const AOwner: IInterface): ITgReactionType;
begin
  if not (AJson is TJSONObject) then
    Exit(nil);
  case TTgDto.IndexOfValue(TJSONObject(AJson), 'type', [
    'emoji',
    'custom_emoji',
    'paid']) of
    0: Result := TTgReactionTypeEmojiImpl.Create(AJson, AOwner);
    1: Result := TTgReactionTypeCustomEmojiImpl.Create(AJson, AOwner);
    2: Result := TTgReactionTypePaidImpl.Create(AJson, AOwner);
  else
    Result := TTgReactionTypeImpl.Create(AJson, AOwner);
  end;
end;

function TgMakeReactionTypeEmoji(AJson: TJSONValue; const AOwner: IInterface): ITgReactionTypeEmoji;
begin
  if AJson is TJSONObject then
    Result := TTgReactionTypeEmojiImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeReactionTypeCustomEmoji(AJson: TJSONValue; const AOwner: IInterface): ITgReactionTypeCustomEmoji;
begin
  if AJson is TJSONObject then
    Result := TTgReactionTypeCustomEmojiImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeReactionTypePaid(AJson: TJSONValue; const AOwner: IInterface): ITgReactionTypePaid;
begin
  if AJson is TJSONObject then
    Result := TTgReactionTypePaidImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeReactionCount(AJson: TJSONValue; const AOwner: IInterface): ITgReactionCount;
begin
  if AJson is TJSONObject then
    Result := TTgReactionCountImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeMessageReactionUpdated(AJson: TJSONValue; const AOwner: IInterface): ITgMessageReactionUpdated;
begin
  if AJson is TJSONObject then
    Result := TTgMessageReactionUpdatedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeMessageReactionCountUpdated(AJson: TJSONValue; const AOwner: IInterface): ITgMessageReactionCountUpdated;
begin
  if AJson is TJSONObject then
    Result := TTgMessageReactionCountUpdatedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeForumTopic(AJson: TJSONValue; const AOwner: IInterface): ITgForumTopic;
begin
  if AJson is TJSONObject then
    Result := TTgForumTopicImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeGiftBackground(AJson: TJSONValue; const AOwner: IInterface): ITgGiftBackground;
begin
  if AJson is TJSONObject then
    Result := TTgGiftBackgroundImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeGift(AJson: TJSONValue; const AOwner: IInterface): ITgGift;
begin
  if AJson is TJSONObject then
    Result := TTgGiftImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeGifts(AJson: TJSONValue; const AOwner: IInterface): ITgGifts;
begin
  if AJson is TJSONObject then
    Result := TTgGiftsImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeUniqueGiftModel(AJson: TJSONValue; const AOwner: IInterface): ITgUniqueGiftModel;
begin
  if AJson is TJSONObject then
    Result := TTgUniqueGiftModelImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeUniqueGiftSymbol(AJson: TJSONValue; const AOwner: IInterface): ITgUniqueGiftSymbol;
begin
  if AJson is TJSONObject then
    Result := TTgUniqueGiftSymbolImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeUniqueGiftBackdropColors(AJson: TJSONValue; const AOwner: IInterface): ITgUniqueGiftBackdropColors;
begin
  if AJson is TJSONObject then
    Result := TTgUniqueGiftBackdropColorsImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeUniqueGiftBackdrop(AJson: TJSONValue; const AOwner: IInterface): ITgUniqueGiftBackdrop;
begin
  if AJson is TJSONObject then
    Result := TTgUniqueGiftBackdropImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeUniqueGiftColors(AJson: TJSONValue; const AOwner: IInterface): ITgUniqueGiftColors;
begin
  if AJson is TJSONObject then
    Result := TTgUniqueGiftColorsImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeUniqueGift(AJson: TJSONValue; const AOwner: IInterface): ITgUniqueGift;
begin
  if AJson is TJSONObject then
    Result := TTgUniqueGiftImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeGiftInfo(AJson: TJSONValue; const AOwner: IInterface): ITgGiftInfo;
begin
  if AJson is TJSONObject then
    Result := TTgGiftInfoImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeUniqueGiftInfo(AJson: TJSONValue; const AOwner: IInterface): ITgUniqueGiftInfo;
begin
  if AJson is TJSONObject then
    Result := TTgUniqueGiftInfoImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeOwnedGift(AJson: TJSONValue; const AOwner: IInterface): ITgOwnedGift;
begin
  if not (AJson is TJSONObject) then
    Exit(nil);
  case TTgDto.IndexOfValue(TJSONObject(AJson), 'type', [
    'regular',
    'unique']) of
    0: Result := TTgOwnedGiftRegularImpl.Create(AJson, AOwner);
    1: Result := TTgOwnedGiftUniqueImpl.Create(AJson, AOwner);
  else
    Result := TTgOwnedGiftImpl.Create(AJson, AOwner);
  end;
end;

function TgMakeOwnedGiftRegular(AJson: TJSONValue; const AOwner: IInterface): ITgOwnedGiftRegular;
begin
  if AJson is TJSONObject then
    Result := TTgOwnedGiftRegularImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeOwnedGiftUnique(AJson: TJSONValue; const AOwner: IInterface): ITgOwnedGiftUnique;
begin
  if AJson is TJSONObject then
    Result := TTgOwnedGiftUniqueImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeOwnedGifts(AJson: TJSONValue; const AOwner: IInterface): ITgOwnedGifts;
begin
  if AJson is TJSONObject then
    Result := TTgOwnedGiftsImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeBotAccessSettings(AJson: TJSONValue; const AOwner: IInterface): ITgBotAccessSettings;
begin
  if AJson is TJSONObject then
    Result := TTgBotAccessSettingsImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeAcceptedGiftTypes(AJson: TJSONValue; const AOwner: IInterface): ITgAcceptedGiftTypes;
begin
  if AJson is TJSONObject then
    Result := TTgAcceptedGiftTypesImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeStarAmount(AJson: TJSONValue; const AOwner: IInterface): ITgStarAmount;
begin
  if AJson is TJSONObject then
    Result := TTgStarAmountImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeBotCommand(AJson: TJSONValue; const AOwner: IInterface): ITgBotCommand;
begin
  if AJson is TJSONObject then
    Result := TTgBotCommandImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeBotName(AJson: TJSONValue; const AOwner: IInterface): ITgBotName;
begin
  if AJson is TJSONObject then
    Result := TTgBotNameImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeBotDescription(AJson: TJSONValue; const AOwner: IInterface): ITgBotDescription;
begin
  if AJson is TJSONObject then
    Result := TTgBotDescriptionImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeBotShortDescription(AJson: TJSONValue; const AOwner: IInterface): ITgBotShortDescription;
begin
  if AJson is TJSONObject then
    Result := TTgBotShortDescriptionImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeMenuButton(AJson: TJSONValue; const AOwner: IInterface): ITgMenuButton;
begin
  if not (AJson is TJSONObject) then
    Exit(nil);
  case TTgDto.IndexOfValue(TJSONObject(AJson), 'type', [
    'commands',
    'web_app',
    'default']) of
    0: Result := TTgMenuButtonCommandsImpl.Create(AJson, AOwner);
    1: Result := TTgMenuButtonWebAppImpl.Create(AJson, AOwner);
    2: Result := TTgMenuButtonDefaultImpl.Create(AJson, AOwner);
  else
    Result := TTgMenuButtonImpl.Create(AJson, AOwner);
  end;
end;

function TgMakeMenuButtonCommands(AJson: TJSONValue; const AOwner: IInterface): ITgMenuButtonCommands;
begin
  if AJson is TJSONObject then
    Result := TTgMenuButtonCommandsImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeMenuButtonWebApp(AJson: TJSONValue; const AOwner: IInterface): ITgMenuButtonWebApp;
begin
  if AJson is TJSONObject then
    Result := TTgMenuButtonWebAppImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeMenuButtonDefault(AJson: TJSONValue; const AOwner: IInterface): ITgMenuButtonDefault;
begin
  if AJson is TJSONObject then
    Result := TTgMenuButtonDefaultImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChatBoostSource(AJson: TJSONValue; const AOwner: IInterface): ITgChatBoostSource;
begin
  if not (AJson is TJSONObject) then
    Exit(nil);
  case TTgDto.IndexOfValue(TJSONObject(AJson), 'source', [
    'premium',
    'gift_code',
    'giveaway']) of
    0: Result := TTgChatBoostSourcePremiumImpl.Create(AJson, AOwner);
    1: Result := TTgChatBoostSourceGiftCodeImpl.Create(AJson, AOwner);
    2: Result := TTgChatBoostSourceGiveawayImpl.Create(AJson, AOwner);
  else
    Result := TTgChatBoostSourceImpl.Create(AJson, AOwner);
  end;
end;

function TgMakeChatBoostSourcePremium(AJson: TJSONValue; const AOwner: IInterface): ITgChatBoostSourcePremium;
begin
  if AJson is TJSONObject then
    Result := TTgChatBoostSourcePremiumImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChatBoostSourceGiftCode(AJson: TJSONValue; const AOwner: IInterface): ITgChatBoostSourceGiftCode;
begin
  if AJson is TJSONObject then
    Result := TTgChatBoostSourceGiftCodeImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChatBoostSourceGiveaway(AJson: TJSONValue; const AOwner: IInterface): ITgChatBoostSourceGiveaway;
begin
  if AJson is TJSONObject then
    Result := TTgChatBoostSourceGiveawayImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChatBoost(AJson: TJSONValue; const AOwner: IInterface): ITgChatBoost;
begin
  if AJson is TJSONObject then
    Result := TTgChatBoostImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChatBoostUpdated(AJson: TJSONValue; const AOwner: IInterface): ITgChatBoostUpdated;
begin
  if AJson is TJSONObject then
    Result := TTgChatBoostUpdatedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChatBoostRemoved(AJson: TJSONValue; const AOwner: IInterface): ITgChatBoostRemoved;
begin
  if AJson is TJSONObject then
    Result := TTgChatBoostRemovedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChatOwnerLeft(AJson: TJSONValue; const AOwner: IInterface): ITgChatOwnerLeft;
begin
  if AJson is TJSONObject then
    Result := TTgChatOwnerLeftImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChatOwnerChanged(AJson: TJSONValue; const AOwner: IInterface): ITgChatOwnerChanged;
begin
  if AJson is TJSONObject then
    Result := TTgChatOwnerChangedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeUserChatBoosts(AJson: TJSONValue; const AOwner: IInterface): ITgUserChatBoosts;
begin
  if AJson is TJSONObject then
    Result := TTgUserChatBoostsImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeBusinessBotRights(AJson: TJSONValue; const AOwner: IInterface): ITgBusinessBotRights;
begin
  if AJson is TJSONObject then
    Result := TTgBusinessBotRightsImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeBusinessConnection(AJson: TJSONValue; const AOwner: IInterface): ITgBusinessConnection;
begin
  if AJson is TJSONObject then
    Result := TTgBusinessConnectionImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeBusinessMessagesDeleted(AJson: TJSONValue; const AOwner: IInterface): ITgBusinessMessagesDeleted;
begin
  if AJson is TJSONObject then
    Result := TTgBusinessMessagesDeletedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeSentWebAppMessage(AJson: TJSONValue; const AOwner: IInterface): ITgSentWebAppMessage;
begin
  if AJson is TJSONObject then
    Result := TTgSentWebAppMessageImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeSentGuestMessage(AJson: TJSONValue; const AOwner: IInterface): ITgSentGuestMessage;
begin
  if AJson is TJSONObject then
    Result := TTgSentGuestMessageImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakePreparedInlineMessage(AJson: TJSONValue; const AOwner: IInterface): ITgPreparedInlineMessage;
begin
  if AJson is TJSONObject then
    Result := TTgPreparedInlineMessageImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakePreparedKeyboardButton(AJson: TJSONValue; const AOwner: IInterface): ITgPreparedKeyboardButton;
begin
  if AJson is TJSONObject then
    Result := TTgPreparedKeyboardButtonImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeResponseParameters(AJson: TJSONValue; const AOwner: IInterface): ITgResponseParameters;
begin
  if AJson is TJSONObject then
    Result := TTgResponseParametersImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeSticker(AJson: TJSONValue; const AOwner: IInterface): ITgSticker;
begin
  if AJson is TJSONObject then
    Result := TTgStickerImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeStickerSet(AJson: TJSONValue; const AOwner: IInterface): ITgStickerSet;
begin
  if AJson is TJSONObject then
    Result := TTgStickerSetImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeMaskPosition(AJson: TJSONValue; const AOwner: IInterface): ITgMaskPosition;
begin
  if AJson is TJSONObject then
    Result := TTgMaskPositionImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichMessage(AJson: TJSONValue; const AOwner: IInterface): ITgRichMessage;
begin
  if AJson is TJSONObject then
    Result := TTgRichMessageImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichMessageButton(AJson: TJSONValue; const AOwner: IInterface): ITgRichMessageButton;
begin
  if AJson is TJSONObject then
    Result := TTgRichMessageButtonImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichText(AJson: TJSONValue; const AOwner: IInterface): ITgRichText;
begin
  if AJson is TJSONArray then
    Exit(TTgRichTextListImpl.Create(AJson, AOwner));
  if (AJson is TJSONString) and not (AJson is TJSONNumber) then
    Exit(TTgRichTextPlainImpl.Create(AJson, AOwner));
  if not (AJson is TJSONObject) then
    Exit(nil);
  case TTgDto.IndexOfValue(TJSONObject(AJson), 'type', [
    'bold',
    'italic',
    'underline',
    'strikethrough',
    'spoiler',
    'date_time',
    'text_mention',
    'subscript',
    'superscript',
    'marked',
    'code',
    'custom_emoji',
    'mathematical_expression',
    'url',
    'email_address',
    'phone_number',
    'bank_card_number',
    'mention',
    'hashtag',
    'cashtag',
    'bot_command',
    'button',
    'anchor',
    'anchor_link',
    'reference',
    'reference_link']) of
    0: Result := TTgRichTextBoldImpl.Create(AJson, AOwner);
    1: Result := TTgRichTextItalicImpl.Create(AJson, AOwner);
    2: Result := TTgRichTextUnderlineImpl.Create(AJson, AOwner);
    3: Result := TTgRichTextStrikethroughImpl.Create(AJson, AOwner);
    4: Result := TTgRichTextSpoilerImpl.Create(AJson, AOwner);
    5: Result := TTgRichTextDateTimeImpl.Create(AJson, AOwner);
    6: Result := TTgRichTextTextMentionImpl.Create(AJson, AOwner);
    7: Result := TTgRichTextSubscriptImpl.Create(AJson, AOwner);
    8: Result := TTgRichTextSuperscriptImpl.Create(AJson, AOwner);
    9: Result := TTgRichTextMarkedImpl.Create(AJson, AOwner);
    10: Result := TTgRichTextCodeImpl.Create(AJson, AOwner);
    11: Result := TTgRichTextCustomEmojiImpl.Create(AJson, AOwner);
    12: Result := TTgRichTextMathematicalExpressionImpl.Create(AJson, AOwner);
    13: Result := TTgRichTextUrlImpl.Create(AJson, AOwner);
    14: Result := TTgRichTextEmailAddressImpl.Create(AJson, AOwner);
    15: Result := TTgRichTextPhoneNumberImpl.Create(AJson, AOwner);
    16: Result := TTgRichTextBankCardNumberImpl.Create(AJson, AOwner);
    17: Result := TTgRichTextMentionImpl.Create(AJson, AOwner);
    18: Result := TTgRichTextHashtagImpl.Create(AJson, AOwner);
    19: Result := TTgRichTextCashtagImpl.Create(AJson, AOwner);
    20: Result := TTgRichTextBotCommandImpl.Create(AJson, AOwner);
    21: Result := TTgRichTextButtonImpl.Create(AJson, AOwner);
    22: Result := TTgRichTextAnchorImpl.Create(AJson, AOwner);
    23: Result := TTgRichTextAnchorLinkImpl.Create(AJson, AOwner);
    24: Result := TTgRichTextReferenceImpl.Create(AJson, AOwner);
    25: Result := TTgRichTextReferenceLinkImpl.Create(AJson, AOwner);
  else
    Result := TTgRichTextImpl.Create(AJson, AOwner);
  end;
end;

function TgMakeRichTextBold(AJson: TJSONValue; const AOwner: IInterface): ITgRichTextBold;
begin
  if AJson is TJSONObject then
    Result := TTgRichTextBoldImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichTextItalic(AJson: TJSONValue; const AOwner: IInterface): ITgRichTextItalic;
begin
  if AJson is TJSONObject then
    Result := TTgRichTextItalicImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichTextUnderline(AJson: TJSONValue; const AOwner: IInterface): ITgRichTextUnderline;
begin
  if AJson is TJSONObject then
    Result := TTgRichTextUnderlineImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichTextStrikethrough(AJson: TJSONValue; const AOwner: IInterface): ITgRichTextStrikethrough;
begin
  if AJson is TJSONObject then
    Result := TTgRichTextStrikethroughImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichTextSpoiler(AJson: TJSONValue; const AOwner: IInterface): ITgRichTextSpoiler;
begin
  if AJson is TJSONObject then
    Result := TTgRichTextSpoilerImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichTextDateTime(AJson: TJSONValue; const AOwner: IInterface): ITgRichTextDateTime;
begin
  if AJson is TJSONObject then
    Result := TTgRichTextDateTimeImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichTextTextMention(AJson: TJSONValue; const AOwner: IInterface): ITgRichTextTextMention;
begin
  if AJson is TJSONObject then
    Result := TTgRichTextTextMentionImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichTextSubscript(AJson: TJSONValue; const AOwner: IInterface): ITgRichTextSubscript;
begin
  if AJson is TJSONObject then
    Result := TTgRichTextSubscriptImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichTextSuperscript(AJson: TJSONValue; const AOwner: IInterface): ITgRichTextSuperscript;
begin
  if AJson is TJSONObject then
    Result := TTgRichTextSuperscriptImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichTextMarked(AJson: TJSONValue; const AOwner: IInterface): ITgRichTextMarked;
begin
  if AJson is TJSONObject then
    Result := TTgRichTextMarkedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichTextCode(AJson: TJSONValue; const AOwner: IInterface): ITgRichTextCode;
begin
  if AJson is TJSONObject then
    Result := TTgRichTextCodeImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichTextCustomEmoji(AJson: TJSONValue; const AOwner: IInterface): ITgRichTextCustomEmoji;
begin
  if AJson is TJSONObject then
    Result := TTgRichTextCustomEmojiImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichTextMathematicalExpression(AJson: TJSONValue; const AOwner: IInterface): ITgRichTextMathematicalExpression;
begin
  if AJson is TJSONObject then
    Result := TTgRichTextMathematicalExpressionImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichTextUrl(AJson: TJSONValue; const AOwner: IInterface): ITgRichTextUrl;
begin
  if AJson is TJSONObject then
    Result := TTgRichTextUrlImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichTextEmailAddress(AJson: TJSONValue; const AOwner: IInterface): ITgRichTextEmailAddress;
begin
  if AJson is TJSONObject then
    Result := TTgRichTextEmailAddressImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichTextPhoneNumber(AJson: TJSONValue; const AOwner: IInterface): ITgRichTextPhoneNumber;
begin
  if AJson is TJSONObject then
    Result := TTgRichTextPhoneNumberImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichTextBankCardNumber(AJson: TJSONValue; const AOwner: IInterface): ITgRichTextBankCardNumber;
begin
  if AJson is TJSONObject then
    Result := TTgRichTextBankCardNumberImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichTextMention(AJson: TJSONValue; const AOwner: IInterface): ITgRichTextMention;
begin
  if AJson is TJSONObject then
    Result := TTgRichTextMentionImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichTextHashtag(AJson: TJSONValue; const AOwner: IInterface): ITgRichTextHashtag;
begin
  if AJson is TJSONObject then
    Result := TTgRichTextHashtagImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichTextCashtag(AJson: TJSONValue; const AOwner: IInterface): ITgRichTextCashtag;
begin
  if AJson is TJSONObject then
    Result := TTgRichTextCashtagImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichTextBotCommand(AJson: TJSONValue; const AOwner: IInterface): ITgRichTextBotCommand;
begin
  if AJson is TJSONObject then
    Result := TTgRichTextBotCommandImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichTextButton(AJson: TJSONValue; const AOwner: IInterface): ITgRichTextButton;
begin
  if AJson is TJSONObject then
    Result := TTgRichTextButtonImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichTextAnchor(AJson: TJSONValue; const AOwner: IInterface): ITgRichTextAnchor;
begin
  if AJson is TJSONObject then
    Result := TTgRichTextAnchorImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichTextAnchorLink(AJson: TJSONValue; const AOwner: IInterface): ITgRichTextAnchorLink;
begin
  if AJson is TJSONObject then
    Result := TTgRichTextAnchorLinkImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichTextReference(AJson: TJSONValue; const AOwner: IInterface): ITgRichTextReference;
begin
  if AJson is TJSONObject then
    Result := TTgRichTextReferenceImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichTextReferenceLink(AJson: TJSONValue; const AOwner: IInterface): ITgRichTextReferenceLink;
begin
  if AJson is TJSONObject then
    Result := TTgRichTextReferenceLinkImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichBlockCaption(AJson: TJSONValue; const AOwner: IInterface): ITgRichBlockCaption;
begin
  if AJson is TJSONObject then
    Result := TTgRichBlockCaptionImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichBlockTableCell(AJson: TJSONValue; const AOwner: IInterface): ITgRichBlockTableCell;
begin
  if AJson is TJSONObject then
    Result := TTgRichBlockTableCellImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichBlockListItem(AJson: TJSONValue; const AOwner: IInterface): ITgRichBlockListItem;
begin
  if AJson is TJSONObject then
    Result := TTgRichBlockListItemImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichBlock(AJson: TJSONValue; const AOwner: IInterface): ITgRichBlock;
begin
  if not (AJson is TJSONObject) then
    Exit(nil);
  case TTgDto.IndexOfValue(TJSONObject(AJson), 'type', [
    'paragraph',
    'heading',
    'pre',
    'footer',
    'divider',
    'mathematical_expression',
    'anchor',
    'list',
    'blockquote',
    'expandable_blockquote',
    'pullquote',
    'collage',
    'slideshow',
    'table',
    'details',
    'map',
    'buttons',
    'animation',
    'audio',
    'document',
    'photo',
    'video',
    'voice_note',
    'thinking']) of
    0: Result := TTgRichBlockParagraphImpl.Create(AJson, AOwner);
    1: Result := TTgRichBlockSectionHeadingImpl.Create(AJson, AOwner);
    2: Result := TTgRichBlockPreformattedImpl.Create(AJson, AOwner);
    3: Result := TTgRichBlockFooterImpl.Create(AJson, AOwner);
    4: Result := TTgRichBlockDividerImpl.Create(AJson, AOwner);
    5: Result := TTgRichBlockMathematicalExpressionImpl.Create(AJson, AOwner);
    6: Result := TTgRichBlockAnchorImpl.Create(AJson, AOwner);
    7: Result := TTgRichBlockListImpl.Create(AJson, AOwner);
    8: Result := TTgRichBlockBlockQuotationImpl.Create(AJson, AOwner);
    9: Result := TTgRichBlockExpandableBlockQuotationImpl.Create(AJson, AOwner);
    10: Result := TTgRichBlockPullQuotationImpl.Create(AJson, AOwner);
    11: Result := TTgRichBlockCollageImpl.Create(AJson, AOwner);
    12: Result := TTgRichBlockSlideshowImpl.Create(AJson, AOwner);
    13: Result := TTgRichBlockTableImpl.Create(AJson, AOwner);
    14: Result := TTgRichBlockDetailsImpl.Create(AJson, AOwner);
    15: Result := TTgRichBlockMapImpl.Create(AJson, AOwner);
    16: Result := TTgRichBlockButtonsImpl.Create(AJson, AOwner);
    17: Result := TTgRichBlockAnimationImpl.Create(AJson, AOwner);
    18: Result := TTgRichBlockAudioImpl.Create(AJson, AOwner);
    19: Result := TTgRichBlockDocumentImpl.Create(AJson, AOwner);
    20: Result := TTgRichBlockPhotoImpl.Create(AJson, AOwner);
    21: Result := TTgRichBlockVideoImpl.Create(AJson, AOwner);
    22: Result := TTgRichBlockVoiceNoteImpl.Create(AJson, AOwner);
    23: Result := TTgRichBlockThinkingImpl.Create(AJson, AOwner);
  else
    Result := TTgRichBlockImpl.Create(AJson, AOwner);
  end;
end;

function TgMakeRichBlockParagraph(AJson: TJSONValue; const AOwner: IInterface): ITgRichBlockParagraph;
begin
  if AJson is TJSONObject then
    Result := TTgRichBlockParagraphImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichBlockSectionHeading(AJson: TJSONValue; const AOwner: IInterface): ITgRichBlockSectionHeading;
begin
  if AJson is TJSONObject then
    Result := TTgRichBlockSectionHeadingImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichBlockPreformatted(AJson: TJSONValue; const AOwner: IInterface): ITgRichBlockPreformatted;
begin
  if AJson is TJSONObject then
    Result := TTgRichBlockPreformattedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichBlockFooter(AJson: TJSONValue; const AOwner: IInterface): ITgRichBlockFooter;
begin
  if AJson is TJSONObject then
    Result := TTgRichBlockFooterImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichBlockDivider(AJson: TJSONValue; const AOwner: IInterface): ITgRichBlockDivider;
begin
  if AJson is TJSONObject then
    Result := TTgRichBlockDividerImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichBlockMathematicalExpression(AJson: TJSONValue; const AOwner: IInterface): ITgRichBlockMathematicalExpression;
begin
  if AJson is TJSONObject then
    Result := TTgRichBlockMathematicalExpressionImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichBlockAnchor(AJson: TJSONValue; const AOwner: IInterface): ITgRichBlockAnchor;
begin
  if AJson is TJSONObject then
    Result := TTgRichBlockAnchorImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichBlockList(AJson: TJSONValue; const AOwner: IInterface): ITgRichBlockList;
begin
  if AJson is TJSONObject then
    Result := TTgRichBlockListImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichBlockBlockQuotation(AJson: TJSONValue; const AOwner: IInterface): ITgRichBlockBlockQuotation;
begin
  if AJson is TJSONObject then
    Result := TTgRichBlockBlockQuotationImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichBlockExpandableBlockQuotation(AJson: TJSONValue; const AOwner: IInterface): ITgRichBlockExpandableBlockQuotation;
begin
  if AJson is TJSONObject then
    Result := TTgRichBlockExpandableBlockQuotationImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichBlockPullQuotation(AJson: TJSONValue; const AOwner: IInterface): ITgRichBlockPullQuotation;
begin
  if AJson is TJSONObject then
    Result := TTgRichBlockPullQuotationImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichBlockCollage(AJson: TJSONValue; const AOwner: IInterface): ITgRichBlockCollage;
begin
  if AJson is TJSONObject then
    Result := TTgRichBlockCollageImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichBlockSlideshow(AJson: TJSONValue; const AOwner: IInterface): ITgRichBlockSlideshow;
begin
  if AJson is TJSONObject then
    Result := TTgRichBlockSlideshowImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichBlockTable(AJson: TJSONValue; const AOwner: IInterface): ITgRichBlockTable;
begin
  if AJson is TJSONObject then
    Result := TTgRichBlockTableImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichBlockDetails(AJson: TJSONValue; const AOwner: IInterface): ITgRichBlockDetails;
begin
  if AJson is TJSONObject then
    Result := TTgRichBlockDetailsImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichBlockMap(AJson: TJSONValue; const AOwner: IInterface): ITgRichBlockMap;
begin
  if AJson is TJSONObject then
    Result := TTgRichBlockMapImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichBlockButtons(AJson: TJSONValue; const AOwner: IInterface): ITgRichBlockButtons;
begin
  if AJson is TJSONObject then
    Result := TTgRichBlockButtonsImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichBlockAnimation(AJson: TJSONValue; const AOwner: IInterface): ITgRichBlockAnimation;
begin
  if AJson is TJSONObject then
    Result := TTgRichBlockAnimationImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichBlockAudio(AJson: TJSONValue; const AOwner: IInterface): ITgRichBlockAudio;
begin
  if AJson is TJSONObject then
    Result := TTgRichBlockAudioImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichBlockDocument(AJson: TJSONValue; const AOwner: IInterface): ITgRichBlockDocument;
begin
  if AJson is TJSONObject then
    Result := TTgRichBlockDocumentImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichBlockPhoto(AJson: TJSONValue; const AOwner: IInterface): ITgRichBlockPhoto;
begin
  if AJson is TJSONObject then
    Result := TTgRichBlockPhotoImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichBlockVideo(AJson: TJSONValue; const AOwner: IInterface): ITgRichBlockVideo;
begin
  if AJson is TJSONObject then
    Result := TTgRichBlockVideoImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichBlockVoiceNote(AJson: TJSONValue; const AOwner: IInterface): ITgRichBlockVoiceNote;
begin
  if AJson is TJSONObject then
    Result := TTgRichBlockVoiceNoteImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRichBlockThinking(AJson: TJSONValue; const AOwner: IInterface): ITgRichBlockThinking;
begin
  if AJson is TJSONObject then
    Result := TTgRichBlockThinkingImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeInlineQuery(AJson: TJSONValue; const AOwner: IInterface): ITgInlineQuery;
begin
  if AJson is TJSONObject then
    Result := TTgInlineQueryImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeChosenInlineResult(AJson: TJSONValue; const AOwner: IInterface): ITgChosenInlineResult;
begin
  if AJson is TJSONObject then
    Result := TTgChosenInlineResultImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeInvoice(AJson: TJSONValue; const AOwner: IInterface): ITgInvoice;
begin
  if AJson is TJSONObject then
    Result := TTgInvoiceImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeShippingAddress(AJson: TJSONValue; const AOwner: IInterface): ITgShippingAddress;
begin
  if AJson is TJSONObject then
    Result := TTgShippingAddressImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeOrderInfo(AJson: TJSONValue; const AOwner: IInterface): ITgOrderInfo;
begin
  if AJson is TJSONObject then
    Result := TTgOrderInfoImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeSuccessfulPayment(AJson: TJSONValue; const AOwner: IInterface): ITgSuccessfulPayment;
begin
  if AJson is TJSONObject then
    Result := TTgSuccessfulPaymentImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRefundedPayment(AJson: TJSONValue; const AOwner: IInterface): ITgRefundedPayment;
begin
  if AJson is TJSONObject then
    Result := TTgRefundedPaymentImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeShippingQuery(AJson: TJSONValue; const AOwner: IInterface): ITgShippingQuery;
begin
  if AJson is TJSONObject then
    Result := TTgShippingQueryImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakePreCheckoutQuery(AJson: TJSONValue; const AOwner: IInterface): ITgPreCheckoutQuery;
begin
  if AJson is TJSONObject then
    Result := TTgPreCheckoutQueryImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakePaidMediaPurchased(AJson: TJSONValue; const AOwner: IInterface): ITgPaidMediaPurchased;
begin
  if AJson is TJSONObject then
    Result := TTgPaidMediaPurchasedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRevenueWithdrawalState(AJson: TJSONValue; const AOwner: IInterface): ITgRevenueWithdrawalState;
begin
  if not (AJson is TJSONObject) then
    Exit(nil);
  case TTgDto.IndexOfValue(TJSONObject(AJson), 'type', [
    'pending',
    'succeeded',
    'failed']) of
    0: Result := TTgRevenueWithdrawalStatePendingImpl.Create(AJson, AOwner);
    1: Result := TTgRevenueWithdrawalStateSucceededImpl.Create(AJson, AOwner);
    2: Result := TTgRevenueWithdrawalStateFailedImpl.Create(AJson, AOwner);
  else
    Result := TTgRevenueWithdrawalStateImpl.Create(AJson, AOwner);
  end;
end;

function TgMakeRevenueWithdrawalStatePending(AJson: TJSONValue; const AOwner: IInterface): ITgRevenueWithdrawalStatePending;
begin
  if AJson is TJSONObject then
    Result := TTgRevenueWithdrawalStatePendingImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRevenueWithdrawalStateSucceeded(AJson: TJSONValue; const AOwner: IInterface): ITgRevenueWithdrawalStateSucceeded;
begin
  if AJson is TJSONObject then
    Result := TTgRevenueWithdrawalStateSucceededImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeRevenueWithdrawalStateFailed(AJson: TJSONValue; const AOwner: IInterface): ITgRevenueWithdrawalStateFailed;
begin
  if AJson is TJSONObject then
    Result := TTgRevenueWithdrawalStateFailedImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeAffiliateInfo(AJson: TJSONValue; const AOwner: IInterface): ITgAffiliateInfo;
begin
  if AJson is TJSONObject then
    Result := TTgAffiliateInfoImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeTransactionPartner(AJson: TJSONValue; const AOwner: IInterface): ITgTransactionPartner;
begin
  if not (AJson is TJSONObject) then
    Exit(nil);
  case TTgDto.IndexOfValue(TJSONObject(AJson), 'type', [
    'user',
    'chat',
    'affiliate_program',
    'fragment',
    'telegram_ads',
    'telegram_api',
    'other']) of
    0: Result := TTgTransactionPartnerUserImpl.Create(AJson, AOwner);
    1: Result := TTgTransactionPartnerChatImpl.Create(AJson, AOwner);
    2: Result := TTgTransactionPartnerAffiliateProgramImpl.Create(AJson, AOwner);
    3: Result := TTgTransactionPartnerFragmentImpl.Create(AJson, AOwner);
    4: Result := TTgTransactionPartnerTelegramAdsImpl.Create(AJson, AOwner);
    5: Result := TTgTransactionPartnerTelegramApiImpl.Create(AJson, AOwner);
    6: Result := TTgTransactionPartnerOtherImpl.Create(AJson, AOwner);
  else
    Result := TTgTransactionPartnerImpl.Create(AJson, AOwner);
  end;
end;

function TgMakeTransactionPartnerUser(AJson: TJSONValue; const AOwner: IInterface): ITgTransactionPartnerUser;
begin
  if AJson is TJSONObject then
    Result := TTgTransactionPartnerUserImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeTransactionPartnerChat(AJson: TJSONValue; const AOwner: IInterface): ITgTransactionPartnerChat;
begin
  if AJson is TJSONObject then
    Result := TTgTransactionPartnerChatImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeTransactionPartnerAffiliateProgram(AJson: TJSONValue; const AOwner: IInterface): ITgTransactionPartnerAffiliateProgram;
begin
  if AJson is TJSONObject then
    Result := TTgTransactionPartnerAffiliateProgramImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeTransactionPartnerFragment(AJson: TJSONValue; const AOwner: IInterface): ITgTransactionPartnerFragment;
begin
  if AJson is TJSONObject then
    Result := TTgTransactionPartnerFragmentImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeTransactionPartnerTelegramAds(AJson: TJSONValue; const AOwner: IInterface): ITgTransactionPartnerTelegramAds;
begin
  if AJson is TJSONObject then
    Result := TTgTransactionPartnerTelegramAdsImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeTransactionPartnerTelegramApi(AJson: TJSONValue; const AOwner: IInterface): ITgTransactionPartnerTelegramApi;
begin
  if AJson is TJSONObject then
    Result := TTgTransactionPartnerTelegramApiImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeTransactionPartnerOther(AJson: TJSONValue; const AOwner: IInterface): ITgTransactionPartnerOther;
begin
  if AJson is TJSONObject then
    Result := TTgTransactionPartnerOtherImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeStarTransaction(AJson: TJSONValue; const AOwner: IInterface): ITgStarTransaction;
begin
  if AJson is TJSONObject then
    Result := TTgStarTransactionImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeStarTransactions(AJson: TJSONValue; const AOwner: IInterface): ITgStarTransactions;
begin
  if AJson is TJSONObject then
    Result := TTgStarTransactionsImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakePassportData(AJson: TJSONValue; const AOwner: IInterface): ITgPassportData;
begin
  if AJson is TJSONObject then
    Result := TTgPassportDataImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakePassportFile(AJson: TJSONValue; const AOwner: IInterface): ITgPassportFile;
begin
  if AJson is TJSONObject then
    Result := TTgPassportFileImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeEncryptedPassportElement(AJson: TJSONValue; const AOwner: IInterface): ITgEncryptedPassportElement;
begin
  if AJson is TJSONObject then
    Result := TTgEncryptedPassportElementImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeEncryptedCredentials(AJson: TJSONValue; const AOwner: IInterface): ITgEncryptedCredentials;
begin
  if AJson is TJSONObject then
    Result := TTgEncryptedCredentialsImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeGame(AJson: TJSONValue; const AOwner: IInterface): ITgGame;
begin
  if AJson is TJSONObject then
    Result := TTgGameImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeCallbackGame(AJson: TJSONValue; const AOwner: IInterface): ITgCallbackGame;
begin
  if AJson is TJSONObject then
    Result := TTgCallbackGameImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

function TgMakeGameHighScore(AJson: TJSONValue; const AOwner: IInterface): ITgGameHighScore;
begin
  if AJson is TJSONObject then
    Result := TTgGameHighScoreImpl.Create(AJson, AOwner)
  else
    Result := nil;
end;

