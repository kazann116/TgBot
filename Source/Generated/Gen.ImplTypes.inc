// Gen.ImplTypes.inc — реализация записей-объединений, классов и фабрик (implementation).
// Сгенерировано TgBotGen по Telegram Bot API 10.3 (August 24, 2026). Не редактируйте вручную.

{ TTgInputPollMedia }

class operator TTgInputPollMedia.Implicit(const AValue: ITgInputMediaAnimation): TTgInputPollMedia;
begin
  Result.FValue := AValue;
end;

class operator TTgInputPollMedia.Implicit(const AValue: ITgInputMediaAudio): TTgInputPollMedia;
begin
  Result.FValue := AValue;
end;

class operator TTgInputPollMedia.Implicit(const AValue: ITgInputMediaDocument): TTgInputPollMedia;
begin
  Result.FValue := AValue;
end;

class operator TTgInputPollMedia.Implicit(const AValue: ITgInputMediaLivePhoto): TTgInputPollMedia;
begin
  Result.FValue := AValue;
end;

class operator TTgInputPollMedia.Implicit(const AValue: ITgInputMediaLocation): TTgInputPollMedia;
begin
  Result.FValue := AValue;
end;

class operator TTgInputPollMedia.Implicit(const AValue: ITgInputMediaPhoto): TTgInputPollMedia;
begin
  Result.FValue := AValue;
end;

class operator TTgInputPollMedia.Implicit(const AValue: ITgInputMediaVenue): TTgInputPollMedia;
begin
  Result.FValue := AValue;
end;

class operator TTgInputPollMedia.Implicit(const AValue: ITgInputMediaVideo): TTgInputPollMedia;
begin
  Result.FValue := AValue;
end;

class function TTgInputPollMedia.Values(const AItems: array of TTgInputPollMedia): TArray<IInterface>;
var
  I: Integer;
begin
  SetLength(Result, Length(AItems));
  for I := 0 to High(AItems) do
    Result[I] := AItems[I].FValue;
end;

function TTgInputPollMedia.IsEmpty: Boolean;
begin
  Result := not Assigned(FValue);
end;

{ TTgInputPollOptionMedia }

class operator TTgInputPollOptionMedia.Implicit(const AValue: ITgInputMediaAnimation): TTgInputPollOptionMedia;
begin
  Result.FValue := AValue;
end;

class operator TTgInputPollOptionMedia.Implicit(const AValue: ITgInputMediaLink): TTgInputPollOptionMedia;
begin
  Result.FValue := AValue;
end;

class operator TTgInputPollOptionMedia.Implicit(const AValue: ITgInputMediaLivePhoto): TTgInputPollOptionMedia;
begin
  Result.FValue := AValue;
end;

class operator TTgInputPollOptionMedia.Implicit(const AValue: ITgInputMediaLocation): TTgInputPollOptionMedia;
begin
  Result.FValue := AValue;
end;

class operator TTgInputPollOptionMedia.Implicit(const AValue: ITgInputMediaPhoto): TTgInputPollOptionMedia;
begin
  Result.FValue := AValue;
end;

class operator TTgInputPollOptionMedia.Implicit(const AValue: ITgInputMediaSticker): TTgInputPollOptionMedia;
begin
  Result.FValue := AValue;
end;

class operator TTgInputPollOptionMedia.Implicit(const AValue: ITgInputMediaVenue): TTgInputPollOptionMedia;
begin
  Result.FValue := AValue;
end;

class operator TTgInputPollOptionMedia.Implicit(const AValue: ITgInputMediaVideo): TTgInputPollOptionMedia;
begin
  Result.FValue := AValue;
end;

class function TTgInputPollOptionMedia.Values(const AItems: array of TTgInputPollOptionMedia): TArray<IInterface>;
var
  I: Integer;
begin
  SetLength(Result, Length(AItems));
  for I := 0 to High(AItems) do
    Result[I] := AItems[I].FValue;
end;

function TTgInputPollOptionMedia.IsEmpty: Boolean;
begin
  Result := not Assigned(FValue);
end;

{ TTgStoryAreaType }

class operator TTgStoryAreaType.Implicit(const AValue: ITgStoryAreaTypeLocation): TTgStoryAreaType;
begin
  Result.FValue := AValue;
end;

class operator TTgStoryAreaType.Implicit(const AValue: ITgStoryAreaTypeSuggestedReaction): TTgStoryAreaType;
begin
  Result.FValue := AValue;
end;

class operator TTgStoryAreaType.Implicit(const AValue: ITgStoryAreaTypeLink): TTgStoryAreaType;
begin
  Result.FValue := AValue;
end;

class operator TTgStoryAreaType.Implicit(const AValue: ITgStoryAreaTypeWeather): TTgStoryAreaType;
begin
  Result.FValue := AValue;
end;

class operator TTgStoryAreaType.Implicit(const AValue: ITgStoryAreaTypeUniqueGift): TTgStoryAreaType;
begin
  Result.FValue := AValue;
end;

class function TTgStoryAreaType.Values(const AItems: array of TTgStoryAreaType): TArray<IInterface>;
var
  I: Integer;
begin
  SetLength(Result, Length(AItems));
  for I := 0 to High(AItems) do
    Result[I] := AItems[I].FValue;
end;

function TTgStoryAreaType.IsEmpty: Boolean;
begin
  Result := not Assigned(FValue);
end;

{ TTgBotCommandScope }

class operator TTgBotCommandScope.Implicit(const AValue: ITgBotCommandScopeDefault): TTgBotCommandScope;
begin
  Result.FValue := AValue;
end;

class operator TTgBotCommandScope.Implicit(const AValue: ITgBotCommandScopeAllPrivateChats): TTgBotCommandScope;
begin
  Result.FValue := AValue;
end;

class operator TTgBotCommandScope.Implicit(const AValue: ITgBotCommandScopeAllGroupChats): TTgBotCommandScope;
begin
  Result.FValue := AValue;
end;

class operator TTgBotCommandScope.Implicit(const AValue: ITgBotCommandScopeAllChatAdministrators): TTgBotCommandScope;
begin
  Result.FValue := AValue;
end;

class operator TTgBotCommandScope.Implicit(const AValue: ITgBotCommandScopeChat): TTgBotCommandScope;
begin
  Result.FValue := AValue;
end;

class operator TTgBotCommandScope.Implicit(const AValue: ITgBotCommandScopeChatAdministrators): TTgBotCommandScope;
begin
  Result.FValue := AValue;
end;

class operator TTgBotCommandScope.Implicit(const AValue: ITgBotCommandScopeChatMember): TTgBotCommandScope;
begin
  Result.FValue := AValue;
end;

class function TTgBotCommandScope.Values(const AItems: array of TTgBotCommandScope): TArray<IInterface>;
var
  I: Integer;
begin
  SetLength(Result, Length(AItems));
  for I := 0 to High(AItems) do
    Result[I] := AItems[I].FValue;
end;

function TTgBotCommandScope.IsEmpty: Boolean;
begin
  Result := not Assigned(FValue);
end;

{ TTgInputMedia }

class operator TTgInputMedia.Implicit(const AValue: ITgInputMediaAnimation): TTgInputMedia;
begin
  Result.FValue := AValue;
end;

class operator TTgInputMedia.Implicit(const AValue: ITgInputMediaAudio): TTgInputMedia;
begin
  Result.FValue := AValue;
end;

class operator TTgInputMedia.Implicit(const AValue: ITgInputMediaDocument): TTgInputMedia;
begin
  Result.FValue := AValue;
end;

class operator TTgInputMedia.Implicit(const AValue: ITgInputMediaLivePhoto): TTgInputMedia;
begin
  Result.FValue := AValue;
end;

class operator TTgInputMedia.Implicit(const AValue: ITgInputMediaPhoto): TTgInputMedia;
begin
  Result.FValue := AValue;
end;

class operator TTgInputMedia.Implicit(const AValue: ITgInputMediaVideo): TTgInputMedia;
begin
  Result.FValue := AValue;
end;

class function TTgInputMedia.Values(const AItems: array of TTgInputMedia): TArray<IInterface>;
var
  I: Integer;
begin
  SetLength(Result, Length(AItems));
  for I := 0 to High(AItems) do
    Result[I] := AItems[I].FValue;
end;

function TTgInputMedia.IsEmpty: Boolean;
begin
  Result := not Assigned(FValue);
end;

{ TTgInputPaidMedia }

class operator TTgInputPaidMedia.Implicit(const AValue: ITgInputPaidMediaLivePhoto): TTgInputPaidMedia;
begin
  Result.FValue := AValue;
end;

class operator TTgInputPaidMedia.Implicit(const AValue: ITgInputPaidMediaPhoto): TTgInputPaidMedia;
begin
  Result.FValue := AValue;
end;

class operator TTgInputPaidMedia.Implicit(const AValue: ITgInputPaidMediaVideo): TTgInputPaidMedia;
begin
  Result.FValue := AValue;
end;

class function TTgInputPaidMedia.Values(const AItems: array of TTgInputPaidMedia): TArray<IInterface>;
var
  I: Integer;
begin
  SetLength(Result, Length(AItems));
  for I := 0 to High(AItems) do
    Result[I] := AItems[I].FValue;
end;

function TTgInputPaidMedia.IsEmpty: Boolean;
begin
  Result := not Assigned(FValue);
end;

{ TTgInputProfilePhoto }

class operator TTgInputProfilePhoto.Implicit(const AValue: ITgInputProfilePhotoStatic): TTgInputProfilePhoto;
begin
  Result.FValue := AValue;
end;

class operator TTgInputProfilePhoto.Implicit(const AValue: ITgInputProfilePhotoAnimated): TTgInputProfilePhoto;
begin
  Result.FValue := AValue;
end;

class function TTgInputProfilePhoto.Values(const AItems: array of TTgInputProfilePhoto): TArray<IInterface>;
var
  I: Integer;
begin
  SetLength(Result, Length(AItems));
  for I := 0 to High(AItems) do
    Result[I] := AItems[I].FValue;
end;

function TTgInputProfilePhoto.IsEmpty: Boolean;
begin
  Result := not Assigned(FValue);
end;

{ TTgInputStoryContent }

class operator TTgInputStoryContent.Implicit(const AValue: ITgInputStoryContentPhoto): TTgInputStoryContent;
begin
  Result.FValue := AValue;
end;

class operator TTgInputStoryContent.Implicit(const AValue: ITgInputStoryContentVideo): TTgInputStoryContent;
begin
  Result.FValue := AValue;
end;

class function TTgInputStoryContent.Values(const AItems: array of TTgInputStoryContent): TArray<IInterface>;
var
  I: Integer;
begin
  SetLength(Result, Length(AItems));
  for I := 0 to High(AItems) do
    Result[I] := AItems[I].FValue;
end;

function TTgInputStoryContent.IsEmpty: Boolean;
begin
  Result := not Assigned(FValue);
end;

{ TTgInputRichBlock }

class operator TTgInputRichBlock.Implicit(const AValue: ITgInputRichBlockParagraph): TTgInputRichBlock;
begin
  Result.FValue := AValue;
end;

class operator TTgInputRichBlock.Implicit(const AValue: ITgInputRichBlockSectionHeading): TTgInputRichBlock;
begin
  Result.FValue := AValue;
end;

class operator TTgInputRichBlock.Implicit(const AValue: ITgInputRichBlockPreformatted): TTgInputRichBlock;
begin
  Result.FValue := AValue;
end;

class operator TTgInputRichBlock.Implicit(const AValue: ITgInputRichBlockFooter): TTgInputRichBlock;
begin
  Result.FValue := AValue;
end;

class operator TTgInputRichBlock.Implicit(const AValue: ITgInputRichBlockDivider): TTgInputRichBlock;
begin
  Result.FValue := AValue;
end;

class operator TTgInputRichBlock.Implicit(const AValue: ITgInputRichBlockMathematicalExpression): TTgInputRichBlock;
begin
  Result.FValue := AValue;
end;

class operator TTgInputRichBlock.Implicit(const AValue: ITgInputRichBlockAnchor): TTgInputRichBlock;
begin
  Result.FValue := AValue;
end;

class operator TTgInputRichBlock.Implicit(const AValue: ITgInputRichBlockList): TTgInputRichBlock;
begin
  Result.FValue := AValue;
end;

class operator TTgInputRichBlock.Implicit(const AValue: ITgInputRichBlockBlockQuotation): TTgInputRichBlock;
begin
  Result.FValue := AValue;
end;

class operator TTgInputRichBlock.Implicit(const AValue: ITgInputRichBlockExpandableBlockQuotation): TTgInputRichBlock;
begin
  Result.FValue := AValue;
end;

class operator TTgInputRichBlock.Implicit(const AValue: ITgInputRichBlockPullQuotation): TTgInputRichBlock;
begin
  Result.FValue := AValue;
end;

class operator TTgInputRichBlock.Implicit(const AValue: ITgInputRichBlockCollage): TTgInputRichBlock;
begin
  Result.FValue := AValue;
end;

class operator TTgInputRichBlock.Implicit(const AValue: ITgInputRichBlockSlideshow): TTgInputRichBlock;
begin
  Result.FValue := AValue;
end;

class operator TTgInputRichBlock.Implicit(const AValue: ITgInputRichBlockTable): TTgInputRichBlock;
begin
  Result.FValue := AValue;
end;

class operator TTgInputRichBlock.Implicit(const AValue: ITgInputRichBlockDetails): TTgInputRichBlock;
begin
  Result.FValue := AValue;
end;

class operator TTgInputRichBlock.Implicit(const AValue: ITgInputRichBlockMap): TTgInputRichBlock;
begin
  Result.FValue := AValue;
end;

class operator TTgInputRichBlock.Implicit(const AValue: ITgInputRichBlockButtons): TTgInputRichBlock;
begin
  Result.FValue := AValue;
end;

class operator TTgInputRichBlock.Implicit(const AValue: ITgInputRichBlockAnimation): TTgInputRichBlock;
begin
  Result.FValue := AValue;
end;

class operator TTgInputRichBlock.Implicit(const AValue: ITgInputRichBlockAudio): TTgInputRichBlock;
begin
  Result.FValue := AValue;
end;

class operator TTgInputRichBlock.Implicit(const AValue: ITgInputRichBlockDocument): TTgInputRichBlock;
begin
  Result.FValue := AValue;
end;

class operator TTgInputRichBlock.Implicit(const AValue: ITgInputRichBlockPhoto): TTgInputRichBlock;
begin
  Result.FValue := AValue;
end;

class operator TTgInputRichBlock.Implicit(const AValue: ITgInputRichBlockVideo): TTgInputRichBlock;
begin
  Result.FValue := AValue;
end;

class operator TTgInputRichBlock.Implicit(const AValue: ITgInputRichBlockVoiceNote): TTgInputRichBlock;
begin
  Result.FValue := AValue;
end;

class operator TTgInputRichBlock.Implicit(const AValue: ITgInputRichBlockThinking): TTgInputRichBlock;
begin
  Result.FValue := AValue;
end;

class function TTgInputRichBlock.Values(const AItems: array of TTgInputRichBlock): TArray<IInterface>;
var
  I: Integer;
begin
  SetLength(Result, Length(AItems));
  for I := 0 to High(AItems) do
    Result[I] := AItems[I].FValue;
end;

function TTgInputRichBlock.IsEmpty: Boolean;
begin
  Result := not Assigned(FValue);
end;

{ TTgInlineQueryResult }

class operator TTgInlineQueryResult.Implicit(const AValue: ITgInlineQueryResultCachedAudio): TTgInlineQueryResult;
begin
  Result.FValue := AValue;
end;

class operator TTgInlineQueryResult.Implicit(const AValue: ITgInlineQueryResultCachedDocument): TTgInlineQueryResult;
begin
  Result.FValue := AValue;
end;

class operator TTgInlineQueryResult.Implicit(const AValue: ITgInlineQueryResultCachedGif): TTgInlineQueryResult;
begin
  Result.FValue := AValue;
end;

class operator TTgInlineQueryResult.Implicit(const AValue: ITgInlineQueryResultCachedMpeg4Gif): TTgInlineQueryResult;
begin
  Result.FValue := AValue;
end;

class operator TTgInlineQueryResult.Implicit(const AValue: ITgInlineQueryResultCachedPhoto): TTgInlineQueryResult;
begin
  Result.FValue := AValue;
end;

class operator TTgInlineQueryResult.Implicit(const AValue: ITgInlineQueryResultCachedSticker): TTgInlineQueryResult;
begin
  Result.FValue := AValue;
end;

class operator TTgInlineQueryResult.Implicit(const AValue: ITgInlineQueryResultCachedVideo): TTgInlineQueryResult;
begin
  Result.FValue := AValue;
end;

class operator TTgInlineQueryResult.Implicit(const AValue: ITgInlineQueryResultCachedVoice): TTgInlineQueryResult;
begin
  Result.FValue := AValue;
end;

class operator TTgInlineQueryResult.Implicit(const AValue: ITgInlineQueryResultArticle): TTgInlineQueryResult;
begin
  Result.FValue := AValue;
end;

class operator TTgInlineQueryResult.Implicit(const AValue: ITgInlineQueryResultAudio): TTgInlineQueryResult;
begin
  Result.FValue := AValue;
end;

class operator TTgInlineQueryResult.Implicit(const AValue: ITgInlineQueryResultContact): TTgInlineQueryResult;
begin
  Result.FValue := AValue;
end;

class operator TTgInlineQueryResult.Implicit(const AValue: ITgInlineQueryResultGame): TTgInlineQueryResult;
begin
  Result.FValue := AValue;
end;

class operator TTgInlineQueryResult.Implicit(const AValue: ITgInlineQueryResultDocument): TTgInlineQueryResult;
begin
  Result.FValue := AValue;
end;

class operator TTgInlineQueryResult.Implicit(const AValue: ITgInlineQueryResultGif): TTgInlineQueryResult;
begin
  Result.FValue := AValue;
end;

class operator TTgInlineQueryResult.Implicit(const AValue: ITgInlineQueryResultLocation): TTgInlineQueryResult;
begin
  Result.FValue := AValue;
end;

class operator TTgInlineQueryResult.Implicit(const AValue: ITgInlineQueryResultMpeg4Gif): TTgInlineQueryResult;
begin
  Result.FValue := AValue;
end;

class operator TTgInlineQueryResult.Implicit(const AValue: ITgInlineQueryResultPhoto): TTgInlineQueryResult;
begin
  Result.FValue := AValue;
end;

class operator TTgInlineQueryResult.Implicit(const AValue: ITgInlineQueryResultVenue): TTgInlineQueryResult;
begin
  Result.FValue := AValue;
end;

class operator TTgInlineQueryResult.Implicit(const AValue: ITgInlineQueryResultVideo): TTgInlineQueryResult;
begin
  Result.FValue := AValue;
end;

class operator TTgInlineQueryResult.Implicit(const AValue: ITgInlineQueryResultVoice): TTgInlineQueryResult;
begin
  Result.FValue := AValue;
end;

class function TTgInlineQueryResult.Values(const AItems: array of TTgInlineQueryResult): TArray<IInterface>;
var
  I: Integer;
begin
  SetLength(Result, Length(AItems));
  for I := 0 to High(AItems) do
    Result[I] := AItems[I].FValue;
end;

function TTgInlineQueryResult.IsEmpty: Boolean;
begin
  Result := not Assigned(FValue);
end;

{ TTgInputMessageContent }

class operator TTgInputMessageContent.Implicit(const AValue: ITgInputTextMessageContent): TTgInputMessageContent;
begin
  Result.FValue := AValue;
end;

class operator TTgInputMessageContent.Implicit(const AValue: ITgInputRichMessageContent): TTgInputMessageContent;
begin
  Result.FValue := AValue;
end;

class operator TTgInputMessageContent.Implicit(const AValue: ITgInputLocationMessageContent): TTgInputMessageContent;
begin
  Result.FValue := AValue;
end;

class operator TTgInputMessageContent.Implicit(const AValue: ITgInputVenueMessageContent): TTgInputMessageContent;
begin
  Result.FValue := AValue;
end;

class operator TTgInputMessageContent.Implicit(const AValue: ITgInputContactMessageContent): TTgInputMessageContent;
begin
  Result.FValue := AValue;
end;

class operator TTgInputMessageContent.Implicit(const AValue: ITgInputInvoiceMessageContent): TTgInputMessageContent;
begin
  Result.FValue := AValue;
end;

class function TTgInputMessageContent.Values(const AItems: array of TTgInputMessageContent): TArray<IInterface>;
var
  I: Integer;
begin
  SetLength(Result, Length(AItems));
  for I := 0 to High(AItems) do
    Result[I] := AItems[I].FValue;
end;

function TTgInputMessageContent.IsEmpty: Boolean;
begin
  Result := not Assigned(FValue);
end;

{ TTgPassportElementError }

class operator TTgPassportElementError.Implicit(const AValue: ITgPassportElementErrorDataField): TTgPassportElementError;
begin
  Result.FValue := AValue;
end;

class operator TTgPassportElementError.Implicit(const AValue: ITgPassportElementErrorFrontSide): TTgPassportElementError;
begin
  Result.FValue := AValue;
end;

class operator TTgPassportElementError.Implicit(const AValue: ITgPassportElementErrorReverseSide): TTgPassportElementError;
begin
  Result.FValue := AValue;
end;

class operator TTgPassportElementError.Implicit(const AValue: ITgPassportElementErrorSelfie): TTgPassportElementError;
begin
  Result.FValue := AValue;
end;

class operator TTgPassportElementError.Implicit(const AValue: ITgPassportElementErrorFile): TTgPassportElementError;
begin
  Result.FValue := AValue;
end;

class operator TTgPassportElementError.Implicit(const AValue: ITgPassportElementErrorFiles): TTgPassportElementError;
begin
  Result.FValue := AValue;
end;

class operator TTgPassportElementError.Implicit(const AValue: ITgPassportElementErrorTranslationFile): TTgPassportElementError;
begin
  Result.FValue := AValue;
end;

class operator TTgPassportElementError.Implicit(const AValue: ITgPassportElementErrorTranslationFiles): TTgPassportElementError;
begin
  Result.FValue := AValue;
end;

class operator TTgPassportElementError.Implicit(const AValue: ITgPassportElementErrorUnspecified): TTgPassportElementError;
begin
  Result.FValue := AValue;
end;

class function TTgPassportElementError.Values(const AItems: array of TTgPassportElementError): TArray<IInterface>;
var
  I: Integer;
begin
  SetLength(Result, Length(AItems));
  for I := 0 to High(AItems) do
    Result[I] := AItems[I].FValue;
end;

function TTgPassportElementError.IsEmpty: Boolean;
begin
  Result := not Assigned(FValue);
end;

{ TTgInputRichMedia }

class operator TTgInputRichMedia.Implicit(const AValue: ITgInputMediaAnimation): TTgInputRichMedia;
begin
  Result.FValue := AValue;
end;

class operator TTgInputRichMedia.Implicit(const AValue: ITgInputMediaAudio): TTgInputRichMedia;
begin
  Result.FValue := AValue;
end;

class operator TTgInputRichMedia.Implicit(const AValue: ITgInputMediaDocument): TTgInputRichMedia;
begin
  Result.FValue := AValue;
end;

class operator TTgInputRichMedia.Implicit(const AValue: ITgInputMediaPhoto): TTgInputRichMedia;
begin
  Result.FValue := AValue;
end;

class operator TTgInputRichMedia.Implicit(const AValue: ITgInputMediaVideo): TTgInputRichMedia;
begin
  Result.FValue := AValue;
end;

class operator TTgInputRichMedia.Implicit(const AValue: ITgInputMediaVoiceNote): TTgInputRichMedia;
begin
  Result.FValue := AValue;
end;

class function TTgInputRichMedia.Values(const AItems: array of TTgInputRichMedia): TArray<IInterface>;
var
  I: Integer;
begin
  SetLength(Result, Length(AItems));
  for I := 0 to High(AItems) do
    Result[I] := AItems[I].FValue;
end;

function TTgInputRichMedia.IsEmpty: Boolean;
begin
  Result := not Assigned(FValue);
end;

{ TTgReplyMarkup }

class operator TTgReplyMarkup.Implicit(const AValue: ITgInlineKeyboardMarkup): TTgReplyMarkup;
begin
  Result.FValue := AValue;
end;

class operator TTgReplyMarkup.Implicit(const AValue: ITgReplyKeyboardMarkup): TTgReplyMarkup;
begin
  Result.FValue := AValue;
end;

class operator TTgReplyMarkup.Implicit(const AValue: ITgReplyKeyboardRemove): TTgReplyMarkup;
begin
  Result.FValue := AValue;
end;

class operator TTgReplyMarkup.Implicit(const AValue: ITgForceReply): TTgReplyMarkup;
begin
  Result.FValue := AValue;
end;

class function TTgReplyMarkup.Values(const AItems: array of TTgReplyMarkup): TArray<IInterface>;
var
  I: Integer;
begin
  SetLength(Result, Length(AItems));
  for I := 0 to High(AItems) do
    Result[I] := AItems[I].FValue;
end;

function TTgReplyMarkup.IsEmpty: Boolean;
begin
  Result := not Assigned(FValue);
end;

{ TTgMediaGroupItem }

class operator TTgMediaGroupItem.Implicit(const AValue: ITgInputMediaAudio): TTgMediaGroupItem;
begin
  Result.FValue := AValue;
end;

class operator TTgMediaGroupItem.Implicit(const AValue: ITgInputMediaDocument): TTgMediaGroupItem;
begin
  Result.FValue := AValue;
end;

class operator TTgMediaGroupItem.Implicit(const AValue: ITgInputMediaLivePhoto): TTgMediaGroupItem;
begin
  Result.FValue := AValue;
end;

class operator TTgMediaGroupItem.Implicit(const AValue: ITgInputMediaPhoto): TTgMediaGroupItem;
begin
  Result.FValue := AValue;
end;

class operator TTgMediaGroupItem.Implicit(const AValue: ITgInputMediaVideo): TTgMediaGroupItem;
begin
  Result.FValue := AValue;
end;

class function TTgMediaGroupItem.Values(const AItems: array of TTgMediaGroupItem): TArray<IInterface>;
var
  I: Integer;
begin
  SetLength(Result, Length(AItems));
  for I := 0 to High(AItems) do
    Result[I] := AItems[I].FValue;
end;

function TTgMediaGroupItem.IsEmpty: Boolean;
begin
  Result := not Assigned(FValue);
end;

{ TTgUpdateImpl }

function TTgUpdateImpl.GetUpdateId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'update_id');
end;

function TTgUpdateImpl.GetMessage: ITgMessage;
begin
  Result := TgMakeMessage(TTgJson.GetValue(FJson, 'message'), JsonOwner);
end;

function TTgUpdateImpl.GetEditedMessage: ITgMessage;
begin
  Result := TgMakeMessage(TTgJson.GetValue(FJson, 'edited_message'), JsonOwner);
end;

function TTgUpdateImpl.GetChannelPost: ITgMessage;
begin
  Result := TgMakeMessage(TTgJson.GetValue(FJson, 'channel_post'), JsonOwner);
end;

function TTgUpdateImpl.GetEditedChannelPost: ITgMessage;
begin
  Result := TgMakeMessage(TTgJson.GetValue(FJson, 'edited_channel_post'), JsonOwner);
end;

function TTgUpdateImpl.GetBusinessConnection: ITgBusinessConnection;
begin
  Result := TgMakeBusinessConnection(TTgJson.GetValue(FJson, 'business_connection'), JsonOwner);
end;

function TTgUpdateImpl.GetBusinessMessage: ITgMessage;
begin
  Result := TgMakeMessage(TTgJson.GetValue(FJson, 'business_message'), JsonOwner);
end;

function TTgUpdateImpl.GetEditedBusinessMessage: ITgMessage;
begin
  Result := TgMakeMessage(TTgJson.GetValue(FJson, 'edited_business_message'), JsonOwner);
end;

function TTgUpdateImpl.GetDeletedBusinessMessages: ITgBusinessMessagesDeleted;
begin
  Result := TgMakeBusinessMessagesDeleted(TTgJson.GetValue(FJson, 'deleted_business_messages'), JsonOwner);
end;

function TTgUpdateImpl.GetGuestMessage: ITgMessage;
begin
  Result := TgMakeMessage(TTgJson.GetValue(FJson, 'guest_message'), JsonOwner);
end;

function TTgUpdateImpl.GetMessageReaction: ITgMessageReactionUpdated;
begin
  Result := TgMakeMessageReactionUpdated(TTgJson.GetValue(FJson, 'message_reaction'), JsonOwner);
end;

function TTgUpdateImpl.GetMessageReactionCount: ITgMessageReactionCountUpdated;
begin
  Result := TgMakeMessageReactionCountUpdated(TTgJson.GetValue(FJson, 'message_reaction_count'), JsonOwner);
end;

function TTgUpdateImpl.GetInlineQuery: ITgInlineQuery;
begin
  Result := TgMakeInlineQuery(TTgJson.GetValue(FJson, 'inline_query'), JsonOwner);
end;

function TTgUpdateImpl.GetChosenInlineResult: ITgChosenInlineResult;
begin
  Result := TgMakeChosenInlineResult(TTgJson.GetValue(FJson, 'chosen_inline_result'), JsonOwner);
end;

function TTgUpdateImpl.GetCallbackQuery: ITgCallbackQuery;
begin
  Result := TgMakeCallbackQuery(TTgJson.GetValue(FJson, 'callback_query'), JsonOwner);
end;

function TTgUpdateImpl.GetShippingQuery: ITgShippingQuery;
begin
  Result := TgMakeShippingQuery(TTgJson.GetValue(FJson, 'shipping_query'), JsonOwner);
end;

function TTgUpdateImpl.GetPreCheckoutQuery: ITgPreCheckoutQuery;
begin
  Result := TgMakePreCheckoutQuery(TTgJson.GetValue(FJson, 'pre_checkout_query'), JsonOwner);
end;

function TTgUpdateImpl.GetPurchasedPaidMedia: ITgPaidMediaPurchased;
begin
  Result := TgMakePaidMediaPurchased(TTgJson.GetValue(FJson, 'purchased_paid_media'), JsonOwner);
end;

function TTgUpdateImpl.GetPoll: ITgPoll;
begin
  Result := TgMakePoll(TTgJson.GetValue(FJson, 'poll'), JsonOwner);
end;

function TTgUpdateImpl.GetPollAnswer: ITgPollAnswer;
begin
  Result := TgMakePollAnswer(TTgJson.GetValue(FJson, 'poll_answer'), JsonOwner);
end;

function TTgUpdateImpl.GetMyChatMember: ITgChatMemberUpdated;
begin
  Result := TgMakeChatMemberUpdated(TTgJson.GetValue(FJson, 'my_chat_member'), JsonOwner);
end;

function TTgUpdateImpl.GetChatMember: ITgChatMemberUpdated;
begin
  Result := TgMakeChatMemberUpdated(TTgJson.GetValue(FJson, 'chat_member'), JsonOwner);
end;

function TTgUpdateImpl.GetChatJoinRequest: ITgChatJoinRequest;
begin
  Result := TgMakeChatJoinRequest(TTgJson.GetValue(FJson, 'chat_join_request'), JsonOwner);
end;

function TTgUpdateImpl.GetChatBoost: ITgChatBoostUpdated;
begin
  Result := TgMakeChatBoostUpdated(TTgJson.GetValue(FJson, 'chat_boost'), JsonOwner);
end;

function TTgUpdateImpl.GetRemovedChatBoost: ITgChatBoostRemoved;
begin
  Result := TgMakeChatBoostRemoved(TTgJson.GetValue(FJson, 'removed_chat_boost'), JsonOwner);
end;

function TTgUpdateImpl.GetManagedBot: ITgManagedBotUpdated;
begin
  Result := TgMakeManagedBotUpdated(TTgJson.GetValue(FJson, 'managed_bot'), JsonOwner);
end;

function TTgUpdateImpl.GetSubscription: ITgBotSubscriptionUpdated;
begin
  Result := TgMakeBotSubscriptionUpdated(TTgJson.GetValue(FJson, 'subscription'), JsonOwner);
end;

function TTgUpdateImpl.GetStoppedMessageGeneration: ITgMessageGenerationStopped;
begin
  Result := TgMakeMessageGenerationStopped(TTgJson.GetValue(FJson, 'stopped_message_generation'), JsonOwner);
end;

{ TTgWebhookInfoImpl }

function TTgWebhookInfoImpl.GetUrl: string;
begin
  Result := TTgJson.GetStr(FJson, 'url');
end;

function TTgWebhookInfoImpl.GetHasCustomCertificate: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'has_custom_certificate');
end;

function TTgWebhookInfoImpl.GetPendingUpdateCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'pending_update_count');
end;

function TTgWebhookInfoImpl.GetIpAddress: string;
begin
  Result := TTgJson.GetStr(FJson, 'ip_address');
end;

function TTgWebhookInfoImpl.GetLastErrorDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'last_error_date');
end;

function TTgWebhookInfoImpl.GetHasLastErrorDate: Boolean;
begin
  Result := TTgJson.Has(FJson, 'last_error_date');
end;

function TTgWebhookInfoImpl.GetLastErrorMessage: string;
begin
  Result := TTgJson.GetStr(FJson, 'last_error_message');
end;

function TTgWebhookInfoImpl.GetLastSynchronizationErrorDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'last_synchronization_error_date');
end;

function TTgWebhookInfoImpl.GetHasLastSynchronizationErrorDate: Boolean;
begin
  Result := TTgJson.Has(FJson, 'last_synchronization_error_date');
end;

function TTgWebhookInfoImpl.GetMaxConnections: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'max_connections');
end;

function TTgWebhookInfoImpl.GetHasMaxConnections: Boolean;
begin
  Result := TTgJson.Has(FJson, 'max_connections');
end;

function TTgWebhookInfoImpl.GetAllowedUpdates: TArray<string>;
begin
  Result := TTgDto.Strings(TTgJson.GetArr(FJson, 'allowed_updates'));
end;

{ TTgUserImpl }

function TTgUserImpl.GetId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'id');
end;

function TTgUserImpl.GetIsBot: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_bot');
end;

function TTgUserImpl.GetFirstName: string;
begin
  Result := TTgJson.GetStr(FJson, 'first_name');
end;

function TTgUserImpl.GetLastName: string;
begin
  Result := TTgJson.GetStr(FJson, 'last_name');
end;

function TTgUserImpl.GetUsername: string;
begin
  Result := TTgJson.GetStr(FJson, 'username');
end;

function TTgUserImpl.GetLanguageCode: string;
begin
  Result := TTgJson.GetStr(FJson, 'language_code');
end;

function TTgUserImpl.GetIsPremium: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_premium');
end;

function TTgUserImpl.GetAddedToAttachmentMenu: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'added_to_attachment_menu');
end;

function TTgUserImpl.GetCanJoinGroups: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_join_groups');
end;

function TTgUserImpl.GetHasCanJoinGroups: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_join_groups');
end;

function TTgUserImpl.GetCanReadAllGroupMessages: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_read_all_group_messages');
end;

function TTgUserImpl.GetHasCanReadAllGroupMessages: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_read_all_group_messages');
end;

function TTgUserImpl.GetSupportsGuestQueries: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'supports_guest_queries');
end;

function TTgUserImpl.GetHasSupportsGuestQueries: Boolean;
begin
  Result := TTgJson.Has(FJson, 'supports_guest_queries');
end;

function TTgUserImpl.GetSupportsInlineQueries: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'supports_inline_queries');
end;

function TTgUserImpl.GetHasSupportsInlineQueries: Boolean;
begin
  Result := TTgJson.Has(FJson, 'supports_inline_queries');
end;

function TTgUserImpl.GetCanConnectToBusiness: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_connect_to_business');
end;

function TTgUserImpl.GetHasCanConnectToBusiness: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_connect_to_business');
end;

function TTgUserImpl.GetHasMainWebApp: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'has_main_web_app');
end;

function TTgUserImpl.GetHasTopicsEnabled: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'has_topics_enabled');
end;

function TTgUserImpl.GetAllowsUsersToCreateTopics: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'allows_users_to_create_topics');
end;

function TTgUserImpl.GetHasAllowsUsersToCreateTopics: Boolean;
begin
  Result := TTgJson.Has(FJson, 'allows_users_to_create_topics');
end;

function TTgUserImpl.GetCanManageBots: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_manage_bots');
end;

function TTgUserImpl.GetHasCanManageBots: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_manage_bots');
end;

function TTgUserImpl.GetSupportsJoinRequestQueries: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'supports_join_request_queries');
end;

function TTgUserImpl.GetHasSupportsJoinRequestQueries: Boolean;
begin
  Result := TTgJson.Has(FJson, 'supports_join_request_queries');
end;

function TTgUserImpl.WithId(AValue: Int64): ITgUser;
begin
  SetInt64('id', AValue);
  Result := Self;
end;

function TTgUserImpl.WithIsBot(AValue: Boolean): ITgUser;
begin
  SetBool('is_bot', AValue);
  Result := Self;
end;

function TTgUserImpl.WithFirstName(const AValue: string): ITgUser;
begin
  SetStr('first_name', AValue);
  Result := Self;
end;

function TTgUserImpl.WithLastName(const AValue: string): ITgUser;
begin
  SetStr('last_name', AValue);
  Result := Self;
end;

function TTgUserImpl.WithUsername(const AValue: string): ITgUser;
begin
  SetStr('username', AValue);
  Result := Self;
end;

function TTgUserImpl.WithLanguageCode(const AValue: string): ITgUser;
begin
  SetStr('language_code', AValue);
  Result := Self;
end;

function TTgUserImpl.WithIsPremium(AValue: Boolean): ITgUser;
begin
  SetBool('is_premium', AValue);
  Result := Self;
end;

function TTgUserImpl.WithAddedToAttachmentMenu(AValue: Boolean): ITgUser;
begin
  SetBool('added_to_attachment_menu', AValue);
  Result := Self;
end;

function TTgUserImpl.WithCanJoinGroups(AValue: Boolean): ITgUser;
begin
  SetBool('can_join_groups', AValue);
  Result := Self;
end;

function TTgUserImpl.WithCanReadAllGroupMessages(AValue: Boolean): ITgUser;
begin
  SetBool('can_read_all_group_messages', AValue);
  Result := Self;
end;

function TTgUserImpl.WithSupportsGuestQueries(AValue: Boolean): ITgUser;
begin
  SetBool('supports_guest_queries', AValue);
  Result := Self;
end;

function TTgUserImpl.WithSupportsInlineQueries(AValue: Boolean): ITgUser;
begin
  SetBool('supports_inline_queries', AValue);
  Result := Self;
end;

function TTgUserImpl.WithCanConnectToBusiness(AValue: Boolean): ITgUser;
begin
  SetBool('can_connect_to_business', AValue);
  Result := Self;
end;

function TTgUserImpl.WithHasMainWebApp(AValue: Boolean): ITgUser;
begin
  SetBool('has_main_web_app', AValue);
  Result := Self;
end;

function TTgUserImpl.WithHasTopicsEnabled(AValue: Boolean): ITgUser;
begin
  SetBool('has_topics_enabled', AValue);
  Result := Self;
end;

function TTgUserImpl.WithAllowsUsersToCreateTopics(AValue: Boolean): ITgUser;
begin
  SetBool('allows_users_to_create_topics', AValue);
  Result := Self;
end;

function TTgUserImpl.WithCanManageBots(AValue: Boolean): ITgUser;
begin
  SetBool('can_manage_bots', AValue);
  Result := Self;
end;

function TTgUserImpl.WithSupportsJoinRequestQueries(AValue: Boolean): ITgUser;
begin
  SetBool('supports_join_request_queries', AValue);
  Result := Self;
end;

{ TTgChatImpl }

function TTgChatImpl.GetId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'id');
end;

function TTgChatImpl.GetChatType: string;
begin
  Result := TTgJson.GetStr(FJson, 'type');
end;

function TTgChatImpl.GetTitle: string;
begin
  Result := TTgJson.GetStr(FJson, 'title');
end;

function TTgChatImpl.GetUsername: string;
begin
  Result := TTgJson.GetStr(FJson, 'username');
end;

function TTgChatImpl.GetFirstName: string;
begin
  Result := TTgJson.GetStr(FJson, 'first_name');
end;

function TTgChatImpl.GetLastName: string;
begin
  Result := TTgJson.GetStr(FJson, 'last_name');
end;

function TTgChatImpl.GetIsForum: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_forum');
end;

function TTgChatImpl.GetIsDirectMessages: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_direct_messages');
end;

{ TTgChatFullInfoImpl }

function TTgChatFullInfoImpl.GetId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'id');
end;

function TTgChatFullInfoImpl.GetChatFullInfoType: string;
begin
  Result := TTgJson.GetStr(FJson, 'type');
end;

function TTgChatFullInfoImpl.GetTitle: string;
begin
  Result := TTgJson.GetStr(FJson, 'title');
end;

function TTgChatFullInfoImpl.GetUsername: string;
begin
  Result := TTgJson.GetStr(FJson, 'username');
end;

function TTgChatFullInfoImpl.GetFirstName: string;
begin
  Result := TTgJson.GetStr(FJson, 'first_name');
end;

function TTgChatFullInfoImpl.GetLastName: string;
begin
  Result := TTgJson.GetStr(FJson, 'last_name');
end;

function TTgChatFullInfoImpl.GetIsForum: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_forum');
end;

function TTgChatFullInfoImpl.GetIsDirectMessages: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_direct_messages');
end;

function TTgChatFullInfoImpl.GetAccentColorId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'accent_color_id');
end;

function TTgChatFullInfoImpl.GetMaxReactionCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'max_reaction_count');
end;

function TTgChatFullInfoImpl.GetPhoto: ITgChatPhoto;
begin
  Result := TgMakeChatPhoto(TTgJson.GetValue(FJson, 'photo'), JsonOwner);
end;

function TTgChatFullInfoImpl.GetActiveUsernames: TArray<string>;
begin
  Result := TTgDto.Strings(TTgJson.GetArr(FJson, 'active_usernames'));
end;

function TTgChatFullInfoImpl.GetBirthdate: ITgBirthdate;
begin
  Result := TgMakeBirthdate(TTgJson.GetValue(FJson, 'birthdate'), JsonOwner);
end;

function TTgChatFullInfoImpl.GetBusinessIntro: ITgBusinessIntro;
begin
  Result := TgMakeBusinessIntro(TTgJson.GetValue(FJson, 'business_intro'), JsonOwner);
end;

function TTgChatFullInfoImpl.GetBusinessLocation: ITgBusinessLocation;
begin
  Result := TgMakeBusinessLocation(TTgJson.GetValue(FJson, 'business_location'), JsonOwner);
end;

function TTgChatFullInfoImpl.GetBusinessOpeningHours: ITgBusinessOpeningHours;
begin
  Result := TgMakeBusinessOpeningHours(TTgJson.GetValue(FJson, 'business_opening_hours'), JsonOwner);
end;

function TTgChatFullInfoImpl.GetPersonalChat: ITgChat;
begin
  Result := TgMakeChat(TTgJson.GetValue(FJson, 'personal_chat'), JsonOwner);
end;

function TTgChatFullInfoImpl.GetParentChat: ITgChat;
begin
  Result := TgMakeChat(TTgJson.GetValue(FJson, 'parent_chat'), JsonOwner);
end;

function TTgChatFullInfoImpl.GetAvailableReactions: TArray<ITgReactionType>;
begin
  Result := TTgDto.Objects<ITgReactionType>(TTgJson.GetArr(FJson, 'available_reactions'), JsonOwner, TgMakeReactionType);
end;

function TTgChatFullInfoImpl.GetBackgroundCustomEmojiId: string;
begin
  Result := TTgJson.GetStr(FJson, 'background_custom_emoji_id');
end;

function TTgChatFullInfoImpl.GetProfileAccentColorId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'profile_accent_color_id');
end;

function TTgChatFullInfoImpl.GetHasProfileAccentColorId: Boolean;
begin
  Result := TTgJson.Has(FJson, 'profile_accent_color_id');
end;

function TTgChatFullInfoImpl.GetProfileBackgroundCustomEmojiId: string;
begin
  Result := TTgJson.GetStr(FJson, 'profile_background_custom_emoji_id');
end;

function TTgChatFullInfoImpl.GetEmojiStatusCustomEmojiId: string;
begin
  Result := TTgJson.GetStr(FJson, 'emoji_status_custom_emoji_id');
end;

function TTgChatFullInfoImpl.GetEmojiStatusExpirationDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'emoji_status_expiration_date');
end;

function TTgChatFullInfoImpl.GetHasEmojiStatusExpirationDate: Boolean;
begin
  Result := TTgJson.Has(FJson, 'emoji_status_expiration_date');
end;

function TTgChatFullInfoImpl.GetBio: string;
begin
  Result := TTgJson.GetStr(FJson, 'bio');
end;

function TTgChatFullInfoImpl.GetHasPrivateForwards: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'has_private_forwards');
end;

function TTgChatFullInfoImpl.GetHasRestrictedVoiceAndVideoMessages: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'has_restricted_voice_and_video_messages');
end;

function TTgChatFullInfoImpl.GetJoinToSendMessages: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'join_to_send_messages');
end;

function TTgChatFullInfoImpl.GetJoinByRequest: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'join_by_request');
end;

function TTgChatFullInfoImpl.GetDescription: string;
begin
  Result := TTgJson.GetStr(FJson, 'description');
end;

function TTgChatFullInfoImpl.GetInviteLink: string;
begin
  Result := TTgJson.GetStr(FJson, 'invite_link');
end;

function TTgChatFullInfoImpl.GetPinnedMessage: ITgMessage;
begin
  Result := TgMakeMessage(TTgJson.GetValue(FJson, 'pinned_message'), JsonOwner);
end;

function TTgChatFullInfoImpl.GetPermissions: ITgChatPermissions;
begin
  Result := TgMakeChatPermissions(TTgJson.GetValue(FJson, 'permissions'), JsonOwner);
end;

function TTgChatFullInfoImpl.GetAcceptedGiftTypes: ITgAcceptedGiftTypes;
begin
  Result := TgMakeAcceptedGiftTypes(TTgJson.GetValue(FJson, 'accepted_gift_types'), JsonOwner);
end;

function TTgChatFullInfoImpl.GetCanSendPaidMedia: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_send_paid_media');
end;

function TTgChatFullInfoImpl.GetSlowModeDelay: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'slow_mode_delay');
end;

function TTgChatFullInfoImpl.GetHasSlowModeDelay: Boolean;
begin
  Result := TTgJson.Has(FJson, 'slow_mode_delay');
end;

function TTgChatFullInfoImpl.GetUnrestrictBoostCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'unrestrict_boost_count');
end;

function TTgChatFullInfoImpl.GetHasUnrestrictBoostCount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'unrestrict_boost_count');
end;

function TTgChatFullInfoImpl.GetMessageAutoDeleteTime: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'message_auto_delete_time');
end;

function TTgChatFullInfoImpl.GetHasMessageAutoDeleteTime: Boolean;
begin
  Result := TTgJson.Has(FJson, 'message_auto_delete_time');
end;

function TTgChatFullInfoImpl.GetHasAggressiveAntiSpamEnabled: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'has_aggressive_anti_spam_enabled');
end;

function TTgChatFullInfoImpl.GetHasHiddenMembers: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'has_hidden_members');
end;

function TTgChatFullInfoImpl.GetHasProtectedContent: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'has_protected_content');
end;

function TTgChatFullInfoImpl.GetHasVisibleHistory: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'has_visible_history');
end;

function TTgChatFullInfoImpl.GetStickerSetName: string;
begin
  Result := TTgJson.GetStr(FJson, 'sticker_set_name');
end;

function TTgChatFullInfoImpl.GetCanSetStickerSet: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_set_sticker_set');
end;

function TTgChatFullInfoImpl.GetCustomEmojiStickerSetName: string;
begin
  Result := TTgJson.GetStr(FJson, 'custom_emoji_sticker_set_name');
end;

function TTgChatFullInfoImpl.GetLinkedChatId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'linked_chat_id');
end;

function TTgChatFullInfoImpl.GetHasLinkedChatId: Boolean;
begin
  Result := TTgJson.Has(FJson, 'linked_chat_id');
end;

function TTgChatFullInfoImpl.GetLocation: ITgChatLocation;
begin
  Result := TgMakeChatLocation(TTgJson.GetValue(FJson, 'location'), JsonOwner);
end;

function TTgChatFullInfoImpl.GetRating: ITgUserRating;
begin
  Result := TgMakeUserRating(TTgJson.GetValue(FJson, 'rating'), JsonOwner);
end;

function TTgChatFullInfoImpl.GetFirstProfileAudio: ITgAudio;
begin
  Result := TgMakeAudio(TTgJson.GetValue(FJson, 'first_profile_audio'), JsonOwner);
end;

function TTgChatFullInfoImpl.GetUniqueGiftColors: ITgUniqueGiftColors;
begin
  Result := TgMakeUniqueGiftColors(TTgJson.GetValue(FJson, 'unique_gift_colors'), JsonOwner);
end;

function TTgChatFullInfoImpl.GetPaidMessageStarCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'paid_message_star_count');
end;

function TTgChatFullInfoImpl.GetHasPaidMessageStarCount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'paid_message_star_count');
end;

function TTgChatFullInfoImpl.GetGuardBot: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'guard_bot'), JsonOwner);
end;

function TTgChatFullInfoImpl.GetCommunity: ITgCommunity;
begin
  Result := TgMakeCommunity(TTgJson.GetValue(FJson, 'community'), JsonOwner);
end;

{ TTgMaybeInaccessibleMessageImpl }

function TTgMaybeInaccessibleMessageImpl.GetKind: TTgMaybeInaccessibleMessageKind;
begin
  Result := TTgMaybeInaccessibleMessageKind.Unknown;
end;

function TTgMaybeInaccessibleMessageImpl.GetKindText: string;
begin
  Result := TTgJson.GetStr(FJson, 'date');
end;

function TTgMaybeInaccessibleMessageImpl.GetMessageId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'message_id');
end;

function TTgMaybeInaccessibleMessageImpl.GetDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'date');
end;

function TTgMaybeInaccessibleMessageImpl.GetChat: ITgChat;
begin
  Result := TgMakeChat(TTgJson.GetValue(FJson, 'chat'), JsonOwner);
end;

function TTgMaybeInaccessibleMessageImpl.AsMessage: ITgMessage;
begin
  if not Supports(Self, ITgMessage, Result) then
    Result := nil;
end;

function TTgMaybeInaccessibleMessageImpl.AsInaccessibleMessage: ITgInaccessibleMessage;
begin
  if not Supports(Self, ITgInaccessibleMessage, Result) then
    Result := nil;
end;

{ TTgMessageImpl }

function TTgMessageImpl.GetKind: TTgMaybeInaccessibleMessageKind;
begin
  Result := TTgMaybeInaccessibleMessageKind.Message;
end;

function TTgMessageImpl.GetMessageThreadId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'message_thread_id');
end;

function TTgMessageImpl.GetHasMessageThreadId: Boolean;
begin
  Result := TTgJson.Has(FJson, 'message_thread_id');
end;

function TTgMessageImpl.GetDirectMessagesTopic: ITgDirectMessagesTopic;
begin
  Result := TgMakeDirectMessagesTopic(TTgJson.GetValue(FJson, 'direct_messages_topic'), JsonOwner);
end;

function TTgMessageImpl.GetFrom: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'from'), JsonOwner);
end;

function TTgMessageImpl.GetSenderChat: ITgChat;
begin
  Result := TgMakeChat(TTgJson.GetValue(FJson, 'sender_chat'), JsonOwner);
end;

function TTgMessageImpl.GetSenderBoostCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'sender_boost_count');
end;

function TTgMessageImpl.GetHasSenderBoostCount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'sender_boost_count');
end;

function TTgMessageImpl.GetSenderBusinessBot: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'sender_business_bot'), JsonOwner);
end;

function TTgMessageImpl.GetSenderTag: string;
begin
  Result := TTgJson.GetStr(FJson, 'sender_tag');
end;

function TTgMessageImpl.GetReceiverUser: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'receiver_user'), JsonOwner);
end;

function TTgMessageImpl.GetEphemeralMessageId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'ephemeral_message_id');
end;

function TTgMessageImpl.GetHasEphemeralMessageId: Boolean;
begin
  Result := TTgJson.Has(FJson, 'ephemeral_message_id');
end;

function TTgMessageImpl.GetGuestQueryId: string;
begin
  Result := TTgJson.GetStr(FJson, 'guest_query_id');
end;

function TTgMessageImpl.GetBusinessConnectionId: string;
begin
  Result := TTgJson.GetStr(FJson, 'business_connection_id');
end;

function TTgMessageImpl.GetForwardOrigin: ITgMessageOrigin;
begin
  Result := TgMakeMessageOrigin(TTgJson.GetValue(FJson, 'forward_origin'), JsonOwner);
end;

function TTgMessageImpl.GetIsTopicMessage: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_topic_message');
end;

function TTgMessageImpl.GetIsAutomaticForward: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_automatic_forward');
end;

function TTgMessageImpl.GetReplyToMessage: ITgMessage;
begin
  Result := TgMakeMessage(TTgJson.GetValue(FJson, 'reply_to_message'), JsonOwner);
end;

function TTgMessageImpl.GetExternalReply: ITgExternalReplyInfo;
begin
  Result := TgMakeExternalReplyInfo(TTgJson.GetValue(FJson, 'external_reply'), JsonOwner);
end;

function TTgMessageImpl.GetQuote: ITgTextQuote;
begin
  Result := TgMakeTextQuote(TTgJson.GetValue(FJson, 'quote'), JsonOwner);
end;

function TTgMessageImpl.GetReplyToStory: ITgStory;
begin
  Result := TgMakeStory(TTgJson.GetValue(FJson, 'reply_to_story'), JsonOwner);
end;

function TTgMessageImpl.GetReplyToChecklistTaskId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'reply_to_checklist_task_id');
end;

function TTgMessageImpl.GetHasReplyToChecklistTaskId: Boolean;
begin
  Result := TTgJson.Has(FJson, 'reply_to_checklist_task_id');
end;

function TTgMessageImpl.GetReplyToPollOptionId: string;
begin
  Result := TTgJson.GetStr(FJson, 'reply_to_poll_option_id');
end;

function TTgMessageImpl.GetViaBot: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'via_bot'), JsonOwner);
end;

function TTgMessageImpl.GetGuestBotCallerUser: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'guest_bot_caller_user'), JsonOwner);
end;

function TTgMessageImpl.GetGuestBotCallerChat: ITgChat;
begin
  Result := TgMakeChat(TTgJson.GetValue(FJson, 'guest_bot_caller_chat'), JsonOwner);
end;

function TTgMessageImpl.GetEditDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'edit_date');
end;

function TTgMessageImpl.GetHasEditDate: Boolean;
begin
  Result := TTgJson.Has(FJson, 'edit_date');
end;

function TTgMessageImpl.GetHasProtectedContent: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'has_protected_content');
end;

function TTgMessageImpl.GetIsFromOffline: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_from_offline');
end;

function TTgMessageImpl.GetIsPaidPost: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_paid_post');
end;

function TTgMessageImpl.GetMediaGroupId: string;
begin
  Result := TTgJson.GetStr(FJson, 'media_group_id');
end;

function TTgMessageImpl.GetAuthorSignature: string;
begin
  Result := TTgJson.GetStr(FJson, 'author_signature');
end;

function TTgMessageImpl.GetPaidStarCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'paid_star_count');
end;

function TTgMessageImpl.GetHasPaidStarCount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'paid_star_count');
end;

function TTgMessageImpl.GetText: string;
begin
  Result := TTgJson.GetStr(FJson, 'text');
end;

function TTgMessageImpl.GetEntities: TArray<ITgMessageEntity>;
begin
  Result := TTgDto.Objects<ITgMessageEntity>(TTgJson.GetArr(FJson, 'entities'), JsonOwner, TgMakeMessageEntity);
end;

function TTgMessageImpl.GetLinkPreviewOptions: ITgLinkPreviewOptions;
begin
  Result := TgMakeLinkPreviewOptions(TTgJson.GetValue(FJson, 'link_preview_options'), JsonOwner);
end;

function TTgMessageImpl.GetSuggestedPostInfo: ITgSuggestedPostInfo;
begin
  Result := TgMakeSuggestedPostInfo(TTgJson.GetValue(FJson, 'suggested_post_info'), JsonOwner);
end;

function TTgMessageImpl.GetEffectId: string;
begin
  Result := TTgJson.GetStr(FJson, 'effect_id');
end;

function TTgMessageImpl.GetRichMessage: ITgRichMessage;
begin
  Result := TgMakeRichMessage(TTgJson.GetValue(FJson, 'rich_message'), JsonOwner);
end;

function TTgMessageImpl.GetAnimation: ITgAnimation;
begin
  Result := TgMakeAnimation(TTgJson.GetValue(FJson, 'animation'), JsonOwner);
end;

function TTgMessageImpl.GetAudio: ITgAudio;
begin
  Result := TgMakeAudio(TTgJson.GetValue(FJson, 'audio'), JsonOwner);
end;

function TTgMessageImpl.GetDocument: ITgDocument;
begin
  Result := TgMakeDocument(TTgJson.GetValue(FJson, 'document'), JsonOwner);
end;

function TTgMessageImpl.GetLivePhoto: ITgLivePhoto;
begin
  Result := TgMakeLivePhoto(TTgJson.GetValue(FJson, 'live_photo'), JsonOwner);
end;

function TTgMessageImpl.GetPaidMedia: ITgPaidMediaInfo;
begin
  Result := TgMakePaidMediaInfo(TTgJson.GetValue(FJson, 'paid_media'), JsonOwner);
end;

function TTgMessageImpl.GetPhoto: TArray<ITgPhotoSize>;
begin
  Result := TTgDto.Objects<ITgPhotoSize>(TTgJson.GetArr(FJson, 'photo'), JsonOwner, TgMakePhotoSize);
end;

function TTgMessageImpl.GetSticker: ITgSticker;
begin
  Result := TgMakeSticker(TTgJson.GetValue(FJson, 'sticker'), JsonOwner);
end;

function TTgMessageImpl.GetStory: ITgStory;
begin
  Result := TgMakeStory(TTgJson.GetValue(FJson, 'story'), JsonOwner);
end;

function TTgMessageImpl.GetVideo: ITgVideo;
begin
  Result := TgMakeVideo(TTgJson.GetValue(FJson, 'video'), JsonOwner);
end;

function TTgMessageImpl.GetVideoNote: ITgVideoNote;
begin
  Result := TgMakeVideoNote(TTgJson.GetValue(FJson, 'video_note'), JsonOwner);
end;

function TTgMessageImpl.GetVoice: ITgVoice;
begin
  Result := TgMakeVoice(TTgJson.GetValue(FJson, 'voice'), JsonOwner);
end;

function TTgMessageImpl.GetCaption: string;
begin
  Result := TTgJson.GetStr(FJson, 'caption');
end;

function TTgMessageImpl.GetCaptionEntities: TArray<ITgMessageEntity>;
begin
  Result := TTgDto.Objects<ITgMessageEntity>(TTgJson.GetArr(FJson, 'caption_entities'), JsonOwner, TgMakeMessageEntity);
end;

function TTgMessageImpl.GetShowCaptionAboveMedia: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'show_caption_above_media');
end;

function TTgMessageImpl.GetHasMediaSpoiler: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'has_media_spoiler');
end;

function TTgMessageImpl.GetChecklist: ITgChecklist;
begin
  Result := TgMakeChecklist(TTgJson.GetValue(FJson, 'checklist'), JsonOwner);
end;

function TTgMessageImpl.GetContact: ITgContact;
begin
  Result := TgMakeContact(TTgJson.GetValue(FJson, 'contact'), JsonOwner);
end;

function TTgMessageImpl.GetDice: ITgDice;
begin
  Result := TgMakeDice(TTgJson.GetValue(FJson, 'dice'), JsonOwner);
end;

function TTgMessageImpl.GetGame: ITgGame;
begin
  Result := TgMakeGame(TTgJson.GetValue(FJson, 'game'), JsonOwner);
end;

function TTgMessageImpl.GetPoll: ITgPoll;
begin
  Result := TgMakePoll(TTgJson.GetValue(FJson, 'poll'), JsonOwner);
end;

function TTgMessageImpl.GetVenue: ITgVenue;
begin
  Result := TgMakeVenue(TTgJson.GetValue(FJson, 'venue'), JsonOwner);
end;

function TTgMessageImpl.GetLocation: ITgLocation;
begin
  Result := TgMakeLocation(TTgJson.GetValue(FJson, 'location'), JsonOwner);
end;

function TTgMessageImpl.GetNewChatMembers: TArray<ITgUser>;
begin
  Result := TTgDto.Objects<ITgUser>(TTgJson.GetArr(FJson, 'new_chat_members'), JsonOwner, TgMakeUser);
end;

function TTgMessageImpl.GetLeftChatMember: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'left_chat_member'), JsonOwner);
end;

function TTgMessageImpl.GetChatOwnerLeft: ITgChatOwnerLeft;
begin
  Result := TgMakeChatOwnerLeft(TTgJson.GetValue(FJson, 'chat_owner_left'), JsonOwner);
end;

function TTgMessageImpl.GetChatOwnerChanged: ITgChatOwnerChanged;
begin
  Result := TgMakeChatOwnerChanged(TTgJson.GetValue(FJson, 'chat_owner_changed'), JsonOwner);
end;

function TTgMessageImpl.GetNewChatTitle: string;
begin
  Result := TTgJson.GetStr(FJson, 'new_chat_title');
end;

function TTgMessageImpl.GetNewChatPhoto: TArray<ITgPhotoSize>;
begin
  Result := TTgDto.Objects<ITgPhotoSize>(TTgJson.GetArr(FJson, 'new_chat_photo'), JsonOwner, TgMakePhotoSize);
end;

function TTgMessageImpl.GetDeleteChatPhoto: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'delete_chat_photo');
end;

function TTgMessageImpl.GetGroupChatCreated: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'group_chat_created');
end;

function TTgMessageImpl.GetSupergroupChatCreated: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'supergroup_chat_created');
end;

function TTgMessageImpl.GetChannelChatCreated: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'channel_chat_created');
end;

function TTgMessageImpl.GetMessageAutoDeleteTimerChanged: ITgMessageAutoDeleteTimerChanged;
begin
  Result := TgMakeMessageAutoDeleteTimerChanged(TTgJson.GetValue(FJson, 'message_auto_delete_timer_changed'), JsonOwner);
end;

function TTgMessageImpl.GetMigrateToChatId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'migrate_to_chat_id');
end;

function TTgMessageImpl.GetHasMigrateToChatId: Boolean;
begin
  Result := TTgJson.Has(FJson, 'migrate_to_chat_id');
end;

function TTgMessageImpl.GetMigrateFromChatId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'migrate_from_chat_id');
end;

function TTgMessageImpl.GetHasMigrateFromChatId: Boolean;
begin
  Result := TTgJson.Has(FJson, 'migrate_from_chat_id');
end;

function TTgMessageImpl.GetPinnedMessage: ITgMaybeInaccessibleMessage;
begin
  Result := TgMakeMaybeInaccessibleMessage(TTgJson.GetValue(FJson, 'pinned_message'), JsonOwner);
end;

function TTgMessageImpl.GetInvoice: ITgInvoice;
begin
  Result := TgMakeInvoice(TTgJson.GetValue(FJson, 'invoice'), JsonOwner);
end;

function TTgMessageImpl.GetSuccessfulPayment: ITgSuccessfulPayment;
begin
  Result := TgMakeSuccessfulPayment(TTgJson.GetValue(FJson, 'successful_payment'), JsonOwner);
end;

function TTgMessageImpl.GetRefundedPayment: ITgRefundedPayment;
begin
  Result := TgMakeRefundedPayment(TTgJson.GetValue(FJson, 'refunded_payment'), JsonOwner);
end;

function TTgMessageImpl.GetUsersShared: ITgUsersShared;
begin
  Result := TgMakeUsersShared(TTgJson.GetValue(FJson, 'users_shared'), JsonOwner);
end;

function TTgMessageImpl.GetChatShared: ITgChatShared;
begin
  Result := TgMakeChatShared(TTgJson.GetValue(FJson, 'chat_shared'), JsonOwner);
end;

function TTgMessageImpl.GetGift: ITgGiftInfo;
begin
  Result := TgMakeGiftInfo(TTgJson.GetValue(FJson, 'gift'), JsonOwner);
end;

function TTgMessageImpl.GetUniqueGift: ITgUniqueGiftInfo;
begin
  Result := TgMakeUniqueGiftInfo(TTgJson.GetValue(FJson, 'unique_gift'), JsonOwner);
end;

function TTgMessageImpl.GetGiftUpgradeSent: ITgGiftInfo;
begin
  Result := TgMakeGiftInfo(TTgJson.GetValue(FJson, 'gift_upgrade_sent'), JsonOwner);
end;

function TTgMessageImpl.GetConnectedWebsite: string;
begin
  Result := TTgJson.GetStr(FJson, 'connected_website');
end;

function TTgMessageImpl.GetWriteAccessAllowed: ITgWriteAccessAllowed;
begin
  Result := TgMakeWriteAccessAllowed(TTgJson.GetValue(FJson, 'write_access_allowed'), JsonOwner);
end;

function TTgMessageImpl.GetPassportData: ITgPassportData;
begin
  Result := TgMakePassportData(TTgJson.GetValue(FJson, 'passport_data'), JsonOwner);
end;

function TTgMessageImpl.GetProximityAlertTriggered: ITgProximityAlertTriggered;
begin
  Result := TgMakeProximityAlertTriggered(TTgJson.GetValue(FJson, 'proximity_alert_triggered'), JsonOwner);
end;

function TTgMessageImpl.GetBoostAdded: ITgChatBoostAdded;
begin
  Result := TgMakeChatBoostAdded(TTgJson.GetValue(FJson, 'boost_added'), JsonOwner);
end;

function TTgMessageImpl.GetChatBackgroundSet: ITgChatBackground;
begin
  Result := TgMakeChatBackground(TTgJson.GetValue(FJson, 'chat_background_set'), JsonOwner);
end;

function TTgMessageImpl.GetChecklistTasksDone: ITgChecklistTasksDone;
begin
  Result := TgMakeChecklistTasksDone(TTgJson.GetValue(FJson, 'checklist_tasks_done'), JsonOwner);
end;

function TTgMessageImpl.GetChecklistTasksAdded: ITgChecklistTasksAdded;
begin
  Result := TgMakeChecklistTasksAdded(TTgJson.GetValue(FJson, 'checklist_tasks_added'), JsonOwner);
end;

function TTgMessageImpl.GetCommunityChatAdded: ITgCommunityChatAdded;
begin
  Result := TgMakeCommunityChatAdded(TTgJson.GetValue(FJson, 'community_chat_added'), JsonOwner);
end;

function TTgMessageImpl.GetCommunityChatJoined: ITgCommunityChatJoined;
begin
  Result := TgMakeCommunityChatJoined(TTgJson.GetValue(FJson, 'community_chat_joined'), JsonOwner);
end;

function TTgMessageImpl.GetCommunityChatRemoved: ITgCommunityChatRemoved;
begin
  Result := TgMakeCommunityChatRemoved(TTgJson.GetValue(FJson, 'community_chat_removed'), JsonOwner);
end;

function TTgMessageImpl.GetDirectMessagePriceChanged: ITgDirectMessagePriceChanged;
begin
  Result := TgMakeDirectMessagePriceChanged(TTgJson.GetValue(FJson, 'direct_message_price_changed'), JsonOwner);
end;

function TTgMessageImpl.GetForumTopicCreated: ITgForumTopicCreated;
begin
  Result := TgMakeForumTopicCreated(TTgJson.GetValue(FJson, 'forum_topic_created'), JsonOwner);
end;

function TTgMessageImpl.GetForumTopicEdited: ITgForumTopicEdited;
begin
  Result := TgMakeForumTopicEdited(TTgJson.GetValue(FJson, 'forum_topic_edited'), JsonOwner);
end;

function TTgMessageImpl.GetForumTopicClosed: ITgForumTopicClosed;
begin
  Result := TgMakeForumTopicClosed(TTgJson.GetValue(FJson, 'forum_topic_closed'), JsonOwner);
end;

function TTgMessageImpl.GetForumTopicReopened: ITgForumTopicReopened;
begin
  Result := TgMakeForumTopicReopened(TTgJson.GetValue(FJson, 'forum_topic_reopened'), JsonOwner);
end;

function TTgMessageImpl.GetGeneralForumTopicHidden: ITgGeneralForumTopicHidden;
begin
  Result := TgMakeGeneralForumTopicHidden(TTgJson.GetValue(FJson, 'general_forum_topic_hidden'), JsonOwner);
end;

function TTgMessageImpl.GetGeneralForumTopicUnhidden: ITgGeneralForumTopicUnhidden;
begin
  Result := TgMakeGeneralForumTopicUnhidden(TTgJson.GetValue(FJson, 'general_forum_topic_unhidden'), JsonOwner);
end;

function TTgMessageImpl.GetGiveawayCreated: ITgGiveawayCreated;
begin
  Result := TgMakeGiveawayCreated(TTgJson.GetValue(FJson, 'giveaway_created'), JsonOwner);
end;

function TTgMessageImpl.GetGiveaway: ITgGiveaway;
begin
  Result := TgMakeGiveaway(TTgJson.GetValue(FJson, 'giveaway'), JsonOwner);
end;

function TTgMessageImpl.GetGiveawayWinners: ITgGiveawayWinners;
begin
  Result := TgMakeGiveawayWinners(TTgJson.GetValue(FJson, 'giveaway_winners'), JsonOwner);
end;

function TTgMessageImpl.GetGiveawayCompleted: ITgGiveawayCompleted;
begin
  Result := TgMakeGiveawayCompleted(TTgJson.GetValue(FJson, 'giveaway_completed'), JsonOwner);
end;

function TTgMessageImpl.GetManagedBotCreated: ITgManagedBotCreated;
begin
  Result := TgMakeManagedBotCreated(TTgJson.GetValue(FJson, 'managed_bot_created'), JsonOwner);
end;

function TTgMessageImpl.GetPaidMessagePriceChanged: ITgPaidMessagePriceChanged;
begin
  Result := TgMakePaidMessagePriceChanged(TTgJson.GetValue(FJson, 'paid_message_price_changed'), JsonOwner);
end;

function TTgMessageImpl.GetPollOptionAdded: ITgPollOptionAdded;
begin
  Result := TgMakePollOptionAdded(TTgJson.GetValue(FJson, 'poll_option_added'), JsonOwner);
end;

function TTgMessageImpl.GetPollOptionDeleted: ITgPollOptionDeleted;
begin
  Result := TgMakePollOptionDeleted(TTgJson.GetValue(FJson, 'poll_option_deleted'), JsonOwner);
end;

function TTgMessageImpl.GetSuggestedPostApproved: ITgSuggestedPostApproved;
begin
  Result := TgMakeSuggestedPostApproved(TTgJson.GetValue(FJson, 'suggested_post_approved'), JsonOwner);
end;

function TTgMessageImpl.GetSuggestedPostApprovalFailed: ITgSuggestedPostApprovalFailed;
begin
  Result := TgMakeSuggestedPostApprovalFailed(TTgJson.GetValue(FJson, 'suggested_post_approval_failed'), JsonOwner);
end;

function TTgMessageImpl.GetSuggestedPostDeclined: ITgSuggestedPostDeclined;
begin
  Result := TgMakeSuggestedPostDeclined(TTgJson.GetValue(FJson, 'suggested_post_declined'), JsonOwner);
end;

function TTgMessageImpl.GetSuggestedPostPaid: ITgSuggestedPostPaid;
begin
  Result := TgMakeSuggestedPostPaid(TTgJson.GetValue(FJson, 'suggested_post_paid'), JsonOwner);
end;

function TTgMessageImpl.GetSuggestedPostRefunded: ITgSuggestedPostRefunded;
begin
  Result := TgMakeSuggestedPostRefunded(TTgJson.GetValue(FJson, 'suggested_post_refunded'), JsonOwner);
end;

function TTgMessageImpl.GetVideoChatScheduled: ITgVideoChatScheduled;
begin
  Result := TgMakeVideoChatScheduled(TTgJson.GetValue(FJson, 'video_chat_scheduled'), JsonOwner);
end;

function TTgMessageImpl.GetVideoChatStarted: ITgVideoChatStarted;
begin
  Result := TgMakeVideoChatStarted(TTgJson.GetValue(FJson, 'video_chat_started'), JsonOwner);
end;

function TTgMessageImpl.GetVideoChatEnded: ITgVideoChatEnded;
begin
  Result := TgMakeVideoChatEnded(TTgJson.GetValue(FJson, 'video_chat_ended'), JsonOwner);
end;

function TTgMessageImpl.GetVideoChatParticipantsInvited: ITgVideoChatParticipantsInvited;
begin
  Result := TgMakeVideoChatParticipantsInvited(TTgJson.GetValue(FJson, 'video_chat_participants_invited'), JsonOwner);
end;

function TTgMessageImpl.GetWebAppData: ITgWebAppData;
begin
  Result := TgMakeWebAppData(TTgJson.GetValue(FJson, 'web_app_data'), JsonOwner);
end;

function TTgMessageImpl.GetReplyMarkup: ITgInlineKeyboardMarkup;
begin
  Result := TgMakeInlineKeyboardMarkup(TTgJson.GetValue(FJson, 'reply_markup'), JsonOwner);
end;

{ TTgMessageIdImpl }

function TTgMessageIdImpl.GetMessageId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'message_id');
end;

{ TTgInaccessibleMessageImpl }

function TTgInaccessibleMessageImpl.GetKind: TTgMaybeInaccessibleMessageKind;
begin
  Result := TTgMaybeInaccessibleMessageKind.InaccessibleMessage;
end;

{ TTgMessageEntityImpl }

function TTgMessageEntityImpl.GetMessageEntityType: string;
begin
  Result := TTgJson.GetStr(FJson, 'type');
end;

function TTgMessageEntityImpl.GetOffset: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'offset');
end;

function TTgMessageEntityImpl.GetLength: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'length');
end;

function TTgMessageEntityImpl.GetUrl: string;
begin
  Result := TTgJson.GetStr(FJson, 'url');
end;

function TTgMessageEntityImpl.GetUser: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'user'), JsonOwner);
end;

function TTgMessageEntityImpl.GetLanguage: string;
begin
  Result := TTgJson.GetStr(FJson, 'language');
end;

function TTgMessageEntityImpl.GetCustomEmojiId: string;
begin
  Result := TTgJson.GetStr(FJson, 'custom_emoji_id');
end;

function TTgMessageEntityImpl.GetUnixTime: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'unix_time');
end;

function TTgMessageEntityImpl.GetHasUnixTime: Boolean;
begin
  Result := TTgJson.Has(FJson, 'unix_time');
end;

function TTgMessageEntityImpl.GetDateTimeFormat: string;
begin
  Result := TTgJson.GetStr(FJson, 'date_time_format');
end;

function TTgMessageEntityImpl.WithMessageEntityType(const AValue: string): ITgMessageEntity;
begin
  SetStr('type', AValue);
  Result := Self;
end;

function TTgMessageEntityImpl.WithOffset(AValue: Integer): ITgMessageEntity;
begin
  SetInt('offset', AValue);
  Result := Self;
end;

function TTgMessageEntityImpl.WithLength(AValue: Integer): ITgMessageEntity;
begin
  SetInt('length', AValue);
  Result := Self;
end;

function TTgMessageEntityImpl.WithUrl(const AValue: string): ITgMessageEntity;
begin
  SetStr('url', AValue);
  Result := Self;
end;

function TTgMessageEntityImpl.WithUser(const AValue: ITgUser): ITgMessageEntity;
begin
  SetObject('user', AValue);
  Result := Self;
end;

function TTgMessageEntityImpl.WithLanguage(const AValue: string): ITgMessageEntity;
begin
  SetStr('language', AValue);
  Result := Self;
end;

function TTgMessageEntityImpl.WithCustomEmojiId(const AValue: string): ITgMessageEntity;
begin
  SetStr('custom_emoji_id', AValue);
  Result := Self;
end;

function TTgMessageEntityImpl.WithUnixTime(AValue: Integer): ITgMessageEntity;
begin
  SetInt('unix_time', AValue);
  Result := Self;
end;

function TTgMessageEntityImpl.WithDateTimeFormat(const AValue: string): ITgMessageEntity;
begin
  SetStr('date_time_format', AValue);
  Result := Self;
end;

{ TTgTextQuoteImpl }

function TTgTextQuoteImpl.GetText: string;
begin
  Result := TTgJson.GetStr(FJson, 'text');
end;

function TTgTextQuoteImpl.GetEntities: TArray<ITgMessageEntity>;
begin
  Result := TTgDto.Objects<ITgMessageEntity>(TTgJson.GetArr(FJson, 'entities'), JsonOwner, TgMakeMessageEntity);
end;

function TTgTextQuoteImpl.GetPosition: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'position');
end;

function TTgTextQuoteImpl.GetIsManual: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_manual');
end;

{ TTgExternalReplyInfoImpl }

function TTgExternalReplyInfoImpl.GetOrigin: ITgMessageOrigin;
begin
  Result := TgMakeMessageOrigin(TTgJson.GetValue(FJson, 'origin'), JsonOwner);
end;

function TTgExternalReplyInfoImpl.GetChat: ITgChat;
begin
  Result := TgMakeChat(TTgJson.GetValue(FJson, 'chat'), JsonOwner);
end;

function TTgExternalReplyInfoImpl.GetMessageId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'message_id');
end;

function TTgExternalReplyInfoImpl.GetHasMessageId: Boolean;
begin
  Result := TTgJson.Has(FJson, 'message_id');
end;

function TTgExternalReplyInfoImpl.GetLinkPreviewOptions: ITgLinkPreviewOptions;
begin
  Result := TgMakeLinkPreviewOptions(TTgJson.GetValue(FJson, 'link_preview_options'), JsonOwner);
end;

function TTgExternalReplyInfoImpl.GetAnimation: ITgAnimation;
begin
  Result := TgMakeAnimation(TTgJson.GetValue(FJson, 'animation'), JsonOwner);
end;

function TTgExternalReplyInfoImpl.GetAudio: ITgAudio;
begin
  Result := TgMakeAudio(TTgJson.GetValue(FJson, 'audio'), JsonOwner);
end;

function TTgExternalReplyInfoImpl.GetDocument: ITgDocument;
begin
  Result := TgMakeDocument(TTgJson.GetValue(FJson, 'document'), JsonOwner);
end;

function TTgExternalReplyInfoImpl.GetLivePhoto: ITgLivePhoto;
begin
  Result := TgMakeLivePhoto(TTgJson.GetValue(FJson, 'live_photo'), JsonOwner);
end;

function TTgExternalReplyInfoImpl.GetPaidMedia: ITgPaidMediaInfo;
begin
  Result := TgMakePaidMediaInfo(TTgJson.GetValue(FJson, 'paid_media'), JsonOwner);
end;

function TTgExternalReplyInfoImpl.GetPhoto: TArray<ITgPhotoSize>;
begin
  Result := TTgDto.Objects<ITgPhotoSize>(TTgJson.GetArr(FJson, 'photo'), JsonOwner, TgMakePhotoSize);
end;

function TTgExternalReplyInfoImpl.GetSticker: ITgSticker;
begin
  Result := TgMakeSticker(TTgJson.GetValue(FJson, 'sticker'), JsonOwner);
end;

function TTgExternalReplyInfoImpl.GetStory: ITgStory;
begin
  Result := TgMakeStory(TTgJson.GetValue(FJson, 'story'), JsonOwner);
end;

function TTgExternalReplyInfoImpl.GetVideo: ITgVideo;
begin
  Result := TgMakeVideo(TTgJson.GetValue(FJson, 'video'), JsonOwner);
end;

function TTgExternalReplyInfoImpl.GetVideoNote: ITgVideoNote;
begin
  Result := TgMakeVideoNote(TTgJson.GetValue(FJson, 'video_note'), JsonOwner);
end;

function TTgExternalReplyInfoImpl.GetVoice: ITgVoice;
begin
  Result := TgMakeVoice(TTgJson.GetValue(FJson, 'voice'), JsonOwner);
end;

function TTgExternalReplyInfoImpl.GetHasMediaSpoiler: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'has_media_spoiler');
end;

function TTgExternalReplyInfoImpl.GetChecklist: ITgChecklist;
begin
  Result := TgMakeChecklist(TTgJson.GetValue(FJson, 'checklist'), JsonOwner);
end;

function TTgExternalReplyInfoImpl.GetContact: ITgContact;
begin
  Result := TgMakeContact(TTgJson.GetValue(FJson, 'contact'), JsonOwner);
end;

function TTgExternalReplyInfoImpl.GetDice: ITgDice;
begin
  Result := TgMakeDice(TTgJson.GetValue(FJson, 'dice'), JsonOwner);
end;

function TTgExternalReplyInfoImpl.GetGame: ITgGame;
begin
  Result := TgMakeGame(TTgJson.GetValue(FJson, 'game'), JsonOwner);
end;

function TTgExternalReplyInfoImpl.GetGiveaway: ITgGiveaway;
begin
  Result := TgMakeGiveaway(TTgJson.GetValue(FJson, 'giveaway'), JsonOwner);
end;

function TTgExternalReplyInfoImpl.GetGiveawayWinners: ITgGiveawayWinners;
begin
  Result := TgMakeGiveawayWinners(TTgJson.GetValue(FJson, 'giveaway_winners'), JsonOwner);
end;

function TTgExternalReplyInfoImpl.GetInvoice: ITgInvoice;
begin
  Result := TgMakeInvoice(TTgJson.GetValue(FJson, 'invoice'), JsonOwner);
end;

function TTgExternalReplyInfoImpl.GetLocation: ITgLocation;
begin
  Result := TgMakeLocation(TTgJson.GetValue(FJson, 'location'), JsonOwner);
end;

function TTgExternalReplyInfoImpl.GetPoll: ITgPoll;
begin
  Result := TgMakePoll(TTgJson.GetValue(FJson, 'poll'), JsonOwner);
end;

function TTgExternalReplyInfoImpl.GetVenue: ITgVenue;
begin
  Result := TgMakeVenue(TTgJson.GetValue(FJson, 'venue'), JsonOwner);
end;

{ TTgReplyParametersImpl }

function TTgReplyParametersImpl.WithMessageId(AValue: Int64): ITgReplyParameters;
begin
  SetInt64('message_id', AValue);
  Result := Self;
end;

function TTgReplyParametersImpl.WithChatId(const AValue: TTgChatId): ITgReplyParameters;
begin
  SetChatId('chat_id', AValue);
  Result := Self;
end;

function TTgReplyParametersImpl.WithEphemeralMessageId(AValue: Int64): ITgReplyParameters;
begin
  SetInt64('ephemeral_message_id', AValue);
  Result := Self;
end;

function TTgReplyParametersImpl.WithAllowSendingWithoutReply(AValue: Boolean): ITgReplyParameters;
begin
  SetBool('allow_sending_without_reply', AValue);
  Result := Self;
end;

function TTgReplyParametersImpl.WithQuote(const AValue: string): ITgReplyParameters;
begin
  SetStr('quote', AValue);
  Result := Self;
end;

function TTgReplyParametersImpl.WithQuoteParseMode(const AValue: string): ITgReplyParameters;
begin
  SetStr('quote_parse_mode', AValue);
  Result := Self;
end;

function TTgReplyParametersImpl.WithQuoteEntities(const AValue: array of ITgMessageEntity): ITgReplyParameters;
begin
  SetObjects('quote_entities', TTgDto.ToIntf<ITgMessageEntity>(AValue));
  Result := Self;
end;

function TTgReplyParametersImpl.WithQuotePosition(AValue: Integer): ITgReplyParameters;
begin
  SetInt('quote_position', AValue);
  Result := Self;
end;

function TTgReplyParametersImpl.WithChecklistTaskId(AValue: Int64): ITgReplyParameters;
begin
  SetInt64('checklist_task_id', AValue);
  Result := Self;
end;

function TTgReplyParametersImpl.WithPollOptionId(const AValue: string): ITgReplyParameters;
begin
  SetStr('poll_option_id', AValue);
  Result := Self;
end;

{ TTgEphemeralMessageParametersImpl }

function TTgEphemeralMessageParametersImpl.WithReceiverUserId(AValue: Int64): ITgEphemeralMessageParameters;
begin
  SetInt64('receiver_user_id', AValue);
  Result := Self;
end;

function TTgEphemeralMessageParametersImpl.WithCallbackQueryId(const AValue: string): ITgEphemeralMessageParameters;
begin
  SetStr('callback_query_id', AValue);
  Result := Self;
end;

function TTgEphemeralMessageParametersImpl.WithReplaceCallbackQueryMessage(AValue: Boolean): ITgEphemeralMessageParameters;
begin
  SetBool('replace_callback_query_message', AValue);
  Result := Self;
end;

{ TTgMessageOriginImpl }

function TTgMessageOriginImpl.GetKind: TTgMessageOriginKind;
begin
  Result := TTgMessageOriginKind.Unknown;
end;

function TTgMessageOriginImpl.GetKindText: string;
begin
  Result := TTgJson.GetStr(FJson, 'type');
end;

function TTgMessageOriginImpl.GetDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'date');
end;

function TTgMessageOriginImpl.AsUser: ITgMessageOriginUser;
begin
  if not Supports(Self, ITgMessageOriginUser, Result) then
    Result := nil;
end;

function TTgMessageOriginImpl.AsHiddenUser: ITgMessageOriginHiddenUser;
begin
  if not Supports(Self, ITgMessageOriginHiddenUser, Result) then
    Result := nil;
end;

function TTgMessageOriginImpl.AsChat: ITgMessageOriginChat;
begin
  if not Supports(Self, ITgMessageOriginChat, Result) then
    Result := nil;
end;

function TTgMessageOriginImpl.AsChannel: ITgMessageOriginChannel;
begin
  if not Supports(Self, ITgMessageOriginChannel, Result) then
    Result := nil;
end;

{ TTgMessageOriginUserImpl }

function TTgMessageOriginUserImpl.GetKind: TTgMessageOriginKind;
begin
  Result := TTgMessageOriginKind.User;
end;

function TTgMessageOriginUserImpl.GetSenderUser: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'sender_user'), JsonOwner);
end;

{ TTgMessageOriginHiddenUserImpl }

function TTgMessageOriginHiddenUserImpl.GetKind: TTgMessageOriginKind;
begin
  Result := TTgMessageOriginKind.HiddenUser;
end;

function TTgMessageOriginHiddenUserImpl.GetSenderUserName: string;
begin
  Result := TTgJson.GetStr(FJson, 'sender_user_name');
end;

{ TTgMessageOriginChatImpl }

function TTgMessageOriginChatImpl.GetKind: TTgMessageOriginKind;
begin
  Result := TTgMessageOriginKind.Chat;
end;

function TTgMessageOriginChatImpl.GetSenderChat: ITgChat;
begin
  Result := TgMakeChat(TTgJson.GetValue(FJson, 'sender_chat'), JsonOwner);
end;

function TTgMessageOriginChatImpl.GetAuthorSignature: string;
begin
  Result := TTgJson.GetStr(FJson, 'author_signature');
end;

{ TTgMessageOriginChannelImpl }

function TTgMessageOriginChannelImpl.GetKind: TTgMessageOriginKind;
begin
  Result := TTgMessageOriginKind.Channel;
end;

function TTgMessageOriginChannelImpl.GetChat: ITgChat;
begin
  Result := TgMakeChat(TTgJson.GetValue(FJson, 'chat'), JsonOwner);
end;

function TTgMessageOriginChannelImpl.GetMessageId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'message_id');
end;

function TTgMessageOriginChannelImpl.GetAuthorSignature: string;
begin
  Result := TTgJson.GetStr(FJson, 'author_signature');
end;

{ TTgPhotoSizeImpl }

function TTgPhotoSizeImpl.GetFileId: string;
begin
  Result := TTgJson.GetStr(FJson, 'file_id');
end;

function TTgPhotoSizeImpl.GetFileUniqueId: string;
begin
  Result := TTgJson.GetStr(FJson, 'file_unique_id');
end;

function TTgPhotoSizeImpl.GetWidth: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'width');
end;

function TTgPhotoSizeImpl.GetHeight: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'height');
end;

function TTgPhotoSizeImpl.GetFileSize: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'file_size');
end;

function TTgPhotoSizeImpl.GetHasFileSize: Boolean;
begin
  Result := TTgJson.Has(FJson, 'file_size');
end;

{ TTgAnimationImpl }

function TTgAnimationImpl.GetFileId: string;
begin
  Result := TTgJson.GetStr(FJson, 'file_id');
end;

function TTgAnimationImpl.GetFileUniqueId: string;
begin
  Result := TTgJson.GetStr(FJson, 'file_unique_id');
end;

function TTgAnimationImpl.GetWidth: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'width');
end;

function TTgAnimationImpl.GetHeight: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'height');
end;

function TTgAnimationImpl.GetDuration: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'duration');
end;

function TTgAnimationImpl.GetThumbnail: ITgPhotoSize;
begin
  Result := TgMakePhotoSize(TTgJson.GetValue(FJson, 'thumbnail'), JsonOwner);
end;

function TTgAnimationImpl.GetFileName: string;
begin
  Result := TTgJson.GetStr(FJson, 'file_name');
end;

function TTgAnimationImpl.GetMimeType: string;
begin
  Result := TTgJson.GetStr(FJson, 'mime_type');
end;

function TTgAnimationImpl.GetFileSize: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'file_size');
end;

function TTgAnimationImpl.GetHasFileSize: Boolean;
begin
  Result := TTgJson.Has(FJson, 'file_size');
end;

{ TTgAudioImpl }

function TTgAudioImpl.GetFileId: string;
begin
  Result := TTgJson.GetStr(FJson, 'file_id');
end;

function TTgAudioImpl.GetFileUniqueId: string;
begin
  Result := TTgJson.GetStr(FJson, 'file_unique_id');
end;

function TTgAudioImpl.GetDuration: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'duration');
end;

function TTgAudioImpl.GetPerformer: string;
begin
  Result := TTgJson.GetStr(FJson, 'performer');
end;

function TTgAudioImpl.GetTitle: string;
begin
  Result := TTgJson.GetStr(FJson, 'title');
end;

function TTgAudioImpl.GetFileName: string;
begin
  Result := TTgJson.GetStr(FJson, 'file_name');
end;

function TTgAudioImpl.GetMimeType: string;
begin
  Result := TTgJson.GetStr(FJson, 'mime_type');
end;

function TTgAudioImpl.GetFileSize: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'file_size');
end;

function TTgAudioImpl.GetHasFileSize: Boolean;
begin
  Result := TTgJson.Has(FJson, 'file_size');
end;

function TTgAudioImpl.GetThumbnail: ITgPhotoSize;
begin
  Result := TgMakePhotoSize(TTgJson.GetValue(FJson, 'thumbnail'), JsonOwner);
end;

{ TTgDocumentImpl }

function TTgDocumentImpl.GetFileId: string;
begin
  Result := TTgJson.GetStr(FJson, 'file_id');
end;

function TTgDocumentImpl.GetFileUniqueId: string;
begin
  Result := TTgJson.GetStr(FJson, 'file_unique_id');
end;

function TTgDocumentImpl.GetThumbnail: ITgPhotoSize;
begin
  Result := TgMakePhotoSize(TTgJson.GetValue(FJson, 'thumbnail'), JsonOwner);
end;

function TTgDocumentImpl.GetFileName: string;
begin
  Result := TTgJson.GetStr(FJson, 'file_name');
end;

function TTgDocumentImpl.GetMimeType: string;
begin
  Result := TTgJson.GetStr(FJson, 'mime_type');
end;

function TTgDocumentImpl.GetFileSize: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'file_size');
end;

function TTgDocumentImpl.GetHasFileSize: Boolean;
begin
  Result := TTgJson.Has(FJson, 'file_size');
end;

{ TTgLivePhotoImpl }

function TTgLivePhotoImpl.GetPhoto: TArray<ITgPhotoSize>;
begin
  Result := TTgDto.Objects<ITgPhotoSize>(TTgJson.GetArr(FJson, 'photo'), JsonOwner, TgMakePhotoSize);
end;

function TTgLivePhotoImpl.GetFileId: string;
begin
  Result := TTgJson.GetStr(FJson, 'file_id');
end;

function TTgLivePhotoImpl.GetFileUniqueId: string;
begin
  Result := TTgJson.GetStr(FJson, 'file_unique_id');
end;

function TTgLivePhotoImpl.GetWidth: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'width');
end;

function TTgLivePhotoImpl.GetHeight: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'height');
end;

function TTgLivePhotoImpl.GetDuration: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'duration');
end;

function TTgLivePhotoImpl.GetMimeType: string;
begin
  Result := TTgJson.GetStr(FJson, 'mime_type');
end;

function TTgLivePhotoImpl.GetFileSize: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'file_size');
end;

function TTgLivePhotoImpl.GetHasFileSize: Boolean;
begin
  Result := TTgJson.Has(FJson, 'file_size');
end;

{ TTgStoryImpl }

function TTgStoryImpl.GetChat: ITgChat;
begin
  Result := TgMakeChat(TTgJson.GetValue(FJson, 'chat'), JsonOwner);
end;

function TTgStoryImpl.GetId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'id');
end;

{ TTgVideoQualityImpl }

function TTgVideoQualityImpl.GetFileId: string;
begin
  Result := TTgJson.GetStr(FJson, 'file_id');
end;

function TTgVideoQualityImpl.GetFileUniqueId: string;
begin
  Result := TTgJson.GetStr(FJson, 'file_unique_id');
end;

function TTgVideoQualityImpl.GetWidth: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'width');
end;

function TTgVideoQualityImpl.GetHeight: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'height');
end;

function TTgVideoQualityImpl.GetCodec: string;
begin
  Result := TTgJson.GetStr(FJson, 'codec');
end;

function TTgVideoQualityImpl.GetFileSize: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'file_size');
end;

function TTgVideoQualityImpl.GetHasFileSize: Boolean;
begin
  Result := TTgJson.Has(FJson, 'file_size');
end;

{ TTgVideoImpl }

function TTgVideoImpl.GetFileId: string;
begin
  Result := TTgJson.GetStr(FJson, 'file_id');
end;

function TTgVideoImpl.GetFileUniqueId: string;
begin
  Result := TTgJson.GetStr(FJson, 'file_unique_id');
end;

function TTgVideoImpl.GetWidth: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'width');
end;

function TTgVideoImpl.GetHeight: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'height');
end;

function TTgVideoImpl.GetDuration: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'duration');
end;

function TTgVideoImpl.GetThumbnail: ITgPhotoSize;
begin
  Result := TgMakePhotoSize(TTgJson.GetValue(FJson, 'thumbnail'), JsonOwner);
end;

function TTgVideoImpl.GetCover: TArray<ITgPhotoSize>;
begin
  Result := TTgDto.Objects<ITgPhotoSize>(TTgJson.GetArr(FJson, 'cover'), JsonOwner, TgMakePhotoSize);
end;

function TTgVideoImpl.GetStartTimestamp: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'start_timestamp');
end;

function TTgVideoImpl.GetHasStartTimestamp: Boolean;
begin
  Result := TTgJson.Has(FJson, 'start_timestamp');
end;

function TTgVideoImpl.GetQualities: TArray<ITgVideoQuality>;
begin
  Result := TTgDto.Objects<ITgVideoQuality>(TTgJson.GetArr(FJson, 'qualities'), JsonOwner, TgMakeVideoQuality);
end;

function TTgVideoImpl.GetFileName: string;
begin
  Result := TTgJson.GetStr(FJson, 'file_name');
end;

function TTgVideoImpl.GetMimeType: string;
begin
  Result := TTgJson.GetStr(FJson, 'mime_type');
end;

function TTgVideoImpl.GetFileSize: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'file_size');
end;

function TTgVideoImpl.GetHasFileSize: Boolean;
begin
  Result := TTgJson.Has(FJson, 'file_size');
end;

{ TTgVideoNoteImpl }

function TTgVideoNoteImpl.GetFileId: string;
begin
  Result := TTgJson.GetStr(FJson, 'file_id');
end;

function TTgVideoNoteImpl.GetFileUniqueId: string;
begin
  Result := TTgJson.GetStr(FJson, 'file_unique_id');
end;

function TTgVideoNoteImpl.GetLength: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'length');
end;

function TTgVideoNoteImpl.GetDuration: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'duration');
end;

function TTgVideoNoteImpl.GetThumbnail: ITgPhotoSize;
begin
  Result := TgMakePhotoSize(TTgJson.GetValue(FJson, 'thumbnail'), JsonOwner);
end;

function TTgVideoNoteImpl.GetFileSize: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'file_size');
end;

function TTgVideoNoteImpl.GetHasFileSize: Boolean;
begin
  Result := TTgJson.Has(FJson, 'file_size');
end;

{ TTgVoiceImpl }

function TTgVoiceImpl.GetFileId: string;
begin
  Result := TTgJson.GetStr(FJson, 'file_id');
end;

function TTgVoiceImpl.GetFileUniqueId: string;
begin
  Result := TTgJson.GetStr(FJson, 'file_unique_id');
end;

function TTgVoiceImpl.GetDuration: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'duration');
end;

function TTgVoiceImpl.GetMimeType: string;
begin
  Result := TTgJson.GetStr(FJson, 'mime_type');
end;

function TTgVoiceImpl.GetFileSize: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'file_size');
end;

function TTgVoiceImpl.GetHasFileSize: Boolean;
begin
  Result := TTgJson.Has(FJson, 'file_size');
end;

{ TTgPaidMediaInfoImpl }

function TTgPaidMediaInfoImpl.GetStarCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'star_count');
end;

function TTgPaidMediaInfoImpl.GetPaidMedia: TArray<ITgPaidMedia>;
begin
  Result := TTgDto.Objects<ITgPaidMedia>(TTgJson.GetArr(FJson, 'paid_media'), JsonOwner, TgMakePaidMedia);
end;

{ TTgPaidMediaImpl }

function TTgPaidMediaImpl.GetKind: TTgPaidMediaKind;
begin
  Result := TTgPaidMediaKind.Unknown;
end;

function TTgPaidMediaImpl.GetKindText: string;
begin
  Result := TTgJson.GetStr(FJson, 'type');
end;

function TTgPaidMediaImpl.AsLivePhoto: ITgPaidMediaLivePhoto;
begin
  if not Supports(Self, ITgPaidMediaLivePhoto, Result) then
    Result := nil;
end;

function TTgPaidMediaImpl.AsPhoto: ITgPaidMediaPhoto;
begin
  if not Supports(Self, ITgPaidMediaPhoto, Result) then
    Result := nil;
end;

function TTgPaidMediaImpl.AsPreview: ITgPaidMediaPreview;
begin
  if not Supports(Self, ITgPaidMediaPreview, Result) then
    Result := nil;
end;

function TTgPaidMediaImpl.AsVideo: ITgPaidMediaVideo;
begin
  if not Supports(Self, ITgPaidMediaVideo, Result) then
    Result := nil;
end;

{ TTgPaidMediaLivePhotoImpl }

function TTgPaidMediaLivePhotoImpl.GetKind: TTgPaidMediaKind;
begin
  Result := TTgPaidMediaKind.LivePhoto;
end;

function TTgPaidMediaLivePhotoImpl.GetLivePhoto: ITgLivePhoto;
begin
  Result := TgMakeLivePhoto(TTgJson.GetValue(FJson, 'live_photo'), JsonOwner);
end;

{ TTgPaidMediaPhotoImpl }

function TTgPaidMediaPhotoImpl.GetKind: TTgPaidMediaKind;
begin
  Result := TTgPaidMediaKind.Photo;
end;

function TTgPaidMediaPhotoImpl.GetPhoto: TArray<ITgPhotoSize>;
begin
  Result := TTgDto.Objects<ITgPhotoSize>(TTgJson.GetArr(FJson, 'photo'), JsonOwner, TgMakePhotoSize);
end;

{ TTgPaidMediaPreviewImpl }

function TTgPaidMediaPreviewImpl.GetKind: TTgPaidMediaKind;
begin
  Result := TTgPaidMediaKind.Preview;
end;

function TTgPaidMediaPreviewImpl.GetWidth: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'width');
end;

function TTgPaidMediaPreviewImpl.GetHasWidth: Boolean;
begin
  Result := TTgJson.Has(FJson, 'width');
end;

function TTgPaidMediaPreviewImpl.GetHeight: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'height');
end;

function TTgPaidMediaPreviewImpl.GetHasHeight: Boolean;
begin
  Result := TTgJson.Has(FJson, 'height');
end;

function TTgPaidMediaPreviewImpl.GetDuration: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'duration');
end;

function TTgPaidMediaPreviewImpl.GetHasDuration: Boolean;
begin
  Result := TTgJson.Has(FJson, 'duration');
end;

{ TTgPaidMediaVideoImpl }

function TTgPaidMediaVideoImpl.GetKind: TTgPaidMediaKind;
begin
  Result := TTgPaidMediaKind.Video;
end;

function TTgPaidMediaVideoImpl.GetVideo: ITgVideo;
begin
  Result := TgMakeVideo(TTgJson.GetValue(FJson, 'video'), JsonOwner);
end;

{ TTgContactImpl }

function TTgContactImpl.GetPhoneNumber: string;
begin
  Result := TTgJson.GetStr(FJson, 'phone_number');
end;

function TTgContactImpl.GetFirstName: string;
begin
  Result := TTgJson.GetStr(FJson, 'first_name');
end;

function TTgContactImpl.GetLastName: string;
begin
  Result := TTgJson.GetStr(FJson, 'last_name');
end;

function TTgContactImpl.GetUserId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'user_id');
end;

function TTgContactImpl.GetHasUserId: Boolean;
begin
  Result := TTgJson.Has(FJson, 'user_id');
end;

function TTgContactImpl.GetVcard: string;
begin
  Result := TTgJson.GetStr(FJson, 'vcard');
end;

{ TTgDiceImpl }

function TTgDiceImpl.GetEmoji: string;
begin
  Result := TTgJson.GetStr(FJson, 'emoji');
end;

function TTgDiceImpl.GetValue: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'value');
end;

{ TTgLinkImpl }

function TTgLinkImpl.GetUrl: string;
begin
  Result := TTgJson.GetStr(FJson, 'url');
end;

{ TTgPollMediaImpl }

function TTgPollMediaImpl.GetAnimation: ITgAnimation;
begin
  Result := TgMakeAnimation(TTgJson.GetValue(FJson, 'animation'), JsonOwner);
end;

function TTgPollMediaImpl.GetAudio: ITgAudio;
begin
  Result := TgMakeAudio(TTgJson.GetValue(FJson, 'audio'), JsonOwner);
end;

function TTgPollMediaImpl.GetDocument: ITgDocument;
begin
  Result := TgMakeDocument(TTgJson.GetValue(FJson, 'document'), JsonOwner);
end;

function TTgPollMediaImpl.GetLink: ITgLink;
begin
  Result := TgMakeLink(TTgJson.GetValue(FJson, 'link'), JsonOwner);
end;

function TTgPollMediaImpl.GetLivePhoto: ITgLivePhoto;
begin
  Result := TgMakeLivePhoto(TTgJson.GetValue(FJson, 'live_photo'), JsonOwner);
end;

function TTgPollMediaImpl.GetLocation: ITgLocation;
begin
  Result := TgMakeLocation(TTgJson.GetValue(FJson, 'location'), JsonOwner);
end;

function TTgPollMediaImpl.GetPhoto: TArray<ITgPhotoSize>;
begin
  Result := TTgDto.Objects<ITgPhotoSize>(TTgJson.GetArr(FJson, 'photo'), JsonOwner, TgMakePhotoSize);
end;

function TTgPollMediaImpl.GetSticker: ITgSticker;
begin
  Result := TgMakeSticker(TTgJson.GetValue(FJson, 'sticker'), JsonOwner);
end;

function TTgPollMediaImpl.GetVenue: ITgVenue;
begin
  Result := TgMakeVenue(TTgJson.GetValue(FJson, 'venue'), JsonOwner);
end;

function TTgPollMediaImpl.GetVideo: ITgVideo;
begin
  Result := TgMakeVideo(TTgJson.GetValue(FJson, 'video'), JsonOwner);
end;

{ TTgPollOptionImpl }

function TTgPollOptionImpl.GetPersistentId: string;
begin
  Result := TTgJson.GetStr(FJson, 'persistent_id');
end;

function TTgPollOptionImpl.GetText: string;
begin
  Result := TTgJson.GetStr(FJson, 'text');
end;

function TTgPollOptionImpl.GetTextEntities: TArray<ITgMessageEntity>;
begin
  Result := TTgDto.Objects<ITgMessageEntity>(TTgJson.GetArr(FJson, 'text_entities'), JsonOwner, TgMakeMessageEntity);
end;

function TTgPollOptionImpl.GetMedia: ITgPollMedia;
begin
  Result := TgMakePollMedia(TTgJson.GetValue(FJson, 'media'), JsonOwner);
end;

function TTgPollOptionImpl.GetVoterCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'voter_count');
end;

function TTgPollOptionImpl.GetAddedByUser: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'added_by_user'), JsonOwner);
end;

function TTgPollOptionImpl.GetAddedByChat: ITgChat;
begin
  Result := TgMakeChat(TTgJson.GetValue(FJson, 'added_by_chat'), JsonOwner);
end;

function TTgPollOptionImpl.GetAdditionDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'addition_date');
end;

function TTgPollOptionImpl.GetHasAdditionDate: Boolean;
begin
  Result := TTgJson.Has(FJson, 'addition_date');
end;

{ TTgInputPollOptionImpl }

function TTgInputPollOptionImpl.WithText(const AValue: string): ITgInputPollOption;
begin
  SetStr('text', AValue);
  Result := Self;
end;

function TTgInputPollOptionImpl.WithTextParseMode(const AValue: string): ITgInputPollOption;
begin
  SetStr('text_parse_mode', AValue);
  Result := Self;
end;

function TTgInputPollOptionImpl.WithTextEntities(const AValue: array of ITgMessageEntity): ITgInputPollOption;
begin
  SetObjects('text_entities', TTgDto.ToIntf<ITgMessageEntity>(AValue));
  Result := Self;
end;

function TTgInputPollOptionImpl.WithMedia(const AValue: TTgInputPollOptionMedia): ITgInputPollOption;
begin
  SetObject('media', AValue.Value);
  Result := Self;
end;

{ TTgPollAnswerImpl }

function TTgPollAnswerImpl.GetPollId: string;
begin
  Result := TTgJson.GetStr(FJson, 'poll_id');
end;

function TTgPollAnswerImpl.GetVoterChat: ITgChat;
begin
  Result := TgMakeChat(TTgJson.GetValue(FJson, 'voter_chat'), JsonOwner);
end;

function TTgPollAnswerImpl.GetUser: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'user'), JsonOwner);
end;

function TTgPollAnswerImpl.GetOptionIds: TArray<Int64>;
begin
  Result := TTgDto.Int64s(TTgJson.GetArr(FJson, 'option_ids'), 'option_ids');
end;

function TTgPollAnswerImpl.GetOptionPersistentIds: TArray<string>;
begin
  Result := TTgDto.Strings(TTgJson.GetArr(FJson, 'option_persistent_ids'));
end;

{ TTgPollImpl }

function TTgPollImpl.GetId: string;
begin
  Result := TTgJson.GetStr(FJson, 'id');
end;

function TTgPollImpl.GetQuestion: string;
begin
  Result := TTgJson.GetStr(FJson, 'question');
end;

function TTgPollImpl.GetQuestionEntities: TArray<ITgMessageEntity>;
begin
  Result := TTgDto.Objects<ITgMessageEntity>(TTgJson.GetArr(FJson, 'question_entities'), JsonOwner, TgMakeMessageEntity);
end;

function TTgPollImpl.GetOptions: TArray<ITgPollOption>;
begin
  Result := TTgDto.Objects<ITgPollOption>(TTgJson.GetArr(FJson, 'options'), JsonOwner, TgMakePollOption);
end;

function TTgPollImpl.GetTotalVoterCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'total_voter_count');
end;

function TTgPollImpl.GetIsClosed: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_closed');
end;

function TTgPollImpl.GetIsAnonymous: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_anonymous');
end;

function TTgPollImpl.GetPollType: string;
begin
  Result := TTgJson.GetStr(FJson, 'type');
end;

function TTgPollImpl.GetAllowsMultipleAnswers: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'allows_multiple_answers');
end;

function TTgPollImpl.GetAllowsRevoting: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'allows_revoting');
end;

function TTgPollImpl.GetMembersOnly: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'members_only');
end;

function TTgPollImpl.GetCountryCodes: TArray<string>;
begin
  Result := TTgDto.Strings(TTgJson.GetArr(FJson, 'country_codes'));
end;

function TTgPollImpl.GetCorrectOptionIds: TArray<Int64>;
begin
  Result := TTgDto.Int64s(TTgJson.GetArr(FJson, 'correct_option_ids'), 'correct_option_ids');
end;

function TTgPollImpl.GetExplanation: string;
begin
  Result := TTgJson.GetStr(FJson, 'explanation');
end;

function TTgPollImpl.GetExplanationEntities: TArray<ITgMessageEntity>;
begin
  Result := TTgDto.Objects<ITgMessageEntity>(TTgJson.GetArr(FJson, 'explanation_entities'), JsonOwner, TgMakeMessageEntity);
end;

function TTgPollImpl.GetExplanationMedia: ITgPollMedia;
begin
  Result := TgMakePollMedia(TTgJson.GetValue(FJson, 'explanation_media'), JsonOwner);
end;

function TTgPollImpl.GetOpenPeriod: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'open_period');
end;

function TTgPollImpl.GetHasOpenPeriod: Boolean;
begin
  Result := TTgJson.Has(FJson, 'open_period');
end;

function TTgPollImpl.GetCloseDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'close_date');
end;

function TTgPollImpl.GetHasCloseDate: Boolean;
begin
  Result := TTgJson.Has(FJson, 'close_date');
end;

function TTgPollImpl.GetDescription: string;
begin
  Result := TTgJson.GetStr(FJson, 'description');
end;

function TTgPollImpl.GetDescriptionEntities: TArray<ITgMessageEntity>;
begin
  Result := TTgDto.Objects<ITgMessageEntity>(TTgJson.GetArr(FJson, 'description_entities'), JsonOwner, TgMakeMessageEntity);
end;

function TTgPollImpl.GetMedia: ITgPollMedia;
begin
  Result := TgMakePollMedia(TTgJson.GetValue(FJson, 'media'), JsonOwner);
end;

{ TTgChecklistTaskImpl }

function TTgChecklistTaskImpl.GetId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'id');
end;

function TTgChecklistTaskImpl.GetText: string;
begin
  Result := TTgJson.GetStr(FJson, 'text');
end;

function TTgChecklistTaskImpl.GetTextEntities: TArray<ITgMessageEntity>;
begin
  Result := TTgDto.Objects<ITgMessageEntity>(TTgJson.GetArr(FJson, 'text_entities'), JsonOwner, TgMakeMessageEntity);
end;

function TTgChecklistTaskImpl.GetCompletedByUser: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'completed_by_user'), JsonOwner);
end;

function TTgChecklistTaskImpl.GetCompletedByChat: ITgChat;
begin
  Result := TgMakeChat(TTgJson.GetValue(FJson, 'completed_by_chat'), JsonOwner);
end;

function TTgChecklistTaskImpl.GetCompletionDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'completion_date');
end;

function TTgChecklistTaskImpl.GetHasCompletionDate: Boolean;
begin
  Result := TTgJson.Has(FJson, 'completion_date');
end;

{ TTgChecklistImpl }

function TTgChecklistImpl.GetTitle: string;
begin
  Result := TTgJson.GetStr(FJson, 'title');
end;

function TTgChecklistImpl.GetTitleEntities: TArray<ITgMessageEntity>;
begin
  Result := TTgDto.Objects<ITgMessageEntity>(TTgJson.GetArr(FJson, 'title_entities'), JsonOwner, TgMakeMessageEntity);
end;

function TTgChecklistImpl.GetTasks: TArray<ITgChecklistTask>;
begin
  Result := TTgDto.Objects<ITgChecklistTask>(TTgJson.GetArr(FJson, 'tasks'), JsonOwner, TgMakeChecklistTask);
end;

function TTgChecklistImpl.GetOthersCanAddTasks: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'others_can_add_tasks');
end;

function TTgChecklistImpl.GetOthersCanMarkTasksAsDone: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'others_can_mark_tasks_as_done');
end;

{ TTgInputChecklistTaskImpl }

function TTgInputChecklistTaskImpl.WithId(AValue: Int64): ITgInputChecklistTask;
begin
  SetInt64('id', AValue);
  Result := Self;
end;

function TTgInputChecklistTaskImpl.WithText(const AValue: string): ITgInputChecklistTask;
begin
  SetStr('text', AValue);
  Result := Self;
end;

function TTgInputChecklistTaskImpl.WithParseMode(const AValue: string): ITgInputChecklistTask;
begin
  SetStr('parse_mode', AValue);
  Result := Self;
end;

function TTgInputChecklistTaskImpl.WithTextEntities(const AValue: array of ITgMessageEntity): ITgInputChecklistTask;
begin
  SetObjects('text_entities', TTgDto.ToIntf<ITgMessageEntity>(AValue));
  Result := Self;
end;

{ TTgInputChecklistImpl }

function TTgInputChecklistImpl.WithTitle(const AValue: string): ITgInputChecklist;
begin
  SetStr('title', AValue);
  Result := Self;
end;

function TTgInputChecklistImpl.WithParseMode(const AValue: string): ITgInputChecklist;
begin
  SetStr('parse_mode', AValue);
  Result := Self;
end;

function TTgInputChecklistImpl.WithTitleEntities(const AValue: array of ITgMessageEntity): ITgInputChecklist;
begin
  SetObjects('title_entities', TTgDto.ToIntf<ITgMessageEntity>(AValue));
  Result := Self;
end;

function TTgInputChecklistImpl.WithTasks(const AValue: array of ITgInputChecklistTask): ITgInputChecklist;
begin
  SetObjects('tasks', TTgDto.ToIntf<ITgInputChecklistTask>(AValue));
  Result := Self;
end;

function TTgInputChecklistImpl.WithOthersCanAddTasks(AValue: Boolean): ITgInputChecklist;
begin
  SetBool('others_can_add_tasks', AValue);
  Result := Self;
end;

function TTgInputChecklistImpl.WithOthersCanMarkTasksAsDone(AValue: Boolean): ITgInputChecklist;
begin
  SetBool('others_can_mark_tasks_as_done', AValue);
  Result := Self;
end;

{ TTgLocationImpl }

function TTgLocationImpl.GetLatitude: Double;
begin
  Result := TTgJson.GetDouble(FJson, 'latitude');
end;

function TTgLocationImpl.GetLongitude: Double;
begin
  Result := TTgJson.GetDouble(FJson, 'longitude');
end;

function TTgLocationImpl.GetHorizontalAccuracy: Double;
begin
  Result := TTgJson.GetDouble(FJson, 'horizontal_accuracy');
end;

function TTgLocationImpl.GetHasHorizontalAccuracy: Boolean;
begin
  Result := TTgJson.Has(FJson, 'horizontal_accuracy');
end;

function TTgLocationImpl.GetLivePeriod: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'live_period');
end;

function TTgLocationImpl.GetHasLivePeriod: Boolean;
begin
  Result := TTgJson.Has(FJson, 'live_period');
end;

function TTgLocationImpl.GetHeading: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'heading');
end;

function TTgLocationImpl.GetHasHeading: Boolean;
begin
  Result := TTgJson.Has(FJson, 'heading');
end;

function TTgLocationImpl.GetProximityAlertRadius: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'proximity_alert_radius');
end;

function TTgLocationImpl.GetHasProximityAlertRadius: Boolean;
begin
  Result := TTgJson.Has(FJson, 'proximity_alert_radius');
end;

function TTgLocationImpl.WithLatitude(AValue: Double): ITgLocation;
begin
  SetDouble('latitude', AValue);
  Result := Self;
end;

function TTgLocationImpl.WithLongitude(AValue: Double): ITgLocation;
begin
  SetDouble('longitude', AValue);
  Result := Self;
end;

function TTgLocationImpl.WithHorizontalAccuracy(AValue: Double): ITgLocation;
begin
  SetDouble('horizontal_accuracy', AValue);
  Result := Self;
end;

function TTgLocationImpl.WithLivePeriod(AValue: Integer): ITgLocation;
begin
  SetInt('live_period', AValue);
  Result := Self;
end;

function TTgLocationImpl.WithHeading(AValue: Integer): ITgLocation;
begin
  SetInt('heading', AValue);
  Result := Self;
end;

function TTgLocationImpl.WithProximityAlertRadius(AValue: Integer): ITgLocation;
begin
  SetInt('proximity_alert_radius', AValue);
  Result := Self;
end;

{ TTgVenueImpl }

function TTgVenueImpl.GetLocation: ITgLocation;
begin
  Result := TgMakeLocation(TTgJson.GetValue(FJson, 'location'), JsonOwner);
end;

function TTgVenueImpl.GetTitle: string;
begin
  Result := TTgJson.GetStr(FJson, 'title');
end;

function TTgVenueImpl.GetAddress: string;
begin
  Result := TTgJson.GetStr(FJson, 'address');
end;

function TTgVenueImpl.GetFoursquareId: string;
begin
  Result := TTgJson.GetStr(FJson, 'foursquare_id');
end;

function TTgVenueImpl.GetFoursquareType: string;
begin
  Result := TTgJson.GetStr(FJson, 'foursquare_type');
end;

function TTgVenueImpl.GetGooglePlaceId: string;
begin
  Result := TTgJson.GetStr(FJson, 'google_place_id');
end;

function TTgVenueImpl.GetGooglePlaceType: string;
begin
  Result := TTgJson.GetStr(FJson, 'google_place_type');
end;

{ TTgWebAppDataImpl }

function TTgWebAppDataImpl.GetData: string;
begin
  Result := TTgJson.GetStr(FJson, 'data');
end;

function TTgWebAppDataImpl.GetButtonText: string;
begin
  Result := TTgJson.GetStr(FJson, 'button_text');
end;

{ TTgProximityAlertTriggeredImpl }

function TTgProximityAlertTriggeredImpl.GetTraveler: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'traveler'), JsonOwner);
end;

function TTgProximityAlertTriggeredImpl.GetWatcher: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'watcher'), JsonOwner);
end;

function TTgProximityAlertTriggeredImpl.GetDistance: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'distance');
end;

{ TTgMessageAutoDeleteTimerChangedImpl }

function TTgMessageAutoDeleteTimerChangedImpl.GetMessageAutoDeleteTime: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'message_auto_delete_time');
end;

{ TTgManagedBotCreatedImpl }

function TTgManagedBotCreatedImpl.GetBot: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'bot'), JsonOwner);
end;

{ TTgManagedBotUpdatedImpl }

function TTgManagedBotUpdatedImpl.GetUser: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'user'), JsonOwner);
end;

function TTgManagedBotUpdatedImpl.GetBot: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'bot'), JsonOwner);
end;

{ TTgBotSubscriptionUpdatedImpl }

function TTgBotSubscriptionUpdatedImpl.GetUser: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'user'), JsonOwner);
end;

function TTgBotSubscriptionUpdatedImpl.GetInvoicePayload: string;
begin
  Result := TTgJson.GetStr(FJson, 'invoice_payload');
end;

function TTgBotSubscriptionUpdatedImpl.GetState: string;
begin
  Result := TTgJson.GetStr(FJson, 'state');
end;

{ TTgMessageGenerationStoppedImpl }

function TTgMessageGenerationStoppedImpl.GetChat: ITgChat;
begin
  Result := TgMakeChat(TTgJson.GetValue(FJson, 'chat'), JsonOwner);
end;

function TTgMessageGenerationStoppedImpl.GetMessageThreadId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'message_thread_id');
end;

function TTgMessageGenerationStoppedImpl.GetHasMessageThreadId: Boolean;
begin
  Result := TTgJson.Has(FJson, 'message_thread_id');
end;

function TTgMessageGenerationStoppedImpl.GetDraftId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'draft_id');
end;

{ TTgPollOptionAddedImpl }

function TTgPollOptionAddedImpl.GetPollMessage: ITgMaybeInaccessibleMessage;
begin
  Result := TgMakeMaybeInaccessibleMessage(TTgJson.GetValue(FJson, 'poll_message'), JsonOwner);
end;

function TTgPollOptionAddedImpl.GetOptionPersistentId: string;
begin
  Result := TTgJson.GetStr(FJson, 'option_persistent_id');
end;

function TTgPollOptionAddedImpl.GetOptionText: string;
begin
  Result := TTgJson.GetStr(FJson, 'option_text');
end;

function TTgPollOptionAddedImpl.GetOptionTextEntities: TArray<ITgMessageEntity>;
begin
  Result := TTgDto.Objects<ITgMessageEntity>(TTgJson.GetArr(FJson, 'option_text_entities'), JsonOwner, TgMakeMessageEntity);
end;

{ TTgPollOptionDeletedImpl }

function TTgPollOptionDeletedImpl.GetPollMessage: ITgMaybeInaccessibleMessage;
begin
  Result := TgMakeMaybeInaccessibleMessage(TTgJson.GetValue(FJson, 'poll_message'), JsonOwner);
end;

function TTgPollOptionDeletedImpl.GetOptionPersistentId: string;
begin
  Result := TTgJson.GetStr(FJson, 'option_persistent_id');
end;

function TTgPollOptionDeletedImpl.GetOptionText: string;
begin
  Result := TTgJson.GetStr(FJson, 'option_text');
end;

function TTgPollOptionDeletedImpl.GetOptionTextEntities: TArray<ITgMessageEntity>;
begin
  Result := TTgDto.Objects<ITgMessageEntity>(TTgJson.GetArr(FJson, 'option_text_entities'), JsonOwner, TgMakeMessageEntity);
end;

{ TTgChatBoostAddedImpl }

function TTgChatBoostAddedImpl.GetBoostCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'boost_count');
end;

{ TTgBackgroundFillImpl }

function TTgBackgroundFillImpl.GetKind: TTgBackgroundFillKind;
begin
  Result := TTgBackgroundFillKind.Unknown;
end;

function TTgBackgroundFillImpl.GetKindText: string;
begin
  Result := TTgJson.GetStr(FJson, 'type');
end;

function TTgBackgroundFillImpl.AsSolid: ITgBackgroundFillSolid;
begin
  if not Supports(Self, ITgBackgroundFillSolid, Result) then
    Result := nil;
end;

function TTgBackgroundFillImpl.AsGradient: ITgBackgroundFillGradient;
begin
  if not Supports(Self, ITgBackgroundFillGradient, Result) then
    Result := nil;
end;

function TTgBackgroundFillImpl.AsFreeformGradient: ITgBackgroundFillFreeformGradient;
begin
  if not Supports(Self, ITgBackgroundFillFreeformGradient, Result) then
    Result := nil;
end;

{ TTgBackgroundFillSolidImpl }

function TTgBackgroundFillSolidImpl.GetKind: TTgBackgroundFillKind;
begin
  Result := TTgBackgroundFillKind.Solid;
end;

function TTgBackgroundFillSolidImpl.GetColor: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'color');
end;

{ TTgBackgroundFillGradientImpl }

function TTgBackgroundFillGradientImpl.GetKind: TTgBackgroundFillKind;
begin
  Result := TTgBackgroundFillKind.Gradient;
end;

function TTgBackgroundFillGradientImpl.GetTopColor: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'top_color');
end;

function TTgBackgroundFillGradientImpl.GetBottomColor: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'bottom_color');
end;

function TTgBackgroundFillGradientImpl.GetRotationAngle: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'rotation_angle');
end;

{ TTgBackgroundFillFreeformGradientImpl }

function TTgBackgroundFillFreeformGradientImpl.GetKind: TTgBackgroundFillKind;
begin
  Result := TTgBackgroundFillKind.FreeformGradient;
end;

function TTgBackgroundFillFreeformGradientImpl.GetColors: TArray<Integer>;
begin
  Result := TTgDto.Integers(TTgJson.GetArr(FJson, 'colors'), 'colors');
end;

{ TTgBackgroundTypeImpl }

function TTgBackgroundTypeImpl.GetKind: TTgBackgroundTypeKind;
begin
  Result := TTgBackgroundTypeKind.Unknown;
end;

function TTgBackgroundTypeImpl.GetKindText: string;
begin
  Result := TTgJson.GetStr(FJson, 'type');
end;

function TTgBackgroundTypeImpl.AsFill: ITgBackgroundTypeFill;
begin
  if not Supports(Self, ITgBackgroundTypeFill, Result) then
    Result := nil;
end;

function TTgBackgroundTypeImpl.AsWallpaper: ITgBackgroundTypeWallpaper;
begin
  if not Supports(Self, ITgBackgroundTypeWallpaper, Result) then
    Result := nil;
end;

function TTgBackgroundTypeImpl.AsPattern: ITgBackgroundTypePattern;
begin
  if not Supports(Self, ITgBackgroundTypePattern, Result) then
    Result := nil;
end;

function TTgBackgroundTypeImpl.AsChatTheme: ITgBackgroundTypeChatTheme;
begin
  if not Supports(Self, ITgBackgroundTypeChatTheme, Result) then
    Result := nil;
end;

{ TTgBackgroundTypeFillImpl }

function TTgBackgroundTypeFillImpl.GetKind: TTgBackgroundTypeKind;
begin
  Result := TTgBackgroundTypeKind.Fill;
end;

function TTgBackgroundTypeFillImpl.GetFill: ITgBackgroundFill;
begin
  Result := TgMakeBackgroundFill(TTgJson.GetValue(FJson, 'fill'), JsonOwner);
end;

function TTgBackgroundTypeFillImpl.GetDarkThemeDimming: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'dark_theme_dimming');
end;

{ TTgBackgroundTypeWallpaperImpl }

function TTgBackgroundTypeWallpaperImpl.GetKind: TTgBackgroundTypeKind;
begin
  Result := TTgBackgroundTypeKind.Wallpaper;
end;

function TTgBackgroundTypeWallpaperImpl.GetDocument: ITgDocument;
begin
  Result := TgMakeDocument(TTgJson.GetValue(FJson, 'document'), JsonOwner);
end;

function TTgBackgroundTypeWallpaperImpl.GetDarkThemeDimming: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'dark_theme_dimming');
end;

function TTgBackgroundTypeWallpaperImpl.GetIsBlurred: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_blurred');
end;

function TTgBackgroundTypeWallpaperImpl.GetIsMoving: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_moving');
end;

{ TTgBackgroundTypePatternImpl }

function TTgBackgroundTypePatternImpl.GetKind: TTgBackgroundTypeKind;
begin
  Result := TTgBackgroundTypeKind.Pattern;
end;

function TTgBackgroundTypePatternImpl.GetDocument: ITgDocument;
begin
  Result := TgMakeDocument(TTgJson.GetValue(FJson, 'document'), JsonOwner);
end;

function TTgBackgroundTypePatternImpl.GetFill: ITgBackgroundFill;
begin
  Result := TgMakeBackgroundFill(TTgJson.GetValue(FJson, 'fill'), JsonOwner);
end;

function TTgBackgroundTypePatternImpl.GetIntensity: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'intensity');
end;

function TTgBackgroundTypePatternImpl.GetIsInverted: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_inverted');
end;

function TTgBackgroundTypePatternImpl.GetIsMoving: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_moving');
end;

{ TTgBackgroundTypeChatThemeImpl }

function TTgBackgroundTypeChatThemeImpl.GetKind: TTgBackgroundTypeKind;
begin
  Result := TTgBackgroundTypeKind.ChatTheme;
end;

function TTgBackgroundTypeChatThemeImpl.GetThemeName: string;
begin
  Result := TTgJson.GetStr(FJson, 'theme_name');
end;

{ TTgChatBackgroundImpl }

function TTgChatBackgroundImpl.GetChatBackgroundType: ITgBackgroundType;
begin
  Result := TgMakeBackgroundType(TTgJson.GetValue(FJson, 'type'), JsonOwner);
end;

{ TTgChecklistTasksDoneImpl }

function TTgChecklistTasksDoneImpl.GetChecklistMessage: ITgMessage;
begin
  Result := TgMakeMessage(TTgJson.GetValue(FJson, 'checklist_message'), JsonOwner);
end;

function TTgChecklistTasksDoneImpl.GetMarkedAsDoneTaskIds: TArray<Int64>;
begin
  Result := TTgDto.Int64s(TTgJson.GetArr(FJson, 'marked_as_done_task_ids'), 'marked_as_done_task_ids');
end;

function TTgChecklistTasksDoneImpl.GetMarkedAsNotDoneTaskIds: TArray<Int64>;
begin
  Result := TTgDto.Int64s(TTgJson.GetArr(FJson, 'marked_as_not_done_task_ids'), 'marked_as_not_done_task_ids');
end;

{ TTgChecklistTasksAddedImpl }

function TTgChecklistTasksAddedImpl.GetChecklistMessage: ITgMessage;
begin
  Result := TgMakeMessage(TTgJson.GetValue(FJson, 'checklist_message'), JsonOwner);
end;

function TTgChecklistTasksAddedImpl.GetTasks: TArray<ITgChecklistTask>;
begin
  Result := TTgDto.Objects<ITgChecklistTask>(TTgJson.GetArr(FJson, 'tasks'), JsonOwner, TgMakeChecklistTask);
end;

{ TTgCommunityChatAddedImpl }

function TTgCommunityChatAddedImpl.GetCommunity: ITgCommunity;
begin
  Result := TgMakeCommunity(TTgJson.GetValue(FJson, 'community'), JsonOwner);
end;

{ TTgCommunityChatJoinedImpl }

function TTgCommunityChatJoinedImpl.GetCommunity: ITgCommunity;
begin
  Result := TgMakeCommunity(TTgJson.GetValue(FJson, 'community'), JsonOwner);
end;

{ TTgCommunityChatRemovedImpl }

{ TTgForumTopicCreatedImpl }

function TTgForumTopicCreatedImpl.GetName: string;
begin
  Result := TTgJson.GetStr(FJson, 'name');
end;

function TTgForumTopicCreatedImpl.GetIconColor: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'icon_color');
end;

function TTgForumTopicCreatedImpl.GetIconCustomEmojiId: string;
begin
  Result := TTgJson.GetStr(FJson, 'icon_custom_emoji_id');
end;

function TTgForumTopicCreatedImpl.GetIsNameImplicit: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_name_implicit');
end;

{ TTgForumTopicClosedImpl }

{ TTgForumTopicEditedImpl }

function TTgForumTopicEditedImpl.GetName: string;
begin
  Result := TTgJson.GetStr(FJson, 'name');
end;

function TTgForumTopicEditedImpl.GetIconCustomEmojiId: string;
begin
  Result := TTgJson.GetStr(FJson, 'icon_custom_emoji_id');
end;

{ TTgForumTopicReopenedImpl }

{ TTgGeneralForumTopicHiddenImpl }

{ TTgGeneralForumTopicUnhiddenImpl }

{ TTgSharedUserImpl }

function TTgSharedUserImpl.GetUserId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'user_id');
end;

function TTgSharedUserImpl.GetFirstName: string;
begin
  Result := TTgJson.GetStr(FJson, 'first_name');
end;

function TTgSharedUserImpl.GetLastName: string;
begin
  Result := TTgJson.GetStr(FJson, 'last_name');
end;

function TTgSharedUserImpl.GetUsername: string;
begin
  Result := TTgJson.GetStr(FJson, 'username');
end;

function TTgSharedUserImpl.GetPhoto: TArray<ITgPhotoSize>;
begin
  Result := TTgDto.Objects<ITgPhotoSize>(TTgJson.GetArr(FJson, 'photo'), JsonOwner, TgMakePhotoSize);
end;

{ TTgUsersSharedImpl }

function TTgUsersSharedImpl.GetRequestId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'request_id');
end;

function TTgUsersSharedImpl.GetUsers: TArray<ITgSharedUser>;
begin
  Result := TTgDto.Objects<ITgSharedUser>(TTgJson.GetArr(FJson, 'users'), JsonOwner, TgMakeSharedUser);
end;

{ TTgChatSharedImpl }

function TTgChatSharedImpl.GetRequestId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'request_id');
end;

function TTgChatSharedImpl.GetChatId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'chat_id');
end;

function TTgChatSharedImpl.GetTitle: string;
begin
  Result := TTgJson.GetStr(FJson, 'title');
end;

function TTgChatSharedImpl.GetUsername: string;
begin
  Result := TTgJson.GetStr(FJson, 'username');
end;

function TTgChatSharedImpl.GetPhoto: TArray<ITgPhotoSize>;
begin
  Result := TTgDto.Objects<ITgPhotoSize>(TTgJson.GetArr(FJson, 'photo'), JsonOwner, TgMakePhotoSize);
end;

{ TTgWriteAccessAllowedImpl }

function TTgWriteAccessAllowedImpl.GetFromRequest: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'from_request');
end;

function TTgWriteAccessAllowedImpl.GetHasFromRequest: Boolean;
begin
  Result := TTgJson.Has(FJson, 'from_request');
end;

function TTgWriteAccessAllowedImpl.GetWebAppName: string;
begin
  Result := TTgJson.GetStr(FJson, 'web_app_name');
end;

function TTgWriteAccessAllowedImpl.GetFromAttachmentMenu: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'from_attachment_menu');
end;

function TTgWriteAccessAllowedImpl.GetHasFromAttachmentMenu: Boolean;
begin
  Result := TTgJson.Has(FJson, 'from_attachment_menu');
end;

{ TTgVideoChatScheduledImpl }

function TTgVideoChatScheduledImpl.GetStartDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'start_date');
end;

{ TTgVideoChatStartedImpl }

{ TTgVideoChatEndedImpl }

function TTgVideoChatEndedImpl.GetDuration: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'duration');
end;

{ TTgVideoChatParticipantsInvitedImpl }

function TTgVideoChatParticipantsInvitedImpl.GetUsers: TArray<ITgUser>;
begin
  Result := TTgDto.Objects<ITgUser>(TTgJson.GetArr(FJson, 'users'), JsonOwner, TgMakeUser);
end;

{ TTgPaidMessagePriceChangedImpl }

function TTgPaidMessagePriceChangedImpl.GetPaidMessageStarCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'paid_message_star_count');
end;

{ TTgDirectMessagePriceChangedImpl }

function TTgDirectMessagePriceChangedImpl.GetAreDirectMessagesEnabled: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'are_direct_messages_enabled');
end;

function TTgDirectMessagePriceChangedImpl.GetDirectMessageStarCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'direct_message_star_count');
end;

function TTgDirectMessagePriceChangedImpl.GetHasDirectMessageStarCount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'direct_message_star_count');
end;

{ TTgSuggestedPostApprovedImpl }

function TTgSuggestedPostApprovedImpl.GetSuggestedPostMessage: ITgMessage;
begin
  Result := TgMakeMessage(TTgJson.GetValue(FJson, 'suggested_post_message'), JsonOwner);
end;

function TTgSuggestedPostApprovedImpl.GetPrice: ITgSuggestedPostPrice;
begin
  Result := TgMakeSuggestedPostPrice(TTgJson.GetValue(FJson, 'price'), JsonOwner);
end;

function TTgSuggestedPostApprovedImpl.GetSendDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'send_date');
end;

{ TTgSuggestedPostApprovalFailedImpl }

function TTgSuggestedPostApprovalFailedImpl.GetSuggestedPostMessage: ITgMessage;
begin
  Result := TgMakeMessage(TTgJson.GetValue(FJson, 'suggested_post_message'), JsonOwner);
end;

function TTgSuggestedPostApprovalFailedImpl.GetPrice: ITgSuggestedPostPrice;
begin
  Result := TgMakeSuggestedPostPrice(TTgJson.GetValue(FJson, 'price'), JsonOwner);
end;

{ TTgSuggestedPostDeclinedImpl }

function TTgSuggestedPostDeclinedImpl.GetSuggestedPostMessage: ITgMessage;
begin
  Result := TgMakeMessage(TTgJson.GetValue(FJson, 'suggested_post_message'), JsonOwner);
end;

function TTgSuggestedPostDeclinedImpl.GetComment: string;
begin
  Result := TTgJson.GetStr(FJson, 'comment');
end;

{ TTgSuggestedPostPaidImpl }

function TTgSuggestedPostPaidImpl.GetSuggestedPostMessage: ITgMessage;
begin
  Result := TgMakeMessage(TTgJson.GetValue(FJson, 'suggested_post_message'), JsonOwner);
end;

function TTgSuggestedPostPaidImpl.GetCurrency: string;
begin
  Result := TTgJson.GetStr(FJson, 'currency');
end;

function TTgSuggestedPostPaidImpl.GetAmount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'amount');
end;

function TTgSuggestedPostPaidImpl.GetHasAmount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'amount');
end;

function TTgSuggestedPostPaidImpl.GetStarAmount: ITgStarAmount;
begin
  Result := TgMakeStarAmount(TTgJson.GetValue(FJson, 'star_amount'), JsonOwner);
end;

{ TTgSuggestedPostRefundedImpl }

function TTgSuggestedPostRefundedImpl.GetSuggestedPostMessage: ITgMessage;
begin
  Result := TgMakeMessage(TTgJson.GetValue(FJson, 'suggested_post_message'), JsonOwner);
end;

function TTgSuggestedPostRefundedImpl.GetReason: string;
begin
  Result := TTgJson.GetStr(FJson, 'reason');
end;

{ TTgGiveawayCreatedImpl }

function TTgGiveawayCreatedImpl.GetPrizeStarCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'prize_star_count');
end;

function TTgGiveawayCreatedImpl.GetHasPrizeStarCount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'prize_star_count');
end;

{ TTgGiveawayImpl }

function TTgGiveawayImpl.GetChats: TArray<ITgChat>;
begin
  Result := TTgDto.Objects<ITgChat>(TTgJson.GetArr(FJson, 'chats'), JsonOwner, TgMakeChat);
end;

function TTgGiveawayImpl.GetWinnersSelectionDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'winners_selection_date');
end;

function TTgGiveawayImpl.GetWinnerCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'winner_count');
end;

function TTgGiveawayImpl.GetOnlyNewMembers: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'only_new_members');
end;

function TTgGiveawayImpl.GetHasPublicWinners: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'has_public_winners');
end;

function TTgGiveawayImpl.GetPrizeDescription: string;
begin
  Result := TTgJson.GetStr(FJson, 'prize_description');
end;

function TTgGiveawayImpl.GetCountryCodes: TArray<string>;
begin
  Result := TTgDto.Strings(TTgJson.GetArr(FJson, 'country_codes'));
end;

function TTgGiveawayImpl.GetPrizeStarCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'prize_star_count');
end;

function TTgGiveawayImpl.GetHasPrizeStarCount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'prize_star_count');
end;

function TTgGiveawayImpl.GetPremiumSubscriptionMonthCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'premium_subscription_month_count');
end;

function TTgGiveawayImpl.GetHasPremiumSubscriptionMonthCount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'premium_subscription_month_count');
end;

{ TTgGiveawayWinnersImpl }

function TTgGiveawayWinnersImpl.GetChat: ITgChat;
begin
  Result := TgMakeChat(TTgJson.GetValue(FJson, 'chat'), JsonOwner);
end;

function TTgGiveawayWinnersImpl.GetGiveawayMessageId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'giveaway_message_id');
end;

function TTgGiveawayWinnersImpl.GetWinnersSelectionDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'winners_selection_date');
end;

function TTgGiveawayWinnersImpl.GetWinnerCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'winner_count');
end;

function TTgGiveawayWinnersImpl.GetWinners: TArray<ITgUser>;
begin
  Result := TTgDto.Objects<ITgUser>(TTgJson.GetArr(FJson, 'winners'), JsonOwner, TgMakeUser);
end;

function TTgGiveawayWinnersImpl.GetAdditionalChatCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'additional_chat_count');
end;

function TTgGiveawayWinnersImpl.GetHasAdditionalChatCount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'additional_chat_count');
end;

function TTgGiveawayWinnersImpl.GetPrizeStarCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'prize_star_count');
end;

function TTgGiveawayWinnersImpl.GetHasPrizeStarCount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'prize_star_count');
end;

function TTgGiveawayWinnersImpl.GetPremiumSubscriptionMonthCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'premium_subscription_month_count');
end;

function TTgGiveawayWinnersImpl.GetHasPremiumSubscriptionMonthCount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'premium_subscription_month_count');
end;

function TTgGiveawayWinnersImpl.GetUnclaimedPrizeCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'unclaimed_prize_count');
end;

function TTgGiveawayWinnersImpl.GetHasUnclaimedPrizeCount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'unclaimed_prize_count');
end;

function TTgGiveawayWinnersImpl.GetOnlyNewMembers: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'only_new_members');
end;

function TTgGiveawayWinnersImpl.GetWasRefunded: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'was_refunded');
end;

function TTgGiveawayWinnersImpl.GetPrizeDescription: string;
begin
  Result := TTgJson.GetStr(FJson, 'prize_description');
end;

{ TTgGiveawayCompletedImpl }

function TTgGiveawayCompletedImpl.GetWinnerCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'winner_count');
end;

function TTgGiveawayCompletedImpl.GetUnclaimedPrizeCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'unclaimed_prize_count');
end;

function TTgGiveawayCompletedImpl.GetHasUnclaimedPrizeCount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'unclaimed_prize_count');
end;

function TTgGiveawayCompletedImpl.GetGiveawayMessage: ITgMessage;
begin
  Result := TgMakeMessage(TTgJson.GetValue(FJson, 'giveaway_message'), JsonOwner);
end;

function TTgGiveawayCompletedImpl.GetIsStarGiveaway: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_star_giveaway');
end;

{ TTgLinkPreviewOptionsImpl }

function TTgLinkPreviewOptionsImpl.GetIsDisabled: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_disabled');
end;

function TTgLinkPreviewOptionsImpl.GetHasIsDisabled: Boolean;
begin
  Result := TTgJson.Has(FJson, 'is_disabled');
end;

function TTgLinkPreviewOptionsImpl.GetUrl: string;
begin
  Result := TTgJson.GetStr(FJson, 'url');
end;

function TTgLinkPreviewOptionsImpl.GetPreferSmallMedia: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'prefer_small_media');
end;

function TTgLinkPreviewOptionsImpl.GetHasPreferSmallMedia: Boolean;
begin
  Result := TTgJson.Has(FJson, 'prefer_small_media');
end;

function TTgLinkPreviewOptionsImpl.GetPreferLargeMedia: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'prefer_large_media');
end;

function TTgLinkPreviewOptionsImpl.GetHasPreferLargeMedia: Boolean;
begin
  Result := TTgJson.Has(FJson, 'prefer_large_media');
end;

function TTgLinkPreviewOptionsImpl.GetShowAboveText: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'show_above_text');
end;

function TTgLinkPreviewOptionsImpl.GetHasShowAboveText: Boolean;
begin
  Result := TTgJson.Has(FJson, 'show_above_text');
end;

function TTgLinkPreviewOptionsImpl.WithIsDisabled(AValue: Boolean): ITgLinkPreviewOptions;
begin
  SetBool('is_disabled', AValue);
  Result := Self;
end;

function TTgLinkPreviewOptionsImpl.WithUrl(const AValue: string): ITgLinkPreviewOptions;
begin
  SetStr('url', AValue);
  Result := Self;
end;

function TTgLinkPreviewOptionsImpl.WithPreferSmallMedia(AValue: Boolean): ITgLinkPreviewOptions;
begin
  SetBool('prefer_small_media', AValue);
  Result := Self;
end;

function TTgLinkPreviewOptionsImpl.WithPreferLargeMedia(AValue: Boolean): ITgLinkPreviewOptions;
begin
  SetBool('prefer_large_media', AValue);
  Result := Self;
end;

function TTgLinkPreviewOptionsImpl.WithShowAboveText(AValue: Boolean): ITgLinkPreviewOptions;
begin
  SetBool('show_above_text', AValue);
  Result := Self;
end;

{ TTgSuggestedPostPriceImpl }

function TTgSuggestedPostPriceImpl.GetCurrency: string;
begin
  Result := TTgJson.GetStr(FJson, 'currency');
end;

function TTgSuggestedPostPriceImpl.GetAmount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'amount');
end;

function TTgSuggestedPostPriceImpl.WithCurrency(const AValue: string): ITgSuggestedPostPrice;
begin
  SetStr('currency', AValue);
  Result := Self;
end;

function TTgSuggestedPostPriceImpl.WithAmount(AValue: Integer): ITgSuggestedPostPrice;
begin
  SetInt('amount', AValue);
  Result := Self;
end;

{ TTgSuggestedPostInfoImpl }

function TTgSuggestedPostInfoImpl.GetState: string;
begin
  Result := TTgJson.GetStr(FJson, 'state');
end;

function TTgSuggestedPostInfoImpl.GetPrice: ITgSuggestedPostPrice;
begin
  Result := TgMakeSuggestedPostPrice(TTgJson.GetValue(FJson, 'price'), JsonOwner);
end;

function TTgSuggestedPostInfoImpl.GetSendDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'send_date');
end;

function TTgSuggestedPostInfoImpl.GetHasSendDate: Boolean;
begin
  Result := TTgJson.Has(FJson, 'send_date');
end;

{ TTgSuggestedPostParametersImpl }

function TTgSuggestedPostParametersImpl.WithPrice(const AValue: ITgSuggestedPostPrice): ITgSuggestedPostParameters;
begin
  SetObject('price', AValue);
  Result := Self;
end;

function TTgSuggestedPostParametersImpl.WithSendDate(AValue: Int64): ITgSuggestedPostParameters;
begin
  SetInt64('send_date', AValue);
  Result := Self;
end;

{ TTgDirectMessagesTopicImpl }

function TTgDirectMessagesTopicImpl.GetTopicId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'topic_id');
end;

function TTgDirectMessagesTopicImpl.GetUser: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'user'), JsonOwner);
end;

{ TTgUserProfilePhotosImpl }

function TTgUserProfilePhotosImpl.GetTotalCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'total_count');
end;

function TTgUserProfilePhotosImpl.GetPhotos: TArray<TArray<ITgPhotoSize>>;
begin
  Result := TTgDto.Objects2<ITgPhotoSize>(TTgJson.GetArr(FJson, 'photos'), JsonOwner, TgMakePhotoSize);
end;

{ TTgUserProfileAudiosImpl }

function TTgUserProfileAudiosImpl.GetTotalCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'total_count');
end;

function TTgUserProfileAudiosImpl.GetAudios: TArray<ITgAudio>;
begin
  Result := TTgDto.Objects<ITgAudio>(TTgJson.GetArr(FJson, 'audios'), JsonOwner, TgMakeAudio);
end;

{ TTgFileImpl }

function TTgFileImpl.GetFileId: string;
begin
  Result := TTgJson.GetStr(FJson, 'file_id');
end;

function TTgFileImpl.GetFileUniqueId: string;
begin
  Result := TTgJson.GetStr(FJson, 'file_unique_id');
end;

function TTgFileImpl.GetFileSize: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'file_size');
end;

function TTgFileImpl.GetHasFileSize: Boolean;
begin
  Result := TTgJson.Has(FJson, 'file_size');
end;

function TTgFileImpl.GetFilePath: string;
begin
  Result := TTgJson.GetStr(FJson, 'file_path');
end;

{ TTgWebAppInfoImpl }

function TTgWebAppInfoImpl.GetUrl: string;
begin
  Result := TTgJson.GetStr(FJson, 'url');
end;

function TTgWebAppInfoImpl.WithUrl(const AValue: string): ITgWebAppInfo;
begin
  SetStr('url', AValue);
  Result := Self;
end;

{ TTgReplyKeyboardMarkupImpl }

function TTgReplyKeyboardMarkupImpl.WithKeyboard(const AValue: array of TArray<ITgKeyboardButton>): ITgReplyKeyboardMarkup;
begin
  SetObjects2('keyboard', TTgDto.ToIntf2<ITgKeyboardButton>(AValue));
  Result := Self;
end;

function TTgReplyKeyboardMarkupImpl.WithKeyboardRow(const ARow: array of ITgKeyboardButton): ITgReplyKeyboardMarkup;
begin
  AppendRow('keyboard', TTgDto.ToIntf<ITgKeyboardButton>(ARow));
  Result := Self;
end;

function TTgReplyKeyboardMarkupImpl.WithIsPersistent(AValue: Boolean): ITgReplyKeyboardMarkup;
begin
  SetBool('is_persistent', AValue);
  Result := Self;
end;

function TTgReplyKeyboardMarkupImpl.WithResizeKeyboard(AValue: Boolean): ITgReplyKeyboardMarkup;
begin
  SetBool('resize_keyboard', AValue);
  Result := Self;
end;

function TTgReplyKeyboardMarkupImpl.WithOneTimeKeyboard(AValue: Boolean): ITgReplyKeyboardMarkup;
begin
  SetBool('one_time_keyboard', AValue);
  Result := Self;
end;

function TTgReplyKeyboardMarkupImpl.WithInputFieldPlaceholder(const AValue: string): ITgReplyKeyboardMarkup;
begin
  SetStr('input_field_placeholder', AValue);
  Result := Self;
end;

function TTgReplyKeyboardMarkupImpl.WithSelective(AValue: Boolean): ITgReplyKeyboardMarkup;
begin
  SetBool('selective', AValue);
  Result := Self;
end;

function TTgReplyKeyboardMarkupImpl.WithForceReply(AValue: Boolean): ITgReplyKeyboardMarkup;
begin
  SetBool('force_reply', AValue);
  Result := Self;
end;

{ TTgKeyboardButtonImpl }

function TTgKeyboardButtonImpl.WithText(const AValue: string): ITgKeyboardButton;
begin
  SetStr('text', AValue);
  Result := Self;
end;

function TTgKeyboardButtonImpl.WithIconCustomEmojiId(const AValue: string): ITgKeyboardButton;
begin
  SetStr('icon_custom_emoji_id', AValue);
  Result := Self;
end;

function TTgKeyboardButtonImpl.WithStyle(const AValue: string): ITgKeyboardButton;
begin
  SetStr('style', AValue);
  Result := Self;
end;

function TTgKeyboardButtonImpl.WithRequestUsers(const AValue: ITgKeyboardButtonRequestUsers): ITgKeyboardButton;
begin
  SetObject('request_users', AValue);
  Result := Self;
end;

function TTgKeyboardButtonImpl.WithRequestChat(const AValue: ITgKeyboardButtonRequestChat): ITgKeyboardButton;
begin
  SetObject('request_chat', AValue);
  Result := Self;
end;

function TTgKeyboardButtonImpl.WithRequestManagedBot(const AValue: ITgKeyboardButtonRequestManagedBot): ITgKeyboardButton;
begin
  SetObject('request_managed_bot', AValue);
  Result := Self;
end;

function TTgKeyboardButtonImpl.WithRequestContact(AValue: Boolean): ITgKeyboardButton;
begin
  SetBool('request_contact', AValue);
  Result := Self;
end;

function TTgKeyboardButtonImpl.WithRequestLocation(AValue: Boolean): ITgKeyboardButton;
begin
  SetBool('request_location', AValue);
  Result := Self;
end;

function TTgKeyboardButtonImpl.WithRequestPoll(const AValue: ITgKeyboardButtonPollType): ITgKeyboardButton;
begin
  SetObject('request_poll', AValue);
  Result := Self;
end;

function TTgKeyboardButtonImpl.WithWebApp(const AValue: ITgWebAppInfo): ITgKeyboardButton;
begin
  SetObject('web_app', AValue);
  Result := Self;
end;

{ TTgKeyboardButtonRequestUsersImpl }

function TTgKeyboardButtonRequestUsersImpl.WithRequestId(AValue: Int64): ITgKeyboardButtonRequestUsers;
begin
  SetInt64('request_id', AValue);
  Result := Self;
end;

function TTgKeyboardButtonRequestUsersImpl.WithUserIsBot(AValue: Boolean): ITgKeyboardButtonRequestUsers;
begin
  SetBool('user_is_bot', AValue);
  Result := Self;
end;

function TTgKeyboardButtonRequestUsersImpl.WithUserIsPremium(AValue: Boolean): ITgKeyboardButtonRequestUsers;
begin
  SetBool('user_is_premium', AValue);
  Result := Self;
end;

function TTgKeyboardButtonRequestUsersImpl.WithMaxQuantity(AValue: Integer): ITgKeyboardButtonRequestUsers;
begin
  SetInt('max_quantity', AValue);
  Result := Self;
end;

function TTgKeyboardButtonRequestUsersImpl.WithRequestName(AValue: Boolean): ITgKeyboardButtonRequestUsers;
begin
  SetBool('request_name', AValue);
  Result := Self;
end;

function TTgKeyboardButtonRequestUsersImpl.WithRequestUsername(AValue: Boolean): ITgKeyboardButtonRequestUsers;
begin
  SetBool('request_username', AValue);
  Result := Self;
end;

function TTgKeyboardButtonRequestUsersImpl.WithRequestPhoto(AValue: Boolean): ITgKeyboardButtonRequestUsers;
begin
  SetBool('request_photo', AValue);
  Result := Self;
end;

{ TTgKeyboardButtonRequestChatImpl }

function TTgKeyboardButtonRequestChatImpl.WithRequestId(AValue: Int64): ITgKeyboardButtonRequestChat;
begin
  SetInt64('request_id', AValue);
  Result := Self;
end;

function TTgKeyboardButtonRequestChatImpl.WithChatIsChannel(AValue: Boolean): ITgKeyboardButtonRequestChat;
begin
  SetBool('chat_is_channel', AValue);
  Result := Self;
end;

function TTgKeyboardButtonRequestChatImpl.WithChatIsForum(AValue: Boolean): ITgKeyboardButtonRequestChat;
begin
  SetBool('chat_is_forum', AValue);
  Result := Self;
end;

function TTgKeyboardButtonRequestChatImpl.WithChatHasUsername(AValue: Boolean): ITgKeyboardButtonRequestChat;
begin
  SetBool('chat_has_username', AValue);
  Result := Self;
end;

function TTgKeyboardButtonRequestChatImpl.WithChatIsCreated(AValue: Boolean): ITgKeyboardButtonRequestChat;
begin
  SetBool('chat_is_created', AValue);
  Result := Self;
end;

function TTgKeyboardButtonRequestChatImpl.WithUserAdministratorRights(const AValue: ITgChatAdministratorRights): ITgKeyboardButtonRequestChat;
begin
  SetObject('user_administrator_rights', AValue);
  Result := Self;
end;

function TTgKeyboardButtonRequestChatImpl.WithBotAdministratorRights(const AValue: ITgChatAdministratorRights): ITgKeyboardButtonRequestChat;
begin
  SetObject('bot_administrator_rights', AValue);
  Result := Self;
end;

function TTgKeyboardButtonRequestChatImpl.WithBotIsMember(AValue: Boolean): ITgKeyboardButtonRequestChat;
begin
  SetBool('bot_is_member', AValue);
  Result := Self;
end;

function TTgKeyboardButtonRequestChatImpl.WithRequestTitle(AValue: Boolean): ITgKeyboardButtonRequestChat;
begin
  SetBool('request_title', AValue);
  Result := Self;
end;

function TTgKeyboardButtonRequestChatImpl.WithRequestUsername(AValue: Boolean): ITgKeyboardButtonRequestChat;
begin
  SetBool('request_username', AValue);
  Result := Self;
end;

function TTgKeyboardButtonRequestChatImpl.WithRequestPhoto(AValue: Boolean): ITgKeyboardButtonRequestChat;
begin
  SetBool('request_photo', AValue);
  Result := Self;
end;

{ TTgKeyboardButtonRequestManagedBotImpl }

function TTgKeyboardButtonRequestManagedBotImpl.WithRequestId(AValue: Int64): ITgKeyboardButtonRequestManagedBot;
begin
  SetInt64('request_id', AValue);
  Result := Self;
end;

function TTgKeyboardButtonRequestManagedBotImpl.WithSuggestedName(const AValue: string): ITgKeyboardButtonRequestManagedBot;
begin
  SetStr('suggested_name', AValue);
  Result := Self;
end;

function TTgKeyboardButtonRequestManagedBotImpl.WithSuggestedUsername(const AValue: string): ITgKeyboardButtonRequestManagedBot;
begin
  SetStr('suggested_username', AValue);
  Result := Self;
end;

{ TTgKeyboardButtonPollTypeImpl }

function TTgKeyboardButtonPollTypeImpl.WithKeyboardButtonPollTypeType(const AValue: string): ITgKeyboardButtonPollType;
begin
  SetStr('type', AValue);
  Result := Self;
end;

{ TTgReplyKeyboardRemoveImpl }

function TTgReplyKeyboardRemoveImpl.WithSelective(AValue: Boolean): ITgReplyKeyboardRemove;
begin
  SetBool('selective', AValue);
  Result := Self;
end;

{ TTgInlineKeyboardMarkupImpl }

function TTgInlineKeyboardMarkupImpl.GetInlineKeyboard: TArray<TArray<ITgInlineKeyboardButton>>;
begin
  Result := TTgDto.Objects2<ITgInlineKeyboardButton>(TTgJson.GetArr(FJson, 'inline_keyboard'), JsonOwner, TgMakeInlineKeyboardButton);
end;

function TTgInlineKeyboardMarkupImpl.GetForceReply: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'force_reply');
end;

function TTgInlineKeyboardMarkupImpl.GetHasForceReply: Boolean;
begin
  Result := TTgJson.Has(FJson, 'force_reply');
end;

function TTgInlineKeyboardMarkupImpl.WithInlineKeyboard(const AValue: array of TArray<ITgInlineKeyboardButton>): ITgInlineKeyboardMarkup;
begin
  SetObjects2('inline_keyboard', TTgDto.ToIntf2<ITgInlineKeyboardButton>(AValue));
  Result := Self;
end;

function TTgInlineKeyboardMarkupImpl.WithInlineKeyboardRow(const ARow: array of ITgInlineKeyboardButton): ITgInlineKeyboardMarkup;
begin
  AppendRow('inline_keyboard', TTgDto.ToIntf<ITgInlineKeyboardButton>(ARow));
  Result := Self;
end;

function TTgInlineKeyboardMarkupImpl.WithForceReply(AValue: Boolean): ITgInlineKeyboardMarkup;
begin
  SetBool('force_reply', AValue);
  Result := Self;
end;

{ TTgInlineKeyboardButtonImpl }

function TTgInlineKeyboardButtonImpl.GetText: string;
begin
  Result := TTgJson.GetStr(FJson, 'text');
end;

function TTgInlineKeyboardButtonImpl.GetIconCustomEmojiId: string;
begin
  Result := TTgJson.GetStr(FJson, 'icon_custom_emoji_id');
end;

function TTgInlineKeyboardButtonImpl.GetStyle: string;
begin
  Result := TTgJson.GetStr(FJson, 'style');
end;

function TTgInlineKeyboardButtonImpl.GetUrl: string;
begin
  Result := TTgJson.GetStr(FJson, 'url');
end;

function TTgInlineKeyboardButtonImpl.GetCallbackData: string;
begin
  Result := TTgJson.GetStr(FJson, 'callback_data');
end;

function TTgInlineKeyboardButtonImpl.GetWebApp: ITgWebAppInfo;
begin
  Result := TgMakeWebAppInfo(TTgJson.GetValue(FJson, 'web_app'), JsonOwner);
end;

function TTgInlineKeyboardButtonImpl.GetLoginUrl: ITgLoginUrl;
begin
  Result := TgMakeLoginUrl(TTgJson.GetValue(FJson, 'login_url'), JsonOwner);
end;

function TTgInlineKeyboardButtonImpl.GetSwitchInlineQuery: string;
begin
  Result := TTgJson.GetStr(FJson, 'switch_inline_query');
end;

function TTgInlineKeyboardButtonImpl.GetSwitchInlineQueryCurrentChat: string;
begin
  Result := TTgJson.GetStr(FJson, 'switch_inline_query_current_chat');
end;

function TTgInlineKeyboardButtonImpl.GetSwitchInlineQueryChosenChat: ITgSwitchInlineQueryChosenChat;
begin
  Result := TgMakeSwitchInlineQueryChosenChat(TTgJson.GetValue(FJson, 'switch_inline_query_chosen_chat'), JsonOwner);
end;

function TTgInlineKeyboardButtonImpl.GetCopyText: ITgCopyTextButton;
begin
  Result := TgMakeCopyTextButton(TTgJson.GetValue(FJson, 'copy_text'), JsonOwner);
end;

function TTgInlineKeyboardButtonImpl.GetCallbackGame: ITgCallbackGame;
begin
  Result := TgMakeCallbackGame(TTgJson.GetValue(FJson, 'callback_game'), JsonOwner);
end;

function TTgInlineKeyboardButtonImpl.GetPay: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'pay');
end;

function TTgInlineKeyboardButtonImpl.GetHasPay: Boolean;
begin
  Result := TTgJson.Has(FJson, 'pay');
end;

function TTgInlineKeyboardButtonImpl.GetDisabled: ITgDisabledButton;
begin
  Result := TgMakeDisabledButton(TTgJson.GetValue(FJson, 'disabled'), JsonOwner);
end;

function TTgInlineKeyboardButtonImpl.WithText(const AValue: string): ITgInlineKeyboardButton;
begin
  SetStr('text', AValue);
  Result := Self;
end;

function TTgInlineKeyboardButtonImpl.WithIconCustomEmojiId(const AValue: string): ITgInlineKeyboardButton;
begin
  SetStr('icon_custom_emoji_id', AValue);
  Result := Self;
end;

function TTgInlineKeyboardButtonImpl.WithStyle(const AValue: string): ITgInlineKeyboardButton;
begin
  SetStr('style', AValue);
  Result := Self;
end;

function TTgInlineKeyboardButtonImpl.WithUrl(const AValue: string): ITgInlineKeyboardButton;
begin
  SetStr('url', AValue);
  Result := Self;
end;

function TTgInlineKeyboardButtonImpl.WithCallbackData(const AValue: string): ITgInlineKeyboardButton;
begin
  SetStr('callback_data', AValue);
  Result := Self;
end;

function TTgInlineKeyboardButtonImpl.WithWebApp(const AValue: ITgWebAppInfo): ITgInlineKeyboardButton;
begin
  SetObject('web_app', AValue);
  Result := Self;
end;

function TTgInlineKeyboardButtonImpl.WithLoginUrl(const AValue: ITgLoginUrl): ITgInlineKeyboardButton;
begin
  SetObject('login_url', AValue);
  Result := Self;
end;

function TTgInlineKeyboardButtonImpl.WithSwitchInlineQuery(const AValue: string): ITgInlineKeyboardButton;
begin
  SetStr('switch_inline_query', AValue);
  Result := Self;
end;

function TTgInlineKeyboardButtonImpl.WithSwitchInlineQueryCurrentChat(const AValue: string): ITgInlineKeyboardButton;
begin
  SetStr('switch_inline_query_current_chat', AValue);
  Result := Self;
end;

function TTgInlineKeyboardButtonImpl.WithSwitchInlineQueryChosenChat(const AValue: ITgSwitchInlineQueryChosenChat): ITgInlineKeyboardButton;
begin
  SetObject('switch_inline_query_chosen_chat', AValue);
  Result := Self;
end;

function TTgInlineKeyboardButtonImpl.WithCopyText(const AValue: ITgCopyTextButton): ITgInlineKeyboardButton;
begin
  SetObject('copy_text', AValue);
  Result := Self;
end;

function TTgInlineKeyboardButtonImpl.WithCallbackGame(const AValue: ITgCallbackGame): ITgInlineKeyboardButton;
begin
  SetObject('callback_game', AValue);
  Result := Self;
end;

function TTgInlineKeyboardButtonImpl.WithPay(AValue: Boolean): ITgInlineKeyboardButton;
begin
  SetBool('pay', AValue);
  Result := Self;
end;

function TTgInlineKeyboardButtonImpl.WithDisabled(const AValue: ITgDisabledButton): ITgInlineKeyboardButton;
begin
  SetObject('disabled', AValue);
  Result := Self;
end;

{ TTgLoginUrlImpl }

function TTgLoginUrlImpl.GetUrl: string;
begin
  Result := TTgJson.GetStr(FJson, 'url');
end;

function TTgLoginUrlImpl.GetForwardText: string;
begin
  Result := TTgJson.GetStr(FJson, 'forward_text');
end;

function TTgLoginUrlImpl.GetBotUsername: string;
begin
  Result := TTgJson.GetStr(FJson, 'bot_username');
end;

function TTgLoginUrlImpl.GetRequestWriteAccess: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'request_write_access');
end;

function TTgLoginUrlImpl.GetHasRequestWriteAccess: Boolean;
begin
  Result := TTgJson.Has(FJson, 'request_write_access');
end;

function TTgLoginUrlImpl.WithUrl(const AValue: string): ITgLoginUrl;
begin
  SetStr('url', AValue);
  Result := Self;
end;

function TTgLoginUrlImpl.WithForwardText(const AValue: string): ITgLoginUrl;
begin
  SetStr('forward_text', AValue);
  Result := Self;
end;

function TTgLoginUrlImpl.WithBotUsername(const AValue: string): ITgLoginUrl;
begin
  SetStr('bot_username', AValue);
  Result := Self;
end;

function TTgLoginUrlImpl.WithRequestWriteAccess(AValue: Boolean): ITgLoginUrl;
begin
  SetBool('request_write_access', AValue);
  Result := Self;
end;

{ TTgSwitchInlineQueryChosenChatImpl }

function TTgSwitchInlineQueryChosenChatImpl.GetQuery: string;
begin
  Result := TTgJson.GetStr(FJson, 'query');
end;

function TTgSwitchInlineQueryChosenChatImpl.GetAllowUserChats: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'allow_user_chats');
end;

function TTgSwitchInlineQueryChosenChatImpl.GetHasAllowUserChats: Boolean;
begin
  Result := TTgJson.Has(FJson, 'allow_user_chats');
end;

function TTgSwitchInlineQueryChosenChatImpl.GetAllowBotChats: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'allow_bot_chats');
end;

function TTgSwitchInlineQueryChosenChatImpl.GetHasAllowBotChats: Boolean;
begin
  Result := TTgJson.Has(FJson, 'allow_bot_chats');
end;

function TTgSwitchInlineQueryChosenChatImpl.GetAllowGroupChats: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'allow_group_chats');
end;

function TTgSwitchInlineQueryChosenChatImpl.GetHasAllowGroupChats: Boolean;
begin
  Result := TTgJson.Has(FJson, 'allow_group_chats');
end;

function TTgSwitchInlineQueryChosenChatImpl.GetAllowChannelChats: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'allow_channel_chats');
end;

function TTgSwitchInlineQueryChosenChatImpl.GetHasAllowChannelChats: Boolean;
begin
  Result := TTgJson.Has(FJson, 'allow_channel_chats');
end;

function TTgSwitchInlineQueryChosenChatImpl.WithQuery(const AValue: string): ITgSwitchInlineQueryChosenChat;
begin
  SetStr('query', AValue);
  Result := Self;
end;

function TTgSwitchInlineQueryChosenChatImpl.WithAllowUserChats(AValue: Boolean): ITgSwitchInlineQueryChosenChat;
begin
  SetBool('allow_user_chats', AValue);
  Result := Self;
end;

function TTgSwitchInlineQueryChosenChatImpl.WithAllowBotChats(AValue: Boolean): ITgSwitchInlineQueryChosenChat;
begin
  SetBool('allow_bot_chats', AValue);
  Result := Self;
end;

function TTgSwitchInlineQueryChosenChatImpl.WithAllowGroupChats(AValue: Boolean): ITgSwitchInlineQueryChosenChat;
begin
  SetBool('allow_group_chats', AValue);
  Result := Self;
end;

function TTgSwitchInlineQueryChosenChatImpl.WithAllowChannelChats(AValue: Boolean): ITgSwitchInlineQueryChosenChat;
begin
  SetBool('allow_channel_chats', AValue);
  Result := Self;
end;

{ TTgCopyTextButtonImpl }

function TTgCopyTextButtonImpl.GetText: string;
begin
  Result := TTgJson.GetStr(FJson, 'text');
end;

function TTgCopyTextButtonImpl.WithText(const AValue: string): ITgCopyTextButton;
begin
  SetStr('text', AValue);
  Result := Self;
end;

{ TTgDisabledButtonImpl }

{ TTgCallbackQueryImpl }

function TTgCallbackQueryImpl.GetId: string;
begin
  Result := TTgJson.GetStr(FJson, 'id');
end;

function TTgCallbackQueryImpl.GetFrom: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'from'), JsonOwner);
end;

function TTgCallbackQueryImpl.GetMessage: ITgMaybeInaccessibleMessage;
begin
  Result := TgMakeMaybeInaccessibleMessage(TTgJson.GetValue(FJson, 'message'), JsonOwner);
end;

function TTgCallbackQueryImpl.GetInlineMessageId: string;
begin
  Result := TTgJson.GetStr(FJson, 'inline_message_id');
end;

function TTgCallbackQueryImpl.GetChatInstance: string;
begin
  Result := TTgJson.GetStr(FJson, 'chat_instance');
end;

function TTgCallbackQueryImpl.GetData: string;
begin
  Result := TTgJson.GetStr(FJson, 'data');
end;

function TTgCallbackQueryImpl.GetGameShortName: string;
begin
  Result := TTgJson.GetStr(FJson, 'game_short_name');
end;

{ TTgForceReplyImpl }

function TTgForceReplyImpl.WithInputFieldPlaceholder(const AValue: string): ITgForceReply;
begin
  SetStr('input_field_placeholder', AValue);
  Result := Self;
end;

function TTgForceReplyImpl.WithSelective(AValue: Boolean): ITgForceReply;
begin
  SetBool('selective', AValue);
  Result := Self;
end;

{ TTgCommunityImpl }

function TTgCommunityImpl.GetId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'id');
end;

function TTgCommunityImpl.GetName: string;
begin
  Result := TTgJson.GetStr(FJson, 'name');
end;

{ TTgChatPhotoImpl }

function TTgChatPhotoImpl.GetSmallFileId: string;
begin
  Result := TTgJson.GetStr(FJson, 'small_file_id');
end;

function TTgChatPhotoImpl.GetSmallFileUniqueId: string;
begin
  Result := TTgJson.GetStr(FJson, 'small_file_unique_id');
end;

function TTgChatPhotoImpl.GetBigFileId: string;
begin
  Result := TTgJson.GetStr(FJson, 'big_file_id');
end;

function TTgChatPhotoImpl.GetBigFileUniqueId: string;
begin
  Result := TTgJson.GetStr(FJson, 'big_file_unique_id');
end;

{ TTgChatInviteLinkImpl }

function TTgChatInviteLinkImpl.GetInviteLink: string;
begin
  Result := TTgJson.GetStr(FJson, 'invite_link');
end;

function TTgChatInviteLinkImpl.GetCreator: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'creator'), JsonOwner);
end;

function TTgChatInviteLinkImpl.GetCreatesJoinRequest: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'creates_join_request');
end;

function TTgChatInviteLinkImpl.GetIsPrimary: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_primary');
end;

function TTgChatInviteLinkImpl.GetIsRevoked: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_revoked');
end;

function TTgChatInviteLinkImpl.GetName: string;
begin
  Result := TTgJson.GetStr(FJson, 'name');
end;

function TTgChatInviteLinkImpl.GetExpireDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'expire_date');
end;

function TTgChatInviteLinkImpl.GetHasExpireDate: Boolean;
begin
  Result := TTgJson.Has(FJson, 'expire_date');
end;

function TTgChatInviteLinkImpl.GetMemberLimit: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'member_limit');
end;

function TTgChatInviteLinkImpl.GetHasMemberLimit: Boolean;
begin
  Result := TTgJson.Has(FJson, 'member_limit');
end;

function TTgChatInviteLinkImpl.GetPendingJoinRequestCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'pending_join_request_count');
end;

function TTgChatInviteLinkImpl.GetHasPendingJoinRequestCount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'pending_join_request_count');
end;

function TTgChatInviteLinkImpl.GetSubscriptionPeriod: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'subscription_period');
end;

function TTgChatInviteLinkImpl.GetHasSubscriptionPeriod: Boolean;
begin
  Result := TTgJson.Has(FJson, 'subscription_period');
end;

function TTgChatInviteLinkImpl.GetSubscriptionPrice: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'subscription_price');
end;

function TTgChatInviteLinkImpl.GetHasSubscriptionPrice: Boolean;
begin
  Result := TTgJson.Has(FJson, 'subscription_price');
end;

{ TTgChatAdministratorRightsImpl }

function TTgChatAdministratorRightsImpl.GetIsAnonymous: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_anonymous');
end;

function TTgChatAdministratorRightsImpl.GetCanManageChat: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_manage_chat');
end;

function TTgChatAdministratorRightsImpl.GetCanDeleteMessages: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_delete_messages');
end;

function TTgChatAdministratorRightsImpl.GetCanManageVideoChats: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_manage_video_chats');
end;

function TTgChatAdministratorRightsImpl.GetCanRestrictMembers: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_restrict_members');
end;

function TTgChatAdministratorRightsImpl.GetCanPromoteMembers: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_promote_members');
end;

function TTgChatAdministratorRightsImpl.GetCanChangeInfo: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_change_info');
end;

function TTgChatAdministratorRightsImpl.GetCanInviteUsers: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_invite_users');
end;

function TTgChatAdministratorRightsImpl.GetCanPostStories: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_post_stories');
end;

function TTgChatAdministratorRightsImpl.GetCanEditStories: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_edit_stories');
end;

function TTgChatAdministratorRightsImpl.GetCanDeleteStories: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_delete_stories');
end;

function TTgChatAdministratorRightsImpl.GetCanPostMessages: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_post_messages');
end;

function TTgChatAdministratorRightsImpl.GetHasCanPostMessages: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_post_messages');
end;

function TTgChatAdministratorRightsImpl.GetCanEditMessages: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_edit_messages');
end;

function TTgChatAdministratorRightsImpl.GetHasCanEditMessages: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_edit_messages');
end;

function TTgChatAdministratorRightsImpl.GetCanPinMessages: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_pin_messages');
end;

function TTgChatAdministratorRightsImpl.GetHasCanPinMessages: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_pin_messages');
end;

function TTgChatAdministratorRightsImpl.GetCanManageTopics: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_manage_topics');
end;

function TTgChatAdministratorRightsImpl.GetHasCanManageTopics: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_manage_topics');
end;

function TTgChatAdministratorRightsImpl.GetCanManageDirectMessages: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_manage_direct_messages');
end;

function TTgChatAdministratorRightsImpl.GetHasCanManageDirectMessages: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_manage_direct_messages');
end;

function TTgChatAdministratorRightsImpl.GetCanManageTags: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_manage_tags');
end;

function TTgChatAdministratorRightsImpl.GetHasCanManageTags: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_manage_tags');
end;

function TTgChatAdministratorRightsImpl.GetCanSendWelcomeMessages: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_send_welcome_messages');
end;

function TTgChatAdministratorRightsImpl.WithIsAnonymous(AValue: Boolean): ITgChatAdministratorRights;
begin
  SetBool('is_anonymous', AValue);
  Result := Self;
end;

function TTgChatAdministratorRightsImpl.WithCanManageChat(AValue: Boolean): ITgChatAdministratorRights;
begin
  SetBool('can_manage_chat', AValue);
  Result := Self;
end;

function TTgChatAdministratorRightsImpl.WithCanDeleteMessages(AValue: Boolean): ITgChatAdministratorRights;
begin
  SetBool('can_delete_messages', AValue);
  Result := Self;
end;

function TTgChatAdministratorRightsImpl.WithCanManageVideoChats(AValue: Boolean): ITgChatAdministratorRights;
begin
  SetBool('can_manage_video_chats', AValue);
  Result := Self;
end;

function TTgChatAdministratorRightsImpl.WithCanRestrictMembers(AValue: Boolean): ITgChatAdministratorRights;
begin
  SetBool('can_restrict_members', AValue);
  Result := Self;
end;

function TTgChatAdministratorRightsImpl.WithCanPromoteMembers(AValue: Boolean): ITgChatAdministratorRights;
begin
  SetBool('can_promote_members', AValue);
  Result := Self;
end;

function TTgChatAdministratorRightsImpl.WithCanChangeInfo(AValue: Boolean): ITgChatAdministratorRights;
begin
  SetBool('can_change_info', AValue);
  Result := Self;
end;

function TTgChatAdministratorRightsImpl.WithCanInviteUsers(AValue: Boolean): ITgChatAdministratorRights;
begin
  SetBool('can_invite_users', AValue);
  Result := Self;
end;

function TTgChatAdministratorRightsImpl.WithCanPostStories(AValue: Boolean): ITgChatAdministratorRights;
begin
  SetBool('can_post_stories', AValue);
  Result := Self;
end;

function TTgChatAdministratorRightsImpl.WithCanEditStories(AValue: Boolean): ITgChatAdministratorRights;
begin
  SetBool('can_edit_stories', AValue);
  Result := Self;
end;

function TTgChatAdministratorRightsImpl.WithCanDeleteStories(AValue: Boolean): ITgChatAdministratorRights;
begin
  SetBool('can_delete_stories', AValue);
  Result := Self;
end;

function TTgChatAdministratorRightsImpl.WithCanPostMessages(AValue: Boolean): ITgChatAdministratorRights;
begin
  SetBool('can_post_messages', AValue);
  Result := Self;
end;

function TTgChatAdministratorRightsImpl.WithCanEditMessages(AValue: Boolean): ITgChatAdministratorRights;
begin
  SetBool('can_edit_messages', AValue);
  Result := Self;
end;

function TTgChatAdministratorRightsImpl.WithCanPinMessages(AValue: Boolean): ITgChatAdministratorRights;
begin
  SetBool('can_pin_messages', AValue);
  Result := Self;
end;

function TTgChatAdministratorRightsImpl.WithCanManageTopics(AValue: Boolean): ITgChatAdministratorRights;
begin
  SetBool('can_manage_topics', AValue);
  Result := Self;
end;

function TTgChatAdministratorRightsImpl.WithCanManageDirectMessages(AValue: Boolean): ITgChatAdministratorRights;
begin
  SetBool('can_manage_direct_messages', AValue);
  Result := Self;
end;

function TTgChatAdministratorRightsImpl.WithCanManageTags(AValue: Boolean): ITgChatAdministratorRights;
begin
  SetBool('can_manage_tags', AValue);
  Result := Self;
end;

function TTgChatAdministratorRightsImpl.WithCanSendWelcomeMessages(AValue: Boolean): ITgChatAdministratorRights;
begin
  SetBool('can_send_welcome_messages', AValue);
  Result := Self;
end;

{ TTgChatMemberUpdatedImpl }

function TTgChatMemberUpdatedImpl.GetChat: ITgChat;
begin
  Result := TgMakeChat(TTgJson.GetValue(FJson, 'chat'), JsonOwner);
end;

function TTgChatMemberUpdatedImpl.GetFrom: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'from'), JsonOwner);
end;

function TTgChatMemberUpdatedImpl.GetDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'date');
end;

function TTgChatMemberUpdatedImpl.GetOldChatMember: ITgChatMember;
begin
  Result := TgMakeChatMember(TTgJson.GetValue(FJson, 'old_chat_member'), JsonOwner);
end;

function TTgChatMemberUpdatedImpl.GetNewChatMember: ITgChatMember;
begin
  Result := TgMakeChatMember(TTgJson.GetValue(FJson, 'new_chat_member'), JsonOwner);
end;

function TTgChatMemberUpdatedImpl.GetInviteLink: ITgChatInviteLink;
begin
  Result := TgMakeChatInviteLink(TTgJson.GetValue(FJson, 'invite_link'), JsonOwner);
end;

function TTgChatMemberUpdatedImpl.GetViaJoinRequest: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'via_join_request');
end;

function TTgChatMemberUpdatedImpl.GetHasViaJoinRequest: Boolean;
begin
  Result := TTgJson.Has(FJson, 'via_join_request');
end;

function TTgChatMemberUpdatedImpl.GetViaChatFolderInviteLink: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'via_chat_folder_invite_link');
end;

function TTgChatMemberUpdatedImpl.GetHasViaChatFolderInviteLink: Boolean;
begin
  Result := TTgJson.Has(FJson, 'via_chat_folder_invite_link');
end;

{ TTgChatMemberImpl }

function TTgChatMemberImpl.GetKind: TTgChatMemberKind;
begin
  Result := TTgChatMemberKind.Unknown;
end;

function TTgChatMemberImpl.GetKindText: string;
begin
  Result := TTgJson.GetStr(FJson, 'status');
end;

function TTgChatMemberImpl.GetStatus: string;
begin
  Result := TTgJson.GetStr(FJson, 'status');
end;

function TTgChatMemberImpl.GetUser: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'user'), JsonOwner);
end;

function TTgChatMemberImpl.AsOwner: ITgChatMemberOwner;
begin
  if not Supports(Self, ITgChatMemberOwner, Result) then
    Result := nil;
end;

function TTgChatMemberImpl.AsAdministrator: ITgChatMemberAdministrator;
begin
  if not Supports(Self, ITgChatMemberAdministrator, Result) then
    Result := nil;
end;

function TTgChatMemberImpl.AsMember: ITgChatMemberMember;
begin
  if not Supports(Self, ITgChatMemberMember, Result) then
    Result := nil;
end;

function TTgChatMemberImpl.AsRestricted: ITgChatMemberRestricted;
begin
  if not Supports(Self, ITgChatMemberRestricted, Result) then
    Result := nil;
end;

function TTgChatMemberImpl.AsLeft: ITgChatMemberLeft;
begin
  if not Supports(Self, ITgChatMemberLeft, Result) then
    Result := nil;
end;

function TTgChatMemberImpl.AsBanned: ITgChatMemberBanned;
begin
  if not Supports(Self, ITgChatMemberBanned, Result) then
    Result := nil;
end;

{ TTgChatMemberOwnerImpl }

function TTgChatMemberOwnerImpl.GetKind: TTgChatMemberKind;
begin
  Result := TTgChatMemberKind.Owner;
end;

function TTgChatMemberOwnerImpl.GetIsAnonymous: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_anonymous');
end;

function TTgChatMemberOwnerImpl.GetCustomTitle: string;
begin
  Result := TTgJson.GetStr(FJson, 'custom_title');
end;

{ TTgChatMemberAdministratorImpl }

function TTgChatMemberAdministratorImpl.GetKind: TTgChatMemberKind;
begin
  Result := TTgChatMemberKind.Administrator;
end;

function TTgChatMemberAdministratorImpl.GetCanBeEdited: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_be_edited');
end;

function TTgChatMemberAdministratorImpl.GetIsAnonymous: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_anonymous');
end;

function TTgChatMemberAdministratorImpl.GetCanManageChat: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_manage_chat');
end;

function TTgChatMemberAdministratorImpl.GetCanDeleteMessages: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_delete_messages');
end;

function TTgChatMemberAdministratorImpl.GetCanManageVideoChats: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_manage_video_chats');
end;

function TTgChatMemberAdministratorImpl.GetCanRestrictMembers: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_restrict_members');
end;

function TTgChatMemberAdministratorImpl.GetCanPromoteMembers: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_promote_members');
end;

function TTgChatMemberAdministratorImpl.GetCanChangeInfo: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_change_info');
end;

function TTgChatMemberAdministratorImpl.GetCanInviteUsers: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_invite_users');
end;

function TTgChatMemberAdministratorImpl.GetCanPostStories: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_post_stories');
end;

function TTgChatMemberAdministratorImpl.GetCanEditStories: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_edit_stories');
end;

function TTgChatMemberAdministratorImpl.GetCanDeleteStories: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_delete_stories');
end;

function TTgChatMemberAdministratorImpl.GetCanPostMessages: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_post_messages');
end;

function TTgChatMemberAdministratorImpl.GetHasCanPostMessages: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_post_messages');
end;

function TTgChatMemberAdministratorImpl.GetCanEditMessages: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_edit_messages');
end;

function TTgChatMemberAdministratorImpl.GetHasCanEditMessages: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_edit_messages');
end;

function TTgChatMemberAdministratorImpl.GetCanPinMessages: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_pin_messages');
end;

function TTgChatMemberAdministratorImpl.GetHasCanPinMessages: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_pin_messages');
end;

function TTgChatMemberAdministratorImpl.GetCanManageTopics: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_manage_topics');
end;

function TTgChatMemberAdministratorImpl.GetHasCanManageTopics: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_manage_topics');
end;

function TTgChatMemberAdministratorImpl.GetCanManageDirectMessages: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_manage_direct_messages');
end;

function TTgChatMemberAdministratorImpl.GetHasCanManageDirectMessages: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_manage_direct_messages');
end;

function TTgChatMemberAdministratorImpl.GetCanManageTags: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_manage_tags');
end;

function TTgChatMemberAdministratorImpl.GetHasCanManageTags: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_manage_tags');
end;

function TTgChatMemberAdministratorImpl.GetCanSendWelcomeMessages: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_send_welcome_messages');
end;

function TTgChatMemberAdministratorImpl.GetCustomTitle: string;
begin
  Result := TTgJson.GetStr(FJson, 'custom_title');
end;

{ TTgChatMemberMemberImpl }

function TTgChatMemberMemberImpl.GetKind: TTgChatMemberKind;
begin
  Result := TTgChatMemberKind.Member;
end;

function TTgChatMemberMemberImpl.GetTag: string;
begin
  Result := TTgJson.GetStr(FJson, 'tag');
end;

function TTgChatMemberMemberImpl.GetUntilDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'until_date');
end;

function TTgChatMemberMemberImpl.GetHasUntilDate: Boolean;
begin
  Result := TTgJson.Has(FJson, 'until_date');
end;

{ TTgChatMemberRestrictedImpl }

function TTgChatMemberRestrictedImpl.GetKind: TTgChatMemberKind;
begin
  Result := TTgChatMemberKind.Restricted;
end;

function TTgChatMemberRestrictedImpl.GetTag: string;
begin
  Result := TTgJson.GetStr(FJson, 'tag');
end;

function TTgChatMemberRestrictedImpl.GetIsMember: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_member');
end;

function TTgChatMemberRestrictedImpl.GetCanSendMessages: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_send_messages');
end;

function TTgChatMemberRestrictedImpl.GetCanSendAudios: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_send_audios');
end;

function TTgChatMemberRestrictedImpl.GetCanSendDocuments: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_send_documents');
end;

function TTgChatMemberRestrictedImpl.GetCanSendPhotos: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_send_photos');
end;

function TTgChatMemberRestrictedImpl.GetCanSendVideos: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_send_videos');
end;

function TTgChatMemberRestrictedImpl.GetCanSendVideoNotes: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_send_video_notes');
end;

function TTgChatMemberRestrictedImpl.GetCanSendVoiceNotes: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_send_voice_notes');
end;

function TTgChatMemberRestrictedImpl.GetCanSendPolls: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_send_polls');
end;

function TTgChatMemberRestrictedImpl.GetCanSendOtherMessages: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_send_other_messages');
end;

function TTgChatMemberRestrictedImpl.GetCanAddWebPagePreviews: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_add_web_page_previews');
end;

function TTgChatMemberRestrictedImpl.GetCanReactToMessages: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_react_to_messages');
end;

function TTgChatMemberRestrictedImpl.GetCanEditTag: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_edit_tag');
end;

function TTgChatMemberRestrictedImpl.GetCanChangeInfo: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_change_info');
end;

function TTgChatMemberRestrictedImpl.GetCanInviteUsers: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_invite_users');
end;

function TTgChatMemberRestrictedImpl.GetCanPinMessages: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_pin_messages');
end;

function TTgChatMemberRestrictedImpl.GetCanManageTopics: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_manage_topics');
end;

function TTgChatMemberRestrictedImpl.GetUntilDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'until_date');
end;

{ TTgChatMemberLeftImpl }

function TTgChatMemberLeftImpl.GetKind: TTgChatMemberKind;
begin
  Result := TTgChatMemberKind.Left;
end;

{ TTgChatMemberBannedImpl }

function TTgChatMemberBannedImpl.GetKind: TTgChatMemberKind;
begin
  Result := TTgChatMemberKind.Banned;
end;

function TTgChatMemberBannedImpl.GetUntilDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'until_date');
end;

{ TTgChatJoinRequestImpl }

function TTgChatJoinRequestImpl.GetChat: ITgChat;
begin
  Result := TgMakeChat(TTgJson.GetValue(FJson, 'chat'), JsonOwner);
end;

function TTgChatJoinRequestImpl.GetFrom: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'from'), JsonOwner);
end;

function TTgChatJoinRequestImpl.GetUserChatId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'user_chat_id');
end;

function TTgChatJoinRequestImpl.GetDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'date');
end;

function TTgChatJoinRequestImpl.GetBio: string;
begin
  Result := TTgJson.GetStr(FJson, 'bio');
end;

function TTgChatJoinRequestImpl.GetInviteLink: ITgChatInviteLink;
begin
  Result := TgMakeChatInviteLink(TTgJson.GetValue(FJson, 'invite_link'), JsonOwner);
end;

function TTgChatJoinRequestImpl.GetQueryId: string;
begin
  Result := TTgJson.GetStr(FJson, 'query_id');
end;

{ TTgChatPermissionsImpl }

function TTgChatPermissionsImpl.GetCanSendMessages: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_send_messages');
end;

function TTgChatPermissionsImpl.GetHasCanSendMessages: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_send_messages');
end;

function TTgChatPermissionsImpl.GetCanSendAudios: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_send_audios');
end;

function TTgChatPermissionsImpl.GetHasCanSendAudios: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_send_audios');
end;

function TTgChatPermissionsImpl.GetCanSendDocuments: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_send_documents');
end;

function TTgChatPermissionsImpl.GetHasCanSendDocuments: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_send_documents');
end;

function TTgChatPermissionsImpl.GetCanSendPhotos: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_send_photos');
end;

function TTgChatPermissionsImpl.GetHasCanSendPhotos: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_send_photos');
end;

function TTgChatPermissionsImpl.GetCanSendVideos: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_send_videos');
end;

function TTgChatPermissionsImpl.GetHasCanSendVideos: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_send_videos');
end;

function TTgChatPermissionsImpl.GetCanSendVideoNotes: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_send_video_notes');
end;

function TTgChatPermissionsImpl.GetHasCanSendVideoNotes: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_send_video_notes');
end;

function TTgChatPermissionsImpl.GetCanSendVoiceNotes: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_send_voice_notes');
end;

function TTgChatPermissionsImpl.GetHasCanSendVoiceNotes: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_send_voice_notes');
end;

function TTgChatPermissionsImpl.GetCanSendPolls: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_send_polls');
end;

function TTgChatPermissionsImpl.GetHasCanSendPolls: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_send_polls');
end;

function TTgChatPermissionsImpl.GetCanSendOtherMessages: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_send_other_messages');
end;

function TTgChatPermissionsImpl.GetHasCanSendOtherMessages: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_send_other_messages');
end;

function TTgChatPermissionsImpl.GetCanAddWebPagePreviews: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_add_web_page_previews');
end;

function TTgChatPermissionsImpl.GetHasCanAddWebPagePreviews: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_add_web_page_previews');
end;

function TTgChatPermissionsImpl.GetCanReactToMessages: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_react_to_messages');
end;

function TTgChatPermissionsImpl.GetHasCanReactToMessages: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_react_to_messages');
end;

function TTgChatPermissionsImpl.GetCanEditTag: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_edit_tag');
end;

function TTgChatPermissionsImpl.GetHasCanEditTag: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_edit_tag');
end;

function TTgChatPermissionsImpl.GetCanChangeInfo: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_change_info');
end;

function TTgChatPermissionsImpl.GetHasCanChangeInfo: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_change_info');
end;

function TTgChatPermissionsImpl.GetCanInviteUsers: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_invite_users');
end;

function TTgChatPermissionsImpl.GetHasCanInviteUsers: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_invite_users');
end;

function TTgChatPermissionsImpl.GetCanPinMessages: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_pin_messages');
end;

function TTgChatPermissionsImpl.GetHasCanPinMessages: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_pin_messages');
end;

function TTgChatPermissionsImpl.GetCanManageTopics: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_manage_topics');
end;

function TTgChatPermissionsImpl.GetHasCanManageTopics: Boolean;
begin
  Result := TTgJson.Has(FJson, 'can_manage_topics');
end;

function TTgChatPermissionsImpl.WithCanSendMessages(AValue: Boolean): ITgChatPermissions;
begin
  SetBool('can_send_messages', AValue);
  Result := Self;
end;

function TTgChatPermissionsImpl.WithCanSendAudios(AValue: Boolean): ITgChatPermissions;
begin
  SetBool('can_send_audios', AValue);
  Result := Self;
end;

function TTgChatPermissionsImpl.WithCanSendDocuments(AValue: Boolean): ITgChatPermissions;
begin
  SetBool('can_send_documents', AValue);
  Result := Self;
end;

function TTgChatPermissionsImpl.WithCanSendPhotos(AValue: Boolean): ITgChatPermissions;
begin
  SetBool('can_send_photos', AValue);
  Result := Self;
end;

function TTgChatPermissionsImpl.WithCanSendVideos(AValue: Boolean): ITgChatPermissions;
begin
  SetBool('can_send_videos', AValue);
  Result := Self;
end;

function TTgChatPermissionsImpl.WithCanSendVideoNotes(AValue: Boolean): ITgChatPermissions;
begin
  SetBool('can_send_video_notes', AValue);
  Result := Self;
end;

function TTgChatPermissionsImpl.WithCanSendVoiceNotes(AValue: Boolean): ITgChatPermissions;
begin
  SetBool('can_send_voice_notes', AValue);
  Result := Self;
end;

function TTgChatPermissionsImpl.WithCanSendPolls(AValue: Boolean): ITgChatPermissions;
begin
  SetBool('can_send_polls', AValue);
  Result := Self;
end;

function TTgChatPermissionsImpl.WithCanSendOtherMessages(AValue: Boolean): ITgChatPermissions;
begin
  SetBool('can_send_other_messages', AValue);
  Result := Self;
end;

function TTgChatPermissionsImpl.WithCanAddWebPagePreviews(AValue: Boolean): ITgChatPermissions;
begin
  SetBool('can_add_web_page_previews', AValue);
  Result := Self;
end;

function TTgChatPermissionsImpl.WithCanReactToMessages(AValue: Boolean): ITgChatPermissions;
begin
  SetBool('can_react_to_messages', AValue);
  Result := Self;
end;

function TTgChatPermissionsImpl.WithCanEditTag(AValue: Boolean): ITgChatPermissions;
begin
  SetBool('can_edit_tag', AValue);
  Result := Self;
end;

function TTgChatPermissionsImpl.WithCanChangeInfo(AValue: Boolean): ITgChatPermissions;
begin
  SetBool('can_change_info', AValue);
  Result := Self;
end;

function TTgChatPermissionsImpl.WithCanInviteUsers(AValue: Boolean): ITgChatPermissions;
begin
  SetBool('can_invite_users', AValue);
  Result := Self;
end;

function TTgChatPermissionsImpl.WithCanPinMessages(AValue: Boolean): ITgChatPermissions;
begin
  SetBool('can_pin_messages', AValue);
  Result := Self;
end;

function TTgChatPermissionsImpl.WithCanManageTopics(AValue: Boolean): ITgChatPermissions;
begin
  SetBool('can_manage_topics', AValue);
  Result := Self;
end;

{ TTgBirthdateImpl }

function TTgBirthdateImpl.GetDay: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'day');
end;

function TTgBirthdateImpl.GetMonth: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'month');
end;

function TTgBirthdateImpl.GetYear: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'year');
end;

function TTgBirthdateImpl.GetHasYear: Boolean;
begin
  Result := TTgJson.Has(FJson, 'year');
end;

{ TTgBusinessIntroImpl }

function TTgBusinessIntroImpl.GetTitle: string;
begin
  Result := TTgJson.GetStr(FJson, 'title');
end;

function TTgBusinessIntroImpl.GetMessage: string;
begin
  Result := TTgJson.GetStr(FJson, 'message');
end;

function TTgBusinessIntroImpl.GetSticker: ITgSticker;
begin
  Result := TgMakeSticker(TTgJson.GetValue(FJson, 'sticker'), JsonOwner);
end;

{ TTgBusinessLocationImpl }

function TTgBusinessLocationImpl.GetAddress: string;
begin
  Result := TTgJson.GetStr(FJson, 'address');
end;

function TTgBusinessLocationImpl.GetLocation: ITgLocation;
begin
  Result := TgMakeLocation(TTgJson.GetValue(FJson, 'location'), JsonOwner);
end;

{ TTgBusinessOpeningHoursIntervalImpl }

function TTgBusinessOpeningHoursIntervalImpl.GetOpeningMinute: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'opening_minute');
end;

function TTgBusinessOpeningHoursIntervalImpl.GetClosingMinute: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'closing_minute');
end;

{ TTgBusinessOpeningHoursImpl }

function TTgBusinessOpeningHoursImpl.GetTimeZoneName: string;
begin
  Result := TTgJson.GetStr(FJson, 'time_zone_name');
end;

function TTgBusinessOpeningHoursImpl.GetOpeningHours: TArray<ITgBusinessOpeningHoursInterval>;
begin
  Result := TTgDto.Objects<ITgBusinessOpeningHoursInterval>(TTgJson.GetArr(FJson, 'opening_hours'), JsonOwner, TgMakeBusinessOpeningHoursInterval);
end;

{ TTgUserRatingImpl }

function TTgUserRatingImpl.GetLevel: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'level');
end;

function TTgUserRatingImpl.GetRating: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'rating');
end;

function TTgUserRatingImpl.GetCurrentLevelRating: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'current_level_rating');
end;

function TTgUserRatingImpl.GetNextLevelRating: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'next_level_rating');
end;

function TTgUserRatingImpl.GetHasNextLevelRating: Boolean;
begin
  Result := TTgJson.Has(FJson, 'next_level_rating');
end;

{ TTgStoryAreaPositionImpl }

function TTgStoryAreaPositionImpl.WithXPercentage(AValue: Double): ITgStoryAreaPosition;
begin
  SetDouble('x_percentage', AValue);
  Result := Self;
end;

function TTgStoryAreaPositionImpl.WithYPercentage(AValue: Double): ITgStoryAreaPosition;
begin
  SetDouble('y_percentage', AValue);
  Result := Self;
end;

function TTgStoryAreaPositionImpl.WithWidthPercentage(AValue: Double): ITgStoryAreaPosition;
begin
  SetDouble('width_percentage', AValue);
  Result := Self;
end;

function TTgStoryAreaPositionImpl.WithHeightPercentage(AValue: Double): ITgStoryAreaPosition;
begin
  SetDouble('height_percentage', AValue);
  Result := Self;
end;

function TTgStoryAreaPositionImpl.WithRotationAngle(AValue: Double): ITgStoryAreaPosition;
begin
  SetDouble('rotation_angle', AValue);
  Result := Self;
end;

function TTgStoryAreaPositionImpl.WithCornerRadiusPercentage(AValue: Double): ITgStoryAreaPosition;
begin
  SetDouble('corner_radius_percentage', AValue);
  Result := Self;
end;

{ TTgLocationAddressImpl }

function TTgLocationAddressImpl.WithCountryCode(const AValue: string): ITgLocationAddress;
begin
  SetStr('country_code', AValue);
  Result := Self;
end;

function TTgLocationAddressImpl.WithState(const AValue: string): ITgLocationAddress;
begin
  SetStr('state', AValue);
  Result := Self;
end;

function TTgLocationAddressImpl.WithCity(const AValue: string): ITgLocationAddress;
begin
  SetStr('city', AValue);
  Result := Self;
end;

function TTgLocationAddressImpl.WithStreet(const AValue: string): ITgLocationAddress;
begin
  SetStr('street', AValue);
  Result := Self;
end;

{ TTgStoryAreaTypeLocationImpl }

function TTgStoryAreaTypeLocationImpl.WithLatitude(AValue: Double): ITgStoryAreaTypeLocation;
begin
  SetDouble('latitude', AValue);
  Result := Self;
end;

function TTgStoryAreaTypeLocationImpl.WithLongitude(AValue: Double): ITgStoryAreaTypeLocation;
begin
  SetDouble('longitude', AValue);
  Result := Self;
end;

function TTgStoryAreaTypeLocationImpl.WithAddress(const AValue: ITgLocationAddress): ITgStoryAreaTypeLocation;
begin
  SetObject('address', AValue);
  Result := Self;
end;

{ TTgStoryAreaTypeSuggestedReactionImpl }

function TTgStoryAreaTypeSuggestedReactionImpl.WithReactionType(const AValue: ITgReactionType): ITgStoryAreaTypeSuggestedReaction;
begin
  SetObject('reaction_type', AValue);
  Result := Self;
end;

function TTgStoryAreaTypeSuggestedReactionImpl.WithIsDark(AValue: Boolean): ITgStoryAreaTypeSuggestedReaction;
begin
  SetBool('is_dark', AValue);
  Result := Self;
end;

function TTgStoryAreaTypeSuggestedReactionImpl.WithIsFlipped(AValue: Boolean): ITgStoryAreaTypeSuggestedReaction;
begin
  SetBool('is_flipped', AValue);
  Result := Self;
end;

{ TTgStoryAreaTypeLinkImpl }

function TTgStoryAreaTypeLinkImpl.WithUrl(const AValue: string): ITgStoryAreaTypeLink;
begin
  SetStr('url', AValue);
  Result := Self;
end;

{ TTgStoryAreaTypeWeatherImpl }

function TTgStoryAreaTypeWeatherImpl.WithTemperature(AValue: Double): ITgStoryAreaTypeWeather;
begin
  SetDouble('temperature', AValue);
  Result := Self;
end;

function TTgStoryAreaTypeWeatherImpl.WithEmoji(const AValue: string): ITgStoryAreaTypeWeather;
begin
  SetStr('emoji', AValue);
  Result := Self;
end;

function TTgStoryAreaTypeWeatherImpl.WithBackgroundColor(AValue: Integer): ITgStoryAreaTypeWeather;
begin
  SetInt('background_color', AValue);
  Result := Self;
end;

{ TTgStoryAreaTypeUniqueGiftImpl }

function TTgStoryAreaTypeUniqueGiftImpl.WithName(const AValue: string): ITgStoryAreaTypeUniqueGift;
begin
  SetStr('name', AValue);
  Result := Self;
end;

{ TTgStoryAreaImpl }

function TTgStoryAreaImpl.WithPosition(const AValue: ITgStoryAreaPosition): ITgStoryArea;
begin
  SetObject('position', AValue);
  Result := Self;
end;

function TTgStoryAreaImpl.WithStoryAreaType(const AValue: TTgStoryAreaType): ITgStoryArea;
begin
  SetObject('type', AValue.Value);
  Result := Self;
end;

{ TTgChatLocationImpl }

function TTgChatLocationImpl.GetLocation: ITgLocation;
begin
  Result := TgMakeLocation(TTgJson.GetValue(FJson, 'location'), JsonOwner);
end;

function TTgChatLocationImpl.GetAddress: string;
begin
  Result := TTgJson.GetStr(FJson, 'address');
end;

{ TTgReactionTypeImpl }

function TTgReactionTypeImpl.GetKind: TTgReactionTypeKind;
begin
  Result := TTgReactionTypeKind.Unknown;
end;

function TTgReactionTypeImpl.GetKindText: string;
begin
  Result := TTgJson.GetStr(FJson, 'type');
end;

function TTgReactionTypeImpl.AsEmoji: ITgReactionTypeEmoji;
begin
  if not Supports(Self, ITgReactionTypeEmoji, Result) then
    Result := nil;
end;

function TTgReactionTypeImpl.AsCustomEmoji: ITgReactionTypeCustomEmoji;
begin
  if not Supports(Self, ITgReactionTypeCustomEmoji, Result) then
    Result := nil;
end;

function TTgReactionTypeImpl.AsPaid: ITgReactionTypePaid;
begin
  if not Supports(Self, ITgReactionTypePaid, Result) then
    Result := nil;
end;

{ TTgReactionTypeEmojiImpl }

function TTgReactionTypeEmojiImpl.GetKind: TTgReactionTypeKind;
begin
  Result := TTgReactionTypeKind.Emoji;
end;

function TTgReactionTypeEmojiImpl.GetEmoji: string;
begin
  Result := TTgJson.GetStr(FJson, 'emoji');
end;

function TTgReactionTypeEmojiImpl.WithEmoji(const AValue: string): ITgReactionTypeEmoji;
begin
  SetStr('emoji', AValue);
  Result := Self;
end;

{ TTgReactionTypeCustomEmojiImpl }

function TTgReactionTypeCustomEmojiImpl.GetKind: TTgReactionTypeKind;
begin
  Result := TTgReactionTypeKind.CustomEmoji;
end;

function TTgReactionTypeCustomEmojiImpl.GetCustomEmojiId: string;
begin
  Result := TTgJson.GetStr(FJson, 'custom_emoji_id');
end;

function TTgReactionTypeCustomEmojiImpl.WithCustomEmojiId(const AValue: string): ITgReactionTypeCustomEmoji;
begin
  SetStr('custom_emoji_id', AValue);
  Result := Self;
end;

{ TTgReactionTypePaidImpl }

function TTgReactionTypePaidImpl.GetKind: TTgReactionTypeKind;
begin
  Result := TTgReactionTypeKind.Paid;
end;

{ TTgReactionCountImpl }

function TTgReactionCountImpl.GetReactionCountType: ITgReactionType;
begin
  Result := TgMakeReactionType(TTgJson.GetValue(FJson, 'type'), JsonOwner);
end;

function TTgReactionCountImpl.GetTotalCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'total_count');
end;

{ TTgMessageReactionUpdatedImpl }

function TTgMessageReactionUpdatedImpl.GetChat: ITgChat;
begin
  Result := TgMakeChat(TTgJson.GetValue(FJson, 'chat'), JsonOwner);
end;

function TTgMessageReactionUpdatedImpl.GetMessageId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'message_id');
end;

function TTgMessageReactionUpdatedImpl.GetUser: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'user'), JsonOwner);
end;

function TTgMessageReactionUpdatedImpl.GetActorChat: ITgChat;
begin
  Result := TgMakeChat(TTgJson.GetValue(FJson, 'actor_chat'), JsonOwner);
end;

function TTgMessageReactionUpdatedImpl.GetDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'date');
end;

function TTgMessageReactionUpdatedImpl.GetOldReaction: TArray<ITgReactionType>;
begin
  Result := TTgDto.Objects<ITgReactionType>(TTgJson.GetArr(FJson, 'old_reaction'), JsonOwner, TgMakeReactionType);
end;

function TTgMessageReactionUpdatedImpl.GetNewReaction: TArray<ITgReactionType>;
begin
  Result := TTgDto.Objects<ITgReactionType>(TTgJson.GetArr(FJson, 'new_reaction'), JsonOwner, TgMakeReactionType);
end;

{ TTgMessageReactionCountUpdatedImpl }

function TTgMessageReactionCountUpdatedImpl.GetChat: ITgChat;
begin
  Result := TgMakeChat(TTgJson.GetValue(FJson, 'chat'), JsonOwner);
end;

function TTgMessageReactionCountUpdatedImpl.GetMessageId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'message_id');
end;

function TTgMessageReactionCountUpdatedImpl.GetDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'date');
end;

function TTgMessageReactionCountUpdatedImpl.GetReactions: TArray<ITgReactionCount>;
begin
  Result := TTgDto.Objects<ITgReactionCount>(TTgJson.GetArr(FJson, 'reactions'), JsonOwner, TgMakeReactionCount);
end;

{ TTgForumTopicImpl }

function TTgForumTopicImpl.GetMessageThreadId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'message_thread_id');
end;

function TTgForumTopicImpl.GetName: string;
begin
  Result := TTgJson.GetStr(FJson, 'name');
end;

function TTgForumTopicImpl.GetIconColor: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'icon_color');
end;

function TTgForumTopicImpl.GetIconCustomEmojiId: string;
begin
  Result := TTgJson.GetStr(FJson, 'icon_custom_emoji_id');
end;

function TTgForumTopicImpl.GetIsNameImplicit: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_name_implicit');
end;

{ TTgGiftBackgroundImpl }

function TTgGiftBackgroundImpl.GetCenterColor: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'center_color');
end;

function TTgGiftBackgroundImpl.GetEdgeColor: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'edge_color');
end;

function TTgGiftBackgroundImpl.GetTextColor: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'text_color');
end;

{ TTgGiftImpl }

function TTgGiftImpl.GetId: string;
begin
  Result := TTgJson.GetStr(FJson, 'id');
end;

function TTgGiftImpl.GetSticker: ITgSticker;
begin
  Result := TgMakeSticker(TTgJson.GetValue(FJson, 'sticker'), JsonOwner);
end;

function TTgGiftImpl.GetStarCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'star_count');
end;

function TTgGiftImpl.GetUpgradeStarCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'upgrade_star_count');
end;

function TTgGiftImpl.GetHasUpgradeStarCount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'upgrade_star_count');
end;

function TTgGiftImpl.GetIsPremium: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_premium');
end;

function TTgGiftImpl.GetHasColors: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'has_colors');
end;

function TTgGiftImpl.GetTotalCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'total_count');
end;

function TTgGiftImpl.GetHasTotalCount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'total_count');
end;

function TTgGiftImpl.GetRemainingCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'remaining_count');
end;

function TTgGiftImpl.GetHasRemainingCount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'remaining_count');
end;

function TTgGiftImpl.GetPersonalTotalCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'personal_total_count');
end;

function TTgGiftImpl.GetHasPersonalTotalCount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'personal_total_count');
end;

function TTgGiftImpl.GetPersonalRemainingCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'personal_remaining_count');
end;

function TTgGiftImpl.GetHasPersonalRemainingCount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'personal_remaining_count');
end;

function TTgGiftImpl.GetBackground: ITgGiftBackground;
begin
  Result := TgMakeGiftBackground(TTgJson.GetValue(FJson, 'background'), JsonOwner);
end;

function TTgGiftImpl.GetUniqueGiftVariantCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'unique_gift_variant_count');
end;

function TTgGiftImpl.GetHasUniqueGiftVariantCount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'unique_gift_variant_count');
end;

function TTgGiftImpl.GetPublisherChat: ITgChat;
begin
  Result := TgMakeChat(TTgJson.GetValue(FJson, 'publisher_chat'), JsonOwner);
end;

{ TTgGiftsImpl }

function TTgGiftsImpl.GetGifts: TArray<ITgGift>;
begin
  Result := TTgDto.Objects<ITgGift>(TTgJson.GetArr(FJson, 'gifts'), JsonOwner, TgMakeGift);
end;

{ TTgUniqueGiftModelImpl }

function TTgUniqueGiftModelImpl.GetName: string;
begin
  Result := TTgJson.GetStr(FJson, 'name');
end;

function TTgUniqueGiftModelImpl.GetSticker: ITgSticker;
begin
  Result := TgMakeSticker(TTgJson.GetValue(FJson, 'sticker'), JsonOwner);
end;

function TTgUniqueGiftModelImpl.GetRarityPerMille: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'rarity_per_mille');
end;

function TTgUniqueGiftModelImpl.GetRarity: string;
begin
  Result := TTgJson.GetStr(FJson, 'rarity');
end;

{ TTgUniqueGiftSymbolImpl }

function TTgUniqueGiftSymbolImpl.GetName: string;
begin
  Result := TTgJson.GetStr(FJson, 'name');
end;

function TTgUniqueGiftSymbolImpl.GetSticker: ITgSticker;
begin
  Result := TgMakeSticker(TTgJson.GetValue(FJson, 'sticker'), JsonOwner);
end;

function TTgUniqueGiftSymbolImpl.GetRarityPerMille: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'rarity_per_mille');
end;

{ TTgUniqueGiftBackdropColorsImpl }

function TTgUniqueGiftBackdropColorsImpl.GetCenterColor: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'center_color');
end;

function TTgUniqueGiftBackdropColorsImpl.GetEdgeColor: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'edge_color');
end;

function TTgUniqueGiftBackdropColorsImpl.GetSymbolColor: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'symbol_color');
end;

function TTgUniqueGiftBackdropColorsImpl.GetTextColor: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'text_color');
end;

{ TTgUniqueGiftBackdropImpl }

function TTgUniqueGiftBackdropImpl.GetName: string;
begin
  Result := TTgJson.GetStr(FJson, 'name');
end;

function TTgUniqueGiftBackdropImpl.GetColors: ITgUniqueGiftBackdropColors;
begin
  Result := TgMakeUniqueGiftBackdropColors(TTgJson.GetValue(FJson, 'colors'), JsonOwner);
end;

function TTgUniqueGiftBackdropImpl.GetRarityPerMille: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'rarity_per_mille');
end;

{ TTgUniqueGiftColorsImpl }

function TTgUniqueGiftColorsImpl.GetModelCustomEmojiId: string;
begin
  Result := TTgJson.GetStr(FJson, 'model_custom_emoji_id');
end;

function TTgUniqueGiftColorsImpl.GetSymbolCustomEmojiId: string;
begin
  Result := TTgJson.GetStr(FJson, 'symbol_custom_emoji_id');
end;

function TTgUniqueGiftColorsImpl.GetLightThemeMainColor: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'light_theme_main_color');
end;

function TTgUniqueGiftColorsImpl.GetLightThemeOtherColors: TArray<Integer>;
begin
  Result := TTgDto.Integers(TTgJson.GetArr(FJson, 'light_theme_other_colors'), 'light_theme_other_colors');
end;

function TTgUniqueGiftColorsImpl.GetDarkThemeMainColor: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'dark_theme_main_color');
end;

function TTgUniqueGiftColorsImpl.GetDarkThemeOtherColors: TArray<Integer>;
begin
  Result := TTgDto.Integers(TTgJson.GetArr(FJson, 'dark_theme_other_colors'), 'dark_theme_other_colors');
end;

{ TTgUniqueGiftImpl }

function TTgUniqueGiftImpl.GetGiftId: string;
begin
  Result := TTgJson.GetStr(FJson, 'gift_id');
end;

function TTgUniqueGiftImpl.GetBaseName: string;
begin
  Result := TTgJson.GetStr(FJson, 'base_name');
end;

function TTgUniqueGiftImpl.GetName: string;
begin
  Result := TTgJson.GetStr(FJson, 'name');
end;

function TTgUniqueGiftImpl.GetNumber: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'number');
end;

function TTgUniqueGiftImpl.GetModel: ITgUniqueGiftModel;
begin
  Result := TgMakeUniqueGiftModel(TTgJson.GetValue(FJson, 'model'), JsonOwner);
end;

function TTgUniqueGiftImpl.GetSymbol: ITgUniqueGiftSymbol;
begin
  Result := TgMakeUniqueGiftSymbol(TTgJson.GetValue(FJson, 'symbol'), JsonOwner);
end;

function TTgUniqueGiftImpl.GetBackdrop: ITgUniqueGiftBackdrop;
begin
  Result := TgMakeUniqueGiftBackdrop(TTgJson.GetValue(FJson, 'backdrop'), JsonOwner);
end;

function TTgUniqueGiftImpl.GetIsPremium: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_premium');
end;

function TTgUniqueGiftImpl.GetIsBurned: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_burned');
end;

function TTgUniqueGiftImpl.GetIsFromBlockchain: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_from_blockchain');
end;

function TTgUniqueGiftImpl.GetColors: ITgUniqueGiftColors;
begin
  Result := TgMakeUniqueGiftColors(TTgJson.GetValue(FJson, 'colors'), JsonOwner);
end;

function TTgUniqueGiftImpl.GetPublisherChat: ITgChat;
begin
  Result := TgMakeChat(TTgJson.GetValue(FJson, 'publisher_chat'), JsonOwner);
end;

{ TTgGiftInfoImpl }

function TTgGiftInfoImpl.GetGift: ITgGift;
begin
  Result := TgMakeGift(TTgJson.GetValue(FJson, 'gift'), JsonOwner);
end;

function TTgGiftInfoImpl.GetOwnedGiftId: string;
begin
  Result := TTgJson.GetStr(FJson, 'owned_gift_id');
end;

function TTgGiftInfoImpl.GetConvertStarCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'convert_star_count');
end;

function TTgGiftInfoImpl.GetHasConvertStarCount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'convert_star_count');
end;

function TTgGiftInfoImpl.GetPrepaidUpgradeStarCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'prepaid_upgrade_star_count');
end;

function TTgGiftInfoImpl.GetHasPrepaidUpgradeStarCount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'prepaid_upgrade_star_count');
end;

function TTgGiftInfoImpl.GetIsUpgradeSeparate: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_upgrade_separate');
end;

function TTgGiftInfoImpl.GetCanBeUpgraded: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_be_upgraded');
end;

function TTgGiftInfoImpl.GetText: string;
begin
  Result := TTgJson.GetStr(FJson, 'text');
end;

function TTgGiftInfoImpl.GetEntities: TArray<ITgMessageEntity>;
begin
  Result := TTgDto.Objects<ITgMessageEntity>(TTgJson.GetArr(FJson, 'entities'), JsonOwner, TgMakeMessageEntity);
end;

function TTgGiftInfoImpl.GetIsPrivate: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_private');
end;

function TTgGiftInfoImpl.GetUniqueGiftNumber: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'unique_gift_number');
end;

function TTgGiftInfoImpl.GetHasUniqueGiftNumber: Boolean;
begin
  Result := TTgJson.Has(FJson, 'unique_gift_number');
end;

{ TTgUniqueGiftInfoImpl }

function TTgUniqueGiftInfoImpl.GetGift: ITgUniqueGift;
begin
  Result := TgMakeUniqueGift(TTgJson.GetValue(FJson, 'gift'), JsonOwner);
end;

function TTgUniqueGiftInfoImpl.GetOrigin: string;
begin
  Result := TTgJson.GetStr(FJson, 'origin');
end;

function TTgUniqueGiftInfoImpl.GetText: string;
begin
  Result := TTgJson.GetStr(FJson, 'text');
end;

function TTgUniqueGiftInfoImpl.GetEntities: TArray<ITgMessageEntity>;
begin
  Result := TTgDto.Objects<ITgMessageEntity>(TTgJson.GetArr(FJson, 'entities'), JsonOwner, TgMakeMessageEntity);
end;

function TTgUniqueGiftInfoImpl.GetIsPrivate: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_private');
end;

function TTgUniqueGiftInfoImpl.GetLastResaleCurrency: string;
begin
  Result := TTgJson.GetStr(FJson, 'last_resale_currency');
end;

function TTgUniqueGiftInfoImpl.GetLastResaleAmount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'last_resale_amount');
end;

function TTgUniqueGiftInfoImpl.GetHasLastResaleAmount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'last_resale_amount');
end;

function TTgUniqueGiftInfoImpl.GetOwnedGiftId: string;
begin
  Result := TTgJson.GetStr(FJson, 'owned_gift_id');
end;

function TTgUniqueGiftInfoImpl.GetTransferStarCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'transfer_star_count');
end;

function TTgUniqueGiftInfoImpl.GetHasTransferStarCount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'transfer_star_count');
end;

function TTgUniqueGiftInfoImpl.GetNextTransferDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'next_transfer_date');
end;

function TTgUniqueGiftInfoImpl.GetHasNextTransferDate: Boolean;
begin
  Result := TTgJson.Has(FJson, 'next_transfer_date');
end;

{ TTgOwnedGiftImpl }

function TTgOwnedGiftImpl.GetKind: TTgOwnedGiftKind;
begin
  Result := TTgOwnedGiftKind.Unknown;
end;

function TTgOwnedGiftImpl.GetKindText: string;
begin
  Result := TTgJson.GetStr(FJson, 'type');
end;

function TTgOwnedGiftImpl.GetOwnedGiftId: string;
begin
  Result := TTgJson.GetStr(FJson, 'owned_gift_id');
end;

function TTgOwnedGiftImpl.GetSenderUser: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'sender_user'), JsonOwner);
end;

function TTgOwnedGiftImpl.GetSendDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'send_date');
end;

function TTgOwnedGiftImpl.GetIsSaved: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_saved');
end;

function TTgOwnedGiftImpl.AsRegular: ITgOwnedGiftRegular;
begin
  if not Supports(Self, ITgOwnedGiftRegular, Result) then
    Result := nil;
end;

function TTgOwnedGiftImpl.AsUnique: ITgOwnedGiftUnique;
begin
  if not Supports(Self, ITgOwnedGiftUnique, Result) then
    Result := nil;
end;

{ TTgOwnedGiftRegularImpl }

function TTgOwnedGiftRegularImpl.GetKind: TTgOwnedGiftKind;
begin
  Result := TTgOwnedGiftKind.Regular;
end;

function TTgOwnedGiftRegularImpl.GetGift: ITgGift;
begin
  Result := TgMakeGift(TTgJson.GetValue(FJson, 'gift'), JsonOwner);
end;

function TTgOwnedGiftRegularImpl.GetText: string;
begin
  Result := TTgJson.GetStr(FJson, 'text');
end;

function TTgOwnedGiftRegularImpl.GetEntities: TArray<ITgMessageEntity>;
begin
  Result := TTgDto.Objects<ITgMessageEntity>(TTgJson.GetArr(FJson, 'entities'), JsonOwner, TgMakeMessageEntity);
end;

function TTgOwnedGiftRegularImpl.GetIsPrivate: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_private');
end;

function TTgOwnedGiftRegularImpl.GetCanBeUpgraded: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_be_upgraded');
end;

function TTgOwnedGiftRegularImpl.GetWasRefunded: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'was_refunded');
end;

function TTgOwnedGiftRegularImpl.GetConvertStarCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'convert_star_count');
end;

function TTgOwnedGiftRegularImpl.GetHasConvertStarCount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'convert_star_count');
end;

function TTgOwnedGiftRegularImpl.GetPrepaidUpgradeStarCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'prepaid_upgrade_star_count');
end;

function TTgOwnedGiftRegularImpl.GetHasPrepaidUpgradeStarCount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'prepaid_upgrade_star_count');
end;

function TTgOwnedGiftRegularImpl.GetIsUpgradeSeparate: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_upgrade_separate');
end;

function TTgOwnedGiftRegularImpl.GetUniqueGiftNumber: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'unique_gift_number');
end;

function TTgOwnedGiftRegularImpl.GetHasUniqueGiftNumber: Boolean;
begin
  Result := TTgJson.Has(FJson, 'unique_gift_number');
end;

{ TTgOwnedGiftUniqueImpl }

function TTgOwnedGiftUniqueImpl.GetKind: TTgOwnedGiftKind;
begin
  Result := TTgOwnedGiftKind.Unique;
end;

function TTgOwnedGiftUniqueImpl.GetGift: ITgUniqueGift;
begin
  Result := TgMakeUniqueGift(TTgJson.GetValue(FJson, 'gift'), JsonOwner);
end;

function TTgOwnedGiftUniqueImpl.GetCanBeTransferred: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_be_transferred');
end;

function TTgOwnedGiftUniqueImpl.GetTransferStarCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'transfer_star_count');
end;

function TTgOwnedGiftUniqueImpl.GetHasTransferStarCount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'transfer_star_count');
end;

function TTgOwnedGiftUniqueImpl.GetNextTransferDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'next_transfer_date');
end;

function TTgOwnedGiftUniqueImpl.GetHasNextTransferDate: Boolean;
begin
  Result := TTgJson.Has(FJson, 'next_transfer_date');
end;

{ TTgOwnedGiftsImpl }

function TTgOwnedGiftsImpl.GetTotalCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'total_count');
end;

function TTgOwnedGiftsImpl.GetGifts: TArray<ITgOwnedGift>;
begin
  Result := TTgDto.Objects<ITgOwnedGift>(TTgJson.GetArr(FJson, 'gifts'), JsonOwner, TgMakeOwnedGift);
end;

function TTgOwnedGiftsImpl.GetNextOffset: string;
begin
  Result := TTgJson.GetStr(FJson, 'next_offset');
end;

{ TTgBotAccessSettingsImpl }

function TTgBotAccessSettingsImpl.GetIsAccessRestricted: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_access_restricted');
end;

function TTgBotAccessSettingsImpl.GetAddedUsers: TArray<ITgUser>;
begin
  Result := TTgDto.Objects<ITgUser>(TTgJson.GetArr(FJson, 'added_users'), JsonOwner, TgMakeUser);
end;

{ TTgAcceptedGiftTypesImpl }

function TTgAcceptedGiftTypesImpl.GetUnlimitedGifts: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'unlimited_gifts');
end;

function TTgAcceptedGiftTypesImpl.GetLimitedGifts: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'limited_gifts');
end;

function TTgAcceptedGiftTypesImpl.GetUniqueGifts: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'unique_gifts');
end;

function TTgAcceptedGiftTypesImpl.GetPremiumSubscription: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'premium_subscription');
end;

function TTgAcceptedGiftTypesImpl.GetGiftsFromChannels: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'gifts_from_channels');
end;

function TTgAcceptedGiftTypesImpl.WithUnlimitedGifts(AValue: Boolean): ITgAcceptedGiftTypes;
begin
  SetBool('unlimited_gifts', AValue);
  Result := Self;
end;

function TTgAcceptedGiftTypesImpl.WithLimitedGifts(AValue: Boolean): ITgAcceptedGiftTypes;
begin
  SetBool('limited_gifts', AValue);
  Result := Self;
end;

function TTgAcceptedGiftTypesImpl.WithUniqueGifts(AValue: Boolean): ITgAcceptedGiftTypes;
begin
  SetBool('unique_gifts', AValue);
  Result := Self;
end;

function TTgAcceptedGiftTypesImpl.WithPremiumSubscription(AValue: Boolean): ITgAcceptedGiftTypes;
begin
  SetBool('premium_subscription', AValue);
  Result := Self;
end;

function TTgAcceptedGiftTypesImpl.WithGiftsFromChannels(AValue: Boolean): ITgAcceptedGiftTypes;
begin
  SetBool('gifts_from_channels', AValue);
  Result := Self;
end;

{ TTgStarAmountImpl }

function TTgStarAmountImpl.GetAmount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'amount');
end;

function TTgStarAmountImpl.GetNanostarAmount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'nanostar_amount');
end;

function TTgStarAmountImpl.GetHasNanostarAmount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'nanostar_amount');
end;

{ TTgBotCommandImpl }

function TTgBotCommandImpl.GetCommand: string;
begin
  Result := TTgJson.GetStr(FJson, 'command');
end;

function TTgBotCommandImpl.GetDescription: string;
begin
  Result := TTgJson.GetStr(FJson, 'description');
end;

function TTgBotCommandImpl.GetIsEphemeral: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_ephemeral');
end;

function TTgBotCommandImpl.GetHasIsEphemeral: Boolean;
begin
  Result := TTgJson.Has(FJson, 'is_ephemeral');
end;

function TTgBotCommandImpl.WithCommand(const AValue: string): ITgBotCommand;
begin
  SetStr('command', AValue);
  Result := Self;
end;

function TTgBotCommandImpl.WithDescription(const AValue: string): ITgBotCommand;
begin
  SetStr('description', AValue);
  Result := Self;
end;

function TTgBotCommandImpl.WithIsEphemeral(AValue: Boolean): ITgBotCommand;
begin
  SetBool('is_ephemeral', AValue);
  Result := Self;
end;

{ TTgBotCommandScopeDefaultImpl }

{ TTgBotCommandScopeAllPrivateChatsImpl }

{ TTgBotCommandScopeAllGroupChatsImpl }

{ TTgBotCommandScopeAllChatAdministratorsImpl }

{ TTgBotCommandScopeChatImpl }

function TTgBotCommandScopeChatImpl.WithChatId(const AValue: TTgChatId): ITgBotCommandScopeChat;
begin
  SetChatId('chat_id', AValue);
  Result := Self;
end;

{ TTgBotCommandScopeChatAdministratorsImpl }

function TTgBotCommandScopeChatAdministratorsImpl.WithChatId(const AValue: TTgChatId): ITgBotCommandScopeChatAdministrators;
begin
  SetChatId('chat_id', AValue);
  Result := Self;
end;

{ TTgBotCommandScopeChatMemberImpl }

function TTgBotCommandScopeChatMemberImpl.WithChatId(const AValue: TTgChatId): ITgBotCommandScopeChatMember;
begin
  SetChatId('chat_id', AValue);
  Result := Self;
end;

function TTgBotCommandScopeChatMemberImpl.WithUserId(AValue: Int64): ITgBotCommandScopeChatMember;
begin
  SetInt64('user_id', AValue);
  Result := Self;
end;

{ TTgBotNameImpl }

function TTgBotNameImpl.GetName: string;
begin
  Result := TTgJson.GetStr(FJson, 'name');
end;

{ TTgBotDescriptionImpl }

function TTgBotDescriptionImpl.GetDescription: string;
begin
  Result := TTgJson.GetStr(FJson, 'description');
end;

{ TTgBotShortDescriptionImpl }

function TTgBotShortDescriptionImpl.GetShortDescription: string;
begin
  Result := TTgJson.GetStr(FJson, 'short_description');
end;

{ TTgMenuButtonImpl }

function TTgMenuButtonImpl.GetKind: TTgMenuButtonKind;
begin
  Result := TTgMenuButtonKind.Unknown;
end;

function TTgMenuButtonImpl.GetKindText: string;
begin
  Result := TTgJson.GetStr(FJson, 'type');
end;

function TTgMenuButtonImpl.AsCommands: ITgMenuButtonCommands;
begin
  if not Supports(Self, ITgMenuButtonCommands, Result) then
    Result := nil;
end;

function TTgMenuButtonImpl.AsWebApp: ITgMenuButtonWebApp;
begin
  if not Supports(Self, ITgMenuButtonWebApp, Result) then
    Result := nil;
end;

function TTgMenuButtonImpl.AsDefault: ITgMenuButtonDefault;
begin
  if not Supports(Self, ITgMenuButtonDefault, Result) then
    Result := nil;
end;

{ TTgMenuButtonCommandsImpl }

function TTgMenuButtonCommandsImpl.GetKind: TTgMenuButtonKind;
begin
  Result := TTgMenuButtonKind.Commands;
end;

{ TTgMenuButtonWebAppImpl }

function TTgMenuButtonWebAppImpl.GetKind: TTgMenuButtonKind;
begin
  Result := TTgMenuButtonKind.WebApp;
end;

function TTgMenuButtonWebAppImpl.GetText: string;
begin
  Result := TTgJson.GetStr(FJson, 'text');
end;

function TTgMenuButtonWebAppImpl.GetWebApp: ITgWebAppInfo;
begin
  Result := TgMakeWebAppInfo(TTgJson.GetValue(FJson, 'web_app'), JsonOwner);
end;

function TTgMenuButtonWebAppImpl.WithText(const AValue: string): ITgMenuButtonWebApp;
begin
  SetStr('text', AValue);
  Result := Self;
end;

function TTgMenuButtonWebAppImpl.WithWebApp(const AValue: ITgWebAppInfo): ITgMenuButtonWebApp;
begin
  SetObject('web_app', AValue);
  Result := Self;
end;

{ TTgMenuButtonDefaultImpl }

function TTgMenuButtonDefaultImpl.GetKind: TTgMenuButtonKind;
begin
  Result := TTgMenuButtonKind.Default;
end;

{ TTgChatBoostSourceImpl }

function TTgChatBoostSourceImpl.GetKind: TTgChatBoostSourceKind;
begin
  Result := TTgChatBoostSourceKind.Unknown;
end;

function TTgChatBoostSourceImpl.GetKindText: string;
begin
  Result := TTgJson.GetStr(FJson, 'source');
end;

function TTgChatBoostSourceImpl.GetSource: string;
begin
  Result := TTgJson.GetStr(FJson, 'source');
end;

function TTgChatBoostSourceImpl.GetUser: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'user'), JsonOwner);
end;

function TTgChatBoostSourceImpl.AsPremium: ITgChatBoostSourcePremium;
begin
  if not Supports(Self, ITgChatBoostSourcePremium, Result) then
    Result := nil;
end;

function TTgChatBoostSourceImpl.AsGiftCode: ITgChatBoostSourceGiftCode;
begin
  if not Supports(Self, ITgChatBoostSourceGiftCode, Result) then
    Result := nil;
end;

function TTgChatBoostSourceImpl.AsGiveaway: ITgChatBoostSourceGiveaway;
begin
  if not Supports(Self, ITgChatBoostSourceGiveaway, Result) then
    Result := nil;
end;

{ TTgChatBoostSourcePremiumImpl }

function TTgChatBoostSourcePremiumImpl.GetKind: TTgChatBoostSourceKind;
begin
  Result := TTgChatBoostSourceKind.Premium;
end;

{ TTgChatBoostSourceGiftCodeImpl }

function TTgChatBoostSourceGiftCodeImpl.GetKind: TTgChatBoostSourceKind;
begin
  Result := TTgChatBoostSourceKind.GiftCode;
end;

{ TTgChatBoostSourceGiveawayImpl }

function TTgChatBoostSourceGiveawayImpl.GetKind: TTgChatBoostSourceKind;
begin
  Result := TTgChatBoostSourceKind.Giveaway;
end;

function TTgChatBoostSourceGiveawayImpl.GetGiveawayMessageId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'giveaway_message_id');
end;

function TTgChatBoostSourceGiveawayImpl.GetPrizeStarCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'prize_star_count');
end;

function TTgChatBoostSourceGiveawayImpl.GetHasPrizeStarCount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'prize_star_count');
end;

function TTgChatBoostSourceGiveawayImpl.GetIsUnclaimed: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_unclaimed');
end;

{ TTgChatBoostImpl }

function TTgChatBoostImpl.GetBoostId: string;
begin
  Result := TTgJson.GetStr(FJson, 'boost_id');
end;

function TTgChatBoostImpl.GetAddDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'add_date');
end;

function TTgChatBoostImpl.GetExpirationDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'expiration_date');
end;

function TTgChatBoostImpl.GetSource: ITgChatBoostSource;
begin
  Result := TgMakeChatBoostSource(TTgJson.GetValue(FJson, 'source'), JsonOwner);
end;

{ TTgChatBoostUpdatedImpl }

function TTgChatBoostUpdatedImpl.GetChat: ITgChat;
begin
  Result := TgMakeChat(TTgJson.GetValue(FJson, 'chat'), JsonOwner);
end;

function TTgChatBoostUpdatedImpl.GetBoost: ITgChatBoost;
begin
  Result := TgMakeChatBoost(TTgJson.GetValue(FJson, 'boost'), JsonOwner);
end;

{ TTgChatBoostRemovedImpl }

function TTgChatBoostRemovedImpl.GetChat: ITgChat;
begin
  Result := TgMakeChat(TTgJson.GetValue(FJson, 'chat'), JsonOwner);
end;

function TTgChatBoostRemovedImpl.GetBoostId: string;
begin
  Result := TTgJson.GetStr(FJson, 'boost_id');
end;

function TTgChatBoostRemovedImpl.GetRemoveDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'remove_date');
end;

function TTgChatBoostRemovedImpl.GetSource: ITgChatBoostSource;
begin
  Result := TgMakeChatBoostSource(TTgJson.GetValue(FJson, 'source'), JsonOwner);
end;

{ TTgChatOwnerLeftImpl }

function TTgChatOwnerLeftImpl.GetNewOwner: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'new_owner'), JsonOwner);
end;

{ TTgChatOwnerChangedImpl }

function TTgChatOwnerChangedImpl.GetNewOwner: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'new_owner'), JsonOwner);
end;

{ TTgUserChatBoostsImpl }

function TTgUserChatBoostsImpl.GetBoosts: TArray<ITgChatBoost>;
begin
  Result := TTgDto.Objects<ITgChatBoost>(TTgJson.GetArr(FJson, 'boosts'), JsonOwner, TgMakeChatBoost);
end;

{ TTgBusinessBotRightsImpl }

function TTgBusinessBotRightsImpl.GetCanReply: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_reply');
end;

function TTgBusinessBotRightsImpl.GetCanReadMessages: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_read_messages');
end;

function TTgBusinessBotRightsImpl.GetCanDeleteSentMessages: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_delete_sent_messages');
end;

function TTgBusinessBotRightsImpl.GetCanDeleteAllMessages: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_delete_all_messages');
end;

function TTgBusinessBotRightsImpl.GetCanEditName: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_edit_name');
end;

function TTgBusinessBotRightsImpl.GetCanEditBio: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_edit_bio');
end;

function TTgBusinessBotRightsImpl.GetCanEditProfilePhoto: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_edit_profile_photo');
end;

function TTgBusinessBotRightsImpl.GetCanEditUsername: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_edit_username');
end;

function TTgBusinessBotRightsImpl.GetCanChangeGiftSettings: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_change_gift_settings');
end;

function TTgBusinessBotRightsImpl.GetCanViewGiftsAndStars: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_view_gifts_and_stars');
end;

function TTgBusinessBotRightsImpl.GetCanConvertGiftsToStars: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_convert_gifts_to_stars');
end;

function TTgBusinessBotRightsImpl.GetCanTransferAndUpgradeGifts: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_transfer_and_upgrade_gifts');
end;

function TTgBusinessBotRightsImpl.GetCanTransferStars: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_transfer_stars');
end;

function TTgBusinessBotRightsImpl.GetCanManageStories: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'can_manage_stories');
end;

{ TTgBusinessConnectionImpl }

function TTgBusinessConnectionImpl.GetId: string;
begin
  Result := TTgJson.GetStr(FJson, 'id');
end;

function TTgBusinessConnectionImpl.GetUser: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'user'), JsonOwner);
end;

function TTgBusinessConnectionImpl.GetUserChatId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'user_chat_id');
end;

function TTgBusinessConnectionImpl.GetDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'date');
end;

function TTgBusinessConnectionImpl.GetRights: ITgBusinessBotRights;
begin
  Result := TgMakeBusinessBotRights(TTgJson.GetValue(FJson, 'rights'), JsonOwner);
end;

function TTgBusinessConnectionImpl.GetIsEnabled: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_enabled');
end;

{ TTgBusinessMessagesDeletedImpl }

function TTgBusinessMessagesDeletedImpl.GetBusinessConnectionId: string;
begin
  Result := TTgJson.GetStr(FJson, 'business_connection_id');
end;

function TTgBusinessMessagesDeletedImpl.GetChat: ITgChat;
begin
  Result := TgMakeChat(TTgJson.GetValue(FJson, 'chat'), JsonOwner);
end;

function TTgBusinessMessagesDeletedImpl.GetMessageIds: TArray<Int64>;
begin
  Result := TTgDto.Int64s(TTgJson.GetArr(FJson, 'message_ids'), 'message_ids');
end;

{ TTgSentWebAppMessageImpl }

function TTgSentWebAppMessageImpl.GetInlineMessageId: string;
begin
  Result := TTgJson.GetStr(FJson, 'inline_message_id');
end;

{ TTgSentGuestMessageImpl }

function TTgSentGuestMessageImpl.GetInlineMessageId: string;
begin
  Result := TTgJson.GetStr(FJson, 'inline_message_id');
end;

{ TTgPreparedInlineMessageImpl }

function TTgPreparedInlineMessageImpl.GetId: string;
begin
  Result := TTgJson.GetStr(FJson, 'id');
end;

function TTgPreparedInlineMessageImpl.GetExpirationDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'expiration_date');
end;

{ TTgPreparedKeyboardButtonImpl }

function TTgPreparedKeyboardButtonImpl.GetId: string;
begin
  Result := TTgJson.GetStr(FJson, 'id');
end;

{ TTgResponseParametersImpl }

function TTgResponseParametersImpl.GetMigrateToChatId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'migrate_to_chat_id');
end;

function TTgResponseParametersImpl.GetHasMigrateToChatId: Boolean;
begin
  Result := TTgJson.Has(FJson, 'migrate_to_chat_id');
end;

function TTgResponseParametersImpl.GetRetryAfter: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'retry_after');
end;

function TTgResponseParametersImpl.GetHasRetryAfter: Boolean;
begin
  Result := TTgJson.Has(FJson, 'retry_after');
end;

{ TTgInputMediaAnimationImpl }

function TTgInputMediaAnimationImpl.WithMedia(const AValue: TTgInputFile): ITgInputMediaAnimation;
begin
  SetFile('media', AValue);
  Result := Self;
end;

function TTgInputMediaAnimationImpl.WithThumbnail(const AValue: TTgInputFile): ITgInputMediaAnimation;
begin
  SetFile('thumbnail', AValue);
  Result := Self;
end;

function TTgInputMediaAnimationImpl.WithCaption(const AValue: string): ITgInputMediaAnimation;
begin
  SetStr('caption', AValue);
  Result := Self;
end;

function TTgInputMediaAnimationImpl.WithParseMode(const AValue: string): ITgInputMediaAnimation;
begin
  SetStr('parse_mode', AValue);
  Result := Self;
end;

function TTgInputMediaAnimationImpl.WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInputMediaAnimation;
begin
  SetObjects('caption_entities', TTgDto.ToIntf<ITgMessageEntity>(AValue));
  Result := Self;
end;

function TTgInputMediaAnimationImpl.WithShowCaptionAboveMedia(AValue: Boolean): ITgInputMediaAnimation;
begin
  SetBool('show_caption_above_media', AValue);
  Result := Self;
end;

function TTgInputMediaAnimationImpl.WithWidth(AValue: Integer): ITgInputMediaAnimation;
begin
  SetInt('width', AValue);
  Result := Self;
end;

function TTgInputMediaAnimationImpl.WithHeight(AValue: Integer): ITgInputMediaAnimation;
begin
  SetInt('height', AValue);
  Result := Self;
end;

function TTgInputMediaAnimationImpl.WithDuration(AValue: Integer): ITgInputMediaAnimation;
begin
  SetInt('duration', AValue);
  Result := Self;
end;

function TTgInputMediaAnimationImpl.WithHasSpoiler(AValue: Boolean): ITgInputMediaAnimation;
begin
  SetBool('has_spoiler', AValue);
  Result := Self;
end;

{ TTgInputMediaAudioImpl }

function TTgInputMediaAudioImpl.WithMedia(const AValue: TTgInputFile): ITgInputMediaAudio;
begin
  SetFile('media', AValue);
  Result := Self;
end;

function TTgInputMediaAudioImpl.WithThumbnail(const AValue: TTgInputFile): ITgInputMediaAudio;
begin
  SetFile('thumbnail', AValue);
  Result := Self;
end;

function TTgInputMediaAudioImpl.WithCaption(const AValue: string): ITgInputMediaAudio;
begin
  SetStr('caption', AValue);
  Result := Self;
end;

function TTgInputMediaAudioImpl.WithParseMode(const AValue: string): ITgInputMediaAudio;
begin
  SetStr('parse_mode', AValue);
  Result := Self;
end;

function TTgInputMediaAudioImpl.WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInputMediaAudio;
begin
  SetObjects('caption_entities', TTgDto.ToIntf<ITgMessageEntity>(AValue));
  Result := Self;
end;

function TTgInputMediaAudioImpl.WithDuration(AValue: Integer): ITgInputMediaAudio;
begin
  SetInt('duration', AValue);
  Result := Self;
end;

function TTgInputMediaAudioImpl.WithPerformer(const AValue: string): ITgInputMediaAudio;
begin
  SetStr('performer', AValue);
  Result := Self;
end;

function TTgInputMediaAudioImpl.WithTitle(const AValue: string): ITgInputMediaAudio;
begin
  SetStr('title', AValue);
  Result := Self;
end;

{ TTgInputMediaDocumentImpl }

function TTgInputMediaDocumentImpl.WithMedia(const AValue: TTgInputFile): ITgInputMediaDocument;
begin
  SetFile('media', AValue);
  Result := Self;
end;

function TTgInputMediaDocumentImpl.WithThumbnail(const AValue: TTgInputFile): ITgInputMediaDocument;
begin
  SetFile('thumbnail', AValue);
  Result := Self;
end;

function TTgInputMediaDocumentImpl.WithCaption(const AValue: string): ITgInputMediaDocument;
begin
  SetStr('caption', AValue);
  Result := Self;
end;

function TTgInputMediaDocumentImpl.WithParseMode(const AValue: string): ITgInputMediaDocument;
begin
  SetStr('parse_mode', AValue);
  Result := Self;
end;

function TTgInputMediaDocumentImpl.WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInputMediaDocument;
begin
  SetObjects('caption_entities', TTgDto.ToIntf<ITgMessageEntity>(AValue));
  Result := Self;
end;

function TTgInputMediaDocumentImpl.WithDisableContentTypeDetection(AValue: Boolean): ITgInputMediaDocument;
begin
  SetBool('disable_content_type_detection', AValue);
  Result := Self;
end;

{ TTgInputMediaLinkImpl }

function TTgInputMediaLinkImpl.WithUrl(const AValue: string): ITgInputMediaLink;
begin
  SetStr('url', AValue);
  Result := Self;
end;

{ TTgInputMediaLivePhotoImpl }

function TTgInputMediaLivePhotoImpl.WithMedia(const AValue: TTgInputFile): ITgInputMediaLivePhoto;
begin
  SetFile('media', AValue);
  Result := Self;
end;

function TTgInputMediaLivePhotoImpl.WithPhoto(const AValue: TTgInputFile): ITgInputMediaLivePhoto;
begin
  SetFile('photo', AValue);
  Result := Self;
end;

function TTgInputMediaLivePhotoImpl.WithCaption(const AValue: string): ITgInputMediaLivePhoto;
begin
  SetStr('caption', AValue);
  Result := Self;
end;

function TTgInputMediaLivePhotoImpl.WithParseMode(const AValue: string): ITgInputMediaLivePhoto;
begin
  SetStr('parse_mode', AValue);
  Result := Self;
end;

function TTgInputMediaLivePhotoImpl.WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInputMediaLivePhoto;
begin
  SetObjects('caption_entities', TTgDto.ToIntf<ITgMessageEntity>(AValue));
  Result := Self;
end;

function TTgInputMediaLivePhotoImpl.WithShowCaptionAboveMedia(AValue: Boolean): ITgInputMediaLivePhoto;
begin
  SetBool('show_caption_above_media', AValue);
  Result := Self;
end;

function TTgInputMediaLivePhotoImpl.WithHasSpoiler(AValue: Boolean): ITgInputMediaLivePhoto;
begin
  SetBool('has_spoiler', AValue);
  Result := Self;
end;

{ TTgInputMediaLocationImpl }

function TTgInputMediaLocationImpl.WithLatitude(AValue: Double): ITgInputMediaLocation;
begin
  SetDouble('latitude', AValue);
  Result := Self;
end;

function TTgInputMediaLocationImpl.WithLongitude(AValue: Double): ITgInputMediaLocation;
begin
  SetDouble('longitude', AValue);
  Result := Self;
end;

function TTgInputMediaLocationImpl.WithHorizontalAccuracy(AValue: Double): ITgInputMediaLocation;
begin
  SetDouble('horizontal_accuracy', AValue);
  Result := Self;
end;

{ TTgInputMediaPhotoImpl }

function TTgInputMediaPhotoImpl.WithMedia(const AValue: TTgInputFile): ITgInputMediaPhoto;
begin
  SetFile('media', AValue);
  Result := Self;
end;

function TTgInputMediaPhotoImpl.WithCaption(const AValue: string): ITgInputMediaPhoto;
begin
  SetStr('caption', AValue);
  Result := Self;
end;

function TTgInputMediaPhotoImpl.WithParseMode(const AValue: string): ITgInputMediaPhoto;
begin
  SetStr('parse_mode', AValue);
  Result := Self;
end;

function TTgInputMediaPhotoImpl.WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInputMediaPhoto;
begin
  SetObjects('caption_entities', TTgDto.ToIntf<ITgMessageEntity>(AValue));
  Result := Self;
end;

function TTgInputMediaPhotoImpl.WithShowCaptionAboveMedia(AValue: Boolean): ITgInputMediaPhoto;
begin
  SetBool('show_caption_above_media', AValue);
  Result := Self;
end;

function TTgInputMediaPhotoImpl.WithHasSpoiler(AValue: Boolean): ITgInputMediaPhoto;
begin
  SetBool('has_spoiler', AValue);
  Result := Self;
end;

{ TTgInputMediaStickerImpl }

function TTgInputMediaStickerImpl.WithMedia(const AValue: TTgInputFile): ITgInputMediaSticker;
begin
  SetFile('media', AValue);
  Result := Self;
end;

function TTgInputMediaStickerImpl.WithEmoji(const AValue: string): ITgInputMediaSticker;
begin
  SetStr('emoji', AValue);
  Result := Self;
end;

{ TTgInputMediaVenueImpl }

function TTgInputMediaVenueImpl.WithLatitude(AValue: Double): ITgInputMediaVenue;
begin
  SetDouble('latitude', AValue);
  Result := Self;
end;

function TTgInputMediaVenueImpl.WithLongitude(AValue: Double): ITgInputMediaVenue;
begin
  SetDouble('longitude', AValue);
  Result := Self;
end;

function TTgInputMediaVenueImpl.WithTitle(const AValue: string): ITgInputMediaVenue;
begin
  SetStr('title', AValue);
  Result := Self;
end;

function TTgInputMediaVenueImpl.WithAddress(const AValue: string): ITgInputMediaVenue;
begin
  SetStr('address', AValue);
  Result := Self;
end;

function TTgInputMediaVenueImpl.WithFoursquareId(const AValue: string): ITgInputMediaVenue;
begin
  SetStr('foursquare_id', AValue);
  Result := Self;
end;

function TTgInputMediaVenueImpl.WithFoursquareType(const AValue: string): ITgInputMediaVenue;
begin
  SetStr('foursquare_type', AValue);
  Result := Self;
end;

function TTgInputMediaVenueImpl.WithGooglePlaceId(const AValue: string): ITgInputMediaVenue;
begin
  SetStr('google_place_id', AValue);
  Result := Self;
end;

function TTgInputMediaVenueImpl.WithGooglePlaceType(const AValue: string): ITgInputMediaVenue;
begin
  SetStr('google_place_type', AValue);
  Result := Self;
end;

{ TTgInputMediaVideoImpl }

function TTgInputMediaVideoImpl.WithMedia(const AValue: TTgInputFile): ITgInputMediaVideo;
begin
  SetFile('media', AValue);
  Result := Self;
end;

function TTgInputMediaVideoImpl.WithThumbnail(const AValue: TTgInputFile): ITgInputMediaVideo;
begin
  SetFile('thumbnail', AValue);
  Result := Self;
end;

function TTgInputMediaVideoImpl.WithCover(const AValue: TTgInputFile): ITgInputMediaVideo;
begin
  SetFile('cover', AValue);
  Result := Self;
end;

function TTgInputMediaVideoImpl.WithStartTimestamp(AValue: Integer): ITgInputMediaVideo;
begin
  SetInt('start_timestamp', AValue);
  Result := Self;
end;

function TTgInputMediaVideoImpl.WithCaption(const AValue: string): ITgInputMediaVideo;
begin
  SetStr('caption', AValue);
  Result := Self;
end;

function TTgInputMediaVideoImpl.WithParseMode(const AValue: string): ITgInputMediaVideo;
begin
  SetStr('parse_mode', AValue);
  Result := Self;
end;

function TTgInputMediaVideoImpl.WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInputMediaVideo;
begin
  SetObjects('caption_entities', TTgDto.ToIntf<ITgMessageEntity>(AValue));
  Result := Self;
end;

function TTgInputMediaVideoImpl.WithShowCaptionAboveMedia(AValue: Boolean): ITgInputMediaVideo;
begin
  SetBool('show_caption_above_media', AValue);
  Result := Self;
end;

function TTgInputMediaVideoImpl.WithWidth(AValue: Integer): ITgInputMediaVideo;
begin
  SetInt('width', AValue);
  Result := Self;
end;

function TTgInputMediaVideoImpl.WithHeight(AValue: Integer): ITgInputMediaVideo;
begin
  SetInt('height', AValue);
  Result := Self;
end;

function TTgInputMediaVideoImpl.WithDuration(AValue: Integer): ITgInputMediaVideo;
begin
  SetInt('duration', AValue);
  Result := Self;
end;

function TTgInputMediaVideoImpl.WithSupportsStreaming(AValue: Boolean): ITgInputMediaVideo;
begin
  SetBool('supports_streaming', AValue);
  Result := Self;
end;

function TTgInputMediaVideoImpl.WithHasSpoiler(AValue: Boolean): ITgInputMediaVideo;
begin
  SetBool('has_spoiler', AValue);
  Result := Self;
end;

{ TTgInputMediaVoiceNoteImpl }

function TTgInputMediaVoiceNoteImpl.WithMedia(const AValue: TTgInputFile): ITgInputMediaVoiceNote;
begin
  SetFile('media', AValue);
  Result := Self;
end;

function TTgInputMediaVoiceNoteImpl.WithCaption(const AValue: string): ITgInputMediaVoiceNote;
begin
  SetStr('caption', AValue);
  Result := Self;
end;

function TTgInputMediaVoiceNoteImpl.WithParseMode(const AValue: string): ITgInputMediaVoiceNote;
begin
  SetStr('parse_mode', AValue);
  Result := Self;
end;

function TTgInputMediaVoiceNoteImpl.WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInputMediaVoiceNote;
begin
  SetObjects('caption_entities', TTgDto.ToIntf<ITgMessageEntity>(AValue));
  Result := Self;
end;

function TTgInputMediaVoiceNoteImpl.WithDuration(AValue: Integer): ITgInputMediaVoiceNote;
begin
  SetInt('duration', AValue);
  Result := Self;
end;

{ TTgInputPaidMediaLivePhotoImpl }

function TTgInputPaidMediaLivePhotoImpl.WithMedia(const AValue: TTgInputFile): ITgInputPaidMediaLivePhoto;
begin
  SetFile('media', AValue);
  Result := Self;
end;

function TTgInputPaidMediaLivePhotoImpl.WithPhoto(const AValue: TTgInputFile): ITgInputPaidMediaLivePhoto;
begin
  SetFile('photo', AValue);
  Result := Self;
end;

{ TTgInputPaidMediaPhotoImpl }

function TTgInputPaidMediaPhotoImpl.WithMedia(const AValue: TTgInputFile): ITgInputPaidMediaPhoto;
begin
  SetFile('media', AValue);
  Result := Self;
end;

{ TTgInputPaidMediaVideoImpl }

function TTgInputPaidMediaVideoImpl.WithMedia(const AValue: TTgInputFile): ITgInputPaidMediaVideo;
begin
  SetFile('media', AValue);
  Result := Self;
end;

function TTgInputPaidMediaVideoImpl.WithThumbnail(const AValue: TTgInputFile): ITgInputPaidMediaVideo;
begin
  SetFile('thumbnail', AValue);
  Result := Self;
end;

function TTgInputPaidMediaVideoImpl.WithCover(const AValue: TTgInputFile): ITgInputPaidMediaVideo;
begin
  SetFile('cover', AValue);
  Result := Self;
end;

function TTgInputPaidMediaVideoImpl.WithStartTimestamp(AValue: Integer): ITgInputPaidMediaVideo;
begin
  SetInt('start_timestamp', AValue);
  Result := Self;
end;

function TTgInputPaidMediaVideoImpl.WithWidth(AValue: Integer): ITgInputPaidMediaVideo;
begin
  SetInt('width', AValue);
  Result := Self;
end;

function TTgInputPaidMediaVideoImpl.WithHeight(AValue: Integer): ITgInputPaidMediaVideo;
begin
  SetInt('height', AValue);
  Result := Self;
end;

function TTgInputPaidMediaVideoImpl.WithDuration(AValue: Integer): ITgInputPaidMediaVideo;
begin
  SetInt('duration', AValue);
  Result := Self;
end;

function TTgInputPaidMediaVideoImpl.WithSupportsStreaming(AValue: Boolean): ITgInputPaidMediaVideo;
begin
  SetBool('supports_streaming', AValue);
  Result := Self;
end;

{ TTgInputProfilePhotoStaticImpl }

function TTgInputProfilePhotoStaticImpl.WithPhoto(const AValue: TTgInputFile): ITgInputProfilePhotoStatic;
begin
  SetFile('photo', AValue);
  Result := Self;
end;

{ TTgInputProfilePhotoAnimatedImpl }

function TTgInputProfilePhotoAnimatedImpl.WithAnimation(const AValue: TTgInputFile): ITgInputProfilePhotoAnimated;
begin
  SetFile('animation', AValue);
  Result := Self;
end;

function TTgInputProfilePhotoAnimatedImpl.WithMainFrameTimestamp(AValue: Double): ITgInputProfilePhotoAnimated;
begin
  SetDouble('main_frame_timestamp', AValue);
  Result := Self;
end;

{ TTgInputStoryContentPhotoImpl }

function TTgInputStoryContentPhotoImpl.WithPhoto(const AValue: TTgInputFile): ITgInputStoryContentPhoto;
begin
  SetFile('photo', AValue);
  Result := Self;
end;

{ TTgInputStoryContentVideoImpl }

function TTgInputStoryContentVideoImpl.WithVideo(const AValue: TTgInputFile): ITgInputStoryContentVideo;
begin
  SetFile('video', AValue);
  Result := Self;
end;

function TTgInputStoryContentVideoImpl.WithDuration(AValue: Double): ITgInputStoryContentVideo;
begin
  SetDouble('duration', AValue);
  Result := Self;
end;

function TTgInputStoryContentVideoImpl.WithCoverFrameTimestamp(AValue: Double): ITgInputStoryContentVideo;
begin
  SetDouble('cover_frame_timestamp', AValue);
  Result := Self;
end;

function TTgInputStoryContentVideoImpl.WithIsAnimation(AValue: Boolean): ITgInputStoryContentVideo;
begin
  SetBool('is_animation', AValue);
  Result := Self;
end;

{ TTgStickerImpl }

function TTgStickerImpl.GetFileId: string;
begin
  Result := TTgJson.GetStr(FJson, 'file_id');
end;

function TTgStickerImpl.GetFileUniqueId: string;
begin
  Result := TTgJson.GetStr(FJson, 'file_unique_id');
end;

function TTgStickerImpl.GetStickerType: string;
begin
  Result := TTgJson.GetStr(FJson, 'type');
end;

function TTgStickerImpl.GetWidth: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'width');
end;

function TTgStickerImpl.GetHeight: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'height');
end;

function TTgStickerImpl.GetIsAnimated: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_animated');
end;

function TTgStickerImpl.GetIsVideo: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_video');
end;

function TTgStickerImpl.GetThumbnail: ITgPhotoSize;
begin
  Result := TgMakePhotoSize(TTgJson.GetValue(FJson, 'thumbnail'), JsonOwner);
end;

function TTgStickerImpl.GetEmoji: string;
begin
  Result := TTgJson.GetStr(FJson, 'emoji');
end;

function TTgStickerImpl.GetSetName: string;
begin
  Result := TTgJson.GetStr(FJson, 'set_name');
end;

function TTgStickerImpl.GetPremiumAnimation: ITgFile;
begin
  Result := TgMakeFile(TTgJson.GetValue(FJson, 'premium_animation'), JsonOwner);
end;

function TTgStickerImpl.GetMaskPosition: ITgMaskPosition;
begin
  Result := TgMakeMaskPosition(TTgJson.GetValue(FJson, 'mask_position'), JsonOwner);
end;

function TTgStickerImpl.GetCustomEmojiId: string;
begin
  Result := TTgJson.GetStr(FJson, 'custom_emoji_id');
end;

function TTgStickerImpl.GetNeedsRepainting: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'needs_repainting');
end;

function TTgStickerImpl.GetFileSize: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'file_size');
end;

function TTgStickerImpl.GetHasFileSize: Boolean;
begin
  Result := TTgJson.Has(FJson, 'file_size');
end;

{ TTgStickerSetImpl }

function TTgStickerSetImpl.GetName: string;
begin
  Result := TTgJson.GetStr(FJson, 'name');
end;

function TTgStickerSetImpl.GetTitle: string;
begin
  Result := TTgJson.GetStr(FJson, 'title');
end;

function TTgStickerSetImpl.GetStickerType: string;
begin
  Result := TTgJson.GetStr(FJson, 'sticker_type');
end;

function TTgStickerSetImpl.GetStickers: TArray<ITgSticker>;
begin
  Result := TTgDto.Objects<ITgSticker>(TTgJson.GetArr(FJson, 'stickers'), JsonOwner, TgMakeSticker);
end;

function TTgStickerSetImpl.GetThumbnail: ITgPhotoSize;
begin
  Result := TgMakePhotoSize(TTgJson.GetValue(FJson, 'thumbnail'), JsonOwner);
end;

{ TTgMaskPositionImpl }

function TTgMaskPositionImpl.GetPoint: string;
begin
  Result := TTgJson.GetStr(FJson, 'point');
end;

function TTgMaskPositionImpl.GetXShift: Double;
begin
  Result := TTgJson.GetDouble(FJson, 'x_shift');
end;

function TTgMaskPositionImpl.GetYShift: Double;
begin
  Result := TTgJson.GetDouble(FJson, 'y_shift');
end;

function TTgMaskPositionImpl.GetScale: Double;
begin
  Result := TTgJson.GetDouble(FJson, 'scale');
end;

function TTgMaskPositionImpl.WithPoint(const AValue: string): ITgMaskPosition;
begin
  SetStr('point', AValue);
  Result := Self;
end;

function TTgMaskPositionImpl.WithXShift(AValue: Double): ITgMaskPosition;
begin
  SetDouble('x_shift', AValue);
  Result := Self;
end;

function TTgMaskPositionImpl.WithYShift(AValue: Double): ITgMaskPosition;
begin
  SetDouble('y_shift', AValue);
  Result := Self;
end;

function TTgMaskPositionImpl.WithScale(AValue: Double): ITgMaskPosition;
begin
  SetDouble('scale', AValue);
  Result := Self;
end;

{ TTgInputStickerImpl }

function TTgInputStickerImpl.WithSticker(const AValue: TTgInputFile): ITgInputSticker;
begin
  SetFile('sticker', AValue);
  Result := Self;
end;

function TTgInputStickerImpl.WithFormat(const AValue: string): ITgInputSticker;
begin
  SetStr('format', AValue);
  Result := Self;
end;

function TTgInputStickerImpl.WithEmojiList(const AValue: TArray<string>): ITgInputSticker;
begin
  SetStrings('emoji_list', AValue);
  Result := Self;
end;

function TTgInputStickerImpl.WithMaskPosition(const AValue: ITgMaskPosition): ITgInputSticker;
begin
  SetObject('mask_position', AValue);
  Result := Self;
end;

function TTgInputStickerImpl.WithKeywords(const AValue: TArray<string>): ITgInputSticker;
begin
  SetStrings('keywords', AValue);
  Result := Self;
end;

{ TTgRichMessageImpl }

function TTgRichMessageImpl.GetBlocks: TArray<ITgRichBlock>;
begin
  Result := TTgDto.Objects<ITgRichBlock>(TTgJson.GetArr(FJson, 'blocks'), JsonOwner, TgMakeRichBlock);
end;

function TTgRichMessageImpl.GetIsRtl: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_rtl');
end;

function TTgRichMessageImpl.GetHasIsRtl: Boolean;
begin
  Result := TTgJson.Has(FJson, 'is_rtl');
end;

{ TTgInputRichMessageImpl }

function TTgInputRichMessageImpl.WithBlocks(const AValue: array of TTgInputRichBlock): ITgInputRichMessage;
begin
  SetObjects('blocks', TTgInputRichBlock.Values(AValue));
  Result := Self;
end;

function TTgInputRichMessageImpl.WithHtml(const AValue: string): ITgInputRichMessage;
begin
  SetStr('html', AValue);
  Result := Self;
end;

function TTgInputRichMessageImpl.WithMarkdown(const AValue: string): ITgInputRichMessage;
begin
  SetStr('markdown', AValue);
  Result := Self;
end;

function TTgInputRichMessageImpl.WithMedia(const AValue: array of ITgInputRichMessageMedia): ITgInputRichMessage;
begin
  SetObjects('media', TTgDto.ToIntf<ITgInputRichMessageMedia>(AValue));
  Result := Self;
end;

function TTgInputRichMessageImpl.WithIsRtl(AValue: Boolean): ITgInputRichMessage;
begin
  SetBool('is_rtl', AValue);
  Result := Self;
end;

function TTgInputRichMessageImpl.WithSkipEntityDetection(AValue: Boolean): ITgInputRichMessage;
begin
  SetBool('skip_entity_detection', AValue);
  Result := Self;
end;

{ TTgInputRichMessageMediaImpl }

function TTgInputRichMessageMediaImpl.WithId(const AValue: string): ITgInputRichMessageMedia;
begin
  SetStr('id', AValue);
  Result := Self;
end;

function TTgInputRichMessageMediaImpl.WithMedia(const AValue: TTgInputRichMedia): ITgInputRichMessageMedia;
begin
  SetObject('media', AValue.Value);
  Result := Self;
end;

{ TTgRichMessageButtonImpl }

function TTgRichMessageButtonImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

function TTgRichMessageButtonImpl.GetStyle: string;
begin
  Result := TTgJson.GetStr(FJson, 'style');
end;

function TTgRichMessageButtonImpl.GetUrl: string;
begin
  Result := TTgJson.GetStr(FJson, 'url');
end;

function TTgRichMessageButtonImpl.GetCallbackData: string;
begin
  Result := TTgJson.GetStr(FJson, 'callback_data');
end;

function TTgRichMessageButtonImpl.GetWebApp: ITgWebAppInfo;
begin
  Result := TgMakeWebAppInfo(TTgJson.GetValue(FJson, 'web_app'), JsonOwner);
end;

function TTgRichMessageButtonImpl.GetLoginUrl: ITgLoginUrl;
begin
  Result := TgMakeLoginUrl(TTgJson.GetValue(FJson, 'login_url'), JsonOwner);
end;

function TTgRichMessageButtonImpl.GetSwitchInlineQuery: string;
begin
  Result := TTgJson.GetStr(FJson, 'switch_inline_query');
end;

function TTgRichMessageButtonImpl.GetSwitchInlineQueryCurrentChat: string;
begin
  Result := TTgJson.GetStr(FJson, 'switch_inline_query_current_chat');
end;

function TTgRichMessageButtonImpl.GetSwitchInlineQueryChosenChat: ITgSwitchInlineQueryChosenChat;
begin
  Result := TgMakeSwitchInlineQueryChosenChat(TTgJson.GetValue(FJson, 'switch_inline_query_chosen_chat'), JsonOwner);
end;

function TTgRichMessageButtonImpl.GetCopyText: ITgCopyTextButton;
begin
  Result := TgMakeCopyTextButton(TTgJson.GetValue(FJson, 'copy_text'), JsonOwner);
end;

function TTgRichMessageButtonImpl.GetDisabled: ITgDisabledButton;
begin
  Result := TgMakeDisabledButton(TTgJson.GetValue(FJson, 'disabled'), JsonOwner);
end;

function TTgRichMessageButtonImpl.WithText(const AValue: ITgRichText): ITgRichMessageButton;
begin
  SetObject('text', AValue);
  Result := Self;
end;

function TTgRichMessageButtonImpl.WithStyle(const AValue: string): ITgRichMessageButton;
begin
  SetStr('style', AValue);
  Result := Self;
end;

function TTgRichMessageButtonImpl.WithUrl(const AValue: string): ITgRichMessageButton;
begin
  SetStr('url', AValue);
  Result := Self;
end;

function TTgRichMessageButtonImpl.WithCallbackData(const AValue: string): ITgRichMessageButton;
begin
  SetStr('callback_data', AValue);
  Result := Self;
end;

function TTgRichMessageButtonImpl.WithWebApp(const AValue: ITgWebAppInfo): ITgRichMessageButton;
begin
  SetObject('web_app', AValue);
  Result := Self;
end;

function TTgRichMessageButtonImpl.WithLoginUrl(const AValue: ITgLoginUrl): ITgRichMessageButton;
begin
  SetObject('login_url', AValue);
  Result := Self;
end;

function TTgRichMessageButtonImpl.WithSwitchInlineQuery(const AValue: string): ITgRichMessageButton;
begin
  SetStr('switch_inline_query', AValue);
  Result := Self;
end;

function TTgRichMessageButtonImpl.WithSwitchInlineQueryCurrentChat(const AValue: string): ITgRichMessageButton;
begin
  SetStr('switch_inline_query_current_chat', AValue);
  Result := Self;
end;

function TTgRichMessageButtonImpl.WithSwitchInlineQueryChosenChat(const AValue: ITgSwitchInlineQueryChosenChat): ITgRichMessageButton;
begin
  SetObject('switch_inline_query_chosen_chat', AValue);
  Result := Self;
end;

function TTgRichMessageButtonImpl.WithCopyText(const AValue: ITgCopyTextButton): ITgRichMessageButton;
begin
  SetObject('copy_text', AValue);
  Result := Self;
end;

function TTgRichMessageButtonImpl.WithDisabled(const AValue: ITgDisabledButton): ITgRichMessageButton;
begin
  SetObject('disabled', AValue);
  Result := Self;
end;

{ TTgRichTextImpl }

function TTgRichTextImpl.GetKind: TTgRichTextKind;
begin
  Result := TTgRichTextKind.Unknown;
end;

function TTgRichTextImpl.GetKindText: string;
begin
  Result := TTgJson.GetStr(FJson, 'type');
end;

function TTgRichTextImpl.AsBold: ITgRichTextBold;
begin
  if not Supports(Self, ITgRichTextBold, Result) then
    Result := nil;
end;

function TTgRichTextImpl.AsItalic: ITgRichTextItalic;
begin
  if not Supports(Self, ITgRichTextItalic, Result) then
    Result := nil;
end;

function TTgRichTextImpl.AsUnderline: ITgRichTextUnderline;
begin
  if not Supports(Self, ITgRichTextUnderline, Result) then
    Result := nil;
end;

function TTgRichTextImpl.AsStrikethrough: ITgRichTextStrikethrough;
begin
  if not Supports(Self, ITgRichTextStrikethrough, Result) then
    Result := nil;
end;

function TTgRichTextImpl.AsSpoiler: ITgRichTextSpoiler;
begin
  if not Supports(Self, ITgRichTextSpoiler, Result) then
    Result := nil;
end;

function TTgRichTextImpl.AsDateTime: ITgRichTextDateTime;
begin
  if not Supports(Self, ITgRichTextDateTime, Result) then
    Result := nil;
end;

function TTgRichTextImpl.AsTextMention: ITgRichTextTextMention;
begin
  if not Supports(Self, ITgRichTextTextMention, Result) then
    Result := nil;
end;

function TTgRichTextImpl.AsSubscript: ITgRichTextSubscript;
begin
  if not Supports(Self, ITgRichTextSubscript, Result) then
    Result := nil;
end;

function TTgRichTextImpl.AsSuperscript: ITgRichTextSuperscript;
begin
  if not Supports(Self, ITgRichTextSuperscript, Result) then
    Result := nil;
end;

function TTgRichTextImpl.AsMarked: ITgRichTextMarked;
begin
  if not Supports(Self, ITgRichTextMarked, Result) then
    Result := nil;
end;

function TTgRichTextImpl.AsCode: ITgRichTextCode;
begin
  if not Supports(Self, ITgRichTextCode, Result) then
    Result := nil;
end;

function TTgRichTextImpl.AsCustomEmoji: ITgRichTextCustomEmoji;
begin
  if not Supports(Self, ITgRichTextCustomEmoji, Result) then
    Result := nil;
end;

function TTgRichTextImpl.AsMathematicalExpression: ITgRichTextMathematicalExpression;
begin
  if not Supports(Self, ITgRichTextMathematicalExpression, Result) then
    Result := nil;
end;

function TTgRichTextImpl.AsUrl: ITgRichTextUrl;
begin
  if not Supports(Self, ITgRichTextUrl, Result) then
    Result := nil;
end;

function TTgRichTextImpl.AsEmailAddress: ITgRichTextEmailAddress;
begin
  if not Supports(Self, ITgRichTextEmailAddress, Result) then
    Result := nil;
end;

function TTgRichTextImpl.AsPhoneNumber: ITgRichTextPhoneNumber;
begin
  if not Supports(Self, ITgRichTextPhoneNumber, Result) then
    Result := nil;
end;

function TTgRichTextImpl.AsBankCardNumber: ITgRichTextBankCardNumber;
begin
  if not Supports(Self, ITgRichTextBankCardNumber, Result) then
    Result := nil;
end;

function TTgRichTextImpl.AsMention: ITgRichTextMention;
begin
  if not Supports(Self, ITgRichTextMention, Result) then
    Result := nil;
end;

function TTgRichTextImpl.AsHashtag: ITgRichTextHashtag;
begin
  if not Supports(Self, ITgRichTextHashtag, Result) then
    Result := nil;
end;

function TTgRichTextImpl.AsCashtag: ITgRichTextCashtag;
begin
  if not Supports(Self, ITgRichTextCashtag, Result) then
    Result := nil;
end;

function TTgRichTextImpl.AsBotCommand: ITgRichTextBotCommand;
begin
  if not Supports(Self, ITgRichTextBotCommand, Result) then
    Result := nil;
end;

function TTgRichTextImpl.AsButton: ITgRichTextButton;
begin
  if not Supports(Self, ITgRichTextButton, Result) then
    Result := nil;
end;

function TTgRichTextImpl.AsAnchor: ITgRichTextAnchor;
begin
  if not Supports(Self, ITgRichTextAnchor, Result) then
    Result := nil;
end;

function TTgRichTextImpl.AsAnchorLink: ITgRichTextAnchorLink;
begin
  if not Supports(Self, ITgRichTextAnchorLink, Result) then
    Result := nil;
end;

function TTgRichTextImpl.AsReference: ITgRichTextReference;
begin
  if not Supports(Self, ITgRichTextReference, Result) then
    Result := nil;
end;

function TTgRichTextImpl.AsReferenceLink: ITgRichTextReferenceLink;
begin
  if not Supports(Self, ITgRichTextReferenceLink, Result) then
    Result := nil;
end;

function TTgRichTextImpl.AsPlain: ITgRichTextPlain;
begin
  if not Supports(Self, ITgRichTextPlain, Result) then
    Result := nil;
end;

function TTgRichTextImpl.AsList: ITgRichTextList;
begin
  if not Supports(Self, ITgRichTextList, Result) then
    Result := nil;
end;

{ TTgRichTextPlainImpl }

function TTgRichTextPlainImpl.GetKind: TTgRichTextKind;
begin
  Result := TTgRichTextKind.Plain;
end;

function TTgRichTextPlainImpl.GetText: string;
begin
  Result := ValueText;
end;

{ TTgRichTextListImpl }

function TTgRichTextListImpl.GetKind: TTgRichTextKind;
begin
  Result := TTgRichTextKind.List;
end;

function TTgRichTextListImpl.GetItems: TArray<ITgRichText>;
begin
  Result := TTgDto.Objects<ITgRichText>(ValueArray, JsonOwner, TgMakeRichText);
end;

{ TTgRichTextBoldImpl }

function TTgRichTextBoldImpl.GetKind: TTgRichTextKind;
begin
  Result := TTgRichTextKind.Bold;
end;

function TTgRichTextBoldImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

function TTgRichTextBoldImpl.WithText(const AValue: ITgRichText): ITgRichTextBold;
begin
  SetObject('text', AValue);
  Result := Self;
end;

{ TTgRichTextItalicImpl }

function TTgRichTextItalicImpl.GetKind: TTgRichTextKind;
begin
  Result := TTgRichTextKind.Italic;
end;

function TTgRichTextItalicImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

function TTgRichTextItalicImpl.WithText(const AValue: ITgRichText): ITgRichTextItalic;
begin
  SetObject('text', AValue);
  Result := Self;
end;

{ TTgRichTextUnderlineImpl }

function TTgRichTextUnderlineImpl.GetKind: TTgRichTextKind;
begin
  Result := TTgRichTextKind.Underline;
end;

function TTgRichTextUnderlineImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

function TTgRichTextUnderlineImpl.WithText(const AValue: ITgRichText): ITgRichTextUnderline;
begin
  SetObject('text', AValue);
  Result := Self;
end;

{ TTgRichTextStrikethroughImpl }

function TTgRichTextStrikethroughImpl.GetKind: TTgRichTextKind;
begin
  Result := TTgRichTextKind.Strikethrough;
end;

function TTgRichTextStrikethroughImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

function TTgRichTextStrikethroughImpl.WithText(const AValue: ITgRichText): ITgRichTextStrikethrough;
begin
  SetObject('text', AValue);
  Result := Self;
end;

{ TTgRichTextSpoilerImpl }

function TTgRichTextSpoilerImpl.GetKind: TTgRichTextKind;
begin
  Result := TTgRichTextKind.Spoiler;
end;

function TTgRichTextSpoilerImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

function TTgRichTextSpoilerImpl.WithText(const AValue: ITgRichText): ITgRichTextSpoiler;
begin
  SetObject('text', AValue);
  Result := Self;
end;

{ TTgRichTextDateTimeImpl }

function TTgRichTextDateTimeImpl.GetKind: TTgRichTextKind;
begin
  Result := TTgRichTextKind.DateTime;
end;

function TTgRichTextDateTimeImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

function TTgRichTextDateTimeImpl.GetUnixTime: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'unix_time');
end;

function TTgRichTextDateTimeImpl.GetDateTimeFormat: string;
begin
  Result := TTgJson.GetStr(FJson, 'date_time_format');
end;

function TTgRichTextDateTimeImpl.WithText(const AValue: ITgRichText): ITgRichTextDateTime;
begin
  SetObject('text', AValue);
  Result := Self;
end;

function TTgRichTextDateTimeImpl.WithUnixTime(AValue: Integer): ITgRichTextDateTime;
begin
  SetInt('unix_time', AValue);
  Result := Self;
end;

function TTgRichTextDateTimeImpl.WithDateTimeFormat(const AValue: string): ITgRichTextDateTime;
begin
  SetStr('date_time_format', AValue);
  Result := Self;
end;

{ TTgRichTextTextMentionImpl }

function TTgRichTextTextMentionImpl.GetKind: TTgRichTextKind;
begin
  Result := TTgRichTextKind.TextMention;
end;

function TTgRichTextTextMentionImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

function TTgRichTextTextMentionImpl.GetUser: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'user'), JsonOwner);
end;

function TTgRichTextTextMentionImpl.WithText(const AValue: ITgRichText): ITgRichTextTextMention;
begin
  SetObject('text', AValue);
  Result := Self;
end;

function TTgRichTextTextMentionImpl.WithUser(const AValue: ITgUser): ITgRichTextTextMention;
begin
  SetObject('user', AValue);
  Result := Self;
end;

{ TTgRichTextSubscriptImpl }

function TTgRichTextSubscriptImpl.GetKind: TTgRichTextKind;
begin
  Result := TTgRichTextKind.Subscript;
end;

function TTgRichTextSubscriptImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

function TTgRichTextSubscriptImpl.WithText(const AValue: ITgRichText): ITgRichTextSubscript;
begin
  SetObject('text', AValue);
  Result := Self;
end;

{ TTgRichTextSuperscriptImpl }

function TTgRichTextSuperscriptImpl.GetKind: TTgRichTextKind;
begin
  Result := TTgRichTextKind.Superscript;
end;

function TTgRichTextSuperscriptImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

function TTgRichTextSuperscriptImpl.WithText(const AValue: ITgRichText): ITgRichTextSuperscript;
begin
  SetObject('text', AValue);
  Result := Self;
end;

{ TTgRichTextMarkedImpl }

function TTgRichTextMarkedImpl.GetKind: TTgRichTextKind;
begin
  Result := TTgRichTextKind.Marked;
end;

function TTgRichTextMarkedImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

function TTgRichTextMarkedImpl.WithText(const AValue: ITgRichText): ITgRichTextMarked;
begin
  SetObject('text', AValue);
  Result := Self;
end;

{ TTgRichTextCodeImpl }

function TTgRichTextCodeImpl.GetKind: TTgRichTextKind;
begin
  Result := TTgRichTextKind.Code;
end;

function TTgRichTextCodeImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

function TTgRichTextCodeImpl.WithText(const AValue: ITgRichText): ITgRichTextCode;
begin
  SetObject('text', AValue);
  Result := Self;
end;

{ TTgRichTextCustomEmojiImpl }

function TTgRichTextCustomEmojiImpl.GetKind: TTgRichTextKind;
begin
  Result := TTgRichTextKind.CustomEmoji;
end;

function TTgRichTextCustomEmojiImpl.GetCustomEmojiId: string;
begin
  Result := TTgJson.GetStr(FJson, 'custom_emoji_id');
end;

function TTgRichTextCustomEmojiImpl.GetAlternativeText: string;
begin
  Result := TTgJson.GetStr(FJson, 'alternative_text');
end;

function TTgRichTextCustomEmojiImpl.WithCustomEmojiId(const AValue: string): ITgRichTextCustomEmoji;
begin
  SetStr('custom_emoji_id', AValue);
  Result := Self;
end;

function TTgRichTextCustomEmojiImpl.WithAlternativeText(const AValue: string): ITgRichTextCustomEmoji;
begin
  SetStr('alternative_text', AValue);
  Result := Self;
end;

{ TTgRichTextMathematicalExpressionImpl }

function TTgRichTextMathematicalExpressionImpl.GetKind: TTgRichTextKind;
begin
  Result := TTgRichTextKind.MathematicalExpression;
end;

function TTgRichTextMathematicalExpressionImpl.GetExpression: string;
begin
  Result := TTgJson.GetStr(FJson, 'expression');
end;

function TTgRichTextMathematicalExpressionImpl.WithExpression(const AValue: string): ITgRichTextMathematicalExpression;
begin
  SetStr('expression', AValue);
  Result := Self;
end;

{ TTgRichTextUrlImpl }

function TTgRichTextUrlImpl.GetKind: TTgRichTextKind;
begin
  Result := TTgRichTextKind.Url;
end;

function TTgRichTextUrlImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

function TTgRichTextUrlImpl.GetUrl: string;
begin
  Result := TTgJson.GetStr(FJson, 'url');
end;

function TTgRichTextUrlImpl.WithText(const AValue: ITgRichText): ITgRichTextUrl;
begin
  SetObject('text', AValue);
  Result := Self;
end;

function TTgRichTextUrlImpl.WithUrl(const AValue: string): ITgRichTextUrl;
begin
  SetStr('url', AValue);
  Result := Self;
end;

{ TTgRichTextEmailAddressImpl }

function TTgRichTextEmailAddressImpl.GetKind: TTgRichTextKind;
begin
  Result := TTgRichTextKind.EmailAddress;
end;

function TTgRichTextEmailAddressImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

function TTgRichTextEmailAddressImpl.GetEmailAddress: string;
begin
  Result := TTgJson.GetStr(FJson, 'email_address');
end;

function TTgRichTextEmailAddressImpl.WithText(const AValue: ITgRichText): ITgRichTextEmailAddress;
begin
  SetObject('text', AValue);
  Result := Self;
end;

function TTgRichTextEmailAddressImpl.WithEmailAddress(const AValue: string): ITgRichTextEmailAddress;
begin
  SetStr('email_address', AValue);
  Result := Self;
end;

{ TTgRichTextPhoneNumberImpl }

function TTgRichTextPhoneNumberImpl.GetKind: TTgRichTextKind;
begin
  Result := TTgRichTextKind.PhoneNumber;
end;

function TTgRichTextPhoneNumberImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

function TTgRichTextPhoneNumberImpl.GetPhoneNumber: string;
begin
  Result := TTgJson.GetStr(FJson, 'phone_number');
end;

function TTgRichTextPhoneNumberImpl.WithText(const AValue: ITgRichText): ITgRichTextPhoneNumber;
begin
  SetObject('text', AValue);
  Result := Self;
end;

function TTgRichTextPhoneNumberImpl.WithPhoneNumber(const AValue: string): ITgRichTextPhoneNumber;
begin
  SetStr('phone_number', AValue);
  Result := Self;
end;

{ TTgRichTextBankCardNumberImpl }

function TTgRichTextBankCardNumberImpl.GetKind: TTgRichTextKind;
begin
  Result := TTgRichTextKind.BankCardNumber;
end;

function TTgRichTextBankCardNumberImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

function TTgRichTextBankCardNumberImpl.GetBankCardNumber: string;
begin
  Result := TTgJson.GetStr(FJson, 'bank_card_number');
end;

function TTgRichTextBankCardNumberImpl.WithText(const AValue: ITgRichText): ITgRichTextBankCardNumber;
begin
  SetObject('text', AValue);
  Result := Self;
end;

function TTgRichTextBankCardNumberImpl.WithBankCardNumber(const AValue: string): ITgRichTextBankCardNumber;
begin
  SetStr('bank_card_number', AValue);
  Result := Self;
end;

{ TTgRichTextMentionImpl }

function TTgRichTextMentionImpl.GetKind: TTgRichTextKind;
begin
  Result := TTgRichTextKind.Mention;
end;

function TTgRichTextMentionImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

function TTgRichTextMentionImpl.GetUsername: string;
begin
  Result := TTgJson.GetStr(FJson, 'username');
end;

function TTgRichTextMentionImpl.WithText(const AValue: ITgRichText): ITgRichTextMention;
begin
  SetObject('text', AValue);
  Result := Self;
end;

function TTgRichTextMentionImpl.WithUsername(const AValue: string): ITgRichTextMention;
begin
  SetStr('username', AValue);
  Result := Self;
end;

{ TTgRichTextHashtagImpl }

function TTgRichTextHashtagImpl.GetKind: TTgRichTextKind;
begin
  Result := TTgRichTextKind.Hashtag;
end;

function TTgRichTextHashtagImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

function TTgRichTextHashtagImpl.GetHashtag: string;
begin
  Result := TTgJson.GetStr(FJson, 'hashtag');
end;

function TTgRichTextHashtagImpl.WithText(const AValue: ITgRichText): ITgRichTextHashtag;
begin
  SetObject('text', AValue);
  Result := Self;
end;

function TTgRichTextHashtagImpl.WithHashtag(const AValue: string): ITgRichTextHashtag;
begin
  SetStr('hashtag', AValue);
  Result := Self;
end;

{ TTgRichTextCashtagImpl }

function TTgRichTextCashtagImpl.GetKind: TTgRichTextKind;
begin
  Result := TTgRichTextKind.Cashtag;
end;

function TTgRichTextCashtagImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

function TTgRichTextCashtagImpl.GetCashtag: string;
begin
  Result := TTgJson.GetStr(FJson, 'cashtag');
end;

function TTgRichTextCashtagImpl.WithText(const AValue: ITgRichText): ITgRichTextCashtag;
begin
  SetObject('text', AValue);
  Result := Self;
end;

function TTgRichTextCashtagImpl.WithCashtag(const AValue: string): ITgRichTextCashtag;
begin
  SetStr('cashtag', AValue);
  Result := Self;
end;

{ TTgRichTextBotCommandImpl }

function TTgRichTextBotCommandImpl.GetKind: TTgRichTextKind;
begin
  Result := TTgRichTextKind.BotCommand;
end;

function TTgRichTextBotCommandImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

function TTgRichTextBotCommandImpl.GetBotCommand: string;
begin
  Result := TTgJson.GetStr(FJson, 'bot_command');
end;

function TTgRichTextBotCommandImpl.WithText(const AValue: ITgRichText): ITgRichTextBotCommand;
begin
  SetObject('text', AValue);
  Result := Self;
end;

function TTgRichTextBotCommandImpl.WithBotCommand(const AValue: string): ITgRichTextBotCommand;
begin
  SetStr('bot_command', AValue);
  Result := Self;
end;

{ TTgRichTextButtonImpl }

function TTgRichTextButtonImpl.GetKind: TTgRichTextKind;
begin
  Result := TTgRichTextKind.Button;
end;

function TTgRichTextButtonImpl.GetButton: ITgRichMessageButton;
begin
  Result := TgMakeRichMessageButton(TTgJson.GetValue(FJson, 'button'), JsonOwner);
end;

function TTgRichTextButtonImpl.WithButton(const AValue: ITgRichMessageButton): ITgRichTextButton;
begin
  SetObject('button', AValue);
  Result := Self;
end;

{ TTgRichTextAnchorImpl }

function TTgRichTextAnchorImpl.GetKind: TTgRichTextKind;
begin
  Result := TTgRichTextKind.Anchor;
end;

function TTgRichTextAnchorImpl.GetName: string;
begin
  Result := TTgJson.GetStr(FJson, 'name');
end;

function TTgRichTextAnchorImpl.WithName(const AValue: string): ITgRichTextAnchor;
begin
  SetStr('name', AValue);
  Result := Self;
end;

{ TTgRichTextAnchorLinkImpl }

function TTgRichTextAnchorLinkImpl.GetKind: TTgRichTextKind;
begin
  Result := TTgRichTextKind.AnchorLink;
end;

function TTgRichTextAnchorLinkImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

function TTgRichTextAnchorLinkImpl.GetAnchorName: string;
begin
  Result := TTgJson.GetStr(FJson, 'anchor_name');
end;

function TTgRichTextAnchorLinkImpl.WithText(const AValue: ITgRichText): ITgRichTextAnchorLink;
begin
  SetObject('text', AValue);
  Result := Self;
end;

function TTgRichTextAnchorLinkImpl.WithAnchorName(const AValue: string): ITgRichTextAnchorLink;
begin
  SetStr('anchor_name', AValue);
  Result := Self;
end;

{ TTgRichTextReferenceImpl }

function TTgRichTextReferenceImpl.GetKind: TTgRichTextKind;
begin
  Result := TTgRichTextKind.Reference;
end;

function TTgRichTextReferenceImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

function TTgRichTextReferenceImpl.GetName: string;
begin
  Result := TTgJson.GetStr(FJson, 'name');
end;

function TTgRichTextReferenceImpl.WithText(const AValue: ITgRichText): ITgRichTextReference;
begin
  SetObject('text', AValue);
  Result := Self;
end;

function TTgRichTextReferenceImpl.WithName(const AValue: string): ITgRichTextReference;
begin
  SetStr('name', AValue);
  Result := Self;
end;

{ TTgRichTextReferenceLinkImpl }

function TTgRichTextReferenceLinkImpl.GetKind: TTgRichTextKind;
begin
  Result := TTgRichTextKind.ReferenceLink;
end;

function TTgRichTextReferenceLinkImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

function TTgRichTextReferenceLinkImpl.GetReferenceName: string;
begin
  Result := TTgJson.GetStr(FJson, 'reference_name');
end;

function TTgRichTextReferenceLinkImpl.WithText(const AValue: ITgRichText): ITgRichTextReferenceLink;
begin
  SetObject('text', AValue);
  Result := Self;
end;

function TTgRichTextReferenceLinkImpl.WithReferenceName(const AValue: string): ITgRichTextReferenceLink;
begin
  SetStr('reference_name', AValue);
  Result := Self;
end;

{ TTgRichBlockCaptionImpl }

function TTgRichBlockCaptionImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

function TTgRichBlockCaptionImpl.GetCredit: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'credit'), JsonOwner);
end;

function TTgRichBlockCaptionImpl.WithText(const AValue: ITgRichText): ITgRichBlockCaption;
begin
  SetObject('text', AValue);
  Result := Self;
end;

function TTgRichBlockCaptionImpl.WithCredit(const AValue: ITgRichText): ITgRichBlockCaption;
begin
  SetObject('credit', AValue);
  Result := Self;
end;

{ TTgRichBlockTableCellImpl }

function TTgRichBlockTableCellImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

function TTgRichBlockTableCellImpl.GetIsHeader: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_header');
end;

function TTgRichBlockTableCellImpl.GetColspan: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'colspan');
end;

function TTgRichBlockTableCellImpl.GetHasColspan: Boolean;
begin
  Result := TTgJson.Has(FJson, 'colspan');
end;

function TTgRichBlockTableCellImpl.GetRowspan: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'rowspan');
end;

function TTgRichBlockTableCellImpl.GetHasRowspan: Boolean;
begin
  Result := TTgJson.Has(FJson, 'rowspan');
end;

function TTgRichBlockTableCellImpl.GetAlign: string;
begin
  Result := TTgJson.GetStr(FJson, 'align');
end;

function TTgRichBlockTableCellImpl.GetValign: string;
begin
  Result := TTgJson.GetStr(FJson, 'valign');
end;

function TTgRichBlockTableCellImpl.WithText(const AValue: ITgRichText): ITgRichBlockTableCell;
begin
  SetObject('text', AValue);
  Result := Self;
end;

function TTgRichBlockTableCellImpl.WithIsHeader(AValue: Boolean): ITgRichBlockTableCell;
begin
  SetBool('is_header', AValue);
  Result := Self;
end;

function TTgRichBlockTableCellImpl.WithColspan(AValue: Integer): ITgRichBlockTableCell;
begin
  SetInt('colspan', AValue);
  Result := Self;
end;

function TTgRichBlockTableCellImpl.WithRowspan(AValue: Integer): ITgRichBlockTableCell;
begin
  SetInt('rowspan', AValue);
  Result := Self;
end;

function TTgRichBlockTableCellImpl.WithAlign(const AValue: string): ITgRichBlockTableCell;
begin
  SetStr('align', AValue);
  Result := Self;
end;

function TTgRichBlockTableCellImpl.WithValign(const AValue: string): ITgRichBlockTableCell;
begin
  SetStr('valign', AValue);
  Result := Self;
end;

{ TTgRichBlockListItemImpl }

function TTgRichBlockListItemImpl.GetRichBlockListItemLabel: string;
begin
  Result := TTgJson.GetStr(FJson, 'label');
end;

function TTgRichBlockListItemImpl.GetBlocks: TArray<ITgRichBlock>;
begin
  Result := TTgDto.Objects<ITgRichBlock>(TTgJson.GetArr(FJson, 'blocks'), JsonOwner, TgMakeRichBlock);
end;

function TTgRichBlockListItemImpl.GetHasCheckbox: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'has_checkbox');
end;

function TTgRichBlockListItemImpl.GetIsChecked: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_checked');
end;

function TTgRichBlockListItemImpl.GetValue: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'value');
end;

function TTgRichBlockListItemImpl.GetHasValue: Boolean;
begin
  Result := TTgJson.Has(FJson, 'value');
end;

function TTgRichBlockListItemImpl.GetRichBlockListItemType: string;
begin
  Result := TTgJson.GetStr(FJson, 'type');
end;

{ TTgRichBlockImpl }

function TTgRichBlockImpl.GetKind: TTgRichBlockKind;
begin
  Result := TTgRichBlockKind.Unknown;
end;

function TTgRichBlockImpl.GetKindText: string;
begin
  Result := TTgJson.GetStr(FJson, 'type');
end;

function TTgRichBlockImpl.AsParagraph: ITgRichBlockParagraph;
begin
  if not Supports(Self, ITgRichBlockParagraph, Result) then
    Result := nil;
end;

function TTgRichBlockImpl.AsSectionHeading: ITgRichBlockSectionHeading;
begin
  if not Supports(Self, ITgRichBlockSectionHeading, Result) then
    Result := nil;
end;

function TTgRichBlockImpl.AsPreformatted: ITgRichBlockPreformatted;
begin
  if not Supports(Self, ITgRichBlockPreformatted, Result) then
    Result := nil;
end;

function TTgRichBlockImpl.AsFooter: ITgRichBlockFooter;
begin
  if not Supports(Self, ITgRichBlockFooter, Result) then
    Result := nil;
end;

function TTgRichBlockImpl.AsDivider: ITgRichBlockDivider;
begin
  if not Supports(Self, ITgRichBlockDivider, Result) then
    Result := nil;
end;

function TTgRichBlockImpl.AsMathematicalExpression: ITgRichBlockMathematicalExpression;
begin
  if not Supports(Self, ITgRichBlockMathematicalExpression, Result) then
    Result := nil;
end;

function TTgRichBlockImpl.AsAnchor: ITgRichBlockAnchor;
begin
  if not Supports(Self, ITgRichBlockAnchor, Result) then
    Result := nil;
end;

function TTgRichBlockImpl.AsList: ITgRichBlockList;
begin
  if not Supports(Self, ITgRichBlockList, Result) then
    Result := nil;
end;

function TTgRichBlockImpl.AsBlockQuotation: ITgRichBlockBlockQuotation;
begin
  if not Supports(Self, ITgRichBlockBlockQuotation, Result) then
    Result := nil;
end;

function TTgRichBlockImpl.AsExpandableBlockQuotation: ITgRichBlockExpandableBlockQuotation;
begin
  if not Supports(Self, ITgRichBlockExpandableBlockQuotation, Result) then
    Result := nil;
end;

function TTgRichBlockImpl.AsPullQuotation: ITgRichBlockPullQuotation;
begin
  if not Supports(Self, ITgRichBlockPullQuotation, Result) then
    Result := nil;
end;

function TTgRichBlockImpl.AsCollage: ITgRichBlockCollage;
begin
  if not Supports(Self, ITgRichBlockCollage, Result) then
    Result := nil;
end;

function TTgRichBlockImpl.AsSlideshow: ITgRichBlockSlideshow;
begin
  if not Supports(Self, ITgRichBlockSlideshow, Result) then
    Result := nil;
end;

function TTgRichBlockImpl.AsTable: ITgRichBlockTable;
begin
  if not Supports(Self, ITgRichBlockTable, Result) then
    Result := nil;
end;

function TTgRichBlockImpl.AsDetails: ITgRichBlockDetails;
begin
  if not Supports(Self, ITgRichBlockDetails, Result) then
    Result := nil;
end;

function TTgRichBlockImpl.AsMap: ITgRichBlockMap;
begin
  if not Supports(Self, ITgRichBlockMap, Result) then
    Result := nil;
end;

function TTgRichBlockImpl.AsButtons: ITgRichBlockButtons;
begin
  if not Supports(Self, ITgRichBlockButtons, Result) then
    Result := nil;
end;

function TTgRichBlockImpl.AsAnimation: ITgRichBlockAnimation;
begin
  if not Supports(Self, ITgRichBlockAnimation, Result) then
    Result := nil;
end;

function TTgRichBlockImpl.AsAudio: ITgRichBlockAudio;
begin
  if not Supports(Self, ITgRichBlockAudio, Result) then
    Result := nil;
end;

function TTgRichBlockImpl.AsDocument: ITgRichBlockDocument;
begin
  if not Supports(Self, ITgRichBlockDocument, Result) then
    Result := nil;
end;

function TTgRichBlockImpl.AsPhoto: ITgRichBlockPhoto;
begin
  if not Supports(Self, ITgRichBlockPhoto, Result) then
    Result := nil;
end;

function TTgRichBlockImpl.AsVideo: ITgRichBlockVideo;
begin
  if not Supports(Self, ITgRichBlockVideo, Result) then
    Result := nil;
end;

function TTgRichBlockImpl.AsVoiceNote: ITgRichBlockVoiceNote;
begin
  if not Supports(Self, ITgRichBlockVoiceNote, Result) then
    Result := nil;
end;

function TTgRichBlockImpl.AsThinking: ITgRichBlockThinking;
begin
  if not Supports(Self, ITgRichBlockThinking, Result) then
    Result := nil;
end;

{ TTgRichBlockParagraphImpl }

function TTgRichBlockParagraphImpl.GetKind: TTgRichBlockKind;
begin
  Result := TTgRichBlockKind.Paragraph;
end;

function TTgRichBlockParagraphImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

{ TTgRichBlockSectionHeadingImpl }

function TTgRichBlockSectionHeadingImpl.GetKind: TTgRichBlockKind;
begin
  Result := TTgRichBlockKind.SectionHeading;
end;

function TTgRichBlockSectionHeadingImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

function TTgRichBlockSectionHeadingImpl.GetSize: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'size');
end;

{ TTgRichBlockPreformattedImpl }

function TTgRichBlockPreformattedImpl.GetKind: TTgRichBlockKind;
begin
  Result := TTgRichBlockKind.Preformatted;
end;

function TTgRichBlockPreformattedImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

function TTgRichBlockPreformattedImpl.GetLanguage: string;
begin
  Result := TTgJson.GetStr(FJson, 'language');
end;

{ TTgRichBlockFooterImpl }

function TTgRichBlockFooterImpl.GetKind: TTgRichBlockKind;
begin
  Result := TTgRichBlockKind.Footer;
end;

function TTgRichBlockFooterImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

{ TTgRichBlockDividerImpl }

function TTgRichBlockDividerImpl.GetKind: TTgRichBlockKind;
begin
  Result := TTgRichBlockKind.Divider;
end;

{ TTgRichBlockMathematicalExpressionImpl }

function TTgRichBlockMathematicalExpressionImpl.GetKind: TTgRichBlockKind;
begin
  Result := TTgRichBlockKind.MathematicalExpression;
end;

function TTgRichBlockMathematicalExpressionImpl.GetExpression: string;
begin
  Result := TTgJson.GetStr(FJson, 'expression');
end;

{ TTgRichBlockAnchorImpl }

function TTgRichBlockAnchorImpl.GetKind: TTgRichBlockKind;
begin
  Result := TTgRichBlockKind.Anchor;
end;

function TTgRichBlockAnchorImpl.GetName: string;
begin
  Result := TTgJson.GetStr(FJson, 'name');
end;

{ TTgRichBlockListImpl }

function TTgRichBlockListImpl.GetKind: TTgRichBlockKind;
begin
  Result := TTgRichBlockKind.List;
end;

function TTgRichBlockListImpl.GetItems: TArray<ITgRichBlockListItem>;
begin
  Result := TTgDto.Objects<ITgRichBlockListItem>(TTgJson.GetArr(FJson, 'items'), JsonOwner, TgMakeRichBlockListItem);
end;

{ TTgRichBlockBlockQuotationImpl }

function TTgRichBlockBlockQuotationImpl.GetKind: TTgRichBlockKind;
begin
  Result := TTgRichBlockKind.BlockQuotation;
end;

function TTgRichBlockBlockQuotationImpl.GetBlocks: TArray<ITgRichBlock>;
begin
  Result := TTgDto.Objects<ITgRichBlock>(TTgJson.GetArr(FJson, 'blocks'), JsonOwner, TgMakeRichBlock);
end;

function TTgRichBlockBlockQuotationImpl.GetCredit: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'credit'), JsonOwner);
end;

{ TTgRichBlockExpandableBlockQuotationImpl }

function TTgRichBlockExpandableBlockQuotationImpl.GetKind: TTgRichBlockKind;
begin
  Result := TTgRichBlockKind.ExpandableBlockQuotation;
end;

function TTgRichBlockExpandableBlockQuotationImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

function TTgRichBlockExpandableBlockQuotationImpl.GetCredit: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'credit'), JsonOwner);
end;

{ TTgRichBlockPullQuotationImpl }

function TTgRichBlockPullQuotationImpl.GetKind: TTgRichBlockKind;
begin
  Result := TTgRichBlockKind.PullQuotation;
end;

function TTgRichBlockPullQuotationImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

function TTgRichBlockPullQuotationImpl.GetCredit: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'credit'), JsonOwner);
end;

{ TTgRichBlockCollageImpl }

function TTgRichBlockCollageImpl.GetKind: TTgRichBlockKind;
begin
  Result := TTgRichBlockKind.Collage;
end;

function TTgRichBlockCollageImpl.GetBlocks: TArray<ITgRichBlock>;
begin
  Result := TTgDto.Objects<ITgRichBlock>(TTgJson.GetArr(FJson, 'blocks'), JsonOwner, TgMakeRichBlock);
end;

function TTgRichBlockCollageImpl.GetCaption: ITgRichBlockCaption;
begin
  Result := TgMakeRichBlockCaption(TTgJson.GetValue(FJson, 'caption'), JsonOwner);
end;

{ TTgRichBlockSlideshowImpl }

function TTgRichBlockSlideshowImpl.GetKind: TTgRichBlockKind;
begin
  Result := TTgRichBlockKind.Slideshow;
end;

function TTgRichBlockSlideshowImpl.GetBlocks: TArray<ITgRichBlock>;
begin
  Result := TTgDto.Objects<ITgRichBlock>(TTgJson.GetArr(FJson, 'blocks'), JsonOwner, TgMakeRichBlock);
end;

function TTgRichBlockSlideshowImpl.GetCaption: ITgRichBlockCaption;
begin
  Result := TgMakeRichBlockCaption(TTgJson.GetValue(FJson, 'caption'), JsonOwner);
end;

{ TTgRichBlockTableImpl }

function TTgRichBlockTableImpl.GetKind: TTgRichBlockKind;
begin
  Result := TTgRichBlockKind.Table;
end;

function TTgRichBlockTableImpl.GetCells: TArray<TArray<ITgRichBlockTableCell>>;
begin
  Result := TTgDto.Objects2<ITgRichBlockTableCell>(TTgJson.GetArr(FJson, 'cells'), JsonOwner, TgMakeRichBlockTableCell);
end;

function TTgRichBlockTableImpl.GetIsBordered: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_bordered');
end;

function TTgRichBlockTableImpl.GetIsStriped: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_striped');
end;

function TTgRichBlockTableImpl.GetIsCompact: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_compact');
end;

function TTgRichBlockTableImpl.GetCaption: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'caption'), JsonOwner);
end;

{ TTgRichBlockDetailsImpl }

function TTgRichBlockDetailsImpl.GetKind: TTgRichBlockKind;
begin
  Result := TTgRichBlockKind.Details;
end;

function TTgRichBlockDetailsImpl.GetSummary: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'summary'), JsonOwner);
end;

function TTgRichBlockDetailsImpl.GetBlocks: TArray<ITgRichBlock>;
begin
  Result := TTgDto.Objects<ITgRichBlock>(TTgJson.GetArr(FJson, 'blocks'), JsonOwner, TgMakeRichBlock);
end;

function TTgRichBlockDetailsImpl.GetIsOpen: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_open');
end;

{ TTgRichBlockMapImpl }

function TTgRichBlockMapImpl.GetKind: TTgRichBlockKind;
begin
  Result := TTgRichBlockKind.Map;
end;

function TTgRichBlockMapImpl.GetLocation: ITgLocation;
begin
  Result := TgMakeLocation(TTgJson.GetValue(FJson, 'location'), JsonOwner);
end;

function TTgRichBlockMapImpl.GetZoom: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'zoom');
end;

function TTgRichBlockMapImpl.GetWidth: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'width');
end;

function TTgRichBlockMapImpl.GetHeight: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'height');
end;

function TTgRichBlockMapImpl.GetCaption: ITgRichBlockCaption;
begin
  Result := TgMakeRichBlockCaption(TTgJson.GetValue(FJson, 'caption'), JsonOwner);
end;

{ TTgRichBlockButtonsImpl }

function TTgRichBlockButtonsImpl.GetKind: TTgRichBlockKind;
begin
  Result := TTgRichBlockKind.Buttons;
end;

function TTgRichBlockButtonsImpl.GetButtons: TArray<ITgRichMessageButton>;
begin
  Result := TTgDto.Objects<ITgRichMessageButton>(TTgJson.GetArr(FJson, 'buttons'), JsonOwner, TgMakeRichMessageButton);
end;

function TTgRichBlockButtonsImpl.GetAlign: string;
begin
  Result := TTgJson.GetStr(FJson, 'align');
end;

{ TTgRichBlockAnimationImpl }

function TTgRichBlockAnimationImpl.GetKind: TTgRichBlockKind;
begin
  Result := TTgRichBlockKind.Animation;
end;

function TTgRichBlockAnimationImpl.GetAnimation: ITgAnimation;
begin
  Result := TgMakeAnimation(TTgJson.GetValue(FJson, 'animation'), JsonOwner);
end;

function TTgRichBlockAnimationImpl.GetHasSpoiler: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'has_spoiler');
end;

function TTgRichBlockAnimationImpl.GetCaption: ITgRichBlockCaption;
begin
  Result := TgMakeRichBlockCaption(TTgJson.GetValue(FJson, 'caption'), JsonOwner);
end;

{ TTgRichBlockAudioImpl }

function TTgRichBlockAudioImpl.GetKind: TTgRichBlockKind;
begin
  Result := TTgRichBlockKind.Audio;
end;

function TTgRichBlockAudioImpl.GetAudio: ITgAudio;
begin
  Result := TgMakeAudio(TTgJson.GetValue(FJson, 'audio'), JsonOwner);
end;

function TTgRichBlockAudioImpl.GetCaption: ITgRichBlockCaption;
begin
  Result := TgMakeRichBlockCaption(TTgJson.GetValue(FJson, 'caption'), JsonOwner);
end;

{ TTgRichBlockDocumentImpl }

function TTgRichBlockDocumentImpl.GetKind: TTgRichBlockKind;
begin
  Result := TTgRichBlockKind.Document;
end;

function TTgRichBlockDocumentImpl.GetDocument: ITgDocument;
begin
  Result := TgMakeDocument(TTgJson.GetValue(FJson, 'document'), JsonOwner);
end;

function TTgRichBlockDocumentImpl.GetCaption: ITgRichBlockCaption;
begin
  Result := TgMakeRichBlockCaption(TTgJson.GetValue(FJson, 'caption'), JsonOwner);
end;

{ TTgRichBlockPhotoImpl }

function TTgRichBlockPhotoImpl.GetKind: TTgRichBlockKind;
begin
  Result := TTgRichBlockKind.Photo;
end;

function TTgRichBlockPhotoImpl.GetPhoto: TArray<ITgPhotoSize>;
begin
  Result := TTgDto.Objects<ITgPhotoSize>(TTgJson.GetArr(FJson, 'photo'), JsonOwner, TgMakePhotoSize);
end;

function TTgRichBlockPhotoImpl.GetHasSpoiler: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'has_spoiler');
end;

function TTgRichBlockPhotoImpl.GetCaption: ITgRichBlockCaption;
begin
  Result := TgMakeRichBlockCaption(TTgJson.GetValue(FJson, 'caption'), JsonOwner);
end;

{ TTgRichBlockVideoImpl }

function TTgRichBlockVideoImpl.GetKind: TTgRichBlockKind;
begin
  Result := TTgRichBlockKind.Video;
end;

function TTgRichBlockVideoImpl.GetVideo: ITgVideo;
begin
  Result := TgMakeVideo(TTgJson.GetValue(FJson, 'video'), JsonOwner);
end;

function TTgRichBlockVideoImpl.GetHasSpoiler: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'has_spoiler');
end;

function TTgRichBlockVideoImpl.GetCaption: ITgRichBlockCaption;
begin
  Result := TgMakeRichBlockCaption(TTgJson.GetValue(FJson, 'caption'), JsonOwner);
end;

{ TTgRichBlockVoiceNoteImpl }

function TTgRichBlockVoiceNoteImpl.GetKind: TTgRichBlockKind;
begin
  Result := TTgRichBlockKind.VoiceNote;
end;

function TTgRichBlockVoiceNoteImpl.GetVoiceNote: ITgVoice;
begin
  Result := TgMakeVoice(TTgJson.GetValue(FJson, 'voice_note'), JsonOwner);
end;

function TTgRichBlockVoiceNoteImpl.GetCaption: ITgRichBlockCaption;
begin
  Result := TgMakeRichBlockCaption(TTgJson.GetValue(FJson, 'caption'), JsonOwner);
end;

{ TTgRichBlockThinkingImpl }

function TTgRichBlockThinkingImpl.GetKind: TTgRichBlockKind;
begin
  Result := TTgRichBlockKind.Thinking;
end;

function TTgRichBlockThinkingImpl.GetText: ITgRichText;
begin
  Result := TgMakeRichText(TTgJson.GetValue(FJson, 'text'), JsonOwner);
end;

{ TTgInputRichBlockListItemImpl }

function TTgInputRichBlockListItemImpl.WithBlocks(const AValue: array of TTgInputRichBlock): ITgInputRichBlockListItem;
begin
  SetObjects('blocks', TTgInputRichBlock.Values(AValue));
  Result := Self;
end;

function TTgInputRichBlockListItemImpl.WithHasCheckbox(AValue: Boolean): ITgInputRichBlockListItem;
begin
  SetBool('has_checkbox', AValue);
  Result := Self;
end;

function TTgInputRichBlockListItemImpl.WithIsChecked(AValue: Boolean): ITgInputRichBlockListItem;
begin
  SetBool('is_checked', AValue);
  Result := Self;
end;

function TTgInputRichBlockListItemImpl.WithValue(AValue: Integer): ITgInputRichBlockListItem;
begin
  SetInt('value', AValue);
  Result := Self;
end;

function TTgInputRichBlockListItemImpl.WithInputRichBlockListItemType(const AValue: string): ITgInputRichBlockListItem;
begin
  SetStr('type', AValue);
  Result := Self;
end;

{ TTgInputRichBlockParagraphImpl }

function TTgInputRichBlockParagraphImpl.WithText(const AValue: ITgRichText): ITgInputRichBlockParagraph;
begin
  SetObject('text', AValue);
  Result := Self;
end;

{ TTgInputRichBlockSectionHeadingImpl }

function TTgInputRichBlockSectionHeadingImpl.WithText(const AValue: ITgRichText): ITgInputRichBlockSectionHeading;
begin
  SetObject('text', AValue);
  Result := Self;
end;

function TTgInputRichBlockSectionHeadingImpl.WithSize(AValue: Integer): ITgInputRichBlockSectionHeading;
begin
  SetInt('size', AValue);
  Result := Self;
end;

{ TTgInputRichBlockPreformattedImpl }

function TTgInputRichBlockPreformattedImpl.WithText(const AValue: ITgRichText): ITgInputRichBlockPreformatted;
begin
  SetObject('text', AValue);
  Result := Self;
end;

function TTgInputRichBlockPreformattedImpl.WithLanguage(const AValue: string): ITgInputRichBlockPreformatted;
begin
  SetStr('language', AValue);
  Result := Self;
end;

{ TTgInputRichBlockFooterImpl }

function TTgInputRichBlockFooterImpl.WithText(const AValue: ITgRichText): ITgInputRichBlockFooter;
begin
  SetObject('text', AValue);
  Result := Self;
end;

{ TTgInputRichBlockDividerImpl }

{ TTgInputRichBlockMathematicalExpressionImpl }

function TTgInputRichBlockMathematicalExpressionImpl.WithExpression(const AValue: string): ITgInputRichBlockMathematicalExpression;
begin
  SetStr('expression', AValue);
  Result := Self;
end;

{ TTgInputRichBlockAnchorImpl }

function TTgInputRichBlockAnchorImpl.WithName(const AValue: string): ITgInputRichBlockAnchor;
begin
  SetStr('name', AValue);
  Result := Self;
end;

{ TTgInputRichBlockListImpl }

function TTgInputRichBlockListImpl.WithItems(const AValue: array of ITgInputRichBlockListItem): ITgInputRichBlockList;
begin
  SetObjects('items', TTgDto.ToIntf<ITgInputRichBlockListItem>(AValue));
  Result := Self;
end;

{ TTgInputRichBlockBlockQuotationImpl }

function TTgInputRichBlockBlockQuotationImpl.WithBlocks(const AValue: array of TTgInputRichBlock): ITgInputRichBlockBlockQuotation;
begin
  SetObjects('blocks', TTgInputRichBlock.Values(AValue));
  Result := Self;
end;

function TTgInputRichBlockBlockQuotationImpl.WithCredit(const AValue: ITgRichText): ITgInputRichBlockBlockQuotation;
begin
  SetObject('credit', AValue);
  Result := Self;
end;

{ TTgInputRichBlockExpandableBlockQuotationImpl }

function TTgInputRichBlockExpandableBlockQuotationImpl.WithText(const AValue: ITgRichText): ITgInputRichBlockExpandableBlockQuotation;
begin
  SetObject('text', AValue);
  Result := Self;
end;

function TTgInputRichBlockExpandableBlockQuotationImpl.WithCredit(const AValue: ITgRichText): ITgInputRichBlockExpandableBlockQuotation;
begin
  SetObject('credit', AValue);
  Result := Self;
end;

{ TTgInputRichBlockPullQuotationImpl }

function TTgInputRichBlockPullQuotationImpl.WithText(const AValue: ITgRichText): ITgInputRichBlockPullQuotation;
begin
  SetObject('text', AValue);
  Result := Self;
end;

function TTgInputRichBlockPullQuotationImpl.WithCredit(const AValue: ITgRichText): ITgInputRichBlockPullQuotation;
begin
  SetObject('credit', AValue);
  Result := Self;
end;

{ TTgInputRichBlockCollageImpl }

function TTgInputRichBlockCollageImpl.WithBlocks(const AValue: array of TTgInputRichBlock): ITgInputRichBlockCollage;
begin
  SetObjects('blocks', TTgInputRichBlock.Values(AValue));
  Result := Self;
end;

function TTgInputRichBlockCollageImpl.WithCaption(const AValue: ITgRichBlockCaption): ITgInputRichBlockCollage;
begin
  SetObject('caption', AValue);
  Result := Self;
end;

{ TTgInputRichBlockSlideshowImpl }

function TTgInputRichBlockSlideshowImpl.WithBlocks(const AValue: array of TTgInputRichBlock): ITgInputRichBlockSlideshow;
begin
  SetObjects('blocks', TTgInputRichBlock.Values(AValue));
  Result := Self;
end;

function TTgInputRichBlockSlideshowImpl.WithCaption(const AValue: ITgRichBlockCaption): ITgInputRichBlockSlideshow;
begin
  SetObject('caption', AValue);
  Result := Self;
end;

{ TTgInputRichBlockTableImpl }

function TTgInputRichBlockTableImpl.WithCells(const AValue: array of TArray<ITgRichBlockTableCell>): ITgInputRichBlockTable;
begin
  SetObjects2('cells', TTgDto.ToIntf2<ITgRichBlockTableCell>(AValue));
  Result := Self;
end;

function TTgInputRichBlockTableImpl.WithCellsRow(const ARow: array of ITgRichBlockTableCell): ITgInputRichBlockTable;
begin
  AppendRow('cells', TTgDto.ToIntf<ITgRichBlockTableCell>(ARow));
  Result := Self;
end;

function TTgInputRichBlockTableImpl.WithIsBordered(AValue: Boolean): ITgInputRichBlockTable;
begin
  SetBool('is_bordered', AValue);
  Result := Self;
end;

function TTgInputRichBlockTableImpl.WithIsStriped(AValue: Boolean): ITgInputRichBlockTable;
begin
  SetBool('is_striped', AValue);
  Result := Self;
end;

function TTgInputRichBlockTableImpl.WithIsCompact(AValue: Boolean): ITgInputRichBlockTable;
begin
  SetBool('is_compact', AValue);
  Result := Self;
end;

function TTgInputRichBlockTableImpl.WithCaption(const AValue: ITgRichText): ITgInputRichBlockTable;
begin
  SetObject('caption', AValue);
  Result := Self;
end;

{ TTgInputRichBlockDetailsImpl }

function TTgInputRichBlockDetailsImpl.WithSummary(const AValue: ITgRichText): ITgInputRichBlockDetails;
begin
  SetObject('summary', AValue);
  Result := Self;
end;

function TTgInputRichBlockDetailsImpl.WithBlocks(const AValue: array of TTgInputRichBlock): ITgInputRichBlockDetails;
begin
  SetObjects('blocks', TTgInputRichBlock.Values(AValue));
  Result := Self;
end;

function TTgInputRichBlockDetailsImpl.WithIsOpen(AValue: Boolean): ITgInputRichBlockDetails;
begin
  SetBool('is_open', AValue);
  Result := Self;
end;

{ TTgInputRichBlockMapImpl }

function TTgInputRichBlockMapImpl.WithLocation(const AValue: ITgLocation): ITgInputRichBlockMap;
begin
  SetObject('location', AValue);
  Result := Self;
end;

function TTgInputRichBlockMapImpl.WithZoom(AValue: Integer): ITgInputRichBlockMap;
begin
  SetInt('zoom', AValue);
  Result := Self;
end;

function TTgInputRichBlockMapImpl.WithWidth(AValue: Integer): ITgInputRichBlockMap;
begin
  SetInt('width', AValue);
  Result := Self;
end;

function TTgInputRichBlockMapImpl.WithHeight(AValue: Integer): ITgInputRichBlockMap;
begin
  SetInt('height', AValue);
  Result := Self;
end;

function TTgInputRichBlockMapImpl.WithCaption(const AValue: ITgRichBlockCaption): ITgInputRichBlockMap;
begin
  SetObject('caption', AValue);
  Result := Self;
end;

{ TTgInputRichBlockButtonsImpl }

function TTgInputRichBlockButtonsImpl.WithButtons(const AValue: array of ITgRichMessageButton): ITgInputRichBlockButtons;
begin
  SetObjects('buttons', TTgDto.ToIntf<ITgRichMessageButton>(AValue));
  Result := Self;
end;

function TTgInputRichBlockButtonsImpl.WithAlign(const AValue: string): ITgInputRichBlockButtons;
begin
  SetStr('align', AValue);
  Result := Self;
end;

{ TTgInputRichBlockAnimationImpl }

function TTgInputRichBlockAnimationImpl.WithAnimation(const AValue: ITgInputMediaAnimation): ITgInputRichBlockAnimation;
begin
  SetObject('animation', AValue);
  Result := Self;
end;

function TTgInputRichBlockAnimationImpl.WithCaption(const AValue: ITgRichBlockCaption): ITgInputRichBlockAnimation;
begin
  SetObject('caption', AValue);
  Result := Self;
end;

{ TTgInputRichBlockAudioImpl }

function TTgInputRichBlockAudioImpl.WithAudio(const AValue: ITgInputMediaAudio): ITgInputRichBlockAudio;
begin
  SetObject('audio', AValue);
  Result := Self;
end;

function TTgInputRichBlockAudioImpl.WithCaption(const AValue: ITgRichBlockCaption): ITgInputRichBlockAudio;
begin
  SetObject('caption', AValue);
  Result := Self;
end;

{ TTgInputRichBlockDocumentImpl }

function TTgInputRichBlockDocumentImpl.WithDocument(const AValue: ITgInputMediaDocument): ITgInputRichBlockDocument;
begin
  SetObject('document', AValue);
  Result := Self;
end;

function TTgInputRichBlockDocumentImpl.WithCaption(const AValue: ITgRichBlockCaption): ITgInputRichBlockDocument;
begin
  SetObject('caption', AValue);
  Result := Self;
end;

{ TTgInputRichBlockPhotoImpl }

function TTgInputRichBlockPhotoImpl.WithPhoto(const AValue: ITgInputMediaPhoto): ITgInputRichBlockPhoto;
begin
  SetObject('photo', AValue);
  Result := Self;
end;

function TTgInputRichBlockPhotoImpl.WithCaption(const AValue: ITgRichBlockCaption): ITgInputRichBlockPhoto;
begin
  SetObject('caption', AValue);
  Result := Self;
end;

{ TTgInputRichBlockVideoImpl }

function TTgInputRichBlockVideoImpl.WithVideo(const AValue: ITgInputMediaVideo): ITgInputRichBlockVideo;
begin
  SetObject('video', AValue);
  Result := Self;
end;

function TTgInputRichBlockVideoImpl.WithCaption(const AValue: ITgRichBlockCaption): ITgInputRichBlockVideo;
begin
  SetObject('caption', AValue);
  Result := Self;
end;

{ TTgInputRichBlockVoiceNoteImpl }

function TTgInputRichBlockVoiceNoteImpl.WithVoiceNote(const AValue: ITgInputMediaVoiceNote): ITgInputRichBlockVoiceNote;
begin
  SetObject('voice_note', AValue);
  Result := Self;
end;

function TTgInputRichBlockVoiceNoteImpl.WithCaption(const AValue: ITgRichBlockCaption): ITgInputRichBlockVoiceNote;
begin
  SetObject('caption', AValue);
  Result := Self;
end;

{ TTgInputRichBlockThinkingImpl }

function TTgInputRichBlockThinkingImpl.WithText(const AValue: ITgRichText): ITgInputRichBlockThinking;
begin
  SetObject('text', AValue);
  Result := Self;
end;

{ TTgInlineQueryImpl }

function TTgInlineQueryImpl.GetId: string;
begin
  Result := TTgJson.GetStr(FJson, 'id');
end;

function TTgInlineQueryImpl.GetFrom: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'from'), JsonOwner);
end;

function TTgInlineQueryImpl.GetQuery: string;
begin
  Result := TTgJson.GetStr(FJson, 'query');
end;

function TTgInlineQueryImpl.GetOffset: string;
begin
  Result := TTgJson.GetStr(FJson, 'offset');
end;

function TTgInlineQueryImpl.GetChatType: string;
begin
  Result := TTgJson.GetStr(FJson, 'chat_type');
end;

function TTgInlineQueryImpl.GetLocation: ITgLocation;
begin
  Result := TgMakeLocation(TTgJson.GetValue(FJson, 'location'), JsonOwner);
end;

{ TTgInlineQueryResultsButtonImpl }

function TTgInlineQueryResultsButtonImpl.WithText(const AValue: string): ITgInlineQueryResultsButton;
begin
  SetStr('text', AValue);
  Result := Self;
end;

function TTgInlineQueryResultsButtonImpl.WithWebApp(const AValue: ITgWebAppInfo): ITgInlineQueryResultsButton;
begin
  SetObject('web_app', AValue);
  Result := Self;
end;

function TTgInlineQueryResultsButtonImpl.WithStartParameter(const AValue: string): ITgInlineQueryResultsButton;
begin
  SetStr('start_parameter', AValue);
  Result := Self;
end;

{ TTgInlineQueryResultArticleImpl }

function TTgInlineQueryResultArticleImpl.WithId(const AValue: string): ITgInlineQueryResultArticle;
begin
  SetStr('id', AValue);
  Result := Self;
end;

function TTgInlineQueryResultArticleImpl.WithTitle(const AValue: string): ITgInlineQueryResultArticle;
begin
  SetStr('title', AValue);
  Result := Self;
end;

function TTgInlineQueryResultArticleImpl.WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultArticle;
begin
  SetObject('input_message_content', AValue.Value);
  Result := Self;
end;

function TTgInlineQueryResultArticleImpl.WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultArticle;
begin
  SetObject('reply_markup', AValue);
  Result := Self;
end;

function TTgInlineQueryResultArticleImpl.WithUrl(const AValue: string): ITgInlineQueryResultArticle;
begin
  SetStr('url', AValue);
  Result := Self;
end;

function TTgInlineQueryResultArticleImpl.WithDescription(const AValue: string): ITgInlineQueryResultArticle;
begin
  SetStr('description', AValue);
  Result := Self;
end;

function TTgInlineQueryResultArticleImpl.WithThumbnailUrl(const AValue: string): ITgInlineQueryResultArticle;
begin
  SetStr('thumbnail_url', AValue);
  Result := Self;
end;

function TTgInlineQueryResultArticleImpl.WithThumbnailWidth(AValue: Integer): ITgInlineQueryResultArticle;
begin
  SetInt('thumbnail_width', AValue);
  Result := Self;
end;

function TTgInlineQueryResultArticleImpl.WithThumbnailHeight(AValue: Integer): ITgInlineQueryResultArticle;
begin
  SetInt('thumbnail_height', AValue);
  Result := Self;
end;

{ TTgInlineQueryResultPhotoImpl }

function TTgInlineQueryResultPhotoImpl.WithId(const AValue: string): ITgInlineQueryResultPhoto;
begin
  SetStr('id', AValue);
  Result := Self;
end;

function TTgInlineQueryResultPhotoImpl.WithPhotoUrl(const AValue: string): ITgInlineQueryResultPhoto;
begin
  SetStr('photo_url', AValue);
  Result := Self;
end;

function TTgInlineQueryResultPhotoImpl.WithThumbnailUrl(const AValue: string): ITgInlineQueryResultPhoto;
begin
  SetStr('thumbnail_url', AValue);
  Result := Self;
end;

function TTgInlineQueryResultPhotoImpl.WithPhotoWidth(AValue: Integer): ITgInlineQueryResultPhoto;
begin
  SetInt('photo_width', AValue);
  Result := Self;
end;

function TTgInlineQueryResultPhotoImpl.WithPhotoHeight(AValue: Integer): ITgInlineQueryResultPhoto;
begin
  SetInt('photo_height', AValue);
  Result := Self;
end;

function TTgInlineQueryResultPhotoImpl.WithTitle(const AValue: string): ITgInlineQueryResultPhoto;
begin
  SetStr('title', AValue);
  Result := Self;
end;

function TTgInlineQueryResultPhotoImpl.WithDescription(const AValue: string): ITgInlineQueryResultPhoto;
begin
  SetStr('description', AValue);
  Result := Self;
end;

function TTgInlineQueryResultPhotoImpl.WithCaption(const AValue: string): ITgInlineQueryResultPhoto;
begin
  SetStr('caption', AValue);
  Result := Self;
end;

function TTgInlineQueryResultPhotoImpl.WithParseMode(const AValue: string): ITgInlineQueryResultPhoto;
begin
  SetStr('parse_mode', AValue);
  Result := Self;
end;

function TTgInlineQueryResultPhotoImpl.WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultPhoto;
begin
  SetObjects('caption_entities', TTgDto.ToIntf<ITgMessageEntity>(AValue));
  Result := Self;
end;

function TTgInlineQueryResultPhotoImpl.WithShowCaptionAboveMedia(AValue: Boolean): ITgInlineQueryResultPhoto;
begin
  SetBool('show_caption_above_media', AValue);
  Result := Self;
end;

function TTgInlineQueryResultPhotoImpl.WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultPhoto;
begin
  SetObject('reply_markup', AValue);
  Result := Self;
end;

function TTgInlineQueryResultPhotoImpl.WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultPhoto;
begin
  SetObject('input_message_content', AValue.Value);
  Result := Self;
end;

{ TTgInlineQueryResultGifImpl }

function TTgInlineQueryResultGifImpl.WithId(const AValue: string): ITgInlineQueryResultGif;
begin
  SetStr('id', AValue);
  Result := Self;
end;

function TTgInlineQueryResultGifImpl.WithGifUrl(const AValue: string): ITgInlineQueryResultGif;
begin
  SetStr('gif_url', AValue);
  Result := Self;
end;

function TTgInlineQueryResultGifImpl.WithGifWidth(AValue: Integer): ITgInlineQueryResultGif;
begin
  SetInt('gif_width', AValue);
  Result := Self;
end;

function TTgInlineQueryResultGifImpl.WithGifHeight(AValue: Integer): ITgInlineQueryResultGif;
begin
  SetInt('gif_height', AValue);
  Result := Self;
end;

function TTgInlineQueryResultGifImpl.WithGifDuration(AValue: Integer): ITgInlineQueryResultGif;
begin
  SetInt('gif_duration', AValue);
  Result := Self;
end;

function TTgInlineQueryResultGifImpl.WithThumbnailUrl(const AValue: string): ITgInlineQueryResultGif;
begin
  SetStr('thumbnail_url', AValue);
  Result := Self;
end;

function TTgInlineQueryResultGifImpl.WithThumbnailMimeType(const AValue: string): ITgInlineQueryResultGif;
begin
  SetStr('thumbnail_mime_type', AValue);
  Result := Self;
end;

function TTgInlineQueryResultGifImpl.WithTitle(const AValue: string): ITgInlineQueryResultGif;
begin
  SetStr('title', AValue);
  Result := Self;
end;

function TTgInlineQueryResultGifImpl.WithCaption(const AValue: string): ITgInlineQueryResultGif;
begin
  SetStr('caption', AValue);
  Result := Self;
end;

function TTgInlineQueryResultGifImpl.WithParseMode(const AValue: string): ITgInlineQueryResultGif;
begin
  SetStr('parse_mode', AValue);
  Result := Self;
end;

function TTgInlineQueryResultGifImpl.WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultGif;
begin
  SetObjects('caption_entities', TTgDto.ToIntf<ITgMessageEntity>(AValue));
  Result := Self;
end;

function TTgInlineQueryResultGifImpl.WithShowCaptionAboveMedia(AValue: Boolean): ITgInlineQueryResultGif;
begin
  SetBool('show_caption_above_media', AValue);
  Result := Self;
end;

function TTgInlineQueryResultGifImpl.WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultGif;
begin
  SetObject('reply_markup', AValue);
  Result := Self;
end;

function TTgInlineQueryResultGifImpl.WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultGif;
begin
  SetObject('input_message_content', AValue.Value);
  Result := Self;
end;

{ TTgInlineQueryResultMpeg4GifImpl }

function TTgInlineQueryResultMpeg4GifImpl.WithId(const AValue: string): ITgInlineQueryResultMpeg4Gif;
begin
  SetStr('id', AValue);
  Result := Self;
end;

function TTgInlineQueryResultMpeg4GifImpl.WithMpeg4Url(const AValue: string): ITgInlineQueryResultMpeg4Gif;
begin
  SetStr('mpeg4_url', AValue);
  Result := Self;
end;

function TTgInlineQueryResultMpeg4GifImpl.WithMpeg4Width(AValue: Integer): ITgInlineQueryResultMpeg4Gif;
begin
  SetInt('mpeg4_width', AValue);
  Result := Self;
end;

function TTgInlineQueryResultMpeg4GifImpl.WithMpeg4Height(AValue: Integer): ITgInlineQueryResultMpeg4Gif;
begin
  SetInt('mpeg4_height', AValue);
  Result := Self;
end;

function TTgInlineQueryResultMpeg4GifImpl.WithMpeg4Duration(AValue: Integer): ITgInlineQueryResultMpeg4Gif;
begin
  SetInt('mpeg4_duration', AValue);
  Result := Self;
end;

function TTgInlineQueryResultMpeg4GifImpl.WithThumbnailUrl(const AValue: string): ITgInlineQueryResultMpeg4Gif;
begin
  SetStr('thumbnail_url', AValue);
  Result := Self;
end;

function TTgInlineQueryResultMpeg4GifImpl.WithThumbnailMimeType(const AValue: string): ITgInlineQueryResultMpeg4Gif;
begin
  SetStr('thumbnail_mime_type', AValue);
  Result := Self;
end;

function TTgInlineQueryResultMpeg4GifImpl.WithTitle(const AValue: string): ITgInlineQueryResultMpeg4Gif;
begin
  SetStr('title', AValue);
  Result := Self;
end;

function TTgInlineQueryResultMpeg4GifImpl.WithCaption(const AValue: string): ITgInlineQueryResultMpeg4Gif;
begin
  SetStr('caption', AValue);
  Result := Self;
end;

function TTgInlineQueryResultMpeg4GifImpl.WithParseMode(const AValue: string): ITgInlineQueryResultMpeg4Gif;
begin
  SetStr('parse_mode', AValue);
  Result := Self;
end;

function TTgInlineQueryResultMpeg4GifImpl.WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultMpeg4Gif;
begin
  SetObjects('caption_entities', TTgDto.ToIntf<ITgMessageEntity>(AValue));
  Result := Self;
end;

function TTgInlineQueryResultMpeg4GifImpl.WithShowCaptionAboveMedia(AValue: Boolean): ITgInlineQueryResultMpeg4Gif;
begin
  SetBool('show_caption_above_media', AValue);
  Result := Self;
end;

function TTgInlineQueryResultMpeg4GifImpl.WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultMpeg4Gif;
begin
  SetObject('reply_markup', AValue);
  Result := Self;
end;

function TTgInlineQueryResultMpeg4GifImpl.WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultMpeg4Gif;
begin
  SetObject('input_message_content', AValue.Value);
  Result := Self;
end;

{ TTgInlineQueryResultVideoImpl }

function TTgInlineQueryResultVideoImpl.WithId(const AValue: string): ITgInlineQueryResultVideo;
begin
  SetStr('id', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVideoImpl.WithVideoUrl(const AValue: string): ITgInlineQueryResultVideo;
begin
  SetStr('video_url', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVideoImpl.WithMimeType(const AValue: string): ITgInlineQueryResultVideo;
begin
  SetStr('mime_type', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVideoImpl.WithThumbnailUrl(const AValue: string): ITgInlineQueryResultVideo;
begin
  SetStr('thumbnail_url', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVideoImpl.WithTitle(const AValue: string): ITgInlineQueryResultVideo;
begin
  SetStr('title', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVideoImpl.WithCaption(const AValue: string): ITgInlineQueryResultVideo;
begin
  SetStr('caption', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVideoImpl.WithParseMode(const AValue: string): ITgInlineQueryResultVideo;
begin
  SetStr('parse_mode', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVideoImpl.WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultVideo;
begin
  SetObjects('caption_entities', TTgDto.ToIntf<ITgMessageEntity>(AValue));
  Result := Self;
end;

function TTgInlineQueryResultVideoImpl.WithShowCaptionAboveMedia(AValue: Boolean): ITgInlineQueryResultVideo;
begin
  SetBool('show_caption_above_media', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVideoImpl.WithVideoWidth(AValue: Integer): ITgInlineQueryResultVideo;
begin
  SetInt('video_width', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVideoImpl.WithVideoHeight(AValue: Integer): ITgInlineQueryResultVideo;
begin
  SetInt('video_height', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVideoImpl.WithVideoDuration(AValue: Integer): ITgInlineQueryResultVideo;
begin
  SetInt('video_duration', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVideoImpl.WithDescription(const AValue: string): ITgInlineQueryResultVideo;
begin
  SetStr('description', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVideoImpl.WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultVideo;
begin
  SetObject('reply_markup', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVideoImpl.WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultVideo;
begin
  SetObject('input_message_content', AValue.Value);
  Result := Self;
end;

{ TTgInlineQueryResultAudioImpl }

function TTgInlineQueryResultAudioImpl.WithId(const AValue: string): ITgInlineQueryResultAudio;
begin
  SetStr('id', AValue);
  Result := Self;
end;

function TTgInlineQueryResultAudioImpl.WithAudioUrl(const AValue: string): ITgInlineQueryResultAudio;
begin
  SetStr('audio_url', AValue);
  Result := Self;
end;

function TTgInlineQueryResultAudioImpl.WithTitle(const AValue: string): ITgInlineQueryResultAudio;
begin
  SetStr('title', AValue);
  Result := Self;
end;

function TTgInlineQueryResultAudioImpl.WithCaption(const AValue: string): ITgInlineQueryResultAudio;
begin
  SetStr('caption', AValue);
  Result := Self;
end;

function TTgInlineQueryResultAudioImpl.WithParseMode(const AValue: string): ITgInlineQueryResultAudio;
begin
  SetStr('parse_mode', AValue);
  Result := Self;
end;

function TTgInlineQueryResultAudioImpl.WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultAudio;
begin
  SetObjects('caption_entities', TTgDto.ToIntf<ITgMessageEntity>(AValue));
  Result := Self;
end;

function TTgInlineQueryResultAudioImpl.WithPerformer(const AValue: string): ITgInlineQueryResultAudio;
begin
  SetStr('performer', AValue);
  Result := Self;
end;

function TTgInlineQueryResultAudioImpl.WithAudioDuration(AValue: Integer): ITgInlineQueryResultAudio;
begin
  SetInt('audio_duration', AValue);
  Result := Self;
end;

function TTgInlineQueryResultAudioImpl.WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultAudio;
begin
  SetObject('reply_markup', AValue);
  Result := Self;
end;

function TTgInlineQueryResultAudioImpl.WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultAudio;
begin
  SetObject('input_message_content', AValue.Value);
  Result := Self;
end;

{ TTgInlineQueryResultVoiceImpl }

function TTgInlineQueryResultVoiceImpl.WithId(const AValue: string): ITgInlineQueryResultVoice;
begin
  SetStr('id', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVoiceImpl.WithVoiceUrl(const AValue: string): ITgInlineQueryResultVoice;
begin
  SetStr('voice_url', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVoiceImpl.WithTitle(const AValue: string): ITgInlineQueryResultVoice;
begin
  SetStr('title', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVoiceImpl.WithCaption(const AValue: string): ITgInlineQueryResultVoice;
begin
  SetStr('caption', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVoiceImpl.WithParseMode(const AValue: string): ITgInlineQueryResultVoice;
begin
  SetStr('parse_mode', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVoiceImpl.WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultVoice;
begin
  SetObjects('caption_entities', TTgDto.ToIntf<ITgMessageEntity>(AValue));
  Result := Self;
end;

function TTgInlineQueryResultVoiceImpl.WithVoiceDuration(AValue: Integer): ITgInlineQueryResultVoice;
begin
  SetInt('voice_duration', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVoiceImpl.WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultVoice;
begin
  SetObject('reply_markup', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVoiceImpl.WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultVoice;
begin
  SetObject('input_message_content', AValue.Value);
  Result := Self;
end;

{ TTgInlineQueryResultDocumentImpl }

function TTgInlineQueryResultDocumentImpl.WithId(const AValue: string): ITgInlineQueryResultDocument;
begin
  SetStr('id', AValue);
  Result := Self;
end;

function TTgInlineQueryResultDocumentImpl.WithTitle(const AValue: string): ITgInlineQueryResultDocument;
begin
  SetStr('title', AValue);
  Result := Self;
end;

function TTgInlineQueryResultDocumentImpl.WithCaption(const AValue: string): ITgInlineQueryResultDocument;
begin
  SetStr('caption', AValue);
  Result := Self;
end;

function TTgInlineQueryResultDocumentImpl.WithParseMode(const AValue: string): ITgInlineQueryResultDocument;
begin
  SetStr('parse_mode', AValue);
  Result := Self;
end;

function TTgInlineQueryResultDocumentImpl.WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultDocument;
begin
  SetObjects('caption_entities', TTgDto.ToIntf<ITgMessageEntity>(AValue));
  Result := Self;
end;

function TTgInlineQueryResultDocumentImpl.WithDocumentUrl(const AValue: string): ITgInlineQueryResultDocument;
begin
  SetStr('document_url', AValue);
  Result := Self;
end;

function TTgInlineQueryResultDocumentImpl.WithMimeType(const AValue: string): ITgInlineQueryResultDocument;
begin
  SetStr('mime_type', AValue);
  Result := Self;
end;

function TTgInlineQueryResultDocumentImpl.WithDescription(const AValue: string): ITgInlineQueryResultDocument;
begin
  SetStr('description', AValue);
  Result := Self;
end;

function TTgInlineQueryResultDocumentImpl.WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultDocument;
begin
  SetObject('reply_markup', AValue);
  Result := Self;
end;

function TTgInlineQueryResultDocumentImpl.WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultDocument;
begin
  SetObject('input_message_content', AValue.Value);
  Result := Self;
end;

function TTgInlineQueryResultDocumentImpl.WithThumbnailUrl(const AValue: string): ITgInlineQueryResultDocument;
begin
  SetStr('thumbnail_url', AValue);
  Result := Self;
end;

function TTgInlineQueryResultDocumentImpl.WithThumbnailWidth(AValue: Integer): ITgInlineQueryResultDocument;
begin
  SetInt('thumbnail_width', AValue);
  Result := Self;
end;

function TTgInlineQueryResultDocumentImpl.WithThumbnailHeight(AValue: Integer): ITgInlineQueryResultDocument;
begin
  SetInt('thumbnail_height', AValue);
  Result := Self;
end;

{ TTgInlineQueryResultLocationImpl }

function TTgInlineQueryResultLocationImpl.WithId(const AValue: string): ITgInlineQueryResultLocation;
begin
  SetStr('id', AValue);
  Result := Self;
end;

function TTgInlineQueryResultLocationImpl.WithLatitude(AValue: Double): ITgInlineQueryResultLocation;
begin
  SetDouble('latitude', AValue);
  Result := Self;
end;

function TTgInlineQueryResultLocationImpl.WithLongitude(AValue: Double): ITgInlineQueryResultLocation;
begin
  SetDouble('longitude', AValue);
  Result := Self;
end;

function TTgInlineQueryResultLocationImpl.WithTitle(const AValue: string): ITgInlineQueryResultLocation;
begin
  SetStr('title', AValue);
  Result := Self;
end;

function TTgInlineQueryResultLocationImpl.WithHorizontalAccuracy(AValue: Double): ITgInlineQueryResultLocation;
begin
  SetDouble('horizontal_accuracy', AValue);
  Result := Self;
end;

function TTgInlineQueryResultLocationImpl.WithLivePeriod(AValue: Integer): ITgInlineQueryResultLocation;
begin
  SetInt('live_period', AValue);
  Result := Self;
end;

function TTgInlineQueryResultLocationImpl.WithHeading(AValue: Integer): ITgInlineQueryResultLocation;
begin
  SetInt('heading', AValue);
  Result := Self;
end;

function TTgInlineQueryResultLocationImpl.WithProximityAlertRadius(AValue: Integer): ITgInlineQueryResultLocation;
begin
  SetInt('proximity_alert_radius', AValue);
  Result := Self;
end;

function TTgInlineQueryResultLocationImpl.WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultLocation;
begin
  SetObject('reply_markup', AValue);
  Result := Self;
end;

function TTgInlineQueryResultLocationImpl.WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultLocation;
begin
  SetObject('input_message_content', AValue.Value);
  Result := Self;
end;

function TTgInlineQueryResultLocationImpl.WithThumbnailUrl(const AValue: string): ITgInlineQueryResultLocation;
begin
  SetStr('thumbnail_url', AValue);
  Result := Self;
end;

function TTgInlineQueryResultLocationImpl.WithThumbnailWidth(AValue: Integer): ITgInlineQueryResultLocation;
begin
  SetInt('thumbnail_width', AValue);
  Result := Self;
end;

function TTgInlineQueryResultLocationImpl.WithThumbnailHeight(AValue: Integer): ITgInlineQueryResultLocation;
begin
  SetInt('thumbnail_height', AValue);
  Result := Self;
end;

{ TTgInlineQueryResultVenueImpl }

function TTgInlineQueryResultVenueImpl.WithId(const AValue: string): ITgInlineQueryResultVenue;
begin
  SetStr('id', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVenueImpl.WithLatitude(AValue: Double): ITgInlineQueryResultVenue;
begin
  SetDouble('latitude', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVenueImpl.WithLongitude(AValue: Double): ITgInlineQueryResultVenue;
begin
  SetDouble('longitude', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVenueImpl.WithTitle(const AValue: string): ITgInlineQueryResultVenue;
begin
  SetStr('title', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVenueImpl.WithAddress(const AValue: string): ITgInlineQueryResultVenue;
begin
  SetStr('address', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVenueImpl.WithFoursquareId(const AValue: string): ITgInlineQueryResultVenue;
begin
  SetStr('foursquare_id', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVenueImpl.WithFoursquareType(const AValue: string): ITgInlineQueryResultVenue;
begin
  SetStr('foursquare_type', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVenueImpl.WithGooglePlaceId(const AValue: string): ITgInlineQueryResultVenue;
begin
  SetStr('google_place_id', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVenueImpl.WithGooglePlaceType(const AValue: string): ITgInlineQueryResultVenue;
begin
  SetStr('google_place_type', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVenueImpl.WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultVenue;
begin
  SetObject('reply_markup', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVenueImpl.WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultVenue;
begin
  SetObject('input_message_content', AValue.Value);
  Result := Self;
end;

function TTgInlineQueryResultVenueImpl.WithThumbnailUrl(const AValue: string): ITgInlineQueryResultVenue;
begin
  SetStr('thumbnail_url', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVenueImpl.WithThumbnailWidth(AValue: Integer): ITgInlineQueryResultVenue;
begin
  SetInt('thumbnail_width', AValue);
  Result := Self;
end;

function TTgInlineQueryResultVenueImpl.WithThumbnailHeight(AValue: Integer): ITgInlineQueryResultVenue;
begin
  SetInt('thumbnail_height', AValue);
  Result := Self;
end;

{ TTgInlineQueryResultContactImpl }

function TTgInlineQueryResultContactImpl.WithId(const AValue: string): ITgInlineQueryResultContact;
begin
  SetStr('id', AValue);
  Result := Self;
end;

function TTgInlineQueryResultContactImpl.WithPhoneNumber(const AValue: string): ITgInlineQueryResultContact;
begin
  SetStr('phone_number', AValue);
  Result := Self;
end;

function TTgInlineQueryResultContactImpl.WithFirstName(const AValue: string): ITgInlineQueryResultContact;
begin
  SetStr('first_name', AValue);
  Result := Self;
end;

function TTgInlineQueryResultContactImpl.WithLastName(const AValue: string): ITgInlineQueryResultContact;
begin
  SetStr('last_name', AValue);
  Result := Self;
end;

function TTgInlineQueryResultContactImpl.WithVcard(const AValue: string): ITgInlineQueryResultContact;
begin
  SetStr('vcard', AValue);
  Result := Self;
end;

function TTgInlineQueryResultContactImpl.WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultContact;
begin
  SetObject('reply_markup', AValue);
  Result := Self;
end;

function TTgInlineQueryResultContactImpl.WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultContact;
begin
  SetObject('input_message_content', AValue.Value);
  Result := Self;
end;

function TTgInlineQueryResultContactImpl.WithThumbnailUrl(const AValue: string): ITgInlineQueryResultContact;
begin
  SetStr('thumbnail_url', AValue);
  Result := Self;
end;

function TTgInlineQueryResultContactImpl.WithThumbnailWidth(AValue: Integer): ITgInlineQueryResultContact;
begin
  SetInt('thumbnail_width', AValue);
  Result := Self;
end;

function TTgInlineQueryResultContactImpl.WithThumbnailHeight(AValue: Integer): ITgInlineQueryResultContact;
begin
  SetInt('thumbnail_height', AValue);
  Result := Self;
end;

{ TTgInlineQueryResultGameImpl }

function TTgInlineQueryResultGameImpl.WithId(const AValue: string): ITgInlineQueryResultGame;
begin
  SetStr('id', AValue);
  Result := Self;
end;

function TTgInlineQueryResultGameImpl.WithGameShortName(const AValue: string): ITgInlineQueryResultGame;
begin
  SetStr('game_short_name', AValue);
  Result := Self;
end;

function TTgInlineQueryResultGameImpl.WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultGame;
begin
  SetObject('reply_markup', AValue);
  Result := Self;
end;

{ TTgInlineQueryResultCachedPhotoImpl }

function TTgInlineQueryResultCachedPhotoImpl.WithId(const AValue: string): ITgInlineQueryResultCachedPhoto;
begin
  SetStr('id', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedPhotoImpl.WithPhotoFileId(const AValue: string): ITgInlineQueryResultCachedPhoto;
begin
  SetStr('photo_file_id', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedPhotoImpl.WithTitle(const AValue: string): ITgInlineQueryResultCachedPhoto;
begin
  SetStr('title', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedPhotoImpl.WithDescription(const AValue: string): ITgInlineQueryResultCachedPhoto;
begin
  SetStr('description', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedPhotoImpl.WithCaption(const AValue: string): ITgInlineQueryResultCachedPhoto;
begin
  SetStr('caption', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedPhotoImpl.WithParseMode(const AValue: string): ITgInlineQueryResultCachedPhoto;
begin
  SetStr('parse_mode', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedPhotoImpl.WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultCachedPhoto;
begin
  SetObjects('caption_entities', TTgDto.ToIntf<ITgMessageEntity>(AValue));
  Result := Self;
end;

function TTgInlineQueryResultCachedPhotoImpl.WithShowCaptionAboveMedia(AValue: Boolean): ITgInlineQueryResultCachedPhoto;
begin
  SetBool('show_caption_above_media', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedPhotoImpl.WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultCachedPhoto;
begin
  SetObject('reply_markup', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedPhotoImpl.WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultCachedPhoto;
begin
  SetObject('input_message_content', AValue.Value);
  Result := Self;
end;

{ TTgInlineQueryResultCachedGifImpl }

function TTgInlineQueryResultCachedGifImpl.WithId(const AValue: string): ITgInlineQueryResultCachedGif;
begin
  SetStr('id', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedGifImpl.WithGifFileId(const AValue: string): ITgInlineQueryResultCachedGif;
begin
  SetStr('gif_file_id', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedGifImpl.WithTitle(const AValue: string): ITgInlineQueryResultCachedGif;
begin
  SetStr('title', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedGifImpl.WithCaption(const AValue: string): ITgInlineQueryResultCachedGif;
begin
  SetStr('caption', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedGifImpl.WithParseMode(const AValue: string): ITgInlineQueryResultCachedGif;
begin
  SetStr('parse_mode', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedGifImpl.WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultCachedGif;
begin
  SetObjects('caption_entities', TTgDto.ToIntf<ITgMessageEntity>(AValue));
  Result := Self;
end;

function TTgInlineQueryResultCachedGifImpl.WithShowCaptionAboveMedia(AValue: Boolean): ITgInlineQueryResultCachedGif;
begin
  SetBool('show_caption_above_media', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedGifImpl.WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultCachedGif;
begin
  SetObject('reply_markup', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedGifImpl.WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultCachedGif;
begin
  SetObject('input_message_content', AValue.Value);
  Result := Self;
end;

{ TTgInlineQueryResultCachedMpeg4GifImpl }

function TTgInlineQueryResultCachedMpeg4GifImpl.WithId(const AValue: string): ITgInlineQueryResultCachedMpeg4Gif;
begin
  SetStr('id', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedMpeg4GifImpl.WithMpeg4FileId(const AValue: string): ITgInlineQueryResultCachedMpeg4Gif;
begin
  SetStr('mpeg4_file_id', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedMpeg4GifImpl.WithTitle(const AValue: string): ITgInlineQueryResultCachedMpeg4Gif;
begin
  SetStr('title', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedMpeg4GifImpl.WithCaption(const AValue: string): ITgInlineQueryResultCachedMpeg4Gif;
begin
  SetStr('caption', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedMpeg4GifImpl.WithParseMode(const AValue: string): ITgInlineQueryResultCachedMpeg4Gif;
begin
  SetStr('parse_mode', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedMpeg4GifImpl.WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultCachedMpeg4Gif;
begin
  SetObjects('caption_entities', TTgDto.ToIntf<ITgMessageEntity>(AValue));
  Result := Self;
end;

function TTgInlineQueryResultCachedMpeg4GifImpl.WithShowCaptionAboveMedia(AValue: Boolean): ITgInlineQueryResultCachedMpeg4Gif;
begin
  SetBool('show_caption_above_media', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedMpeg4GifImpl.WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultCachedMpeg4Gif;
begin
  SetObject('reply_markup', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedMpeg4GifImpl.WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultCachedMpeg4Gif;
begin
  SetObject('input_message_content', AValue.Value);
  Result := Self;
end;

{ TTgInlineQueryResultCachedStickerImpl }

function TTgInlineQueryResultCachedStickerImpl.WithId(const AValue: string): ITgInlineQueryResultCachedSticker;
begin
  SetStr('id', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedStickerImpl.WithStickerFileId(const AValue: string): ITgInlineQueryResultCachedSticker;
begin
  SetStr('sticker_file_id', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedStickerImpl.WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultCachedSticker;
begin
  SetObject('reply_markup', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedStickerImpl.WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultCachedSticker;
begin
  SetObject('input_message_content', AValue.Value);
  Result := Self;
end;

{ TTgInlineQueryResultCachedDocumentImpl }

function TTgInlineQueryResultCachedDocumentImpl.WithId(const AValue: string): ITgInlineQueryResultCachedDocument;
begin
  SetStr('id', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedDocumentImpl.WithTitle(const AValue: string): ITgInlineQueryResultCachedDocument;
begin
  SetStr('title', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedDocumentImpl.WithDocumentFileId(const AValue: string): ITgInlineQueryResultCachedDocument;
begin
  SetStr('document_file_id', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedDocumentImpl.WithDescription(const AValue: string): ITgInlineQueryResultCachedDocument;
begin
  SetStr('description', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedDocumentImpl.WithCaption(const AValue: string): ITgInlineQueryResultCachedDocument;
begin
  SetStr('caption', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedDocumentImpl.WithParseMode(const AValue: string): ITgInlineQueryResultCachedDocument;
begin
  SetStr('parse_mode', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedDocumentImpl.WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultCachedDocument;
begin
  SetObjects('caption_entities', TTgDto.ToIntf<ITgMessageEntity>(AValue));
  Result := Self;
end;

function TTgInlineQueryResultCachedDocumentImpl.WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultCachedDocument;
begin
  SetObject('reply_markup', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedDocumentImpl.WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultCachedDocument;
begin
  SetObject('input_message_content', AValue.Value);
  Result := Self;
end;

{ TTgInlineQueryResultCachedVideoImpl }

function TTgInlineQueryResultCachedVideoImpl.WithId(const AValue: string): ITgInlineQueryResultCachedVideo;
begin
  SetStr('id', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedVideoImpl.WithVideoFileId(const AValue: string): ITgInlineQueryResultCachedVideo;
begin
  SetStr('video_file_id', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedVideoImpl.WithTitle(const AValue: string): ITgInlineQueryResultCachedVideo;
begin
  SetStr('title', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedVideoImpl.WithDescription(const AValue: string): ITgInlineQueryResultCachedVideo;
begin
  SetStr('description', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedVideoImpl.WithCaption(const AValue: string): ITgInlineQueryResultCachedVideo;
begin
  SetStr('caption', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedVideoImpl.WithParseMode(const AValue: string): ITgInlineQueryResultCachedVideo;
begin
  SetStr('parse_mode', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedVideoImpl.WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultCachedVideo;
begin
  SetObjects('caption_entities', TTgDto.ToIntf<ITgMessageEntity>(AValue));
  Result := Self;
end;

function TTgInlineQueryResultCachedVideoImpl.WithShowCaptionAboveMedia(AValue: Boolean): ITgInlineQueryResultCachedVideo;
begin
  SetBool('show_caption_above_media', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedVideoImpl.WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultCachedVideo;
begin
  SetObject('reply_markup', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedVideoImpl.WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultCachedVideo;
begin
  SetObject('input_message_content', AValue.Value);
  Result := Self;
end;

{ TTgInlineQueryResultCachedVoiceImpl }

function TTgInlineQueryResultCachedVoiceImpl.WithId(const AValue: string): ITgInlineQueryResultCachedVoice;
begin
  SetStr('id', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedVoiceImpl.WithVoiceFileId(const AValue: string): ITgInlineQueryResultCachedVoice;
begin
  SetStr('voice_file_id', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedVoiceImpl.WithTitle(const AValue: string): ITgInlineQueryResultCachedVoice;
begin
  SetStr('title', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedVoiceImpl.WithCaption(const AValue: string): ITgInlineQueryResultCachedVoice;
begin
  SetStr('caption', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedVoiceImpl.WithParseMode(const AValue: string): ITgInlineQueryResultCachedVoice;
begin
  SetStr('parse_mode', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedVoiceImpl.WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultCachedVoice;
begin
  SetObjects('caption_entities', TTgDto.ToIntf<ITgMessageEntity>(AValue));
  Result := Self;
end;

function TTgInlineQueryResultCachedVoiceImpl.WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultCachedVoice;
begin
  SetObject('reply_markup', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedVoiceImpl.WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultCachedVoice;
begin
  SetObject('input_message_content', AValue.Value);
  Result := Self;
end;

{ TTgInlineQueryResultCachedAudioImpl }

function TTgInlineQueryResultCachedAudioImpl.WithId(const AValue: string): ITgInlineQueryResultCachedAudio;
begin
  SetStr('id', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedAudioImpl.WithAudioFileId(const AValue: string): ITgInlineQueryResultCachedAudio;
begin
  SetStr('audio_file_id', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedAudioImpl.WithCaption(const AValue: string): ITgInlineQueryResultCachedAudio;
begin
  SetStr('caption', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedAudioImpl.WithParseMode(const AValue: string): ITgInlineQueryResultCachedAudio;
begin
  SetStr('parse_mode', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedAudioImpl.WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultCachedAudio;
begin
  SetObjects('caption_entities', TTgDto.ToIntf<ITgMessageEntity>(AValue));
  Result := Self;
end;

function TTgInlineQueryResultCachedAudioImpl.WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultCachedAudio;
begin
  SetObject('reply_markup', AValue);
  Result := Self;
end;

function TTgInlineQueryResultCachedAudioImpl.WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultCachedAudio;
begin
  SetObject('input_message_content', AValue.Value);
  Result := Self;
end;

{ TTgInputTextMessageContentImpl }

function TTgInputTextMessageContentImpl.WithMessageText(const AValue: string): ITgInputTextMessageContent;
begin
  SetStr('message_text', AValue);
  Result := Self;
end;

function TTgInputTextMessageContentImpl.WithParseMode(const AValue: string): ITgInputTextMessageContent;
begin
  SetStr('parse_mode', AValue);
  Result := Self;
end;

function TTgInputTextMessageContentImpl.WithEntities(const AValue: array of ITgMessageEntity): ITgInputTextMessageContent;
begin
  SetObjects('entities', TTgDto.ToIntf<ITgMessageEntity>(AValue));
  Result := Self;
end;

function TTgInputTextMessageContentImpl.WithLinkPreviewOptions(const AValue: ITgLinkPreviewOptions): ITgInputTextMessageContent;
begin
  SetObject('link_preview_options', AValue);
  Result := Self;
end;

{ TTgInputRichMessageContentImpl }

function TTgInputRichMessageContentImpl.WithRichMessage(const AValue: ITgInputRichMessage): ITgInputRichMessageContent;
begin
  SetObject('rich_message', AValue);
  Result := Self;
end;

{ TTgInputLocationMessageContentImpl }

function TTgInputLocationMessageContentImpl.WithLatitude(AValue: Double): ITgInputLocationMessageContent;
begin
  SetDouble('latitude', AValue);
  Result := Self;
end;

function TTgInputLocationMessageContentImpl.WithLongitude(AValue: Double): ITgInputLocationMessageContent;
begin
  SetDouble('longitude', AValue);
  Result := Self;
end;

function TTgInputLocationMessageContentImpl.WithHorizontalAccuracy(AValue: Double): ITgInputLocationMessageContent;
begin
  SetDouble('horizontal_accuracy', AValue);
  Result := Self;
end;

function TTgInputLocationMessageContentImpl.WithLivePeriod(AValue: Integer): ITgInputLocationMessageContent;
begin
  SetInt('live_period', AValue);
  Result := Self;
end;

function TTgInputLocationMessageContentImpl.WithHeading(AValue: Integer): ITgInputLocationMessageContent;
begin
  SetInt('heading', AValue);
  Result := Self;
end;

function TTgInputLocationMessageContentImpl.WithProximityAlertRadius(AValue: Integer): ITgInputLocationMessageContent;
begin
  SetInt('proximity_alert_radius', AValue);
  Result := Self;
end;

{ TTgInputVenueMessageContentImpl }

function TTgInputVenueMessageContentImpl.WithLatitude(AValue: Double): ITgInputVenueMessageContent;
begin
  SetDouble('latitude', AValue);
  Result := Self;
end;

function TTgInputVenueMessageContentImpl.WithLongitude(AValue: Double): ITgInputVenueMessageContent;
begin
  SetDouble('longitude', AValue);
  Result := Self;
end;

function TTgInputVenueMessageContentImpl.WithTitle(const AValue: string): ITgInputVenueMessageContent;
begin
  SetStr('title', AValue);
  Result := Self;
end;

function TTgInputVenueMessageContentImpl.WithAddress(const AValue: string): ITgInputVenueMessageContent;
begin
  SetStr('address', AValue);
  Result := Self;
end;

function TTgInputVenueMessageContentImpl.WithFoursquareId(const AValue: string): ITgInputVenueMessageContent;
begin
  SetStr('foursquare_id', AValue);
  Result := Self;
end;

function TTgInputVenueMessageContentImpl.WithFoursquareType(const AValue: string): ITgInputVenueMessageContent;
begin
  SetStr('foursquare_type', AValue);
  Result := Self;
end;

function TTgInputVenueMessageContentImpl.WithGooglePlaceId(const AValue: string): ITgInputVenueMessageContent;
begin
  SetStr('google_place_id', AValue);
  Result := Self;
end;

function TTgInputVenueMessageContentImpl.WithGooglePlaceType(const AValue: string): ITgInputVenueMessageContent;
begin
  SetStr('google_place_type', AValue);
  Result := Self;
end;

{ TTgInputContactMessageContentImpl }

function TTgInputContactMessageContentImpl.WithPhoneNumber(const AValue: string): ITgInputContactMessageContent;
begin
  SetStr('phone_number', AValue);
  Result := Self;
end;

function TTgInputContactMessageContentImpl.WithFirstName(const AValue: string): ITgInputContactMessageContent;
begin
  SetStr('first_name', AValue);
  Result := Self;
end;

function TTgInputContactMessageContentImpl.WithLastName(const AValue: string): ITgInputContactMessageContent;
begin
  SetStr('last_name', AValue);
  Result := Self;
end;

function TTgInputContactMessageContentImpl.WithVcard(const AValue: string): ITgInputContactMessageContent;
begin
  SetStr('vcard', AValue);
  Result := Self;
end;

{ TTgInputInvoiceMessageContentImpl }

function TTgInputInvoiceMessageContentImpl.WithTitle(const AValue: string): ITgInputInvoiceMessageContent;
begin
  SetStr('title', AValue);
  Result := Self;
end;

function TTgInputInvoiceMessageContentImpl.WithDescription(const AValue: string): ITgInputInvoiceMessageContent;
begin
  SetStr('description', AValue);
  Result := Self;
end;

function TTgInputInvoiceMessageContentImpl.WithPayload(const AValue: string): ITgInputInvoiceMessageContent;
begin
  SetStr('payload', AValue);
  Result := Self;
end;

function TTgInputInvoiceMessageContentImpl.WithProviderToken(const AValue: string): ITgInputInvoiceMessageContent;
begin
  SetStr('provider_token', AValue);
  Result := Self;
end;

function TTgInputInvoiceMessageContentImpl.WithCurrency(const AValue: string): ITgInputInvoiceMessageContent;
begin
  SetStr('currency', AValue);
  Result := Self;
end;

function TTgInputInvoiceMessageContentImpl.WithPrices(const AValue: array of ITgLabeledPrice): ITgInputInvoiceMessageContent;
begin
  SetObjects('prices', TTgDto.ToIntf<ITgLabeledPrice>(AValue));
  Result := Self;
end;

function TTgInputInvoiceMessageContentImpl.WithMaxTipAmount(AValue: Integer): ITgInputInvoiceMessageContent;
begin
  SetInt('max_tip_amount', AValue);
  Result := Self;
end;

function TTgInputInvoiceMessageContentImpl.WithSuggestedTipAmounts(const AValue: TArray<Integer>): ITgInputInvoiceMessageContent;
begin
  SetIntegers('suggested_tip_amounts', AValue);
  Result := Self;
end;

function TTgInputInvoiceMessageContentImpl.WithProviderData(const AValue: string): ITgInputInvoiceMessageContent;
begin
  SetStr('provider_data', AValue);
  Result := Self;
end;

function TTgInputInvoiceMessageContentImpl.WithPhotoUrl(const AValue: string): ITgInputInvoiceMessageContent;
begin
  SetStr('photo_url', AValue);
  Result := Self;
end;

function TTgInputInvoiceMessageContentImpl.WithPhotoSize(AValue: Integer): ITgInputInvoiceMessageContent;
begin
  SetInt('photo_size', AValue);
  Result := Self;
end;

function TTgInputInvoiceMessageContentImpl.WithPhotoWidth(AValue: Integer): ITgInputInvoiceMessageContent;
begin
  SetInt('photo_width', AValue);
  Result := Self;
end;

function TTgInputInvoiceMessageContentImpl.WithPhotoHeight(AValue: Integer): ITgInputInvoiceMessageContent;
begin
  SetInt('photo_height', AValue);
  Result := Self;
end;

function TTgInputInvoiceMessageContentImpl.WithNeedName(AValue: Boolean): ITgInputInvoiceMessageContent;
begin
  SetBool('need_name', AValue);
  Result := Self;
end;

function TTgInputInvoiceMessageContentImpl.WithNeedPhoneNumber(AValue: Boolean): ITgInputInvoiceMessageContent;
begin
  SetBool('need_phone_number', AValue);
  Result := Self;
end;

function TTgInputInvoiceMessageContentImpl.WithNeedEmail(AValue: Boolean): ITgInputInvoiceMessageContent;
begin
  SetBool('need_email', AValue);
  Result := Self;
end;

function TTgInputInvoiceMessageContentImpl.WithNeedShippingAddress(AValue: Boolean): ITgInputInvoiceMessageContent;
begin
  SetBool('need_shipping_address', AValue);
  Result := Self;
end;

function TTgInputInvoiceMessageContentImpl.WithSendPhoneNumberToProvider(AValue: Boolean): ITgInputInvoiceMessageContent;
begin
  SetBool('send_phone_number_to_provider', AValue);
  Result := Self;
end;

function TTgInputInvoiceMessageContentImpl.WithSendEmailToProvider(AValue: Boolean): ITgInputInvoiceMessageContent;
begin
  SetBool('send_email_to_provider', AValue);
  Result := Self;
end;

function TTgInputInvoiceMessageContentImpl.WithIsFlexible(AValue: Boolean): ITgInputInvoiceMessageContent;
begin
  SetBool('is_flexible', AValue);
  Result := Self;
end;

{ TTgChosenInlineResultImpl }

function TTgChosenInlineResultImpl.GetResultId: string;
begin
  Result := TTgJson.GetStr(FJson, 'result_id');
end;

function TTgChosenInlineResultImpl.GetFrom: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'from'), JsonOwner);
end;

function TTgChosenInlineResultImpl.GetLocation: ITgLocation;
begin
  Result := TgMakeLocation(TTgJson.GetValue(FJson, 'location'), JsonOwner);
end;

function TTgChosenInlineResultImpl.GetInlineMessageId: string;
begin
  Result := TTgJson.GetStr(FJson, 'inline_message_id');
end;

function TTgChosenInlineResultImpl.GetQuery: string;
begin
  Result := TTgJson.GetStr(FJson, 'query');
end;

{ TTgLabeledPriceImpl }

function TTgLabeledPriceImpl.WithLabeledPriceLabel(const AValue: string): ITgLabeledPrice;
begin
  SetStr('label', AValue);
  Result := Self;
end;

function TTgLabeledPriceImpl.WithAmount(AValue: Integer): ITgLabeledPrice;
begin
  SetInt('amount', AValue);
  Result := Self;
end;

{ TTgInvoiceImpl }

function TTgInvoiceImpl.GetTitle: string;
begin
  Result := TTgJson.GetStr(FJson, 'title');
end;

function TTgInvoiceImpl.GetDescription: string;
begin
  Result := TTgJson.GetStr(FJson, 'description');
end;

function TTgInvoiceImpl.GetStartParameter: string;
begin
  Result := TTgJson.GetStr(FJson, 'start_parameter');
end;

function TTgInvoiceImpl.GetCurrency: string;
begin
  Result := TTgJson.GetStr(FJson, 'currency');
end;

function TTgInvoiceImpl.GetTotalAmount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'total_amount');
end;

{ TTgShippingAddressImpl }

function TTgShippingAddressImpl.GetCountryCode: string;
begin
  Result := TTgJson.GetStr(FJson, 'country_code');
end;

function TTgShippingAddressImpl.GetState: string;
begin
  Result := TTgJson.GetStr(FJson, 'state');
end;

function TTgShippingAddressImpl.GetCity: string;
begin
  Result := TTgJson.GetStr(FJson, 'city');
end;

function TTgShippingAddressImpl.GetStreetLine1: string;
begin
  Result := TTgJson.GetStr(FJson, 'street_line1');
end;

function TTgShippingAddressImpl.GetStreetLine2: string;
begin
  Result := TTgJson.GetStr(FJson, 'street_line2');
end;

function TTgShippingAddressImpl.GetPostCode: string;
begin
  Result := TTgJson.GetStr(FJson, 'post_code');
end;

{ TTgOrderInfoImpl }

function TTgOrderInfoImpl.GetName: string;
begin
  Result := TTgJson.GetStr(FJson, 'name');
end;

function TTgOrderInfoImpl.GetPhoneNumber: string;
begin
  Result := TTgJson.GetStr(FJson, 'phone_number');
end;

function TTgOrderInfoImpl.GetEmail: string;
begin
  Result := TTgJson.GetStr(FJson, 'email');
end;

function TTgOrderInfoImpl.GetShippingAddress: ITgShippingAddress;
begin
  Result := TgMakeShippingAddress(TTgJson.GetValue(FJson, 'shipping_address'), JsonOwner);
end;

{ TTgShippingOptionImpl }

function TTgShippingOptionImpl.WithId(const AValue: string): ITgShippingOption;
begin
  SetStr('id', AValue);
  Result := Self;
end;

function TTgShippingOptionImpl.WithTitle(const AValue: string): ITgShippingOption;
begin
  SetStr('title', AValue);
  Result := Self;
end;

function TTgShippingOptionImpl.WithPrices(const AValue: array of ITgLabeledPrice): ITgShippingOption;
begin
  SetObjects('prices', TTgDto.ToIntf<ITgLabeledPrice>(AValue));
  Result := Self;
end;

{ TTgSuccessfulPaymentImpl }

function TTgSuccessfulPaymentImpl.GetCurrency: string;
begin
  Result := TTgJson.GetStr(FJson, 'currency');
end;

function TTgSuccessfulPaymentImpl.GetTotalAmount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'total_amount');
end;

function TTgSuccessfulPaymentImpl.GetInvoicePayload: string;
begin
  Result := TTgJson.GetStr(FJson, 'invoice_payload');
end;

function TTgSuccessfulPaymentImpl.GetSubscriptionExpirationDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'subscription_expiration_date');
end;

function TTgSuccessfulPaymentImpl.GetHasSubscriptionExpirationDate: Boolean;
begin
  Result := TTgJson.Has(FJson, 'subscription_expiration_date');
end;

function TTgSuccessfulPaymentImpl.GetIsRecurring: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_recurring');
end;

function TTgSuccessfulPaymentImpl.GetIsFirstRecurring: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_first_recurring');
end;

function TTgSuccessfulPaymentImpl.GetShippingOptionId: string;
begin
  Result := TTgJson.GetStr(FJson, 'shipping_option_id');
end;

function TTgSuccessfulPaymentImpl.GetOrderInfo: ITgOrderInfo;
begin
  Result := TgMakeOrderInfo(TTgJson.GetValue(FJson, 'order_info'), JsonOwner);
end;

function TTgSuccessfulPaymentImpl.GetTelegramPaymentChargeId: string;
begin
  Result := TTgJson.GetStr(FJson, 'telegram_payment_charge_id');
end;

function TTgSuccessfulPaymentImpl.GetProviderPaymentChargeId: string;
begin
  Result := TTgJson.GetStr(FJson, 'provider_payment_charge_id');
end;

{ TTgRefundedPaymentImpl }

function TTgRefundedPaymentImpl.GetCurrency: string;
begin
  Result := TTgJson.GetStr(FJson, 'currency');
end;

function TTgRefundedPaymentImpl.GetTotalAmount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'total_amount');
end;

function TTgRefundedPaymentImpl.GetInvoicePayload: string;
begin
  Result := TTgJson.GetStr(FJson, 'invoice_payload');
end;

function TTgRefundedPaymentImpl.GetTelegramPaymentChargeId: string;
begin
  Result := TTgJson.GetStr(FJson, 'telegram_payment_charge_id');
end;

function TTgRefundedPaymentImpl.GetProviderPaymentChargeId: string;
begin
  Result := TTgJson.GetStr(FJson, 'provider_payment_charge_id');
end;

{ TTgShippingQueryImpl }

function TTgShippingQueryImpl.GetId: string;
begin
  Result := TTgJson.GetStr(FJson, 'id');
end;

function TTgShippingQueryImpl.GetFrom: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'from'), JsonOwner);
end;

function TTgShippingQueryImpl.GetInvoicePayload: string;
begin
  Result := TTgJson.GetStr(FJson, 'invoice_payload');
end;

function TTgShippingQueryImpl.GetShippingAddress: ITgShippingAddress;
begin
  Result := TgMakeShippingAddress(TTgJson.GetValue(FJson, 'shipping_address'), JsonOwner);
end;

{ TTgPreCheckoutQueryImpl }

function TTgPreCheckoutQueryImpl.GetId: string;
begin
  Result := TTgJson.GetStr(FJson, 'id');
end;

function TTgPreCheckoutQueryImpl.GetFrom: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'from'), JsonOwner);
end;

function TTgPreCheckoutQueryImpl.GetCurrency: string;
begin
  Result := TTgJson.GetStr(FJson, 'currency');
end;

function TTgPreCheckoutQueryImpl.GetTotalAmount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'total_amount');
end;

function TTgPreCheckoutQueryImpl.GetInvoicePayload: string;
begin
  Result := TTgJson.GetStr(FJson, 'invoice_payload');
end;

function TTgPreCheckoutQueryImpl.GetShippingOptionId: string;
begin
  Result := TTgJson.GetStr(FJson, 'shipping_option_id');
end;

function TTgPreCheckoutQueryImpl.GetOrderInfo: ITgOrderInfo;
begin
  Result := TgMakeOrderInfo(TTgJson.GetValue(FJson, 'order_info'), JsonOwner);
end;

{ TTgPaidMediaPurchasedImpl }

function TTgPaidMediaPurchasedImpl.GetFrom: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'from'), JsonOwner);
end;

function TTgPaidMediaPurchasedImpl.GetPaidMediaPayload: string;
begin
  Result := TTgJson.GetStr(FJson, 'paid_media_payload');
end;

{ TTgRevenueWithdrawalStateImpl }

function TTgRevenueWithdrawalStateImpl.GetKind: TTgRevenueWithdrawalStateKind;
begin
  Result := TTgRevenueWithdrawalStateKind.Unknown;
end;

function TTgRevenueWithdrawalStateImpl.GetKindText: string;
begin
  Result := TTgJson.GetStr(FJson, 'type');
end;

function TTgRevenueWithdrawalStateImpl.AsPending: ITgRevenueWithdrawalStatePending;
begin
  if not Supports(Self, ITgRevenueWithdrawalStatePending, Result) then
    Result := nil;
end;

function TTgRevenueWithdrawalStateImpl.AsSucceeded: ITgRevenueWithdrawalStateSucceeded;
begin
  if not Supports(Self, ITgRevenueWithdrawalStateSucceeded, Result) then
    Result := nil;
end;

function TTgRevenueWithdrawalStateImpl.AsFailed: ITgRevenueWithdrawalStateFailed;
begin
  if not Supports(Self, ITgRevenueWithdrawalStateFailed, Result) then
    Result := nil;
end;

{ TTgRevenueWithdrawalStatePendingImpl }

function TTgRevenueWithdrawalStatePendingImpl.GetKind: TTgRevenueWithdrawalStateKind;
begin
  Result := TTgRevenueWithdrawalStateKind.Pending;
end;

{ TTgRevenueWithdrawalStateSucceededImpl }

function TTgRevenueWithdrawalStateSucceededImpl.GetKind: TTgRevenueWithdrawalStateKind;
begin
  Result := TTgRevenueWithdrawalStateKind.Succeeded;
end;

function TTgRevenueWithdrawalStateSucceededImpl.GetDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'date');
end;

function TTgRevenueWithdrawalStateSucceededImpl.GetUrl: string;
begin
  Result := TTgJson.GetStr(FJson, 'url');
end;

{ TTgRevenueWithdrawalStateFailedImpl }

function TTgRevenueWithdrawalStateFailedImpl.GetKind: TTgRevenueWithdrawalStateKind;
begin
  Result := TTgRevenueWithdrawalStateKind.Failed;
end;

{ TTgAffiliateInfoImpl }

function TTgAffiliateInfoImpl.GetAffiliateUser: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'affiliate_user'), JsonOwner);
end;

function TTgAffiliateInfoImpl.GetAffiliateChat: ITgChat;
begin
  Result := TgMakeChat(TTgJson.GetValue(FJson, 'affiliate_chat'), JsonOwner);
end;

function TTgAffiliateInfoImpl.GetCommissionPerMille: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'commission_per_mille');
end;

function TTgAffiliateInfoImpl.GetAmount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'amount');
end;

function TTgAffiliateInfoImpl.GetNanostarAmount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'nanostar_amount');
end;

function TTgAffiliateInfoImpl.GetHasNanostarAmount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'nanostar_amount');
end;

{ TTgTransactionPartnerImpl }

function TTgTransactionPartnerImpl.GetKind: TTgTransactionPartnerKind;
begin
  Result := TTgTransactionPartnerKind.Unknown;
end;

function TTgTransactionPartnerImpl.GetKindText: string;
begin
  Result := TTgJson.GetStr(FJson, 'type');
end;

function TTgTransactionPartnerImpl.AsUser: ITgTransactionPartnerUser;
begin
  if not Supports(Self, ITgTransactionPartnerUser, Result) then
    Result := nil;
end;

function TTgTransactionPartnerImpl.AsChat: ITgTransactionPartnerChat;
begin
  if not Supports(Self, ITgTransactionPartnerChat, Result) then
    Result := nil;
end;

function TTgTransactionPartnerImpl.AsAffiliateProgram: ITgTransactionPartnerAffiliateProgram;
begin
  if not Supports(Self, ITgTransactionPartnerAffiliateProgram, Result) then
    Result := nil;
end;

function TTgTransactionPartnerImpl.AsFragment: ITgTransactionPartnerFragment;
begin
  if not Supports(Self, ITgTransactionPartnerFragment, Result) then
    Result := nil;
end;

function TTgTransactionPartnerImpl.AsTelegramAds: ITgTransactionPartnerTelegramAds;
begin
  if not Supports(Self, ITgTransactionPartnerTelegramAds, Result) then
    Result := nil;
end;

function TTgTransactionPartnerImpl.AsTelegramApi: ITgTransactionPartnerTelegramApi;
begin
  if not Supports(Self, ITgTransactionPartnerTelegramApi, Result) then
    Result := nil;
end;

function TTgTransactionPartnerImpl.AsOther: ITgTransactionPartnerOther;
begin
  if not Supports(Self, ITgTransactionPartnerOther, Result) then
    Result := nil;
end;

{ TTgTransactionPartnerUserImpl }

function TTgTransactionPartnerUserImpl.GetKind: TTgTransactionPartnerKind;
begin
  Result := TTgTransactionPartnerKind.User;
end;

function TTgTransactionPartnerUserImpl.GetTransactionType: string;
begin
  Result := TTgJson.GetStr(FJson, 'transaction_type');
end;

function TTgTransactionPartnerUserImpl.GetUser: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'user'), JsonOwner);
end;

function TTgTransactionPartnerUserImpl.GetAffiliate: ITgAffiliateInfo;
begin
  Result := TgMakeAffiliateInfo(TTgJson.GetValue(FJson, 'affiliate'), JsonOwner);
end;

function TTgTransactionPartnerUserImpl.GetInvoicePayload: string;
begin
  Result := TTgJson.GetStr(FJson, 'invoice_payload');
end;

function TTgTransactionPartnerUserImpl.GetSubscriptionPeriod: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'subscription_period');
end;

function TTgTransactionPartnerUserImpl.GetHasSubscriptionPeriod: Boolean;
begin
  Result := TTgJson.Has(FJson, 'subscription_period');
end;

function TTgTransactionPartnerUserImpl.GetPaidMedia: TArray<ITgPaidMedia>;
begin
  Result := TTgDto.Objects<ITgPaidMedia>(TTgJson.GetArr(FJson, 'paid_media'), JsonOwner, TgMakePaidMedia);
end;

function TTgTransactionPartnerUserImpl.GetPaidMediaPayload: string;
begin
  Result := TTgJson.GetStr(FJson, 'paid_media_payload');
end;

function TTgTransactionPartnerUserImpl.GetGift: ITgGift;
begin
  Result := TgMakeGift(TTgJson.GetValue(FJson, 'gift'), JsonOwner);
end;

function TTgTransactionPartnerUserImpl.GetPremiumSubscriptionDuration: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'premium_subscription_duration');
end;

function TTgTransactionPartnerUserImpl.GetHasPremiumSubscriptionDuration: Boolean;
begin
  Result := TTgJson.Has(FJson, 'premium_subscription_duration');
end;

{ TTgTransactionPartnerChatImpl }

function TTgTransactionPartnerChatImpl.GetKind: TTgTransactionPartnerKind;
begin
  Result := TTgTransactionPartnerKind.Chat;
end;

function TTgTransactionPartnerChatImpl.GetChat: ITgChat;
begin
  Result := TgMakeChat(TTgJson.GetValue(FJson, 'chat'), JsonOwner);
end;

function TTgTransactionPartnerChatImpl.GetGift: ITgGift;
begin
  Result := TgMakeGift(TTgJson.GetValue(FJson, 'gift'), JsonOwner);
end;

{ TTgTransactionPartnerAffiliateProgramImpl }

function TTgTransactionPartnerAffiliateProgramImpl.GetKind: TTgTransactionPartnerKind;
begin
  Result := TTgTransactionPartnerKind.AffiliateProgram;
end;

function TTgTransactionPartnerAffiliateProgramImpl.GetSponsorUser: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'sponsor_user'), JsonOwner);
end;

function TTgTransactionPartnerAffiliateProgramImpl.GetCommissionPerMille: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'commission_per_mille');
end;

{ TTgTransactionPartnerFragmentImpl }

function TTgTransactionPartnerFragmentImpl.GetKind: TTgTransactionPartnerKind;
begin
  Result := TTgTransactionPartnerKind.Fragment;
end;

function TTgTransactionPartnerFragmentImpl.GetWithdrawalState: ITgRevenueWithdrawalState;
begin
  Result := TgMakeRevenueWithdrawalState(TTgJson.GetValue(FJson, 'withdrawal_state'), JsonOwner);
end;

{ TTgTransactionPartnerTelegramAdsImpl }

function TTgTransactionPartnerTelegramAdsImpl.GetKind: TTgTransactionPartnerKind;
begin
  Result := TTgTransactionPartnerKind.TelegramAds;
end;

{ TTgTransactionPartnerTelegramApiImpl }

function TTgTransactionPartnerTelegramApiImpl.GetKind: TTgTransactionPartnerKind;
begin
  Result := TTgTransactionPartnerKind.TelegramApi;
end;

function TTgTransactionPartnerTelegramApiImpl.GetRequestCount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'request_count');
end;

{ TTgTransactionPartnerOtherImpl }

function TTgTransactionPartnerOtherImpl.GetKind: TTgTransactionPartnerKind;
begin
  Result := TTgTransactionPartnerKind.Other;
end;

{ TTgStarTransactionImpl }

function TTgStarTransactionImpl.GetId: string;
begin
  Result := TTgJson.GetStr(FJson, 'id');
end;

function TTgStarTransactionImpl.GetAmount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'amount');
end;

function TTgStarTransactionImpl.GetNanostarAmount: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'nanostar_amount');
end;

function TTgStarTransactionImpl.GetHasNanostarAmount: Boolean;
begin
  Result := TTgJson.Has(FJson, 'nanostar_amount');
end;

function TTgStarTransactionImpl.GetDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'date');
end;

function TTgStarTransactionImpl.GetSource: ITgTransactionPartner;
begin
  Result := TgMakeTransactionPartner(TTgJson.GetValue(FJson, 'source'), JsonOwner);
end;

function TTgStarTransactionImpl.GetReceiver: ITgTransactionPartner;
begin
  Result := TgMakeTransactionPartner(TTgJson.GetValue(FJson, 'receiver'), JsonOwner);
end;

{ TTgStarTransactionsImpl }

function TTgStarTransactionsImpl.GetTransactions: TArray<ITgStarTransaction>;
begin
  Result := TTgDto.Objects<ITgStarTransaction>(TTgJson.GetArr(FJson, 'transactions'), JsonOwner, TgMakeStarTransaction);
end;

{ TTgPassportDataImpl }

function TTgPassportDataImpl.GetData: TArray<ITgEncryptedPassportElement>;
begin
  Result := TTgDto.Objects<ITgEncryptedPassportElement>(TTgJson.GetArr(FJson, 'data'), JsonOwner, TgMakeEncryptedPassportElement);
end;

function TTgPassportDataImpl.GetCredentials: ITgEncryptedCredentials;
begin
  Result := TgMakeEncryptedCredentials(TTgJson.GetValue(FJson, 'credentials'), JsonOwner);
end;

{ TTgPassportFileImpl }

function TTgPassportFileImpl.GetFileId: string;
begin
  Result := TTgJson.GetStr(FJson, 'file_id');
end;

function TTgPassportFileImpl.GetFileUniqueId: string;
begin
  Result := TTgJson.GetStr(FJson, 'file_unique_id');
end;

function TTgPassportFileImpl.GetFileSize: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'file_size');
end;

function TTgPassportFileImpl.GetFileDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'file_date');
end;

{ TTgEncryptedPassportElementImpl }

function TTgEncryptedPassportElementImpl.GetEncryptedPassportElementType: string;
begin
  Result := TTgJson.GetStr(FJson, 'type');
end;

function TTgEncryptedPassportElementImpl.GetData: string;
begin
  Result := TTgJson.GetStr(FJson, 'data');
end;

function TTgEncryptedPassportElementImpl.GetPhoneNumber: string;
begin
  Result := TTgJson.GetStr(FJson, 'phone_number');
end;

function TTgEncryptedPassportElementImpl.GetEmail: string;
begin
  Result := TTgJson.GetStr(FJson, 'email');
end;

function TTgEncryptedPassportElementImpl.GetFiles: TArray<ITgPassportFile>;
begin
  Result := TTgDto.Objects<ITgPassportFile>(TTgJson.GetArr(FJson, 'files'), JsonOwner, TgMakePassportFile);
end;

function TTgEncryptedPassportElementImpl.GetFrontSide: ITgPassportFile;
begin
  Result := TgMakePassportFile(TTgJson.GetValue(FJson, 'front_side'), JsonOwner);
end;

function TTgEncryptedPassportElementImpl.GetReverseSide: ITgPassportFile;
begin
  Result := TgMakePassportFile(TTgJson.GetValue(FJson, 'reverse_side'), JsonOwner);
end;

function TTgEncryptedPassportElementImpl.GetSelfie: ITgPassportFile;
begin
  Result := TgMakePassportFile(TTgJson.GetValue(FJson, 'selfie'), JsonOwner);
end;

function TTgEncryptedPassportElementImpl.GetTranslation: TArray<ITgPassportFile>;
begin
  Result := TTgDto.Objects<ITgPassportFile>(TTgJson.GetArr(FJson, 'translation'), JsonOwner, TgMakePassportFile);
end;

function TTgEncryptedPassportElementImpl.GetHash: string;
begin
  Result := TTgJson.GetStr(FJson, 'hash');
end;

{ TTgEncryptedCredentialsImpl }

function TTgEncryptedCredentialsImpl.GetData: string;
begin
  Result := TTgJson.GetStr(FJson, 'data');
end;

function TTgEncryptedCredentialsImpl.GetHash: string;
begin
  Result := TTgJson.GetStr(FJson, 'hash');
end;

function TTgEncryptedCredentialsImpl.GetSecret: string;
begin
  Result := TTgJson.GetStr(FJson, 'secret');
end;

{ TTgPassportElementErrorDataFieldImpl }

function TTgPassportElementErrorDataFieldImpl.WithPassportElementErrorDataFieldType(const AValue: string): ITgPassportElementErrorDataField;
begin
  SetStr('type', AValue);
  Result := Self;
end;

function TTgPassportElementErrorDataFieldImpl.WithFieldName(const AValue: string): ITgPassportElementErrorDataField;
begin
  SetStr('field_name', AValue);
  Result := Self;
end;

function TTgPassportElementErrorDataFieldImpl.WithDataHash(const AValue: string): ITgPassportElementErrorDataField;
begin
  SetStr('data_hash', AValue);
  Result := Self;
end;

function TTgPassportElementErrorDataFieldImpl.WithMessage(const AValue: string): ITgPassportElementErrorDataField;
begin
  SetStr('message', AValue);
  Result := Self;
end;

{ TTgPassportElementErrorFrontSideImpl }

function TTgPassportElementErrorFrontSideImpl.WithPassportElementErrorFrontSideType(const AValue: string): ITgPassportElementErrorFrontSide;
begin
  SetStr('type', AValue);
  Result := Self;
end;

function TTgPassportElementErrorFrontSideImpl.WithFileHash(const AValue: string): ITgPassportElementErrorFrontSide;
begin
  SetStr('file_hash', AValue);
  Result := Self;
end;

function TTgPassportElementErrorFrontSideImpl.WithMessage(const AValue: string): ITgPassportElementErrorFrontSide;
begin
  SetStr('message', AValue);
  Result := Self;
end;

{ TTgPassportElementErrorReverseSideImpl }

function TTgPassportElementErrorReverseSideImpl.WithPassportElementErrorReverseSideType(const AValue: string): ITgPassportElementErrorReverseSide;
begin
  SetStr('type', AValue);
  Result := Self;
end;

function TTgPassportElementErrorReverseSideImpl.WithFileHash(const AValue: string): ITgPassportElementErrorReverseSide;
begin
  SetStr('file_hash', AValue);
  Result := Self;
end;

function TTgPassportElementErrorReverseSideImpl.WithMessage(const AValue: string): ITgPassportElementErrorReverseSide;
begin
  SetStr('message', AValue);
  Result := Self;
end;

{ TTgPassportElementErrorSelfieImpl }

function TTgPassportElementErrorSelfieImpl.WithPassportElementErrorSelfieType(const AValue: string): ITgPassportElementErrorSelfie;
begin
  SetStr('type', AValue);
  Result := Self;
end;

function TTgPassportElementErrorSelfieImpl.WithFileHash(const AValue: string): ITgPassportElementErrorSelfie;
begin
  SetStr('file_hash', AValue);
  Result := Self;
end;

function TTgPassportElementErrorSelfieImpl.WithMessage(const AValue: string): ITgPassportElementErrorSelfie;
begin
  SetStr('message', AValue);
  Result := Self;
end;

{ TTgPassportElementErrorFileImpl }

function TTgPassportElementErrorFileImpl.WithPassportElementErrorFileType(const AValue: string): ITgPassportElementErrorFile;
begin
  SetStr('type', AValue);
  Result := Self;
end;

function TTgPassportElementErrorFileImpl.WithFileHash(const AValue: string): ITgPassportElementErrorFile;
begin
  SetStr('file_hash', AValue);
  Result := Self;
end;

function TTgPassportElementErrorFileImpl.WithMessage(const AValue: string): ITgPassportElementErrorFile;
begin
  SetStr('message', AValue);
  Result := Self;
end;

{ TTgPassportElementErrorFilesImpl }

function TTgPassportElementErrorFilesImpl.WithPassportElementErrorFilesType(const AValue: string): ITgPassportElementErrorFiles;
begin
  SetStr('type', AValue);
  Result := Self;
end;

function TTgPassportElementErrorFilesImpl.WithFileHashes(const AValue: TArray<string>): ITgPassportElementErrorFiles;
begin
  SetStrings('file_hashes', AValue);
  Result := Self;
end;

function TTgPassportElementErrorFilesImpl.WithMessage(const AValue: string): ITgPassportElementErrorFiles;
begin
  SetStr('message', AValue);
  Result := Self;
end;

{ TTgPassportElementErrorTranslationFileImpl }

function TTgPassportElementErrorTranslationFileImpl.WithPassportElementErrorTranslationFileType(const AValue: string): ITgPassportElementErrorTranslationFile;
begin
  SetStr('type', AValue);
  Result := Self;
end;

function TTgPassportElementErrorTranslationFileImpl.WithFileHash(const AValue: string): ITgPassportElementErrorTranslationFile;
begin
  SetStr('file_hash', AValue);
  Result := Self;
end;

function TTgPassportElementErrorTranslationFileImpl.WithMessage(const AValue: string): ITgPassportElementErrorTranslationFile;
begin
  SetStr('message', AValue);
  Result := Self;
end;

{ TTgPassportElementErrorTranslationFilesImpl }

function TTgPassportElementErrorTranslationFilesImpl.WithPassportElementErrorTranslationFilesType(const AValue: string): ITgPassportElementErrorTranslationFiles;
begin
  SetStr('type', AValue);
  Result := Self;
end;

function TTgPassportElementErrorTranslationFilesImpl.WithFileHashes(const AValue: TArray<string>): ITgPassportElementErrorTranslationFiles;
begin
  SetStrings('file_hashes', AValue);
  Result := Self;
end;

function TTgPassportElementErrorTranslationFilesImpl.WithMessage(const AValue: string): ITgPassportElementErrorTranslationFiles;
begin
  SetStr('message', AValue);
  Result := Self;
end;

{ TTgPassportElementErrorUnspecifiedImpl }

function TTgPassportElementErrorUnspecifiedImpl.WithPassportElementErrorUnspecifiedType(const AValue: string): ITgPassportElementErrorUnspecified;
begin
  SetStr('type', AValue);
  Result := Self;
end;

function TTgPassportElementErrorUnspecifiedImpl.WithElementHash(const AValue: string): ITgPassportElementErrorUnspecified;
begin
  SetStr('element_hash', AValue);
  Result := Self;
end;

function TTgPassportElementErrorUnspecifiedImpl.WithMessage(const AValue: string): ITgPassportElementErrorUnspecified;
begin
  SetStr('message', AValue);
  Result := Self;
end;

{ TTgGameImpl }

function TTgGameImpl.GetTitle: string;
begin
  Result := TTgJson.GetStr(FJson, 'title');
end;

function TTgGameImpl.GetDescription: string;
begin
  Result := TTgJson.GetStr(FJson, 'description');
end;

function TTgGameImpl.GetPhoto: TArray<ITgPhotoSize>;
begin
  Result := TTgDto.Objects<ITgPhotoSize>(TTgJson.GetArr(FJson, 'photo'), JsonOwner, TgMakePhotoSize);
end;

function TTgGameImpl.GetText: string;
begin
  Result := TTgJson.GetStr(FJson, 'text');
end;

function TTgGameImpl.GetTextEntities: TArray<ITgMessageEntity>;
begin
  Result := TTgDto.Objects<ITgMessageEntity>(TTgJson.GetArr(FJson, 'text_entities'), JsonOwner, TgMakeMessageEntity);
end;

function TTgGameImpl.GetAnimation: ITgAnimation;
begin
  Result := TgMakeAnimation(TTgJson.GetValue(FJson, 'animation'), JsonOwner);
end;

{ TTgCallbackGameImpl }

{ TTgGameHighScoreImpl }

function TTgGameHighScoreImpl.GetPosition: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'position');
end;

function TTgGameHighScoreImpl.GetUser: ITgUser;
begin
  Result := TgMakeUser(TTgJson.GetValue(FJson, 'user'), JsonOwner);
end;

function TTgGameHighScoreImpl.GetScore: Integer;
begin
  Result := TTgJson.GetInt(FJson, 'score');
end;

{ TTgUpdate }

class function TTgUpdate.FromJson(const AJsonText: string): ITgUpdate;
begin
  Result := TTgDto.Parse<ITgUpdate>(AJsonText, TgMakeUpdate);
end;

{ TTgWebhookInfo }

class function TTgWebhookInfo.FromJson(const AJsonText: string): ITgWebhookInfo;
begin
  Result := TTgDto.Parse<ITgWebhookInfo>(AJsonText, TgMakeWebhookInfo);
end;

{ TTgUser }

class function TTgUser.Create(AId: Int64; AIsBot: Boolean; const AFirstName: string): ITgUser;
var
  LObj: TTgUserImpl;
begin
  LObj := TTgUserImpl.CreateNew;
  Result := LObj;
  LObj.SetInt64('id', AId);
  LObj.SetBool('is_bot', AIsBot);
  LObj.SetStr('first_name', AFirstName);
end;

class function TTgUser.FromJson(const AJsonText: string): ITgUser;
begin
  Result := TTgDto.Parse<ITgUser>(AJsonText, TgMakeUser);
end;

{ TTgChat }

class function TTgChat.FromJson(const AJsonText: string): ITgChat;
begin
  Result := TTgDto.Parse<ITgChat>(AJsonText, TgMakeChat);
end;

{ TTgChatFullInfo }

class function TTgChatFullInfo.FromJson(const AJsonText: string): ITgChatFullInfo;
begin
  Result := TTgDto.Parse<ITgChatFullInfo>(AJsonText, TgMakeChatFullInfo);
end;

{ TTgMaybeInaccessibleMessage }

class function TTgMaybeInaccessibleMessage.FromJson(const AJsonText: string): ITgMaybeInaccessibleMessage;
begin
  Result := TTgDto.Parse<ITgMaybeInaccessibleMessage>(AJsonText, TgMakeMaybeInaccessibleMessage);
end;

{ TTgMessage }

class function TTgMessage.FromJson(const AJsonText: string): ITgMessage;
begin
  Result := TTgDto.Parse<ITgMessage>(AJsonText, TgMakeMessage);
end;

{ TTgMessageId }

class function TTgMessageId.FromJson(const AJsonText: string): ITgMessageId;
begin
  Result := TTgDto.Parse<ITgMessageId>(AJsonText, TgMakeMessageId);
end;

{ TTgInaccessibleMessage }

class function TTgInaccessibleMessage.FromJson(const AJsonText: string): ITgInaccessibleMessage;
begin
  Result := TTgDto.Parse<ITgInaccessibleMessage>(AJsonText, TgMakeInaccessibleMessage);
end;

{ TTgMessageEntity }

class function TTgMessageEntity.Create(const AMessageEntityType: string; AOffset: Integer;
  ALength: Integer): ITgMessageEntity;
var
  LObj: TTgMessageEntityImpl;
begin
  LObj := TTgMessageEntityImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', AMessageEntityType);
  LObj.SetInt('offset', AOffset);
  LObj.SetInt('length', ALength);
end;

class function TTgMessageEntity.FromJson(const AJsonText: string): ITgMessageEntity;
begin
  Result := TTgDto.Parse<ITgMessageEntity>(AJsonText, TgMakeMessageEntity);
end;

{ TTgTextQuote }

class function TTgTextQuote.FromJson(const AJsonText: string): ITgTextQuote;
begin
  Result := TTgDto.Parse<ITgTextQuote>(AJsonText, TgMakeTextQuote);
end;

{ TTgExternalReplyInfo }

class function TTgExternalReplyInfo.FromJson(const AJsonText: string): ITgExternalReplyInfo;
begin
  Result := TTgDto.Parse<ITgExternalReplyInfo>(AJsonText, TgMakeExternalReplyInfo);
end;

{ TTgReplyParameters }

class function TTgReplyParameters.Create: ITgReplyParameters;
begin
  Result := TTgReplyParametersImpl.CreateNew;
end;

{ TTgEphemeralMessageParameters }

class function TTgEphemeralMessageParameters.Create(AReceiverUserId: Int64): ITgEphemeralMessageParameters;
var
  LObj: TTgEphemeralMessageParametersImpl;
begin
  LObj := TTgEphemeralMessageParametersImpl.CreateNew;
  Result := LObj;
  LObj.SetInt64('receiver_user_id', AReceiverUserId);
end;

{ TTgMessageOrigin }

class function TTgMessageOrigin.FromJson(const AJsonText: string): ITgMessageOrigin;
begin
  Result := TTgDto.Parse<ITgMessageOrigin>(AJsonText, TgMakeMessageOrigin);
end;

{ TTgMessageOriginUser }

class function TTgMessageOriginUser.FromJson(const AJsonText: string): ITgMessageOriginUser;
begin
  Result := TTgDto.Parse<ITgMessageOriginUser>(AJsonText, TgMakeMessageOriginUser);
end;

{ TTgMessageOriginHiddenUser }

class function TTgMessageOriginHiddenUser.FromJson(const AJsonText: string): ITgMessageOriginHiddenUser;
begin
  Result := TTgDto.Parse<ITgMessageOriginHiddenUser>(AJsonText, TgMakeMessageOriginHiddenUser);
end;

{ TTgMessageOriginChat }

class function TTgMessageOriginChat.FromJson(const AJsonText: string): ITgMessageOriginChat;
begin
  Result := TTgDto.Parse<ITgMessageOriginChat>(AJsonText, TgMakeMessageOriginChat);
end;

{ TTgMessageOriginChannel }

class function TTgMessageOriginChannel.FromJson(const AJsonText: string): ITgMessageOriginChannel;
begin
  Result := TTgDto.Parse<ITgMessageOriginChannel>(AJsonText, TgMakeMessageOriginChannel);
end;

{ TTgPhotoSize }

class function TTgPhotoSize.FromJson(const AJsonText: string): ITgPhotoSize;
begin
  Result := TTgDto.Parse<ITgPhotoSize>(AJsonText, TgMakePhotoSize);
end;

{ TTgAnimation }

class function TTgAnimation.FromJson(const AJsonText: string): ITgAnimation;
begin
  Result := TTgDto.Parse<ITgAnimation>(AJsonText, TgMakeAnimation);
end;

{ TTgAudio }

class function TTgAudio.FromJson(const AJsonText: string): ITgAudio;
begin
  Result := TTgDto.Parse<ITgAudio>(AJsonText, TgMakeAudio);
end;

{ TTgDocument }

class function TTgDocument.FromJson(const AJsonText: string): ITgDocument;
begin
  Result := TTgDto.Parse<ITgDocument>(AJsonText, TgMakeDocument);
end;

{ TTgLivePhoto }

class function TTgLivePhoto.FromJson(const AJsonText: string): ITgLivePhoto;
begin
  Result := TTgDto.Parse<ITgLivePhoto>(AJsonText, TgMakeLivePhoto);
end;

{ TTgStory }

class function TTgStory.FromJson(const AJsonText: string): ITgStory;
begin
  Result := TTgDto.Parse<ITgStory>(AJsonText, TgMakeStory);
end;

{ TTgVideoQuality }

class function TTgVideoQuality.FromJson(const AJsonText: string): ITgVideoQuality;
begin
  Result := TTgDto.Parse<ITgVideoQuality>(AJsonText, TgMakeVideoQuality);
end;

{ TTgVideo }

class function TTgVideo.FromJson(const AJsonText: string): ITgVideo;
begin
  Result := TTgDto.Parse<ITgVideo>(AJsonText, TgMakeVideo);
end;

{ TTgVideoNote }

class function TTgVideoNote.FromJson(const AJsonText: string): ITgVideoNote;
begin
  Result := TTgDto.Parse<ITgVideoNote>(AJsonText, TgMakeVideoNote);
end;

{ TTgVoice }

class function TTgVoice.FromJson(const AJsonText: string): ITgVoice;
begin
  Result := TTgDto.Parse<ITgVoice>(AJsonText, TgMakeVoice);
end;

{ TTgPaidMediaInfo }

class function TTgPaidMediaInfo.FromJson(const AJsonText: string): ITgPaidMediaInfo;
begin
  Result := TTgDto.Parse<ITgPaidMediaInfo>(AJsonText, TgMakePaidMediaInfo);
end;

{ TTgPaidMedia }

class function TTgPaidMedia.FromJson(const AJsonText: string): ITgPaidMedia;
begin
  Result := TTgDto.Parse<ITgPaidMedia>(AJsonText, TgMakePaidMedia);
end;

{ TTgPaidMediaLivePhoto }

class function TTgPaidMediaLivePhoto.FromJson(const AJsonText: string): ITgPaidMediaLivePhoto;
begin
  Result := TTgDto.Parse<ITgPaidMediaLivePhoto>(AJsonText, TgMakePaidMediaLivePhoto);
end;

{ TTgPaidMediaPhoto }

class function TTgPaidMediaPhoto.FromJson(const AJsonText: string): ITgPaidMediaPhoto;
begin
  Result := TTgDto.Parse<ITgPaidMediaPhoto>(AJsonText, TgMakePaidMediaPhoto);
end;

{ TTgPaidMediaPreview }

class function TTgPaidMediaPreview.FromJson(const AJsonText: string): ITgPaidMediaPreview;
begin
  Result := TTgDto.Parse<ITgPaidMediaPreview>(AJsonText, TgMakePaidMediaPreview);
end;

{ TTgPaidMediaVideo }

class function TTgPaidMediaVideo.FromJson(const AJsonText: string): ITgPaidMediaVideo;
begin
  Result := TTgDto.Parse<ITgPaidMediaVideo>(AJsonText, TgMakePaidMediaVideo);
end;

{ TTgContact }

class function TTgContact.FromJson(const AJsonText: string): ITgContact;
begin
  Result := TTgDto.Parse<ITgContact>(AJsonText, TgMakeContact);
end;

{ TTgDice }

class function TTgDice.FromJson(const AJsonText: string): ITgDice;
begin
  Result := TTgDto.Parse<ITgDice>(AJsonText, TgMakeDice);
end;

{ TTgLink }

class function TTgLink.FromJson(const AJsonText: string): ITgLink;
begin
  Result := TTgDto.Parse<ITgLink>(AJsonText, TgMakeLink);
end;

{ TTgPollMedia }

class function TTgPollMedia.FromJson(const AJsonText: string): ITgPollMedia;
begin
  Result := TTgDto.Parse<ITgPollMedia>(AJsonText, TgMakePollMedia);
end;

{ TTgPollOption }

class function TTgPollOption.FromJson(const AJsonText: string): ITgPollOption;
begin
  Result := TTgDto.Parse<ITgPollOption>(AJsonText, TgMakePollOption);
end;

{ TTgInputPollOption }

class function TTgInputPollOption.Create(const AText: string): ITgInputPollOption;
var
  LObj: TTgInputPollOptionImpl;
begin
  LObj := TTgInputPollOptionImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('text', AText);
end;

{ TTgPollAnswer }

class function TTgPollAnswer.FromJson(const AJsonText: string): ITgPollAnswer;
begin
  Result := TTgDto.Parse<ITgPollAnswer>(AJsonText, TgMakePollAnswer);
end;

{ TTgPoll }

class function TTgPoll.FromJson(const AJsonText: string): ITgPoll;
begin
  Result := TTgDto.Parse<ITgPoll>(AJsonText, TgMakePoll);
end;

{ TTgChecklistTask }

class function TTgChecklistTask.FromJson(const AJsonText: string): ITgChecklistTask;
begin
  Result := TTgDto.Parse<ITgChecklistTask>(AJsonText, TgMakeChecklistTask);
end;

{ TTgChecklist }

class function TTgChecklist.FromJson(const AJsonText: string): ITgChecklist;
begin
  Result := TTgDto.Parse<ITgChecklist>(AJsonText, TgMakeChecklist);
end;

{ TTgInputChecklistTask }

class function TTgInputChecklistTask.Create(AId: Int64; const AText: string): ITgInputChecklistTask;
var
  LObj: TTgInputChecklistTaskImpl;
begin
  LObj := TTgInputChecklistTaskImpl.CreateNew;
  Result := LObj;
  LObj.SetInt64('id', AId);
  LObj.SetStr('text', AText);
end;

{ TTgInputChecklist }

class function TTgInputChecklist.Create(const ATitle: string;
  const ATasks: array of ITgInputChecklistTask): ITgInputChecklist;
var
  LObj: TTgInputChecklistImpl;
begin
  LObj := TTgInputChecklistImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('title', ATitle);
  LObj.SetObjects('tasks', TTgDto.ToIntf<ITgInputChecklistTask>(ATasks));
end;

{ TTgLocation }

class function TTgLocation.Create(ALatitude: Double; ALongitude: Double): ITgLocation;
var
  LObj: TTgLocationImpl;
begin
  LObj := TTgLocationImpl.CreateNew;
  Result := LObj;
  LObj.SetDouble('latitude', ALatitude);
  LObj.SetDouble('longitude', ALongitude);
end;

class function TTgLocation.FromJson(const AJsonText: string): ITgLocation;
begin
  Result := TTgDto.Parse<ITgLocation>(AJsonText, TgMakeLocation);
end;

{ TTgVenue }

class function TTgVenue.FromJson(const AJsonText: string): ITgVenue;
begin
  Result := TTgDto.Parse<ITgVenue>(AJsonText, TgMakeVenue);
end;

{ TTgWebAppData }

class function TTgWebAppData.FromJson(const AJsonText: string): ITgWebAppData;
begin
  Result := TTgDto.Parse<ITgWebAppData>(AJsonText, TgMakeWebAppData);
end;

{ TTgProximityAlertTriggered }

class function TTgProximityAlertTriggered.FromJson(const AJsonText: string): ITgProximityAlertTriggered;
begin
  Result := TTgDto.Parse<ITgProximityAlertTriggered>(AJsonText, TgMakeProximityAlertTriggered);
end;

{ TTgMessageAutoDeleteTimerChanged }

class function TTgMessageAutoDeleteTimerChanged.FromJson(const AJsonText: string): ITgMessageAutoDeleteTimerChanged;
begin
  Result := TTgDto.Parse<ITgMessageAutoDeleteTimerChanged>(AJsonText, TgMakeMessageAutoDeleteTimerChanged);
end;

{ TTgManagedBotCreated }

class function TTgManagedBotCreated.FromJson(const AJsonText: string): ITgManagedBotCreated;
begin
  Result := TTgDto.Parse<ITgManagedBotCreated>(AJsonText, TgMakeManagedBotCreated);
end;

{ TTgManagedBotUpdated }

class function TTgManagedBotUpdated.FromJson(const AJsonText: string): ITgManagedBotUpdated;
begin
  Result := TTgDto.Parse<ITgManagedBotUpdated>(AJsonText, TgMakeManagedBotUpdated);
end;

{ TTgBotSubscriptionUpdated }

class function TTgBotSubscriptionUpdated.FromJson(const AJsonText: string): ITgBotSubscriptionUpdated;
begin
  Result := TTgDto.Parse<ITgBotSubscriptionUpdated>(AJsonText, TgMakeBotSubscriptionUpdated);
end;

{ TTgMessageGenerationStopped }

class function TTgMessageGenerationStopped.FromJson(const AJsonText: string): ITgMessageGenerationStopped;
begin
  Result := TTgDto.Parse<ITgMessageGenerationStopped>(AJsonText, TgMakeMessageGenerationStopped);
end;

{ TTgPollOptionAdded }

class function TTgPollOptionAdded.FromJson(const AJsonText: string): ITgPollOptionAdded;
begin
  Result := TTgDto.Parse<ITgPollOptionAdded>(AJsonText, TgMakePollOptionAdded);
end;

{ TTgPollOptionDeleted }

class function TTgPollOptionDeleted.FromJson(const AJsonText: string): ITgPollOptionDeleted;
begin
  Result := TTgDto.Parse<ITgPollOptionDeleted>(AJsonText, TgMakePollOptionDeleted);
end;

{ TTgChatBoostAdded }

class function TTgChatBoostAdded.FromJson(const AJsonText: string): ITgChatBoostAdded;
begin
  Result := TTgDto.Parse<ITgChatBoostAdded>(AJsonText, TgMakeChatBoostAdded);
end;

{ TTgBackgroundFill }

class function TTgBackgroundFill.FromJson(const AJsonText: string): ITgBackgroundFill;
begin
  Result := TTgDto.Parse<ITgBackgroundFill>(AJsonText, TgMakeBackgroundFill);
end;

{ TTgBackgroundFillSolid }

class function TTgBackgroundFillSolid.FromJson(const AJsonText: string): ITgBackgroundFillSolid;
begin
  Result := TTgDto.Parse<ITgBackgroundFillSolid>(AJsonText, TgMakeBackgroundFillSolid);
end;

{ TTgBackgroundFillGradient }

class function TTgBackgroundFillGradient.FromJson(const AJsonText: string): ITgBackgroundFillGradient;
begin
  Result := TTgDto.Parse<ITgBackgroundFillGradient>(AJsonText, TgMakeBackgroundFillGradient);
end;

{ TTgBackgroundFillFreeformGradient }

class function TTgBackgroundFillFreeformGradient.FromJson(const AJsonText: string): ITgBackgroundFillFreeformGradient;
begin
  Result := TTgDto.Parse<ITgBackgroundFillFreeformGradient>(AJsonText, TgMakeBackgroundFillFreeformGradient);
end;

{ TTgBackgroundType }

class function TTgBackgroundType.FromJson(const AJsonText: string): ITgBackgroundType;
begin
  Result := TTgDto.Parse<ITgBackgroundType>(AJsonText, TgMakeBackgroundType);
end;

{ TTgBackgroundTypeFill }

class function TTgBackgroundTypeFill.FromJson(const AJsonText: string): ITgBackgroundTypeFill;
begin
  Result := TTgDto.Parse<ITgBackgroundTypeFill>(AJsonText, TgMakeBackgroundTypeFill);
end;

{ TTgBackgroundTypeWallpaper }

class function TTgBackgroundTypeWallpaper.FromJson(const AJsonText: string): ITgBackgroundTypeWallpaper;
begin
  Result := TTgDto.Parse<ITgBackgroundTypeWallpaper>(AJsonText, TgMakeBackgroundTypeWallpaper);
end;

{ TTgBackgroundTypePattern }

class function TTgBackgroundTypePattern.FromJson(const AJsonText: string): ITgBackgroundTypePattern;
begin
  Result := TTgDto.Parse<ITgBackgroundTypePattern>(AJsonText, TgMakeBackgroundTypePattern);
end;

{ TTgBackgroundTypeChatTheme }

class function TTgBackgroundTypeChatTheme.FromJson(const AJsonText: string): ITgBackgroundTypeChatTheme;
begin
  Result := TTgDto.Parse<ITgBackgroundTypeChatTheme>(AJsonText, TgMakeBackgroundTypeChatTheme);
end;

{ TTgChatBackground }

class function TTgChatBackground.FromJson(const AJsonText: string): ITgChatBackground;
begin
  Result := TTgDto.Parse<ITgChatBackground>(AJsonText, TgMakeChatBackground);
end;

{ TTgChecklistTasksDone }

class function TTgChecklistTasksDone.FromJson(const AJsonText: string): ITgChecklistTasksDone;
begin
  Result := TTgDto.Parse<ITgChecklistTasksDone>(AJsonText, TgMakeChecklistTasksDone);
end;

{ TTgChecklistTasksAdded }

class function TTgChecklistTasksAdded.FromJson(const AJsonText: string): ITgChecklistTasksAdded;
begin
  Result := TTgDto.Parse<ITgChecklistTasksAdded>(AJsonText, TgMakeChecklistTasksAdded);
end;

{ TTgCommunityChatAdded }

class function TTgCommunityChatAdded.FromJson(const AJsonText: string): ITgCommunityChatAdded;
begin
  Result := TTgDto.Parse<ITgCommunityChatAdded>(AJsonText, TgMakeCommunityChatAdded);
end;

{ TTgCommunityChatJoined }

class function TTgCommunityChatJoined.FromJson(const AJsonText: string): ITgCommunityChatJoined;
begin
  Result := TTgDto.Parse<ITgCommunityChatJoined>(AJsonText, TgMakeCommunityChatJoined);
end;

{ TTgCommunityChatRemoved }

class function TTgCommunityChatRemoved.FromJson(const AJsonText: string): ITgCommunityChatRemoved;
begin
  Result := TTgDto.Parse<ITgCommunityChatRemoved>(AJsonText, TgMakeCommunityChatRemoved);
end;

{ TTgForumTopicCreated }

class function TTgForumTopicCreated.FromJson(const AJsonText: string): ITgForumTopicCreated;
begin
  Result := TTgDto.Parse<ITgForumTopicCreated>(AJsonText, TgMakeForumTopicCreated);
end;

{ TTgForumTopicClosed }

class function TTgForumTopicClosed.FromJson(const AJsonText: string): ITgForumTopicClosed;
begin
  Result := TTgDto.Parse<ITgForumTopicClosed>(AJsonText, TgMakeForumTopicClosed);
end;

{ TTgForumTopicEdited }

class function TTgForumTopicEdited.FromJson(const AJsonText: string): ITgForumTopicEdited;
begin
  Result := TTgDto.Parse<ITgForumTopicEdited>(AJsonText, TgMakeForumTopicEdited);
end;

{ TTgForumTopicReopened }

class function TTgForumTopicReopened.FromJson(const AJsonText: string): ITgForumTopicReopened;
begin
  Result := TTgDto.Parse<ITgForumTopicReopened>(AJsonText, TgMakeForumTopicReopened);
end;

{ TTgGeneralForumTopicHidden }

class function TTgGeneralForumTopicHidden.FromJson(const AJsonText: string): ITgGeneralForumTopicHidden;
begin
  Result := TTgDto.Parse<ITgGeneralForumTopicHidden>(AJsonText, TgMakeGeneralForumTopicHidden);
end;

{ TTgGeneralForumTopicUnhidden }

class function TTgGeneralForumTopicUnhidden.FromJson(const AJsonText: string): ITgGeneralForumTopicUnhidden;
begin
  Result := TTgDto.Parse<ITgGeneralForumTopicUnhidden>(AJsonText, TgMakeGeneralForumTopicUnhidden);
end;

{ TTgSharedUser }

class function TTgSharedUser.FromJson(const AJsonText: string): ITgSharedUser;
begin
  Result := TTgDto.Parse<ITgSharedUser>(AJsonText, TgMakeSharedUser);
end;

{ TTgUsersShared }

class function TTgUsersShared.FromJson(const AJsonText: string): ITgUsersShared;
begin
  Result := TTgDto.Parse<ITgUsersShared>(AJsonText, TgMakeUsersShared);
end;

{ TTgChatShared }

class function TTgChatShared.FromJson(const AJsonText: string): ITgChatShared;
begin
  Result := TTgDto.Parse<ITgChatShared>(AJsonText, TgMakeChatShared);
end;

{ TTgWriteAccessAllowed }

class function TTgWriteAccessAllowed.FromJson(const AJsonText: string): ITgWriteAccessAllowed;
begin
  Result := TTgDto.Parse<ITgWriteAccessAllowed>(AJsonText, TgMakeWriteAccessAllowed);
end;

{ TTgVideoChatScheduled }

class function TTgVideoChatScheduled.FromJson(const AJsonText: string): ITgVideoChatScheduled;
begin
  Result := TTgDto.Parse<ITgVideoChatScheduled>(AJsonText, TgMakeVideoChatScheduled);
end;

{ TTgVideoChatStarted }

class function TTgVideoChatStarted.FromJson(const AJsonText: string): ITgVideoChatStarted;
begin
  Result := TTgDto.Parse<ITgVideoChatStarted>(AJsonText, TgMakeVideoChatStarted);
end;

{ TTgVideoChatEnded }

class function TTgVideoChatEnded.FromJson(const AJsonText: string): ITgVideoChatEnded;
begin
  Result := TTgDto.Parse<ITgVideoChatEnded>(AJsonText, TgMakeVideoChatEnded);
end;

{ TTgVideoChatParticipantsInvited }

class function TTgVideoChatParticipantsInvited.FromJson(const AJsonText: string): ITgVideoChatParticipantsInvited;
begin
  Result := TTgDto.Parse<ITgVideoChatParticipantsInvited>(AJsonText, TgMakeVideoChatParticipantsInvited);
end;

{ TTgPaidMessagePriceChanged }

class function TTgPaidMessagePriceChanged.FromJson(const AJsonText: string): ITgPaidMessagePriceChanged;
begin
  Result := TTgDto.Parse<ITgPaidMessagePriceChanged>(AJsonText, TgMakePaidMessagePriceChanged);
end;

{ TTgDirectMessagePriceChanged }

class function TTgDirectMessagePriceChanged.FromJson(const AJsonText: string): ITgDirectMessagePriceChanged;
begin
  Result := TTgDto.Parse<ITgDirectMessagePriceChanged>(AJsonText, TgMakeDirectMessagePriceChanged);
end;

{ TTgSuggestedPostApproved }

class function TTgSuggestedPostApproved.FromJson(const AJsonText: string): ITgSuggestedPostApproved;
begin
  Result := TTgDto.Parse<ITgSuggestedPostApproved>(AJsonText, TgMakeSuggestedPostApproved);
end;

{ TTgSuggestedPostApprovalFailed }

class function TTgSuggestedPostApprovalFailed.FromJson(const AJsonText: string): ITgSuggestedPostApprovalFailed;
begin
  Result := TTgDto.Parse<ITgSuggestedPostApprovalFailed>(AJsonText, TgMakeSuggestedPostApprovalFailed);
end;

{ TTgSuggestedPostDeclined }

class function TTgSuggestedPostDeclined.FromJson(const AJsonText: string): ITgSuggestedPostDeclined;
begin
  Result := TTgDto.Parse<ITgSuggestedPostDeclined>(AJsonText, TgMakeSuggestedPostDeclined);
end;

{ TTgSuggestedPostPaid }

class function TTgSuggestedPostPaid.FromJson(const AJsonText: string): ITgSuggestedPostPaid;
begin
  Result := TTgDto.Parse<ITgSuggestedPostPaid>(AJsonText, TgMakeSuggestedPostPaid);
end;

{ TTgSuggestedPostRefunded }

class function TTgSuggestedPostRefunded.FromJson(const AJsonText: string): ITgSuggestedPostRefunded;
begin
  Result := TTgDto.Parse<ITgSuggestedPostRefunded>(AJsonText, TgMakeSuggestedPostRefunded);
end;

{ TTgGiveawayCreated }

class function TTgGiveawayCreated.FromJson(const AJsonText: string): ITgGiveawayCreated;
begin
  Result := TTgDto.Parse<ITgGiveawayCreated>(AJsonText, TgMakeGiveawayCreated);
end;

{ TTgGiveaway }

class function TTgGiveaway.FromJson(const AJsonText: string): ITgGiveaway;
begin
  Result := TTgDto.Parse<ITgGiveaway>(AJsonText, TgMakeGiveaway);
end;

{ TTgGiveawayWinners }

class function TTgGiveawayWinners.FromJson(const AJsonText: string): ITgGiveawayWinners;
begin
  Result := TTgDto.Parse<ITgGiveawayWinners>(AJsonText, TgMakeGiveawayWinners);
end;

{ TTgGiveawayCompleted }

class function TTgGiveawayCompleted.FromJson(const AJsonText: string): ITgGiveawayCompleted;
begin
  Result := TTgDto.Parse<ITgGiveawayCompleted>(AJsonText, TgMakeGiveawayCompleted);
end;

{ TTgLinkPreviewOptions }

class function TTgLinkPreviewOptions.Create: ITgLinkPreviewOptions;
begin
  Result := TTgLinkPreviewOptionsImpl.CreateNew;
end;

class function TTgLinkPreviewOptions.FromJson(const AJsonText: string): ITgLinkPreviewOptions;
begin
  Result := TTgDto.Parse<ITgLinkPreviewOptions>(AJsonText, TgMakeLinkPreviewOptions);
end;

{ TTgSuggestedPostPrice }

class function TTgSuggestedPostPrice.Create(const ACurrency: string;
  AAmount: Integer): ITgSuggestedPostPrice;
var
  LObj: TTgSuggestedPostPriceImpl;
begin
  LObj := TTgSuggestedPostPriceImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('currency', ACurrency);
  LObj.SetInt('amount', AAmount);
end;

class function TTgSuggestedPostPrice.FromJson(const AJsonText: string): ITgSuggestedPostPrice;
begin
  Result := TTgDto.Parse<ITgSuggestedPostPrice>(AJsonText, TgMakeSuggestedPostPrice);
end;

{ TTgSuggestedPostInfo }

class function TTgSuggestedPostInfo.FromJson(const AJsonText: string): ITgSuggestedPostInfo;
begin
  Result := TTgDto.Parse<ITgSuggestedPostInfo>(AJsonText, TgMakeSuggestedPostInfo);
end;

{ TTgSuggestedPostParameters }

class function TTgSuggestedPostParameters.Create: ITgSuggestedPostParameters;
begin
  Result := TTgSuggestedPostParametersImpl.CreateNew;
end;

{ TTgDirectMessagesTopic }

class function TTgDirectMessagesTopic.FromJson(const AJsonText: string): ITgDirectMessagesTopic;
begin
  Result := TTgDto.Parse<ITgDirectMessagesTopic>(AJsonText, TgMakeDirectMessagesTopic);
end;

{ TTgUserProfilePhotos }

class function TTgUserProfilePhotos.FromJson(const AJsonText: string): ITgUserProfilePhotos;
begin
  Result := TTgDto.Parse<ITgUserProfilePhotos>(AJsonText, TgMakeUserProfilePhotos);
end;

{ TTgUserProfileAudios }

class function TTgUserProfileAudios.FromJson(const AJsonText: string): ITgUserProfileAudios;
begin
  Result := TTgDto.Parse<ITgUserProfileAudios>(AJsonText, TgMakeUserProfileAudios);
end;

{ TTgFile }

class function TTgFile.FromJson(const AJsonText: string): ITgFile;
begin
  Result := TTgDto.Parse<ITgFile>(AJsonText, TgMakeFile);
end;

{ TTgWebAppInfo }

class function TTgWebAppInfo.Create(const AUrl: string): ITgWebAppInfo;
var
  LObj: TTgWebAppInfoImpl;
begin
  LObj := TTgWebAppInfoImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('url', AUrl);
end;

class function TTgWebAppInfo.FromJson(const AJsonText: string): ITgWebAppInfo;
begin
  Result := TTgDto.Parse<ITgWebAppInfo>(AJsonText, TgMakeWebAppInfo);
end;

{ TTgReplyKeyboardMarkup }

class function TTgReplyKeyboardMarkup.Create(const AKeyboard: array of TArray<ITgKeyboardButton>): ITgReplyKeyboardMarkup;
var
  LObj: TTgReplyKeyboardMarkupImpl;
begin
  LObj := TTgReplyKeyboardMarkupImpl.CreateNew;
  Result := LObj;
  LObj.SetObjects2('keyboard', TTgDto.ToIntf2<ITgKeyboardButton>(AKeyboard));
end;

{ TTgKeyboardButton }

class function TTgKeyboardButton.Create(const AText: string): ITgKeyboardButton;
var
  LObj: TTgKeyboardButtonImpl;
begin
  LObj := TTgKeyboardButtonImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('text', AText);
end;

{ TTgKeyboardButtonRequestUsers }

class function TTgKeyboardButtonRequestUsers.Create(ARequestId: Int64): ITgKeyboardButtonRequestUsers;
var
  LObj: TTgKeyboardButtonRequestUsersImpl;
begin
  LObj := TTgKeyboardButtonRequestUsersImpl.CreateNew;
  Result := LObj;
  LObj.SetInt64('request_id', ARequestId);
end;

{ TTgKeyboardButtonRequestChat }

class function TTgKeyboardButtonRequestChat.Create(ARequestId: Int64;
  AChatIsChannel: Boolean): ITgKeyboardButtonRequestChat;
var
  LObj: TTgKeyboardButtonRequestChatImpl;
begin
  LObj := TTgKeyboardButtonRequestChatImpl.CreateNew;
  Result := LObj;
  LObj.SetInt64('request_id', ARequestId);
  LObj.SetBool('chat_is_channel', AChatIsChannel);
end;

{ TTgKeyboardButtonRequestManagedBot }

class function TTgKeyboardButtonRequestManagedBot.Create(ARequestId: Int64): ITgKeyboardButtonRequestManagedBot;
var
  LObj: TTgKeyboardButtonRequestManagedBotImpl;
begin
  LObj := TTgKeyboardButtonRequestManagedBotImpl.CreateNew;
  Result := LObj;
  LObj.SetInt64('request_id', ARequestId);
end;

{ TTgKeyboardButtonPollType }

class function TTgKeyboardButtonPollType.Create: ITgKeyboardButtonPollType;
begin
  Result := TTgKeyboardButtonPollTypeImpl.CreateNew;
end;

{ TTgReplyKeyboardRemove }

class function TTgReplyKeyboardRemove.Create: ITgReplyKeyboardRemove;
var
  LObj: TTgReplyKeyboardRemoveImpl;
begin
  LObj := TTgReplyKeyboardRemoveImpl.CreateNew;
  Result := LObj;
  LObj.SetBool('remove_keyboard', True);
end;

{ TTgInlineKeyboardMarkup }

class function TTgInlineKeyboardMarkup.Create(const AInlineKeyboard: array of TArray<ITgInlineKeyboardButton>): ITgInlineKeyboardMarkup;
var
  LObj: TTgInlineKeyboardMarkupImpl;
begin
  LObj := TTgInlineKeyboardMarkupImpl.CreateNew;
  Result := LObj;
  LObj.SetObjects2('inline_keyboard', TTgDto.ToIntf2<ITgInlineKeyboardButton>(AInlineKeyboard));
end;

class function TTgInlineKeyboardMarkup.FromJson(const AJsonText: string): ITgInlineKeyboardMarkup;
begin
  Result := TTgDto.Parse<ITgInlineKeyboardMarkup>(AJsonText, TgMakeInlineKeyboardMarkup);
end;

{ TTgInlineKeyboardButton }

class function TTgInlineKeyboardButton.Create(const AText: string): ITgInlineKeyboardButton;
var
  LObj: TTgInlineKeyboardButtonImpl;
begin
  LObj := TTgInlineKeyboardButtonImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('text', AText);
end;

class function TTgInlineKeyboardButton.FromJson(const AJsonText: string): ITgInlineKeyboardButton;
begin
  Result := TTgDto.Parse<ITgInlineKeyboardButton>(AJsonText, TgMakeInlineKeyboardButton);
end;

{ TTgLoginUrl }

class function TTgLoginUrl.Create(const AUrl: string): ITgLoginUrl;
var
  LObj: TTgLoginUrlImpl;
begin
  LObj := TTgLoginUrlImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('url', AUrl);
end;

class function TTgLoginUrl.FromJson(const AJsonText: string): ITgLoginUrl;
begin
  Result := TTgDto.Parse<ITgLoginUrl>(AJsonText, TgMakeLoginUrl);
end;

{ TTgSwitchInlineQueryChosenChat }

class function TTgSwitchInlineQueryChosenChat.Create: ITgSwitchInlineQueryChosenChat;
begin
  Result := TTgSwitchInlineQueryChosenChatImpl.CreateNew;
end;

class function TTgSwitchInlineQueryChosenChat.FromJson(const AJsonText: string): ITgSwitchInlineQueryChosenChat;
begin
  Result := TTgDto.Parse<ITgSwitchInlineQueryChosenChat>(AJsonText, TgMakeSwitchInlineQueryChosenChat);
end;

{ TTgCopyTextButton }

class function TTgCopyTextButton.Create(const AText: string): ITgCopyTextButton;
var
  LObj: TTgCopyTextButtonImpl;
begin
  LObj := TTgCopyTextButtonImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('text', AText);
end;

class function TTgCopyTextButton.FromJson(const AJsonText: string): ITgCopyTextButton;
begin
  Result := TTgDto.Parse<ITgCopyTextButton>(AJsonText, TgMakeCopyTextButton);
end;

{ TTgDisabledButton }

class function TTgDisabledButton.Create: ITgDisabledButton;
begin
  Result := TTgDisabledButtonImpl.CreateNew;
end;

class function TTgDisabledButton.FromJson(const AJsonText: string): ITgDisabledButton;
begin
  Result := TTgDto.Parse<ITgDisabledButton>(AJsonText, TgMakeDisabledButton);
end;

{ TTgCallbackQuery }

class function TTgCallbackQuery.FromJson(const AJsonText: string): ITgCallbackQuery;
begin
  Result := TTgDto.Parse<ITgCallbackQuery>(AJsonText, TgMakeCallbackQuery);
end;

{ TTgForceReply }

class function TTgForceReply.Create: ITgForceReply;
var
  LObj: TTgForceReplyImpl;
begin
  LObj := TTgForceReplyImpl.CreateNew;
  Result := LObj;
  LObj.SetBool('force_reply', True);
end;

{ TTgCommunity }

class function TTgCommunity.FromJson(const AJsonText: string): ITgCommunity;
begin
  Result := TTgDto.Parse<ITgCommunity>(AJsonText, TgMakeCommunity);
end;

{ TTgChatPhoto }

class function TTgChatPhoto.FromJson(const AJsonText: string): ITgChatPhoto;
begin
  Result := TTgDto.Parse<ITgChatPhoto>(AJsonText, TgMakeChatPhoto);
end;

{ TTgChatInviteLink }

class function TTgChatInviteLink.FromJson(const AJsonText: string): ITgChatInviteLink;
begin
  Result := TTgDto.Parse<ITgChatInviteLink>(AJsonText, TgMakeChatInviteLink);
end;

{ TTgChatAdministratorRights }

class function TTgChatAdministratorRights.Create(AIsAnonymous: Boolean; ACanManageChat: Boolean;
  ACanDeleteMessages: Boolean; ACanManageVideoChats: Boolean; ACanRestrictMembers: Boolean;
  ACanPromoteMembers: Boolean; ACanChangeInfo: Boolean; ACanInviteUsers: Boolean;
  ACanPostStories: Boolean; ACanEditStories: Boolean; ACanDeleteStories: Boolean;
  ACanSendWelcomeMessages: Boolean): ITgChatAdministratorRights;
var
  LObj: TTgChatAdministratorRightsImpl;
begin
  LObj := TTgChatAdministratorRightsImpl.CreateNew;
  Result := LObj;
  LObj.SetBool('is_anonymous', AIsAnonymous);
  LObj.SetBool('can_manage_chat', ACanManageChat);
  LObj.SetBool('can_delete_messages', ACanDeleteMessages);
  LObj.SetBool('can_manage_video_chats', ACanManageVideoChats);
  LObj.SetBool('can_restrict_members', ACanRestrictMembers);
  LObj.SetBool('can_promote_members', ACanPromoteMembers);
  LObj.SetBool('can_change_info', ACanChangeInfo);
  LObj.SetBool('can_invite_users', ACanInviteUsers);
  LObj.SetBool('can_post_stories', ACanPostStories);
  LObj.SetBool('can_edit_stories', ACanEditStories);
  LObj.SetBool('can_delete_stories', ACanDeleteStories);
  LObj.SetBool('can_send_welcome_messages', ACanSendWelcomeMessages);
end;

class function TTgChatAdministratorRights.FromJson(const AJsonText: string): ITgChatAdministratorRights;
begin
  Result := TTgDto.Parse<ITgChatAdministratorRights>(AJsonText, TgMakeChatAdministratorRights);
end;

{ TTgChatMemberUpdated }

class function TTgChatMemberUpdated.FromJson(const AJsonText: string): ITgChatMemberUpdated;
begin
  Result := TTgDto.Parse<ITgChatMemberUpdated>(AJsonText, TgMakeChatMemberUpdated);
end;

{ TTgChatMember }

class function TTgChatMember.FromJson(const AJsonText: string): ITgChatMember;
begin
  Result := TTgDto.Parse<ITgChatMember>(AJsonText, TgMakeChatMember);
end;

{ TTgChatMemberOwner }

class function TTgChatMemberOwner.FromJson(const AJsonText: string): ITgChatMemberOwner;
begin
  Result := TTgDto.Parse<ITgChatMemberOwner>(AJsonText, TgMakeChatMemberOwner);
end;

{ TTgChatMemberAdministrator }

class function TTgChatMemberAdministrator.FromJson(const AJsonText: string): ITgChatMemberAdministrator;
begin
  Result := TTgDto.Parse<ITgChatMemberAdministrator>(AJsonText, TgMakeChatMemberAdministrator);
end;

{ TTgChatMemberMember }

class function TTgChatMemberMember.FromJson(const AJsonText: string): ITgChatMemberMember;
begin
  Result := TTgDto.Parse<ITgChatMemberMember>(AJsonText, TgMakeChatMemberMember);
end;

{ TTgChatMemberRestricted }

class function TTgChatMemberRestricted.FromJson(const AJsonText: string): ITgChatMemberRestricted;
begin
  Result := TTgDto.Parse<ITgChatMemberRestricted>(AJsonText, TgMakeChatMemberRestricted);
end;

{ TTgChatMemberLeft }

class function TTgChatMemberLeft.FromJson(const AJsonText: string): ITgChatMemberLeft;
begin
  Result := TTgDto.Parse<ITgChatMemberLeft>(AJsonText, TgMakeChatMemberLeft);
end;

{ TTgChatMemberBanned }

class function TTgChatMemberBanned.FromJson(const AJsonText: string): ITgChatMemberBanned;
begin
  Result := TTgDto.Parse<ITgChatMemberBanned>(AJsonText, TgMakeChatMemberBanned);
end;

{ TTgChatJoinRequest }

class function TTgChatJoinRequest.FromJson(const AJsonText: string): ITgChatJoinRequest;
begin
  Result := TTgDto.Parse<ITgChatJoinRequest>(AJsonText, TgMakeChatJoinRequest);
end;

{ TTgChatPermissions }

class function TTgChatPermissions.Create: ITgChatPermissions;
begin
  Result := TTgChatPermissionsImpl.CreateNew;
end;

class function TTgChatPermissions.FromJson(const AJsonText: string): ITgChatPermissions;
begin
  Result := TTgDto.Parse<ITgChatPermissions>(AJsonText, TgMakeChatPermissions);
end;

{ TTgBirthdate }

class function TTgBirthdate.FromJson(const AJsonText: string): ITgBirthdate;
begin
  Result := TTgDto.Parse<ITgBirthdate>(AJsonText, TgMakeBirthdate);
end;

{ TTgBusinessIntro }

class function TTgBusinessIntro.FromJson(const AJsonText: string): ITgBusinessIntro;
begin
  Result := TTgDto.Parse<ITgBusinessIntro>(AJsonText, TgMakeBusinessIntro);
end;

{ TTgBusinessLocation }

class function TTgBusinessLocation.FromJson(const AJsonText: string): ITgBusinessLocation;
begin
  Result := TTgDto.Parse<ITgBusinessLocation>(AJsonText, TgMakeBusinessLocation);
end;

{ TTgBusinessOpeningHoursInterval }

class function TTgBusinessOpeningHoursInterval.FromJson(const AJsonText: string): ITgBusinessOpeningHoursInterval;
begin
  Result := TTgDto.Parse<ITgBusinessOpeningHoursInterval>(AJsonText, TgMakeBusinessOpeningHoursInterval);
end;

{ TTgBusinessOpeningHours }

class function TTgBusinessOpeningHours.FromJson(const AJsonText: string): ITgBusinessOpeningHours;
begin
  Result := TTgDto.Parse<ITgBusinessOpeningHours>(AJsonText, TgMakeBusinessOpeningHours);
end;

{ TTgUserRating }

class function TTgUserRating.FromJson(const AJsonText: string): ITgUserRating;
begin
  Result := TTgDto.Parse<ITgUserRating>(AJsonText, TgMakeUserRating);
end;

{ TTgStoryAreaPosition }

class function TTgStoryAreaPosition.Create(AXPercentage: Double; AYPercentage: Double;
  AWidthPercentage: Double; AHeightPercentage: Double; ARotationAngle: Double;
  ACornerRadiusPercentage: Double): ITgStoryAreaPosition;
var
  LObj: TTgStoryAreaPositionImpl;
begin
  LObj := TTgStoryAreaPositionImpl.CreateNew;
  Result := LObj;
  LObj.SetDouble('x_percentage', AXPercentage);
  LObj.SetDouble('y_percentage', AYPercentage);
  LObj.SetDouble('width_percentage', AWidthPercentage);
  LObj.SetDouble('height_percentage', AHeightPercentage);
  LObj.SetDouble('rotation_angle', ARotationAngle);
  LObj.SetDouble('corner_radius_percentage', ACornerRadiusPercentage);
end;

{ TTgLocationAddress }

class function TTgLocationAddress.Create(const ACountryCode: string): ITgLocationAddress;
var
  LObj: TTgLocationAddressImpl;
begin
  LObj := TTgLocationAddressImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('country_code', ACountryCode);
end;

{ TTgStoryAreaTypeLocation }

class function TTgStoryAreaTypeLocation.Create(ALatitude: Double;
  ALongitude: Double): ITgStoryAreaTypeLocation;
var
  LObj: TTgStoryAreaTypeLocationImpl;
begin
  LObj := TTgStoryAreaTypeLocationImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'location');
  LObj.SetDouble('latitude', ALatitude);
  LObj.SetDouble('longitude', ALongitude);
end;

{ TTgStoryAreaTypeSuggestedReaction }

class function TTgStoryAreaTypeSuggestedReaction.Create(const AReactionType: ITgReactionType): ITgStoryAreaTypeSuggestedReaction;
var
  LObj: TTgStoryAreaTypeSuggestedReactionImpl;
begin
  LObj := TTgStoryAreaTypeSuggestedReactionImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'suggested_reaction');
  LObj.SetObject('reaction_type', AReactionType);
end;

{ TTgStoryAreaTypeLink }

class function TTgStoryAreaTypeLink.Create(const AUrl: string): ITgStoryAreaTypeLink;
var
  LObj: TTgStoryAreaTypeLinkImpl;
begin
  LObj := TTgStoryAreaTypeLinkImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'link');
  LObj.SetStr('url', AUrl);
end;

{ TTgStoryAreaTypeWeather }

class function TTgStoryAreaTypeWeather.Create(ATemperature: Double; const AEmoji: string;
  ABackgroundColor: Integer): ITgStoryAreaTypeWeather;
var
  LObj: TTgStoryAreaTypeWeatherImpl;
begin
  LObj := TTgStoryAreaTypeWeatherImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'weather');
  LObj.SetDouble('temperature', ATemperature);
  LObj.SetStr('emoji', AEmoji);
  LObj.SetInt('background_color', ABackgroundColor);
end;

{ TTgStoryAreaTypeUniqueGift }

class function TTgStoryAreaTypeUniqueGift.Create(const AName: string): ITgStoryAreaTypeUniqueGift;
var
  LObj: TTgStoryAreaTypeUniqueGiftImpl;
begin
  LObj := TTgStoryAreaTypeUniqueGiftImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'unique_gift');
  LObj.SetStr('name', AName);
end;

{ TTgStoryArea }

class function TTgStoryArea.Create(const APosition: ITgStoryAreaPosition;
  const AStoryAreaType: TTgStoryAreaType): ITgStoryArea;
var
  LObj: TTgStoryAreaImpl;
begin
  LObj := TTgStoryAreaImpl.CreateNew;
  Result := LObj;
  LObj.SetObject('position', APosition);
  LObj.SetObject('type', AStoryAreaType.Value);
end;

{ TTgChatLocation }

class function TTgChatLocation.FromJson(const AJsonText: string): ITgChatLocation;
begin
  Result := TTgDto.Parse<ITgChatLocation>(AJsonText, TgMakeChatLocation);
end;

{ TTgReactionType }

class function TTgReactionType.FromJson(const AJsonText: string): ITgReactionType;
begin
  Result := TTgDto.Parse<ITgReactionType>(AJsonText, TgMakeReactionType);
end;

{ TTgReactionTypeEmoji }

class function TTgReactionTypeEmoji.Create(const AEmoji: string): ITgReactionTypeEmoji;
var
  LObj: TTgReactionTypeEmojiImpl;
begin
  LObj := TTgReactionTypeEmojiImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'emoji');
  LObj.SetStr('emoji', AEmoji);
end;

class function TTgReactionTypeEmoji.FromJson(const AJsonText: string): ITgReactionTypeEmoji;
begin
  Result := TTgDto.Parse<ITgReactionTypeEmoji>(AJsonText, TgMakeReactionTypeEmoji);
end;

{ TTgReactionTypeCustomEmoji }

class function TTgReactionTypeCustomEmoji.Create(const ACustomEmojiId: string): ITgReactionTypeCustomEmoji;
var
  LObj: TTgReactionTypeCustomEmojiImpl;
begin
  LObj := TTgReactionTypeCustomEmojiImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'custom_emoji');
  LObj.SetStr('custom_emoji_id', ACustomEmojiId);
end;

class function TTgReactionTypeCustomEmoji.FromJson(const AJsonText: string): ITgReactionTypeCustomEmoji;
begin
  Result := TTgDto.Parse<ITgReactionTypeCustomEmoji>(AJsonText, TgMakeReactionTypeCustomEmoji);
end;

{ TTgReactionTypePaid }

class function TTgReactionTypePaid.Create: ITgReactionTypePaid;
var
  LObj: TTgReactionTypePaidImpl;
begin
  LObj := TTgReactionTypePaidImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'paid');
end;

class function TTgReactionTypePaid.FromJson(const AJsonText: string): ITgReactionTypePaid;
begin
  Result := TTgDto.Parse<ITgReactionTypePaid>(AJsonText, TgMakeReactionTypePaid);
end;

{ TTgReactionCount }

class function TTgReactionCount.FromJson(const AJsonText: string): ITgReactionCount;
begin
  Result := TTgDto.Parse<ITgReactionCount>(AJsonText, TgMakeReactionCount);
end;

{ TTgMessageReactionUpdated }

class function TTgMessageReactionUpdated.FromJson(const AJsonText: string): ITgMessageReactionUpdated;
begin
  Result := TTgDto.Parse<ITgMessageReactionUpdated>(AJsonText, TgMakeMessageReactionUpdated);
end;

{ TTgMessageReactionCountUpdated }

class function TTgMessageReactionCountUpdated.FromJson(const AJsonText: string): ITgMessageReactionCountUpdated;
begin
  Result := TTgDto.Parse<ITgMessageReactionCountUpdated>(AJsonText, TgMakeMessageReactionCountUpdated);
end;

{ TTgForumTopic }

class function TTgForumTopic.FromJson(const AJsonText: string): ITgForumTopic;
begin
  Result := TTgDto.Parse<ITgForumTopic>(AJsonText, TgMakeForumTopic);
end;

{ TTgGiftBackground }

class function TTgGiftBackground.FromJson(const AJsonText: string): ITgGiftBackground;
begin
  Result := TTgDto.Parse<ITgGiftBackground>(AJsonText, TgMakeGiftBackground);
end;

{ TTgGift }

class function TTgGift.FromJson(const AJsonText: string): ITgGift;
begin
  Result := TTgDto.Parse<ITgGift>(AJsonText, TgMakeGift);
end;

{ TTgGifts }

class function TTgGifts.FromJson(const AJsonText: string): ITgGifts;
begin
  Result := TTgDto.Parse<ITgGifts>(AJsonText, TgMakeGifts);
end;

{ TTgUniqueGiftModel }

class function TTgUniqueGiftModel.FromJson(const AJsonText: string): ITgUniqueGiftModel;
begin
  Result := TTgDto.Parse<ITgUniqueGiftModel>(AJsonText, TgMakeUniqueGiftModel);
end;

{ TTgUniqueGiftSymbol }

class function TTgUniqueGiftSymbol.FromJson(const AJsonText: string): ITgUniqueGiftSymbol;
begin
  Result := TTgDto.Parse<ITgUniqueGiftSymbol>(AJsonText, TgMakeUniqueGiftSymbol);
end;

{ TTgUniqueGiftBackdropColors }

class function TTgUniqueGiftBackdropColors.FromJson(const AJsonText: string): ITgUniqueGiftBackdropColors;
begin
  Result := TTgDto.Parse<ITgUniqueGiftBackdropColors>(AJsonText, TgMakeUniqueGiftBackdropColors);
end;

{ TTgUniqueGiftBackdrop }

class function TTgUniqueGiftBackdrop.FromJson(const AJsonText: string): ITgUniqueGiftBackdrop;
begin
  Result := TTgDto.Parse<ITgUniqueGiftBackdrop>(AJsonText, TgMakeUniqueGiftBackdrop);
end;

{ TTgUniqueGiftColors }

class function TTgUniqueGiftColors.FromJson(const AJsonText: string): ITgUniqueGiftColors;
begin
  Result := TTgDto.Parse<ITgUniqueGiftColors>(AJsonText, TgMakeUniqueGiftColors);
end;

{ TTgUniqueGift }

class function TTgUniqueGift.FromJson(const AJsonText: string): ITgUniqueGift;
begin
  Result := TTgDto.Parse<ITgUniqueGift>(AJsonText, TgMakeUniqueGift);
end;

{ TTgGiftInfo }

class function TTgGiftInfo.FromJson(const AJsonText: string): ITgGiftInfo;
begin
  Result := TTgDto.Parse<ITgGiftInfo>(AJsonText, TgMakeGiftInfo);
end;

{ TTgUniqueGiftInfo }

class function TTgUniqueGiftInfo.FromJson(const AJsonText: string): ITgUniqueGiftInfo;
begin
  Result := TTgDto.Parse<ITgUniqueGiftInfo>(AJsonText, TgMakeUniqueGiftInfo);
end;

{ TTgOwnedGift }

class function TTgOwnedGift.FromJson(const AJsonText: string): ITgOwnedGift;
begin
  Result := TTgDto.Parse<ITgOwnedGift>(AJsonText, TgMakeOwnedGift);
end;

{ TTgOwnedGiftRegular }

class function TTgOwnedGiftRegular.FromJson(const AJsonText: string): ITgOwnedGiftRegular;
begin
  Result := TTgDto.Parse<ITgOwnedGiftRegular>(AJsonText, TgMakeOwnedGiftRegular);
end;

{ TTgOwnedGiftUnique }

class function TTgOwnedGiftUnique.FromJson(const AJsonText: string): ITgOwnedGiftUnique;
begin
  Result := TTgDto.Parse<ITgOwnedGiftUnique>(AJsonText, TgMakeOwnedGiftUnique);
end;

{ TTgOwnedGifts }

class function TTgOwnedGifts.FromJson(const AJsonText: string): ITgOwnedGifts;
begin
  Result := TTgDto.Parse<ITgOwnedGifts>(AJsonText, TgMakeOwnedGifts);
end;

{ TTgBotAccessSettings }

class function TTgBotAccessSettings.FromJson(const AJsonText: string): ITgBotAccessSettings;
begin
  Result := TTgDto.Parse<ITgBotAccessSettings>(AJsonText, TgMakeBotAccessSettings);
end;

{ TTgAcceptedGiftTypes }

class function TTgAcceptedGiftTypes.Create(AUnlimitedGifts: Boolean; ALimitedGifts: Boolean;
  AUniqueGifts: Boolean; APremiumSubscription: Boolean;
  AGiftsFromChannels: Boolean): ITgAcceptedGiftTypes;
var
  LObj: TTgAcceptedGiftTypesImpl;
begin
  LObj := TTgAcceptedGiftTypesImpl.CreateNew;
  Result := LObj;
  LObj.SetBool('unlimited_gifts', AUnlimitedGifts);
  LObj.SetBool('limited_gifts', ALimitedGifts);
  LObj.SetBool('unique_gifts', AUniqueGifts);
  LObj.SetBool('premium_subscription', APremiumSubscription);
  LObj.SetBool('gifts_from_channels', AGiftsFromChannels);
end;

class function TTgAcceptedGiftTypes.FromJson(const AJsonText: string): ITgAcceptedGiftTypes;
begin
  Result := TTgDto.Parse<ITgAcceptedGiftTypes>(AJsonText, TgMakeAcceptedGiftTypes);
end;

{ TTgStarAmount }

class function TTgStarAmount.FromJson(const AJsonText: string): ITgStarAmount;
begin
  Result := TTgDto.Parse<ITgStarAmount>(AJsonText, TgMakeStarAmount);
end;

{ TTgBotCommand }

class function TTgBotCommand.Create(const ACommand: string;
  const ADescription: string): ITgBotCommand;
var
  LObj: TTgBotCommandImpl;
begin
  LObj := TTgBotCommandImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('command', ACommand);
  LObj.SetStr('description', ADescription);
end;

class function TTgBotCommand.FromJson(const AJsonText: string): ITgBotCommand;
begin
  Result := TTgDto.Parse<ITgBotCommand>(AJsonText, TgMakeBotCommand);
end;

{ TTgBotCommandScopeDefault }

class function TTgBotCommandScopeDefault.Create: ITgBotCommandScopeDefault;
var
  LObj: TTgBotCommandScopeDefaultImpl;
begin
  LObj := TTgBotCommandScopeDefaultImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'default');
end;

{ TTgBotCommandScopeAllPrivateChats }

class function TTgBotCommandScopeAllPrivateChats.Create: ITgBotCommandScopeAllPrivateChats;
var
  LObj: TTgBotCommandScopeAllPrivateChatsImpl;
begin
  LObj := TTgBotCommandScopeAllPrivateChatsImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'all_private_chats');
end;

{ TTgBotCommandScopeAllGroupChats }

class function TTgBotCommandScopeAllGroupChats.Create: ITgBotCommandScopeAllGroupChats;
var
  LObj: TTgBotCommandScopeAllGroupChatsImpl;
begin
  LObj := TTgBotCommandScopeAllGroupChatsImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'all_group_chats');
end;

{ TTgBotCommandScopeAllChatAdministrators }

class function TTgBotCommandScopeAllChatAdministrators.Create: ITgBotCommandScopeAllChatAdministrators;
var
  LObj: TTgBotCommandScopeAllChatAdministratorsImpl;
begin
  LObj := TTgBotCommandScopeAllChatAdministratorsImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'all_chat_administrators');
end;

{ TTgBotCommandScopeChat }

class function TTgBotCommandScopeChat.Create(const AChatId: TTgChatId): ITgBotCommandScopeChat;
var
  LObj: TTgBotCommandScopeChatImpl;
begin
  LObj := TTgBotCommandScopeChatImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'chat');
  LObj.SetChatId('chat_id', AChatId);
end;

{ TTgBotCommandScopeChatAdministrators }

class function TTgBotCommandScopeChatAdministrators.Create(const AChatId: TTgChatId): ITgBotCommandScopeChatAdministrators;
var
  LObj: TTgBotCommandScopeChatAdministratorsImpl;
begin
  LObj := TTgBotCommandScopeChatAdministratorsImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'chat_administrators');
  LObj.SetChatId('chat_id', AChatId);
end;

{ TTgBotCommandScopeChatMember }

class function TTgBotCommandScopeChatMember.Create(const AChatId: TTgChatId;
  AUserId: Int64): ITgBotCommandScopeChatMember;
var
  LObj: TTgBotCommandScopeChatMemberImpl;
begin
  LObj := TTgBotCommandScopeChatMemberImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'chat_member');
  LObj.SetChatId('chat_id', AChatId);
  LObj.SetInt64('user_id', AUserId);
end;

{ TTgBotName }

class function TTgBotName.FromJson(const AJsonText: string): ITgBotName;
begin
  Result := TTgDto.Parse<ITgBotName>(AJsonText, TgMakeBotName);
end;

{ TTgBotDescription }

class function TTgBotDescription.FromJson(const AJsonText: string): ITgBotDescription;
begin
  Result := TTgDto.Parse<ITgBotDescription>(AJsonText, TgMakeBotDescription);
end;

{ TTgBotShortDescription }

class function TTgBotShortDescription.FromJson(const AJsonText: string): ITgBotShortDescription;
begin
  Result := TTgDto.Parse<ITgBotShortDescription>(AJsonText, TgMakeBotShortDescription);
end;

{ TTgMenuButton }

class function TTgMenuButton.FromJson(const AJsonText: string): ITgMenuButton;
begin
  Result := TTgDto.Parse<ITgMenuButton>(AJsonText, TgMakeMenuButton);
end;

{ TTgMenuButtonCommands }

class function TTgMenuButtonCommands.Create: ITgMenuButtonCommands;
var
  LObj: TTgMenuButtonCommandsImpl;
begin
  LObj := TTgMenuButtonCommandsImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'commands');
end;

class function TTgMenuButtonCommands.FromJson(const AJsonText: string): ITgMenuButtonCommands;
begin
  Result := TTgDto.Parse<ITgMenuButtonCommands>(AJsonText, TgMakeMenuButtonCommands);
end;

{ TTgMenuButtonWebApp }

class function TTgMenuButtonWebApp.Create(const AText: string;
  const AWebApp: ITgWebAppInfo): ITgMenuButtonWebApp;
var
  LObj: TTgMenuButtonWebAppImpl;
begin
  LObj := TTgMenuButtonWebAppImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'web_app');
  LObj.SetStr('text', AText);
  LObj.SetObject('web_app', AWebApp);
end;

class function TTgMenuButtonWebApp.FromJson(const AJsonText: string): ITgMenuButtonWebApp;
begin
  Result := TTgDto.Parse<ITgMenuButtonWebApp>(AJsonText, TgMakeMenuButtonWebApp);
end;

{ TTgMenuButtonDefault }

class function TTgMenuButtonDefault.Create: ITgMenuButtonDefault;
var
  LObj: TTgMenuButtonDefaultImpl;
begin
  LObj := TTgMenuButtonDefaultImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'default');
end;

class function TTgMenuButtonDefault.FromJson(const AJsonText: string): ITgMenuButtonDefault;
begin
  Result := TTgDto.Parse<ITgMenuButtonDefault>(AJsonText, TgMakeMenuButtonDefault);
end;

{ TTgChatBoostSource }

class function TTgChatBoostSource.FromJson(const AJsonText: string): ITgChatBoostSource;
begin
  Result := TTgDto.Parse<ITgChatBoostSource>(AJsonText, TgMakeChatBoostSource);
end;

{ TTgChatBoostSourcePremium }

class function TTgChatBoostSourcePremium.FromJson(const AJsonText: string): ITgChatBoostSourcePremium;
begin
  Result := TTgDto.Parse<ITgChatBoostSourcePremium>(AJsonText, TgMakeChatBoostSourcePremium);
end;

{ TTgChatBoostSourceGiftCode }

class function TTgChatBoostSourceGiftCode.FromJson(const AJsonText: string): ITgChatBoostSourceGiftCode;
begin
  Result := TTgDto.Parse<ITgChatBoostSourceGiftCode>(AJsonText, TgMakeChatBoostSourceGiftCode);
end;

{ TTgChatBoostSourceGiveaway }

class function TTgChatBoostSourceGiveaway.FromJson(const AJsonText: string): ITgChatBoostSourceGiveaway;
begin
  Result := TTgDto.Parse<ITgChatBoostSourceGiveaway>(AJsonText, TgMakeChatBoostSourceGiveaway);
end;

{ TTgChatBoost }

class function TTgChatBoost.FromJson(const AJsonText: string): ITgChatBoost;
begin
  Result := TTgDto.Parse<ITgChatBoost>(AJsonText, TgMakeChatBoost);
end;

{ TTgChatBoostUpdated }

class function TTgChatBoostUpdated.FromJson(const AJsonText: string): ITgChatBoostUpdated;
begin
  Result := TTgDto.Parse<ITgChatBoostUpdated>(AJsonText, TgMakeChatBoostUpdated);
end;

{ TTgChatBoostRemoved }

class function TTgChatBoostRemoved.FromJson(const AJsonText: string): ITgChatBoostRemoved;
begin
  Result := TTgDto.Parse<ITgChatBoostRemoved>(AJsonText, TgMakeChatBoostRemoved);
end;

{ TTgChatOwnerLeft }

class function TTgChatOwnerLeft.FromJson(const AJsonText: string): ITgChatOwnerLeft;
begin
  Result := TTgDto.Parse<ITgChatOwnerLeft>(AJsonText, TgMakeChatOwnerLeft);
end;

{ TTgChatOwnerChanged }

class function TTgChatOwnerChanged.FromJson(const AJsonText: string): ITgChatOwnerChanged;
begin
  Result := TTgDto.Parse<ITgChatOwnerChanged>(AJsonText, TgMakeChatOwnerChanged);
end;

{ TTgUserChatBoosts }

class function TTgUserChatBoosts.FromJson(const AJsonText: string): ITgUserChatBoosts;
begin
  Result := TTgDto.Parse<ITgUserChatBoosts>(AJsonText, TgMakeUserChatBoosts);
end;

{ TTgBusinessBotRights }

class function TTgBusinessBotRights.FromJson(const AJsonText: string): ITgBusinessBotRights;
begin
  Result := TTgDto.Parse<ITgBusinessBotRights>(AJsonText, TgMakeBusinessBotRights);
end;

{ TTgBusinessConnection }

class function TTgBusinessConnection.FromJson(const AJsonText: string): ITgBusinessConnection;
begin
  Result := TTgDto.Parse<ITgBusinessConnection>(AJsonText, TgMakeBusinessConnection);
end;

{ TTgBusinessMessagesDeleted }

class function TTgBusinessMessagesDeleted.FromJson(const AJsonText: string): ITgBusinessMessagesDeleted;
begin
  Result := TTgDto.Parse<ITgBusinessMessagesDeleted>(AJsonText, TgMakeBusinessMessagesDeleted);
end;

{ TTgSentWebAppMessage }

class function TTgSentWebAppMessage.FromJson(const AJsonText: string): ITgSentWebAppMessage;
begin
  Result := TTgDto.Parse<ITgSentWebAppMessage>(AJsonText, TgMakeSentWebAppMessage);
end;

{ TTgSentGuestMessage }

class function TTgSentGuestMessage.FromJson(const AJsonText: string): ITgSentGuestMessage;
begin
  Result := TTgDto.Parse<ITgSentGuestMessage>(AJsonText, TgMakeSentGuestMessage);
end;

{ TTgPreparedInlineMessage }

class function TTgPreparedInlineMessage.FromJson(const AJsonText: string): ITgPreparedInlineMessage;
begin
  Result := TTgDto.Parse<ITgPreparedInlineMessage>(AJsonText, TgMakePreparedInlineMessage);
end;

{ TTgPreparedKeyboardButton }

class function TTgPreparedKeyboardButton.FromJson(const AJsonText: string): ITgPreparedKeyboardButton;
begin
  Result := TTgDto.Parse<ITgPreparedKeyboardButton>(AJsonText, TgMakePreparedKeyboardButton);
end;

{ TTgResponseParameters }

class function TTgResponseParameters.FromJson(const AJsonText: string): ITgResponseParameters;
begin
  Result := TTgDto.Parse<ITgResponseParameters>(AJsonText, TgMakeResponseParameters);
end;

{ TTgInputMediaAnimation }

class function TTgInputMediaAnimation.Create(const AMedia: TTgInputFile): ITgInputMediaAnimation;
var
  LObj: TTgInputMediaAnimationImpl;
begin
  LObj := TTgInputMediaAnimationImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'animation');
  LObj.SetFile('media', AMedia);
end;

{ TTgInputMediaAudio }

class function TTgInputMediaAudio.Create(const AMedia: TTgInputFile): ITgInputMediaAudio;
var
  LObj: TTgInputMediaAudioImpl;
begin
  LObj := TTgInputMediaAudioImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'audio');
  LObj.SetFile('media', AMedia);
end;

{ TTgInputMediaDocument }

class function TTgInputMediaDocument.Create(const AMedia: TTgInputFile): ITgInputMediaDocument;
var
  LObj: TTgInputMediaDocumentImpl;
begin
  LObj := TTgInputMediaDocumentImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'document');
  LObj.SetFile('media', AMedia);
end;

{ TTgInputMediaLink }

class function TTgInputMediaLink.Create(const AUrl: string): ITgInputMediaLink;
var
  LObj: TTgInputMediaLinkImpl;
begin
  LObj := TTgInputMediaLinkImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'link');
  LObj.SetStr('url', AUrl);
end;

{ TTgInputMediaLivePhoto }

class function TTgInputMediaLivePhoto.Create(const AMedia: TTgInputFile;
  const APhoto: TTgInputFile): ITgInputMediaLivePhoto;
var
  LObj: TTgInputMediaLivePhotoImpl;
begin
  LObj := TTgInputMediaLivePhotoImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'live_photo');
  LObj.SetFile('media', AMedia);
  LObj.SetFile('photo', APhoto);
end;

{ TTgInputMediaLocation }

class function TTgInputMediaLocation.Create(ALatitude: Double;
  ALongitude: Double): ITgInputMediaLocation;
var
  LObj: TTgInputMediaLocationImpl;
begin
  LObj := TTgInputMediaLocationImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'location');
  LObj.SetDouble('latitude', ALatitude);
  LObj.SetDouble('longitude', ALongitude);
end;

{ TTgInputMediaPhoto }

class function TTgInputMediaPhoto.Create(const AMedia: TTgInputFile): ITgInputMediaPhoto;
var
  LObj: TTgInputMediaPhotoImpl;
begin
  LObj := TTgInputMediaPhotoImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'photo');
  LObj.SetFile('media', AMedia);
end;

{ TTgInputMediaSticker }

class function TTgInputMediaSticker.Create(const AMedia: TTgInputFile): ITgInputMediaSticker;
var
  LObj: TTgInputMediaStickerImpl;
begin
  LObj := TTgInputMediaStickerImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'sticker');
  LObj.SetFile('media', AMedia);
end;

{ TTgInputMediaVenue }

class function TTgInputMediaVenue.Create(ALatitude: Double; ALongitude: Double;
  const ATitle: string; const AAddress: string): ITgInputMediaVenue;
var
  LObj: TTgInputMediaVenueImpl;
begin
  LObj := TTgInputMediaVenueImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'venue');
  LObj.SetDouble('latitude', ALatitude);
  LObj.SetDouble('longitude', ALongitude);
  LObj.SetStr('title', ATitle);
  LObj.SetStr('address', AAddress);
end;

{ TTgInputMediaVideo }

class function TTgInputMediaVideo.Create(const AMedia: TTgInputFile): ITgInputMediaVideo;
var
  LObj: TTgInputMediaVideoImpl;
begin
  LObj := TTgInputMediaVideoImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'video');
  LObj.SetFile('media', AMedia);
end;

{ TTgInputMediaVoiceNote }

class function TTgInputMediaVoiceNote.Create(const AMedia: TTgInputFile): ITgInputMediaVoiceNote;
var
  LObj: TTgInputMediaVoiceNoteImpl;
begin
  LObj := TTgInputMediaVoiceNoteImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'voice_note');
  LObj.SetFile('media', AMedia);
end;

{ TTgInputPaidMediaLivePhoto }

class function TTgInputPaidMediaLivePhoto.Create(const AMedia: TTgInputFile;
  const APhoto: TTgInputFile): ITgInputPaidMediaLivePhoto;
var
  LObj: TTgInputPaidMediaLivePhotoImpl;
begin
  LObj := TTgInputPaidMediaLivePhotoImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'live_photo');
  LObj.SetFile('media', AMedia);
  LObj.SetFile('photo', APhoto);
end;

{ TTgInputPaidMediaPhoto }

class function TTgInputPaidMediaPhoto.Create(const AMedia: TTgInputFile): ITgInputPaidMediaPhoto;
var
  LObj: TTgInputPaidMediaPhotoImpl;
begin
  LObj := TTgInputPaidMediaPhotoImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'photo');
  LObj.SetFile('media', AMedia);
end;

{ TTgInputPaidMediaVideo }

class function TTgInputPaidMediaVideo.Create(const AMedia: TTgInputFile): ITgInputPaidMediaVideo;
var
  LObj: TTgInputPaidMediaVideoImpl;
begin
  LObj := TTgInputPaidMediaVideoImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'video');
  LObj.SetFile('media', AMedia);
end;

{ TTgInputProfilePhotoStatic }

class function TTgInputProfilePhotoStatic.Create(const APhoto: TTgInputFile): ITgInputProfilePhotoStatic;
var
  LObj: TTgInputProfilePhotoStaticImpl;
begin
  LObj := TTgInputProfilePhotoStaticImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'static');
  LObj.SetFile('photo', APhoto);
end;

{ TTgInputProfilePhotoAnimated }

class function TTgInputProfilePhotoAnimated.Create(const AAnimation: TTgInputFile): ITgInputProfilePhotoAnimated;
var
  LObj: TTgInputProfilePhotoAnimatedImpl;
begin
  LObj := TTgInputProfilePhotoAnimatedImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'animated');
  LObj.SetFile('animation', AAnimation);
end;

{ TTgInputStoryContentPhoto }

class function TTgInputStoryContentPhoto.Create(const APhoto: TTgInputFile): ITgInputStoryContentPhoto;
var
  LObj: TTgInputStoryContentPhotoImpl;
begin
  LObj := TTgInputStoryContentPhotoImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'photo');
  LObj.SetFile('photo', APhoto);
end;

{ TTgInputStoryContentVideo }

class function TTgInputStoryContentVideo.Create(const AVideo: TTgInputFile): ITgInputStoryContentVideo;
var
  LObj: TTgInputStoryContentVideoImpl;
begin
  LObj := TTgInputStoryContentVideoImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'video');
  LObj.SetFile('video', AVideo);
end;

{ TTgSticker }

class function TTgSticker.FromJson(const AJsonText: string): ITgSticker;
begin
  Result := TTgDto.Parse<ITgSticker>(AJsonText, TgMakeSticker);
end;

{ TTgStickerSet }

class function TTgStickerSet.FromJson(const AJsonText: string): ITgStickerSet;
begin
  Result := TTgDto.Parse<ITgStickerSet>(AJsonText, TgMakeStickerSet);
end;

{ TTgMaskPosition }

class function TTgMaskPosition.Create(const APoint: string; AXShift: Double; AYShift: Double;
  AScale: Double): ITgMaskPosition;
var
  LObj: TTgMaskPositionImpl;
begin
  LObj := TTgMaskPositionImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('point', APoint);
  LObj.SetDouble('x_shift', AXShift);
  LObj.SetDouble('y_shift', AYShift);
  LObj.SetDouble('scale', AScale);
end;

class function TTgMaskPosition.FromJson(const AJsonText: string): ITgMaskPosition;
begin
  Result := TTgDto.Parse<ITgMaskPosition>(AJsonText, TgMakeMaskPosition);
end;

{ TTgInputSticker }

class function TTgInputSticker.Create(const ASticker: TTgInputFile; const AFormat: string;
  const AEmojiList: TArray<string>): ITgInputSticker;
var
  LObj: TTgInputStickerImpl;
begin
  LObj := TTgInputStickerImpl.CreateNew;
  Result := LObj;
  LObj.SetFile('sticker', ASticker);
  LObj.SetStr('format', AFormat);
  LObj.SetStrings('emoji_list', AEmojiList);
end;

{ TTgRichMessage }

class function TTgRichMessage.FromJson(const AJsonText: string): ITgRichMessage;
begin
  Result := TTgDto.Parse<ITgRichMessage>(AJsonText, TgMakeRichMessage);
end;

{ TTgInputRichMessage }

class function TTgInputRichMessage.Create: ITgInputRichMessage;
begin
  Result := TTgInputRichMessageImpl.CreateNew;
end;

{ TTgInputRichMessageMedia }

class function TTgInputRichMessageMedia.Create(const AId: string;
  const AMedia: TTgInputRichMedia): ITgInputRichMessageMedia;
var
  LObj: TTgInputRichMessageMediaImpl;
begin
  LObj := TTgInputRichMessageMediaImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('id', AId);
  LObj.SetObject('media', AMedia.Value);
end;

{ TTgRichMessageButton }

class function TTgRichMessageButton.Create(const AText: ITgRichText): ITgRichMessageButton;
var
  LObj: TTgRichMessageButtonImpl;
begin
  LObj := TTgRichMessageButtonImpl.CreateNew;
  Result := LObj;
  LObj.SetObject('text', AText);
end;

class function TTgRichMessageButton.FromJson(const AJsonText: string): ITgRichMessageButton;
begin
  Result := TTgDto.Parse<ITgRichMessageButton>(AJsonText, TgMakeRichMessageButton);
end;

{ TTgRichText }

class function TTgRichText.FromJson(const AJsonText: string): ITgRichText;
begin
  Result := TTgDto.Parse<ITgRichText>(AJsonText, TgMakeRichText);
end;

{ TTgRichTextPlain }

class function TTgRichTextPlain.Create(const AText: string): ITgRichTextPlain;
begin
  Result := TTgRichTextPlainImpl.CreateValue(TJSONString.Create(AText));
end;

{ TTgRichTextList }

class function TTgRichTextList.Create(const AItems: array of ITgRichText): ITgRichTextList;
begin
  Result := TTgRichTextListImpl.CreateValue(TTgDto.SerializeArray(TTgDto.ToIntf<ITgRichText>(AItems), nil));
end;

{ TTgRichTextBold }

class function TTgRichTextBold.Create(const AText: ITgRichText): ITgRichTextBold;
var
  LObj: TTgRichTextBoldImpl;
begin
  LObj := TTgRichTextBoldImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'bold');
  LObj.SetObject('text', AText);
end;

class function TTgRichTextBold.FromJson(const AJsonText: string): ITgRichTextBold;
begin
  Result := TTgDto.Parse<ITgRichTextBold>(AJsonText, TgMakeRichTextBold);
end;

{ TTgRichTextItalic }

class function TTgRichTextItalic.Create(const AText: ITgRichText): ITgRichTextItalic;
var
  LObj: TTgRichTextItalicImpl;
begin
  LObj := TTgRichTextItalicImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'italic');
  LObj.SetObject('text', AText);
end;

class function TTgRichTextItalic.FromJson(const AJsonText: string): ITgRichTextItalic;
begin
  Result := TTgDto.Parse<ITgRichTextItalic>(AJsonText, TgMakeRichTextItalic);
end;

{ TTgRichTextUnderline }

class function TTgRichTextUnderline.Create(const AText: ITgRichText): ITgRichTextUnderline;
var
  LObj: TTgRichTextUnderlineImpl;
begin
  LObj := TTgRichTextUnderlineImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'underline');
  LObj.SetObject('text', AText);
end;

class function TTgRichTextUnderline.FromJson(const AJsonText: string): ITgRichTextUnderline;
begin
  Result := TTgDto.Parse<ITgRichTextUnderline>(AJsonText, TgMakeRichTextUnderline);
end;

{ TTgRichTextStrikethrough }

class function TTgRichTextStrikethrough.Create(const AText: ITgRichText): ITgRichTextStrikethrough;
var
  LObj: TTgRichTextStrikethroughImpl;
begin
  LObj := TTgRichTextStrikethroughImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'strikethrough');
  LObj.SetObject('text', AText);
end;

class function TTgRichTextStrikethrough.FromJson(const AJsonText: string): ITgRichTextStrikethrough;
begin
  Result := TTgDto.Parse<ITgRichTextStrikethrough>(AJsonText, TgMakeRichTextStrikethrough);
end;

{ TTgRichTextSpoiler }

class function TTgRichTextSpoiler.Create(const AText: ITgRichText): ITgRichTextSpoiler;
var
  LObj: TTgRichTextSpoilerImpl;
begin
  LObj := TTgRichTextSpoilerImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'spoiler');
  LObj.SetObject('text', AText);
end;

class function TTgRichTextSpoiler.FromJson(const AJsonText: string): ITgRichTextSpoiler;
begin
  Result := TTgDto.Parse<ITgRichTextSpoiler>(AJsonText, TgMakeRichTextSpoiler);
end;

{ TTgRichTextDateTime }

class function TTgRichTextDateTime.Create(const AText: ITgRichText; AUnixTime: Integer;
  const ADateTimeFormat: string): ITgRichTextDateTime;
var
  LObj: TTgRichTextDateTimeImpl;
begin
  LObj := TTgRichTextDateTimeImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'date_time');
  LObj.SetObject('text', AText);
  LObj.SetInt('unix_time', AUnixTime);
  LObj.SetStr('date_time_format', ADateTimeFormat);
end;

class function TTgRichTextDateTime.FromJson(const AJsonText: string): ITgRichTextDateTime;
begin
  Result := TTgDto.Parse<ITgRichTextDateTime>(AJsonText, TgMakeRichTextDateTime);
end;

{ TTgRichTextTextMention }

class function TTgRichTextTextMention.Create(const AText: ITgRichText;
  const AUser: ITgUser): ITgRichTextTextMention;
var
  LObj: TTgRichTextTextMentionImpl;
begin
  LObj := TTgRichTextTextMentionImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'text_mention');
  LObj.SetObject('text', AText);
  LObj.SetObject('user', AUser);
end;

class function TTgRichTextTextMention.FromJson(const AJsonText: string): ITgRichTextTextMention;
begin
  Result := TTgDto.Parse<ITgRichTextTextMention>(AJsonText, TgMakeRichTextTextMention);
end;

{ TTgRichTextSubscript }

class function TTgRichTextSubscript.Create(const AText: ITgRichText): ITgRichTextSubscript;
var
  LObj: TTgRichTextSubscriptImpl;
begin
  LObj := TTgRichTextSubscriptImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'subscript');
  LObj.SetObject('text', AText);
end;

class function TTgRichTextSubscript.FromJson(const AJsonText: string): ITgRichTextSubscript;
begin
  Result := TTgDto.Parse<ITgRichTextSubscript>(AJsonText, TgMakeRichTextSubscript);
end;

{ TTgRichTextSuperscript }

class function TTgRichTextSuperscript.Create(const AText: ITgRichText): ITgRichTextSuperscript;
var
  LObj: TTgRichTextSuperscriptImpl;
begin
  LObj := TTgRichTextSuperscriptImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'superscript');
  LObj.SetObject('text', AText);
end;

class function TTgRichTextSuperscript.FromJson(const AJsonText: string): ITgRichTextSuperscript;
begin
  Result := TTgDto.Parse<ITgRichTextSuperscript>(AJsonText, TgMakeRichTextSuperscript);
end;

{ TTgRichTextMarked }

class function TTgRichTextMarked.Create(const AText: ITgRichText): ITgRichTextMarked;
var
  LObj: TTgRichTextMarkedImpl;
begin
  LObj := TTgRichTextMarkedImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'marked');
  LObj.SetObject('text', AText);
end;

class function TTgRichTextMarked.FromJson(const AJsonText: string): ITgRichTextMarked;
begin
  Result := TTgDto.Parse<ITgRichTextMarked>(AJsonText, TgMakeRichTextMarked);
end;

{ TTgRichTextCode }

class function TTgRichTextCode.Create(const AText: ITgRichText): ITgRichTextCode;
var
  LObj: TTgRichTextCodeImpl;
begin
  LObj := TTgRichTextCodeImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'code');
  LObj.SetObject('text', AText);
end;

class function TTgRichTextCode.FromJson(const AJsonText: string): ITgRichTextCode;
begin
  Result := TTgDto.Parse<ITgRichTextCode>(AJsonText, TgMakeRichTextCode);
end;

{ TTgRichTextCustomEmoji }

class function TTgRichTextCustomEmoji.Create(const ACustomEmojiId: string;
  const AAlternativeText: string): ITgRichTextCustomEmoji;
var
  LObj: TTgRichTextCustomEmojiImpl;
begin
  LObj := TTgRichTextCustomEmojiImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'custom_emoji');
  LObj.SetStr('custom_emoji_id', ACustomEmojiId);
  LObj.SetStr('alternative_text', AAlternativeText);
end;

class function TTgRichTextCustomEmoji.FromJson(const AJsonText: string): ITgRichTextCustomEmoji;
begin
  Result := TTgDto.Parse<ITgRichTextCustomEmoji>(AJsonText, TgMakeRichTextCustomEmoji);
end;

{ TTgRichTextMathematicalExpression }

class function TTgRichTextMathematicalExpression.Create(const AExpression: string): ITgRichTextMathematicalExpression;
var
  LObj: TTgRichTextMathematicalExpressionImpl;
begin
  LObj := TTgRichTextMathematicalExpressionImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'mathematical_expression');
  LObj.SetStr('expression', AExpression);
end;

class function TTgRichTextMathematicalExpression.FromJson(const AJsonText: string): ITgRichTextMathematicalExpression;
begin
  Result := TTgDto.Parse<ITgRichTextMathematicalExpression>(AJsonText, TgMakeRichTextMathematicalExpression);
end;

{ TTgRichTextUrl }

class function TTgRichTextUrl.Create(const AText: ITgRichText; const AUrl: string): ITgRichTextUrl;
var
  LObj: TTgRichTextUrlImpl;
begin
  LObj := TTgRichTextUrlImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'url');
  LObj.SetObject('text', AText);
  LObj.SetStr('url', AUrl);
end;

class function TTgRichTextUrl.FromJson(const AJsonText: string): ITgRichTextUrl;
begin
  Result := TTgDto.Parse<ITgRichTextUrl>(AJsonText, TgMakeRichTextUrl);
end;

{ TTgRichTextEmailAddress }

class function TTgRichTextEmailAddress.Create(const AText: ITgRichText;
  const AEmailAddress: string): ITgRichTextEmailAddress;
var
  LObj: TTgRichTextEmailAddressImpl;
begin
  LObj := TTgRichTextEmailAddressImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'email_address');
  LObj.SetObject('text', AText);
  LObj.SetStr('email_address', AEmailAddress);
end;

class function TTgRichTextEmailAddress.FromJson(const AJsonText: string): ITgRichTextEmailAddress;
begin
  Result := TTgDto.Parse<ITgRichTextEmailAddress>(AJsonText, TgMakeRichTextEmailAddress);
end;

{ TTgRichTextPhoneNumber }

class function TTgRichTextPhoneNumber.Create(const AText: ITgRichText;
  const APhoneNumber: string): ITgRichTextPhoneNumber;
var
  LObj: TTgRichTextPhoneNumberImpl;
begin
  LObj := TTgRichTextPhoneNumberImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'phone_number');
  LObj.SetObject('text', AText);
  LObj.SetStr('phone_number', APhoneNumber);
end;

class function TTgRichTextPhoneNumber.FromJson(const AJsonText: string): ITgRichTextPhoneNumber;
begin
  Result := TTgDto.Parse<ITgRichTextPhoneNumber>(AJsonText, TgMakeRichTextPhoneNumber);
end;

{ TTgRichTextBankCardNumber }

class function TTgRichTextBankCardNumber.Create(const AText: ITgRichText;
  const ABankCardNumber: string): ITgRichTextBankCardNumber;
var
  LObj: TTgRichTextBankCardNumberImpl;
begin
  LObj := TTgRichTextBankCardNumberImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'bank_card_number');
  LObj.SetObject('text', AText);
  LObj.SetStr('bank_card_number', ABankCardNumber);
end;

class function TTgRichTextBankCardNumber.FromJson(const AJsonText: string): ITgRichTextBankCardNumber;
begin
  Result := TTgDto.Parse<ITgRichTextBankCardNumber>(AJsonText, TgMakeRichTextBankCardNumber);
end;

{ TTgRichTextMention }

class function TTgRichTextMention.Create(const AText: ITgRichText;
  const AUsername: string): ITgRichTextMention;
var
  LObj: TTgRichTextMentionImpl;
begin
  LObj := TTgRichTextMentionImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'mention');
  LObj.SetObject('text', AText);
  LObj.SetStr('username', AUsername);
end;

class function TTgRichTextMention.FromJson(const AJsonText: string): ITgRichTextMention;
begin
  Result := TTgDto.Parse<ITgRichTextMention>(AJsonText, TgMakeRichTextMention);
end;

{ TTgRichTextHashtag }

class function TTgRichTextHashtag.Create(const AText: ITgRichText;
  const AHashtag: string): ITgRichTextHashtag;
var
  LObj: TTgRichTextHashtagImpl;
begin
  LObj := TTgRichTextHashtagImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'hashtag');
  LObj.SetObject('text', AText);
  LObj.SetStr('hashtag', AHashtag);
end;

class function TTgRichTextHashtag.FromJson(const AJsonText: string): ITgRichTextHashtag;
begin
  Result := TTgDto.Parse<ITgRichTextHashtag>(AJsonText, TgMakeRichTextHashtag);
end;

{ TTgRichTextCashtag }

class function TTgRichTextCashtag.Create(const AText: ITgRichText;
  const ACashtag: string): ITgRichTextCashtag;
var
  LObj: TTgRichTextCashtagImpl;
begin
  LObj := TTgRichTextCashtagImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'cashtag');
  LObj.SetObject('text', AText);
  LObj.SetStr('cashtag', ACashtag);
end;

class function TTgRichTextCashtag.FromJson(const AJsonText: string): ITgRichTextCashtag;
begin
  Result := TTgDto.Parse<ITgRichTextCashtag>(AJsonText, TgMakeRichTextCashtag);
end;

{ TTgRichTextBotCommand }

class function TTgRichTextBotCommand.Create(const AText: ITgRichText;
  const ABotCommand: string): ITgRichTextBotCommand;
var
  LObj: TTgRichTextBotCommandImpl;
begin
  LObj := TTgRichTextBotCommandImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'bot_command');
  LObj.SetObject('text', AText);
  LObj.SetStr('bot_command', ABotCommand);
end;

class function TTgRichTextBotCommand.FromJson(const AJsonText: string): ITgRichTextBotCommand;
begin
  Result := TTgDto.Parse<ITgRichTextBotCommand>(AJsonText, TgMakeRichTextBotCommand);
end;

{ TTgRichTextButton }

class function TTgRichTextButton.Create(const AButton: ITgRichMessageButton): ITgRichTextButton;
var
  LObj: TTgRichTextButtonImpl;
begin
  LObj := TTgRichTextButtonImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'button');
  LObj.SetObject('button', AButton);
end;

class function TTgRichTextButton.FromJson(const AJsonText: string): ITgRichTextButton;
begin
  Result := TTgDto.Parse<ITgRichTextButton>(AJsonText, TgMakeRichTextButton);
end;

{ TTgRichTextAnchor }

class function TTgRichTextAnchor.Create(const AName: string): ITgRichTextAnchor;
var
  LObj: TTgRichTextAnchorImpl;
begin
  LObj := TTgRichTextAnchorImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'anchor');
  LObj.SetStr('name', AName);
end;

class function TTgRichTextAnchor.FromJson(const AJsonText: string): ITgRichTextAnchor;
begin
  Result := TTgDto.Parse<ITgRichTextAnchor>(AJsonText, TgMakeRichTextAnchor);
end;

{ TTgRichTextAnchorLink }

class function TTgRichTextAnchorLink.Create(const AText: ITgRichText;
  const AAnchorName: string): ITgRichTextAnchorLink;
var
  LObj: TTgRichTextAnchorLinkImpl;
begin
  LObj := TTgRichTextAnchorLinkImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'anchor_link');
  LObj.SetObject('text', AText);
  LObj.SetStr('anchor_name', AAnchorName);
end;

class function TTgRichTextAnchorLink.FromJson(const AJsonText: string): ITgRichTextAnchorLink;
begin
  Result := TTgDto.Parse<ITgRichTextAnchorLink>(AJsonText, TgMakeRichTextAnchorLink);
end;

{ TTgRichTextReference }

class function TTgRichTextReference.Create(const AText: ITgRichText;
  const AName: string): ITgRichTextReference;
var
  LObj: TTgRichTextReferenceImpl;
begin
  LObj := TTgRichTextReferenceImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'reference');
  LObj.SetObject('text', AText);
  LObj.SetStr('name', AName);
end;

class function TTgRichTextReference.FromJson(const AJsonText: string): ITgRichTextReference;
begin
  Result := TTgDto.Parse<ITgRichTextReference>(AJsonText, TgMakeRichTextReference);
end;

{ TTgRichTextReferenceLink }

class function TTgRichTextReferenceLink.Create(const AText: ITgRichText;
  const AReferenceName: string): ITgRichTextReferenceLink;
var
  LObj: TTgRichTextReferenceLinkImpl;
begin
  LObj := TTgRichTextReferenceLinkImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'reference_link');
  LObj.SetObject('text', AText);
  LObj.SetStr('reference_name', AReferenceName);
end;

class function TTgRichTextReferenceLink.FromJson(const AJsonText: string): ITgRichTextReferenceLink;
begin
  Result := TTgDto.Parse<ITgRichTextReferenceLink>(AJsonText, TgMakeRichTextReferenceLink);
end;

{ TTgRichBlockCaption }

class function TTgRichBlockCaption.Create(const AText: ITgRichText): ITgRichBlockCaption;
var
  LObj: TTgRichBlockCaptionImpl;
begin
  LObj := TTgRichBlockCaptionImpl.CreateNew;
  Result := LObj;
  LObj.SetObject('text', AText);
end;

class function TTgRichBlockCaption.FromJson(const AJsonText: string): ITgRichBlockCaption;
begin
  Result := TTgDto.Parse<ITgRichBlockCaption>(AJsonText, TgMakeRichBlockCaption);
end;

{ TTgRichBlockTableCell }

class function TTgRichBlockTableCell.Create(const AAlign: string;
  const AValign: string): ITgRichBlockTableCell;
var
  LObj: TTgRichBlockTableCellImpl;
begin
  LObj := TTgRichBlockTableCellImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('align', AAlign);
  LObj.SetStr('valign', AValign);
end;

class function TTgRichBlockTableCell.FromJson(const AJsonText: string): ITgRichBlockTableCell;
begin
  Result := TTgDto.Parse<ITgRichBlockTableCell>(AJsonText, TgMakeRichBlockTableCell);
end;

{ TTgRichBlockListItem }

class function TTgRichBlockListItem.FromJson(const AJsonText: string): ITgRichBlockListItem;
begin
  Result := TTgDto.Parse<ITgRichBlockListItem>(AJsonText, TgMakeRichBlockListItem);
end;

{ TTgRichBlock }

class function TTgRichBlock.FromJson(const AJsonText: string): ITgRichBlock;
begin
  Result := TTgDto.Parse<ITgRichBlock>(AJsonText, TgMakeRichBlock);
end;

{ TTgRichBlockParagraph }

class function TTgRichBlockParagraph.FromJson(const AJsonText: string): ITgRichBlockParagraph;
begin
  Result := TTgDto.Parse<ITgRichBlockParagraph>(AJsonText, TgMakeRichBlockParagraph);
end;

{ TTgRichBlockSectionHeading }

class function TTgRichBlockSectionHeading.FromJson(const AJsonText: string): ITgRichBlockSectionHeading;
begin
  Result := TTgDto.Parse<ITgRichBlockSectionHeading>(AJsonText, TgMakeRichBlockSectionHeading);
end;

{ TTgRichBlockPreformatted }

class function TTgRichBlockPreformatted.FromJson(const AJsonText: string): ITgRichBlockPreformatted;
begin
  Result := TTgDto.Parse<ITgRichBlockPreformatted>(AJsonText, TgMakeRichBlockPreformatted);
end;

{ TTgRichBlockFooter }

class function TTgRichBlockFooter.FromJson(const AJsonText: string): ITgRichBlockFooter;
begin
  Result := TTgDto.Parse<ITgRichBlockFooter>(AJsonText, TgMakeRichBlockFooter);
end;

{ TTgRichBlockDivider }

class function TTgRichBlockDivider.FromJson(const AJsonText: string): ITgRichBlockDivider;
begin
  Result := TTgDto.Parse<ITgRichBlockDivider>(AJsonText, TgMakeRichBlockDivider);
end;

{ TTgRichBlockMathematicalExpression }

class function TTgRichBlockMathematicalExpression.FromJson(const AJsonText: string): ITgRichBlockMathematicalExpression;
begin
  Result := TTgDto.Parse<ITgRichBlockMathematicalExpression>(AJsonText, TgMakeRichBlockMathematicalExpression);
end;

{ TTgRichBlockAnchor }

class function TTgRichBlockAnchor.FromJson(const AJsonText: string): ITgRichBlockAnchor;
begin
  Result := TTgDto.Parse<ITgRichBlockAnchor>(AJsonText, TgMakeRichBlockAnchor);
end;

{ TTgRichBlockList }

class function TTgRichBlockList.FromJson(const AJsonText: string): ITgRichBlockList;
begin
  Result := TTgDto.Parse<ITgRichBlockList>(AJsonText, TgMakeRichBlockList);
end;

{ TTgRichBlockBlockQuotation }

class function TTgRichBlockBlockQuotation.FromJson(const AJsonText: string): ITgRichBlockBlockQuotation;
begin
  Result := TTgDto.Parse<ITgRichBlockBlockQuotation>(AJsonText, TgMakeRichBlockBlockQuotation);
end;

{ TTgRichBlockExpandableBlockQuotation }

class function TTgRichBlockExpandableBlockQuotation.FromJson(const AJsonText: string): ITgRichBlockExpandableBlockQuotation;
begin
  Result := TTgDto.Parse<ITgRichBlockExpandableBlockQuotation>(AJsonText, TgMakeRichBlockExpandableBlockQuotation);
end;

{ TTgRichBlockPullQuotation }

class function TTgRichBlockPullQuotation.FromJson(const AJsonText: string): ITgRichBlockPullQuotation;
begin
  Result := TTgDto.Parse<ITgRichBlockPullQuotation>(AJsonText, TgMakeRichBlockPullQuotation);
end;

{ TTgRichBlockCollage }

class function TTgRichBlockCollage.FromJson(const AJsonText: string): ITgRichBlockCollage;
begin
  Result := TTgDto.Parse<ITgRichBlockCollage>(AJsonText, TgMakeRichBlockCollage);
end;

{ TTgRichBlockSlideshow }

class function TTgRichBlockSlideshow.FromJson(const AJsonText: string): ITgRichBlockSlideshow;
begin
  Result := TTgDto.Parse<ITgRichBlockSlideshow>(AJsonText, TgMakeRichBlockSlideshow);
end;

{ TTgRichBlockTable }

class function TTgRichBlockTable.FromJson(const AJsonText: string): ITgRichBlockTable;
begin
  Result := TTgDto.Parse<ITgRichBlockTable>(AJsonText, TgMakeRichBlockTable);
end;

{ TTgRichBlockDetails }

class function TTgRichBlockDetails.FromJson(const AJsonText: string): ITgRichBlockDetails;
begin
  Result := TTgDto.Parse<ITgRichBlockDetails>(AJsonText, TgMakeRichBlockDetails);
end;

{ TTgRichBlockMap }

class function TTgRichBlockMap.FromJson(const AJsonText: string): ITgRichBlockMap;
begin
  Result := TTgDto.Parse<ITgRichBlockMap>(AJsonText, TgMakeRichBlockMap);
end;

{ TTgRichBlockButtons }

class function TTgRichBlockButtons.FromJson(const AJsonText: string): ITgRichBlockButtons;
begin
  Result := TTgDto.Parse<ITgRichBlockButtons>(AJsonText, TgMakeRichBlockButtons);
end;

{ TTgRichBlockAnimation }

class function TTgRichBlockAnimation.FromJson(const AJsonText: string): ITgRichBlockAnimation;
begin
  Result := TTgDto.Parse<ITgRichBlockAnimation>(AJsonText, TgMakeRichBlockAnimation);
end;

{ TTgRichBlockAudio }

class function TTgRichBlockAudio.FromJson(const AJsonText: string): ITgRichBlockAudio;
begin
  Result := TTgDto.Parse<ITgRichBlockAudio>(AJsonText, TgMakeRichBlockAudio);
end;

{ TTgRichBlockDocument }

class function TTgRichBlockDocument.FromJson(const AJsonText: string): ITgRichBlockDocument;
begin
  Result := TTgDto.Parse<ITgRichBlockDocument>(AJsonText, TgMakeRichBlockDocument);
end;

{ TTgRichBlockPhoto }

class function TTgRichBlockPhoto.FromJson(const AJsonText: string): ITgRichBlockPhoto;
begin
  Result := TTgDto.Parse<ITgRichBlockPhoto>(AJsonText, TgMakeRichBlockPhoto);
end;

{ TTgRichBlockVideo }

class function TTgRichBlockVideo.FromJson(const AJsonText: string): ITgRichBlockVideo;
begin
  Result := TTgDto.Parse<ITgRichBlockVideo>(AJsonText, TgMakeRichBlockVideo);
end;

{ TTgRichBlockVoiceNote }

class function TTgRichBlockVoiceNote.FromJson(const AJsonText: string): ITgRichBlockVoiceNote;
begin
  Result := TTgDto.Parse<ITgRichBlockVoiceNote>(AJsonText, TgMakeRichBlockVoiceNote);
end;

{ TTgRichBlockThinking }

class function TTgRichBlockThinking.FromJson(const AJsonText: string): ITgRichBlockThinking;
begin
  Result := TTgDto.Parse<ITgRichBlockThinking>(AJsonText, TgMakeRichBlockThinking);
end;

{ TTgInputRichBlockListItem }

class function TTgInputRichBlockListItem.Create(const ABlocks: array of TTgInputRichBlock): ITgInputRichBlockListItem;
var
  LObj: TTgInputRichBlockListItemImpl;
begin
  LObj := TTgInputRichBlockListItemImpl.CreateNew;
  Result := LObj;
  LObj.SetObjects('blocks', TTgInputRichBlock.Values(ABlocks));
end;

{ TTgInputRichBlockParagraph }

class function TTgInputRichBlockParagraph.Create(const AText: ITgRichText): ITgInputRichBlockParagraph;
var
  LObj: TTgInputRichBlockParagraphImpl;
begin
  LObj := TTgInputRichBlockParagraphImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'paragraph');
  LObj.SetObject('text', AText);
end;

{ TTgInputRichBlockSectionHeading }

class function TTgInputRichBlockSectionHeading.Create(const AText: ITgRichText;
  ASize: Integer): ITgInputRichBlockSectionHeading;
var
  LObj: TTgInputRichBlockSectionHeadingImpl;
begin
  LObj := TTgInputRichBlockSectionHeadingImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'heading');
  LObj.SetObject('text', AText);
  LObj.SetInt('size', ASize);
end;

{ TTgInputRichBlockPreformatted }

class function TTgInputRichBlockPreformatted.Create(const AText: ITgRichText): ITgInputRichBlockPreformatted;
var
  LObj: TTgInputRichBlockPreformattedImpl;
begin
  LObj := TTgInputRichBlockPreformattedImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'pre');
  LObj.SetObject('text', AText);
end;

{ TTgInputRichBlockFooter }

class function TTgInputRichBlockFooter.Create(const AText: ITgRichText): ITgInputRichBlockFooter;
var
  LObj: TTgInputRichBlockFooterImpl;
begin
  LObj := TTgInputRichBlockFooterImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'footer');
  LObj.SetObject('text', AText);
end;

{ TTgInputRichBlockDivider }

class function TTgInputRichBlockDivider.Create: ITgInputRichBlockDivider;
var
  LObj: TTgInputRichBlockDividerImpl;
begin
  LObj := TTgInputRichBlockDividerImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'divider');
end;

{ TTgInputRichBlockMathematicalExpression }

class function TTgInputRichBlockMathematicalExpression.Create(const AExpression: string): ITgInputRichBlockMathematicalExpression;
var
  LObj: TTgInputRichBlockMathematicalExpressionImpl;
begin
  LObj := TTgInputRichBlockMathematicalExpressionImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'mathematical_expression');
  LObj.SetStr('expression', AExpression);
end;

{ TTgInputRichBlockAnchor }

class function TTgInputRichBlockAnchor.Create(const AName: string): ITgInputRichBlockAnchor;
var
  LObj: TTgInputRichBlockAnchorImpl;
begin
  LObj := TTgInputRichBlockAnchorImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'anchor');
  LObj.SetStr('name', AName);
end;

{ TTgInputRichBlockList }

class function TTgInputRichBlockList.Create(const AItems: array of ITgInputRichBlockListItem): ITgInputRichBlockList;
var
  LObj: TTgInputRichBlockListImpl;
begin
  LObj := TTgInputRichBlockListImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'list');
  LObj.SetObjects('items', TTgDto.ToIntf<ITgInputRichBlockListItem>(AItems));
end;

{ TTgInputRichBlockBlockQuotation }

class function TTgInputRichBlockBlockQuotation.Create(const ABlocks: array of TTgInputRichBlock): ITgInputRichBlockBlockQuotation;
var
  LObj: TTgInputRichBlockBlockQuotationImpl;
begin
  LObj := TTgInputRichBlockBlockQuotationImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'blockquote');
  LObj.SetObjects('blocks', TTgInputRichBlock.Values(ABlocks));
end;

{ TTgInputRichBlockExpandableBlockQuotation }

class function TTgInputRichBlockExpandableBlockQuotation.Create(const AText: ITgRichText): ITgInputRichBlockExpandableBlockQuotation;
var
  LObj: TTgInputRichBlockExpandableBlockQuotationImpl;
begin
  LObj := TTgInputRichBlockExpandableBlockQuotationImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'expandable_blockquote');
  LObj.SetObject('text', AText);
end;

{ TTgInputRichBlockPullQuotation }

class function TTgInputRichBlockPullQuotation.Create(const AText: ITgRichText): ITgInputRichBlockPullQuotation;
var
  LObj: TTgInputRichBlockPullQuotationImpl;
begin
  LObj := TTgInputRichBlockPullQuotationImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'pullquote');
  LObj.SetObject('text', AText);
end;

{ TTgInputRichBlockCollage }

class function TTgInputRichBlockCollage.Create(const ABlocks: array of TTgInputRichBlock): ITgInputRichBlockCollage;
var
  LObj: TTgInputRichBlockCollageImpl;
begin
  LObj := TTgInputRichBlockCollageImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'collage');
  LObj.SetObjects('blocks', TTgInputRichBlock.Values(ABlocks));
end;

{ TTgInputRichBlockSlideshow }

class function TTgInputRichBlockSlideshow.Create(const ABlocks: array of TTgInputRichBlock): ITgInputRichBlockSlideshow;
var
  LObj: TTgInputRichBlockSlideshowImpl;
begin
  LObj := TTgInputRichBlockSlideshowImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'slideshow');
  LObj.SetObjects('blocks', TTgInputRichBlock.Values(ABlocks));
end;

{ TTgInputRichBlockTable }

class function TTgInputRichBlockTable.Create(const ACells: array of TArray<ITgRichBlockTableCell>): ITgInputRichBlockTable;
var
  LObj: TTgInputRichBlockTableImpl;
begin
  LObj := TTgInputRichBlockTableImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'table');
  LObj.SetObjects2('cells', TTgDto.ToIntf2<ITgRichBlockTableCell>(ACells));
end;

{ TTgInputRichBlockDetails }

class function TTgInputRichBlockDetails.Create(const ASummary: ITgRichText;
  const ABlocks: array of TTgInputRichBlock): ITgInputRichBlockDetails;
var
  LObj: TTgInputRichBlockDetailsImpl;
begin
  LObj := TTgInputRichBlockDetailsImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'details');
  LObj.SetObject('summary', ASummary);
  LObj.SetObjects('blocks', TTgInputRichBlock.Values(ABlocks));
end;

{ TTgInputRichBlockMap }

class function TTgInputRichBlockMap.Create(const ALocation: ITgLocation): ITgInputRichBlockMap;
var
  LObj: TTgInputRichBlockMapImpl;
begin
  LObj := TTgInputRichBlockMapImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'map');
  LObj.SetObject('location', ALocation);
end;

{ TTgInputRichBlockButtons }

class function TTgInputRichBlockButtons.Create(const AButtons: array of ITgRichMessageButton): ITgInputRichBlockButtons;
var
  LObj: TTgInputRichBlockButtonsImpl;
begin
  LObj := TTgInputRichBlockButtonsImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'buttons');
  LObj.SetObjects('buttons', TTgDto.ToIntf<ITgRichMessageButton>(AButtons));
end;

{ TTgInputRichBlockAnimation }

class function TTgInputRichBlockAnimation.Create(const AAnimation: ITgInputMediaAnimation): ITgInputRichBlockAnimation;
var
  LObj: TTgInputRichBlockAnimationImpl;
begin
  LObj := TTgInputRichBlockAnimationImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'animation');
  LObj.SetObject('animation', AAnimation);
end;

{ TTgInputRichBlockAudio }

class function TTgInputRichBlockAudio.Create(const AAudio: ITgInputMediaAudio): ITgInputRichBlockAudio;
var
  LObj: TTgInputRichBlockAudioImpl;
begin
  LObj := TTgInputRichBlockAudioImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'audio');
  LObj.SetObject('audio', AAudio);
end;

{ TTgInputRichBlockDocument }

class function TTgInputRichBlockDocument.Create(const ADocument: ITgInputMediaDocument): ITgInputRichBlockDocument;
var
  LObj: TTgInputRichBlockDocumentImpl;
begin
  LObj := TTgInputRichBlockDocumentImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'document');
  LObj.SetObject('document', ADocument);
end;

{ TTgInputRichBlockPhoto }

class function TTgInputRichBlockPhoto.Create(const APhoto: ITgInputMediaPhoto): ITgInputRichBlockPhoto;
var
  LObj: TTgInputRichBlockPhotoImpl;
begin
  LObj := TTgInputRichBlockPhotoImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'photo');
  LObj.SetObject('photo', APhoto);
end;

{ TTgInputRichBlockVideo }

class function TTgInputRichBlockVideo.Create(const AVideo: ITgInputMediaVideo): ITgInputRichBlockVideo;
var
  LObj: TTgInputRichBlockVideoImpl;
begin
  LObj := TTgInputRichBlockVideoImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'video');
  LObj.SetObject('video', AVideo);
end;

{ TTgInputRichBlockVoiceNote }

class function TTgInputRichBlockVoiceNote.Create(const AVoiceNote: ITgInputMediaVoiceNote): ITgInputRichBlockVoiceNote;
var
  LObj: TTgInputRichBlockVoiceNoteImpl;
begin
  LObj := TTgInputRichBlockVoiceNoteImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'voice_note');
  LObj.SetObject('voice_note', AVoiceNote);
end;

{ TTgInputRichBlockThinking }

class function TTgInputRichBlockThinking.Create(const AText: ITgRichText): ITgInputRichBlockThinking;
var
  LObj: TTgInputRichBlockThinkingImpl;
begin
  LObj := TTgInputRichBlockThinkingImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'thinking');
  LObj.SetObject('text', AText);
end;

{ TTgInlineQuery }

class function TTgInlineQuery.FromJson(const AJsonText: string): ITgInlineQuery;
begin
  Result := TTgDto.Parse<ITgInlineQuery>(AJsonText, TgMakeInlineQuery);
end;

{ TTgInlineQueryResultsButton }

class function TTgInlineQueryResultsButton.Create(const AText: string): ITgInlineQueryResultsButton;
var
  LObj: TTgInlineQueryResultsButtonImpl;
begin
  LObj := TTgInlineQueryResultsButtonImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('text', AText);
end;

{ TTgInlineQueryResultArticle }

class function TTgInlineQueryResultArticle.Create(const AId: string; const ATitle: string;
  const AInputMessageContent: TTgInputMessageContent): ITgInlineQueryResultArticle;
var
  LObj: TTgInlineQueryResultArticleImpl;
begin
  LObj := TTgInlineQueryResultArticleImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'article');
  LObj.SetStr('id', AId);
  LObj.SetStr('title', ATitle);
  LObj.SetObject('input_message_content', AInputMessageContent.Value);
end;

{ TTgInlineQueryResultPhoto }

class function TTgInlineQueryResultPhoto.Create(const AId: string; const APhotoUrl: string;
  const AThumbnailUrl: string): ITgInlineQueryResultPhoto;
var
  LObj: TTgInlineQueryResultPhotoImpl;
begin
  LObj := TTgInlineQueryResultPhotoImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'photo');
  LObj.SetStr('id', AId);
  LObj.SetStr('photo_url', APhotoUrl);
  LObj.SetStr('thumbnail_url', AThumbnailUrl);
end;

{ TTgInlineQueryResultGif }

class function TTgInlineQueryResultGif.Create(const AId: string; const AGifUrl: string;
  const AThumbnailUrl: string): ITgInlineQueryResultGif;
var
  LObj: TTgInlineQueryResultGifImpl;
begin
  LObj := TTgInlineQueryResultGifImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'gif');
  LObj.SetStr('id', AId);
  LObj.SetStr('gif_url', AGifUrl);
  LObj.SetStr('thumbnail_url', AThumbnailUrl);
end;

{ TTgInlineQueryResultMpeg4Gif }

class function TTgInlineQueryResultMpeg4Gif.Create(const AId: string; const AMpeg4Url: string;
  const AThumbnailUrl: string): ITgInlineQueryResultMpeg4Gif;
var
  LObj: TTgInlineQueryResultMpeg4GifImpl;
begin
  LObj := TTgInlineQueryResultMpeg4GifImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'mpeg4_gif');
  LObj.SetStr('id', AId);
  LObj.SetStr('mpeg4_url', AMpeg4Url);
  LObj.SetStr('thumbnail_url', AThumbnailUrl);
end;

{ TTgInlineQueryResultVideo }

class function TTgInlineQueryResultVideo.Create(const AId: string; const AVideoUrl: string;
  const AMimeType: string; const AThumbnailUrl: string;
  const ATitle: string): ITgInlineQueryResultVideo;
var
  LObj: TTgInlineQueryResultVideoImpl;
begin
  LObj := TTgInlineQueryResultVideoImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'video');
  LObj.SetStr('id', AId);
  LObj.SetStr('video_url', AVideoUrl);
  LObj.SetStr('mime_type', AMimeType);
  LObj.SetStr('thumbnail_url', AThumbnailUrl);
  LObj.SetStr('title', ATitle);
end;

{ TTgInlineQueryResultAudio }

class function TTgInlineQueryResultAudio.Create(const AId: string; const AAudioUrl: string;
  const ATitle: string): ITgInlineQueryResultAudio;
var
  LObj: TTgInlineQueryResultAudioImpl;
begin
  LObj := TTgInlineQueryResultAudioImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'audio');
  LObj.SetStr('id', AId);
  LObj.SetStr('audio_url', AAudioUrl);
  LObj.SetStr('title', ATitle);
end;

{ TTgInlineQueryResultVoice }

class function TTgInlineQueryResultVoice.Create(const AId: string; const AVoiceUrl: string;
  const ATitle: string): ITgInlineQueryResultVoice;
var
  LObj: TTgInlineQueryResultVoiceImpl;
begin
  LObj := TTgInlineQueryResultVoiceImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'voice');
  LObj.SetStr('id', AId);
  LObj.SetStr('voice_url', AVoiceUrl);
  LObj.SetStr('title', ATitle);
end;

{ TTgInlineQueryResultDocument }

class function TTgInlineQueryResultDocument.Create(const AId: string; const ATitle: string;
  const ADocumentUrl: string; const AMimeType: string): ITgInlineQueryResultDocument;
var
  LObj: TTgInlineQueryResultDocumentImpl;
begin
  LObj := TTgInlineQueryResultDocumentImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'document');
  LObj.SetStr('id', AId);
  LObj.SetStr('title', ATitle);
  LObj.SetStr('document_url', ADocumentUrl);
  LObj.SetStr('mime_type', AMimeType);
end;

{ TTgInlineQueryResultLocation }

class function TTgInlineQueryResultLocation.Create(const AId: string; ALatitude: Double;
  ALongitude: Double; const ATitle: string): ITgInlineQueryResultLocation;
var
  LObj: TTgInlineQueryResultLocationImpl;
begin
  LObj := TTgInlineQueryResultLocationImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'location');
  LObj.SetStr('id', AId);
  LObj.SetDouble('latitude', ALatitude);
  LObj.SetDouble('longitude', ALongitude);
  LObj.SetStr('title', ATitle);
end;

{ TTgInlineQueryResultVenue }

class function TTgInlineQueryResultVenue.Create(const AId: string; ALatitude: Double;
  ALongitude: Double; const ATitle: string; const AAddress: string): ITgInlineQueryResultVenue;
var
  LObj: TTgInlineQueryResultVenueImpl;
begin
  LObj := TTgInlineQueryResultVenueImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'venue');
  LObj.SetStr('id', AId);
  LObj.SetDouble('latitude', ALatitude);
  LObj.SetDouble('longitude', ALongitude);
  LObj.SetStr('title', ATitle);
  LObj.SetStr('address', AAddress);
end;

{ TTgInlineQueryResultContact }

class function TTgInlineQueryResultContact.Create(const AId: string; const APhoneNumber: string;
  const AFirstName: string): ITgInlineQueryResultContact;
var
  LObj: TTgInlineQueryResultContactImpl;
begin
  LObj := TTgInlineQueryResultContactImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'contact');
  LObj.SetStr('id', AId);
  LObj.SetStr('phone_number', APhoneNumber);
  LObj.SetStr('first_name', AFirstName);
end;

{ TTgInlineQueryResultGame }

class function TTgInlineQueryResultGame.Create(const AId: string;
  const AGameShortName: string): ITgInlineQueryResultGame;
var
  LObj: TTgInlineQueryResultGameImpl;
begin
  LObj := TTgInlineQueryResultGameImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'game');
  LObj.SetStr('id', AId);
  LObj.SetStr('game_short_name', AGameShortName);
end;

{ TTgInlineQueryResultCachedPhoto }

class function TTgInlineQueryResultCachedPhoto.Create(const AId: string;
  const APhotoFileId: string): ITgInlineQueryResultCachedPhoto;
var
  LObj: TTgInlineQueryResultCachedPhotoImpl;
begin
  LObj := TTgInlineQueryResultCachedPhotoImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'photo');
  LObj.SetStr('id', AId);
  LObj.SetStr('photo_file_id', APhotoFileId);
end;

{ TTgInlineQueryResultCachedGif }

class function TTgInlineQueryResultCachedGif.Create(const AId: string;
  const AGifFileId: string): ITgInlineQueryResultCachedGif;
var
  LObj: TTgInlineQueryResultCachedGifImpl;
begin
  LObj := TTgInlineQueryResultCachedGifImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'gif');
  LObj.SetStr('id', AId);
  LObj.SetStr('gif_file_id', AGifFileId);
end;

{ TTgInlineQueryResultCachedMpeg4Gif }

class function TTgInlineQueryResultCachedMpeg4Gif.Create(const AId: string;
  const AMpeg4FileId: string): ITgInlineQueryResultCachedMpeg4Gif;
var
  LObj: TTgInlineQueryResultCachedMpeg4GifImpl;
begin
  LObj := TTgInlineQueryResultCachedMpeg4GifImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'mpeg4_gif');
  LObj.SetStr('id', AId);
  LObj.SetStr('mpeg4_file_id', AMpeg4FileId);
end;

{ TTgInlineQueryResultCachedSticker }

class function TTgInlineQueryResultCachedSticker.Create(const AId: string;
  const AStickerFileId: string): ITgInlineQueryResultCachedSticker;
var
  LObj: TTgInlineQueryResultCachedStickerImpl;
begin
  LObj := TTgInlineQueryResultCachedStickerImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'sticker');
  LObj.SetStr('id', AId);
  LObj.SetStr('sticker_file_id', AStickerFileId);
end;

{ TTgInlineQueryResultCachedDocument }

class function TTgInlineQueryResultCachedDocument.Create(const AId: string; const ATitle: string;
  const ADocumentFileId: string): ITgInlineQueryResultCachedDocument;
var
  LObj: TTgInlineQueryResultCachedDocumentImpl;
begin
  LObj := TTgInlineQueryResultCachedDocumentImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'document');
  LObj.SetStr('id', AId);
  LObj.SetStr('title', ATitle);
  LObj.SetStr('document_file_id', ADocumentFileId);
end;

{ TTgInlineQueryResultCachedVideo }

class function TTgInlineQueryResultCachedVideo.Create(const AId: string; const AVideoFileId: string;
  const ATitle: string): ITgInlineQueryResultCachedVideo;
var
  LObj: TTgInlineQueryResultCachedVideoImpl;
begin
  LObj := TTgInlineQueryResultCachedVideoImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'video');
  LObj.SetStr('id', AId);
  LObj.SetStr('video_file_id', AVideoFileId);
  LObj.SetStr('title', ATitle);
end;

{ TTgInlineQueryResultCachedVoice }

class function TTgInlineQueryResultCachedVoice.Create(const AId: string; const AVoiceFileId: string;
  const ATitle: string): ITgInlineQueryResultCachedVoice;
var
  LObj: TTgInlineQueryResultCachedVoiceImpl;
begin
  LObj := TTgInlineQueryResultCachedVoiceImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'voice');
  LObj.SetStr('id', AId);
  LObj.SetStr('voice_file_id', AVoiceFileId);
  LObj.SetStr('title', ATitle);
end;

{ TTgInlineQueryResultCachedAudio }

class function TTgInlineQueryResultCachedAudio.Create(const AId: string;
  const AAudioFileId: string): ITgInlineQueryResultCachedAudio;
var
  LObj: TTgInlineQueryResultCachedAudioImpl;
begin
  LObj := TTgInlineQueryResultCachedAudioImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('type', 'audio');
  LObj.SetStr('id', AId);
  LObj.SetStr('audio_file_id', AAudioFileId);
end;

{ TTgInputTextMessageContent }

class function TTgInputTextMessageContent.Create(const AMessageText: string): ITgInputTextMessageContent;
var
  LObj: TTgInputTextMessageContentImpl;
begin
  LObj := TTgInputTextMessageContentImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('message_text', AMessageText);
end;

{ TTgInputRichMessageContent }

class function TTgInputRichMessageContent.Create(const ARichMessage: ITgInputRichMessage): ITgInputRichMessageContent;
var
  LObj: TTgInputRichMessageContentImpl;
begin
  LObj := TTgInputRichMessageContentImpl.CreateNew;
  Result := LObj;
  LObj.SetObject('rich_message', ARichMessage);
end;

{ TTgInputLocationMessageContent }

class function TTgInputLocationMessageContent.Create(ALatitude: Double;
  ALongitude: Double): ITgInputLocationMessageContent;
var
  LObj: TTgInputLocationMessageContentImpl;
begin
  LObj := TTgInputLocationMessageContentImpl.CreateNew;
  Result := LObj;
  LObj.SetDouble('latitude', ALatitude);
  LObj.SetDouble('longitude', ALongitude);
end;

{ TTgInputVenueMessageContent }

class function TTgInputVenueMessageContent.Create(ALatitude: Double; ALongitude: Double;
  const ATitle: string; const AAddress: string): ITgInputVenueMessageContent;
var
  LObj: TTgInputVenueMessageContentImpl;
begin
  LObj := TTgInputVenueMessageContentImpl.CreateNew;
  Result := LObj;
  LObj.SetDouble('latitude', ALatitude);
  LObj.SetDouble('longitude', ALongitude);
  LObj.SetStr('title', ATitle);
  LObj.SetStr('address', AAddress);
end;

{ TTgInputContactMessageContent }

class function TTgInputContactMessageContent.Create(const APhoneNumber: string;
  const AFirstName: string): ITgInputContactMessageContent;
var
  LObj: TTgInputContactMessageContentImpl;
begin
  LObj := TTgInputContactMessageContentImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('phone_number', APhoneNumber);
  LObj.SetStr('first_name', AFirstName);
end;

{ TTgInputInvoiceMessageContent }

class function TTgInputInvoiceMessageContent.Create(const ATitle: string;
  const ADescription: string; const APayload: string; const ACurrency: string;
  const APrices: array of ITgLabeledPrice): ITgInputInvoiceMessageContent;
var
  LObj: TTgInputInvoiceMessageContentImpl;
begin
  LObj := TTgInputInvoiceMessageContentImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('title', ATitle);
  LObj.SetStr('description', ADescription);
  LObj.SetStr('payload', APayload);
  LObj.SetStr('currency', ACurrency);
  LObj.SetObjects('prices', TTgDto.ToIntf<ITgLabeledPrice>(APrices));
end;

{ TTgChosenInlineResult }

class function TTgChosenInlineResult.FromJson(const AJsonText: string): ITgChosenInlineResult;
begin
  Result := TTgDto.Parse<ITgChosenInlineResult>(AJsonText, TgMakeChosenInlineResult);
end;

{ TTgLabeledPrice }

class function TTgLabeledPrice.Create(const ALabeledPriceLabel: string;
  AAmount: Integer): ITgLabeledPrice;
var
  LObj: TTgLabeledPriceImpl;
begin
  LObj := TTgLabeledPriceImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('label', ALabeledPriceLabel);
  LObj.SetInt('amount', AAmount);
end;

{ TTgInvoice }

class function TTgInvoice.FromJson(const AJsonText: string): ITgInvoice;
begin
  Result := TTgDto.Parse<ITgInvoice>(AJsonText, TgMakeInvoice);
end;

{ TTgShippingAddress }

class function TTgShippingAddress.FromJson(const AJsonText: string): ITgShippingAddress;
begin
  Result := TTgDto.Parse<ITgShippingAddress>(AJsonText, TgMakeShippingAddress);
end;

{ TTgOrderInfo }

class function TTgOrderInfo.FromJson(const AJsonText: string): ITgOrderInfo;
begin
  Result := TTgDto.Parse<ITgOrderInfo>(AJsonText, TgMakeOrderInfo);
end;

{ TTgShippingOption }

class function TTgShippingOption.Create(const AId: string; const ATitle: string;
  const APrices: array of ITgLabeledPrice): ITgShippingOption;
var
  LObj: TTgShippingOptionImpl;
begin
  LObj := TTgShippingOptionImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('id', AId);
  LObj.SetStr('title', ATitle);
  LObj.SetObjects('prices', TTgDto.ToIntf<ITgLabeledPrice>(APrices));
end;

{ TTgSuccessfulPayment }

class function TTgSuccessfulPayment.FromJson(const AJsonText: string): ITgSuccessfulPayment;
begin
  Result := TTgDto.Parse<ITgSuccessfulPayment>(AJsonText, TgMakeSuccessfulPayment);
end;

{ TTgRefundedPayment }

class function TTgRefundedPayment.FromJson(const AJsonText: string): ITgRefundedPayment;
begin
  Result := TTgDto.Parse<ITgRefundedPayment>(AJsonText, TgMakeRefundedPayment);
end;

{ TTgShippingQuery }

class function TTgShippingQuery.FromJson(const AJsonText: string): ITgShippingQuery;
begin
  Result := TTgDto.Parse<ITgShippingQuery>(AJsonText, TgMakeShippingQuery);
end;

{ TTgPreCheckoutQuery }

class function TTgPreCheckoutQuery.FromJson(const AJsonText: string): ITgPreCheckoutQuery;
begin
  Result := TTgDto.Parse<ITgPreCheckoutQuery>(AJsonText, TgMakePreCheckoutQuery);
end;

{ TTgPaidMediaPurchased }

class function TTgPaidMediaPurchased.FromJson(const AJsonText: string): ITgPaidMediaPurchased;
begin
  Result := TTgDto.Parse<ITgPaidMediaPurchased>(AJsonText, TgMakePaidMediaPurchased);
end;

{ TTgRevenueWithdrawalState }

class function TTgRevenueWithdrawalState.FromJson(const AJsonText: string): ITgRevenueWithdrawalState;
begin
  Result := TTgDto.Parse<ITgRevenueWithdrawalState>(AJsonText, TgMakeRevenueWithdrawalState);
end;

{ TTgRevenueWithdrawalStatePending }

class function TTgRevenueWithdrawalStatePending.FromJson(const AJsonText: string): ITgRevenueWithdrawalStatePending;
begin
  Result := TTgDto.Parse<ITgRevenueWithdrawalStatePending>(AJsonText, TgMakeRevenueWithdrawalStatePending);
end;

{ TTgRevenueWithdrawalStateSucceeded }

class function TTgRevenueWithdrawalStateSucceeded.FromJson(const AJsonText: string): ITgRevenueWithdrawalStateSucceeded;
begin
  Result := TTgDto.Parse<ITgRevenueWithdrawalStateSucceeded>(AJsonText, TgMakeRevenueWithdrawalStateSucceeded);
end;

{ TTgRevenueWithdrawalStateFailed }

class function TTgRevenueWithdrawalStateFailed.FromJson(const AJsonText: string): ITgRevenueWithdrawalStateFailed;
begin
  Result := TTgDto.Parse<ITgRevenueWithdrawalStateFailed>(AJsonText, TgMakeRevenueWithdrawalStateFailed);
end;

{ TTgAffiliateInfo }

class function TTgAffiliateInfo.FromJson(const AJsonText: string): ITgAffiliateInfo;
begin
  Result := TTgDto.Parse<ITgAffiliateInfo>(AJsonText, TgMakeAffiliateInfo);
end;

{ TTgTransactionPartner }

class function TTgTransactionPartner.FromJson(const AJsonText: string): ITgTransactionPartner;
begin
  Result := TTgDto.Parse<ITgTransactionPartner>(AJsonText, TgMakeTransactionPartner);
end;

{ TTgTransactionPartnerUser }

class function TTgTransactionPartnerUser.FromJson(const AJsonText: string): ITgTransactionPartnerUser;
begin
  Result := TTgDto.Parse<ITgTransactionPartnerUser>(AJsonText, TgMakeTransactionPartnerUser);
end;

{ TTgTransactionPartnerChat }

class function TTgTransactionPartnerChat.FromJson(const AJsonText: string): ITgTransactionPartnerChat;
begin
  Result := TTgDto.Parse<ITgTransactionPartnerChat>(AJsonText, TgMakeTransactionPartnerChat);
end;

{ TTgTransactionPartnerAffiliateProgram }

class function TTgTransactionPartnerAffiliateProgram.FromJson(const AJsonText: string): ITgTransactionPartnerAffiliateProgram;
begin
  Result := TTgDto.Parse<ITgTransactionPartnerAffiliateProgram>(AJsonText, TgMakeTransactionPartnerAffiliateProgram);
end;

{ TTgTransactionPartnerFragment }

class function TTgTransactionPartnerFragment.FromJson(const AJsonText: string): ITgTransactionPartnerFragment;
begin
  Result := TTgDto.Parse<ITgTransactionPartnerFragment>(AJsonText, TgMakeTransactionPartnerFragment);
end;

{ TTgTransactionPartnerTelegramAds }

class function TTgTransactionPartnerTelegramAds.FromJson(const AJsonText: string): ITgTransactionPartnerTelegramAds;
begin
  Result := TTgDto.Parse<ITgTransactionPartnerTelegramAds>(AJsonText, TgMakeTransactionPartnerTelegramAds);
end;

{ TTgTransactionPartnerTelegramApi }

class function TTgTransactionPartnerTelegramApi.FromJson(const AJsonText: string): ITgTransactionPartnerTelegramApi;
begin
  Result := TTgDto.Parse<ITgTransactionPartnerTelegramApi>(AJsonText, TgMakeTransactionPartnerTelegramApi);
end;

{ TTgTransactionPartnerOther }

class function TTgTransactionPartnerOther.FromJson(const AJsonText: string): ITgTransactionPartnerOther;
begin
  Result := TTgDto.Parse<ITgTransactionPartnerOther>(AJsonText, TgMakeTransactionPartnerOther);
end;

{ TTgStarTransaction }

class function TTgStarTransaction.FromJson(const AJsonText: string): ITgStarTransaction;
begin
  Result := TTgDto.Parse<ITgStarTransaction>(AJsonText, TgMakeStarTransaction);
end;

{ TTgStarTransactions }

class function TTgStarTransactions.FromJson(const AJsonText: string): ITgStarTransactions;
begin
  Result := TTgDto.Parse<ITgStarTransactions>(AJsonText, TgMakeStarTransactions);
end;

{ TTgPassportData }

class function TTgPassportData.FromJson(const AJsonText: string): ITgPassportData;
begin
  Result := TTgDto.Parse<ITgPassportData>(AJsonText, TgMakePassportData);
end;

{ TTgPassportFile }

class function TTgPassportFile.FromJson(const AJsonText: string): ITgPassportFile;
begin
  Result := TTgDto.Parse<ITgPassportFile>(AJsonText, TgMakePassportFile);
end;

{ TTgEncryptedPassportElement }

class function TTgEncryptedPassportElement.FromJson(const AJsonText: string): ITgEncryptedPassportElement;
begin
  Result := TTgDto.Parse<ITgEncryptedPassportElement>(AJsonText, TgMakeEncryptedPassportElement);
end;

{ TTgEncryptedCredentials }

class function TTgEncryptedCredentials.FromJson(const AJsonText: string): ITgEncryptedCredentials;
begin
  Result := TTgDto.Parse<ITgEncryptedCredentials>(AJsonText, TgMakeEncryptedCredentials);
end;

{ TTgPassportElementErrorDataField }

class function TTgPassportElementErrorDataField.Create(const APassportElementErrorDataFieldType: string; const AFieldName: string; const ADataHash: string; const AMessage: string): ITgPassportElementErrorDataField;
var
  LObj: TTgPassportElementErrorDataFieldImpl;
begin
  LObj := TTgPassportElementErrorDataFieldImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('source', 'data');
  LObj.SetStr('type', APassportElementErrorDataFieldType);
  LObj.SetStr('field_name', AFieldName);
  LObj.SetStr('data_hash', ADataHash);
  LObj.SetStr('message', AMessage);
end;

{ TTgPassportElementErrorFrontSide }

class function TTgPassportElementErrorFrontSide.Create(const APassportElementErrorFrontSideType: string; const AFileHash: string; const AMessage: string): ITgPassportElementErrorFrontSide;
var
  LObj: TTgPassportElementErrorFrontSideImpl;
begin
  LObj := TTgPassportElementErrorFrontSideImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('source', 'front_side');
  LObj.SetStr('type', APassportElementErrorFrontSideType);
  LObj.SetStr('file_hash', AFileHash);
  LObj.SetStr('message', AMessage);
end;

{ TTgPassportElementErrorReverseSide }

class function TTgPassportElementErrorReverseSide.Create(const APassportElementErrorReverseSideType: string; const AFileHash: string; const AMessage: string): ITgPassportElementErrorReverseSide;
var
  LObj: TTgPassportElementErrorReverseSideImpl;
begin
  LObj := TTgPassportElementErrorReverseSideImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('source', 'reverse_side');
  LObj.SetStr('type', APassportElementErrorReverseSideType);
  LObj.SetStr('file_hash', AFileHash);
  LObj.SetStr('message', AMessage);
end;

{ TTgPassportElementErrorSelfie }

class function TTgPassportElementErrorSelfie.Create(const APassportElementErrorSelfieType: string;
  const AFileHash: string; const AMessage: string): ITgPassportElementErrorSelfie;
var
  LObj: TTgPassportElementErrorSelfieImpl;
begin
  LObj := TTgPassportElementErrorSelfieImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('source', 'selfie');
  LObj.SetStr('type', APassportElementErrorSelfieType);
  LObj.SetStr('file_hash', AFileHash);
  LObj.SetStr('message', AMessage);
end;

{ TTgPassportElementErrorFile }

class function TTgPassportElementErrorFile.Create(const APassportElementErrorFileType: string;
  const AFileHash: string; const AMessage: string): ITgPassportElementErrorFile;
var
  LObj: TTgPassportElementErrorFileImpl;
begin
  LObj := TTgPassportElementErrorFileImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('source', 'file');
  LObj.SetStr('type', APassportElementErrorFileType);
  LObj.SetStr('file_hash', AFileHash);
  LObj.SetStr('message', AMessage);
end;

{ TTgPassportElementErrorFiles }

class function TTgPassportElementErrorFiles.Create(const APassportElementErrorFilesType: string;
  const AFileHashes: TArray<string>; const AMessage: string): ITgPassportElementErrorFiles;
var
  LObj: TTgPassportElementErrorFilesImpl;
begin
  LObj := TTgPassportElementErrorFilesImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('source', 'files');
  LObj.SetStr('type', APassportElementErrorFilesType);
  LObj.SetStrings('file_hashes', AFileHashes);
  LObj.SetStr('message', AMessage);
end;

{ TTgPassportElementErrorTranslationFile }

class function TTgPassportElementErrorTranslationFile.Create(const APassportElementErrorTranslationFileType: string; const AFileHash: string; const AMessage: string): ITgPassportElementErrorTranslationFile;
var
  LObj: TTgPassportElementErrorTranslationFileImpl;
begin
  LObj := TTgPassportElementErrorTranslationFileImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('source', 'translation_file');
  LObj.SetStr('type', APassportElementErrorTranslationFileType);
  LObj.SetStr('file_hash', AFileHash);
  LObj.SetStr('message', AMessage);
end;

{ TTgPassportElementErrorTranslationFiles }

class function TTgPassportElementErrorTranslationFiles.Create(const APassportElementErrorTranslationFilesType: string; const AFileHashes: TArray<string>; const AMessage: string): ITgPassportElementErrorTranslationFiles;
var
  LObj: TTgPassportElementErrorTranslationFilesImpl;
begin
  LObj := TTgPassportElementErrorTranslationFilesImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('source', 'translation_files');
  LObj.SetStr('type', APassportElementErrorTranslationFilesType);
  LObj.SetStrings('file_hashes', AFileHashes);
  LObj.SetStr('message', AMessage);
end;

{ TTgPassportElementErrorUnspecified }

class function TTgPassportElementErrorUnspecified.Create(const APassportElementErrorUnspecifiedType: string; const AElementHash: string; const AMessage: string): ITgPassportElementErrorUnspecified;
var
  LObj: TTgPassportElementErrorUnspecifiedImpl;
begin
  LObj := TTgPassportElementErrorUnspecifiedImpl.CreateNew;
  Result := LObj;
  LObj.SetStr('source', 'unspecified');
  LObj.SetStr('type', APassportElementErrorUnspecifiedType);
  LObj.SetStr('element_hash', AElementHash);
  LObj.SetStr('message', AMessage);
end;

{ TTgGame }

class function TTgGame.FromJson(const AJsonText: string): ITgGame;
begin
  Result := TTgDto.Parse<ITgGame>(AJsonText, TgMakeGame);
end;

{ TTgCallbackGame }

class function TTgCallbackGame.Create: ITgCallbackGame;
begin
  Result := TTgCallbackGameImpl.CreateNew;
end;

class function TTgCallbackGame.FromJson(const AJsonText: string): ITgCallbackGame;
begin
  Result := TTgDto.Parse<ITgCallbackGame>(AJsonText, TgMakeCallbackGame);
end;

{ TTgGameHighScore }

class function TTgGameHighScore.FromJson(const AJsonText: string): ITgGameHighScore;
begin
  Result := TTgDto.Parse<ITgGameHighScore>(AJsonText, TgMakeGameHighScore);
end;

