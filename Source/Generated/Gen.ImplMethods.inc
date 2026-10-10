// Gen.ImplMethods.inc — записи опций и методы TTgApi (implementation).
// Сгенерировано TgBotGen по Telegram Bot API 10.3 (August 24, 2026). Не редактируйте вручную.

{ TTgGetUpdatesOptions }

procedure TTgGetUpdatesOptions.ApplyTo(AParams: TTgParams);
begin
  if Offset.HasValue then
    AParams.Add('offset', Offset.Value);
  if Limit.HasValue then
    AParams.Add('limit', Limit.Value);
  if Timeout.HasValue then
    AParams.Add('timeout', Timeout.Value);
  if AllowedUpdates.HasValue then
    AParams.AddStrings('allowed_updates', AllowedUpdates.Value);
end;

{ TTgSetWebhookOptions }

procedure TTgSetWebhookOptions.ApplyTo(AParams: TTgParams);
begin
  if not Certificate.IsEmpty then
    AParams.AddFile('certificate', Certificate);
  if IpAddress.HasValue then
    AParams.Add('ip_address', IpAddress.Value);
  if MaxConnections.HasValue then
    AParams.Add('max_connections', MaxConnections.Value);
  if AllowedUpdates.HasValue then
    AParams.AddStrings('allowed_updates', AllowedUpdates.Value);
  if DropPendingUpdates.HasValue then
    AParams.Add('drop_pending_updates', DropPendingUpdates.Value);
  if SecretToken.HasValue then
    AParams.Add('secret_token', SecretToken.Value);
end;

{ TTgDeleteWebhookOptions }

procedure TTgDeleteWebhookOptions.ApplyTo(AParams: TTgParams);
begin
  if DropPendingUpdates.HasValue then
    AParams.Add('drop_pending_updates', DropPendingUpdates.Value);
end;

{ TTgSendMessageOptions }

procedure TTgSendMessageOptions.ApplyTo(AParams: TTgParams);
begin
  if BusinessConnectionId.HasValue then
    AParams.Add('business_connection_id', BusinessConnectionId.Value);
  if MessageThreadId.HasValue then
    AParams.Add('message_thread_id', MessageThreadId.Value);
  if DirectMessagesTopicId.HasValue then
    AParams.Add('direct_messages_topic_id', DirectMessagesTopicId.Value);
  if System.Assigned(EphemeralMessageParameters) then
    AParams.AddJson('ephemeral_message_parameters', TTgDto.Serialize(EphemeralMessageParameters, AParams));
  if ParseMode.HasValue then
    AParams.Add('parse_mode', ParseMode.Value);
  if Entities.HasValue then
    AParams.AddJson('entities', TTgDto.SerializeArray(TTgDto.ToIntf<ITgMessageEntity>(Entities.Value), AParams, 'entities'));
  if System.Assigned(LinkPreviewOptions) then
    AParams.AddJson('link_preview_options', TTgDto.Serialize(LinkPreviewOptions, AParams));
  if DisableNotification.HasValue then
    AParams.Add('disable_notification', DisableNotification.Value);
  if ProtectContent.HasValue then
    AParams.Add('protect_content', ProtectContent.Value);
  if AllowPaidBroadcast.HasValue then
    AParams.Add('allow_paid_broadcast', AllowPaidBroadcast.Value);
  if MessageEffectId.HasValue then
    AParams.Add('message_effect_id', MessageEffectId.Value);
  if System.Assigned(SuggestedPostParameters) then
    AParams.AddJson('suggested_post_parameters', TTgDto.Serialize(SuggestedPostParameters, AParams));
  if System.Assigned(ReplyParameters) then
    AParams.AddJson('reply_parameters', TTgDto.Serialize(ReplyParameters, AParams));
  if not ReplyMarkup.IsEmpty then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup.Value, AParams));
end;

{ TTgForwardMessageOptions }

procedure TTgForwardMessageOptions.ApplyTo(AParams: TTgParams);
begin
  if MessageThreadId.HasValue then
    AParams.Add('message_thread_id', MessageThreadId.Value);
  if DirectMessagesTopicId.HasValue then
    AParams.Add('direct_messages_topic_id', DirectMessagesTopicId.Value);
  if VideoStartTimestamp.HasValue then
    AParams.Add('video_start_timestamp', VideoStartTimestamp.Value);
  if DisableNotification.HasValue then
    AParams.Add('disable_notification', DisableNotification.Value);
  if ProtectContent.HasValue then
    AParams.Add('protect_content', ProtectContent.Value);
  if MessageEffectId.HasValue then
    AParams.Add('message_effect_id', MessageEffectId.Value);
  if System.Assigned(SuggestedPostParameters) then
    AParams.AddJson('suggested_post_parameters', TTgDto.Serialize(SuggestedPostParameters, AParams));
end;

{ TTgForwardMessagesOptions }

procedure TTgForwardMessagesOptions.ApplyTo(AParams: TTgParams);
begin
  if MessageThreadId.HasValue then
    AParams.Add('message_thread_id', MessageThreadId.Value);
  if DirectMessagesTopicId.HasValue then
    AParams.Add('direct_messages_topic_id', DirectMessagesTopicId.Value);
  if DisableNotification.HasValue then
    AParams.Add('disable_notification', DisableNotification.Value);
  if ProtectContent.HasValue then
    AParams.Add('protect_content', ProtectContent.Value);
end;

{ TTgCopyMessageOptions }

procedure TTgCopyMessageOptions.ApplyTo(AParams: TTgParams);
begin
  if MessageThreadId.HasValue then
    AParams.Add('message_thread_id', MessageThreadId.Value);
  if DirectMessagesTopicId.HasValue then
    AParams.Add('direct_messages_topic_id', DirectMessagesTopicId.Value);
  if VideoStartTimestamp.HasValue then
    AParams.Add('video_start_timestamp', VideoStartTimestamp.Value);
  if Caption.HasValue then
    AParams.Add('caption', Caption.Value);
  if ParseMode.HasValue then
    AParams.Add('parse_mode', ParseMode.Value);
  if CaptionEntities.HasValue then
    AParams.AddJson('caption_entities', TTgDto.SerializeArray(TTgDto.ToIntf<ITgMessageEntity>(CaptionEntities.Value), AParams, 'caption_entities'));
  if ShowCaptionAboveMedia.HasValue then
    AParams.Add('show_caption_above_media', ShowCaptionAboveMedia.Value);
  if DisableNotification.HasValue then
    AParams.Add('disable_notification', DisableNotification.Value);
  if ProtectContent.HasValue then
    AParams.Add('protect_content', ProtectContent.Value);
  if AllowPaidBroadcast.HasValue then
    AParams.Add('allow_paid_broadcast', AllowPaidBroadcast.Value);
  if MessageEffectId.HasValue then
    AParams.Add('message_effect_id', MessageEffectId.Value);
  if System.Assigned(SuggestedPostParameters) then
    AParams.AddJson('suggested_post_parameters', TTgDto.Serialize(SuggestedPostParameters, AParams));
  if System.Assigned(ReplyParameters) then
    AParams.AddJson('reply_parameters', TTgDto.Serialize(ReplyParameters, AParams));
  if not ReplyMarkup.IsEmpty then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup.Value, AParams));
end;

{ TTgCopyMessagesOptions }

procedure TTgCopyMessagesOptions.ApplyTo(AParams: TTgParams);
begin
  if MessageThreadId.HasValue then
    AParams.Add('message_thread_id', MessageThreadId.Value);
  if DirectMessagesTopicId.HasValue then
    AParams.Add('direct_messages_topic_id', DirectMessagesTopicId.Value);
  if DisableNotification.HasValue then
    AParams.Add('disable_notification', DisableNotification.Value);
  if ProtectContent.HasValue then
    AParams.Add('protect_content', ProtectContent.Value);
  if RemoveCaption.HasValue then
    AParams.Add('remove_caption', RemoveCaption.Value);
end;

{ TTgSendPhotoOptions }

procedure TTgSendPhotoOptions.ApplyTo(AParams: TTgParams);
begin
  if BusinessConnectionId.HasValue then
    AParams.Add('business_connection_id', BusinessConnectionId.Value);
  if MessageThreadId.HasValue then
    AParams.Add('message_thread_id', MessageThreadId.Value);
  if DirectMessagesTopicId.HasValue then
    AParams.Add('direct_messages_topic_id', DirectMessagesTopicId.Value);
  if System.Assigned(EphemeralMessageParameters) then
    AParams.AddJson('ephemeral_message_parameters', TTgDto.Serialize(EphemeralMessageParameters, AParams));
  if Caption.HasValue then
    AParams.Add('caption', Caption.Value);
  if ParseMode.HasValue then
    AParams.Add('parse_mode', ParseMode.Value);
  if CaptionEntities.HasValue then
    AParams.AddJson('caption_entities', TTgDto.SerializeArray(TTgDto.ToIntf<ITgMessageEntity>(CaptionEntities.Value), AParams, 'caption_entities'));
  if ShowCaptionAboveMedia.HasValue then
    AParams.Add('show_caption_above_media', ShowCaptionAboveMedia.Value);
  if HasSpoiler.HasValue then
    AParams.Add('has_spoiler', HasSpoiler.Value);
  if DisableNotification.HasValue then
    AParams.Add('disable_notification', DisableNotification.Value);
  if ProtectContent.HasValue then
    AParams.Add('protect_content', ProtectContent.Value);
  if AllowPaidBroadcast.HasValue then
    AParams.Add('allow_paid_broadcast', AllowPaidBroadcast.Value);
  if MessageEffectId.HasValue then
    AParams.Add('message_effect_id', MessageEffectId.Value);
  if System.Assigned(SuggestedPostParameters) then
    AParams.AddJson('suggested_post_parameters', TTgDto.Serialize(SuggestedPostParameters, AParams));
  if System.Assigned(ReplyParameters) then
    AParams.AddJson('reply_parameters', TTgDto.Serialize(ReplyParameters, AParams));
  if not ReplyMarkup.IsEmpty then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup.Value, AParams));
end;

{ TTgSendLivePhotoOptions }

procedure TTgSendLivePhotoOptions.ApplyTo(AParams: TTgParams);
begin
  if BusinessConnectionId.HasValue then
    AParams.Add('business_connection_id', BusinessConnectionId.Value);
  if MessageThreadId.HasValue then
    AParams.Add('message_thread_id', MessageThreadId.Value);
  if DirectMessagesTopicId.HasValue then
    AParams.Add('direct_messages_topic_id', DirectMessagesTopicId.Value);
  if System.Assigned(EphemeralMessageParameters) then
    AParams.AddJson('ephemeral_message_parameters', TTgDto.Serialize(EphemeralMessageParameters, AParams));
  if Caption.HasValue then
    AParams.Add('caption', Caption.Value);
  if ParseMode.HasValue then
    AParams.Add('parse_mode', ParseMode.Value);
  if CaptionEntities.HasValue then
    AParams.AddJson('caption_entities', TTgDto.SerializeArray(TTgDto.ToIntf<ITgMessageEntity>(CaptionEntities.Value), AParams, 'caption_entities'));
  if ShowCaptionAboveMedia.HasValue then
    AParams.Add('show_caption_above_media', ShowCaptionAboveMedia.Value);
  if HasSpoiler.HasValue then
    AParams.Add('has_spoiler', HasSpoiler.Value);
  if DisableNotification.HasValue then
    AParams.Add('disable_notification', DisableNotification.Value);
  if ProtectContent.HasValue then
    AParams.Add('protect_content', ProtectContent.Value);
  if AllowPaidBroadcast.HasValue then
    AParams.Add('allow_paid_broadcast', AllowPaidBroadcast.Value);
  if MessageEffectId.HasValue then
    AParams.Add('message_effect_id', MessageEffectId.Value);
  if System.Assigned(SuggestedPostParameters) then
    AParams.AddJson('suggested_post_parameters', TTgDto.Serialize(SuggestedPostParameters, AParams));
  if System.Assigned(ReplyParameters) then
    AParams.AddJson('reply_parameters', TTgDto.Serialize(ReplyParameters, AParams));
  if not ReplyMarkup.IsEmpty then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup.Value, AParams));
end;

{ TTgSendAudioOptions }

procedure TTgSendAudioOptions.ApplyTo(AParams: TTgParams);
begin
  if BusinessConnectionId.HasValue then
    AParams.Add('business_connection_id', BusinessConnectionId.Value);
  if MessageThreadId.HasValue then
    AParams.Add('message_thread_id', MessageThreadId.Value);
  if DirectMessagesTopicId.HasValue then
    AParams.Add('direct_messages_topic_id', DirectMessagesTopicId.Value);
  if System.Assigned(EphemeralMessageParameters) then
    AParams.AddJson('ephemeral_message_parameters', TTgDto.Serialize(EphemeralMessageParameters, AParams));
  if Caption.HasValue then
    AParams.Add('caption', Caption.Value);
  if ParseMode.HasValue then
    AParams.Add('parse_mode', ParseMode.Value);
  if CaptionEntities.HasValue then
    AParams.AddJson('caption_entities', TTgDto.SerializeArray(TTgDto.ToIntf<ITgMessageEntity>(CaptionEntities.Value), AParams, 'caption_entities'));
  if Duration.HasValue then
    AParams.Add('duration', Duration.Value);
  if Performer.HasValue then
    AParams.Add('performer', Performer.Value);
  if Title.HasValue then
    AParams.Add('title', Title.Value);
  if not Thumbnail.IsEmpty then
    AParams.AddFile('thumbnail', Thumbnail);
  if DisableNotification.HasValue then
    AParams.Add('disable_notification', DisableNotification.Value);
  if ProtectContent.HasValue then
    AParams.Add('protect_content', ProtectContent.Value);
  if AllowPaidBroadcast.HasValue then
    AParams.Add('allow_paid_broadcast', AllowPaidBroadcast.Value);
  if MessageEffectId.HasValue then
    AParams.Add('message_effect_id', MessageEffectId.Value);
  if System.Assigned(SuggestedPostParameters) then
    AParams.AddJson('suggested_post_parameters', TTgDto.Serialize(SuggestedPostParameters, AParams));
  if System.Assigned(ReplyParameters) then
    AParams.AddJson('reply_parameters', TTgDto.Serialize(ReplyParameters, AParams));
  if not ReplyMarkup.IsEmpty then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup.Value, AParams));
end;

{ TTgSendDocumentOptions }

procedure TTgSendDocumentOptions.ApplyTo(AParams: TTgParams);
begin
  if BusinessConnectionId.HasValue then
    AParams.Add('business_connection_id', BusinessConnectionId.Value);
  if MessageThreadId.HasValue then
    AParams.Add('message_thread_id', MessageThreadId.Value);
  if DirectMessagesTopicId.HasValue then
    AParams.Add('direct_messages_topic_id', DirectMessagesTopicId.Value);
  if System.Assigned(EphemeralMessageParameters) then
    AParams.AddJson('ephemeral_message_parameters', TTgDto.Serialize(EphemeralMessageParameters, AParams));
  if not Thumbnail.IsEmpty then
    AParams.AddFile('thumbnail', Thumbnail);
  if Caption.HasValue then
    AParams.Add('caption', Caption.Value);
  if ParseMode.HasValue then
    AParams.Add('parse_mode', ParseMode.Value);
  if CaptionEntities.HasValue then
    AParams.AddJson('caption_entities', TTgDto.SerializeArray(TTgDto.ToIntf<ITgMessageEntity>(CaptionEntities.Value), AParams, 'caption_entities'));
  if DisableContentTypeDetection.HasValue then
    AParams.Add('disable_content_type_detection', DisableContentTypeDetection.Value);
  if DisableNotification.HasValue then
    AParams.Add('disable_notification', DisableNotification.Value);
  if ProtectContent.HasValue then
    AParams.Add('protect_content', ProtectContent.Value);
  if AllowPaidBroadcast.HasValue then
    AParams.Add('allow_paid_broadcast', AllowPaidBroadcast.Value);
  if MessageEffectId.HasValue then
    AParams.Add('message_effect_id', MessageEffectId.Value);
  if System.Assigned(SuggestedPostParameters) then
    AParams.AddJson('suggested_post_parameters', TTgDto.Serialize(SuggestedPostParameters, AParams));
  if System.Assigned(ReplyParameters) then
    AParams.AddJson('reply_parameters', TTgDto.Serialize(ReplyParameters, AParams));
  if not ReplyMarkup.IsEmpty then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup.Value, AParams));
end;

{ TTgSendVideoOptions }

procedure TTgSendVideoOptions.ApplyTo(AParams: TTgParams);
begin
  if BusinessConnectionId.HasValue then
    AParams.Add('business_connection_id', BusinessConnectionId.Value);
  if MessageThreadId.HasValue then
    AParams.Add('message_thread_id', MessageThreadId.Value);
  if DirectMessagesTopicId.HasValue then
    AParams.Add('direct_messages_topic_id', DirectMessagesTopicId.Value);
  if System.Assigned(EphemeralMessageParameters) then
    AParams.AddJson('ephemeral_message_parameters', TTgDto.Serialize(EphemeralMessageParameters, AParams));
  if Duration.HasValue then
    AParams.Add('duration', Duration.Value);
  if Width.HasValue then
    AParams.Add('width', Width.Value);
  if Height.HasValue then
    AParams.Add('height', Height.Value);
  if not Thumbnail.IsEmpty then
    AParams.AddFile('thumbnail', Thumbnail);
  if not Cover.IsEmpty then
    AParams.AddFile('cover', Cover);
  if StartTimestamp.HasValue then
    AParams.Add('start_timestamp', StartTimestamp.Value);
  if Caption.HasValue then
    AParams.Add('caption', Caption.Value);
  if ParseMode.HasValue then
    AParams.Add('parse_mode', ParseMode.Value);
  if CaptionEntities.HasValue then
    AParams.AddJson('caption_entities', TTgDto.SerializeArray(TTgDto.ToIntf<ITgMessageEntity>(CaptionEntities.Value), AParams, 'caption_entities'));
  if ShowCaptionAboveMedia.HasValue then
    AParams.Add('show_caption_above_media', ShowCaptionAboveMedia.Value);
  if HasSpoiler.HasValue then
    AParams.Add('has_spoiler', HasSpoiler.Value);
  if SupportsStreaming.HasValue then
    AParams.Add('supports_streaming', SupportsStreaming.Value);
  if DisableNotification.HasValue then
    AParams.Add('disable_notification', DisableNotification.Value);
  if ProtectContent.HasValue then
    AParams.Add('protect_content', ProtectContent.Value);
  if AllowPaidBroadcast.HasValue then
    AParams.Add('allow_paid_broadcast', AllowPaidBroadcast.Value);
  if MessageEffectId.HasValue then
    AParams.Add('message_effect_id', MessageEffectId.Value);
  if System.Assigned(SuggestedPostParameters) then
    AParams.AddJson('suggested_post_parameters', TTgDto.Serialize(SuggestedPostParameters, AParams));
  if System.Assigned(ReplyParameters) then
    AParams.AddJson('reply_parameters', TTgDto.Serialize(ReplyParameters, AParams));
  if not ReplyMarkup.IsEmpty then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup.Value, AParams));
end;

{ TTgSendAnimationOptions }

procedure TTgSendAnimationOptions.ApplyTo(AParams: TTgParams);
begin
  if BusinessConnectionId.HasValue then
    AParams.Add('business_connection_id', BusinessConnectionId.Value);
  if MessageThreadId.HasValue then
    AParams.Add('message_thread_id', MessageThreadId.Value);
  if DirectMessagesTopicId.HasValue then
    AParams.Add('direct_messages_topic_id', DirectMessagesTopicId.Value);
  if System.Assigned(EphemeralMessageParameters) then
    AParams.AddJson('ephemeral_message_parameters', TTgDto.Serialize(EphemeralMessageParameters, AParams));
  if Duration.HasValue then
    AParams.Add('duration', Duration.Value);
  if Width.HasValue then
    AParams.Add('width', Width.Value);
  if Height.HasValue then
    AParams.Add('height', Height.Value);
  if not Thumbnail.IsEmpty then
    AParams.AddFile('thumbnail', Thumbnail);
  if Caption.HasValue then
    AParams.Add('caption', Caption.Value);
  if ParseMode.HasValue then
    AParams.Add('parse_mode', ParseMode.Value);
  if CaptionEntities.HasValue then
    AParams.AddJson('caption_entities', TTgDto.SerializeArray(TTgDto.ToIntf<ITgMessageEntity>(CaptionEntities.Value), AParams, 'caption_entities'));
  if ShowCaptionAboveMedia.HasValue then
    AParams.Add('show_caption_above_media', ShowCaptionAboveMedia.Value);
  if HasSpoiler.HasValue then
    AParams.Add('has_spoiler', HasSpoiler.Value);
  if DisableNotification.HasValue then
    AParams.Add('disable_notification', DisableNotification.Value);
  if ProtectContent.HasValue then
    AParams.Add('protect_content', ProtectContent.Value);
  if AllowPaidBroadcast.HasValue then
    AParams.Add('allow_paid_broadcast', AllowPaidBroadcast.Value);
  if MessageEffectId.HasValue then
    AParams.Add('message_effect_id', MessageEffectId.Value);
  if System.Assigned(SuggestedPostParameters) then
    AParams.AddJson('suggested_post_parameters', TTgDto.Serialize(SuggestedPostParameters, AParams));
  if System.Assigned(ReplyParameters) then
    AParams.AddJson('reply_parameters', TTgDto.Serialize(ReplyParameters, AParams));
  if not ReplyMarkup.IsEmpty then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup.Value, AParams));
end;

{ TTgSendVoiceOptions }

procedure TTgSendVoiceOptions.ApplyTo(AParams: TTgParams);
begin
  if BusinessConnectionId.HasValue then
    AParams.Add('business_connection_id', BusinessConnectionId.Value);
  if MessageThreadId.HasValue then
    AParams.Add('message_thread_id', MessageThreadId.Value);
  if DirectMessagesTopicId.HasValue then
    AParams.Add('direct_messages_topic_id', DirectMessagesTopicId.Value);
  if System.Assigned(EphemeralMessageParameters) then
    AParams.AddJson('ephemeral_message_parameters', TTgDto.Serialize(EphemeralMessageParameters, AParams));
  if Caption.HasValue then
    AParams.Add('caption', Caption.Value);
  if ParseMode.HasValue then
    AParams.Add('parse_mode', ParseMode.Value);
  if CaptionEntities.HasValue then
    AParams.AddJson('caption_entities', TTgDto.SerializeArray(TTgDto.ToIntf<ITgMessageEntity>(CaptionEntities.Value), AParams, 'caption_entities'));
  if Duration.HasValue then
    AParams.Add('duration', Duration.Value);
  if DisableNotification.HasValue then
    AParams.Add('disable_notification', DisableNotification.Value);
  if ProtectContent.HasValue then
    AParams.Add('protect_content', ProtectContent.Value);
  if AllowPaidBroadcast.HasValue then
    AParams.Add('allow_paid_broadcast', AllowPaidBroadcast.Value);
  if MessageEffectId.HasValue then
    AParams.Add('message_effect_id', MessageEffectId.Value);
  if System.Assigned(SuggestedPostParameters) then
    AParams.AddJson('suggested_post_parameters', TTgDto.Serialize(SuggestedPostParameters, AParams));
  if System.Assigned(ReplyParameters) then
    AParams.AddJson('reply_parameters', TTgDto.Serialize(ReplyParameters, AParams));
  if not ReplyMarkup.IsEmpty then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup.Value, AParams));
end;

{ TTgSendVideoNoteOptions }

procedure TTgSendVideoNoteOptions.ApplyTo(AParams: TTgParams);
begin
  if BusinessConnectionId.HasValue then
    AParams.Add('business_connection_id', BusinessConnectionId.Value);
  if MessageThreadId.HasValue then
    AParams.Add('message_thread_id', MessageThreadId.Value);
  if DirectMessagesTopicId.HasValue then
    AParams.Add('direct_messages_topic_id', DirectMessagesTopicId.Value);
  if System.Assigned(EphemeralMessageParameters) then
    AParams.AddJson('ephemeral_message_parameters', TTgDto.Serialize(EphemeralMessageParameters, AParams));
  if Duration.HasValue then
    AParams.Add('duration', Duration.Value);
  if Length.HasValue then
    AParams.Add('length', Length.Value);
  if not Thumbnail.IsEmpty then
    AParams.AddFile('thumbnail', Thumbnail);
  if DisableNotification.HasValue then
    AParams.Add('disable_notification', DisableNotification.Value);
  if ProtectContent.HasValue then
    AParams.Add('protect_content', ProtectContent.Value);
  if AllowPaidBroadcast.HasValue then
    AParams.Add('allow_paid_broadcast', AllowPaidBroadcast.Value);
  if MessageEffectId.HasValue then
    AParams.Add('message_effect_id', MessageEffectId.Value);
  if System.Assigned(SuggestedPostParameters) then
    AParams.AddJson('suggested_post_parameters', TTgDto.Serialize(SuggestedPostParameters, AParams));
  if System.Assigned(ReplyParameters) then
    AParams.AddJson('reply_parameters', TTgDto.Serialize(ReplyParameters, AParams));
  if not ReplyMarkup.IsEmpty then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup.Value, AParams));
end;

{ TTgSendPaidMediaOptions }

procedure TTgSendPaidMediaOptions.ApplyTo(AParams: TTgParams);
begin
  if BusinessConnectionId.HasValue then
    AParams.Add('business_connection_id', BusinessConnectionId.Value);
  if MessageThreadId.HasValue then
    AParams.Add('message_thread_id', MessageThreadId.Value);
  if DirectMessagesTopicId.HasValue then
    AParams.Add('direct_messages_topic_id', DirectMessagesTopicId.Value);
  if Payload.HasValue then
    AParams.Add('payload', Payload.Value);
  if Caption.HasValue then
    AParams.Add('caption', Caption.Value);
  if ParseMode.HasValue then
    AParams.Add('parse_mode', ParseMode.Value);
  if CaptionEntities.HasValue then
    AParams.AddJson('caption_entities', TTgDto.SerializeArray(TTgDto.ToIntf<ITgMessageEntity>(CaptionEntities.Value), AParams, 'caption_entities'));
  if ShowCaptionAboveMedia.HasValue then
    AParams.Add('show_caption_above_media', ShowCaptionAboveMedia.Value);
  if DisableNotification.HasValue then
    AParams.Add('disable_notification', DisableNotification.Value);
  if ProtectContent.HasValue then
    AParams.Add('protect_content', ProtectContent.Value);
  if AllowPaidBroadcast.HasValue then
    AParams.Add('allow_paid_broadcast', AllowPaidBroadcast.Value);
  if System.Assigned(SuggestedPostParameters) then
    AParams.AddJson('suggested_post_parameters', TTgDto.Serialize(SuggestedPostParameters, AParams));
  if System.Assigned(ReplyParameters) then
    AParams.AddJson('reply_parameters', TTgDto.Serialize(ReplyParameters, AParams));
  if not ReplyMarkup.IsEmpty then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup.Value, AParams));
end;

{ TTgSendMediaGroupOptions }

procedure TTgSendMediaGroupOptions.ApplyTo(AParams: TTgParams);
begin
  if BusinessConnectionId.HasValue then
    AParams.Add('business_connection_id', BusinessConnectionId.Value);
  if MessageThreadId.HasValue then
    AParams.Add('message_thread_id', MessageThreadId.Value);
  if DirectMessagesTopicId.HasValue then
    AParams.Add('direct_messages_topic_id', DirectMessagesTopicId.Value);
  if DisableNotification.HasValue then
    AParams.Add('disable_notification', DisableNotification.Value);
  if ProtectContent.HasValue then
    AParams.Add('protect_content', ProtectContent.Value);
  if AllowPaidBroadcast.HasValue then
    AParams.Add('allow_paid_broadcast', AllowPaidBroadcast.Value);
  if MessageEffectId.HasValue then
    AParams.Add('message_effect_id', MessageEffectId.Value);
  if System.Assigned(ReplyParameters) then
    AParams.AddJson('reply_parameters', TTgDto.Serialize(ReplyParameters, AParams));
end;

{ TTgSendLocationOptions }

procedure TTgSendLocationOptions.ApplyTo(AParams: TTgParams);
begin
  if BusinessConnectionId.HasValue then
    AParams.Add('business_connection_id', BusinessConnectionId.Value);
  if MessageThreadId.HasValue then
    AParams.Add('message_thread_id', MessageThreadId.Value);
  if DirectMessagesTopicId.HasValue then
    AParams.Add('direct_messages_topic_id', DirectMessagesTopicId.Value);
  if System.Assigned(EphemeralMessageParameters) then
    AParams.AddJson('ephemeral_message_parameters', TTgDto.Serialize(EphemeralMessageParameters, AParams));
  if HorizontalAccuracy.HasValue then
    AParams.Add('horizontal_accuracy', HorizontalAccuracy.Value);
  if LivePeriod.HasValue then
    AParams.Add('live_period', LivePeriod.Value);
  if Heading.HasValue then
    AParams.Add('heading', Heading.Value);
  if ProximityAlertRadius.HasValue then
    AParams.Add('proximity_alert_radius', ProximityAlertRadius.Value);
  if DisableNotification.HasValue then
    AParams.Add('disable_notification', DisableNotification.Value);
  if ProtectContent.HasValue then
    AParams.Add('protect_content', ProtectContent.Value);
  if AllowPaidBroadcast.HasValue then
    AParams.Add('allow_paid_broadcast', AllowPaidBroadcast.Value);
  if MessageEffectId.HasValue then
    AParams.Add('message_effect_id', MessageEffectId.Value);
  if System.Assigned(SuggestedPostParameters) then
    AParams.AddJson('suggested_post_parameters', TTgDto.Serialize(SuggestedPostParameters, AParams));
  if System.Assigned(ReplyParameters) then
    AParams.AddJson('reply_parameters', TTgDto.Serialize(ReplyParameters, AParams));
  if not ReplyMarkup.IsEmpty then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup.Value, AParams));
end;

{ TTgSendVenueOptions }

procedure TTgSendVenueOptions.ApplyTo(AParams: TTgParams);
begin
  if BusinessConnectionId.HasValue then
    AParams.Add('business_connection_id', BusinessConnectionId.Value);
  if MessageThreadId.HasValue then
    AParams.Add('message_thread_id', MessageThreadId.Value);
  if DirectMessagesTopicId.HasValue then
    AParams.Add('direct_messages_topic_id', DirectMessagesTopicId.Value);
  if System.Assigned(EphemeralMessageParameters) then
    AParams.AddJson('ephemeral_message_parameters', TTgDto.Serialize(EphemeralMessageParameters, AParams));
  if FoursquareId.HasValue then
    AParams.Add('foursquare_id', FoursquareId.Value);
  if FoursquareType.HasValue then
    AParams.Add('foursquare_type', FoursquareType.Value);
  if GooglePlaceId.HasValue then
    AParams.Add('google_place_id', GooglePlaceId.Value);
  if GooglePlaceType.HasValue then
    AParams.Add('google_place_type', GooglePlaceType.Value);
  if DisableNotification.HasValue then
    AParams.Add('disable_notification', DisableNotification.Value);
  if ProtectContent.HasValue then
    AParams.Add('protect_content', ProtectContent.Value);
  if AllowPaidBroadcast.HasValue then
    AParams.Add('allow_paid_broadcast', AllowPaidBroadcast.Value);
  if MessageEffectId.HasValue then
    AParams.Add('message_effect_id', MessageEffectId.Value);
  if System.Assigned(SuggestedPostParameters) then
    AParams.AddJson('suggested_post_parameters', TTgDto.Serialize(SuggestedPostParameters, AParams));
  if System.Assigned(ReplyParameters) then
    AParams.AddJson('reply_parameters', TTgDto.Serialize(ReplyParameters, AParams));
  if not ReplyMarkup.IsEmpty then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup.Value, AParams));
end;

{ TTgSendContactOptions }

procedure TTgSendContactOptions.ApplyTo(AParams: TTgParams);
begin
  if BusinessConnectionId.HasValue then
    AParams.Add('business_connection_id', BusinessConnectionId.Value);
  if MessageThreadId.HasValue then
    AParams.Add('message_thread_id', MessageThreadId.Value);
  if DirectMessagesTopicId.HasValue then
    AParams.Add('direct_messages_topic_id', DirectMessagesTopicId.Value);
  if System.Assigned(EphemeralMessageParameters) then
    AParams.AddJson('ephemeral_message_parameters', TTgDto.Serialize(EphemeralMessageParameters, AParams));
  if LastName.HasValue then
    AParams.Add('last_name', LastName.Value);
  if Vcard.HasValue then
    AParams.Add('vcard', Vcard.Value);
  if DisableNotification.HasValue then
    AParams.Add('disable_notification', DisableNotification.Value);
  if ProtectContent.HasValue then
    AParams.Add('protect_content', ProtectContent.Value);
  if AllowPaidBroadcast.HasValue then
    AParams.Add('allow_paid_broadcast', AllowPaidBroadcast.Value);
  if MessageEffectId.HasValue then
    AParams.Add('message_effect_id', MessageEffectId.Value);
  if System.Assigned(SuggestedPostParameters) then
    AParams.AddJson('suggested_post_parameters', TTgDto.Serialize(SuggestedPostParameters, AParams));
  if System.Assigned(ReplyParameters) then
    AParams.AddJson('reply_parameters', TTgDto.Serialize(ReplyParameters, AParams));
  if not ReplyMarkup.IsEmpty then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup.Value, AParams));
end;

{ TTgSendPollOptions }

procedure TTgSendPollOptions.ApplyTo(AParams: TTgParams);
begin
  if BusinessConnectionId.HasValue then
    AParams.Add('business_connection_id', BusinessConnectionId.Value);
  if MessageThreadId.HasValue then
    AParams.Add('message_thread_id', MessageThreadId.Value);
  if QuestionParseMode.HasValue then
    AParams.Add('question_parse_mode', QuestionParseMode.Value);
  if QuestionEntities.HasValue then
    AParams.AddJson('question_entities', TTgDto.SerializeArray(TTgDto.ToIntf<ITgMessageEntity>(QuestionEntities.Value), AParams, 'question_entities'));
  if IsAnonymous.HasValue then
    AParams.Add('is_anonymous', IsAnonymous.Value);
  if PollType.HasValue then
    AParams.Add('type', PollType.Value);
  if AllowsMultipleAnswers.HasValue then
    AParams.Add('allows_multiple_answers', AllowsMultipleAnswers.Value);
  if AllowsRevoting.HasValue then
    AParams.Add('allows_revoting', AllowsRevoting.Value);
  if ShuffleOptions.HasValue then
    AParams.Add('shuffle_options', ShuffleOptions.Value);
  if AllowAddingOptions.HasValue then
    AParams.Add('allow_adding_options', AllowAddingOptions.Value);
  if HideResultsUntilCloses.HasValue then
    AParams.Add('hide_results_until_closes', HideResultsUntilCloses.Value);
  if MembersOnly.HasValue then
    AParams.Add('members_only', MembersOnly.Value);
  if CountryCodes.HasValue then
    AParams.AddStrings('country_codes', CountryCodes.Value);
  if CorrectOptionIds.HasValue then
    AParams.AddInt64s('correct_option_ids', CorrectOptionIds.Value);
  if Explanation.HasValue then
    AParams.Add('explanation', Explanation.Value);
  if ExplanationParseMode.HasValue then
    AParams.Add('explanation_parse_mode', ExplanationParseMode.Value);
  if ExplanationEntities.HasValue then
    AParams.AddJson('explanation_entities', TTgDto.SerializeArray(TTgDto.ToIntf<ITgMessageEntity>(ExplanationEntities.Value), AParams, 'explanation_entities'));
  if not ExplanationMedia.IsEmpty then
    AParams.AddJson('explanation_media', TTgDto.Serialize(ExplanationMedia.Value, AParams));
  if OpenPeriod.HasValue then
    AParams.Add('open_period', OpenPeriod.Value);
  if CloseDate.HasValue then
    AParams.Add('close_date', CloseDate.Value);
  if IsClosed.HasValue then
    AParams.Add('is_closed', IsClosed.Value);
  if Description.HasValue then
    AParams.Add('description', Description.Value);
  if DescriptionParseMode.HasValue then
    AParams.Add('description_parse_mode', DescriptionParseMode.Value);
  if DescriptionEntities.HasValue then
    AParams.AddJson('description_entities', TTgDto.SerializeArray(TTgDto.ToIntf<ITgMessageEntity>(DescriptionEntities.Value), AParams, 'description_entities'));
  if not Media.IsEmpty then
    AParams.AddJson('media', TTgDto.Serialize(Media.Value, AParams));
  if DisableNotification.HasValue then
    AParams.Add('disable_notification', DisableNotification.Value);
  if ProtectContent.HasValue then
    AParams.Add('protect_content', ProtectContent.Value);
  if AllowPaidBroadcast.HasValue then
    AParams.Add('allow_paid_broadcast', AllowPaidBroadcast.Value);
  if MessageEffectId.HasValue then
    AParams.Add('message_effect_id', MessageEffectId.Value);
  if System.Assigned(ReplyParameters) then
    AParams.AddJson('reply_parameters', TTgDto.Serialize(ReplyParameters, AParams));
  if not ReplyMarkup.IsEmpty then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup.Value, AParams));
end;

{ TTgSendChecklistOptions }

procedure TTgSendChecklistOptions.ApplyTo(AParams: TTgParams);
begin
  if DisableNotification.HasValue then
    AParams.Add('disable_notification', DisableNotification.Value);
  if ProtectContent.HasValue then
    AParams.Add('protect_content', ProtectContent.Value);
  if MessageEffectId.HasValue then
    AParams.Add('message_effect_id', MessageEffectId.Value);
  if System.Assigned(ReplyParameters) then
    AParams.AddJson('reply_parameters', TTgDto.Serialize(ReplyParameters, AParams));
  if System.Assigned(ReplyMarkup) then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup, AParams));
end;

{ TTgSendDiceOptions }

procedure TTgSendDiceOptions.ApplyTo(AParams: TTgParams);
begin
  if BusinessConnectionId.HasValue then
    AParams.Add('business_connection_id', BusinessConnectionId.Value);
  if MessageThreadId.HasValue then
    AParams.Add('message_thread_id', MessageThreadId.Value);
  if DirectMessagesTopicId.HasValue then
    AParams.Add('direct_messages_topic_id', DirectMessagesTopicId.Value);
  if Emoji.HasValue then
    AParams.Add('emoji', Emoji.Value);
  if DisableNotification.HasValue then
    AParams.Add('disable_notification', DisableNotification.Value);
  if ProtectContent.HasValue then
    AParams.Add('protect_content', ProtectContent.Value);
  if AllowPaidBroadcast.HasValue then
    AParams.Add('allow_paid_broadcast', AllowPaidBroadcast.Value);
  if MessageEffectId.HasValue then
    AParams.Add('message_effect_id', MessageEffectId.Value);
  if System.Assigned(SuggestedPostParameters) then
    AParams.AddJson('suggested_post_parameters', TTgDto.Serialize(SuggestedPostParameters, AParams));
  if System.Assigned(ReplyParameters) then
    AParams.AddJson('reply_parameters', TTgDto.Serialize(ReplyParameters, AParams));
  if not ReplyMarkup.IsEmpty then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup.Value, AParams));
end;

{ TTgSendMessageDraftOptions }

procedure TTgSendMessageDraftOptions.ApplyTo(AParams: TTgParams);
begin
  if MessageThreadId.HasValue then
    AParams.Add('message_thread_id', MessageThreadId.Value);
  if Text.HasValue then
    AParams.Add('text', Text.Value);
  if ParseMode.HasValue then
    AParams.Add('parse_mode', ParseMode.Value);
  if Entities.HasValue then
    AParams.AddJson('entities', TTgDto.SerializeArray(TTgDto.ToIntf<ITgMessageEntity>(Entities.Value), AParams, 'entities'));
  if CanStop.HasValue then
    AParams.Add('can_stop', CanStop.Value);
  if KeepOnStop.HasValue then
    AParams.Add('keep_on_stop', KeepOnStop.Value);
end;

{ TTgSendChatActionOptions }

procedure TTgSendChatActionOptions.ApplyTo(AParams: TTgParams);
begin
  if BusinessConnectionId.HasValue then
    AParams.Add('business_connection_id', BusinessConnectionId.Value);
  if MessageThreadId.HasValue then
    AParams.Add('message_thread_id', MessageThreadId.Value);
end;

{ TTgSetMessageReactionOptions }

procedure TTgSetMessageReactionOptions.ApplyTo(AParams: TTgParams);
begin
  if Reaction.HasValue then
    AParams.AddJson('reaction', TTgDto.SerializeArray(TTgDto.ToIntf<ITgReactionType>(Reaction.Value), AParams, 'reaction'));
  if IsBig.HasValue then
    AParams.Add('is_big', IsBig.Value);
end;

{ TTgGetUserProfilePhotosOptions }

procedure TTgGetUserProfilePhotosOptions.ApplyTo(AParams: TTgParams);
begin
  if Offset.HasValue then
    AParams.Add('offset', Offset.Value);
  if Limit.HasValue then
    AParams.Add('limit', Limit.Value);
end;

{ TTgGetUserProfileAudiosOptions }

procedure TTgGetUserProfileAudiosOptions.ApplyTo(AParams: TTgParams);
begin
  if Offset.HasValue then
    AParams.Add('offset', Offset.Value);
  if Limit.HasValue then
    AParams.Add('limit', Limit.Value);
end;

{ TTgSetUserEmojiStatusOptions }

procedure TTgSetUserEmojiStatusOptions.ApplyTo(AParams: TTgParams);
begin
  if EmojiStatusCustomEmojiId.HasValue then
    AParams.Add('emoji_status_custom_emoji_id', EmojiStatusCustomEmojiId.Value);
  if EmojiStatusExpirationDate.HasValue then
    AParams.Add('emoji_status_expiration_date', EmojiStatusExpirationDate.Value);
end;

{ TTgBanChatMemberOptions }

procedure TTgBanChatMemberOptions.ApplyTo(AParams: TTgParams);
begin
  if UntilDate.HasValue then
    AParams.Add('until_date', UntilDate.Value);
  if RevokeMessages.HasValue then
    AParams.Add('revoke_messages', RevokeMessages.Value);
end;

{ TTgUnbanChatMemberOptions }

procedure TTgUnbanChatMemberOptions.ApplyTo(AParams: TTgParams);
begin
  if OnlyIfBanned.HasValue then
    AParams.Add('only_if_banned', OnlyIfBanned.Value);
end;

{ TTgRestrictChatMemberOptions }

procedure TTgRestrictChatMemberOptions.ApplyTo(AParams: TTgParams);
begin
  if UseIndependentChatPermissions.HasValue then
    AParams.Add('use_independent_chat_permissions', UseIndependentChatPermissions.Value);
  if UntilDate.HasValue then
    AParams.Add('until_date', UntilDate.Value);
end;

{ TTgPromoteChatMemberOptions }

procedure TTgPromoteChatMemberOptions.ApplyTo(AParams: TTgParams);
begin
  if IsAnonymous.HasValue then
    AParams.Add('is_anonymous', IsAnonymous.Value);
  if CanManageChat.HasValue then
    AParams.Add('can_manage_chat', CanManageChat.Value);
  if CanDeleteMessages.HasValue then
    AParams.Add('can_delete_messages', CanDeleteMessages.Value);
  if CanManageVideoChats.HasValue then
    AParams.Add('can_manage_video_chats', CanManageVideoChats.Value);
  if CanRestrictMembers.HasValue then
    AParams.Add('can_restrict_members', CanRestrictMembers.Value);
  if CanPromoteMembers.HasValue then
    AParams.Add('can_promote_members', CanPromoteMembers.Value);
  if CanChangeInfo.HasValue then
    AParams.Add('can_change_info', CanChangeInfo.Value);
  if CanInviteUsers.HasValue then
    AParams.Add('can_invite_users', CanInviteUsers.Value);
  if CanPostStories.HasValue then
    AParams.Add('can_post_stories', CanPostStories.Value);
  if CanEditStories.HasValue then
    AParams.Add('can_edit_stories', CanEditStories.Value);
  if CanDeleteStories.HasValue then
    AParams.Add('can_delete_stories', CanDeleteStories.Value);
  if CanPostMessages.HasValue then
    AParams.Add('can_post_messages', CanPostMessages.Value);
  if CanEditMessages.HasValue then
    AParams.Add('can_edit_messages', CanEditMessages.Value);
  if CanPinMessages.HasValue then
    AParams.Add('can_pin_messages', CanPinMessages.Value);
  if CanManageTopics.HasValue then
    AParams.Add('can_manage_topics', CanManageTopics.Value);
  if CanManageDirectMessages.HasValue then
    AParams.Add('can_manage_direct_messages', CanManageDirectMessages.Value);
  if CanManageTags.HasValue then
    AParams.Add('can_manage_tags', CanManageTags.Value);
  if CanSendWelcomeMessages.HasValue then
    AParams.Add('can_send_welcome_messages', CanSendWelcomeMessages.Value);
end;

{ TTgSetChatMemberTagOptions }

procedure TTgSetChatMemberTagOptions.ApplyTo(AParams: TTgParams);
begin
  if Tag.HasValue then
    AParams.Add('tag', Tag.Value);
end;

{ TTgSetChatPermissionsOptions }

procedure TTgSetChatPermissionsOptions.ApplyTo(AParams: TTgParams);
begin
  if UseIndependentChatPermissions.HasValue then
    AParams.Add('use_independent_chat_permissions', UseIndependentChatPermissions.Value);
end;

{ TTgCreateChatInviteLinkOptions }

procedure TTgCreateChatInviteLinkOptions.ApplyTo(AParams: TTgParams);
begin
  if Name.HasValue then
    AParams.Add('name', Name.Value);
  if ExpireDate.HasValue then
    AParams.Add('expire_date', ExpireDate.Value);
  if MemberLimit.HasValue then
    AParams.Add('member_limit', MemberLimit.Value);
  if CreatesJoinRequest.HasValue then
    AParams.Add('creates_join_request', CreatesJoinRequest.Value);
end;

{ TTgEditChatInviteLinkOptions }

procedure TTgEditChatInviteLinkOptions.ApplyTo(AParams: TTgParams);
begin
  if Name.HasValue then
    AParams.Add('name', Name.Value);
  if ExpireDate.HasValue then
    AParams.Add('expire_date', ExpireDate.Value);
  if MemberLimit.HasValue then
    AParams.Add('member_limit', MemberLimit.Value);
  if CreatesJoinRequest.HasValue then
    AParams.Add('creates_join_request', CreatesJoinRequest.Value);
end;

{ TTgCreateChatSubscriptionInviteLinkOptions }

procedure TTgCreateChatSubscriptionInviteLinkOptions.ApplyTo(AParams: TTgParams);
begin
  if Name.HasValue then
    AParams.Add('name', Name.Value);
end;

{ TTgEditChatSubscriptionInviteLinkOptions }

procedure TTgEditChatSubscriptionInviteLinkOptions.ApplyTo(AParams: TTgParams);
begin
  if Name.HasValue then
    AParams.Add('name', Name.Value);
end;

{ TTgSetChatDescriptionOptions }

procedure TTgSetChatDescriptionOptions.ApplyTo(AParams: TTgParams);
begin
  if Description.HasValue then
    AParams.Add('description', Description.Value);
end;

{ TTgPinChatMessageOptions }

procedure TTgPinChatMessageOptions.ApplyTo(AParams: TTgParams);
begin
  if BusinessConnectionId.HasValue then
    AParams.Add('business_connection_id', BusinessConnectionId.Value);
  if DisableNotification.HasValue then
    AParams.Add('disable_notification', DisableNotification.Value);
end;

{ TTgUnpinChatMessageOptions }

procedure TTgUnpinChatMessageOptions.ApplyTo(AParams: TTgParams);
begin
  if BusinessConnectionId.HasValue then
    AParams.Add('business_connection_id', BusinessConnectionId.Value);
  if MessageId.HasValue then
    AParams.Add('message_id', MessageId.Value);
end;

{ TTgGetChatAdministratorsOptions }

procedure TTgGetChatAdministratorsOptions.ApplyTo(AParams: TTgParams);
begin
  if ReturnBots.HasValue then
    AParams.Add('return_bots', ReturnBots.Value);
end;

{ TTgCreateForumTopicOptions }

procedure TTgCreateForumTopicOptions.ApplyTo(AParams: TTgParams);
begin
  if IconColor.HasValue then
    AParams.Add('icon_color', IconColor.Value);
  if IconCustomEmojiId.HasValue then
    AParams.Add('icon_custom_emoji_id', IconCustomEmojiId.Value);
end;

{ TTgEditForumTopicOptions }

procedure TTgEditForumTopicOptions.ApplyTo(AParams: TTgParams);
begin
  if Name.HasValue then
    AParams.Add('name', Name.Value);
  if IconCustomEmojiId.HasValue then
    AParams.Add('icon_custom_emoji_id', IconCustomEmojiId.Value);
end;

{ TTgAnswerCallbackQueryOptions }

procedure TTgAnswerCallbackQueryOptions.ApplyTo(AParams: TTgParams);
begin
  if Text.HasValue then
    AParams.Add('text', Text.Value);
  if ShowAlert.HasValue then
    AParams.Add('show_alert', ShowAlert.Value);
  if Url.HasValue then
    AParams.Add('url', Url.Value);
  if CacheTime.HasValue then
    AParams.Add('cache_time', CacheTime.Value);
end;

{ TTgSetManagedBotAccessSettingsOptions }

procedure TTgSetManagedBotAccessSettingsOptions.ApplyTo(AParams: TTgParams);
begin
  if AddedUserIds.HasValue then
    AParams.AddInt64s('added_user_ids', AddedUserIds.Value);
end;

{ TTgSetMyCommandsOptions }

procedure TTgSetMyCommandsOptions.ApplyTo(AParams: TTgParams);
begin
  if not Scope.IsEmpty then
    AParams.AddJson('scope', TTgDto.Serialize(Scope.Value, AParams));
  if LanguageCode.HasValue then
    AParams.Add('language_code', LanguageCode.Value);
end;

{ TTgDeleteMyCommandsOptions }

procedure TTgDeleteMyCommandsOptions.ApplyTo(AParams: TTgParams);
begin
  if not Scope.IsEmpty then
    AParams.AddJson('scope', TTgDto.Serialize(Scope.Value, AParams));
  if LanguageCode.HasValue then
    AParams.Add('language_code', LanguageCode.Value);
end;

{ TTgGetMyCommandsOptions }

procedure TTgGetMyCommandsOptions.ApplyTo(AParams: TTgParams);
begin
  if not Scope.IsEmpty then
    AParams.AddJson('scope', TTgDto.Serialize(Scope.Value, AParams));
  if LanguageCode.HasValue then
    AParams.Add('language_code', LanguageCode.Value);
end;

{ TTgSetMyNameOptions }

procedure TTgSetMyNameOptions.ApplyTo(AParams: TTgParams);
begin
  if Name.HasValue then
    AParams.Add('name', Name.Value);
  if LanguageCode.HasValue then
    AParams.Add('language_code', LanguageCode.Value);
end;

{ TTgGetMyNameOptions }

procedure TTgGetMyNameOptions.ApplyTo(AParams: TTgParams);
begin
  if LanguageCode.HasValue then
    AParams.Add('language_code', LanguageCode.Value);
end;

{ TTgSetMyDescriptionOptions }

procedure TTgSetMyDescriptionOptions.ApplyTo(AParams: TTgParams);
begin
  if Description.HasValue then
    AParams.Add('description', Description.Value);
  if LanguageCode.HasValue then
    AParams.Add('language_code', LanguageCode.Value);
end;

{ TTgGetMyDescriptionOptions }

procedure TTgGetMyDescriptionOptions.ApplyTo(AParams: TTgParams);
begin
  if LanguageCode.HasValue then
    AParams.Add('language_code', LanguageCode.Value);
end;

{ TTgSetMyShortDescriptionOptions }

procedure TTgSetMyShortDescriptionOptions.ApplyTo(AParams: TTgParams);
begin
  if ShortDescription.HasValue then
    AParams.Add('short_description', ShortDescription.Value);
  if LanguageCode.HasValue then
    AParams.Add('language_code', LanguageCode.Value);
end;

{ TTgGetMyShortDescriptionOptions }

procedure TTgGetMyShortDescriptionOptions.ApplyTo(AParams: TTgParams);
begin
  if LanguageCode.HasValue then
    AParams.Add('language_code', LanguageCode.Value);
end;

{ TTgSetChatMenuButtonOptions }

procedure TTgSetChatMenuButtonOptions.ApplyTo(AParams: TTgParams);
begin
  if ChatId.HasValue then
    AParams.Add('chat_id', ChatId.Value);
  if System.Assigned(MenuButton) then
    AParams.AddJson('menu_button', TTgDto.Serialize(MenuButton, AParams));
end;

{ TTgGetChatMenuButtonOptions }

procedure TTgGetChatMenuButtonOptions.ApplyTo(AParams: TTgParams);
begin
  if ChatId.HasValue then
    AParams.Add('chat_id', ChatId.Value);
end;

{ TTgSetMyDefaultAdministratorRightsOptions }

procedure TTgSetMyDefaultAdministratorRightsOptions.ApplyTo(AParams: TTgParams);
begin
  if System.Assigned(Rights) then
    AParams.AddJson('rights', TTgDto.Serialize(Rights, AParams));
  if ForChannels.HasValue then
    AParams.Add('for_channels', ForChannels.Value);
end;

{ TTgGetMyDefaultAdministratorRightsOptions }

procedure TTgGetMyDefaultAdministratorRightsOptions.ApplyTo(AParams: TTgParams);
begin
  if ForChannels.HasValue then
    AParams.Add('for_channels', ForChannels.Value);
end;

{ TTgSendGiftOptions }

procedure TTgSendGiftOptions.ApplyTo(AParams: TTgParams);
begin
  if UserId.HasValue then
    AParams.Add('user_id', UserId.Value);
  if not ChatId.IsEmpty then
    AParams.AddChatId('chat_id', ChatId);
  if PayForUpgrade.HasValue then
    AParams.Add('pay_for_upgrade', PayForUpgrade.Value);
  if Text.HasValue then
    AParams.Add('text', Text.Value);
  if TextParseMode.HasValue then
    AParams.Add('text_parse_mode', TextParseMode.Value);
  if TextEntities.HasValue then
    AParams.AddJson('text_entities', TTgDto.SerializeArray(TTgDto.ToIntf<ITgMessageEntity>(TextEntities.Value), AParams, 'text_entities'));
end;

{ TTgGiftPremiumSubscriptionOptions }

procedure TTgGiftPremiumSubscriptionOptions.ApplyTo(AParams: TTgParams);
begin
  if Text.HasValue then
    AParams.Add('text', Text.Value);
  if TextParseMode.HasValue then
    AParams.Add('text_parse_mode', TextParseMode.Value);
  if TextEntities.HasValue then
    AParams.AddJson('text_entities', TTgDto.SerializeArray(TTgDto.ToIntf<ITgMessageEntity>(TextEntities.Value), AParams, 'text_entities'));
end;

{ TTgVerifyUserOptions }

procedure TTgVerifyUserOptions.ApplyTo(AParams: TTgParams);
begin
  if CustomDescription.HasValue then
    AParams.Add('custom_description', CustomDescription.Value);
end;

{ TTgVerifyChatOptions }

procedure TTgVerifyChatOptions.ApplyTo(AParams: TTgParams);
begin
  if CustomDescription.HasValue then
    AParams.Add('custom_description', CustomDescription.Value);
end;

{ TTgSetBusinessAccountNameOptions }

procedure TTgSetBusinessAccountNameOptions.ApplyTo(AParams: TTgParams);
begin
  if LastName.HasValue then
    AParams.Add('last_name', LastName.Value);
end;

{ TTgSetBusinessAccountUsernameOptions }

procedure TTgSetBusinessAccountUsernameOptions.ApplyTo(AParams: TTgParams);
begin
  if Username.HasValue then
    AParams.Add('username', Username.Value);
end;

{ TTgSetBusinessAccountBioOptions }

procedure TTgSetBusinessAccountBioOptions.ApplyTo(AParams: TTgParams);
begin
  if Bio.HasValue then
    AParams.Add('bio', Bio.Value);
end;

{ TTgSetBusinessAccountProfilePhotoOptions }

procedure TTgSetBusinessAccountProfilePhotoOptions.ApplyTo(AParams: TTgParams);
begin
  if IsPublic.HasValue then
    AParams.Add('is_public', IsPublic.Value);
end;

{ TTgRemoveBusinessAccountProfilePhotoOptions }

procedure TTgRemoveBusinessAccountProfilePhotoOptions.ApplyTo(AParams: TTgParams);
begin
  if IsPublic.HasValue then
    AParams.Add('is_public', IsPublic.Value);
end;

{ TTgGetBusinessAccountGiftsOptions }

procedure TTgGetBusinessAccountGiftsOptions.ApplyTo(AParams: TTgParams);
begin
  if ExcludeUnsaved.HasValue then
    AParams.Add('exclude_unsaved', ExcludeUnsaved.Value);
  if ExcludeSaved.HasValue then
    AParams.Add('exclude_saved', ExcludeSaved.Value);
  if ExcludeUnlimited.HasValue then
    AParams.Add('exclude_unlimited', ExcludeUnlimited.Value);
  if ExcludeLimitedUpgradable.HasValue then
    AParams.Add('exclude_limited_upgradable', ExcludeLimitedUpgradable.Value);
  if ExcludeLimitedNonUpgradable.HasValue then
    AParams.Add('exclude_limited_non_upgradable', ExcludeLimitedNonUpgradable.Value);
  if ExcludeUnique.HasValue then
    AParams.Add('exclude_unique', ExcludeUnique.Value);
  if ExcludeFromBlockchain.HasValue then
    AParams.Add('exclude_from_blockchain', ExcludeFromBlockchain.Value);
  if SortByPrice.HasValue then
    AParams.Add('sort_by_price', SortByPrice.Value);
  if Offset.HasValue then
    AParams.Add('offset', Offset.Value);
  if Limit.HasValue then
    AParams.Add('limit', Limit.Value);
end;

{ TTgGetUserGiftsOptions }

procedure TTgGetUserGiftsOptions.ApplyTo(AParams: TTgParams);
begin
  if ExcludeUnlimited.HasValue then
    AParams.Add('exclude_unlimited', ExcludeUnlimited.Value);
  if ExcludeLimitedUpgradable.HasValue then
    AParams.Add('exclude_limited_upgradable', ExcludeLimitedUpgradable.Value);
  if ExcludeLimitedNonUpgradable.HasValue then
    AParams.Add('exclude_limited_non_upgradable', ExcludeLimitedNonUpgradable.Value);
  if ExcludeFromBlockchain.HasValue then
    AParams.Add('exclude_from_blockchain', ExcludeFromBlockchain.Value);
  if ExcludeUnique.HasValue then
    AParams.Add('exclude_unique', ExcludeUnique.Value);
  if SortByPrice.HasValue then
    AParams.Add('sort_by_price', SortByPrice.Value);
  if Offset.HasValue then
    AParams.Add('offset', Offset.Value);
  if Limit.HasValue then
    AParams.Add('limit', Limit.Value);
end;

{ TTgGetChatGiftsOptions }

procedure TTgGetChatGiftsOptions.ApplyTo(AParams: TTgParams);
begin
  if ExcludeUnsaved.HasValue then
    AParams.Add('exclude_unsaved', ExcludeUnsaved.Value);
  if ExcludeSaved.HasValue then
    AParams.Add('exclude_saved', ExcludeSaved.Value);
  if ExcludeUnlimited.HasValue then
    AParams.Add('exclude_unlimited', ExcludeUnlimited.Value);
  if ExcludeLimitedUpgradable.HasValue then
    AParams.Add('exclude_limited_upgradable', ExcludeLimitedUpgradable.Value);
  if ExcludeLimitedNonUpgradable.HasValue then
    AParams.Add('exclude_limited_non_upgradable', ExcludeLimitedNonUpgradable.Value);
  if ExcludeFromBlockchain.HasValue then
    AParams.Add('exclude_from_blockchain', ExcludeFromBlockchain.Value);
  if ExcludeUnique.HasValue then
    AParams.Add('exclude_unique', ExcludeUnique.Value);
  if SortByPrice.HasValue then
    AParams.Add('sort_by_price', SortByPrice.Value);
  if Offset.HasValue then
    AParams.Add('offset', Offset.Value);
  if Limit.HasValue then
    AParams.Add('limit', Limit.Value);
end;

{ TTgUpgradeGiftOptions }

procedure TTgUpgradeGiftOptions.ApplyTo(AParams: TTgParams);
begin
  if KeepOriginalDetails.HasValue then
    AParams.Add('keep_original_details', KeepOriginalDetails.Value);
  if StarCount.HasValue then
    AParams.Add('star_count', StarCount.Value);
end;

{ TTgTransferGiftOptions }

procedure TTgTransferGiftOptions.ApplyTo(AParams: TTgParams);
begin
  if StarCount.HasValue then
    AParams.Add('star_count', StarCount.Value);
end;

{ TTgPostStoryOptions }

procedure TTgPostStoryOptions.ApplyTo(AParams: TTgParams);
begin
  if Caption.HasValue then
    AParams.Add('caption', Caption.Value);
  if ParseMode.HasValue then
    AParams.Add('parse_mode', ParseMode.Value);
  if CaptionEntities.HasValue then
    AParams.AddJson('caption_entities', TTgDto.SerializeArray(TTgDto.ToIntf<ITgMessageEntity>(CaptionEntities.Value), AParams, 'caption_entities'));
  if Areas.HasValue then
    AParams.AddJson('areas', TTgDto.SerializeArray(TTgDto.ToIntf<ITgStoryArea>(Areas.Value), AParams, 'areas'));
  if PostToChatPage.HasValue then
    AParams.Add('post_to_chat_page', PostToChatPage.Value);
  if ProtectContent.HasValue then
    AParams.Add('protect_content', ProtectContent.Value);
end;

{ TTgRepostStoryOptions }

procedure TTgRepostStoryOptions.ApplyTo(AParams: TTgParams);
begin
  if PostToChatPage.HasValue then
    AParams.Add('post_to_chat_page', PostToChatPage.Value);
  if ProtectContent.HasValue then
    AParams.Add('protect_content', ProtectContent.Value);
end;

{ TTgEditStoryOptions }

procedure TTgEditStoryOptions.ApplyTo(AParams: TTgParams);
begin
  if Caption.HasValue then
    AParams.Add('caption', Caption.Value);
  if ParseMode.HasValue then
    AParams.Add('parse_mode', ParseMode.Value);
  if CaptionEntities.HasValue then
    AParams.AddJson('caption_entities', TTgDto.SerializeArray(TTgDto.ToIntf<ITgMessageEntity>(CaptionEntities.Value), AParams, 'caption_entities'));
  if Areas.HasValue then
    AParams.AddJson('areas', TTgDto.SerializeArray(TTgDto.ToIntf<ITgStoryArea>(Areas.Value), AParams, 'areas'));
end;

{ TTgSavePreparedInlineMessageOptions }

procedure TTgSavePreparedInlineMessageOptions.ApplyTo(AParams: TTgParams);
begin
  if AllowUserChats.HasValue then
    AParams.Add('allow_user_chats', AllowUserChats.Value);
  if AllowBotChats.HasValue then
    AParams.Add('allow_bot_chats', AllowBotChats.Value);
  if AllowGroupChats.HasValue then
    AParams.Add('allow_group_chats', AllowGroupChats.Value);
  if AllowChannelChats.HasValue then
    AParams.Add('allow_channel_chats', AllowChannelChats.Value);
end;

{ TTgEditMessageTextOptions }

procedure TTgEditMessageTextOptions.ApplyTo(AParams: TTgParams);
begin
  if BusinessConnectionId.HasValue then
    AParams.Add('business_connection_id', BusinessConnectionId.Value);
  if not ChatId.IsEmpty then
    AParams.AddChatId('chat_id', ChatId);
  if MessageId.HasValue then
    AParams.Add('message_id', MessageId.Value);
  if InlineMessageId.HasValue then
    AParams.Add('inline_message_id', InlineMessageId.Value);
  if Text.HasValue then
    AParams.Add('text', Text.Value);
  if ParseMode.HasValue then
    AParams.Add('parse_mode', ParseMode.Value);
  if Entities.HasValue then
    AParams.AddJson('entities', TTgDto.SerializeArray(TTgDto.ToIntf<ITgMessageEntity>(Entities.Value), AParams, 'entities'));
  if System.Assigned(LinkPreviewOptions) then
    AParams.AddJson('link_preview_options', TTgDto.Serialize(LinkPreviewOptions, AParams));
  if System.Assigned(RichMessage) then
    AParams.AddJson('rich_message', TTgDto.Serialize(RichMessage, AParams));
  if System.Assigned(ReplyMarkup) then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup, AParams));
end;

{ TTgEditMessageCaptionOptions }

procedure TTgEditMessageCaptionOptions.ApplyTo(AParams: TTgParams);
begin
  if BusinessConnectionId.HasValue then
    AParams.Add('business_connection_id', BusinessConnectionId.Value);
  if not ChatId.IsEmpty then
    AParams.AddChatId('chat_id', ChatId);
  if MessageId.HasValue then
    AParams.Add('message_id', MessageId.Value);
  if InlineMessageId.HasValue then
    AParams.Add('inline_message_id', InlineMessageId.Value);
  if Caption.HasValue then
    AParams.Add('caption', Caption.Value);
  if ParseMode.HasValue then
    AParams.Add('parse_mode', ParseMode.Value);
  if CaptionEntities.HasValue then
    AParams.AddJson('caption_entities', TTgDto.SerializeArray(TTgDto.ToIntf<ITgMessageEntity>(CaptionEntities.Value), AParams, 'caption_entities'));
  if ShowCaptionAboveMedia.HasValue then
    AParams.Add('show_caption_above_media', ShowCaptionAboveMedia.Value);
  if System.Assigned(ReplyMarkup) then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup, AParams));
end;

{ TTgEditMessageMediaOptions }

procedure TTgEditMessageMediaOptions.ApplyTo(AParams: TTgParams);
begin
  if BusinessConnectionId.HasValue then
    AParams.Add('business_connection_id', BusinessConnectionId.Value);
  if not ChatId.IsEmpty then
    AParams.AddChatId('chat_id', ChatId);
  if MessageId.HasValue then
    AParams.Add('message_id', MessageId.Value);
  if InlineMessageId.HasValue then
    AParams.Add('inline_message_id', InlineMessageId.Value);
  if System.Assigned(ReplyMarkup) then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup, AParams));
end;

{ TTgEditMessageLiveLocationOptions }

procedure TTgEditMessageLiveLocationOptions.ApplyTo(AParams: TTgParams);
begin
  if BusinessConnectionId.HasValue then
    AParams.Add('business_connection_id', BusinessConnectionId.Value);
  if not ChatId.IsEmpty then
    AParams.AddChatId('chat_id', ChatId);
  if MessageId.HasValue then
    AParams.Add('message_id', MessageId.Value);
  if InlineMessageId.HasValue then
    AParams.Add('inline_message_id', InlineMessageId.Value);
  if LivePeriod.HasValue then
    AParams.Add('live_period', LivePeriod.Value);
  if HorizontalAccuracy.HasValue then
    AParams.Add('horizontal_accuracy', HorizontalAccuracy.Value);
  if Heading.HasValue then
    AParams.Add('heading', Heading.Value);
  if ProximityAlertRadius.HasValue then
    AParams.Add('proximity_alert_radius', ProximityAlertRadius.Value);
  if System.Assigned(ReplyMarkup) then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup, AParams));
end;

{ TTgStopMessageLiveLocationOptions }

procedure TTgStopMessageLiveLocationOptions.ApplyTo(AParams: TTgParams);
begin
  if BusinessConnectionId.HasValue then
    AParams.Add('business_connection_id', BusinessConnectionId.Value);
  if not ChatId.IsEmpty then
    AParams.AddChatId('chat_id', ChatId);
  if MessageId.HasValue then
    AParams.Add('message_id', MessageId.Value);
  if InlineMessageId.HasValue then
    AParams.Add('inline_message_id', InlineMessageId.Value);
  if System.Assigned(ReplyMarkup) then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup, AParams));
end;

{ TTgEditMessageChecklistOptions }

procedure TTgEditMessageChecklistOptions.ApplyTo(AParams: TTgParams);
begin
  if System.Assigned(ReplyMarkup) then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup, AParams));
end;

{ TTgEditMessageReplyMarkupOptions }

procedure TTgEditMessageReplyMarkupOptions.ApplyTo(AParams: TTgParams);
begin
  if BusinessConnectionId.HasValue then
    AParams.Add('business_connection_id', BusinessConnectionId.Value);
  if not ChatId.IsEmpty then
    AParams.AddChatId('chat_id', ChatId);
  if MessageId.HasValue then
    AParams.Add('message_id', MessageId.Value);
  if InlineMessageId.HasValue then
    AParams.Add('inline_message_id', InlineMessageId.Value);
  if System.Assigned(ReplyMarkup) then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup, AParams));
end;

{ TTgStopPollOptions }

procedure TTgStopPollOptions.ApplyTo(AParams: TTgParams);
begin
  if BusinessConnectionId.HasValue then
    AParams.Add('business_connection_id', BusinessConnectionId.Value);
  if System.Assigned(ReplyMarkup) then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup, AParams));
end;

{ TTgEditEphemeralMessageTextOptions }

procedure TTgEditEphemeralMessageTextOptions.ApplyTo(AParams: TTgParams);
begin
  if Text.HasValue then
    AParams.Add('text', Text.Value);
  if ParseMode.HasValue then
    AParams.Add('parse_mode', ParseMode.Value);
  if Entities.HasValue then
    AParams.AddJson('entities', TTgDto.SerializeArray(TTgDto.ToIntf<ITgMessageEntity>(Entities.Value), AParams, 'entities'));
  if System.Assigned(RichMessage) then
    AParams.AddJson('rich_message', TTgDto.Serialize(RichMessage, AParams));
  if System.Assigned(LinkPreviewOptions) then
    AParams.AddJson('link_preview_options', TTgDto.Serialize(LinkPreviewOptions, AParams));
  if System.Assigned(ReplyMarkup) then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup, AParams));
end;

{ TTgEditEphemeralMessageMediaOptions }

procedure TTgEditEphemeralMessageMediaOptions.ApplyTo(AParams: TTgParams);
begin
  if System.Assigned(ReplyMarkup) then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup, AParams));
end;

{ TTgEditEphemeralMessageCaptionOptions }

procedure TTgEditEphemeralMessageCaptionOptions.ApplyTo(AParams: TTgParams);
begin
  if Caption.HasValue then
    AParams.Add('caption', Caption.Value);
  if ParseMode.HasValue then
    AParams.Add('parse_mode', ParseMode.Value);
  if CaptionEntities.HasValue then
    AParams.AddJson('caption_entities', TTgDto.SerializeArray(TTgDto.ToIntf<ITgMessageEntity>(CaptionEntities.Value), AParams, 'caption_entities'));
  if ShowCaptionAboveMedia.HasValue then
    AParams.Add('show_caption_above_media', ShowCaptionAboveMedia.Value);
  if System.Assigned(ReplyMarkup) then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup, AParams));
end;

{ TTgEditEphemeralMessageReplyMarkupOptions }

procedure TTgEditEphemeralMessageReplyMarkupOptions.ApplyTo(AParams: TTgParams);
begin
  if System.Assigned(ReplyMarkup) then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup, AParams));
end;

{ TTgApproveSuggestedPostOptions }

procedure TTgApproveSuggestedPostOptions.ApplyTo(AParams: TTgParams);
begin
  if SendDate.HasValue then
    AParams.Add('send_date', SendDate.Value);
end;

{ TTgDeclineSuggestedPostOptions }

procedure TTgDeclineSuggestedPostOptions.ApplyTo(AParams: TTgParams);
begin
  if Comment.HasValue then
    AParams.Add('comment', Comment.Value);
end;

{ TTgDeleteMessageReactionOptions }

procedure TTgDeleteMessageReactionOptions.ApplyTo(AParams: TTgParams);
begin
  if UserId.HasValue then
    AParams.Add('user_id', UserId.Value);
  if ActorChatId.HasValue then
    AParams.Add('actor_chat_id', ActorChatId.Value);
end;

{ TTgDeleteAllMessageReactionsOptions }

procedure TTgDeleteAllMessageReactionsOptions.ApplyTo(AParams: TTgParams);
begin
  if UserId.HasValue then
    AParams.Add('user_id', UserId.Value);
  if ActorChatId.HasValue then
    AParams.Add('actor_chat_id', ActorChatId.Value);
end;

{ TTgSendStickerOptions }

procedure TTgSendStickerOptions.ApplyTo(AParams: TTgParams);
begin
  if BusinessConnectionId.HasValue then
    AParams.Add('business_connection_id', BusinessConnectionId.Value);
  if MessageThreadId.HasValue then
    AParams.Add('message_thread_id', MessageThreadId.Value);
  if DirectMessagesTopicId.HasValue then
    AParams.Add('direct_messages_topic_id', DirectMessagesTopicId.Value);
  if System.Assigned(EphemeralMessageParameters) then
    AParams.AddJson('ephemeral_message_parameters', TTgDto.Serialize(EphemeralMessageParameters, AParams));
  if Emoji.HasValue then
    AParams.Add('emoji', Emoji.Value);
  if DisableNotification.HasValue then
    AParams.Add('disable_notification', DisableNotification.Value);
  if ProtectContent.HasValue then
    AParams.Add('protect_content', ProtectContent.Value);
  if AllowPaidBroadcast.HasValue then
    AParams.Add('allow_paid_broadcast', AllowPaidBroadcast.Value);
  if MessageEffectId.HasValue then
    AParams.Add('message_effect_id', MessageEffectId.Value);
  if System.Assigned(SuggestedPostParameters) then
    AParams.AddJson('suggested_post_parameters', TTgDto.Serialize(SuggestedPostParameters, AParams));
  if System.Assigned(ReplyParameters) then
    AParams.AddJson('reply_parameters', TTgDto.Serialize(ReplyParameters, AParams));
  if not ReplyMarkup.IsEmpty then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup.Value, AParams));
end;

{ TTgCreateNewStickerSetOptions }

procedure TTgCreateNewStickerSetOptions.ApplyTo(AParams: TTgParams);
begin
  if StickerType.HasValue then
    AParams.Add('sticker_type', StickerType.Value);
  if NeedsRepainting.HasValue then
    AParams.Add('needs_repainting', NeedsRepainting.Value);
end;

{ TTgSetStickerKeywordsOptions }

procedure TTgSetStickerKeywordsOptions.ApplyTo(AParams: TTgParams);
begin
  if Keywords.HasValue then
    AParams.AddStrings('keywords', Keywords.Value);
end;

{ TTgSetStickerMaskPositionOptions }

procedure TTgSetStickerMaskPositionOptions.ApplyTo(AParams: TTgParams);
begin
  if System.Assigned(MaskPosition) then
    AParams.AddJson('mask_position', TTgDto.Serialize(MaskPosition, AParams));
end;

{ TTgSetStickerSetThumbnailOptions }

procedure TTgSetStickerSetThumbnailOptions.ApplyTo(AParams: TTgParams);
begin
  if not Thumbnail.IsEmpty then
    AParams.AddFile('thumbnail', Thumbnail);
end;

{ TTgSetCustomEmojiStickerSetThumbnailOptions }

procedure TTgSetCustomEmojiStickerSetThumbnailOptions.ApplyTo(AParams: TTgParams);
begin
  if CustomEmojiId.HasValue then
    AParams.Add('custom_emoji_id', CustomEmojiId.Value);
end;

{ TTgSendRichMessageOptions }

procedure TTgSendRichMessageOptions.ApplyTo(AParams: TTgParams);
begin
  if BusinessConnectionId.HasValue then
    AParams.Add('business_connection_id', BusinessConnectionId.Value);
  if MessageThreadId.HasValue then
    AParams.Add('message_thread_id', MessageThreadId.Value);
  if DirectMessagesTopicId.HasValue then
    AParams.Add('direct_messages_topic_id', DirectMessagesTopicId.Value);
  if System.Assigned(EphemeralMessageParameters) then
    AParams.AddJson('ephemeral_message_parameters', TTgDto.Serialize(EphemeralMessageParameters, AParams));
  if DisableNotification.HasValue then
    AParams.Add('disable_notification', DisableNotification.Value);
  if ProtectContent.HasValue then
    AParams.Add('protect_content', ProtectContent.Value);
  if AllowPaidBroadcast.HasValue then
    AParams.Add('allow_paid_broadcast', AllowPaidBroadcast.Value);
  if MessageEffectId.HasValue then
    AParams.Add('message_effect_id', MessageEffectId.Value);
  if System.Assigned(SuggestedPostParameters) then
    AParams.AddJson('suggested_post_parameters', TTgDto.Serialize(SuggestedPostParameters, AParams));
  if System.Assigned(ReplyParameters) then
    AParams.AddJson('reply_parameters', TTgDto.Serialize(ReplyParameters, AParams));
  if not ReplyMarkup.IsEmpty then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup.Value, AParams));
end;

{ TTgSendRichMessageDraftOptions }

procedure TTgSendRichMessageDraftOptions.ApplyTo(AParams: TTgParams);
begin
  if MessageThreadId.HasValue then
    AParams.Add('message_thread_id', MessageThreadId.Value);
  if CanStop.HasValue then
    AParams.Add('can_stop', CanStop.Value);
  if KeepOnStop.HasValue then
    AParams.Add('keep_on_stop', KeepOnStop.Value);
end;

{ TTgAnswerInlineQueryOptions }

procedure TTgAnswerInlineQueryOptions.ApplyTo(AParams: TTgParams);
begin
  if CacheTime.HasValue then
    AParams.Add('cache_time', CacheTime.Value);
  if IsPersonal.HasValue then
    AParams.Add('is_personal', IsPersonal.Value);
  if NextOffset.HasValue then
    AParams.Add('next_offset', NextOffset.Value);
  if System.Assigned(Button) then
    AParams.AddJson('button', TTgDto.Serialize(Button, AParams));
end;

{ TTgSendInvoiceOptions }

procedure TTgSendInvoiceOptions.ApplyTo(AParams: TTgParams);
begin
  if MessageThreadId.HasValue then
    AParams.Add('message_thread_id', MessageThreadId.Value);
  if DirectMessagesTopicId.HasValue then
    AParams.Add('direct_messages_topic_id', DirectMessagesTopicId.Value);
  if ProviderToken.HasValue then
    AParams.Add('provider_token', ProviderToken.Value);
  if MaxTipAmount.HasValue then
    AParams.Add('max_tip_amount', MaxTipAmount.Value);
  if SuggestedTipAmounts.HasValue then
    AParams.AddJson('suggested_tip_amounts', TTgDto.IntegersJson(SuggestedTipAmounts.Value));
  if StartParameter.HasValue then
    AParams.Add('start_parameter', StartParameter.Value);
  if ProviderData.HasValue then
    AParams.Add('provider_data', ProviderData.Value);
  if PhotoUrl.HasValue then
    AParams.Add('photo_url', PhotoUrl.Value);
  if PhotoSize.HasValue then
    AParams.Add('photo_size', PhotoSize.Value);
  if PhotoWidth.HasValue then
    AParams.Add('photo_width', PhotoWidth.Value);
  if PhotoHeight.HasValue then
    AParams.Add('photo_height', PhotoHeight.Value);
  if NeedName.HasValue then
    AParams.Add('need_name', NeedName.Value);
  if NeedPhoneNumber.HasValue then
    AParams.Add('need_phone_number', NeedPhoneNumber.Value);
  if NeedEmail.HasValue then
    AParams.Add('need_email', NeedEmail.Value);
  if NeedShippingAddress.HasValue then
    AParams.Add('need_shipping_address', NeedShippingAddress.Value);
  if SendPhoneNumberToProvider.HasValue then
    AParams.Add('send_phone_number_to_provider', SendPhoneNumberToProvider.Value);
  if SendEmailToProvider.HasValue then
    AParams.Add('send_email_to_provider', SendEmailToProvider.Value);
  if IsFlexible.HasValue then
    AParams.Add('is_flexible', IsFlexible.Value);
  if DisableNotification.HasValue then
    AParams.Add('disable_notification', DisableNotification.Value);
  if ProtectContent.HasValue then
    AParams.Add('protect_content', ProtectContent.Value);
  if AllowPaidBroadcast.HasValue then
    AParams.Add('allow_paid_broadcast', AllowPaidBroadcast.Value);
  if MessageEffectId.HasValue then
    AParams.Add('message_effect_id', MessageEffectId.Value);
  if System.Assigned(SuggestedPostParameters) then
    AParams.AddJson('suggested_post_parameters', TTgDto.Serialize(SuggestedPostParameters, AParams));
  if System.Assigned(ReplyParameters) then
    AParams.AddJson('reply_parameters', TTgDto.Serialize(ReplyParameters, AParams));
  if System.Assigned(ReplyMarkup) then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup, AParams));
end;

{ TTgCreateInvoiceLinkOptions }

procedure TTgCreateInvoiceLinkOptions.ApplyTo(AParams: TTgParams);
begin
  if BusinessConnectionId.HasValue then
    AParams.Add('business_connection_id', BusinessConnectionId.Value);
  if ProviderToken.HasValue then
    AParams.Add('provider_token', ProviderToken.Value);
  if SubscriptionPeriod.HasValue then
    AParams.Add('subscription_period', SubscriptionPeriod.Value);
  if MaxTipAmount.HasValue then
    AParams.Add('max_tip_amount', MaxTipAmount.Value);
  if SuggestedTipAmounts.HasValue then
    AParams.AddJson('suggested_tip_amounts', TTgDto.IntegersJson(SuggestedTipAmounts.Value));
  if ProviderData.HasValue then
    AParams.Add('provider_data', ProviderData.Value);
  if PhotoUrl.HasValue then
    AParams.Add('photo_url', PhotoUrl.Value);
  if PhotoSize.HasValue then
    AParams.Add('photo_size', PhotoSize.Value);
  if PhotoWidth.HasValue then
    AParams.Add('photo_width', PhotoWidth.Value);
  if PhotoHeight.HasValue then
    AParams.Add('photo_height', PhotoHeight.Value);
  if NeedName.HasValue then
    AParams.Add('need_name', NeedName.Value);
  if NeedPhoneNumber.HasValue then
    AParams.Add('need_phone_number', NeedPhoneNumber.Value);
  if NeedEmail.HasValue then
    AParams.Add('need_email', NeedEmail.Value);
  if NeedShippingAddress.HasValue then
    AParams.Add('need_shipping_address', NeedShippingAddress.Value);
  if SendPhoneNumberToProvider.HasValue then
    AParams.Add('send_phone_number_to_provider', SendPhoneNumberToProvider.Value);
  if SendEmailToProvider.HasValue then
    AParams.Add('send_email_to_provider', SendEmailToProvider.Value);
  if IsFlexible.HasValue then
    AParams.Add('is_flexible', IsFlexible.Value);
end;

{ TTgAnswerShippingQueryOptions }

procedure TTgAnswerShippingQueryOptions.ApplyTo(AParams: TTgParams);
begin
  if ShippingOptions.HasValue then
    AParams.AddJson('shipping_options', TTgDto.SerializeArray(TTgDto.ToIntf<ITgShippingOption>(ShippingOptions.Value), AParams, 'shipping_options'));
  if ErrorMessage.HasValue then
    AParams.Add('error_message', ErrorMessage.Value);
end;

{ TTgAnswerPreCheckoutQueryOptions }

procedure TTgAnswerPreCheckoutQueryOptions.ApplyTo(AParams: TTgParams);
begin
  if ErrorMessage.HasValue then
    AParams.Add('error_message', ErrorMessage.Value);
end;

{ TTgGetStarTransactionsOptions }

procedure TTgGetStarTransactionsOptions.ApplyTo(AParams: TTgParams);
begin
  if Offset.HasValue then
    AParams.Add('offset', Offset.Value);
  if Limit.HasValue then
    AParams.Add('limit', Limit.Value);
end;

{ TTgSendGameOptions }

procedure TTgSendGameOptions.ApplyTo(AParams: TTgParams);
begin
  if BusinessConnectionId.HasValue then
    AParams.Add('business_connection_id', BusinessConnectionId.Value);
  if MessageThreadId.HasValue then
    AParams.Add('message_thread_id', MessageThreadId.Value);
  if DisableNotification.HasValue then
    AParams.Add('disable_notification', DisableNotification.Value);
  if ProtectContent.HasValue then
    AParams.Add('protect_content', ProtectContent.Value);
  if AllowPaidBroadcast.HasValue then
    AParams.Add('allow_paid_broadcast', AllowPaidBroadcast.Value);
  if MessageEffectId.HasValue then
    AParams.Add('message_effect_id', MessageEffectId.Value);
  if System.Assigned(ReplyParameters) then
    AParams.AddJson('reply_parameters', TTgDto.Serialize(ReplyParameters, AParams));
  if System.Assigned(ReplyMarkup) then
    AParams.AddJson('reply_markup', TTgDto.Serialize(ReplyMarkup, AParams));
end;

{ TTgSetGameScoreOptions }

procedure TTgSetGameScoreOptions.ApplyTo(AParams: TTgParams);
begin
  if Force.HasValue then
    AParams.Add('force', Force.Value);
  if DisableEditMessage.HasValue then
    AParams.Add('disable_edit_message', DisableEditMessage.Value);
  if ChatId.HasValue then
    AParams.Add('chat_id', ChatId.Value);
  if MessageId.HasValue then
    AParams.Add('message_id', MessageId.Value);
  if InlineMessageId.HasValue then
    AParams.Add('inline_message_id', InlineMessageId.Value);
end;

{ TTgGetGameHighScoresOptions }

procedure TTgGetGameHighScoresOptions.ApplyTo(AParams: TTgParams);
begin
  if ChatId.HasValue then
    AParams.Add('chat_id', ChatId.Value);
  if MessageId.HasValue then
    AParams.Add('message_id', MessageId.Value);
  if InlineMessageId.HasValue then
    AParams.Add('inline_message_id', InlineMessageId.Value);
end;

{ TTgApi }

function TTgApi.BuildGetUpdatesParams(const AOptions: TTgGetUpdatesOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecGetUpdates(AParams: TTgParams): TArray<ITgUpdate>;
var
  LValue: TJSONValue;
begin
  LValue := Call('getUpdates', AParams);
  Result := TTgDto.ResultArray<ITgUpdate>(LValue, 'getUpdates', TgMakeUpdate);
end;

function TTgApi.GetUpdates(const AOptions: TTgGetUpdatesOptions): TArray<ITgUpdate>;
var
  LParams: TTgParams;
begin
  LParams := BuildGetUpdatesParams(AOptions);
  try
    Result := ExecGetUpdates(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.GetUpdates: TArray<ITgUpdate>;
begin
  Result := GetUpdates(Default(TTgGetUpdatesOptions));
end;

function TTgApi.GetUpdatesAsync(const AOptions: TTgGetUpdatesOptions;
  const AOnSuccess: TProc<TArray<ITgUpdate>>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<TArray<ITgUpdate>>;
begin
  LExec := ExecGetUpdates;
  Result := RunAsyncCall<TArray<ITgUpdate>>(BuildGetUpdatesParams(AOptions), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.GetUpdatesAsync(const AOnSuccess: TProc<TArray<ITgUpdate>>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := GetUpdatesAsync(Default(TTgGetUpdatesOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryGetUpdates(const AOptions: TTgGetUpdatesOptions; out AResult: TArray<ITgUpdate>;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(TArray<ITgUpdate>);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetUpdates(AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryGetUpdates(out AResult: TArray<ITgUpdate>; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryGetUpdates(Default(TTgGetUpdatesOptions), AResult, AError);
end;

function TTgApi.BuildSetWebhookParams(const AUrl: string;
  const AOptions: TTgSetWebhookOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('url', AUrl);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetWebhook(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setWebhook', AParams);
  Result := TTgDto.ResultBool(LValue, 'setWebhook');
end;

function TTgApi.SetWebhook(const AUrl: string; const AOptions: TTgSetWebhookOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetWebhookParams(AUrl, AOptions);
  try
    Result := ExecSetWebhook(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetWebhook(const AUrl: string): Boolean;
begin
  Result := SetWebhook(AUrl, Default(TTgSetWebhookOptions));
end;

function TTgApi.SetWebhookAsync(const AUrl: string; const AOptions: TTgSetWebhookOptions;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetWebhook;
  Result := RunAsyncCall<Boolean>(BuildSetWebhookParams(AUrl, AOptions), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.SetWebhookAsync(const AUrl: string; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := SetWebhookAsync(AUrl, Default(TTgSetWebhookOptions), AOnSuccess, AOnError);
end;

function TTgApi.TrySetWebhook(const AUrl: string; const AOptions: TTgSetWebhookOptions;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetWebhook(AUrl, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySetWebhook(const AUrl: string; out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySetWebhook(AUrl, Default(TTgSetWebhookOptions), AError);
end;

function TTgApi.BuildDeleteWebhookParams(const AOptions: TTgDeleteWebhookOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecDeleteWebhook(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('deleteWebhook', AParams);
  Result := TTgDto.ResultBool(LValue, 'deleteWebhook');
end;

function TTgApi.DeleteWebhook(const AOptions: TTgDeleteWebhookOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildDeleteWebhookParams(AOptions);
  try
    Result := ExecDeleteWebhook(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.DeleteWebhook: Boolean;
begin
  Result := DeleteWebhook(Default(TTgDeleteWebhookOptions));
end;

function TTgApi.DeleteWebhookAsync(const AOptions: TTgDeleteWebhookOptions;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecDeleteWebhook;
  Result := RunAsyncCall<Boolean>(BuildDeleteWebhookParams(AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.DeleteWebhookAsync(const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := DeleteWebhookAsync(Default(TTgDeleteWebhookOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryDeleteWebhook(const AOptions: TTgDeleteWebhookOptions;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    DeleteWebhook(AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryDeleteWebhook(out AError: TTgErrorInfo): Boolean;
begin
  Result := TryDeleteWebhook(Default(TTgDeleteWebhookOptions), AError);
end;

function TTgApi.ExecGetWebhookInfo(AParams: TTgParams): ITgWebhookInfo;
var
  LValue: TJSONValue;
begin
  LValue := Call('getWebhookInfo', AParams);
  Result := TTgDto.ResultObject<ITgWebhookInfo>(LValue, 'getWebhookInfo', TgMakeWebhookInfo);
end;

function TTgApi.GetWebhookInfo: ITgWebhookInfo;
begin
  Result := ExecGetWebhookInfo(nil);
end;

function TTgApi.GetWebhookInfoAsync(const AOnSuccess: TProc<ITgWebhookInfo>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgWebhookInfo>;
begin
  LExec := ExecGetWebhookInfo;
  Result := RunAsyncCall<ITgWebhookInfo>(nil, LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryGetWebhookInfo(out AResult: ITgWebhookInfo; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgWebhookInfo);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetWebhookInfo;
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.ExecGetMe(AParams: TTgParams): ITgUser;
var
  LValue: TJSONValue;
begin
  LValue := Call('getMe', AParams);
  Result := TTgDto.ResultObject<ITgUser>(LValue, 'getMe', TgMakeUser);
end;

function TTgApi.GetMe: ITgUser;
begin
  Result := ExecGetMe(nil);
end;

function TTgApi.GetMeAsync(const AOnSuccess: TProc<ITgUser>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgUser>;
begin
  LExec := ExecGetMe;
  Result := RunAsyncCall<ITgUser>(nil, LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryGetMe(out AResult: ITgUser; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgUser);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetMe;
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.ExecLogOut(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('logOut', AParams);
  Result := TTgDto.ResultBool(LValue, 'logOut');
end;

function TTgApi.LogOut: Boolean;
begin
  Result := ExecLogOut(nil);
end;

function TTgApi.LogOutAsync(const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecLogOut;
  Result := RunAsyncCall<Boolean>(nil, LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryLogOut(out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    LogOut;
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.ExecClose(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('close', AParams);
  Result := TTgDto.ResultBool(LValue, 'close');
end;

function TTgApi.Close: Boolean;
begin
  Result := ExecClose(nil);
end;

function TTgApi.CloseAsync(const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecClose;
  Result := RunAsyncCall<Boolean>(nil, LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryClose(out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    Close;
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildSendMessageParams(const AChatId: TTgChatId; const AText: string;
  const AOptions: TTgSendMessageOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('text', AText);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSendMessage(AParams: TTgParams): ITgMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('sendMessage', AParams);
  Result := TTgDto.ResultObject<ITgMessage>(LValue, 'sendMessage', TgMakeMessage);
end;

function TTgApi.SendMessage(const AChatId: TTgChatId; const AText: string;
  const AOptions: TTgSendMessageOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildSendMessageParams(AChatId, AText, AOptions);
  try
    Result := ExecSendMessage(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SendMessage(const AChatId: TTgChatId; const AText: string): ITgMessage;
begin
  Result := SendMessage(AChatId, AText, Default(TTgSendMessageOptions));
end;

function TTgApi.SendMessageAsync(const AChatId: TTgChatId; const AText: string;
  const AOptions: TTgSendMessageOptions; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecSendMessage;
  Result := RunAsyncCall<ITgMessage>(BuildSendMessageParams(AChatId, AText, AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.SendMessageAsync(const AChatId: TTgChatId; const AText: string;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
begin
  Result := SendMessageAsync(AChatId, AText, Default(TTgSendMessageOptions), AOnSuccess, AOnError);
end;

function TTgApi.TrySendMessage(const AChatId: TTgChatId; const AText: string;
  const AOptions: TTgSendMessageOptions; out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := SendMessage(AChatId, AText, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySendMessage(const AChatId: TTgChatId; const AText: string;
  out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySendMessage(AChatId, AText, Default(TTgSendMessageOptions), AResult, AError);
end;

function TTgApi.BuildSendMessageVariant1Params(const AChatId: TTgChatId; const AText: string;
  const AReplyMarkup: TTgReplyMarkup; const AOptions: TTgSendMessageOptions): TTgParams;
var
  LOptions: TTgSendMessageOptions;
begin
  LOptions := AOptions;
  LOptions.ReplyMarkup := AReplyMarkup;
  Result := BuildSendMessageParams(AChatId, AText, LOptions);
end;

function TTgApi.SendMessage(const AChatId: TTgChatId; const AText: string;
  const AReplyMarkup: TTgReplyMarkup; const AOptions: TTgSendMessageOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildSendMessageVariant1Params(AChatId, AText, AReplyMarkup, AOptions);
  try
    Result := ExecSendMessage(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SendMessage(const AChatId: TTgChatId; const AText: string;
  const AReplyMarkup: TTgReplyMarkup): ITgMessage;
begin
  Result := SendMessage(AChatId, AText, AReplyMarkup, Default(TTgSendMessageOptions));
end;

function TTgApi.SendMessageAsync(const AChatId: TTgChatId; const AText: string;
  const AReplyMarkup: TTgReplyMarkup; const AOptions: TTgSendMessageOptions;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecSendMessage;
  Result := RunAsyncCall<ITgMessage>(BuildSendMessageVariant1Params(AChatId, AText, AReplyMarkup, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.SendMessageAsync(const AChatId: TTgChatId; const AText: string;
  const AReplyMarkup: TTgReplyMarkup; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := SendMessageAsync(AChatId, AText, AReplyMarkup, Default(TTgSendMessageOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TrySendMessage(const AChatId: TTgChatId; const AText: string;
  const AReplyMarkup: TTgReplyMarkup; const AOptions: TTgSendMessageOptions;
  out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := SendMessage(AChatId, AText, AReplyMarkup, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySendMessage(const AChatId: TTgChatId; const AText: string;
  const AReplyMarkup: TTgReplyMarkup; out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySendMessage(AChatId, AText, AReplyMarkup, Default(TTgSendMessageOptions), AResult,
  AError);
end;

function TTgApi.BuildForwardMessageParams(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
  AMessageId: Int64; const AOptions: TTgForwardMessageOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.AddChatId('from_chat_id', AFromChatId);
    Result.Add('message_id', AMessageId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecForwardMessage(AParams: TTgParams): ITgMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('forwardMessage', AParams);
  Result := TTgDto.ResultObject<ITgMessage>(LValue, 'forwardMessage', TgMakeMessage);
end;

function TTgApi.ForwardMessage(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
  AMessageId: Int64; const AOptions: TTgForwardMessageOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildForwardMessageParams(AChatId, AFromChatId, AMessageId, AOptions);
  try
    Result := ExecForwardMessage(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.ForwardMessage(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
  AMessageId: Int64): ITgMessage;
begin
  Result := ForwardMessage(AChatId, AFromChatId, AMessageId, Default(TTgForwardMessageOptions));
end;

function TTgApi.ForwardMessageAsync(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
  AMessageId: Int64; const AOptions: TTgForwardMessageOptions; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecForwardMessage;
  Result := RunAsyncCall<ITgMessage>(BuildForwardMessageParams(AChatId, AFromChatId, AMessageId, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.ForwardMessageAsync(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
  AMessageId: Int64; const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
begin
  Result := ForwardMessageAsync(AChatId, AFromChatId, AMessageId, Default(TTgForwardMessageOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TryForwardMessage(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
  AMessageId: Int64; const AOptions: TTgForwardMessageOptions; out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := ForwardMessage(AChatId, AFromChatId, AMessageId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryForwardMessage(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
  AMessageId: Int64; out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryForwardMessage(AChatId, AFromChatId, AMessageId, Default(TTgForwardMessageOptions),
  AResult, AError);
end;

function TTgApi.BuildForwardMessagesParams(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
  const AMessageIds: TArray<Int64>; const AOptions: TTgForwardMessagesOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.AddChatId('from_chat_id', AFromChatId);
    Result.AddInt64s('message_ids', AMessageIds);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecForwardMessages(AParams: TTgParams): TArray<ITgMessageId>;
var
  LValue: TJSONValue;
begin
  LValue := Call('forwardMessages', AParams);
  Result := TTgDto.ResultArray<ITgMessageId>(LValue, 'forwardMessages', TgMakeMessageId);
end;

function TTgApi.ForwardMessages(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
  const AMessageIds: TArray<Int64>;
  const AOptions: TTgForwardMessagesOptions): TArray<ITgMessageId>;
var
  LParams: TTgParams;
begin
  LParams := BuildForwardMessagesParams(AChatId, AFromChatId, AMessageIds, AOptions);
  try
    Result := ExecForwardMessages(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.ForwardMessages(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
  const AMessageIds: TArray<Int64>): TArray<ITgMessageId>;
begin
  Result := ForwardMessages(AChatId, AFromChatId, AMessageIds, Default(TTgForwardMessagesOptions));
end;

function TTgApi.ForwardMessagesAsync(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
  const AMessageIds: TArray<Int64>; const AOptions: TTgForwardMessagesOptions;
  const AOnSuccess: TProc<TArray<ITgMessageId>>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<TArray<ITgMessageId>>;
begin
  LExec := ExecForwardMessages;
  Result := RunAsyncCall<TArray<ITgMessageId>>(BuildForwardMessagesParams(AChatId, AFromChatId, AMessageIds, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.ForwardMessagesAsync(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
  const AMessageIds: TArray<Int64>; const AOnSuccess: TProc<TArray<ITgMessageId>>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := ForwardMessagesAsync(AChatId, AFromChatId, AMessageIds,
  Default(TTgForwardMessagesOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryForwardMessages(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
  const AMessageIds: TArray<Int64>; const AOptions: TTgForwardMessagesOptions;
  out AResult: TArray<ITgMessageId>; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(TArray<ITgMessageId>);
  AError := TTgErrorInfo.Empty;
  try
    AResult := ForwardMessages(AChatId, AFromChatId, AMessageIds, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryForwardMessages(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
  const AMessageIds: TArray<Int64>; out AResult: TArray<ITgMessageId>;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryForwardMessages(AChatId, AFromChatId, AMessageIds,
  Default(TTgForwardMessagesOptions), AResult, AError);
end;

function TTgApi.BuildCopyMessageParams(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
  AMessageId: Int64; const AOptions: TTgCopyMessageOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.AddChatId('from_chat_id', AFromChatId);
    Result.Add('message_id', AMessageId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecCopyMessage(AParams: TTgParams): ITgMessageId;
var
  LValue: TJSONValue;
begin
  LValue := Call('copyMessage', AParams);
  Result := TTgDto.ResultObject<ITgMessageId>(LValue, 'copyMessage', TgMakeMessageId);
end;

function TTgApi.CopyMessage(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
  AMessageId: Int64; const AOptions: TTgCopyMessageOptions): ITgMessageId;
var
  LParams: TTgParams;
begin
  LParams := BuildCopyMessageParams(AChatId, AFromChatId, AMessageId, AOptions);
  try
    Result := ExecCopyMessage(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.CopyMessage(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
  AMessageId: Int64): ITgMessageId;
begin
  Result := CopyMessage(AChatId, AFromChatId, AMessageId, Default(TTgCopyMessageOptions));
end;

function TTgApi.CopyMessageAsync(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
  AMessageId: Int64; const AOptions: TTgCopyMessageOptions; const AOnSuccess: TProc<ITgMessageId>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessageId>;
begin
  LExec := ExecCopyMessage;
  Result := RunAsyncCall<ITgMessageId>(BuildCopyMessageParams(AChatId, AFromChatId, AMessageId, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.CopyMessageAsync(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
  AMessageId: Int64; const AOnSuccess: TProc<ITgMessageId>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := CopyMessageAsync(AChatId, AFromChatId, AMessageId, Default(TTgCopyMessageOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TryCopyMessage(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
  AMessageId: Int64; const AOptions: TTgCopyMessageOptions; out AResult: ITgMessageId;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessageId);
  AError := TTgErrorInfo.Empty;
  try
    AResult := CopyMessage(AChatId, AFromChatId, AMessageId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryCopyMessage(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
  AMessageId: Int64; out AResult: ITgMessageId; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryCopyMessage(AChatId, AFromChatId, AMessageId, Default(TTgCopyMessageOptions),
  AResult, AError);
end;

function TTgApi.BuildCopyMessagesParams(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
  const AMessageIds: TArray<Int64>; const AOptions: TTgCopyMessagesOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.AddChatId('from_chat_id', AFromChatId);
    Result.AddInt64s('message_ids', AMessageIds);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecCopyMessages(AParams: TTgParams): TArray<ITgMessageId>;
var
  LValue: TJSONValue;
begin
  LValue := Call('copyMessages', AParams);
  Result := TTgDto.ResultArray<ITgMessageId>(LValue, 'copyMessages', TgMakeMessageId);
end;

function TTgApi.CopyMessages(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
  const AMessageIds: TArray<Int64>; const AOptions: TTgCopyMessagesOptions): TArray<ITgMessageId>;
var
  LParams: TTgParams;
begin
  LParams := BuildCopyMessagesParams(AChatId, AFromChatId, AMessageIds, AOptions);
  try
    Result := ExecCopyMessages(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.CopyMessages(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
  const AMessageIds: TArray<Int64>): TArray<ITgMessageId>;
begin
  Result := CopyMessages(AChatId, AFromChatId, AMessageIds, Default(TTgCopyMessagesOptions));
end;

function TTgApi.CopyMessagesAsync(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
  const AMessageIds: TArray<Int64>; const AOptions: TTgCopyMessagesOptions;
  const AOnSuccess: TProc<TArray<ITgMessageId>>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<TArray<ITgMessageId>>;
begin
  LExec := ExecCopyMessages;
  Result := RunAsyncCall<TArray<ITgMessageId>>(BuildCopyMessagesParams(AChatId, AFromChatId, AMessageIds, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.CopyMessagesAsync(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
  const AMessageIds: TArray<Int64>; const AOnSuccess: TProc<TArray<ITgMessageId>>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := CopyMessagesAsync(AChatId, AFromChatId, AMessageIds, Default(TTgCopyMessagesOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TryCopyMessages(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
  const AMessageIds: TArray<Int64>; const AOptions: TTgCopyMessagesOptions;
  out AResult: TArray<ITgMessageId>; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(TArray<ITgMessageId>);
  AError := TTgErrorInfo.Empty;
  try
    AResult := CopyMessages(AChatId, AFromChatId, AMessageIds, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryCopyMessages(const AChatId: TTgChatId; const AFromChatId: TTgChatId;
  const AMessageIds: TArray<Int64>; out AResult: TArray<ITgMessageId>;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryCopyMessages(AChatId, AFromChatId, AMessageIds, Default(TTgCopyMessagesOptions),
  AResult, AError);
end;

function TTgApi.BuildSendPhotoParams(const AChatId: TTgChatId; const APhoto: TTgInputFile;
  const AOptions: TTgSendPhotoOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.AddFile('photo', APhoto);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSendPhoto(AParams: TTgParams): ITgMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('sendPhoto', AParams);
  Result := TTgDto.ResultObject<ITgMessage>(LValue, 'sendPhoto', TgMakeMessage);
end;

function TTgApi.SendPhoto(const AChatId: TTgChatId; const APhoto: TTgInputFile;
  const AOptions: TTgSendPhotoOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildSendPhotoParams(AChatId, APhoto, AOptions);
  try
    Result := ExecSendPhoto(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SendPhoto(const AChatId: TTgChatId; const APhoto: TTgInputFile): ITgMessage;
begin
  Result := SendPhoto(AChatId, APhoto, Default(TTgSendPhotoOptions));
end;

function TTgApi.SendPhotoAsync(const AChatId: TTgChatId; const APhoto: TTgInputFile;
  const AOptions: TTgSendPhotoOptions; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecSendPhoto;
  Result := RunAsyncCall<ITgMessage>(BuildSendPhotoParams(AChatId, APhoto, AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.SendPhotoAsync(const AChatId: TTgChatId; const APhoto: TTgInputFile;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
begin
  Result := SendPhotoAsync(AChatId, APhoto, Default(TTgSendPhotoOptions), AOnSuccess, AOnError);
end;

function TTgApi.TrySendPhoto(const AChatId: TTgChatId; const APhoto: TTgInputFile;
  const AOptions: TTgSendPhotoOptions; out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := SendPhoto(AChatId, APhoto, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySendPhoto(const AChatId: TTgChatId; const APhoto: TTgInputFile;
  out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySendPhoto(AChatId, APhoto, Default(TTgSendPhotoOptions), AResult, AError);
end;

function TTgApi.BuildSendPhotoVariant1Params(const AChatId: TTgChatId; const APhoto: TTgInputFile;
  const ACaption: string; const AOptions: TTgSendPhotoOptions): TTgParams;
var
  LOptions: TTgSendPhotoOptions;
begin
  LOptions := AOptions;
  LOptions.Caption := ACaption;
  Result := BuildSendPhotoParams(AChatId, APhoto, LOptions);
end;

function TTgApi.SendPhoto(const AChatId: TTgChatId; const APhoto: TTgInputFile;
  const ACaption: string; const AOptions: TTgSendPhotoOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildSendPhotoVariant1Params(AChatId, APhoto, ACaption, AOptions);
  try
    Result := ExecSendPhoto(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SendPhoto(const AChatId: TTgChatId; const APhoto: TTgInputFile;
  const ACaption: string): ITgMessage;
begin
  Result := SendPhoto(AChatId, APhoto, ACaption, Default(TTgSendPhotoOptions));
end;

function TTgApi.SendPhotoAsync(const AChatId: TTgChatId; const APhoto: TTgInputFile;
  const ACaption: string; const AOptions: TTgSendPhotoOptions; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecSendPhoto;
  Result := RunAsyncCall<ITgMessage>(BuildSendPhotoVariant1Params(AChatId, APhoto, ACaption, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.SendPhotoAsync(const AChatId: TTgChatId; const APhoto: TTgInputFile;
  const ACaption: string; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := SendPhotoAsync(AChatId, APhoto, ACaption, Default(TTgSendPhotoOptions), AOnSuccess,
  AOnError);
end;

function TTgApi.TrySendPhoto(const AChatId: TTgChatId; const APhoto: TTgInputFile;
  const ACaption: string; const AOptions: TTgSendPhotoOptions; out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := SendPhoto(AChatId, APhoto, ACaption, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySendPhoto(const AChatId: TTgChatId; const APhoto: TTgInputFile;
  const ACaption: string; out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySendPhoto(AChatId, APhoto, ACaption, Default(TTgSendPhotoOptions), AResult, AError);
end;

function TTgApi.BuildSendLivePhotoParams(const AChatId: TTgChatId; const ALivePhoto: TTgInputFile;
  const APhoto: TTgInputFile; const AOptions: TTgSendLivePhotoOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.AddFile('live_photo', ALivePhoto);
    Result.AddFile('photo', APhoto);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSendLivePhoto(AParams: TTgParams): ITgMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('sendLivePhoto', AParams);
  Result := TTgDto.ResultObject<ITgMessage>(LValue, 'sendLivePhoto', TgMakeMessage);
end;

function TTgApi.SendLivePhoto(const AChatId: TTgChatId; const ALivePhoto: TTgInputFile;
  const APhoto: TTgInputFile; const AOptions: TTgSendLivePhotoOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildSendLivePhotoParams(AChatId, ALivePhoto, APhoto, AOptions);
  try
    Result := ExecSendLivePhoto(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SendLivePhoto(const AChatId: TTgChatId; const ALivePhoto: TTgInputFile;
  const APhoto: TTgInputFile): ITgMessage;
begin
  Result := SendLivePhoto(AChatId, ALivePhoto, APhoto, Default(TTgSendLivePhotoOptions));
end;

function TTgApi.SendLivePhotoAsync(const AChatId: TTgChatId; const ALivePhoto: TTgInputFile;
  const APhoto: TTgInputFile; const AOptions: TTgSendLivePhotoOptions;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecSendLivePhoto;
  Result := RunAsyncCall<ITgMessage>(BuildSendLivePhotoParams(AChatId, ALivePhoto, APhoto, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.SendLivePhotoAsync(const AChatId: TTgChatId; const ALivePhoto: TTgInputFile;
  const APhoto: TTgInputFile; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := SendLivePhotoAsync(AChatId, ALivePhoto, APhoto, Default(TTgSendLivePhotoOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TrySendLivePhoto(const AChatId: TTgChatId; const ALivePhoto: TTgInputFile;
  const APhoto: TTgInputFile; const AOptions: TTgSendLivePhotoOptions; out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := SendLivePhoto(AChatId, ALivePhoto, APhoto, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySendLivePhoto(const AChatId: TTgChatId; const ALivePhoto: TTgInputFile;
  const APhoto: TTgInputFile; out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySendLivePhoto(AChatId, ALivePhoto, APhoto, Default(TTgSendLivePhotoOptions), AResult,
  AError);
end;

function TTgApi.BuildSendAudioParams(const AChatId: TTgChatId; const AAudio: TTgInputFile;
  const AOptions: TTgSendAudioOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.AddFile('audio', AAudio);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSendAudio(AParams: TTgParams): ITgMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('sendAudio', AParams);
  Result := TTgDto.ResultObject<ITgMessage>(LValue, 'sendAudio', TgMakeMessage);
end;

function TTgApi.SendAudio(const AChatId: TTgChatId; const AAudio: TTgInputFile;
  const AOptions: TTgSendAudioOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildSendAudioParams(AChatId, AAudio, AOptions);
  try
    Result := ExecSendAudio(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SendAudio(const AChatId: TTgChatId; const AAudio: TTgInputFile): ITgMessage;
begin
  Result := SendAudio(AChatId, AAudio, Default(TTgSendAudioOptions));
end;

function TTgApi.SendAudioAsync(const AChatId: TTgChatId; const AAudio: TTgInputFile;
  const AOptions: TTgSendAudioOptions; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecSendAudio;
  Result := RunAsyncCall<ITgMessage>(BuildSendAudioParams(AChatId, AAudio, AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.SendAudioAsync(const AChatId: TTgChatId; const AAudio: TTgInputFile;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
begin
  Result := SendAudioAsync(AChatId, AAudio, Default(TTgSendAudioOptions), AOnSuccess, AOnError);
end;

function TTgApi.TrySendAudio(const AChatId: TTgChatId; const AAudio: TTgInputFile;
  const AOptions: TTgSendAudioOptions; out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := SendAudio(AChatId, AAudio, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySendAudio(const AChatId: TTgChatId; const AAudio: TTgInputFile;
  out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySendAudio(AChatId, AAudio, Default(TTgSendAudioOptions), AResult, AError);
end;

function TTgApi.BuildSendDocumentParams(const AChatId: TTgChatId; const ADocument: TTgInputFile;
  const AOptions: TTgSendDocumentOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.AddFile('document', ADocument);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSendDocument(AParams: TTgParams): ITgMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('sendDocument', AParams);
  Result := TTgDto.ResultObject<ITgMessage>(LValue, 'sendDocument', TgMakeMessage);
end;

function TTgApi.SendDocument(const AChatId: TTgChatId; const ADocument: TTgInputFile;
  const AOptions: TTgSendDocumentOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildSendDocumentParams(AChatId, ADocument, AOptions);
  try
    Result := ExecSendDocument(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SendDocument(const AChatId: TTgChatId; const ADocument: TTgInputFile): ITgMessage;
begin
  Result := SendDocument(AChatId, ADocument, Default(TTgSendDocumentOptions));
end;

function TTgApi.SendDocumentAsync(const AChatId: TTgChatId; const ADocument: TTgInputFile;
  const AOptions: TTgSendDocumentOptions; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecSendDocument;
  Result := RunAsyncCall<ITgMessage>(BuildSendDocumentParams(AChatId, ADocument, AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.SendDocumentAsync(const AChatId: TTgChatId; const ADocument: TTgInputFile;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
begin
  Result := SendDocumentAsync(AChatId, ADocument, Default(TTgSendDocumentOptions), AOnSuccess,
  AOnError);
end;

function TTgApi.TrySendDocument(const AChatId: TTgChatId; const ADocument: TTgInputFile;
  const AOptions: TTgSendDocumentOptions; out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := SendDocument(AChatId, ADocument, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySendDocument(const AChatId: TTgChatId; const ADocument: TTgInputFile;
  out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySendDocument(AChatId, ADocument, Default(TTgSendDocumentOptions), AResult, AError);
end;

function TTgApi.BuildSendDocumentVariant1Params(const AChatId: TTgChatId;
  const ADocument: TTgInputFile; const ACaption: string;
  const AOptions: TTgSendDocumentOptions): TTgParams;
var
  LOptions: TTgSendDocumentOptions;
begin
  LOptions := AOptions;
  LOptions.Caption := ACaption;
  Result := BuildSendDocumentParams(AChatId, ADocument, LOptions);
end;

function TTgApi.SendDocument(const AChatId: TTgChatId; const ADocument: TTgInputFile;
  const ACaption: string; const AOptions: TTgSendDocumentOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildSendDocumentVariant1Params(AChatId, ADocument, ACaption, AOptions);
  try
    Result := ExecSendDocument(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SendDocument(const AChatId: TTgChatId; const ADocument: TTgInputFile;
  const ACaption: string): ITgMessage;
begin
  Result := SendDocument(AChatId, ADocument, ACaption, Default(TTgSendDocumentOptions));
end;

function TTgApi.SendDocumentAsync(const AChatId: TTgChatId; const ADocument: TTgInputFile;
  const ACaption: string; const AOptions: TTgSendDocumentOptions;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecSendDocument;
  Result := RunAsyncCall<ITgMessage>(BuildSendDocumentVariant1Params(AChatId, ADocument, ACaption, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.SendDocumentAsync(const AChatId: TTgChatId; const ADocument: TTgInputFile;
  const ACaption: string; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := SendDocumentAsync(AChatId, ADocument, ACaption, Default(TTgSendDocumentOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TrySendDocument(const AChatId: TTgChatId; const ADocument: TTgInputFile;
  const ACaption: string; const AOptions: TTgSendDocumentOptions; out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := SendDocument(AChatId, ADocument, ACaption, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySendDocument(const AChatId: TTgChatId; const ADocument: TTgInputFile;
  const ACaption: string; out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySendDocument(AChatId, ADocument, ACaption, Default(TTgSendDocumentOptions), AResult,
  AError);
end;

function TTgApi.BuildSendVideoParams(const AChatId: TTgChatId; const AVideo: TTgInputFile;
  const AOptions: TTgSendVideoOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.AddFile('video', AVideo);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSendVideo(AParams: TTgParams): ITgMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('sendVideo', AParams);
  Result := TTgDto.ResultObject<ITgMessage>(LValue, 'sendVideo', TgMakeMessage);
end;

function TTgApi.SendVideo(const AChatId: TTgChatId; const AVideo: TTgInputFile;
  const AOptions: TTgSendVideoOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildSendVideoParams(AChatId, AVideo, AOptions);
  try
    Result := ExecSendVideo(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SendVideo(const AChatId: TTgChatId; const AVideo: TTgInputFile): ITgMessage;
begin
  Result := SendVideo(AChatId, AVideo, Default(TTgSendVideoOptions));
end;

function TTgApi.SendVideoAsync(const AChatId: TTgChatId; const AVideo: TTgInputFile;
  const AOptions: TTgSendVideoOptions; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecSendVideo;
  Result := RunAsyncCall<ITgMessage>(BuildSendVideoParams(AChatId, AVideo, AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.SendVideoAsync(const AChatId: TTgChatId; const AVideo: TTgInputFile;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
begin
  Result := SendVideoAsync(AChatId, AVideo, Default(TTgSendVideoOptions), AOnSuccess, AOnError);
end;

function TTgApi.TrySendVideo(const AChatId: TTgChatId; const AVideo: TTgInputFile;
  const AOptions: TTgSendVideoOptions; out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := SendVideo(AChatId, AVideo, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySendVideo(const AChatId: TTgChatId; const AVideo: TTgInputFile;
  out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySendVideo(AChatId, AVideo, Default(TTgSendVideoOptions), AResult, AError);
end;

function TTgApi.BuildSendAnimationParams(const AChatId: TTgChatId; const AAnimation: TTgInputFile;
  const AOptions: TTgSendAnimationOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.AddFile('animation', AAnimation);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSendAnimation(AParams: TTgParams): ITgMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('sendAnimation', AParams);
  Result := TTgDto.ResultObject<ITgMessage>(LValue, 'sendAnimation', TgMakeMessage);
end;

function TTgApi.SendAnimation(const AChatId: TTgChatId; const AAnimation: TTgInputFile;
  const AOptions: TTgSendAnimationOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildSendAnimationParams(AChatId, AAnimation, AOptions);
  try
    Result := ExecSendAnimation(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SendAnimation(const AChatId: TTgChatId; const AAnimation: TTgInputFile): ITgMessage;
begin
  Result := SendAnimation(AChatId, AAnimation, Default(TTgSendAnimationOptions));
end;

function TTgApi.SendAnimationAsync(const AChatId: TTgChatId; const AAnimation: TTgInputFile;
  const AOptions: TTgSendAnimationOptions; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecSendAnimation;
  Result := RunAsyncCall<ITgMessage>(BuildSendAnimationParams(AChatId, AAnimation, AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.SendAnimationAsync(const AChatId: TTgChatId; const AAnimation: TTgInputFile;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
begin
  Result := SendAnimationAsync(AChatId, AAnimation, Default(TTgSendAnimationOptions), AOnSuccess,
  AOnError);
end;

function TTgApi.TrySendAnimation(const AChatId: TTgChatId; const AAnimation: TTgInputFile;
  const AOptions: TTgSendAnimationOptions; out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := SendAnimation(AChatId, AAnimation, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySendAnimation(const AChatId: TTgChatId; const AAnimation: TTgInputFile;
  out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySendAnimation(AChatId, AAnimation, Default(TTgSendAnimationOptions), AResult,
  AError);
end;

function TTgApi.BuildSendVoiceParams(const AChatId: TTgChatId; const AVoice: TTgInputFile;
  const AOptions: TTgSendVoiceOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.AddFile('voice', AVoice);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSendVoice(AParams: TTgParams): ITgMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('sendVoice', AParams);
  Result := TTgDto.ResultObject<ITgMessage>(LValue, 'sendVoice', TgMakeMessage);
end;

function TTgApi.SendVoice(const AChatId: TTgChatId; const AVoice: TTgInputFile;
  const AOptions: TTgSendVoiceOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildSendVoiceParams(AChatId, AVoice, AOptions);
  try
    Result := ExecSendVoice(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SendVoice(const AChatId: TTgChatId; const AVoice: TTgInputFile): ITgMessage;
begin
  Result := SendVoice(AChatId, AVoice, Default(TTgSendVoiceOptions));
end;

function TTgApi.SendVoiceAsync(const AChatId: TTgChatId; const AVoice: TTgInputFile;
  const AOptions: TTgSendVoiceOptions; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecSendVoice;
  Result := RunAsyncCall<ITgMessage>(BuildSendVoiceParams(AChatId, AVoice, AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.SendVoiceAsync(const AChatId: TTgChatId; const AVoice: TTgInputFile;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
begin
  Result := SendVoiceAsync(AChatId, AVoice, Default(TTgSendVoiceOptions), AOnSuccess, AOnError);
end;

function TTgApi.TrySendVoice(const AChatId: TTgChatId; const AVoice: TTgInputFile;
  const AOptions: TTgSendVoiceOptions; out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := SendVoice(AChatId, AVoice, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySendVoice(const AChatId: TTgChatId; const AVoice: TTgInputFile;
  out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySendVoice(AChatId, AVoice, Default(TTgSendVoiceOptions), AResult, AError);
end;

function TTgApi.BuildSendVideoNoteParams(const AChatId: TTgChatId; const AVideoNote: TTgInputFile;
  const AOptions: TTgSendVideoNoteOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.AddFile('video_note', AVideoNote);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSendVideoNote(AParams: TTgParams): ITgMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('sendVideoNote', AParams);
  Result := TTgDto.ResultObject<ITgMessage>(LValue, 'sendVideoNote', TgMakeMessage);
end;

function TTgApi.SendVideoNote(const AChatId: TTgChatId; const AVideoNote: TTgInputFile;
  const AOptions: TTgSendVideoNoteOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildSendVideoNoteParams(AChatId, AVideoNote, AOptions);
  try
    Result := ExecSendVideoNote(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SendVideoNote(const AChatId: TTgChatId; const AVideoNote: TTgInputFile): ITgMessage;
begin
  Result := SendVideoNote(AChatId, AVideoNote, Default(TTgSendVideoNoteOptions));
end;

function TTgApi.SendVideoNoteAsync(const AChatId: TTgChatId; const AVideoNote: TTgInputFile;
  const AOptions: TTgSendVideoNoteOptions; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecSendVideoNote;
  Result := RunAsyncCall<ITgMessage>(BuildSendVideoNoteParams(AChatId, AVideoNote, AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.SendVideoNoteAsync(const AChatId: TTgChatId; const AVideoNote: TTgInputFile;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
begin
  Result := SendVideoNoteAsync(AChatId, AVideoNote, Default(TTgSendVideoNoteOptions), AOnSuccess,
  AOnError);
end;

function TTgApi.TrySendVideoNote(const AChatId: TTgChatId; const AVideoNote: TTgInputFile;
  const AOptions: TTgSendVideoNoteOptions; out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := SendVideoNote(AChatId, AVideoNote, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySendVideoNote(const AChatId: TTgChatId; const AVideoNote: TTgInputFile;
  out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySendVideoNote(AChatId, AVideoNote, Default(TTgSendVideoNoteOptions), AResult,
  AError);
end;

function TTgApi.BuildSendPaidMediaParams(const AChatId: TTgChatId; AStarCount: Integer;
  const AMedia: array of TTgInputPaidMedia; const AOptions: TTgSendPaidMediaOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('star_count', AStarCount);
    Result.AddJson('media',
      TTgDto.SerializeArray(TTgInputPaidMedia.Values(AMedia), Result, 'media'));
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSendPaidMedia(AParams: TTgParams): ITgMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('sendPaidMedia', AParams);
  Result := TTgDto.ResultObject<ITgMessage>(LValue, 'sendPaidMedia', TgMakeMessage);
end;

function TTgApi.SendPaidMedia(const AChatId: TTgChatId; AStarCount: Integer;
  const AMedia: array of TTgInputPaidMedia; const AOptions: TTgSendPaidMediaOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildSendPaidMediaParams(AChatId, AStarCount, AMedia, AOptions);
  try
    Result := ExecSendPaidMedia(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SendPaidMedia(const AChatId: TTgChatId; AStarCount: Integer;
  const AMedia: array of TTgInputPaidMedia): ITgMessage;
begin
  Result := SendPaidMedia(AChatId, AStarCount, AMedia, Default(TTgSendPaidMediaOptions));
end;

function TTgApi.SendPaidMediaAsync(const AChatId: TTgChatId; AStarCount: Integer;
  const AMedia: array of TTgInputPaidMedia; const AOptions: TTgSendPaidMediaOptions;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecSendPaidMedia;
  Result := RunAsyncCall<ITgMessage>(BuildSendPaidMediaParams(AChatId, AStarCount, AMedia, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.SendPaidMediaAsync(const AChatId: TTgChatId; AStarCount: Integer;
  const AMedia: array of TTgInputPaidMedia; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := SendPaidMediaAsync(AChatId, AStarCount, AMedia, Default(TTgSendPaidMediaOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TrySendPaidMedia(const AChatId: TTgChatId; AStarCount: Integer;
  const AMedia: array of TTgInputPaidMedia; const AOptions: TTgSendPaidMediaOptions;
  out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := SendPaidMedia(AChatId, AStarCount, AMedia, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySendPaidMedia(const AChatId: TTgChatId; AStarCount: Integer;
  const AMedia: array of TTgInputPaidMedia; out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySendPaidMedia(AChatId, AStarCount, AMedia, Default(TTgSendPaidMediaOptions), AResult,
  AError);
end;

function TTgApi.BuildSendMediaGroupParams(const AChatId: TTgChatId;
  const AMedia: array of TTgMediaGroupItem; const AOptions: TTgSendMediaGroupOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.AddJson('media',
      TTgDto.SerializeArray(TTgMediaGroupItem.Values(AMedia), Result, 'media'));
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSendMediaGroup(AParams: TTgParams): TArray<ITgMessage>;
var
  LValue: TJSONValue;
begin
  LValue := Call('sendMediaGroup', AParams);
  Result := TTgDto.ResultArray<ITgMessage>(LValue, 'sendMediaGroup', TgMakeMessage);
end;

function TTgApi.SendMediaGroup(const AChatId: TTgChatId; const AMedia: array of TTgMediaGroupItem;
  const AOptions: TTgSendMediaGroupOptions): TArray<ITgMessage>;
var
  LParams: TTgParams;
begin
  LParams := BuildSendMediaGroupParams(AChatId, AMedia, AOptions);
  try
    Result := ExecSendMediaGroup(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SendMediaGroup(const AChatId: TTgChatId;
  const AMedia: array of TTgMediaGroupItem): TArray<ITgMessage>;
begin
  Result := SendMediaGroup(AChatId, AMedia, Default(TTgSendMediaGroupOptions));
end;

function TTgApi.SendMediaGroupAsync(const AChatId: TTgChatId;
  const AMedia: array of TTgMediaGroupItem; const AOptions: TTgSendMediaGroupOptions;
  const AOnSuccess: TProc<TArray<ITgMessage>>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<TArray<ITgMessage>>;
begin
  LExec := ExecSendMediaGroup;
  Result := RunAsyncCall<TArray<ITgMessage>>(BuildSendMediaGroupParams(AChatId, AMedia, AOptions),
    LExec, AOnSuccess, AOnError);
end;

function TTgApi.SendMediaGroupAsync(const AChatId: TTgChatId;
  const AMedia: array of TTgMediaGroupItem; const AOnSuccess: TProc<TArray<ITgMessage>>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := SendMediaGroupAsync(AChatId, AMedia, Default(TTgSendMediaGroupOptions), AOnSuccess,
  AOnError);
end;

function TTgApi.TrySendMediaGroup(const AChatId: TTgChatId;
  const AMedia: array of TTgMediaGroupItem; const AOptions: TTgSendMediaGroupOptions;
  out AResult: TArray<ITgMessage>; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(TArray<ITgMessage>);
  AError := TTgErrorInfo.Empty;
  try
    AResult := SendMediaGroup(AChatId, AMedia, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySendMediaGroup(const AChatId: TTgChatId;
  const AMedia: array of TTgMediaGroupItem; out AResult: TArray<ITgMessage>;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySendMediaGroup(AChatId, AMedia, Default(TTgSendMediaGroupOptions), AResult, AError);
end;

function TTgApi.BuildSendLocationParams(const AChatId: TTgChatId; ALatitude: Double;
  ALongitude: Double; const AOptions: TTgSendLocationOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('latitude', ALatitude);
    Result.Add('longitude', ALongitude);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSendLocation(AParams: TTgParams): ITgMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('sendLocation', AParams);
  Result := TTgDto.ResultObject<ITgMessage>(LValue, 'sendLocation', TgMakeMessage);
end;

function TTgApi.SendLocation(const AChatId: TTgChatId; ALatitude: Double; ALongitude: Double;
  const AOptions: TTgSendLocationOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildSendLocationParams(AChatId, ALatitude, ALongitude, AOptions);
  try
    Result := ExecSendLocation(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SendLocation(const AChatId: TTgChatId; ALatitude: Double;
  ALongitude: Double): ITgMessage;
begin
  Result := SendLocation(AChatId, ALatitude, ALongitude, Default(TTgSendLocationOptions));
end;

function TTgApi.SendLocationAsync(const AChatId: TTgChatId; ALatitude: Double; ALongitude: Double;
  const AOptions: TTgSendLocationOptions; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecSendLocation;
  Result := RunAsyncCall<ITgMessage>(BuildSendLocationParams(AChatId, ALatitude, ALongitude, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.SendLocationAsync(const AChatId: TTgChatId; ALatitude: Double; ALongitude: Double;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
begin
  Result := SendLocationAsync(AChatId, ALatitude, ALongitude, Default(TTgSendLocationOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TrySendLocation(const AChatId: TTgChatId; ALatitude: Double; ALongitude: Double;
  const AOptions: TTgSendLocationOptions; out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := SendLocation(AChatId, ALatitude, ALongitude, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySendLocation(const AChatId: TTgChatId; ALatitude: Double; ALongitude: Double;
  out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySendLocation(AChatId, ALatitude, ALongitude, Default(TTgSendLocationOptions),
  AResult, AError);
end;

function TTgApi.BuildSendVenueParams(const AChatId: TTgChatId; ALatitude: Double;
  ALongitude: Double; const ATitle: string; const AAddress: string;
  const AOptions: TTgSendVenueOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('latitude', ALatitude);
    Result.Add('longitude', ALongitude);
    Result.Add('title', ATitle);
    Result.Add('address', AAddress);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSendVenue(AParams: TTgParams): ITgMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('sendVenue', AParams);
  Result := TTgDto.ResultObject<ITgMessage>(LValue, 'sendVenue', TgMakeMessage);
end;

function TTgApi.SendVenue(const AChatId: TTgChatId; ALatitude: Double; ALongitude: Double;
  const ATitle: string; const AAddress: string; const AOptions: TTgSendVenueOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildSendVenueParams(AChatId, ALatitude, ALongitude, ATitle, AAddress, AOptions);
  try
    Result := ExecSendVenue(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SendVenue(const AChatId: TTgChatId; ALatitude: Double; ALongitude: Double;
  const ATitle: string; const AAddress: string): ITgMessage;
begin
  Result := SendVenue(AChatId, ALatitude, ALongitude, ATitle, AAddress,
  Default(TTgSendVenueOptions));
end;

function TTgApi.SendVenueAsync(const AChatId: TTgChatId; ALatitude: Double; ALongitude: Double;
  const ATitle: string; const AAddress: string; const AOptions: TTgSendVenueOptions;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecSendVenue;
  Result := RunAsyncCall<ITgMessage>(BuildSendVenueParams(AChatId, ALatitude, ALongitude, ATitle, AAddress, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.SendVenueAsync(const AChatId: TTgChatId; ALatitude: Double; ALongitude: Double;
  const ATitle: string; const AAddress: string; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := SendVenueAsync(AChatId, ALatitude, ALongitude, ATitle, AAddress,
  Default(TTgSendVenueOptions), AOnSuccess, AOnError);
end;

function TTgApi.TrySendVenue(const AChatId: TTgChatId; ALatitude: Double; ALongitude: Double;
  const ATitle: string; const AAddress: string; const AOptions: TTgSendVenueOptions;
  out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := SendVenue(AChatId, ALatitude, ALongitude, ATitle, AAddress, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySendVenue(const AChatId: TTgChatId; ALatitude: Double; ALongitude: Double;
  const ATitle: string; const AAddress: string; out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySendVenue(AChatId, ALatitude, ALongitude, ATitle, AAddress,
  Default(TTgSendVenueOptions), AResult, AError);
end;

function TTgApi.BuildSendContactParams(const AChatId: TTgChatId; const APhoneNumber: string;
  const AFirstName: string; const AOptions: TTgSendContactOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('phone_number', APhoneNumber);
    Result.Add('first_name', AFirstName);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSendContact(AParams: TTgParams): ITgMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('sendContact', AParams);
  Result := TTgDto.ResultObject<ITgMessage>(LValue, 'sendContact', TgMakeMessage);
end;

function TTgApi.SendContact(const AChatId: TTgChatId; const APhoneNumber: string;
  const AFirstName: string; const AOptions: TTgSendContactOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildSendContactParams(AChatId, APhoneNumber, AFirstName, AOptions);
  try
    Result := ExecSendContact(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SendContact(const AChatId: TTgChatId; const APhoneNumber: string;
  const AFirstName: string): ITgMessage;
begin
  Result := SendContact(AChatId, APhoneNumber, AFirstName, Default(TTgSendContactOptions));
end;

function TTgApi.SendContactAsync(const AChatId: TTgChatId; const APhoneNumber: string;
  const AFirstName: string; const AOptions: TTgSendContactOptions;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecSendContact;
  Result := RunAsyncCall<ITgMessage>(BuildSendContactParams(AChatId, APhoneNumber, AFirstName, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.SendContactAsync(const AChatId: TTgChatId; const APhoneNumber: string;
  const AFirstName: string; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := SendContactAsync(AChatId, APhoneNumber, AFirstName, Default(TTgSendContactOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TrySendContact(const AChatId: TTgChatId; const APhoneNumber: string;
  const AFirstName: string; const AOptions: TTgSendContactOptions; out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := SendContact(AChatId, APhoneNumber, AFirstName, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySendContact(const AChatId: TTgChatId; const APhoneNumber: string;
  const AFirstName: string; out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySendContact(AChatId, APhoneNumber, AFirstName, Default(TTgSendContactOptions),
  AResult, AError);
end;

function TTgApi.BuildSendPollParams(const AChatId: TTgChatId; const AQuestion: string;
  const APollOptions: array of ITgInputPollOption; const AOptions: TTgSendPollOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('question', AQuestion);
    Result.AddJson('options',
      TTgDto.SerializeArray(TTgDto.ToIntf<ITgInputPollOption>(APollOptions), Result, 'options'));
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSendPoll(AParams: TTgParams): ITgMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('sendPoll', AParams);
  Result := TTgDto.ResultObject<ITgMessage>(LValue, 'sendPoll', TgMakeMessage);
end;

function TTgApi.SendPoll(const AChatId: TTgChatId; const AQuestion: string;
  const APollOptions: array of ITgInputPollOption; const AOptions: TTgSendPollOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildSendPollParams(AChatId, AQuestion, APollOptions, AOptions);
  try
    Result := ExecSendPoll(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SendPoll(const AChatId: TTgChatId; const AQuestion: string;
  const APollOptions: array of ITgInputPollOption): ITgMessage;
begin
  Result := SendPoll(AChatId, AQuestion, APollOptions, Default(TTgSendPollOptions));
end;

function TTgApi.SendPollAsync(const AChatId: TTgChatId; const AQuestion: string;
  const APollOptions: array of ITgInputPollOption; const AOptions: TTgSendPollOptions;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecSendPoll;
  Result := RunAsyncCall<ITgMessage>(BuildSendPollParams(AChatId, AQuestion, APollOptions, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.SendPollAsync(const AChatId: TTgChatId; const AQuestion: string;
  const APollOptions: array of ITgInputPollOption; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := SendPollAsync(AChatId, AQuestion, APollOptions, Default(TTgSendPollOptions), AOnSuccess,
  AOnError);
end;

function TTgApi.TrySendPoll(const AChatId: TTgChatId; const AQuestion: string;
  const APollOptions: array of ITgInputPollOption; const AOptions: TTgSendPollOptions;
  out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := SendPoll(AChatId, AQuestion, APollOptions, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySendPoll(const AChatId: TTgChatId; const AQuestion: string;
  const APollOptions: array of ITgInputPollOption; out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySendPoll(AChatId, AQuestion, APollOptions, Default(TTgSendPollOptions), AResult,
  AError);
end;

function TTgApi.BuildSendChecklistParams(const ABusinessConnectionId: string;
  const AChatId: TTgChatId; const AChecklist: ITgInputChecklist;
  const AOptions: TTgSendChecklistOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('business_connection_id', ABusinessConnectionId);
    Result.AddChatId('chat_id', AChatId);
    Result.AddJson('checklist', TTgDto.Serialize(AChecklist, Result));
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSendChecklist(AParams: TTgParams): ITgMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('sendChecklist', AParams);
  Result := TTgDto.ResultObject<ITgMessage>(LValue, 'sendChecklist', TgMakeMessage);
end;

function TTgApi.SendChecklist(const ABusinessConnectionId: string; const AChatId: TTgChatId;
  const AChecklist: ITgInputChecklist; const AOptions: TTgSendChecklistOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildSendChecklistParams(ABusinessConnectionId, AChatId, AChecklist, AOptions);
  try
    Result := ExecSendChecklist(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SendChecklist(const ABusinessConnectionId: string; const AChatId: TTgChatId;
  const AChecklist: ITgInputChecklist): ITgMessage;
begin
  Result := SendChecklist(ABusinessConnectionId, AChatId, AChecklist,
  Default(TTgSendChecklistOptions));
end;

function TTgApi.SendChecklistAsync(const ABusinessConnectionId: string; const AChatId: TTgChatId;
  const AChecklist: ITgInputChecklist; const AOptions: TTgSendChecklistOptions;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecSendChecklist;
  Result := RunAsyncCall<ITgMessage>(BuildSendChecklistParams(ABusinessConnectionId, AChatId, AChecklist, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.SendChecklistAsync(const ABusinessConnectionId: string; const AChatId: TTgChatId;
  const AChecklist: ITgInputChecklist; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := SendChecklistAsync(ABusinessConnectionId, AChatId, AChecklist,
  Default(TTgSendChecklistOptions), AOnSuccess, AOnError);
end;

function TTgApi.TrySendChecklist(const ABusinessConnectionId: string; const AChatId: TTgChatId;
  const AChecklist: ITgInputChecklist; const AOptions: TTgSendChecklistOptions;
  out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := SendChecklist(ABusinessConnectionId, AChatId, AChecklist, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySendChecklist(const ABusinessConnectionId: string; const AChatId: TTgChatId;
  const AChecklist: ITgInputChecklist; out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySendChecklist(ABusinessConnectionId, AChatId, AChecklist,
  Default(TTgSendChecklistOptions), AResult, AError);
end;

function TTgApi.BuildSendDiceParams(const AChatId: TTgChatId;
  const AOptions: TTgSendDiceOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSendDice(AParams: TTgParams): ITgMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('sendDice', AParams);
  Result := TTgDto.ResultObject<ITgMessage>(LValue, 'sendDice', TgMakeMessage);
end;

function TTgApi.SendDice(const AChatId: TTgChatId; const AOptions: TTgSendDiceOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildSendDiceParams(AChatId, AOptions);
  try
    Result := ExecSendDice(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SendDice(const AChatId: TTgChatId): ITgMessage;
begin
  Result := SendDice(AChatId, Default(TTgSendDiceOptions));
end;

function TTgApi.SendDiceAsync(const AChatId: TTgChatId; const AOptions: TTgSendDiceOptions;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecSendDice;
  Result := RunAsyncCall<ITgMessage>(BuildSendDiceParams(AChatId, AOptions), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.SendDiceAsync(const AChatId: TTgChatId; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := SendDiceAsync(AChatId, Default(TTgSendDiceOptions), AOnSuccess, AOnError);
end;

function TTgApi.TrySendDice(const AChatId: TTgChatId; const AOptions: TTgSendDiceOptions;
  out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := SendDice(AChatId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySendDice(const AChatId: TTgChatId; out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySendDice(AChatId, Default(TTgSendDiceOptions), AResult, AError);
end;

function TTgApi.BuildSendMessageDraftParams(AChatId: Int64; ADraftId: Int64;
  const AOptions: TTgSendMessageDraftOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('chat_id', AChatId);
    Result.Add('draft_id', ADraftId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSendMessageDraft(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('sendMessageDraft', AParams);
  Result := TTgDto.ResultBool(LValue, 'sendMessageDraft');
end;

function TTgApi.SendMessageDraft(AChatId: Int64; ADraftId: Int64;
  const AOptions: TTgSendMessageDraftOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSendMessageDraftParams(AChatId, ADraftId, AOptions);
  try
    Result := ExecSendMessageDraft(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SendMessageDraft(AChatId: Int64; ADraftId: Int64): Boolean;
begin
  Result := SendMessageDraft(AChatId, ADraftId, Default(TTgSendMessageDraftOptions));
end;

function TTgApi.SendMessageDraftAsync(AChatId: Int64; ADraftId: Int64;
  const AOptions: TTgSendMessageDraftOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSendMessageDraft;
  Result := RunAsyncCall<Boolean>(BuildSendMessageDraftParams(AChatId, ADraftId, AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.SendMessageDraftAsync(AChatId: Int64; ADraftId: Int64;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
begin
  Result := SendMessageDraftAsync(AChatId, ADraftId, Default(TTgSendMessageDraftOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TrySendMessageDraft(AChatId: Int64; ADraftId: Int64;
  const AOptions: TTgSendMessageDraftOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SendMessageDraft(AChatId, ADraftId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySendMessageDraft(AChatId: Int64; ADraftId: Int64;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySendMessageDraft(AChatId, ADraftId, Default(TTgSendMessageDraftOptions), AError);
end;

function TTgApi.BuildSendChatActionParams(const AChatId: TTgChatId; const AAction: string;
  const AOptions: TTgSendChatActionOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('action', AAction);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSendChatAction(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('sendChatAction', AParams);
  Result := TTgDto.ResultBool(LValue, 'sendChatAction');
end;

function TTgApi.SendChatAction(const AChatId: TTgChatId; const AAction: string;
  const AOptions: TTgSendChatActionOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSendChatActionParams(AChatId, AAction, AOptions);
  try
    Result := ExecSendChatAction(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SendChatAction(const AChatId: TTgChatId; const AAction: string): Boolean;
begin
  Result := SendChatAction(AChatId, AAction, Default(TTgSendChatActionOptions));
end;

function TTgApi.SendChatActionAsync(const AChatId: TTgChatId; const AAction: string;
  const AOptions: TTgSendChatActionOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSendChatAction;
  Result := RunAsyncCall<Boolean>(BuildSendChatActionParams(AChatId, AAction, AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.SendChatActionAsync(const AChatId: TTgChatId; const AAction: string;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
begin
  Result := SendChatActionAsync(AChatId, AAction, Default(TTgSendChatActionOptions), AOnSuccess,
  AOnError);
end;

function TTgApi.TrySendChatAction(const AChatId: TTgChatId; const AAction: string;
  const AOptions: TTgSendChatActionOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SendChatAction(AChatId, AAction, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySendChatAction(const AChatId: TTgChatId; const AAction: string;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySendChatAction(AChatId, AAction, Default(TTgSendChatActionOptions), AError);
end;

function TTgApi.BuildSetMessageReactionParams(const AChatId: TTgChatId; AMessageId: Int64;
  const AOptions: TTgSetMessageReactionOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('message_id', AMessageId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetMessageReaction(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setMessageReaction', AParams);
  Result := TTgDto.ResultBool(LValue, 'setMessageReaction');
end;

function TTgApi.SetMessageReaction(const AChatId: TTgChatId; AMessageId: Int64;
  const AOptions: TTgSetMessageReactionOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetMessageReactionParams(AChatId, AMessageId, AOptions);
  try
    Result := ExecSetMessageReaction(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetMessageReaction(const AChatId: TTgChatId; AMessageId: Int64): Boolean;
begin
  Result := SetMessageReaction(AChatId, AMessageId, Default(TTgSetMessageReactionOptions));
end;

function TTgApi.SetMessageReactionAsync(const AChatId: TTgChatId; AMessageId: Int64;
  const AOptions: TTgSetMessageReactionOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetMessageReaction;
  Result := RunAsyncCall<Boolean>(BuildSetMessageReactionParams(AChatId, AMessageId, AOptions),
    LExec, AOnSuccess, AOnError);
end;

function TTgApi.SetMessageReactionAsync(const AChatId: TTgChatId; AMessageId: Int64;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
begin
  Result := SetMessageReactionAsync(AChatId, AMessageId, Default(TTgSetMessageReactionOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TrySetMessageReaction(const AChatId: TTgChatId; AMessageId: Int64;
  const AOptions: TTgSetMessageReactionOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetMessageReaction(AChatId, AMessageId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySetMessageReaction(const AChatId: TTgChatId; AMessageId: Int64;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySetMessageReaction(AChatId, AMessageId, Default(TTgSetMessageReactionOptions),
  AError);
end;

function TTgApi.BuildGetUserProfilePhotosParams(AUserId: Int64;
  const AOptions: TTgGetUserProfilePhotosOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('user_id', AUserId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecGetUserProfilePhotos(AParams: TTgParams): ITgUserProfilePhotos;
var
  LValue: TJSONValue;
begin
  LValue := Call('getUserProfilePhotos', AParams);
  Result := TTgDto.ResultObject<ITgUserProfilePhotos>(LValue, 'getUserProfilePhotos',
    TgMakeUserProfilePhotos);
end;

function TTgApi.GetUserProfilePhotos(AUserId: Int64;
  const AOptions: TTgGetUserProfilePhotosOptions): ITgUserProfilePhotos;
var
  LParams: TTgParams;
begin
  LParams := BuildGetUserProfilePhotosParams(AUserId, AOptions);
  try
    Result := ExecGetUserProfilePhotos(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.GetUserProfilePhotos(AUserId: Int64): ITgUserProfilePhotos;
begin
  Result := GetUserProfilePhotos(AUserId, Default(TTgGetUserProfilePhotosOptions));
end;

function TTgApi.GetUserProfilePhotosAsync(AUserId: Int64;
  const AOptions: TTgGetUserProfilePhotosOptions; const AOnSuccess: TProc<ITgUserProfilePhotos>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgUserProfilePhotos>;
begin
  LExec := ExecGetUserProfilePhotos;
  Result := RunAsyncCall<ITgUserProfilePhotos>(BuildGetUserProfilePhotosParams(AUserId, AOptions),
    LExec, AOnSuccess, AOnError);
end;

function TTgApi.GetUserProfilePhotosAsync(AUserId: Int64;
  const AOnSuccess: TProc<ITgUserProfilePhotos>; const AOnError: TProc<Exception>): ITask;
begin
  Result := GetUserProfilePhotosAsync(AUserId, Default(TTgGetUserProfilePhotosOptions), AOnSuccess,
  AOnError);
end;

function TTgApi.TryGetUserProfilePhotos(AUserId: Int64;
  const AOptions: TTgGetUserProfilePhotosOptions; out AResult: ITgUserProfilePhotos;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgUserProfilePhotos);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetUserProfilePhotos(AUserId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryGetUserProfilePhotos(AUserId: Int64; out AResult: ITgUserProfilePhotos;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryGetUserProfilePhotos(AUserId, Default(TTgGetUserProfilePhotosOptions), AResult,
  AError);
end;

function TTgApi.BuildGetUserProfileAudiosParams(AUserId: Int64;
  const AOptions: TTgGetUserProfileAudiosOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('user_id', AUserId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecGetUserProfileAudios(AParams: TTgParams): ITgUserProfileAudios;
var
  LValue: TJSONValue;
begin
  LValue := Call('getUserProfileAudios', AParams);
  Result := TTgDto.ResultObject<ITgUserProfileAudios>(LValue, 'getUserProfileAudios',
    TgMakeUserProfileAudios);
end;

function TTgApi.GetUserProfileAudios(AUserId: Int64;
  const AOptions: TTgGetUserProfileAudiosOptions): ITgUserProfileAudios;
var
  LParams: TTgParams;
begin
  LParams := BuildGetUserProfileAudiosParams(AUserId, AOptions);
  try
    Result := ExecGetUserProfileAudios(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.GetUserProfileAudios(AUserId: Int64): ITgUserProfileAudios;
begin
  Result := GetUserProfileAudios(AUserId, Default(TTgGetUserProfileAudiosOptions));
end;

function TTgApi.GetUserProfileAudiosAsync(AUserId: Int64;
  const AOptions: TTgGetUserProfileAudiosOptions; const AOnSuccess: TProc<ITgUserProfileAudios>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgUserProfileAudios>;
begin
  LExec := ExecGetUserProfileAudios;
  Result := RunAsyncCall<ITgUserProfileAudios>(BuildGetUserProfileAudiosParams(AUserId, AOptions),
    LExec, AOnSuccess, AOnError);
end;

function TTgApi.GetUserProfileAudiosAsync(AUserId: Int64;
  const AOnSuccess: TProc<ITgUserProfileAudios>; const AOnError: TProc<Exception>): ITask;
begin
  Result := GetUserProfileAudiosAsync(AUserId, Default(TTgGetUserProfileAudiosOptions), AOnSuccess,
  AOnError);
end;

function TTgApi.TryGetUserProfileAudios(AUserId: Int64;
  const AOptions: TTgGetUserProfileAudiosOptions; out AResult: ITgUserProfileAudios;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgUserProfileAudios);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetUserProfileAudios(AUserId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryGetUserProfileAudios(AUserId: Int64; out AResult: ITgUserProfileAudios;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryGetUserProfileAudios(AUserId, Default(TTgGetUserProfileAudiosOptions), AResult,
  AError);
end;

function TTgApi.BuildSetUserEmojiStatusParams(AUserId: Int64;
  const AOptions: TTgSetUserEmojiStatusOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('user_id', AUserId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetUserEmojiStatus(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setUserEmojiStatus', AParams);
  Result := TTgDto.ResultBool(LValue, 'setUserEmojiStatus');
end;

function TTgApi.SetUserEmojiStatus(AUserId: Int64;
  const AOptions: TTgSetUserEmojiStatusOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetUserEmojiStatusParams(AUserId, AOptions);
  try
    Result := ExecSetUserEmojiStatus(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetUserEmojiStatus(AUserId: Int64): Boolean;
begin
  Result := SetUserEmojiStatus(AUserId, Default(TTgSetUserEmojiStatusOptions));
end;

function TTgApi.SetUserEmojiStatusAsync(AUserId: Int64;
  const AOptions: TTgSetUserEmojiStatusOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetUserEmojiStatus;
  Result := RunAsyncCall<Boolean>(BuildSetUserEmojiStatusParams(AUserId, AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.SetUserEmojiStatusAsync(AUserId: Int64; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := SetUserEmojiStatusAsync(AUserId, Default(TTgSetUserEmojiStatusOptions), AOnSuccess,
  AOnError);
end;

function TTgApi.TrySetUserEmojiStatus(AUserId: Int64; const AOptions: TTgSetUserEmojiStatusOptions;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetUserEmojiStatus(AUserId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySetUserEmojiStatus(AUserId: Int64; out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySetUserEmojiStatus(AUserId, Default(TTgSetUserEmojiStatusOptions), AError);
end;

function TTgApi.BuildGetFileParams(const AFileId: string): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('file_id', AFileId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecGetFile(AParams: TTgParams): ITgFile;
var
  LValue: TJSONValue;
begin
  LValue := Call('getFile', AParams);
  Result := TTgDto.ResultObject<ITgFile>(LValue, 'getFile', TgMakeFile);
end;

function TTgApi.GetFile(const AFileId: string): ITgFile;
var
  LParams: TTgParams;
begin
  LParams := BuildGetFileParams(AFileId);
  try
    Result := ExecGetFile(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.GetFileAsync(const AFileId: string; const AOnSuccess: TProc<ITgFile>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgFile>;
begin
  LExec := ExecGetFile;
  Result := RunAsyncCall<ITgFile>(BuildGetFileParams(AFileId), LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryGetFile(const AFileId: string; out AResult: ITgFile;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgFile);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetFile(AFileId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildBanChatMemberParams(const AChatId: TTgChatId; AUserId: Int64;
  const AOptions: TTgBanChatMemberOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('user_id', AUserId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecBanChatMember(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('banChatMember', AParams);
  Result := TTgDto.ResultBool(LValue, 'banChatMember');
end;

function TTgApi.BanChatMember(const AChatId: TTgChatId; AUserId: Int64;
  const AOptions: TTgBanChatMemberOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildBanChatMemberParams(AChatId, AUserId, AOptions);
  try
    Result := ExecBanChatMember(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.BanChatMember(const AChatId: TTgChatId; AUserId: Int64): Boolean;
begin
  Result := BanChatMember(AChatId, AUserId, Default(TTgBanChatMemberOptions));
end;

function TTgApi.BanChatMemberAsync(const AChatId: TTgChatId; AUserId: Int64;
  const AOptions: TTgBanChatMemberOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecBanChatMember;
  Result := RunAsyncCall<Boolean>(BuildBanChatMemberParams(AChatId, AUserId, AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.BanChatMemberAsync(const AChatId: TTgChatId; AUserId: Int64;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
begin
  Result := BanChatMemberAsync(AChatId, AUserId, Default(TTgBanChatMemberOptions), AOnSuccess,
  AOnError);
end;

function TTgApi.TryBanChatMember(const AChatId: TTgChatId; AUserId: Int64;
  const AOptions: TTgBanChatMemberOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    BanChatMember(AChatId, AUserId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryBanChatMember(const AChatId: TTgChatId; AUserId: Int64;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryBanChatMember(AChatId, AUserId, Default(TTgBanChatMemberOptions), AError);
end;

function TTgApi.BuildUnbanChatMemberParams(const AChatId: TTgChatId; AUserId: Int64;
  const AOptions: TTgUnbanChatMemberOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('user_id', AUserId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecUnbanChatMember(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('unbanChatMember', AParams);
  Result := TTgDto.ResultBool(LValue, 'unbanChatMember');
end;

function TTgApi.UnbanChatMember(const AChatId: TTgChatId; AUserId: Int64;
  const AOptions: TTgUnbanChatMemberOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildUnbanChatMemberParams(AChatId, AUserId, AOptions);
  try
    Result := ExecUnbanChatMember(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.UnbanChatMember(const AChatId: TTgChatId; AUserId: Int64): Boolean;
begin
  Result := UnbanChatMember(AChatId, AUserId, Default(TTgUnbanChatMemberOptions));
end;

function TTgApi.UnbanChatMemberAsync(const AChatId: TTgChatId; AUserId: Int64;
  const AOptions: TTgUnbanChatMemberOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecUnbanChatMember;
  Result := RunAsyncCall<Boolean>(BuildUnbanChatMemberParams(AChatId, AUserId, AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.UnbanChatMemberAsync(const AChatId: TTgChatId; AUserId: Int64;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
begin
  Result := UnbanChatMemberAsync(AChatId, AUserId, Default(TTgUnbanChatMemberOptions), AOnSuccess,
  AOnError);
end;

function TTgApi.TryUnbanChatMember(const AChatId: TTgChatId; AUserId: Int64;
  const AOptions: TTgUnbanChatMemberOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    UnbanChatMember(AChatId, AUserId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryUnbanChatMember(const AChatId: TTgChatId; AUserId: Int64;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryUnbanChatMember(AChatId, AUserId, Default(TTgUnbanChatMemberOptions), AError);
end;

function TTgApi.BuildRestrictChatMemberParams(const AChatId: TTgChatId; AUserId: Int64;
  const APermissions: ITgChatPermissions; const AOptions: TTgRestrictChatMemberOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('user_id', AUserId);
    Result.AddJson('permissions', TTgDto.Serialize(APermissions, Result));
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecRestrictChatMember(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('restrictChatMember', AParams);
  Result := TTgDto.ResultBool(LValue, 'restrictChatMember');
end;

function TTgApi.RestrictChatMember(const AChatId: TTgChatId; AUserId: Int64;
  const APermissions: ITgChatPermissions; const AOptions: TTgRestrictChatMemberOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildRestrictChatMemberParams(AChatId, AUserId, APermissions, AOptions);
  try
    Result := ExecRestrictChatMember(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.RestrictChatMember(const AChatId: TTgChatId; AUserId: Int64;
  const APermissions: ITgChatPermissions): Boolean;
begin
  Result := RestrictChatMember(AChatId, AUserId, APermissions,
  Default(TTgRestrictChatMemberOptions));
end;

function TTgApi.RestrictChatMemberAsync(const AChatId: TTgChatId; AUserId: Int64;
  const APermissions: ITgChatPermissions; const AOptions: TTgRestrictChatMemberOptions;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecRestrictChatMember;
  Result := RunAsyncCall<Boolean>(BuildRestrictChatMemberParams(AChatId, AUserId, APermissions, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.RestrictChatMemberAsync(const AChatId: TTgChatId; AUserId: Int64;
  const APermissions: ITgChatPermissions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := RestrictChatMemberAsync(AChatId, AUserId, APermissions,
  Default(TTgRestrictChatMemberOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryRestrictChatMember(const AChatId: TTgChatId; AUserId: Int64;
  const APermissions: ITgChatPermissions; const AOptions: TTgRestrictChatMemberOptions;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    RestrictChatMember(AChatId, AUserId, APermissions, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryRestrictChatMember(const AChatId: TTgChatId; AUserId: Int64;
  const APermissions: ITgChatPermissions; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryRestrictChatMember(AChatId, AUserId, APermissions,
  Default(TTgRestrictChatMemberOptions), AError);
end;

function TTgApi.BuildPromoteChatMemberParams(const AChatId: TTgChatId; AUserId: Int64;
  const AOptions: TTgPromoteChatMemberOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('user_id', AUserId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecPromoteChatMember(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('promoteChatMember', AParams);
  Result := TTgDto.ResultBool(LValue, 'promoteChatMember');
end;

function TTgApi.PromoteChatMember(const AChatId: TTgChatId; AUserId: Int64;
  const AOptions: TTgPromoteChatMemberOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildPromoteChatMemberParams(AChatId, AUserId, AOptions);
  try
    Result := ExecPromoteChatMember(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.PromoteChatMember(const AChatId: TTgChatId; AUserId: Int64): Boolean;
begin
  Result := PromoteChatMember(AChatId, AUserId, Default(TTgPromoteChatMemberOptions));
end;

function TTgApi.PromoteChatMemberAsync(const AChatId: TTgChatId; AUserId: Int64;
  const AOptions: TTgPromoteChatMemberOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecPromoteChatMember;
  Result := RunAsyncCall<Boolean>(BuildPromoteChatMemberParams(AChatId, AUserId, AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.PromoteChatMemberAsync(const AChatId: TTgChatId; AUserId: Int64;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
begin
  Result := PromoteChatMemberAsync(AChatId, AUserId, Default(TTgPromoteChatMemberOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TryPromoteChatMember(const AChatId: TTgChatId; AUserId: Int64;
  const AOptions: TTgPromoteChatMemberOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    PromoteChatMember(AChatId, AUserId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryPromoteChatMember(const AChatId: TTgChatId; AUserId: Int64;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryPromoteChatMember(AChatId, AUserId, Default(TTgPromoteChatMemberOptions), AError);
end;

function TTgApi.BuildSetChatAdministratorCustomTitleParams(const AChatId: TTgChatId; AUserId: Int64;
  const ACustomTitle: string): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('user_id', AUserId);
    Result.Add('custom_title', ACustomTitle);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetChatAdministratorCustomTitle(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setChatAdministratorCustomTitle', AParams);
  Result := TTgDto.ResultBool(LValue, 'setChatAdministratorCustomTitle');
end;

function TTgApi.SetChatAdministratorCustomTitle(const AChatId: TTgChatId; AUserId: Int64;
  const ACustomTitle: string): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetChatAdministratorCustomTitleParams(AChatId, AUserId, ACustomTitle);
  try
    Result := ExecSetChatAdministratorCustomTitle(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetChatAdministratorCustomTitleAsync(const AChatId: TTgChatId; AUserId: Int64;
  const ACustomTitle: string; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetChatAdministratorCustomTitle;
  Result := RunAsyncCall<Boolean>(BuildSetChatAdministratorCustomTitleParams(AChatId, AUserId, ACustomTitle), LExec, AOnSuccess, AOnError);
end;

function TTgApi.TrySetChatAdministratorCustomTitle(const AChatId: TTgChatId; AUserId: Int64;
  const ACustomTitle: string; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetChatAdministratorCustomTitle(AChatId, AUserId, ACustomTitle);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildSetChatMemberTagParams(const AChatId: TTgChatId; AUserId: Int64;
  const AOptions: TTgSetChatMemberTagOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('user_id', AUserId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetChatMemberTag(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setChatMemberTag', AParams);
  Result := TTgDto.ResultBool(LValue, 'setChatMemberTag');
end;

function TTgApi.SetChatMemberTag(const AChatId: TTgChatId; AUserId: Int64;
  const AOptions: TTgSetChatMemberTagOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetChatMemberTagParams(AChatId, AUserId, AOptions);
  try
    Result := ExecSetChatMemberTag(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetChatMemberTag(const AChatId: TTgChatId; AUserId: Int64): Boolean;
begin
  Result := SetChatMemberTag(AChatId, AUserId, Default(TTgSetChatMemberTagOptions));
end;

function TTgApi.SetChatMemberTagAsync(const AChatId: TTgChatId; AUserId: Int64;
  const AOptions: TTgSetChatMemberTagOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetChatMemberTag;
  Result := RunAsyncCall<Boolean>(BuildSetChatMemberTagParams(AChatId, AUserId, AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.SetChatMemberTagAsync(const AChatId: TTgChatId; AUserId: Int64;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
begin
  Result := SetChatMemberTagAsync(AChatId, AUserId, Default(TTgSetChatMemberTagOptions), AOnSuccess,
  AOnError);
end;

function TTgApi.TrySetChatMemberTag(const AChatId: TTgChatId; AUserId: Int64;
  const AOptions: TTgSetChatMemberTagOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetChatMemberTag(AChatId, AUserId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySetChatMemberTag(const AChatId: TTgChatId; AUserId: Int64;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySetChatMemberTag(AChatId, AUserId, Default(TTgSetChatMemberTagOptions), AError);
end;

function TTgApi.BuildBanChatSenderChatParams(const AChatId: TTgChatId;
  ASenderChatId: Int64): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('sender_chat_id', ASenderChatId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecBanChatSenderChat(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('banChatSenderChat', AParams);
  Result := TTgDto.ResultBool(LValue, 'banChatSenderChat');
end;

function TTgApi.BanChatSenderChat(const AChatId: TTgChatId; ASenderChatId: Int64): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildBanChatSenderChatParams(AChatId, ASenderChatId);
  try
    Result := ExecBanChatSenderChat(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.BanChatSenderChatAsync(const AChatId: TTgChatId; ASenderChatId: Int64;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecBanChatSenderChat;
  Result := RunAsyncCall<Boolean>(BuildBanChatSenderChatParams(AChatId, ASenderChatId), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.TryBanChatSenderChat(const AChatId: TTgChatId; ASenderChatId: Int64;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    BanChatSenderChat(AChatId, ASenderChatId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildUnbanChatSenderChatParams(const AChatId: TTgChatId;
  ASenderChatId: Int64): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('sender_chat_id', ASenderChatId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecUnbanChatSenderChat(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('unbanChatSenderChat', AParams);
  Result := TTgDto.ResultBool(LValue, 'unbanChatSenderChat');
end;

function TTgApi.UnbanChatSenderChat(const AChatId: TTgChatId; ASenderChatId: Int64): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildUnbanChatSenderChatParams(AChatId, ASenderChatId);
  try
    Result := ExecUnbanChatSenderChat(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.UnbanChatSenderChatAsync(const AChatId: TTgChatId; ASenderChatId: Int64;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecUnbanChatSenderChat;
  Result := RunAsyncCall<Boolean>(BuildUnbanChatSenderChatParams(AChatId, ASenderChatId), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.TryUnbanChatSenderChat(const AChatId: TTgChatId; ASenderChatId: Int64;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    UnbanChatSenderChat(AChatId, ASenderChatId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildSetChatPermissionsParams(const AChatId: TTgChatId;
  const APermissions: ITgChatPermissions; const AOptions: TTgSetChatPermissionsOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.AddJson('permissions', TTgDto.Serialize(APermissions, Result));
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetChatPermissions(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setChatPermissions', AParams);
  Result := TTgDto.ResultBool(LValue, 'setChatPermissions');
end;

function TTgApi.SetChatPermissions(const AChatId: TTgChatId; const APermissions: ITgChatPermissions;
  const AOptions: TTgSetChatPermissionsOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetChatPermissionsParams(AChatId, APermissions, AOptions);
  try
    Result := ExecSetChatPermissions(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetChatPermissions(const AChatId: TTgChatId;
  const APermissions: ITgChatPermissions): Boolean;
begin
  Result := SetChatPermissions(AChatId, APermissions, Default(TTgSetChatPermissionsOptions));
end;

function TTgApi.SetChatPermissionsAsync(const AChatId: TTgChatId;
  const APermissions: ITgChatPermissions; const AOptions: TTgSetChatPermissionsOptions;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetChatPermissions;
  Result := RunAsyncCall<Boolean>(BuildSetChatPermissionsParams(AChatId, APermissions, AOptions),
    LExec, AOnSuccess, AOnError);
end;

function TTgApi.SetChatPermissionsAsync(const AChatId: TTgChatId;
  const APermissions: ITgChatPermissions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := SetChatPermissionsAsync(AChatId, APermissions, Default(TTgSetChatPermissionsOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TrySetChatPermissions(const AChatId: TTgChatId;
  const APermissions: ITgChatPermissions; const AOptions: TTgSetChatPermissionsOptions;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetChatPermissions(AChatId, APermissions, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySetChatPermissions(const AChatId: TTgChatId;
  const APermissions: ITgChatPermissions; out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySetChatPermissions(AChatId, APermissions, Default(TTgSetChatPermissionsOptions),
  AError);
end;

function TTgApi.BuildExportChatInviteLinkParams(const AChatId: TTgChatId): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecExportChatInviteLink(AParams: TTgParams): string;
var
  LValue: TJSONValue;
begin
  LValue := Call('exportChatInviteLink', AParams);
  Result := TTgDto.ResultStr(LValue, 'exportChatInviteLink');
end;

function TTgApi.ExportChatInviteLink(const AChatId: TTgChatId): string;
var
  LParams: TTgParams;
begin
  LParams := BuildExportChatInviteLinkParams(AChatId);
  try
    Result := ExecExportChatInviteLink(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.ExportChatInviteLinkAsync(const AChatId: TTgChatId; const AOnSuccess: TProc<string>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<string>;
begin
  LExec := ExecExportChatInviteLink;
  Result := RunAsyncCall<string>(BuildExportChatInviteLinkParams(AChatId), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.TryExportChatInviteLink(const AChatId: TTgChatId; out AResult: string;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(string);
  AError := TTgErrorInfo.Empty;
  try
    AResult := ExportChatInviteLink(AChatId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildCreateChatInviteLinkParams(const AChatId: TTgChatId;
  const AOptions: TTgCreateChatInviteLinkOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecCreateChatInviteLink(AParams: TTgParams): ITgChatInviteLink;
var
  LValue: TJSONValue;
begin
  LValue := Call('createChatInviteLink', AParams);
  Result := TTgDto.ResultObject<ITgChatInviteLink>(LValue, 'createChatInviteLink',
    TgMakeChatInviteLink);
end;

function TTgApi.CreateChatInviteLink(const AChatId: TTgChatId;
  const AOptions: TTgCreateChatInviteLinkOptions): ITgChatInviteLink;
var
  LParams: TTgParams;
begin
  LParams := BuildCreateChatInviteLinkParams(AChatId, AOptions);
  try
    Result := ExecCreateChatInviteLink(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.CreateChatInviteLink(const AChatId: TTgChatId): ITgChatInviteLink;
begin
  Result := CreateChatInviteLink(AChatId, Default(TTgCreateChatInviteLinkOptions));
end;

function TTgApi.CreateChatInviteLinkAsync(const AChatId: TTgChatId;
  const AOptions: TTgCreateChatInviteLinkOptions; const AOnSuccess: TProc<ITgChatInviteLink>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgChatInviteLink>;
begin
  LExec := ExecCreateChatInviteLink;
  Result := RunAsyncCall<ITgChatInviteLink>(BuildCreateChatInviteLinkParams(AChatId, AOptions),
    LExec, AOnSuccess, AOnError);
end;

function TTgApi.CreateChatInviteLinkAsync(const AChatId: TTgChatId;
  const AOnSuccess: TProc<ITgChatInviteLink>; const AOnError: TProc<Exception>): ITask;
begin
  Result := CreateChatInviteLinkAsync(AChatId, Default(TTgCreateChatInviteLinkOptions), AOnSuccess,
  AOnError);
end;

function TTgApi.TryCreateChatInviteLink(const AChatId: TTgChatId;
  const AOptions: TTgCreateChatInviteLinkOptions; out AResult: ITgChatInviteLink;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgChatInviteLink);
  AError := TTgErrorInfo.Empty;
  try
    AResult := CreateChatInviteLink(AChatId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryCreateChatInviteLink(const AChatId: TTgChatId; out AResult: ITgChatInviteLink;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryCreateChatInviteLink(AChatId, Default(TTgCreateChatInviteLinkOptions), AResult,
  AError);
end;

function TTgApi.BuildEditChatInviteLinkParams(const AChatId: TTgChatId; const AInviteLink: string;
  const AOptions: TTgEditChatInviteLinkOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('invite_link', AInviteLink);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecEditChatInviteLink(AParams: TTgParams): ITgChatInviteLink;
var
  LValue: TJSONValue;
begin
  LValue := Call('editChatInviteLink', AParams);
  Result := TTgDto.ResultObject<ITgChatInviteLink>(LValue, 'editChatInviteLink',
    TgMakeChatInviteLink);
end;

function TTgApi.EditChatInviteLink(const AChatId: TTgChatId; const AInviteLink: string;
  const AOptions: TTgEditChatInviteLinkOptions): ITgChatInviteLink;
var
  LParams: TTgParams;
begin
  LParams := BuildEditChatInviteLinkParams(AChatId, AInviteLink, AOptions);
  try
    Result := ExecEditChatInviteLink(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.EditChatInviteLink(const AChatId: TTgChatId;
  const AInviteLink: string): ITgChatInviteLink;
begin
  Result := EditChatInviteLink(AChatId, AInviteLink, Default(TTgEditChatInviteLinkOptions));
end;

function TTgApi.EditChatInviteLinkAsync(const AChatId: TTgChatId; const AInviteLink: string;
  const AOptions: TTgEditChatInviteLinkOptions; const AOnSuccess: TProc<ITgChatInviteLink>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgChatInviteLink>;
begin
  LExec := ExecEditChatInviteLink;
  Result := RunAsyncCall<ITgChatInviteLink>(BuildEditChatInviteLinkParams(AChatId, AInviteLink, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.EditChatInviteLinkAsync(const AChatId: TTgChatId; const AInviteLink: string;
  const AOnSuccess: TProc<ITgChatInviteLink>; const AOnError: TProc<Exception>): ITask;
begin
  Result := EditChatInviteLinkAsync(AChatId, AInviteLink, Default(TTgEditChatInviteLinkOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TryEditChatInviteLink(const AChatId: TTgChatId; const AInviteLink: string;
  const AOptions: TTgEditChatInviteLinkOptions; out AResult: ITgChatInviteLink;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgChatInviteLink);
  AError := TTgErrorInfo.Empty;
  try
    AResult := EditChatInviteLink(AChatId, AInviteLink, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryEditChatInviteLink(const AChatId: TTgChatId; const AInviteLink: string;
  out AResult: ITgChatInviteLink; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryEditChatInviteLink(AChatId, AInviteLink, Default(TTgEditChatInviteLinkOptions),
  AResult, AError);
end;

function TTgApi.BuildCreateChatSubscriptionInviteLinkParams(const AChatId: TTgChatId;
  ASubscriptionPeriod: Integer; ASubscriptionPrice: Integer;
  const AOptions: TTgCreateChatSubscriptionInviteLinkOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('subscription_period', ASubscriptionPeriod);
    Result.Add('subscription_price', ASubscriptionPrice);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecCreateChatSubscriptionInviteLink(AParams: TTgParams): ITgChatInviteLink;
var
  LValue: TJSONValue;
begin
  LValue := Call('createChatSubscriptionInviteLink', AParams);
  Result := TTgDto.ResultObject<ITgChatInviteLink>(LValue, 'createChatSubscriptionInviteLink',
    TgMakeChatInviteLink);
end;

function TTgApi.CreateChatSubscriptionInviteLink(const AChatId: TTgChatId;
  ASubscriptionPeriod: Integer; ASubscriptionPrice: Integer;
  const AOptions: TTgCreateChatSubscriptionInviteLinkOptions): ITgChatInviteLink;
var
  LParams: TTgParams;
begin
  LParams := BuildCreateChatSubscriptionInviteLinkParams(AChatId, ASubscriptionPeriod,
    ASubscriptionPrice, AOptions);
  try
    Result := ExecCreateChatSubscriptionInviteLink(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.CreateChatSubscriptionInviteLink(const AChatId: TTgChatId;
  ASubscriptionPeriod: Integer; ASubscriptionPrice: Integer): ITgChatInviteLink;
begin
  Result := CreateChatSubscriptionInviteLink(AChatId, ASubscriptionPeriod, ASubscriptionPrice,
  Default(TTgCreateChatSubscriptionInviteLinkOptions));
end;

function TTgApi.CreateChatSubscriptionInviteLinkAsync(const AChatId: TTgChatId;
  ASubscriptionPeriod: Integer; ASubscriptionPrice: Integer;
  const AOptions: TTgCreateChatSubscriptionInviteLinkOptions;
  const AOnSuccess: TProc<ITgChatInviteLink>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgChatInviteLink>;
begin
  LExec := ExecCreateChatSubscriptionInviteLink;
  Result := RunAsyncCall<ITgChatInviteLink>(BuildCreateChatSubscriptionInviteLinkParams(AChatId, ASubscriptionPeriod, ASubscriptionPrice, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.CreateChatSubscriptionInviteLinkAsync(const AChatId: TTgChatId;
  ASubscriptionPeriod: Integer; ASubscriptionPrice: Integer;
  const AOnSuccess: TProc<ITgChatInviteLink>; const AOnError: TProc<Exception>): ITask;
begin
  Result := CreateChatSubscriptionInviteLinkAsync(AChatId, ASubscriptionPeriod, ASubscriptionPrice,
  Default(TTgCreateChatSubscriptionInviteLinkOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryCreateChatSubscriptionInviteLink(const AChatId: TTgChatId;
  ASubscriptionPeriod: Integer; ASubscriptionPrice: Integer;
  const AOptions: TTgCreateChatSubscriptionInviteLinkOptions; out AResult: ITgChatInviteLink;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgChatInviteLink);
  AError := TTgErrorInfo.Empty;
  try
    AResult := CreateChatSubscriptionInviteLink(AChatId, ASubscriptionPeriod, ASubscriptionPrice,
      AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryCreateChatSubscriptionInviteLink(const AChatId: TTgChatId;
  ASubscriptionPeriod: Integer; ASubscriptionPrice: Integer; out AResult: ITgChatInviteLink;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryCreateChatSubscriptionInviteLink(AChatId, ASubscriptionPeriod, ASubscriptionPrice,
  Default(TTgCreateChatSubscriptionInviteLinkOptions), AResult, AError);
end;

function TTgApi.BuildEditChatSubscriptionInviteLinkParams(const AChatId: TTgChatId;
  const AInviteLink: string; const AOptions: TTgEditChatSubscriptionInviteLinkOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('invite_link', AInviteLink);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecEditChatSubscriptionInviteLink(AParams: TTgParams): ITgChatInviteLink;
var
  LValue: TJSONValue;
begin
  LValue := Call('editChatSubscriptionInviteLink', AParams);
  Result := TTgDto.ResultObject<ITgChatInviteLink>(LValue, 'editChatSubscriptionInviteLink',
    TgMakeChatInviteLink);
end;

function TTgApi.EditChatSubscriptionInviteLink(const AChatId: TTgChatId; const AInviteLink: string;
  const AOptions: TTgEditChatSubscriptionInviteLinkOptions): ITgChatInviteLink;
var
  LParams: TTgParams;
begin
  LParams := BuildEditChatSubscriptionInviteLinkParams(AChatId, AInviteLink, AOptions);
  try
    Result := ExecEditChatSubscriptionInviteLink(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.EditChatSubscriptionInviteLink(const AChatId: TTgChatId;
  const AInviteLink: string): ITgChatInviteLink;
begin
  Result := EditChatSubscriptionInviteLink(AChatId, AInviteLink,
  Default(TTgEditChatSubscriptionInviteLinkOptions));
end;

function TTgApi.EditChatSubscriptionInviteLinkAsync(const AChatId: TTgChatId;
  const AInviteLink: string; const AOptions: TTgEditChatSubscriptionInviteLinkOptions;
  const AOnSuccess: TProc<ITgChatInviteLink>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgChatInviteLink>;
begin
  LExec := ExecEditChatSubscriptionInviteLink;
  Result := RunAsyncCall<ITgChatInviteLink>(BuildEditChatSubscriptionInviteLinkParams(AChatId, AInviteLink, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.EditChatSubscriptionInviteLinkAsync(const AChatId: TTgChatId;
  const AInviteLink: string; const AOnSuccess: TProc<ITgChatInviteLink>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := EditChatSubscriptionInviteLinkAsync(AChatId, AInviteLink,
  Default(TTgEditChatSubscriptionInviteLinkOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryEditChatSubscriptionInviteLink(const AChatId: TTgChatId;
  const AInviteLink: string; const AOptions: TTgEditChatSubscriptionInviteLinkOptions;
  out AResult: ITgChatInviteLink; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgChatInviteLink);
  AError := TTgErrorInfo.Empty;
  try
    AResult := EditChatSubscriptionInviteLink(AChatId, AInviteLink, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryEditChatSubscriptionInviteLink(const AChatId: TTgChatId;
  const AInviteLink: string; out AResult: ITgChatInviteLink; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryEditChatSubscriptionInviteLink(AChatId, AInviteLink,
  Default(TTgEditChatSubscriptionInviteLinkOptions), AResult, AError);
end;

function TTgApi.BuildRevokeChatInviteLinkParams(const AChatId: TTgChatId;
  const AInviteLink: string): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('invite_link', AInviteLink);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecRevokeChatInviteLink(AParams: TTgParams): ITgChatInviteLink;
var
  LValue: TJSONValue;
begin
  LValue := Call('revokeChatInviteLink', AParams);
  Result := TTgDto.ResultObject<ITgChatInviteLink>(LValue, 'revokeChatInviteLink',
    TgMakeChatInviteLink);
end;

function TTgApi.RevokeChatInviteLink(const AChatId: TTgChatId;
  const AInviteLink: string): ITgChatInviteLink;
var
  LParams: TTgParams;
begin
  LParams := BuildRevokeChatInviteLinkParams(AChatId, AInviteLink);
  try
    Result := ExecRevokeChatInviteLink(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.RevokeChatInviteLinkAsync(const AChatId: TTgChatId; const AInviteLink: string;
  const AOnSuccess: TProc<ITgChatInviteLink>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgChatInviteLink>;
begin
  LExec := ExecRevokeChatInviteLink;
  Result := RunAsyncCall<ITgChatInviteLink>(BuildRevokeChatInviteLinkParams(AChatId, AInviteLink),
    LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryRevokeChatInviteLink(const AChatId: TTgChatId; const AInviteLink: string;
  out AResult: ITgChatInviteLink; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgChatInviteLink);
  AError := TTgErrorInfo.Empty;
  try
    AResult := RevokeChatInviteLink(AChatId, AInviteLink);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildApproveChatJoinRequestParams(const AChatId: TTgChatId;
  AUserId: Int64): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('user_id', AUserId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecApproveChatJoinRequest(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('approveChatJoinRequest', AParams);
  Result := TTgDto.ResultBool(LValue, 'approveChatJoinRequest');
end;

function TTgApi.ApproveChatJoinRequest(const AChatId: TTgChatId; AUserId: Int64): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildApproveChatJoinRequestParams(AChatId, AUserId);
  try
    Result := ExecApproveChatJoinRequest(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.ApproveChatJoinRequestAsync(const AChatId: TTgChatId; AUserId: Int64;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecApproveChatJoinRequest;
  Result := RunAsyncCall<Boolean>(BuildApproveChatJoinRequestParams(AChatId, AUserId), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.TryApproveChatJoinRequest(const AChatId: TTgChatId; AUserId: Int64;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    ApproveChatJoinRequest(AChatId, AUserId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildDeclineChatJoinRequestParams(const AChatId: TTgChatId;
  AUserId: Int64): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('user_id', AUserId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecDeclineChatJoinRequest(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('declineChatJoinRequest', AParams);
  Result := TTgDto.ResultBool(LValue, 'declineChatJoinRequest');
end;

function TTgApi.DeclineChatJoinRequest(const AChatId: TTgChatId; AUserId: Int64): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildDeclineChatJoinRequestParams(AChatId, AUserId);
  try
    Result := ExecDeclineChatJoinRequest(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.DeclineChatJoinRequestAsync(const AChatId: TTgChatId; AUserId: Int64;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecDeclineChatJoinRequest;
  Result := RunAsyncCall<Boolean>(BuildDeclineChatJoinRequestParams(AChatId, AUserId), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.TryDeclineChatJoinRequest(const AChatId: TTgChatId; AUserId: Int64;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    DeclineChatJoinRequest(AChatId, AUserId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildAnswerChatJoinRequestQueryParams(const AChatJoinRequestQueryId: string;
  const AChatJoinRequestQueryResult: string): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('chat_join_request_query_id', AChatJoinRequestQueryId);
    Result.Add('result', AChatJoinRequestQueryResult);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecAnswerChatJoinRequestQuery(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('answerChatJoinRequestQuery', AParams);
  Result := TTgDto.ResultBool(LValue, 'answerChatJoinRequestQuery');
end;

function TTgApi.AnswerChatJoinRequestQuery(const AChatJoinRequestQueryId: string;
  const AChatJoinRequestQueryResult: string): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildAnswerChatJoinRequestQueryParams(AChatJoinRequestQueryId,
    AChatJoinRequestQueryResult);
  try
    Result := ExecAnswerChatJoinRequestQuery(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.AnswerChatJoinRequestQueryAsync(const AChatJoinRequestQueryId: string;
  const AChatJoinRequestQueryResult: string; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecAnswerChatJoinRequestQuery;
  Result := RunAsyncCall<Boolean>(BuildAnswerChatJoinRequestQueryParams(AChatJoinRequestQueryId, AChatJoinRequestQueryResult), LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryAnswerChatJoinRequestQuery(const AChatJoinRequestQueryId: string;
  const AChatJoinRequestQueryResult: string; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    AnswerChatJoinRequestQuery(AChatJoinRequestQueryId, AChatJoinRequestQueryResult);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildSendChatJoinRequestWebAppParams(const AChatJoinRequestQueryId: string;
  const AWebAppUrl: string): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('chat_join_request_query_id', AChatJoinRequestQueryId);
    Result.Add('web_app_url', AWebAppUrl);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSendChatJoinRequestWebApp(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('sendChatJoinRequestWebApp', AParams);
  Result := TTgDto.ResultBool(LValue, 'sendChatJoinRequestWebApp');
end;

function TTgApi.SendChatJoinRequestWebApp(const AChatJoinRequestQueryId: string;
  const AWebAppUrl: string): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSendChatJoinRequestWebAppParams(AChatJoinRequestQueryId, AWebAppUrl);
  try
    Result := ExecSendChatJoinRequestWebApp(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SendChatJoinRequestWebAppAsync(const AChatJoinRequestQueryId: string;
  const AWebAppUrl: string; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSendChatJoinRequestWebApp;
  Result := RunAsyncCall<Boolean>(BuildSendChatJoinRequestWebAppParams(AChatJoinRequestQueryId, AWebAppUrl), LExec, AOnSuccess, AOnError);
end;

function TTgApi.TrySendChatJoinRequestWebApp(const AChatJoinRequestQueryId: string;
  const AWebAppUrl: string; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SendChatJoinRequestWebApp(AChatJoinRequestQueryId, AWebAppUrl);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildSetChatPhotoParams(const AChatId: TTgChatId;
  const APhoto: TTgInputFile): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.AddFile('photo', APhoto);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetChatPhoto(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setChatPhoto', AParams);
  Result := TTgDto.ResultBool(LValue, 'setChatPhoto');
end;

function TTgApi.SetChatPhoto(const AChatId: TTgChatId; const APhoto: TTgInputFile): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetChatPhotoParams(AChatId, APhoto);
  try
    Result := ExecSetChatPhoto(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetChatPhotoAsync(const AChatId: TTgChatId; const APhoto: TTgInputFile;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetChatPhoto;
  Result := RunAsyncCall<Boolean>(BuildSetChatPhotoParams(AChatId, APhoto), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.TrySetChatPhoto(const AChatId: TTgChatId; const APhoto: TTgInputFile;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetChatPhoto(AChatId, APhoto);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildDeleteChatPhotoParams(const AChatId: TTgChatId): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecDeleteChatPhoto(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('deleteChatPhoto', AParams);
  Result := TTgDto.ResultBool(LValue, 'deleteChatPhoto');
end;

function TTgApi.DeleteChatPhoto(const AChatId: TTgChatId): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildDeleteChatPhotoParams(AChatId);
  try
    Result := ExecDeleteChatPhoto(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.DeleteChatPhotoAsync(const AChatId: TTgChatId; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecDeleteChatPhoto;
  Result := RunAsyncCall<Boolean>(BuildDeleteChatPhotoParams(AChatId), LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryDeleteChatPhoto(const AChatId: TTgChatId; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    DeleteChatPhoto(AChatId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildSetChatTitleParams(const AChatId: TTgChatId; const ATitle: string): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('title', ATitle);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetChatTitle(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setChatTitle', AParams);
  Result := TTgDto.ResultBool(LValue, 'setChatTitle');
end;

function TTgApi.SetChatTitle(const AChatId: TTgChatId; const ATitle: string): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetChatTitleParams(AChatId, ATitle);
  try
    Result := ExecSetChatTitle(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetChatTitleAsync(const AChatId: TTgChatId; const ATitle: string;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetChatTitle;
  Result := RunAsyncCall<Boolean>(BuildSetChatTitleParams(AChatId, ATitle), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.TrySetChatTitle(const AChatId: TTgChatId; const ATitle: string;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetChatTitle(AChatId, ATitle);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildSetChatDescriptionParams(const AChatId: TTgChatId;
  const AOptions: TTgSetChatDescriptionOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetChatDescription(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setChatDescription', AParams);
  Result := TTgDto.ResultBool(LValue, 'setChatDescription');
end;

function TTgApi.SetChatDescription(const AChatId: TTgChatId;
  const AOptions: TTgSetChatDescriptionOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetChatDescriptionParams(AChatId, AOptions);
  try
    Result := ExecSetChatDescription(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetChatDescription(const AChatId: TTgChatId): Boolean;
begin
  Result := SetChatDescription(AChatId, Default(TTgSetChatDescriptionOptions));
end;

function TTgApi.SetChatDescriptionAsync(const AChatId: TTgChatId;
  const AOptions: TTgSetChatDescriptionOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetChatDescription;
  Result := RunAsyncCall<Boolean>(BuildSetChatDescriptionParams(AChatId, AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.SetChatDescriptionAsync(const AChatId: TTgChatId; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := SetChatDescriptionAsync(AChatId, Default(TTgSetChatDescriptionOptions), AOnSuccess,
  AOnError);
end;

function TTgApi.TrySetChatDescription(const AChatId: TTgChatId;
  const AOptions: TTgSetChatDescriptionOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetChatDescription(AChatId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySetChatDescription(const AChatId: TTgChatId; out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySetChatDescription(AChatId, Default(TTgSetChatDescriptionOptions), AError);
end;

function TTgApi.BuildPinChatMessageParams(const AChatId: TTgChatId; AMessageId: Int64;
  const AOptions: TTgPinChatMessageOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('message_id', AMessageId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecPinChatMessage(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('pinChatMessage', AParams);
  Result := TTgDto.ResultBool(LValue, 'pinChatMessage');
end;

function TTgApi.PinChatMessage(const AChatId: TTgChatId; AMessageId: Int64;
  const AOptions: TTgPinChatMessageOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildPinChatMessageParams(AChatId, AMessageId, AOptions);
  try
    Result := ExecPinChatMessage(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.PinChatMessage(const AChatId: TTgChatId; AMessageId: Int64): Boolean;
begin
  Result := PinChatMessage(AChatId, AMessageId, Default(TTgPinChatMessageOptions));
end;

function TTgApi.PinChatMessageAsync(const AChatId: TTgChatId; AMessageId: Int64;
  const AOptions: TTgPinChatMessageOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecPinChatMessage;
  Result := RunAsyncCall<Boolean>(BuildPinChatMessageParams(AChatId, AMessageId, AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.PinChatMessageAsync(const AChatId: TTgChatId; AMessageId: Int64;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
begin
  Result := PinChatMessageAsync(AChatId, AMessageId, Default(TTgPinChatMessageOptions), AOnSuccess,
  AOnError);
end;

function TTgApi.TryPinChatMessage(const AChatId: TTgChatId; AMessageId: Int64;
  const AOptions: TTgPinChatMessageOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    PinChatMessage(AChatId, AMessageId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryPinChatMessage(const AChatId: TTgChatId; AMessageId: Int64;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryPinChatMessage(AChatId, AMessageId, Default(TTgPinChatMessageOptions), AError);
end;

function TTgApi.BuildUnpinChatMessageParams(const AChatId: TTgChatId;
  const AOptions: TTgUnpinChatMessageOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecUnpinChatMessage(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('unpinChatMessage', AParams);
  Result := TTgDto.ResultBool(LValue, 'unpinChatMessage');
end;

function TTgApi.UnpinChatMessage(const AChatId: TTgChatId;
  const AOptions: TTgUnpinChatMessageOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildUnpinChatMessageParams(AChatId, AOptions);
  try
    Result := ExecUnpinChatMessage(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.UnpinChatMessage(const AChatId: TTgChatId): Boolean;
begin
  Result := UnpinChatMessage(AChatId, Default(TTgUnpinChatMessageOptions));
end;

function TTgApi.UnpinChatMessageAsync(const AChatId: TTgChatId;
  const AOptions: TTgUnpinChatMessageOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecUnpinChatMessage;
  Result := RunAsyncCall<Boolean>(BuildUnpinChatMessageParams(AChatId, AOptions), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.UnpinChatMessageAsync(const AChatId: TTgChatId; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := UnpinChatMessageAsync(AChatId, Default(TTgUnpinChatMessageOptions), AOnSuccess,
  AOnError);
end;

function TTgApi.TryUnpinChatMessage(const AChatId: TTgChatId;
  const AOptions: TTgUnpinChatMessageOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    UnpinChatMessage(AChatId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryUnpinChatMessage(const AChatId: TTgChatId; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryUnpinChatMessage(AChatId, Default(TTgUnpinChatMessageOptions), AError);
end;

function TTgApi.BuildUnpinAllChatMessagesParams(const AChatId: TTgChatId): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecUnpinAllChatMessages(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('unpinAllChatMessages', AParams);
  Result := TTgDto.ResultBool(LValue, 'unpinAllChatMessages');
end;

function TTgApi.UnpinAllChatMessages(const AChatId: TTgChatId): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildUnpinAllChatMessagesParams(AChatId);
  try
    Result := ExecUnpinAllChatMessages(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.UnpinAllChatMessagesAsync(const AChatId: TTgChatId;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecUnpinAllChatMessages;
  Result := RunAsyncCall<Boolean>(BuildUnpinAllChatMessagesParams(AChatId), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.TryUnpinAllChatMessages(const AChatId: TTgChatId;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    UnpinAllChatMessages(AChatId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildLeaveChatParams(const AChatId: TTgChatId): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecLeaveChat(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('leaveChat', AParams);
  Result := TTgDto.ResultBool(LValue, 'leaveChat');
end;

function TTgApi.LeaveChat(const AChatId: TTgChatId): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildLeaveChatParams(AChatId);
  try
    Result := ExecLeaveChat(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.LeaveChatAsync(const AChatId: TTgChatId; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecLeaveChat;
  Result := RunAsyncCall<Boolean>(BuildLeaveChatParams(AChatId), LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryLeaveChat(const AChatId: TTgChatId; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    LeaveChat(AChatId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildGetChatParams(const AChatId: TTgChatId): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecGetChat(AParams: TTgParams): ITgChatFullInfo;
var
  LValue: TJSONValue;
begin
  LValue := Call('getChat', AParams);
  Result := TTgDto.ResultObject<ITgChatFullInfo>(LValue, 'getChat', TgMakeChatFullInfo);
end;

function TTgApi.GetChat(const AChatId: TTgChatId): ITgChatFullInfo;
var
  LParams: TTgParams;
begin
  LParams := BuildGetChatParams(AChatId);
  try
    Result := ExecGetChat(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.GetChatAsync(const AChatId: TTgChatId; const AOnSuccess: TProc<ITgChatFullInfo>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgChatFullInfo>;
begin
  LExec := ExecGetChat;
  Result := RunAsyncCall<ITgChatFullInfo>(BuildGetChatParams(AChatId), LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryGetChat(const AChatId: TTgChatId; out AResult: ITgChatFullInfo;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgChatFullInfo);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetChat(AChatId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildGetChatAdministratorsParams(const AChatId: TTgChatId;
  const AOptions: TTgGetChatAdministratorsOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecGetChatAdministrators(AParams: TTgParams): TArray<ITgChatMember>;
var
  LValue: TJSONValue;
begin
  LValue := Call('getChatAdministrators', AParams);
  Result := TTgDto.ResultArray<ITgChatMember>(LValue, 'getChatAdministrators', TgMakeChatMember);
end;

function TTgApi.GetChatAdministrators(const AChatId: TTgChatId;
  const AOptions: TTgGetChatAdministratorsOptions): TArray<ITgChatMember>;
var
  LParams: TTgParams;
begin
  LParams := BuildGetChatAdministratorsParams(AChatId, AOptions);
  try
    Result := ExecGetChatAdministrators(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.GetChatAdministrators(const AChatId: TTgChatId): TArray<ITgChatMember>;
begin
  Result := GetChatAdministrators(AChatId, Default(TTgGetChatAdministratorsOptions));
end;

function TTgApi.GetChatAdministratorsAsync(const AChatId: TTgChatId;
  const AOptions: TTgGetChatAdministratorsOptions; const AOnSuccess: TProc<TArray<ITgChatMember>>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<TArray<ITgChatMember>>;
begin
  LExec := ExecGetChatAdministrators;
  Result := RunAsyncCall<TArray<ITgChatMember>>(BuildGetChatAdministratorsParams(AChatId, AOptions),
    LExec, AOnSuccess, AOnError);
end;

function TTgApi.GetChatAdministratorsAsync(const AChatId: TTgChatId;
  const AOnSuccess: TProc<TArray<ITgChatMember>>; const AOnError: TProc<Exception>): ITask;
begin
  Result := GetChatAdministratorsAsync(AChatId, Default(TTgGetChatAdministratorsOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TryGetChatAdministrators(const AChatId: TTgChatId;
  const AOptions: TTgGetChatAdministratorsOptions; out AResult: TArray<ITgChatMember>;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(TArray<ITgChatMember>);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetChatAdministrators(AChatId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryGetChatAdministrators(const AChatId: TTgChatId;
  out AResult: TArray<ITgChatMember>; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryGetChatAdministrators(AChatId, Default(TTgGetChatAdministratorsOptions), AResult,
  AError);
end;

function TTgApi.BuildGetChatMemberCountParams(const AChatId: TTgChatId): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecGetChatMemberCount(AParams: TTgParams): Integer;
var
  LValue: TJSONValue;
begin
  LValue := Call('getChatMemberCount', AParams);
  Result := TTgDto.ResultInt(LValue, 'getChatMemberCount');
end;

function TTgApi.GetChatMemberCount(const AChatId: TTgChatId): Integer;
var
  LParams: TTgParams;
begin
  LParams := BuildGetChatMemberCountParams(AChatId);
  try
    Result := ExecGetChatMemberCount(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.GetChatMemberCountAsync(const AChatId: TTgChatId; const AOnSuccess: TProc<Integer>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Integer>;
begin
  LExec := ExecGetChatMemberCount;
  Result := RunAsyncCall<Integer>(BuildGetChatMemberCountParams(AChatId), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.TryGetChatMemberCount(const AChatId: TTgChatId; out AResult: Integer;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(Integer);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetChatMemberCount(AChatId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildGetChatMemberParams(const AChatId: TTgChatId; AUserId: Int64): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('user_id', AUserId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecGetChatMember(AParams: TTgParams): ITgChatMember;
var
  LValue: TJSONValue;
begin
  LValue := Call('getChatMember', AParams);
  Result := TTgDto.ResultObject<ITgChatMember>(LValue, 'getChatMember', TgMakeChatMember);
end;

function TTgApi.GetChatMember(const AChatId: TTgChatId; AUserId: Int64): ITgChatMember;
var
  LParams: TTgParams;
begin
  LParams := BuildGetChatMemberParams(AChatId, AUserId);
  try
    Result := ExecGetChatMember(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.GetChatMemberAsync(const AChatId: TTgChatId; AUserId: Int64;
  const AOnSuccess: TProc<ITgChatMember>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgChatMember>;
begin
  LExec := ExecGetChatMember;
  Result := RunAsyncCall<ITgChatMember>(BuildGetChatMemberParams(AChatId, AUserId), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.TryGetChatMember(const AChatId: TTgChatId; AUserId: Int64;
  out AResult: ITgChatMember; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgChatMember);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetChatMember(AChatId, AUserId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildGetUserPersonalChatMessagesParams(AUserId: Int64; ALimit: Integer): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('user_id', AUserId);
    Result.Add('limit', ALimit);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecGetUserPersonalChatMessages(AParams: TTgParams): TArray<ITgMessage>;
var
  LValue: TJSONValue;
begin
  LValue := Call('getUserPersonalChatMessages', AParams);
  Result := TTgDto.ResultArray<ITgMessage>(LValue, 'getUserPersonalChatMessages', TgMakeMessage);
end;

function TTgApi.GetUserPersonalChatMessages(AUserId: Int64; ALimit: Integer): TArray<ITgMessage>;
var
  LParams: TTgParams;
begin
  LParams := BuildGetUserPersonalChatMessagesParams(AUserId, ALimit);
  try
    Result := ExecGetUserPersonalChatMessages(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.GetUserPersonalChatMessagesAsync(AUserId: Int64; ALimit: Integer;
  const AOnSuccess: TProc<TArray<ITgMessage>>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<TArray<ITgMessage>>;
begin
  LExec := ExecGetUserPersonalChatMessages;
  Result := RunAsyncCall<TArray<ITgMessage>>(BuildGetUserPersonalChatMessagesParams(AUserId, ALimit), LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryGetUserPersonalChatMessages(AUserId: Int64; ALimit: Integer;
  out AResult: TArray<ITgMessage>; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(TArray<ITgMessage>);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetUserPersonalChatMessages(AUserId, ALimit);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildSetChatStickerSetParams(const AChatId: TTgChatId;
  const AStickerSetName: string): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('sticker_set_name', AStickerSetName);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetChatStickerSet(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setChatStickerSet', AParams);
  Result := TTgDto.ResultBool(LValue, 'setChatStickerSet');
end;

function TTgApi.SetChatStickerSet(const AChatId: TTgChatId; const AStickerSetName: string): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetChatStickerSetParams(AChatId, AStickerSetName);
  try
    Result := ExecSetChatStickerSet(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetChatStickerSetAsync(const AChatId: TTgChatId; const AStickerSetName: string;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetChatStickerSet;
  Result := RunAsyncCall<Boolean>(BuildSetChatStickerSetParams(AChatId, AStickerSetName), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.TrySetChatStickerSet(const AChatId: TTgChatId; const AStickerSetName: string;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetChatStickerSet(AChatId, AStickerSetName);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildDeleteChatStickerSetParams(const AChatId: TTgChatId): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecDeleteChatStickerSet(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('deleteChatStickerSet', AParams);
  Result := TTgDto.ResultBool(LValue, 'deleteChatStickerSet');
end;

function TTgApi.DeleteChatStickerSet(const AChatId: TTgChatId): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildDeleteChatStickerSetParams(AChatId);
  try
    Result := ExecDeleteChatStickerSet(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.DeleteChatStickerSetAsync(const AChatId: TTgChatId;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecDeleteChatStickerSet;
  Result := RunAsyncCall<Boolean>(BuildDeleteChatStickerSetParams(AChatId), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.TryDeleteChatStickerSet(const AChatId: TTgChatId;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    DeleteChatStickerSet(AChatId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.ExecGetForumTopicIconStickers(AParams: TTgParams): TArray<ITgSticker>;
var
  LValue: TJSONValue;
begin
  LValue := Call('getForumTopicIconStickers', AParams);
  Result := TTgDto.ResultArray<ITgSticker>(LValue, 'getForumTopicIconStickers', TgMakeSticker);
end;

function TTgApi.GetForumTopicIconStickers: TArray<ITgSticker>;
begin
  Result := ExecGetForumTopicIconStickers(nil);
end;

function TTgApi.GetForumTopicIconStickersAsync(const AOnSuccess: TProc<TArray<ITgSticker>>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<TArray<ITgSticker>>;
begin
  LExec := ExecGetForumTopicIconStickers;
  Result := RunAsyncCall<TArray<ITgSticker>>(nil, LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryGetForumTopicIconStickers(out AResult: TArray<ITgSticker>;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(TArray<ITgSticker>);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetForumTopicIconStickers;
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildCreateForumTopicParams(const AChatId: TTgChatId; const AName: string;
  const AOptions: TTgCreateForumTopicOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('name', AName);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecCreateForumTopic(AParams: TTgParams): ITgForumTopic;
var
  LValue: TJSONValue;
begin
  LValue := Call('createForumTopic', AParams);
  Result := TTgDto.ResultObject<ITgForumTopic>(LValue, 'createForumTopic', TgMakeForumTopic);
end;

function TTgApi.CreateForumTopic(const AChatId: TTgChatId; const AName: string;
  const AOptions: TTgCreateForumTopicOptions): ITgForumTopic;
var
  LParams: TTgParams;
begin
  LParams := BuildCreateForumTopicParams(AChatId, AName, AOptions);
  try
    Result := ExecCreateForumTopic(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.CreateForumTopic(const AChatId: TTgChatId; const AName: string): ITgForumTopic;
begin
  Result := CreateForumTopic(AChatId, AName, Default(TTgCreateForumTopicOptions));
end;

function TTgApi.CreateForumTopicAsync(const AChatId: TTgChatId; const AName: string;
  const AOptions: TTgCreateForumTopicOptions; const AOnSuccess: TProc<ITgForumTopic>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgForumTopic>;
begin
  LExec := ExecCreateForumTopic;
  Result := RunAsyncCall<ITgForumTopic>(BuildCreateForumTopicParams(AChatId, AName, AOptions),
    LExec, AOnSuccess, AOnError);
end;

function TTgApi.CreateForumTopicAsync(const AChatId: TTgChatId; const AName: string;
  const AOnSuccess: TProc<ITgForumTopic>; const AOnError: TProc<Exception>): ITask;
begin
  Result := CreateForumTopicAsync(AChatId, AName, Default(TTgCreateForumTopicOptions), AOnSuccess,
  AOnError);
end;

function TTgApi.TryCreateForumTopic(const AChatId: TTgChatId; const AName: string;
  const AOptions: TTgCreateForumTopicOptions; out AResult: ITgForumTopic;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgForumTopic);
  AError := TTgErrorInfo.Empty;
  try
    AResult := CreateForumTopic(AChatId, AName, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryCreateForumTopic(const AChatId: TTgChatId; const AName: string;
  out AResult: ITgForumTopic; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryCreateForumTopic(AChatId, AName, Default(TTgCreateForumTopicOptions), AResult,
  AError);
end;

function TTgApi.BuildEditForumTopicParams(const AChatId: TTgChatId; AMessageThreadId: Int64;
  const AOptions: TTgEditForumTopicOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('message_thread_id', AMessageThreadId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecEditForumTopic(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('editForumTopic', AParams);
  Result := TTgDto.ResultBool(LValue, 'editForumTopic');
end;

function TTgApi.EditForumTopic(const AChatId: TTgChatId; AMessageThreadId: Int64;
  const AOptions: TTgEditForumTopicOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildEditForumTopicParams(AChatId, AMessageThreadId, AOptions);
  try
    Result := ExecEditForumTopic(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.EditForumTopic(const AChatId: TTgChatId; AMessageThreadId: Int64): Boolean;
begin
  Result := EditForumTopic(AChatId, AMessageThreadId, Default(TTgEditForumTopicOptions));
end;

function TTgApi.EditForumTopicAsync(const AChatId: TTgChatId; AMessageThreadId: Int64;
  const AOptions: TTgEditForumTopicOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecEditForumTopic;
  Result := RunAsyncCall<Boolean>(BuildEditForumTopicParams(AChatId, AMessageThreadId, AOptions),
    LExec, AOnSuccess, AOnError);
end;

function TTgApi.EditForumTopicAsync(const AChatId: TTgChatId; AMessageThreadId: Int64;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
begin
  Result := EditForumTopicAsync(AChatId, AMessageThreadId, Default(TTgEditForumTopicOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TryEditForumTopic(const AChatId: TTgChatId; AMessageThreadId: Int64;
  const AOptions: TTgEditForumTopicOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    EditForumTopic(AChatId, AMessageThreadId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryEditForumTopic(const AChatId: TTgChatId; AMessageThreadId: Int64;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryEditForumTopic(AChatId, AMessageThreadId, Default(TTgEditForumTopicOptions), AError);
end;

function TTgApi.BuildCloseForumTopicParams(const AChatId: TTgChatId;
  AMessageThreadId: Int64): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('message_thread_id', AMessageThreadId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecCloseForumTopic(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('closeForumTopic', AParams);
  Result := TTgDto.ResultBool(LValue, 'closeForumTopic');
end;

function TTgApi.CloseForumTopic(const AChatId: TTgChatId; AMessageThreadId: Int64): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildCloseForumTopicParams(AChatId, AMessageThreadId);
  try
    Result := ExecCloseForumTopic(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.CloseForumTopicAsync(const AChatId: TTgChatId; AMessageThreadId: Int64;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecCloseForumTopic;
  Result := RunAsyncCall<Boolean>(BuildCloseForumTopicParams(AChatId, AMessageThreadId), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.TryCloseForumTopic(const AChatId: TTgChatId; AMessageThreadId: Int64;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    CloseForumTopic(AChatId, AMessageThreadId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildReopenForumTopicParams(const AChatId: TTgChatId;
  AMessageThreadId: Int64): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('message_thread_id', AMessageThreadId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecReopenForumTopic(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('reopenForumTopic', AParams);
  Result := TTgDto.ResultBool(LValue, 'reopenForumTopic');
end;

function TTgApi.ReopenForumTopic(const AChatId: TTgChatId; AMessageThreadId: Int64): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildReopenForumTopicParams(AChatId, AMessageThreadId);
  try
    Result := ExecReopenForumTopic(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.ReopenForumTopicAsync(const AChatId: TTgChatId; AMessageThreadId: Int64;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecReopenForumTopic;
  Result := RunAsyncCall<Boolean>(BuildReopenForumTopicParams(AChatId, AMessageThreadId), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.TryReopenForumTopic(const AChatId: TTgChatId; AMessageThreadId: Int64;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    ReopenForumTopic(AChatId, AMessageThreadId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildDeleteForumTopicParams(const AChatId: TTgChatId;
  AMessageThreadId: Int64): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('message_thread_id', AMessageThreadId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecDeleteForumTopic(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('deleteForumTopic', AParams);
  Result := TTgDto.ResultBool(LValue, 'deleteForumTopic');
end;

function TTgApi.DeleteForumTopic(const AChatId: TTgChatId; AMessageThreadId: Int64): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildDeleteForumTopicParams(AChatId, AMessageThreadId);
  try
    Result := ExecDeleteForumTopic(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.DeleteForumTopicAsync(const AChatId: TTgChatId; AMessageThreadId: Int64;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecDeleteForumTopic;
  Result := RunAsyncCall<Boolean>(BuildDeleteForumTopicParams(AChatId, AMessageThreadId), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.TryDeleteForumTopic(const AChatId: TTgChatId; AMessageThreadId: Int64;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    DeleteForumTopic(AChatId, AMessageThreadId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildUnpinAllForumTopicMessagesParams(const AChatId: TTgChatId;
  AMessageThreadId: Int64): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('message_thread_id', AMessageThreadId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecUnpinAllForumTopicMessages(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('unpinAllForumTopicMessages', AParams);
  Result := TTgDto.ResultBool(LValue, 'unpinAllForumTopicMessages');
end;

function TTgApi.UnpinAllForumTopicMessages(const AChatId: TTgChatId;
  AMessageThreadId: Int64): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildUnpinAllForumTopicMessagesParams(AChatId, AMessageThreadId);
  try
    Result := ExecUnpinAllForumTopicMessages(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.UnpinAllForumTopicMessagesAsync(const AChatId: TTgChatId; AMessageThreadId: Int64;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecUnpinAllForumTopicMessages;
  Result := RunAsyncCall<Boolean>(BuildUnpinAllForumTopicMessagesParams(AChatId, AMessageThreadId),
    LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryUnpinAllForumTopicMessages(const AChatId: TTgChatId; AMessageThreadId: Int64;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    UnpinAllForumTopicMessages(AChatId, AMessageThreadId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildEditGeneralForumTopicParams(const AChatId: TTgChatId;
  const AName: string): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('name', AName);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecEditGeneralForumTopic(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('editGeneralForumTopic', AParams);
  Result := TTgDto.ResultBool(LValue, 'editGeneralForumTopic');
end;

function TTgApi.EditGeneralForumTopic(const AChatId: TTgChatId; const AName: string): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildEditGeneralForumTopicParams(AChatId, AName);
  try
    Result := ExecEditGeneralForumTopic(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.EditGeneralForumTopicAsync(const AChatId: TTgChatId; const AName: string;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecEditGeneralForumTopic;
  Result := RunAsyncCall<Boolean>(BuildEditGeneralForumTopicParams(AChatId, AName), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.TryEditGeneralForumTopic(const AChatId: TTgChatId; const AName: string;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    EditGeneralForumTopic(AChatId, AName);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildCloseGeneralForumTopicParams(const AChatId: TTgChatId): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecCloseGeneralForumTopic(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('closeGeneralForumTopic', AParams);
  Result := TTgDto.ResultBool(LValue, 'closeGeneralForumTopic');
end;

function TTgApi.CloseGeneralForumTopic(const AChatId: TTgChatId): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildCloseGeneralForumTopicParams(AChatId);
  try
    Result := ExecCloseGeneralForumTopic(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.CloseGeneralForumTopicAsync(const AChatId: TTgChatId;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecCloseGeneralForumTopic;
  Result := RunAsyncCall<Boolean>(BuildCloseGeneralForumTopicParams(AChatId), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.TryCloseGeneralForumTopic(const AChatId: TTgChatId;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    CloseGeneralForumTopic(AChatId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildReopenGeneralForumTopicParams(const AChatId: TTgChatId): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecReopenGeneralForumTopic(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('reopenGeneralForumTopic', AParams);
  Result := TTgDto.ResultBool(LValue, 'reopenGeneralForumTopic');
end;

function TTgApi.ReopenGeneralForumTopic(const AChatId: TTgChatId): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildReopenGeneralForumTopicParams(AChatId);
  try
    Result := ExecReopenGeneralForumTopic(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.ReopenGeneralForumTopicAsync(const AChatId: TTgChatId;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecReopenGeneralForumTopic;
  Result := RunAsyncCall<Boolean>(BuildReopenGeneralForumTopicParams(AChatId), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.TryReopenGeneralForumTopic(const AChatId: TTgChatId;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    ReopenGeneralForumTopic(AChatId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildHideGeneralForumTopicParams(const AChatId: TTgChatId): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecHideGeneralForumTopic(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('hideGeneralForumTopic', AParams);
  Result := TTgDto.ResultBool(LValue, 'hideGeneralForumTopic');
end;

function TTgApi.HideGeneralForumTopic(const AChatId: TTgChatId): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildHideGeneralForumTopicParams(AChatId);
  try
    Result := ExecHideGeneralForumTopic(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.HideGeneralForumTopicAsync(const AChatId: TTgChatId;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecHideGeneralForumTopic;
  Result := RunAsyncCall<Boolean>(BuildHideGeneralForumTopicParams(AChatId), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.TryHideGeneralForumTopic(const AChatId: TTgChatId;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    HideGeneralForumTopic(AChatId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildUnhideGeneralForumTopicParams(const AChatId: TTgChatId): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecUnhideGeneralForumTopic(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('unhideGeneralForumTopic', AParams);
  Result := TTgDto.ResultBool(LValue, 'unhideGeneralForumTopic');
end;

function TTgApi.UnhideGeneralForumTopic(const AChatId: TTgChatId): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildUnhideGeneralForumTopicParams(AChatId);
  try
    Result := ExecUnhideGeneralForumTopic(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.UnhideGeneralForumTopicAsync(const AChatId: TTgChatId;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecUnhideGeneralForumTopic;
  Result := RunAsyncCall<Boolean>(BuildUnhideGeneralForumTopicParams(AChatId), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.TryUnhideGeneralForumTopic(const AChatId: TTgChatId;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    UnhideGeneralForumTopic(AChatId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildUnpinAllGeneralForumTopicMessagesParams(const AChatId: TTgChatId): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecUnpinAllGeneralForumTopicMessages(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('unpinAllGeneralForumTopicMessages', AParams);
  Result := TTgDto.ResultBool(LValue, 'unpinAllGeneralForumTopicMessages');
end;

function TTgApi.UnpinAllGeneralForumTopicMessages(const AChatId: TTgChatId): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildUnpinAllGeneralForumTopicMessagesParams(AChatId);
  try
    Result := ExecUnpinAllGeneralForumTopicMessages(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.UnpinAllGeneralForumTopicMessagesAsync(const AChatId: TTgChatId;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecUnpinAllGeneralForumTopicMessages;
  Result := RunAsyncCall<Boolean>(BuildUnpinAllGeneralForumTopicMessagesParams(AChatId), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.TryUnpinAllGeneralForumTopicMessages(const AChatId: TTgChatId;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    UnpinAllGeneralForumTopicMessages(AChatId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildAnswerCallbackQueryParams(const ACallbackQueryId: string;
  const AOptions: TTgAnswerCallbackQueryOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('callback_query_id', ACallbackQueryId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecAnswerCallbackQuery(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('answerCallbackQuery', AParams);
  Result := TTgDto.ResultBool(LValue, 'answerCallbackQuery');
end;

function TTgApi.AnswerCallbackQuery(const ACallbackQueryId: string;
  const AOptions: TTgAnswerCallbackQueryOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildAnswerCallbackQueryParams(ACallbackQueryId, AOptions);
  try
    Result := ExecAnswerCallbackQuery(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.AnswerCallbackQuery(const ACallbackQueryId: string): Boolean;
begin
  Result := AnswerCallbackQuery(ACallbackQueryId, Default(TTgAnswerCallbackQueryOptions));
end;

function TTgApi.AnswerCallbackQueryAsync(const ACallbackQueryId: string;
  const AOptions: TTgAnswerCallbackQueryOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecAnswerCallbackQuery;
  Result := RunAsyncCall<Boolean>(BuildAnswerCallbackQueryParams(ACallbackQueryId, AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.AnswerCallbackQueryAsync(const ACallbackQueryId: string;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
begin
  Result := AnswerCallbackQueryAsync(ACallbackQueryId, Default(TTgAnswerCallbackQueryOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TryAnswerCallbackQuery(const ACallbackQueryId: string;
  const AOptions: TTgAnswerCallbackQueryOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    AnswerCallbackQuery(ACallbackQueryId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryAnswerCallbackQuery(const ACallbackQueryId: string;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryAnswerCallbackQuery(ACallbackQueryId, Default(TTgAnswerCallbackQueryOptions),
  AError);
end;

function TTgApi.BuildAnswerCallbackQueryVariant1Params(const ACallbackQueryId: string;
  const AText: string; const AOptions: TTgAnswerCallbackQueryOptions): TTgParams;
var
  LOptions: TTgAnswerCallbackQueryOptions;
begin
  LOptions := AOptions;
  LOptions.Text := AText;
  Result := BuildAnswerCallbackQueryParams(ACallbackQueryId, LOptions);
end;

function TTgApi.AnswerCallbackQuery(const ACallbackQueryId: string; const AText: string;
  const AOptions: TTgAnswerCallbackQueryOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildAnswerCallbackQueryVariant1Params(ACallbackQueryId, AText, AOptions);
  try
    Result := ExecAnswerCallbackQuery(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.AnswerCallbackQuery(const ACallbackQueryId: string; const AText: string): Boolean;
begin
  Result := AnswerCallbackQuery(ACallbackQueryId, AText, Default(TTgAnswerCallbackQueryOptions));
end;

function TTgApi.AnswerCallbackQueryAsync(const ACallbackQueryId: string; const AText: string;
  const AOptions: TTgAnswerCallbackQueryOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecAnswerCallbackQuery;
  Result := RunAsyncCall<Boolean>(BuildAnswerCallbackQueryVariant1Params(ACallbackQueryId, AText, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.AnswerCallbackQueryAsync(const ACallbackQueryId: string; const AText: string;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
begin
  Result := AnswerCallbackQueryAsync(ACallbackQueryId, AText,
  Default(TTgAnswerCallbackQueryOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryAnswerCallbackQuery(const ACallbackQueryId: string; const AText: string;
  const AOptions: TTgAnswerCallbackQueryOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    AnswerCallbackQuery(ACallbackQueryId, AText, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryAnswerCallbackQuery(const ACallbackQueryId: string; const AText: string;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryAnswerCallbackQuery(ACallbackQueryId, AText, Default(TTgAnswerCallbackQueryOptions),
  AError);
end;

function TTgApi.BuildAnswerCallbackQueryVariant2Params(const ACallbackQueryId: string;
  const AText: string; AShowAlert: Boolean;
  const AOptions: TTgAnswerCallbackQueryOptions): TTgParams;
var
  LOptions: TTgAnswerCallbackQueryOptions;
begin
  LOptions := AOptions;
  LOptions.Text := AText;
  LOptions.ShowAlert := AShowAlert;
  Result := BuildAnswerCallbackQueryParams(ACallbackQueryId, LOptions);
end;

function TTgApi.AnswerCallbackQuery(const ACallbackQueryId: string; const AText: string;
  AShowAlert: Boolean; const AOptions: TTgAnswerCallbackQueryOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildAnswerCallbackQueryVariant2Params(ACallbackQueryId, AText, AShowAlert, AOptions);
  try
    Result := ExecAnswerCallbackQuery(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.AnswerCallbackQuery(const ACallbackQueryId: string; const AText: string;
  AShowAlert: Boolean): Boolean;
begin
  Result := AnswerCallbackQuery(ACallbackQueryId, AText, AShowAlert,
  Default(TTgAnswerCallbackQueryOptions));
end;

function TTgApi.AnswerCallbackQueryAsync(const ACallbackQueryId: string; const AText: string;
  AShowAlert: Boolean; const AOptions: TTgAnswerCallbackQueryOptions;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecAnswerCallbackQuery;
  Result := RunAsyncCall<Boolean>(BuildAnswerCallbackQueryVariant2Params(ACallbackQueryId, AText, AShowAlert, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.AnswerCallbackQueryAsync(const ACallbackQueryId: string; const AText: string;
  AShowAlert: Boolean; const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
begin
  Result := AnswerCallbackQueryAsync(ACallbackQueryId, AText, AShowAlert,
  Default(TTgAnswerCallbackQueryOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryAnswerCallbackQuery(const ACallbackQueryId: string; const AText: string;
  AShowAlert: Boolean; const AOptions: TTgAnswerCallbackQueryOptions;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    AnswerCallbackQuery(ACallbackQueryId, AText, AShowAlert, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryAnswerCallbackQuery(const ACallbackQueryId: string; const AText: string;
  AShowAlert: Boolean; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryAnswerCallbackQuery(ACallbackQueryId, AText, AShowAlert,
  Default(TTgAnswerCallbackQueryOptions), AError);
end;

function TTgApi.BuildAnswerGuestQueryParams(const AGuestQueryId: string;
  const AGuestQueryResult: TTgInlineQueryResult): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('guest_query_id', AGuestQueryId);
    Result.AddJson('result', TTgDto.Serialize(AGuestQueryResult.Value, Result));
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecAnswerGuestQuery(AParams: TTgParams): ITgSentGuestMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('answerGuestQuery', AParams);
  Result := TTgDto.ResultObject<ITgSentGuestMessage>(LValue, 'answerGuestQuery',
    TgMakeSentGuestMessage);
end;

function TTgApi.AnswerGuestQuery(const AGuestQueryId: string;
  const AGuestQueryResult: TTgInlineQueryResult): ITgSentGuestMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildAnswerGuestQueryParams(AGuestQueryId, AGuestQueryResult);
  try
    Result := ExecAnswerGuestQuery(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.AnswerGuestQueryAsync(const AGuestQueryId: string;
  const AGuestQueryResult: TTgInlineQueryResult; const AOnSuccess: TProc<ITgSentGuestMessage>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgSentGuestMessage>;
begin
  LExec := ExecAnswerGuestQuery;
  Result := RunAsyncCall<ITgSentGuestMessage>(BuildAnswerGuestQueryParams(AGuestQueryId, AGuestQueryResult), LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryAnswerGuestQuery(const AGuestQueryId: string;
  const AGuestQueryResult: TTgInlineQueryResult; out AResult: ITgSentGuestMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgSentGuestMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := AnswerGuestQuery(AGuestQueryId, AGuestQueryResult);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildGetUserChatBoostsParams(const AChatId: TTgChatId; AUserId: Int64): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('user_id', AUserId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecGetUserChatBoosts(AParams: TTgParams): ITgUserChatBoosts;
var
  LValue: TJSONValue;
begin
  LValue := Call('getUserChatBoosts', AParams);
  Result := TTgDto.ResultObject<ITgUserChatBoosts>(LValue, 'getUserChatBoosts',
    TgMakeUserChatBoosts);
end;

function TTgApi.GetUserChatBoosts(const AChatId: TTgChatId; AUserId: Int64): ITgUserChatBoosts;
var
  LParams: TTgParams;
begin
  LParams := BuildGetUserChatBoostsParams(AChatId, AUserId);
  try
    Result := ExecGetUserChatBoosts(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.GetUserChatBoostsAsync(const AChatId: TTgChatId; AUserId: Int64;
  const AOnSuccess: TProc<ITgUserChatBoosts>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgUserChatBoosts>;
begin
  LExec := ExecGetUserChatBoosts;
  Result := RunAsyncCall<ITgUserChatBoosts>(BuildGetUserChatBoostsParams(AChatId, AUserId), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.TryGetUserChatBoosts(const AChatId: TTgChatId; AUserId: Int64;
  out AResult: ITgUserChatBoosts; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgUserChatBoosts);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetUserChatBoosts(AChatId, AUserId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildGetBusinessConnectionParams(const ABusinessConnectionId: string): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('business_connection_id', ABusinessConnectionId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecGetBusinessConnection(AParams: TTgParams): ITgBusinessConnection;
var
  LValue: TJSONValue;
begin
  LValue := Call('getBusinessConnection', AParams);
  Result := TTgDto.ResultObject<ITgBusinessConnection>(LValue, 'getBusinessConnection',
    TgMakeBusinessConnection);
end;

function TTgApi.GetBusinessConnection(const ABusinessConnectionId: string): ITgBusinessConnection;
var
  LParams: TTgParams;
begin
  LParams := BuildGetBusinessConnectionParams(ABusinessConnectionId);
  try
    Result := ExecGetBusinessConnection(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.GetBusinessConnectionAsync(const ABusinessConnectionId: string;
  const AOnSuccess: TProc<ITgBusinessConnection>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgBusinessConnection>;
begin
  LExec := ExecGetBusinessConnection;
  Result := RunAsyncCall<ITgBusinessConnection>(BuildGetBusinessConnectionParams(ABusinessConnectionId), LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryGetBusinessConnection(const ABusinessConnectionId: string;
  out AResult: ITgBusinessConnection; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgBusinessConnection);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetBusinessConnection(ABusinessConnectionId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildGetManagedBotTokenParams(AUserId: Int64): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('user_id', AUserId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecGetManagedBotToken(AParams: TTgParams): string;
var
  LValue: TJSONValue;
begin
  LValue := Call('getManagedBotToken', AParams);
  Result := TTgDto.ResultStr(LValue, 'getManagedBotToken');
end;

function TTgApi.GetManagedBotToken(AUserId: Int64): string;
var
  LParams: TTgParams;
begin
  LParams := BuildGetManagedBotTokenParams(AUserId);
  try
    Result := ExecGetManagedBotToken(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.GetManagedBotTokenAsync(AUserId: Int64; const AOnSuccess: TProc<string>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<string>;
begin
  LExec := ExecGetManagedBotToken;
  Result := RunAsyncCall<string>(BuildGetManagedBotTokenParams(AUserId), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.TryGetManagedBotToken(AUserId: Int64; out AResult: string;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(string);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetManagedBotToken(AUserId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildReplaceManagedBotTokenParams(AUserId: Int64): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('user_id', AUserId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecReplaceManagedBotToken(AParams: TTgParams): string;
var
  LValue: TJSONValue;
begin
  LValue := Call('replaceManagedBotToken', AParams);
  Result := TTgDto.ResultStr(LValue, 'replaceManagedBotToken');
end;

function TTgApi.ReplaceManagedBotToken(AUserId: Int64): string;
var
  LParams: TTgParams;
begin
  LParams := BuildReplaceManagedBotTokenParams(AUserId);
  try
    Result := ExecReplaceManagedBotToken(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.ReplaceManagedBotTokenAsync(AUserId: Int64; const AOnSuccess: TProc<string>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<string>;
begin
  LExec := ExecReplaceManagedBotToken;
  Result := RunAsyncCall<string>(BuildReplaceManagedBotTokenParams(AUserId), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.TryReplaceManagedBotToken(AUserId: Int64; out AResult: string;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(string);
  AError := TTgErrorInfo.Empty;
  try
    AResult := ReplaceManagedBotToken(AUserId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildGetManagedBotAccessSettingsParams(AUserId: Int64): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('user_id', AUserId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecGetManagedBotAccessSettings(AParams: TTgParams): ITgBotAccessSettings;
var
  LValue: TJSONValue;
begin
  LValue := Call('getManagedBotAccessSettings', AParams);
  Result := TTgDto.ResultObject<ITgBotAccessSettings>(LValue, 'getManagedBotAccessSettings',
    TgMakeBotAccessSettings);
end;

function TTgApi.GetManagedBotAccessSettings(AUserId: Int64): ITgBotAccessSettings;
var
  LParams: TTgParams;
begin
  LParams := BuildGetManagedBotAccessSettingsParams(AUserId);
  try
    Result := ExecGetManagedBotAccessSettings(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.GetManagedBotAccessSettingsAsync(AUserId: Int64;
  const AOnSuccess: TProc<ITgBotAccessSettings>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgBotAccessSettings>;
begin
  LExec := ExecGetManagedBotAccessSettings;
  Result := RunAsyncCall<ITgBotAccessSettings>(BuildGetManagedBotAccessSettingsParams(AUserId),
    LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryGetManagedBotAccessSettings(AUserId: Int64; out AResult: ITgBotAccessSettings;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgBotAccessSettings);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetManagedBotAccessSettings(AUserId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildSetManagedBotAccessSettingsParams(AUserId: Int64; AIsAccessRestricted: Boolean;
  const AOptions: TTgSetManagedBotAccessSettingsOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('user_id', AUserId);
    Result.Add('is_access_restricted', AIsAccessRestricted);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetManagedBotAccessSettings(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setManagedBotAccessSettings', AParams);
  Result := TTgDto.ResultBool(LValue, 'setManagedBotAccessSettings');
end;

function TTgApi.SetManagedBotAccessSettings(AUserId: Int64; AIsAccessRestricted: Boolean;
  const AOptions: TTgSetManagedBotAccessSettingsOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetManagedBotAccessSettingsParams(AUserId, AIsAccessRestricted, AOptions);
  try
    Result := ExecSetManagedBotAccessSettings(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetManagedBotAccessSettings(AUserId: Int64; AIsAccessRestricted: Boolean): Boolean;
begin
  Result := SetManagedBotAccessSettings(AUserId, AIsAccessRestricted,
  Default(TTgSetManagedBotAccessSettingsOptions));
end;

function TTgApi.SetManagedBotAccessSettingsAsync(AUserId: Int64; AIsAccessRestricted: Boolean;
  const AOptions: TTgSetManagedBotAccessSettingsOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetManagedBotAccessSettings;
  Result := RunAsyncCall<Boolean>(BuildSetManagedBotAccessSettingsParams(AUserId, AIsAccessRestricted, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.SetManagedBotAccessSettingsAsync(AUserId: Int64; AIsAccessRestricted: Boolean;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
begin
  Result := SetManagedBotAccessSettingsAsync(AUserId, AIsAccessRestricted,
  Default(TTgSetManagedBotAccessSettingsOptions), AOnSuccess, AOnError);
end;

function TTgApi.TrySetManagedBotAccessSettings(AUserId: Int64; AIsAccessRestricted: Boolean;
  const AOptions: TTgSetManagedBotAccessSettingsOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetManagedBotAccessSettings(AUserId, AIsAccessRestricted, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySetManagedBotAccessSettings(AUserId: Int64; AIsAccessRestricted: Boolean;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySetManagedBotAccessSettings(AUserId, AIsAccessRestricted,
  Default(TTgSetManagedBotAccessSettingsOptions), AError);
end;

function TTgApi.BuildSetMyCommandsParams(const ACommands: array of ITgBotCommand;
  const AOptions: TTgSetMyCommandsOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddJson('commands',
      TTgDto.SerializeArray(TTgDto.ToIntf<ITgBotCommand>(ACommands), Result, 'commands'));
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetMyCommands(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setMyCommands', AParams);
  Result := TTgDto.ResultBool(LValue, 'setMyCommands');
end;

function TTgApi.SetMyCommands(const ACommands: array of ITgBotCommand;
  const AOptions: TTgSetMyCommandsOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetMyCommandsParams(ACommands, AOptions);
  try
    Result := ExecSetMyCommands(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetMyCommands(const ACommands: array of ITgBotCommand): Boolean;
begin
  Result := SetMyCommands(ACommands, Default(TTgSetMyCommandsOptions));
end;

function TTgApi.SetMyCommandsAsync(const ACommands: array of ITgBotCommand;
  const AOptions: TTgSetMyCommandsOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetMyCommands;
  Result := RunAsyncCall<Boolean>(BuildSetMyCommandsParams(ACommands, AOptions), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.SetMyCommandsAsync(const ACommands: array of ITgBotCommand;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
begin
  Result := SetMyCommandsAsync(ACommands, Default(TTgSetMyCommandsOptions), AOnSuccess, AOnError);
end;

function TTgApi.TrySetMyCommands(const ACommands: array of ITgBotCommand;
  const AOptions: TTgSetMyCommandsOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetMyCommands(ACommands, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySetMyCommands(const ACommands: array of ITgBotCommand;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySetMyCommands(ACommands, Default(TTgSetMyCommandsOptions), AError);
end;

function TTgApi.BuildDeleteMyCommandsParams(const AOptions: TTgDeleteMyCommandsOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecDeleteMyCommands(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('deleteMyCommands', AParams);
  Result := TTgDto.ResultBool(LValue, 'deleteMyCommands');
end;

function TTgApi.DeleteMyCommands(const AOptions: TTgDeleteMyCommandsOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildDeleteMyCommandsParams(AOptions);
  try
    Result := ExecDeleteMyCommands(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.DeleteMyCommands: Boolean;
begin
  Result := DeleteMyCommands(Default(TTgDeleteMyCommandsOptions));
end;

function TTgApi.DeleteMyCommandsAsync(const AOptions: TTgDeleteMyCommandsOptions;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecDeleteMyCommands;
  Result := RunAsyncCall<Boolean>(BuildDeleteMyCommandsParams(AOptions), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.DeleteMyCommandsAsync(const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := DeleteMyCommandsAsync(Default(TTgDeleteMyCommandsOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryDeleteMyCommands(const AOptions: TTgDeleteMyCommandsOptions;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    DeleteMyCommands(AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryDeleteMyCommands(out AError: TTgErrorInfo): Boolean;
begin
  Result := TryDeleteMyCommands(Default(TTgDeleteMyCommandsOptions), AError);
end;

function TTgApi.BuildGetMyCommandsParams(const AOptions: TTgGetMyCommandsOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecGetMyCommands(AParams: TTgParams): TArray<ITgBotCommand>;
var
  LValue: TJSONValue;
begin
  LValue := Call('getMyCommands', AParams);
  Result := TTgDto.ResultArray<ITgBotCommand>(LValue, 'getMyCommands', TgMakeBotCommand);
end;

function TTgApi.GetMyCommands(const AOptions: TTgGetMyCommandsOptions): TArray<ITgBotCommand>;
var
  LParams: TTgParams;
begin
  LParams := BuildGetMyCommandsParams(AOptions);
  try
    Result := ExecGetMyCommands(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.GetMyCommands: TArray<ITgBotCommand>;
begin
  Result := GetMyCommands(Default(TTgGetMyCommandsOptions));
end;

function TTgApi.GetMyCommandsAsync(const AOptions: TTgGetMyCommandsOptions;
  const AOnSuccess: TProc<TArray<ITgBotCommand>>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<TArray<ITgBotCommand>>;
begin
  LExec := ExecGetMyCommands;
  Result := RunAsyncCall<TArray<ITgBotCommand>>(BuildGetMyCommandsParams(AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.GetMyCommandsAsync(const AOnSuccess: TProc<TArray<ITgBotCommand>>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := GetMyCommandsAsync(Default(TTgGetMyCommandsOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryGetMyCommands(const AOptions: TTgGetMyCommandsOptions;
  out AResult: TArray<ITgBotCommand>; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(TArray<ITgBotCommand>);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetMyCommands(AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryGetMyCommands(out AResult: TArray<ITgBotCommand>;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryGetMyCommands(Default(TTgGetMyCommandsOptions), AResult, AError);
end;

function TTgApi.BuildSetMyNameParams(const AOptions: TTgSetMyNameOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetMyName(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setMyName', AParams);
  Result := TTgDto.ResultBool(LValue, 'setMyName');
end;

function TTgApi.SetMyName(const AOptions: TTgSetMyNameOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetMyNameParams(AOptions);
  try
    Result := ExecSetMyName(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetMyName: Boolean;
begin
  Result := SetMyName(Default(TTgSetMyNameOptions));
end;

function TTgApi.SetMyNameAsync(const AOptions: TTgSetMyNameOptions;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetMyName;
  Result := RunAsyncCall<Boolean>(BuildSetMyNameParams(AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.SetMyNameAsync(const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := SetMyNameAsync(Default(TTgSetMyNameOptions), AOnSuccess, AOnError);
end;

function TTgApi.TrySetMyName(const AOptions: TTgSetMyNameOptions;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetMyName(AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySetMyName(out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySetMyName(Default(TTgSetMyNameOptions), AError);
end;

function TTgApi.BuildGetMyNameParams(const AOptions: TTgGetMyNameOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecGetMyName(AParams: TTgParams): ITgBotName;
var
  LValue: TJSONValue;
begin
  LValue := Call('getMyName', AParams);
  Result := TTgDto.ResultObject<ITgBotName>(LValue, 'getMyName', TgMakeBotName);
end;

function TTgApi.GetMyName(const AOptions: TTgGetMyNameOptions): ITgBotName;
var
  LParams: TTgParams;
begin
  LParams := BuildGetMyNameParams(AOptions);
  try
    Result := ExecGetMyName(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.GetMyName: ITgBotName;
begin
  Result := GetMyName(Default(TTgGetMyNameOptions));
end;

function TTgApi.GetMyNameAsync(const AOptions: TTgGetMyNameOptions;
  const AOnSuccess: TProc<ITgBotName>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgBotName>;
begin
  LExec := ExecGetMyName;
  Result := RunAsyncCall<ITgBotName>(BuildGetMyNameParams(AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.GetMyNameAsync(const AOnSuccess: TProc<ITgBotName>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := GetMyNameAsync(Default(TTgGetMyNameOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryGetMyName(const AOptions: TTgGetMyNameOptions; out AResult: ITgBotName;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgBotName);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetMyName(AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryGetMyName(out AResult: ITgBotName; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryGetMyName(Default(TTgGetMyNameOptions), AResult, AError);
end;

function TTgApi.BuildSetMyDescriptionParams(const AOptions: TTgSetMyDescriptionOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetMyDescription(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setMyDescription', AParams);
  Result := TTgDto.ResultBool(LValue, 'setMyDescription');
end;

function TTgApi.SetMyDescription(const AOptions: TTgSetMyDescriptionOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetMyDescriptionParams(AOptions);
  try
    Result := ExecSetMyDescription(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetMyDescription: Boolean;
begin
  Result := SetMyDescription(Default(TTgSetMyDescriptionOptions));
end;

function TTgApi.SetMyDescriptionAsync(const AOptions: TTgSetMyDescriptionOptions;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetMyDescription;
  Result := RunAsyncCall<Boolean>(BuildSetMyDescriptionParams(AOptions), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.SetMyDescriptionAsync(const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := SetMyDescriptionAsync(Default(TTgSetMyDescriptionOptions), AOnSuccess, AOnError);
end;

function TTgApi.TrySetMyDescription(const AOptions: TTgSetMyDescriptionOptions;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetMyDescription(AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySetMyDescription(out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySetMyDescription(Default(TTgSetMyDescriptionOptions), AError);
end;

function TTgApi.BuildGetMyDescriptionParams(const AOptions: TTgGetMyDescriptionOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecGetMyDescription(AParams: TTgParams): ITgBotDescription;
var
  LValue: TJSONValue;
begin
  LValue := Call('getMyDescription', AParams);
  Result := TTgDto.ResultObject<ITgBotDescription>(LValue, 'getMyDescription',
    TgMakeBotDescription);
end;

function TTgApi.GetMyDescription(const AOptions: TTgGetMyDescriptionOptions): ITgBotDescription;
var
  LParams: TTgParams;
begin
  LParams := BuildGetMyDescriptionParams(AOptions);
  try
    Result := ExecGetMyDescription(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.GetMyDescription: ITgBotDescription;
begin
  Result := GetMyDescription(Default(TTgGetMyDescriptionOptions));
end;

function TTgApi.GetMyDescriptionAsync(const AOptions: TTgGetMyDescriptionOptions;
  const AOnSuccess: TProc<ITgBotDescription>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgBotDescription>;
begin
  LExec := ExecGetMyDescription;
  Result := RunAsyncCall<ITgBotDescription>(BuildGetMyDescriptionParams(AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.GetMyDescriptionAsync(const AOnSuccess: TProc<ITgBotDescription>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := GetMyDescriptionAsync(Default(TTgGetMyDescriptionOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryGetMyDescription(const AOptions: TTgGetMyDescriptionOptions;
  out AResult: ITgBotDescription; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgBotDescription);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetMyDescription(AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryGetMyDescription(out AResult: ITgBotDescription;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryGetMyDescription(Default(TTgGetMyDescriptionOptions), AResult, AError);
end;

function TTgApi.BuildSetMyShortDescriptionParams(const AOptions: TTgSetMyShortDescriptionOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetMyShortDescription(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setMyShortDescription', AParams);
  Result := TTgDto.ResultBool(LValue, 'setMyShortDescription');
end;

function TTgApi.SetMyShortDescription(const AOptions: TTgSetMyShortDescriptionOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetMyShortDescriptionParams(AOptions);
  try
    Result := ExecSetMyShortDescription(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetMyShortDescription: Boolean;
begin
  Result := SetMyShortDescription(Default(TTgSetMyShortDescriptionOptions));
end;

function TTgApi.SetMyShortDescriptionAsync(const AOptions: TTgSetMyShortDescriptionOptions;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetMyShortDescription;
  Result := RunAsyncCall<Boolean>(BuildSetMyShortDescriptionParams(AOptions), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.SetMyShortDescriptionAsync(const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := SetMyShortDescriptionAsync(Default(TTgSetMyShortDescriptionOptions), AOnSuccess,
  AOnError);
end;

function TTgApi.TrySetMyShortDescription(const AOptions: TTgSetMyShortDescriptionOptions;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetMyShortDescription(AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySetMyShortDescription(out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySetMyShortDescription(Default(TTgSetMyShortDescriptionOptions), AError);
end;

function TTgApi.BuildGetMyShortDescriptionParams(const AOptions: TTgGetMyShortDescriptionOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecGetMyShortDescription(AParams: TTgParams): ITgBotShortDescription;
var
  LValue: TJSONValue;
begin
  LValue := Call('getMyShortDescription', AParams);
  Result := TTgDto.ResultObject<ITgBotShortDescription>(LValue, 'getMyShortDescription',
    TgMakeBotShortDescription);
end;

function TTgApi.GetMyShortDescription(const AOptions: TTgGetMyShortDescriptionOptions): ITgBotShortDescription;
var
  LParams: TTgParams;
begin
  LParams := BuildGetMyShortDescriptionParams(AOptions);
  try
    Result := ExecGetMyShortDescription(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.GetMyShortDescription: ITgBotShortDescription;
begin
  Result := GetMyShortDescription(Default(TTgGetMyShortDescriptionOptions));
end;

function TTgApi.GetMyShortDescriptionAsync(const AOptions: TTgGetMyShortDescriptionOptions;
  const AOnSuccess: TProc<ITgBotShortDescription>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgBotShortDescription>;
begin
  LExec := ExecGetMyShortDescription;
  Result := RunAsyncCall<ITgBotShortDescription>(BuildGetMyShortDescriptionParams(AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.GetMyShortDescriptionAsync(const AOnSuccess: TProc<ITgBotShortDescription>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := GetMyShortDescriptionAsync(Default(TTgGetMyShortDescriptionOptions), AOnSuccess,
  AOnError);
end;

function TTgApi.TryGetMyShortDescription(const AOptions: TTgGetMyShortDescriptionOptions;
  out AResult: ITgBotShortDescription; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgBotShortDescription);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetMyShortDescription(AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryGetMyShortDescription(out AResult: ITgBotShortDescription;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryGetMyShortDescription(Default(TTgGetMyShortDescriptionOptions), AResult, AError);
end;

function TTgApi.BuildSetMyProfilePhotoParams(const APhoto: TTgInputProfilePhoto): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddJson('photo', TTgDto.Serialize(APhoto.Value, Result));
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetMyProfilePhoto(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setMyProfilePhoto', AParams);
  Result := TTgDto.ResultBool(LValue, 'setMyProfilePhoto');
end;

function TTgApi.SetMyProfilePhoto(const APhoto: TTgInputProfilePhoto): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetMyProfilePhotoParams(APhoto);
  try
    Result := ExecSetMyProfilePhoto(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetMyProfilePhotoAsync(const APhoto: TTgInputProfilePhoto;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetMyProfilePhoto;
  Result := RunAsyncCall<Boolean>(BuildSetMyProfilePhotoParams(APhoto), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.TrySetMyProfilePhoto(const APhoto: TTgInputProfilePhoto;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetMyProfilePhoto(APhoto);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.ExecRemoveMyProfilePhoto(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('removeMyProfilePhoto', AParams);
  Result := TTgDto.ResultBool(LValue, 'removeMyProfilePhoto');
end;

function TTgApi.RemoveMyProfilePhoto: Boolean;
begin
  Result := ExecRemoveMyProfilePhoto(nil);
end;

function TTgApi.RemoveMyProfilePhotoAsync(const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecRemoveMyProfilePhoto;
  Result := RunAsyncCall<Boolean>(nil, LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryRemoveMyProfilePhoto(out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    RemoveMyProfilePhoto;
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildSetChatMenuButtonParams(const AOptions: TTgSetChatMenuButtonOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetChatMenuButton(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setChatMenuButton', AParams);
  Result := TTgDto.ResultBool(LValue, 'setChatMenuButton');
end;

function TTgApi.SetChatMenuButton(const AOptions: TTgSetChatMenuButtonOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetChatMenuButtonParams(AOptions);
  try
    Result := ExecSetChatMenuButton(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetChatMenuButton: Boolean;
begin
  Result := SetChatMenuButton(Default(TTgSetChatMenuButtonOptions));
end;

function TTgApi.SetChatMenuButtonAsync(const AOptions: TTgSetChatMenuButtonOptions;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetChatMenuButton;
  Result := RunAsyncCall<Boolean>(BuildSetChatMenuButtonParams(AOptions), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.SetChatMenuButtonAsync(const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := SetChatMenuButtonAsync(Default(TTgSetChatMenuButtonOptions), AOnSuccess, AOnError);
end;

function TTgApi.TrySetChatMenuButton(const AOptions: TTgSetChatMenuButtonOptions;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetChatMenuButton(AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySetChatMenuButton(out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySetChatMenuButton(Default(TTgSetChatMenuButtonOptions), AError);
end;

function TTgApi.BuildGetChatMenuButtonParams(const AOptions: TTgGetChatMenuButtonOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecGetChatMenuButton(AParams: TTgParams): ITgMenuButton;
var
  LValue: TJSONValue;
begin
  LValue := Call('getChatMenuButton', AParams);
  Result := TTgDto.ResultObject<ITgMenuButton>(LValue, 'getChatMenuButton', TgMakeMenuButton);
end;

function TTgApi.GetChatMenuButton(const AOptions: TTgGetChatMenuButtonOptions): ITgMenuButton;
var
  LParams: TTgParams;
begin
  LParams := BuildGetChatMenuButtonParams(AOptions);
  try
    Result := ExecGetChatMenuButton(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.GetChatMenuButton: ITgMenuButton;
begin
  Result := GetChatMenuButton(Default(TTgGetChatMenuButtonOptions));
end;

function TTgApi.GetChatMenuButtonAsync(const AOptions: TTgGetChatMenuButtonOptions;
  const AOnSuccess: TProc<ITgMenuButton>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMenuButton>;
begin
  LExec := ExecGetChatMenuButton;
  Result := RunAsyncCall<ITgMenuButton>(BuildGetChatMenuButtonParams(AOptions), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.GetChatMenuButtonAsync(const AOnSuccess: TProc<ITgMenuButton>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := GetChatMenuButtonAsync(Default(TTgGetChatMenuButtonOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryGetChatMenuButton(const AOptions: TTgGetChatMenuButtonOptions;
  out AResult: ITgMenuButton; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMenuButton);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetChatMenuButton(AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryGetChatMenuButton(out AResult: ITgMenuButton; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryGetChatMenuButton(Default(TTgGetChatMenuButtonOptions), AResult, AError);
end;

function TTgApi.BuildSetMyDefaultAdministratorRightsParams(const AOptions: TTgSetMyDefaultAdministratorRightsOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetMyDefaultAdministratorRights(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setMyDefaultAdministratorRights', AParams);
  Result := TTgDto.ResultBool(LValue, 'setMyDefaultAdministratorRights');
end;

function TTgApi.SetMyDefaultAdministratorRights(const AOptions: TTgSetMyDefaultAdministratorRightsOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetMyDefaultAdministratorRightsParams(AOptions);
  try
    Result := ExecSetMyDefaultAdministratorRights(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetMyDefaultAdministratorRights: Boolean;
begin
  Result := SetMyDefaultAdministratorRights(Default(TTgSetMyDefaultAdministratorRightsOptions));
end;

function TTgApi.SetMyDefaultAdministratorRightsAsync(const AOptions: TTgSetMyDefaultAdministratorRightsOptions; const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetMyDefaultAdministratorRights;
  Result := RunAsyncCall<Boolean>(BuildSetMyDefaultAdministratorRightsParams(AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.SetMyDefaultAdministratorRightsAsync(const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := SetMyDefaultAdministratorRightsAsync(Default(TTgSetMyDefaultAdministratorRightsOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TrySetMyDefaultAdministratorRights(const AOptions: TTgSetMyDefaultAdministratorRightsOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetMyDefaultAdministratorRights(AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySetMyDefaultAdministratorRights(out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySetMyDefaultAdministratorRights(Default(TTgSetMyDefaultAdministratorRightsOptions),
  AError);
end;

function TTgApi.BuildGetMyDefaultAdministratorRightsParams(const AOptions: TTgGetMyDefaultAdministratorRightsOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecGetMyDefaultAdministratorRights(AParams: TTgParams): ITgChatAdministratorRights;
var
  LValue: TJSONValue;
begin
  LValue := Call('getMyDefaultAdministratorRights', AParams);
  Result := TTgDto.ResultObject<ITgChatAdministratorRights>(LValue,
    'getMyDefaultAdministratorRights', TgMakeChatAdministratorRights);
end;

function TTgApi.GetMyDefaultAdministratorRights(const AOptions: TTgGetMyDefaultAdministratorRightsOptions): ITgChatAdministratorRights;
var
  LParams: TTgParams;
begin
  LParams := BuildGetMyDefaultAdministratorRightsParams(AOptions);
  try
    Result := ExecGetMyDefaultAdministratorRights(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.GetMyDefaultAdministratorRights: ITgChatAdministratorRights;
begin
  Result := GetMyDefaultAdministratorRights(Default(TTgGetMyDefaultAdministratorRightsOptions));
end;

function TTgApi.GetMyDefaultAdministratorRightsAsync(const AOptions: TTgGetMyDefaultAdministratorRightsOptions; const AOnSuccess: TProc<ITgChatAdministratorRights>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgChatAdministratorRights>;
begin
  LExec := ExecGetMyDefaultAdministratorRights;
  Result := RunAsyncCall<ITgChatAdministratorRights>(BuildGetMyDefaultAdministratorRightsParams(AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.GetMyDefaultAdministratorRightsAsync(const AOnSuccess: TProc<ITgChatAdministratorRights>; const AOnError: TProc<Exception>): ITask;
begin
  Result := GetMyDefaultAdministratorRightsAsync(Default(TTgGetMyDefaultAdministratorRightsOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TryGetMyDefaultAdministratorRights(const AOptions: TTgGetMyDefaultAdministratorRightsOptions; out AResult: ITgChatAdministratorRights; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgChatAdministratorRights);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetMyDefaultAdministratorRights(AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryGetMyDefaultAdministratorRights(out AResult: ITgChatAdministratorRights;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryGetMyDefaultAdministratorRights(Default(TTgGetMyDefaultAdministratorRightsOptions),
  AResult, AError);
end;

function TTgApi.ExecGetAvailableGifts(AParams: TTgParams): ITgGifts;
var
  LValue: TJSONValue;
begin
  LValue := Call('getAvailableGifts', AParams);
  Result := TTgDto.ResultObject<ITgGifts>(LValue, 'getAvailableGifts', TgMakeGifts);
end;

function TTgApi.GetAvailableGifts: ITgGifts;
begin
  Result := ExecGetAvailableGifts(nil);
end;

function TTgApi.GetAvailableGiftsAsync(const AOnSuccess: TProc<ITgGifts>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgGifts>;
begin
  LExec := ExecGetAvailableGifts;
  Result := RunAsyncCall<ITgGifts>(nil, LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryGetAvailableGifts(out AResult: ITgGifts; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgGifts);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetAvailableGifts;
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildSendGiftParams(const AGiftId: string;
  const AOptions: TTgSendGiftOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('gift_id', AGiftId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSendGift(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('sendGift', AParams);
  Result := TTgDto.ResultBool(LValue, 'sendGift');
end;

function TTgApi.SendGift(const AGiftId: string; const AOptions: TTgSendGiftOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSendGiftParams(AGiftId, AOptions);
  try
    Result := ExecSendGift(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SendGift(const AGiftId: string): Boolean;
begin
  Result := SendGift(AGiftId, Default(TTgSendGiftOptions));
end;

function TTgApi.SendGiftAsync(const AGiftId: string; const AOptions: TTgSendGiftOptions;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSendGift;
  Result := RunAsyncCall<Boolean>(BuildSendGiftParams(AGiftId, AOptions), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.SendGiftAsync(const AGiftId: string; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := SendGiftAsync(AGiftId, Default(TTgSendGiftOptions), AOnSuccess, AOnError);
end;

function TTgApi.TrySendGift(const AGiftId: string; const AOptions: TTgSendGiftOptions;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SendGift(AGiftId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySendGift(const AGiftId: string; out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySendGift(AGiftId, Default(TTgSendGiftOptions), AError);
end;

function TTgApi.BuildGiftPremiumSubscriptionParams(AUserId: Int64; AMonthCount: Integer;
  AStarCount: Integer; const AOptions: TTgGiftPremiumSubscriptionOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('user_id', AUserId);
    Result.Add('month_count', AMonthCount);
    Result.Add('star_count', AStarCount);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecGiftPremiumSubscription(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('giftPremiumSubscription', AParams);
  Result := TTgDto.ResultBool(LValue, 'giftPremiumSubscription');
end;

function TTgApi.GiftPremiumSubscription(AUserId: Int64; AMonthCount: Integer; AStarCount: Integer;
  const AOptions: TTgGiftPremiumSubscriptionOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildGiftPremiumSubscriptionParams(AUserId, AMonthCount, AStarCount, AOptions);
  try
    Result := ExecGiftPremiumSubscription(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.GiftPremiumSubscription(AUserId: Int64; AMonthCount: Integer;
  AStarCount: Integer): Boolean;
begin
  Result := GiftPremiumSubscription(AUserId, AMonthCount, AStarCount,
  Default(TTgGiftPremiumSubscriptionOptions));
end;

function TTgApi.GiftPremiumSubscriptionAsync(AUserId: Int64; AMonthCount: Integer;
  AStarCount: Integer; const AOptions: TTgGiftPremiumSubscriptionOptions;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecGiftPremiumSubscription;
  Result := RunAsyncCall<Boolean>(BuildGiftPremiumSubscriptionParams(AUserId, AMonthCount, AStarCount, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.GiftPremiumSubscriptionAsync(AUserId: Int64; AMonthCount: Integer;
  AStarCount: Integer; const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
begin
  Result := GiftPremiumSubscriptionAsync(AUserId, AMonthCount, AStarCount,
  Default(TTgGiftPremiumSubscriptionOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryGiftPremiumSubscription(AUserId: Int64; AMonthCount: Integer;
  AStarCount: Integer; const AOptions: TTgGiftPremiumSubscriptionOptions;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    GiftPremiumSubscription(AUserId, AMonthCount, AStarCount, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryGiftPremiumSubscription(AUserId: Int64; AMonthCount: Integer;
  AStarCount: Integer; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryGiftPremiumSubscription(AUserId, AMonthCount, AStarCount,
  Default(TTgGiftPremiumSubscriptionOptions), AError);
end;

function TTgApi.BuildVerifyUserParams(AUserId: Int64;
  const AOptions: TTgVerifyUserOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('user_id', AUserId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecVerifyUser(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('verifyUser', AParams);
  Result := TTgDto.ResultBool(LValue, 'verifyUser');
end;

function TTgApi.VerifyUser(AUserId: Int64; const AOptions: TTgVerifyUserOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildVerifyUserParams(AUserId, AOptions);
  try
    Result := ExecVerifyUser(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.VerifyUser(AUserId: Int64): Boolean;
begin
  Result := VerifyUser(AUserId, Default(TTgVerifyUserOptions));
end;

function TTgApi.VerifyUserAsync(AUserId: Int64; const AOptions: TTgVerifyUserOptions;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecVerifyUser;
  Result := RunAsyncCall<Boolean>(BuildVerifyUserParams(AUserId, AOptions), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.VerifyUserAsync(AUserId: Int64; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := VerifyUserAsync(AUserId, Default(TTgVerifyUserOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryVerifyUser(AUserId: Int64; const AOptions: TTgVerifyUserOptions;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    VerifyUser(AUserId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryVerifyUser(AUserId: Int64; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryVerifyUser(AUserId, Default(TTgVerifyUserOptions), AError);
end;

function TTgApi.BuildVerifyChatParams(const AChatId: TTgChatId;
  const AOptions: TTgVerifyChatOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecVerifyChat(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('verifyChat', AParams);
  Result := TTgDto.ResultBool(LValue, 'verifyChat');
end;

function TTgApi.VerifyChat(const AChatId: TTgChatId; const AOptions: TTgVerifyChatOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildVerifyChatParams(AChatId, AOptions);
  try
    Result := ExecVerifyChat(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.VerifyChat(const AChatId: TTgChatId): Boolean;
begin
  Result := VerifyChat(AChatId, Default(TTgVerifyChatOptions));
end;

function TTgApi.VerifyChatAsync(const AChatId: TTgChatId; const AOptions: TTgVerifyChatOptions;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecVerifyChat;
  Result := RunAsyncCall<Boolean>(BuildVerifyChatParams(AChatId, AOptions), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.VerifyChatAsync(const AChatId: TTgChatId; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := VerifyChatAsync(AChatId, Default(TTgVerifyChatOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryVerifyChat(const AChatId: TTgChatId; const AOptions: TTgVerifyChatOptions;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    VerifyChat(AChatId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryVerifyChat(const AChatId: TTgChatId; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryVerifyChat(AChatId, Default(TTgVerifyChatOptions), AError);
end;

function TTgApi.BuildRemoveUserVerificationParams(AUserId: Int64): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('user_id', AUserId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecRemoveUserVerification(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('removeUserVerification', AParams);
  Result := TTgDto.ResultBool(LValue, 'removeUserVerification');
end;

function TTgApi.RemoveUserVerification(AUserId: Int64): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildRemoveUserVerificationParams(AUserId);
  try
    Result := ExecRemoveUserVerification(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.RemoveUserVerificationAsync(AUserId: Int64; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecRemoveUserVerification;
  Result := RunAsyncCall<Boolean>(BuildRemoveUserVerificationParams(AUserId), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.TryRemoveUserVerification(AUserId: Int64; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    RemoveUserVerification(AUserId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildRemoveChatVerificationParams(const AChatId: TTgChatId): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecRemoveChatVerification(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('removeChatVerification', AParams);
  Result := TTgDto.ResultBool(LValue, 'removeChatVerification');
end;

function TTgApi.RemoveChatVerification(const AChatId: TTgChatId): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildRemoveChatVerificationParams(AChatId);
  try
    Result := ExecRemoveChatVerification(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.RemoveChatVerificationAsync(const AChatId: TTgChatId;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecRemoveChatVerification;
  Result := RunAsyncCall<Boolean>(BuildRemoveChatVerificationParams(AChatId), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.TryRemoveChatVerification(const AChatId: TTgChatId;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    RemoveChatVerification(AChatId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildReadBusinessMessageParams(const ABusinessConnectionId: string; AChatId: Int64;
  AMessageId: Int64): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('business_connection_id', ABusinessConnectionId);
    Result.Add('chat_id', AChatId);
    Result.Add('message_id', AMessageId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecReadBusinessMessage(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('readBusinessMessage', AParams);
  Result := TTgDto.ResultBool(LValue, 'readBusinessMessage');
end;

function TTgApi.ReadBusinessMessage(const ABusinessConnectionId: string; AChatId: Int64;
  AMessageId: Int64): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildReadBusinessMessageParams(ABusinessConnectionId, AChatId, AMessageId);
  try
    Result := ExecReadBusinessMessage(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.ReadBusinessMessageAsync(const ABusinessConnectionId: string; AChatId: Int64;
  AMessageId: Int64; const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecReadBusinessMessage;
  Result := RunAsyncCall<Boolean>(BuildReadBusinessMessageParams(ABusinessConnectionId, AChatId, AMessageId), LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryReadBusinessMessage(const ABusinessConnectionId: string; AChatId: Int64;
  AMessageId: Int64; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    ReadBusinessMessage(ABusinessConnectionId, AChatId, AMessageId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildDeleteBusinessMessagesParams(const ABusinessConnectionId: string;
  const AMessageIds: TArray<Int64>): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('business_connection_id', ABusinessConnectionId);
    Result.AddInt64s('message_ids', AMessageIds);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecDeleteBusinessMessages(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('deleteBusinessMessages', AParams);
  Result := TTgDto.ResultBool(LValue, 'deleteBusinessMessages');
end;

function TTgApi.DeleteBusinessMessages(const ABusinessConnectionId: string;
  const AMessageIds: TArray<Int64>): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildDeleteBusinessMessagesParams(ABusinessConnectionId, AMessageIds);
  try
    Result := ExecDeleteBusinessMessages(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.DeleteBusinessMessagesAsync(const ABusinessConnectionId: string;
  const AMessageIds: TArray<Int64>; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecDeleteBusinessMessages;
  Result := RunAsyncCall<Boolean>(BuildDeleteBusinessMessagesParams(ABusinessConnectionId, AMessageIds), LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryDeleteBusinessMessages(const ABusinessConnectionId: string;
  const AMessageIds: TArray<Int64>; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    DeleteBusinessMessages(ABusinessConnectionId, AMessageIds);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildSetBusinessAccountNameParams(const ABusinessConnectionId: string;
  const AFirstName: string; const AOptions: TTgSetBusinessAccountNameOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('business_connection_id', ABusinessConnectionId);
    Result.Add('first_name', AFirstName);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetBusinessAccountName(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setBusinessAccountName', AParams);
  Result := TTgDto.ResultBool(LValue, 'setBusinessAccountName');
end;

function TTgApi.SetBusinessAccountName(const ABusinessConnectionId: string;
  const AFirstName: string; const AOptions: TTgSetBusinessAccountNameOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetBusinessAccountNameParams(ABusinessConnectionId, AFirstName, AOptions);
  try
    Result := ExecSetBusinessAccountName(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetBusinessAccountName(const ABusinessConnectionId: string;
  const AFirstName: string): Boolean;
begin
  Result := SetBusinessAccountName(ABusinessConnectionId, AFirstName,
  Default(TTgSetBusinessAccountNameOptions));
end;

function TTgApi.SetBusinessAccountNameAsync(const ABusinessConnectionId: string;
  const AFirstName: string; const AOptions: TTgSetBusinessAccountNameOptions;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetBusinessAccountName;
  Result := RunAsyncCall<Boolean>(BuildSetBusinessAccountNameParams(ABusinessConnectionId, AFirstName, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.SetBusinessAccountNameAsync(const ABusinessConnectionId: string;
  const AFirstName: string; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := SetBusinessAccountNameAsync(ABusinessConnectionId, AFirstName,
  Default(TTgSetBusinessAccountNameOptions), AOnSuccess, AOnError);
end;

function TTgApi.TrySetBusinessAccountName(const ABusinessConnectionId: string;
  const AFirstName: string; const AOptions: TTgSetBusinessAccountNameOptions;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetBusinessAccountName(ABusinessConnectionId, AFirstName, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySetBusinessAccountName(const ABusinessConnectionId: string;
  const AFirstName: string; out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySetBusinessAccountName(ABusinessConnectionId, AFirstName,
  Default(TTgSetBusinessAccountNameOptions), AError);
end;

function TTgApi.BuildSetBusinessAccountUsernameParams(const ABusinessConnectionId: string;
  const AOptions: TTgSetBusinessAccountUsernameOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('business_connection_id', ABusinessConnectionId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetBusinessAccountUsername(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setBusinessAccountUsername', AParams);
  Result := TTgDto.ResultBool(LValue, 'setBusinessAccountUsername');
end;

function TTgApi.SetBusinessAccountUsername(const ABusinessConnectionId: string;
  const AOptions: TTgSetBusinessAccountUsernameOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetBusinessAccountUsernameParams(ABusinessConnectionId, AOptions);
  try
    Result := ExecSetBusinessAccountUsername(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetBusinessAccountUsername(const ABusinessConnectionId: string): Boolean;
begin
  Result := SetBusinessAccountUsername(ABusinessConnectionId,
  Default(TTgSetBusinessAccountUsernameOptions));
end;

function TTgApi.SetBusinessAccountUsernameAsync(const ABusinessConnectionId: string;
  const AOptions: TTgSetBusinessAccountUsernameOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetBusinessAccountUsername;
  Result := RunAsyncCall<Boolean>(BuildSetBusinessAccountUsernameParams(ABusinessConnectionId, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.SetBusinessAccountUsernameAsync(const ABusinessConnectionId: string;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
begin
  Result := SetBusinessAccountUsernameAsync(ABusinessConnectionId,
  Default(TTgSetBusinessAccountUsernameOptions), AOnSuccess, AOnError);
end;

function TTgApi.TrySetBusinessAccountUsername(const ABusinessConnectionId: string;
  const AOptions: TTgSetBusinessAccountUsernameOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetBusinessAccountUsername(ABusinessConnectionId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySetBusinessAccountUsername(const ABusinessConnectionId: string;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySetBusinessAccountUsername(ABusinessConnectionId,
  Default(TTgSetBusinessAccountUsernameOptions), AError);
end;

function TTgApi.BuildSetBusinessAccountBioParams(const ABusinessConnectionId: string;
  const AOptions: TTgSetBusinessAccountBioOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('business_connection_id', ABusinessConnectionId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetBusinessAccountBio(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setBusinessAccountBio', AParams);
  Result := TTgDto.ResultBool(LValue, 'setBusinessAccountBio');
end;

function TTgApi.SetBusinessAccountBio(const ABusinessConnectionId: string;
  const AOptions: TTgSetBusinessAccountBioOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetBusinessAccountBioParams(ABusinessConnectionId, AOptions);
  try
    Result := ExecSetBusinessAccountBio(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetBusinessAccountBio(const ABusinessConnectionId: string): Boolean;
begin
  Result := SetBusinessAccountBio(ABusinessConnectionId, Default(TTgSetBusinessAccountBioOptions));
end;

function TTgApi.SetBusinessAccountBioAsync(const ABusinessConnectionId: string;
  const AOptions: TTgSetBusinessAccountBioOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetBusinessAccountBio;
  Result := RunAsyncCall<Boolean>(BuildSetBusinessAccountBioParams(ABusinessConnectionId, AOptions),
    LExec, AOnSuccess, AOnError);
end;

function TTgApi.SetBusinessAccountBioAsync(const ABusinessConnectionId: string;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
begin
  Result := SetBusinessAccountBioAsync(ABusinessConnectionId,
  Default(TTgSetBusinessAccountBioOptions), AOnSuccess, AOnError);
end;

function TTgApi.TrySetBusinessAccountBio(const ABusinessConnectionId: string;
  const AOptions: TTgSetBusinessAccountBioOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetBusinessAccountBio(ABusinessConnectionId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySetBusinessAccountBio(const ABusinessConnectionId: string;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySetBusinessAccountBio(ABusinessConnectionId,
  Default(TTgSetBusinessAccountBioOptions), AError);
end;

function TTgApi.BuildSetBusinessAccountProfilePhotoParams(const ABusinessConnectionId: string;
  const APhoto: TTgInputProfilePhoto;
  const AOptions: TTgSetBusinessAccountProfilePhotoOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('business_connection_id', ABusinessConnectionId);
    Result.AddJson('photo', TTgDto.Serialize(APhoto.Value, Result));
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetBusinessAccountProfilePhoto(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setBusinessAccountProfilePhoto', AParams);
  Result := TTgDto.ResultBool(LValue, 'setBusinessAccountProfilePhoto');
end;

function TTgApi.SetBusinessAccountProfilePhoto(const ABusinessConnectionId: string;
  const APhoto: TTgInputProfilePhoto;
  const AOptions: TTgSetBusinessAccountProfilePhotoOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetBusinessAccountProfilePhotoParams(ABusinessConnectionId, APhoto, AOptions);
  try
    Result := ExecSetBusinessAccountProfilePhoto(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetBusinessAccountProfilePhoto(const ABusinessConnectionId: string;
  const APhoto: TTgInputProfilePhoto): Boolean;
begin
  Result := SetBusinessAccountProfilePhoto(ABusinessConnectionId, APhoto,
  Default(TTgSetBusinessAccountProfilePhotoOptions));
end;

function TTgApi.SetBusinessAccountProfilePhotoAsync(const ABusinessConnectionId: string;
  const APhoto: TTgInputProfilePhoto; const AOptions: TTgSetBusinessAccountProfilePhotoOptions;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetBusinessAccountProfilePhoto;
  Result := RunAsyncCall<Boolean>(BuildSetBusinessAccountProfilePhotoParams(ABusinessConnectionId, APhoto, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.SetBusinessAccountProfilePhotoAsync(const ABusinessConnectionId: string;
  const APhoto: TTgInputProfilePhoto; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := SetBusinessAccountProfilePhotoAsync(ABusinessConnectionId, APhoto,
  Default(TTgSetBusinessAccountProfilePhotoOptions), AOnSuccess, AOnError);
end;

function TTgApi.TrySetBusinessAccountProfilePhoto(const ABusinessConnectionId: string;
  const APhoto: TTgInputProfilePhoto; const AOptions: TTgSetBusinessAccountProfilePhotoOptions;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetBusinessAccountProfilePhoto(ABusinessConnectionId, APhoto, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySetBusinessAccountProfilePhoto(const ABusinessConnectionId: string;
  const APhoto: TTgInputProfilePhoto; out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySetBusinessAccountProfilePhoto(ABusinessConnectionId, APhoto,
  Default(TTgSetBusinessAccountProfilePhotoOptions), AError);
end;

function TTgApi.BuildRemoveBusinessAccountProfilePhotoParams(const ABusinessConnectionId: string;
  const AOptions: TTgRemoveBusinessAccountProfilePhotoOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('business_connection_id', ABusinessConnectionId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecRemoveBusinessAccountProfilePhoto(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('removeBusinessAccountProfilePhoto', AParams);
  Result := TTgDto.ResultBool(LValue, 'removeBusinessAccountProfilePhoto');
end;

function TTgApi.RemoveBusinessAccountProfilePhoto(const ABusinessConnectionId: string;
  const AOptions: TTgRemoveBusinessAccountProfilePhotoOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildRemoveBusinessAccountProfilePhotoParams(ABusinessConnectionId, AOptions);
  try
    Result := ExecRemoveBusinessAccountProfilePhoto(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.RemoveBusinessAccountProfilePhoto(const ABusinessConnectionId: string): Boolean;
begin
  Result := RemoveBusinessAccountProfilePhoto(ABusinessConnectionId,
  Default(TTgRemoveBusinessAccountProfilePhotoOptions));
end;

function TTgApi.RemoveBusinessAccountProfilePhotoAsync(const ABusinessConnectionId: string;
  const AOptions: TTgRemoveBusinessAccountProfilePhotoOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecRemoveBusinessAccountProfilePhoto;
  Result := RunAsyncCall<Boolean>(BuildRemoveBusinessAccountProfilePhotoParams(ABusinessConnectionId, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.RemoveBusinessAccountProfilePhotoAsync(const ABusinessConnectionId: string;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
begin
  Result := RemoveBusinessAccountProfilePhotoAsync(ABusinessConnectionId,
  Default(TTgRemoveBusinessAccountProfilePhotoOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryRemoveBusinessAccountProfilePhoto(const ABusinessConnectionId: string;
  const AOptions: TTgRemoveBusinessAccountProfilePhotoOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    RemoveBusinessAccountProfilePhoto(ABusinessConnectionId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryRemoveBusinessAccountProfilePhoto(const ABusinessConnectionId: string;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryRemoveBusinessAccountProfilePhoto(ABusinessConnectionId,
  Default(TTgRemoveBusinessAccountProfilePhotoOptions), AError);
end;

function TTgApi.BuildSetBusinessAccountGiftSettingsParams(const ABusinessConnectionId: string;
  AShowGiftButton: Boolean; const AAcceptedGiftTypes: ITgAcceptedGiftTypes): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('business_connection_id', ABusinessConnectionId);
    Result.Add('show_gift_button', AShowGiftButton);
    Result.AddJson('accepted_gift_types', TTgDto.Serialize(AAcceptedGiftTypes, Result));
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetBusinessAccountGiftSettings(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setBusinessAccountGiftSettings', AParams);
  Result := TTgDto.ResultBool(LValue, 'setBusinessAccountGiftSettings');
end;

function TTgApi.SetBusinessAccountGiftSettings(const ABusinessConnectionId: string;
  AShowGiftButton: Boolean; const AAcceptedGiftTypes: ITgAcceptedGiftTypes): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetBusinessAccountGiftSettingsParams(ABusinessConnectionId, AShowGiftButton,
    AAcceptedGiftTypes);
  try
    Result := ExecSetBusinessAccountGiftSettings(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetBusinessAccountGiftSettingsAsync(const ABusinessConnectionId: string;
  AShowGiftButton: Boolean; const AAcceptedGiftTypes: ITgAcceptedGiftTypes;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetBusinessAccountGiftSettings;
  Result := RunAsyncCall<Boolean>(BuildSetBusinessAccountGiftSettingsParams(ABusinessConnectionId, AShowGiftButton, AAcceptedGiftTypes), LExec, AOnSuccess, AOnError);
end;

function TTgApi.TrySetBusinessAccountGiftSettings(const ABusinessConnectionId: string;
  AShowGiftButton: Boolean; const AAcceptedGiftTypes: ITgAcceptedGiftTypes;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetBusinessAccountGiftSettings(ABusinessConnectionId, AShowGiftButton, AAcceptedGiftTypes);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildGetBusinessAccountStarBalanceParams(const ABusinessConnectionId: string): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('business_connection_id', ABusinessConnectionId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecGetBusinessAccountStarBalance(AParams: TTgParams): ITgStarAmount;
var
  LValue: TJSONValue;
begin
  LValue := Call('getBusinessAccountStarBalance', AParams);
  Result := TTgDto.ResultObject<ITgStarAmount>(LValue, 'getBusinessAccountStarBalance',
    TgMakeStarAmount);
end;

function TTgApi.GetBusinessAccountStarBalance(const ABusinessConnectionId: string): ITgStarAmount;
var
  LParams: TTgParams;
begin
  LParams := BuildGetBusinessAccountStarBalanceParams(ABusinessConnectionId);
  try
    Result := ExecGetBusinessAccountStarBalance(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.GetBusinessAccountStarBalanceAsync(const ABusinessConnectionId: string;
  const AOnSuccess: TProc<ITgStarAmount>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgStarAmount>;
begin
  LExec := ExecGetBusinessAccountStarBalance;
  Result := RunAsyncCall<ITgStarAmount>(BuildGetBusinessAccountStarBalanceParams(ABusinessConnectionId), LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryGetBusinessAccountStarBalance(const ABusinessConnectionId: string;
  out AResult: ITgStarAmount; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgStarAmount);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetBusinessAccountStarBalance(ABusinessConnectionId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildTransferBusinessAccountStarsParams(const ABusinessConnectionId: string;
  AStarCount: Integer): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('business_connection_id', ABusinessConnectionId);
    Result.Add('star_count', AStarCount);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecTransferBusinessAccountStars(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('transferBusinessAccountStars', AParams);
  Result := TTgDto.ResultBool(LValue, 'transferBusinessAccountStars');
end;

function TTgApi.TransferBusinessAccountStars(const ABusinessConnectionId: string;
  AStarCount: Integer): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildTransferBusinessAccountStarsParams(ABusinessConnectionId, AStarCount);
  try
    Result := ExecTransferBusinessAccountStars(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.TransferBusinessAccountStarsAsync(const ABusinessConnectionId: string;
  AStarCount: Integer; const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecTransferBusinessAccountStars;
  Result := RunAsyncCall<Boolean>(BuildTransferBusinessAccountStarsParams(ABusinessConnectionId, AStarCount), LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryTransferBusinessAccountStars(const ABusinessConnectionId: string;
  AStarCount: Integer; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    TransferBusinessAccountStars(ABusinessConnectionId, AStarCount);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildGetBusinessAccountGiftsParams(const ABusinessConnectionId: string;
  const AOptions: TTgGetBusinessAccountGiftsOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('business_connection_id', ABusinessConnectionId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecGetBusinessAccountGifts(AParams: TTgParams): ITgOwnedGifts;
var
  LValue: TJSONValue;
begin
  LValue := Call('getBusinessAccountGifts', AParams);
  Result := TTgDto.ResultObject<ITgOwnedGifts>(LValue, 'getBusinessAccountGifts', TgMakeOwnedGifts);
end;

function TTgApi.GetBusinessAccountGifts(const ABusinessConnectionId: string;
  const AOptions: TTgGetBusinessAccountGiftsOptions): ITgOwnedGifts;
var
  LParams: TTgParams;
begin
  LParams := BuildGetBusinessAccountGiftsParams(ABusinessConnectionId, AOptions);
  try
    Result := ExecGetBusinessAccountGifts(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.GetBusinessAccountGifts(const ABusinessConnectionId: string): ITgOwnedGifts;
begin
  Result := GetBusinessAccountGifts(ABusinessConnectionId,
  Default(TTgGetBusinessAccountGiftsOptions));
end;

function TTgApi.GetBusinessAccountGiftsAsync(const ABusinessConnectionId: string;
  const AOptions: TTgGetBusinessAccountGiftsOptions; const AOnSuccess: TProc<ITgOwnedGifts>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgOwnedGifts>;
begin
  LExec := ExecGetBusinessAccountGifts;
  Result := RunAsyncCall<ITgOwnedGifts>(BuildGetBusinessAccountGiftsParams(ABusinessConnectionId, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.GetBusinessAccountGiftsAsync(const ABusinessConnectionId: string;
  const AOnSuccess: TProc<ITgOwnedGifts>; const AOnError: TProc<Exception>): ITask;
begin
  Result := GetBusinessAccountGiftsAsync(ABusinessConnectionId,
  Default(TTgGetBusinessAccountGiftsOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryGetBusinessAccountGifts(const ABusinessConnectionId: string;
  const AOptions: TTgGetBusinessAccountGiftsOptions; out AResult: ITgOwnedGifts;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgOwnedGifts);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetBusinessAccountGifts(ABusinessConnectionId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryGetBusinessAccountGifts(const ABusinessConnectionId: string;
  out AResult: ITgOwnedGifts; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryGetBusinessAccountGifts(ABusinessConnectionId,
  Default(TTgGetBusinessAccountGiftsOptions), AResult, AError);
end;

function TTgApi.BuildGetUserGiftsParams(AUserId: Int64;
  const AOptions: TTgGetUserGiftsOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('user_id', AUserId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecGetUserGifts(AParams: TTgParams): ITgOwnedGifts;
var
  LValue: TJSONValue;
begin
  LValue := Call('getUserGifts', AParams);
  Result := TTgDto.ResultObject<ITgOwnedGifts>(LValue, 'getUserGifts', TgMakeOwnedGifts);
end;

function TTgApi.GetUserGifts(AUserId: Int64; const AOptions: TTgGetUserGiftsOptions): ITgOwnedGifts;
var
  LParams: TTgParams;
begin
  LParams := BuildGetUserGiftsParams(AUserId, AOptions);
  try
    Result := ExecGetUserGifts(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.GetUserGifts(AUserId: Int64): ITgOwnedGifts;
begin
  Result := GetUserGifts(AUserId, Default(TTgGetUserGiftsOptions));
end;

function TTgApi.GetUserGiftsAsync(AUserId: Int64; const AOptions: TTgGetUserGiftsOptions;
  const AOnSuccess: TProc<ITgOwnedGifts>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgOwnedGifts>;
begin
  LExec := ExecGetUserGifts;
  Result := RunAsyncCall<ITgOwnedGifts>(BuildGetUserGiftsParams(AUserId, AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.GetUserGiftsAsync(AUserId: Int64; const AOnSuccess: TProc<ITgOwnedGifts>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := GetUserGiftsAsync(AUserId, Default(TTgGetUserGiftsOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryGetUserGifts(AUserId: Int64; const AOptions: TTgGetUserGiftsOptions;
  out AResult: ITgOwnedGifts; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgOwnedGifts);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetUserGifts(AUserId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryGetUserGifts(AUserId: Int64; out AResult: ITgOwnedGifts;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryGetUserGifts(AUserId, Default(TTgGetUserGiftsOptions), AResult, AError);
end;

function TTgApi.BuildGetChatGiftsParams(const AChatId: TTgChatId;
  const AOptions: TTgGetChatGiftsOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecGetChatGifts(AParams: TTgParams): ITgOwnedGifts;
var
  LValue: TJSONValue;
begin
  LValue := Call('getChatGifts', AParams);
  Result := TTgDto.ResultObject<ITgOwnedGifts>(LValue, 'getChatGifts', TgMakeOwnedGifts);
end;

function TTgApi.GetChatGifts(const AChatId: TTgChatId;
  const AOptions: TTgGetChatGiftsOptions): ITgOwnedGifts;
var
  LParams: TTgParams;
begin
  LParams := BuildGetChatGiftsParams(AChatId, AOptions);
  try
    Result := ExecGetChatGifts(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.GetChatGifts(const AChatId: TTgChatId): ITgOwnedGifts;
begin
  Result := GetChatGifts(AChatId, Default(TTgGetChatGiftsOptions));
end;

function TTgApi.GetChatGiftsAsync(const AChatId: TTgChatId; const AOptions: TTgGetChatGiftsOptions;
  const AOnSuccess: TProc<ITgOwnedGifts>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgOwnedGifts>;
begin
  LExec := ExecGetChatGifts;
  Result := RunAsyncCall<ITgOwnedGifts>(BuildGetChatGiftsParams(AChatId, AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.GetChatGiftsAsync(const AChatId: TTgChatId; const AOnSuccess: TProc<ITgOwnedGifts>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := GetChatGiftsAsync(AChatId, Default(TTgGetChatGiftsOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryGetChatGifts(const AChatId: TTgChatId; const AOptions: TTgGetChatGiftsOptions;
  out AResult: ITgOwnedGifts; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgOwnedGifts);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetChatGifts(AChatId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryGetChatGifts(const AChatId: TTgChatId; out AResult: ITgOwnedGifts;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryGetChatGifts(AChatId, Default(TTgGetChatGiftsOptions), AResult, AError);
end;

function TTgApi.BuildConvertGiftToStarsParams(const ABusinessConnectionId: string;
  const AOwnedGiftId: string): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('business_connection_id', ABusinessConnectionId);
    Result.Add('owned_gift_id', AOwnedGiftId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecConvertGiftToStars(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('convertGiftToStars', AParams);
  Result := TTgDto.ResultBool(LValue, 'convertGiftToStars');
end;

function TTgApi.ConvertGiftToStars(const ABusinessConnectionId: string;
  const AOwnedGiftId: string): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildConvertGiftToStarsParams(ABusinessConnectionId, AOwnedGiftId);
  try
    Result := ExecConvertGiftToStars(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.ConvertGiftToStarsAsync(const ABusinessConnectionId: string;
  const AOwnedGiftId: string; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecConvertGiftToStars;
  Result := RunAsyncCall<Boolean>(BuildConvertGiftToStarsParams(ABusinessConnectionId, AOwnedGiftId), LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryConvertGiftToStars(const ABusinessConnectionId: string;
  const AOwnedGiftId: string; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    ConvertGiftToStars(ABusinessConnectionId, AOwnedGiftId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildUpgradeGiftParams(const ABusinessConnectionId: string;
  const AOwnedGiftId: string; const AOptions: TTgUpgradeGiftOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('business_connection_id', ABusinessConnectionId);
    Result.Add('owned_gift_id', AOwnedGiftId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecUpgradeGift(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('upgradeGift', AParams);
  Result := TTgDto.ResultBool(LValue, 'upgradeGift');
end;

function TTgApi.UpgradeGift(const ABusinessConnectionId: string; const AOwnedGiftId: string;
  const AOptions: TTgUpgradeGiftOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildUpgradeGiftParams(ABusinessConnectionId, AOwnedGiftId, AOptions);
  try
    Result := ExecUpgradeGift(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.UpgradeGift(const ABusinessConnectionId: string;
  const AOwnedGiftId: string): Boolean;
begin
  Result := UpgradeGift(ABusinessConnectionId, AOwnedGiftId, Default(TTgUpgradeGiftOptions));
end;

function TTgApi.UpgradeGiftAsync(const ABusinessConnectionId: string; const AOwnedGiftId: string;
  const AOptions: TTgUpgradeGiftOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecUpgradeGift;
  Result := RunAsyncCall<Boolean>(BuildUpgradeGiftParams(ABusinessConnectionId, AOwnedGiftId, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.UpgradeGiftAsync(const ABusinessConnectionId: string; const AOwnedGiftId: string;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
begin
  Result := UpgradeGiftAsync(ABusinessConnectionId, AOwnedGiftId, Default(TTgUpgradeGiftOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TryUpgradeGift(const ABusinessConnectionId: string; const AOwnedGiftId: string;
  const AOptions: TTgUpgradeGiftOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    UpgradeGift(ABusinessConnectionId, AOwnedGiftId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryUpgradeGift(const ABusinessConnectionId: string; const AOwnedGiftId: string;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryUpgradeGift(ABusinessConnectionId, AOwnedGiftId, Default(TTgUpgradeGiftOptions),
  AError);
end;

function TTgApi.BuildTransferGiftParams(const ABusinessConnectionId: string;
  const AOwnedGiftId: string; ANewOwnerChatId: Int64;
  const AOptions: TTgTransferGiftOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('business_connection_id', ABusinessConnectionId);
    Result.Add('owned_gift_id', AOwnedGiftId);
    Result.Add('new_owner_chat_id', ANewOwnerChatId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecTransferGift(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('transferGift', AParams);
  Result := TTgDto.ResultBool(LValue, 'transferGift');
end;

function TTgApi.TransferGift(const ABusinessConnectionId: string; const AOwnedGiftId: string;
  ANewOwnerChatId: Int64; const AOptions: TTgTransferGiftOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildTransferGiftParams(ABusinessConnectionId, AOwnedGiftId, ANewOwnerChatId,
    AOptions);
  try
    Result := ExecTransferGift(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.TransferGift(const ABusinessConnectionId: string; const AOwnedGiftId: string;
  ANewOwnerChatId: Int64): Boolean;
begin
  Result := TransferGift(ABusinessConnectionId, AOwnedGiftId, ANewOwnerChatId,
  Default(TTgTransferGiftOptions));
end;

function TTgApi.TransferGiftAsync(const ABusinessConnectionId: string; const AOwnedGiftId: string;
  ANewOwnerChatId: Int64; const AOptions: TTgTransferGiftOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecTransferGift;
  Result := RunAsyncCall<Boolean>(BuildTransferGiftParams(ABusinessConnectionId, AOwnedGiftId, ANewOwnerChatId, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.TransferGiftAsync(const ABusinessConnectionId: string; const AOwnedGiftId: string;
  ANewOwnerChatId: Int64; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := TransferGiftAsync(ABusinessConnectionId, AOwnedGiftId, ANewOwnerChatId,
  Default(TTgTransferGiftOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryTransferGift(const ABusinessConnectionId: string; const AOwnedGiftId: string;
  ANewOwnerChatId: Int64; const AOptions: TTgTransferGiftOptions;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    TransferGift(ABusinessConnectionId, AOwnedGiftId, ANewOwnerChatId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryTransferGift(const ABusinessConnectionId: string; const AOwnedGiftId: string;
  ANewOwnerChatId: Int64; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryTransferGift(ABusinessConnectionId, AOwnedGiftId, ANewOwnerChatId,
  Default(TTgTransferGiftOptions), AError);
end;

function TTgApi.BuildPostStoryParams(const ABusinessConnectionId: string;
  const AContent: TTgInputStoryContent; AActivePeriod: Integer;
  const AOptions: TTgPostStoryOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('business_connection_id', ABusinessConnectionId);
    Result.AddJson('content', TTgDto.Serialize(AContent.Value, Result));
    Result.Add('active_period', AActivePeriod);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecPostStory(AParams: TTgParams): ITgStory;
var
  LValue: TJSONValue;
begin
  LValue := Call('postStory', AParams);
  Result := TTgDto.ResultObject<ITgStory>(LValue, 'postStory', TgMakeStory);
end;

function TTgApi.PostStory(const ABusinessConnectionId: string; const AContent: TTgInputStoryContent;
  AActivePeriod: Integer; const AOptions: TTgPostStoryOptions): ITgStory;
var
  LParams: TTgParams;
begin
  LParams := BuildPostStoryParams(ABusinessConnectionId, AContent, AActivePeriod, AOptions);
  try
    Result := ExecPostStory(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.PostStory(const ABusinessConnectionId: string; const AContent: TTgInputStoryContent;
  AActivePeriod: Integer): ITgStory;
begin
  Result := PostStory(ABusinessConnectionId, AContent, AActivePeriod, Default(TTgPostStoryOptions));
end;

function TTgApi.PostStoryAsync(const ABusinessConnectionId: string;
  const AContent: TTgInputStoryContent; AActivePeriod: Integer; const AOptions: TTgPostStoryOptions;
  const AOnSuccess: TProc<ITgStory>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgStory>;
begin
  LExec := ExecPostStory;
  Result := RunAsyncCall<ITgStory>(BuildPostStoryParams(ABusinessConnectionId, AContent, AActivePeriod, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.PostStoryAsync(const ABusinessConnectionId: string;
  const AContent: TTgInputStoryContent; AActivePeriod: Integer; const AOnSuccess: TProc<ITgStory>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := PostStoryAsync(ABusinessConnectionId, AContent, AActivePeriod,
  Default(TTgPostStoryOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryPostStory(const ABusinessConnectionId: string;
  const AContent: TTgInputStoryContent; AActivePeriod: Integer; const AOptions: TTgPostStoryOptions;
  out AResult: ITgStory; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgStory);
  AError := TTgErrorInfo.Empty;
  try
    AResult := PostStory(ABusinessConnectionId, AContent, AActivePeriod, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryPostStory(const ABusinessConnectionId: string;
  const AContent: TTgInputStoryContent; AActivePeriod: Integer; out AResult: ITgStory;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryPostStory(ABusinessConnectionId, AContent, AActivePeriod,
  Default(TTgPostStoryOptions), AResult, AError);
end;

function TTgApi.BuildRepostStoryParams(const ABusinessConnectionId: string; AFromChatId: Int64;
  AFromStoryId: Int64; AActivePeriod: Integer; const AOptions: TTgRepostStoryOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('business_connection_id', ABusinessConnectionId);
    Result.Add('from_chat_id', AFromChatId);
    Result.Add('from_story_id', AFromStoryId);
    Result.Add('active_period', AActivePeriod);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecRepostStory(AParams: TTgParams): ITgStory;
var
  LValue: TJSONValue;
begin
  LValue := Call('repostStory', AParams);
  Result := TTgDto.ResultObject<ITgStory>(LValue, 'repostStory', TgMakeStory);
end;

function TTgApi.RepostStory(const ABusinessConnectionId: string; AFromChatId: Int64;
  AFromStoryId: Int64; AActivePeriod: Integer; const AOptions: TTgRepostStoryOptions): ITgStory;
var
  LParams: TTgParams;
begin
  LParams := BuildRepostStoryParams(ABusinessConnectionId, AFromChatId, AFromStoryId, AActivePeriod,
    AOptions);
  try
    Result := ExecRepostStory(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.RepostStory(const ABusinessConnectionId: string; AFromChatId: Int64;
  AFromStoryId: Int64; AActivePeriod: Integer): ITgStory;
begin
  Result := RepostStory(ABusinessConnectionId, AFromChatId, AFromStoryId, AActivePeriod,
  Default(TTgRepostStoryOptions));
end;

function TTgApi.RepostStoryAsync(const ABusinessConnectionId: string; AFromChatId: Int64;
  AFromStoryId: Int64; AActivePeriod: Integer; const AOptions: TTgRepostStoryOptions;
  const AOnSuccess: TProc<ITgStory>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgStory>;
begin
  LExec := ExecRepostStory;
  Result := RunAsyncCall<ITgStory>(BuildRepostStoryParams(ABusinessConnectionId, AFromChatId, AFromStoryId, AActivePeriod, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.RepostStoryAsync(const ABusinessConnectionId: string; AFromChatId: Int64;
  AFromStoryId: Int64; AActivePeriod: Integer; const AOnSuccess: TProc<ITgStory>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := RepostStoryAsync(ABusinessConnectionId, AFromChatId, AFromStoryId, AActivePeriod,
  Default(TTgRepostStoryOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryRepostStory(const ABusinessConnectionId: string; AFromChatId: Int64;
  AFromStoryId: Int64; AActivePeriod: Integer; const AOptions: TTgRepostStoryOptions;
  out AResult: ITgStory; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgStory);
  AError := TTgErrorInfo.Empty;
  try
    AResult := RepostStory(ABusinessConnectionId, AFromChatId, AFromStoryId, AActivePeriod,
      AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryRepostStory(const ABusinessConnectionId: string; AFromChatId: Int64;
  AFromStoryId: Int64; AActivePeriod: Integer; out AResult: ITgStory;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryRepostStory(ABusinessConnectionId, AFromChatId, AFromStoryId, AActivePeriod,
  Default(TTgRepostStoryOptions), AResult, AError);
end;

function TTgApi.BuildEditStoryParams(const ABusinessConnectionId: string; AStoryId: Int64;
  const AContent: TTgInputStoryContent; const AOptions: TTgEditStoryOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('business_connection_id', ABusinessConnectionId);
    Result.Add('story_id', AStoryId);
    Result.AddJson('content', TTgDto.Serialize(AContent.Value, Result));
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecEditStory(AParams: TTgParams): ITgStory;
var
  LValue: TJSONValue;
begin
  LValue := Call('editStory', AParams);
  Result := TTgDto.ResultObject<ITgStory>(LValue, 'editStory', TgMakeStory);
end;

function TTgApi.EditStory(const ABusinessConnectionId: string; AStoryId: Int64;
  const AContent: TTgInputStoryContent; const AOptions: TTgEditStoryOptions): ITgStory;
var
  LParams: TTgParams;
begin
  LParams := BuildEditStoryParams(ABusinessConnectionId, AStoryId, AContent, AOptions);
  try
    Result := ExecEditStory(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.EditStory(const ABusinessConnectionId: string; AStoryId: Int64;
  const AContent: TTgInputStoryContent): ITgStory;
begin
  Result := EditStory(ABusinessConnectionId, AStoryId, AContent, Default(TTgEditStoryOptions));
end;

function TTgApi.EditStoryAsync(const ABusinessConnectionId: string; AStoryId: Int64;
  const AContent: TTgInputStoryContent; const AOptions: TTgEditStoryOptions;
  const AOnSuccess: TProc<ITgStory>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgStory>;
begin
  LExec := ExecEditStory;
  Result := RunAsyncCall<ITgStory>(BuildEditStoryParams(ABusinessConnectionId, AStoryId, AContent, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.EditStoryAsync(const ABusinessConnectionId: string; AStoryId: Int64;
  const AContent: TTgInputStoryContent; const AOnSuccess: TProc<ITgStory>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := EditStoryAsync(ABusinessConnectionId, AStoryId, AContent, Default(TTgEditStoryOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TryEditStory(const ABusinessConnectionId: string; AStoryId: Int64;
  const AContent: TTgInputStoryContent; const AOptions: TTgEditStoryOptions; out AResult: ITgStory;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgStory);
  AError := TTgErrorInfo.Empty;
  try
    AResult := EditStory(ABusinessConnectionId, AStoryId, AContent, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryEditStory(const ABusinessConnectionId: string; AStoryId: Int64;
  const AContent: TTgInputStoryContent; out AResult: ITgStory; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryEditStory(ABusinessConnectionId, AStoryId, AContent, Default(TTgEditStoryOptions),
  AResult, AError);
end;

function TTgApi.BuildDeleteStoryParams(const ABusinessConnectionId: string;
  AStoryId: Int64): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('business_connection_id', ABusinessConnectionId);
    Result.Add('story_id', AStoryId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecDeleteStory(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('deleteStory', AParams);
  Result := TTgDto.ResultBool(LValue, 'deleteStory');
end;

function TTgApi.DeleteStory(const ABusinessConnectionId: string; AStoryId: Int64): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildDeleteStoryParams(ABusinessConnectionId, AStoryId);
  try
    Result := ExecDeleteStory(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.DeleteStoryAsync(const ABusinessConnectionId: string; AStoryId: Int64;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecDeleteStory;
  Result := RunAsyncCall<Boolean>(BuildDeleteStoryParams(ABusinessConnectionId, AStoryId), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.TryDeleteStory(const ABusinessConnectionId: string; AStoryId: Int64;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    DeleteStory(ABusinessConnectionId, AStoryId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildAnswerWebAppQueryParams(const AWebAppQueryId: string;
  const AWebAppQueryResult: TTgInlineQueryResult): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('web_app_query_id', AWebAppQueryId);
    Result.AddJson('result', TTgDto.Serialize(AWebAppQueryResult.Value, Result));
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecAnswerWebAppQuery(AParams: TTgParams): ITgSentWebAppMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('answerWebAppQuery', AParams);
  Result := TTgDto.ResultObject<ITgSentWebAppMessage>(LValue, 'answerWebAppQuery',
    TgMakeSentWebAppMessage);
end;

function TTgApi.AnswerWebAppQuery(const AWebAppQueryId: string;
  const AWebAppQueryResult: TTgInlineQueryResult): ITgSentWebAppMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildAnswerWebAppQueryParams(AWebAppQueryId, AWebAppQueryResult);
  try
    Result := ExecAnswerWebAppQuery(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.AnswerWebAppQueryAsync(const AWebAppQueryId: string;
  const AWebAppQueryResult: TTgInlineQueryResult; const AOnSuccess: TProc<ITgSentWebAppMessage>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgSentWebAppMessage>;
begin
  LExec := ExecAnswerWebAppQuery;
  Result := RunAsyncCall<ITgSentWebAppMessage>(BuildAnswerWebAppQueryParams(AWebAppQueryId, AWebAppQueryResult), LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryAnswerWebAppQuery(const AWebAppQueryId: string;
  const AWebAppQueryResult: TTgInlineQueryResult; out AResult: ITgSentWebAppMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgSentWebAppMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := AnswerWebAppQuery(AWebAppQueryId, AWebAppQueryResult);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildSavePreparedInlineMessageParams(AUserId: Int64;
  const APreparedInlineMessageResult: TTgInlineQueryResult;
  const AOptions: TTgSavePreparedInlineMessageOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('user_id', AUserId);
    Result.AddJson('result', TTgDto.Serialize(APreparedInlineMessageResult.Value, Result));
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSavePreparedInlineMessage(AParams: TTgParams): ITgPreparedInlineMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('savePreparedInlineMessage', AParams);
  Result := TTgDto.ResultObject<ITgPreparedInlineMessage>(LValue, 'savePreparedInlineMessage',
    TgMakePreparedInlineMessage);
end;

function TTgApi.SavePreparedInlineMessage(AUserId: Int64;
  const APreparedInlineMessageResult: TTgInlineQueryResult;
  const AOptions: TTgSavePreparedInlineMessageOptions): ITgPreparedInlineMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildSavePreparedInlineMessageParams(AUserId, APreparedInlineMessageResult, AOptions);
  try
    Result := ExecSavePreparedInlineMessage(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SavePreparedInlineMessage(AUserId: Int64;
  const APreparedInlineMessageResult: TTgInlineQueryResult): ITgPreparedInlineMessage;
begin
  Result := SavePreparedInlineMessage(AUserId, APreparedInlineMessageResult,
  Default(TTgSavePreparedInlineMessageOptions));
end;

function TTgApi.SavePreparedInlineMessageAsync(AUserId: Int64;
  const APreparedInlineMessageResult: TTgInlineQueryResult;
  const AOptions: TTgSavePreparedInlineMessageOptions;
  const AOnSuccess: TProc<ITgPreparedInlineMessage>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgPreparedInlineMessage>;
begin
  LExec := ExecSavePreparedInlineMessage;
  Result := RunAsyncCall<ITgPreparedInlineMessage>(BuildSavePreparedInlineMessageParams(AUserId, APreparedInlineMessageResult, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.SavePreparedInlineMessageAsync(AUserId: Int64;
  const APreparedInlineMessageResult: TTgInlineQueryResult;
  const AOnSuccess: TProc<ITgPreparedInlineMessage>; const AOnError: TProc<Exception>): ITask;
begin
  Result := SavePreparedInlineMessageAsync(AUserId, APreparedInlineMessageResult,
  Default(TTgSavePreparedInlineMessageOptions), AOnSuccess, AOnError);
end;

function TTgApi.TrySavePreparedInlineMessage(AUserId: Int64;
  const APreparedInlineMessageResult: TTgInlineQueryResult;
  const AOptions: TTgSavePreparedInlineMessageOptions; out AResult: ITgPreparedInlineMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgPreparedInlineMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := SavePreparedInlineMessage(AUserId, APreparedInlineMessageResult, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySavePreparedInlineMessage(AUserId: Int64;
  const APreparedInlineMessageResult: TTgInlineQueryResult; out AResult: ITgPreparedInlineMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySavePreparedInlineMessage(AUserId, APreparedInlineMessageResult,
  Default(TTgSavePreparedInlineMessageOptions), AResult, AError);
end;

function TTgApi.BuildSavePreparedKeyboardButtonParams(AUserId: Int64;
  const AButton: ITgKeyboardButton): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('user_id', AUserId);
    Result.AddJson('button', TTgDto.Serialize(AButton, Result));
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSavePreparedKeyboardButton(AParams: TTgParams): ITgPreparedKeyboardButton;
var
  LValue: TJSONValue;
begin
  LValue := Call('savePreparedKeyboardButton', AParams);
  Result := TTgDto.ResultObject<ITgPreparedKeyboardButton>(LValue, 'savePreparedKeyboardButton',
    TgMakePreparedKeyboardButton);
end;

function TTgApi.SavePreparedKeyboardButton(AUserId: Int64;
  const AButton: ITgKeyboardButton): ITgPreparedKeyboardButton;
var
  LParams: TTgParams;
begin
  LParams := BuildSavePreparedKeyboardButtonParams(AUserId, AButton);
  try
    Result := ExecSavePreparedKeyboardButton(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SavePreparedKeyboardButtonAsync(AUserId: Int64; const AButton: ITgKeyboardButton;
  const AOnSuccess: TProc<ITgPreparedKeyboardButton>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgPreparedKeyboardButton>;
begin
  LExec := ExecSavePreparedKeyboardButton;
  Result := RunAsyncCall<ITgPreparedKeyboardButton>(BuildSavePreparedKeyboardButtonParams(AUserId, AButton), LExec, AOnSuccess, AOnError);
end;

function TTgApi.TrySavePreparedKeyboardButton(AUserId: Int64; const AButton: ITgKeyboardButton;
  out AResult: ITgPreparedKeyboardButton; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgPreparedKeyboardButton);
  AError := TTgErrorInfo.Empty;
  try
    AResult := SavePreparedKeyboardButton(AUserId, AButton);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildEditMessageTextParams(const AOptions: TTgEditMessageTextOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecEditMessageText(AParams: TTgParams): ITgMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('editMessageText', AParams);
  Result := TTgDto.ResultObjectOrTrue<ITgMessage>(LValue, 'editMessageText', TgMakeMessage);
end;

function TTgApi.EditMessageText(const AOptions: TTgEditMessageTextOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildEditMessageTextParams(AOptions);
  try
    Result := ExecEditMessageText(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.EditMessageText: ITgMessage;
begin
  Result := EditMessageText(Default(TTgEditMessageTextOptions));
end;

function TTgApi.EditMessageTextAsync(const AOptions: TTgEditMessageTextOptions;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecEditMessageText;
  Result := RunAsyncCall<ITgMessage>(BuildEditMessageTextParams(AOptions), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.EditMessageTextAsync(const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := EditMessageTextAsync(Default(TTgEditMessageTextOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryEditMessageText(const AOptions: TTgEditMessageTextOptions;
  out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := EditMessageText(AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryEditMessageText(out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryEditMessageText(Default(TTgEditMessageTextOptions), AResult, AError);
end;

function TTgApi.BuildEditMessageTextVariant1Params(const AChatId: TTgChatId; AMessageId: Int64;
  const AText: string; const AOptions: TTgEditMessageTextOptions): TTgParams;
var
  LOptions: TTgEditMessageTextOptions;
begin
  LOptions := AOptions;
  LOptions.ChatId := AChatId;
  LOptions.MessageId := AMessageId;
  LOptions.Text := AText;
  Result := BuildEditMessageTextParams(LOptions);
end;

function TTgApi.EditMessageText(const AChatId: TTgChatId; AMessageId: Int64; const AText: string;
  const AOptions: TTgEditMessageTextOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildEditMessageTextVariant1Params(AChatId, AMessageId, AText, AOptions);
  try
    Result := ExecEditMessageText(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.EditMessageText(const AChatId: TTgChatId; AMessageId: Int64;
  const AText: string): ITgMessage;
begin
  Result := EditMessageText(AChatId, AMessageId, AText, Default(TTgEditMessageTextOptions));
end;

function TTgApi.EditMessageTextAsync(const AChatId: TTgChatId; AMessageId: Int64;
  const AText: string; const AOptions: TTgEditMessageTextOptions;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecEditMessageText;
  Result := RunAsyncCall<ITgMessage>(BuildEditMessageTextVariant1Params(AChatId, AMessageId, AText, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.EditMessageTextAsync(const AChatId: TTgChatId; AMessageId: Int64;
  const AText: string; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := EditMessageTextAsync(AChatId, AMessageId, AText, Default(TTgEditMessageTextOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TryEditMessageText(const AChatId: TTgChatId; AMessageId: Int64; const AText: string;
  const AOptions: TTgEditMessageTextOptions; out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := EditMessageText(AChatId, AMessageId, AText, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryEditMessageText(const AChatId: TTgChatId; AMessageId: Int64; const AText: string;
  out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryEditMessageText(AChatId, AMessageId, AText, Default(TTgEditMessageTextOptions),
  AResult, AError);
end;

function TTgApi.BuildEditMessageTextVariant2Params(const AInlineMessageId: string;
  const AText: string; const AOptions: TTgEditMessageTextOptions): TTgParams;
var
  LOptions: TTgEditMessageTextOptions;
begin
  LOptions := AOptions;
  LOptions.InlineMessageId := AInlineMessageId;
  LOptions.Text := AText;
  Result := BuildEditMessageTextParams(LOptions);
end;

function TTgApi.ExecEditMessageTextVariant2(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('editMessageText', AParams);
  Result := TTgDto.ResultBool(LValue, 'editMessageText');
end;

function TTgApi.EditInlineMessageText(const AInlineMessageId: string; const AText: string;
  const AOptions: TTgEditMessageTextOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildEditMessageTextVariant2Params(AInlineMessageId, AText, AOptions);
  try
    Result := ExecEditMessageTextVariant2(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.EditInlineMessageText(const AInlineMessageId: string; const AText: string): Boolean;
begin
  Result := EditInlineMessageText(AInlineMessageId, AText, Default(TTgEditMessageTextOptions));
end;

function TTgApi.EditInlineMessageTextAsync(const AInlineMessageId: string; const AText: string;
  const AOptions: TTgEditMessageTextOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecEditMessageTextVariant2;
  Result := RunAsyncCall<Boolean>(BuildEditMessageTextVariant2Params(AInlineMessageId, AText, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.EditInlineMessageTextAsync(const AInlineMessageId: string; const AText: string;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
begin
  Result := EditInlineMessageTextAsync(AInlineMessageId, AText, Default(TTgEditMessageTextOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TryEditInlineMessageText(const AInlineMessageId: string; const AText: string;
  const AOptions: TTgEditMessageTextOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    EditInlineMessageText(AInlineMessageId, AText, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryEditInlineMessageText(const AInlineMessageId: string; const AText: string;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryEditInlineMessageText(AInlineMessageId, AText, Default(TTgEditMessageTextOptions),
  AError);
end;

function TTgApi.BuildEditMessageCaptionParams(const AOptions: TTgEditMessageCaptionOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecEditMessageCaption(AParams: TTgParams): ITgMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('editMessageCaption', AParams);
  Result := TTgDto.ResultObjectOrTrue<ITgMessage>(LValue, 'editMessageCaption', TgMakeMessage);
end;

function TTgApi.EditMessageCaption(const AOptions: TTgEditMessageCaptionOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildEditMessageCaptionParams(AOptions);
  try
    Result := ExecEditMessageCaption(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.EditMessageCaption: ITgMessage;
begin
  Result := EditMessageCaption(Default(TTgEditMessageCaptionOptions));
end;

function TTgApi.EditMessageCaptionAsync(const AOptions: TTgEditMessageCaptionOptions;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecEditMessageCaption;
  Result := RunAsyncCall<ITgMessage>(BuildEditMessageCaptionParams(AOptions), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.EditMessageCaptionAsync(const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := EditMessageCaptionAsync(Default(TTgEditMessageCaptionOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryEditMessageCaption(const AOptions: TTgEditMessageCaptionOptions;
  out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := EditMessageCaption(AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryEditMessageCaption(out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryEditMessageCaption(Default(TTgEditMessageCaptionOptions), AResult, AError);
end;

function TTgApi.BuildEditMessageCaptionVariant1Params(const AChatId: TTgChatId; AMessageId: Int64;
  const ACaption: string; const AOptions: TTgEditMessageCaptionOptions): TTgParams;
var
  LOptions: TTgEditMessageCaptionOptions;
begin
  LOptions := AOptions;
  LOptions.ChatId := AChatId;
  LOptions.MessageId := AMessageId;
  LOptions.Caption := ACaption;
  Result := BuildEditMessageCaptionParams(LOptions);
end;

function TTgApi.EditMessageCaption(const AChatId: TTgChatId; AMessageId: Int64;
  const ACaption: string; const AOptions: TTgEditMessageCaptionOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildEditMessageCaptionVariant1Params(AChatId, AMessageId, ACaption, AOptions);
  try
    Result := ExecEditMessageCaption(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.EditMessageCaption(const AChatId: TTgChatId; AMessageId: Int64;
  const ACaption: string): ITgMessage;
begin
  Result := EditMessageCaption(AChatId, AMessageId, ACaption,
  Default(TTgEditMessageCaptionOptions));
end;

function TTgApi.EditMessageCaptionAsync(const AChatId: TTgChatId; AMessageId: Int64;
  const ACaption: string; const AOptions: TTgEditMessageCaptionOptions;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecEditMessageCaption;
  Result := RunAsyncCall<ITgMessage>(BuildEditMessageCaptionVariant1Params(AChatId, AMessageId, ACaption, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.EditMessageCaptionAsync(const AChatId: TTgChatId; AMessageId: Int64;
  const ACaption: string; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := EditMessageCaptionAsync(AChatId, AMessageId, ACaption,
  Default(TTgEditMessageCaptionOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryEditMessageCaption(const AChatId: TTgChatId; AMessageId: Int64;
  const ACaption: string; const AOptions: TTgEditMessageCaptionOptions; out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := EditMessageCaption(AChatId, AMessageId, ACaption, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryEditMessageCaption(const AChatId: TTgChatId; AMessageId: Int64;
  const ACaption: string; out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryEditMessageCaption(AChatId, AMessageId, ACaption,
  Default(TTgEditMessageCaptionOptions), AResult, AError);
end;

function TTgApi.BuildEditMessageCaptionVariant2Params(const AInlineMessageId: string;
  const ACaption: string; const AOptions: TTgEditMessageCaptionOptions): TTgParams;
var
  LOptions: TTgEditMessageCaptionOptions;
begin
  LOptions := AOptions;
  LOptions.InlineMessageId := AInlineMessageId;
  LOptions.Caption := ACaption;
  Result := BuildEditMessageCaptionParams(LOptions);
end;

function TTgApi.ExecEditMessageCaptionVariant2(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('editMessageCaption', AParams);
  Result := TTgDto.ResultBool(LValue, 'editMessageCaption');
end;

function TTgApi.EditInlineMessageCaption(const AInlineMessageId: string; const ACaption: string;
  const AOptions: TTgEditMessageCaptionOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildEditMessageCaptionVariant2Params(AInlineMessageId, ACaption, AOptions);
  try
    Result := ExecEditMessageCaptionVariant2(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.EditInlineMessageCaption(const AInlineMessageId: string;
  const ACaption: string): Boolean;
begin
  Result := EditInlineMessageCaption(AInlineMessageId, ACaption,
  Default(TTgEditMessageCaptionOptions));
end;

function TTgApi.EditInlineMessageCaptionAsync(const AInlineMessageId: string;
  const ACaption: string; const AOptions: TTgEditMessageCaptionOptions;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecEditMessageCaptionVariant2;
  Result := RunAsyncCall<Boolean>(BuildEditMessageCaptionVariant2Params(AInlineMessageId, ACaption, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.EditInlineMessageCaptionAsync(const AInlineMessageId: string;
  const ACaption: string; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := EditInlineMessageCaptionAsync(AInlineMessageId, ACaption,
  Default(TTgEditMessageCaptionOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryEditInlineMessageCaption(const AInlineMessageId: string; const ACaption: string;
  const AOptions: TTgEditMessageCaptionOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    EditInlineMessageCaption(AInlineMessageId, ACaption, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryEditInlineMessageCaption(const AInlineMessageId: string; const ACaption: string;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryEditInlineMessageCaption(AInlineMessageId, ACaption,
  Default(TTgEditMessageCaptionOptions), AError);
end;

function TTgApi.BuildEditMessageMediaParams(const AMedia: TTgInputMedia;
  const AOptions: TTgEditMessageMediaOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddJson('media', TTgDto.Serialize(AMedia.Value, Result));
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecEditMessageMedia(AParams: TTgParams): ITgMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('editMessageMedia', AParams);
  Result := TTgDto.ResultObjectOrTrue<ITgMessage>(LValue, 'editMessageMedia', TgMakeMessage);
end;

function TTgApi.EditMessageMedia(const AMedia: TTgInputMedia;
  const AOptions: TTgEditMessageMediaOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildEditMessageMediaParams(AMedia, AOptions);
  try
    Result := ExecEditMessageMedia(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.EditMessageMedia(const AMedia: TTgInputMedia): ITgMessage;
begin
  Result := EditMessageMedia(AMedia, Default(TTgEditMessageMediaOptions));
end;

function TTgApi.EditMessageMediaAsync(const AMedia: TTgInputMedia;
  const AOptions: TTgEditMessageMediaOptions; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecEditMessageMedia;
  Result := RunAsyncCall<ITgMessage>(BuildEditMessageMediaParams(AMedia, AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.EditMessageMediaAsync(const AMedia: TTgInputMedia;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
begin
  Result := EditMessageMediaAsync(AMedia, Default(TTgEditMessageMediaOptions), AOnSuccess,
  AOnError);
end;

function TTgApi.TryEditMessageMedia(const AMedia: TTgInputMedia;
  const AOptions: TTgEditMessageMediaOptions; out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := EditMessageMedia(AMedia, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryEditMessageMedia(const AMedia: TTgInputMedia; out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryEditMessageMedia(AMedia, Default(TTgEditMessageMediaOptions), AResult, AError);
end;

function TTgApi.BuildEditMessageMediaVariant1Params(const AChatId: TTgChatId; AMessageId: Int64;
  const AMedia: TTgInputMedia; const AOptions: TTgEditMessageMediaOptions): TTgParams;
var
  LOptions: TTgEditMessageMediaOptions;
begin
  LOptions := AOptions;
  LOptions.ChatId := AChatId;
  LOptions.MessageId := AMessageId;
  Result := BuildEditMessageMediaParams(AMedia, LOptions);
end;

function TTgApi.EditMessageMedia(const AChatId: TTgChatId; AMessageId: Int64;
  const AMedia: TTgInputMedia; const AOptions: TTgEditMessageMediaOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildEditMessageMediaVariant1Params(AChatId, AMessageId, AMedia, AOptions);
  try
    Result := ExecEditMessageMedia(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.EditMessageMedia(const AChatId: TTgChatId; AMessageId: Int64;
  const AMedia: TTgInputMedia): ITgMessage;
begin
  Result := EditMessageMedia(AChatId, AMessageId, AMedia, Default(TTgEditMessageMediaOptions));
end;

function TTgApi.EditMessageMediaAsync(const AChatId: TTgChatId; AMessageId: Int64;
  const AMedia: TTgInputMedia; const AOptions: TTgEditMessageMediaOptions;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecEditMessageMedia;
  Result := RunAsyncCall<ITgMessage>(BuildEditMessageMediaVariant1Params(AChatId, AMessageId, AMedia, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.EditMessageMediaAsync(const AChatId: TTgChatId; AMessageId: Int64;
  const AMedia: TTgInputMedia; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := EditMessageMediaAsync(AChatId, AMessageId, AMedia, Default(TTgEditMessageMediaOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TryEditMessageMedia(const AChatId: TTgChatId; AMessageId: Int64;
  const AMedia: TTgInputMedia; const AOptions: TTgEditMessageMediaOptions; out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := EditMessageMedia(AChatId, AMessageId, AMedia, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryEditMessageMedia(const AChatId: TTgChatId; AMessageId: Int64;
  const AMedia: TTgInputMedia; out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryEditMessageMedia(AChatId, AMessageId, AMedia, Default(TTgEditMessageMediaOptions),
  AResult, AError);
end;

function TTgApi.BuildEditMessageMediaVariant2Params(const AInlineMessageId: string;
  const AMedia: TTgInputMedia; const AOptions: TTgEditMessageMediaOptions): TTgParams;
var
  LOptions: TTgEditMessageMediaOptions;
begin
  LOptions := AOptions;
  LOptions.InlineMessageId := AInlineMessageId;
  Result := BuildEditMessageMediaParams(AMedia, LOptions);
end;

function TTgApi.ExecEditMessageMediaVariant2(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('editMessageMedia', AParams);
  Result := TTgDto.ResultBool(LValue, 'editMessageMedia');
end;

function TTgApi.EditInlineMessageMedia(const AInlineMessageId: string; const AMedia: TTgInputMedia;
  const AOptions: TTgEditMessageMediaOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildEditMessageMediaVariant2Params(AInlineMessageId, AMedia, AOptions);
  try
    Result := ExecEditMessageMediaVariant2(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.EditInlineMessageMedia(const AInlineMessageId: string;
  const AMedia: TTgInputMedia): Boolean;
begin
  Result := EditInlineMessageMedia(AInlineMessageId, AMedia, Default(TTgEditMessageMediaOptions));
end;

function TTgApi.EditInlineMessageMediaAsync(const AInlineMessageId: string;
  const AMedia: TTgInputMedia; const AOptions: TTgEditMessageMediaOptions;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecEditMessageMediaVariant2;
  Result := RunAsyncCall<Boolean>(BuildEditMessageMediaVariant2Params(AInlineMessageId, AMedia, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.EditInlineMessageMediaAsync(const AInlineMessageId: string;
  const AMedia: TTgInputMedia; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := EditInlineMessageMediaAsync(AInlineMessageId, AMedia,
  Default(TTgEditMessageMediaOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryEditInlineMessageMedia(const AInlineMessageId: string;
  const AMedia: TTgInputMedia; const AOptions: TTgEditMessageMediaOptions;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    EditInlineMessageMedia(AInlineMessageId, AMedia, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryEditInlineMessageMedia(const AInlineMessageId: string;
  const AMedia: TTgInputMedia; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryEditInlineMessageMedia(AInlineMessageId, AMedia, Default(TTgEditMessageMediaOptions),
  AError);
end;

function TTgApi.BuildEditMessageLiveLocationParams(ALatitude: Double; ALongitude: Double;
  const AOptions: TTgEditMessageLiveLocationOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('latitude', ALatitude);
    Result.Add('longitude', ALongitude);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecEditMessageLiveLocation(AParams: TTgParams): ITgMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('editMessageLiveLocation', AParams);
  Result := TTgDto.ResultObjectOrTrue<ITgMessage>(LValue, 'editMessageLiveLocation', TgMakeMessage);
end;

function TTgApi.EditMessageLiveLocation(ALatitude: Double; ALongitude: Double;
  const AOptions: TTgEditMessageLiveLocationOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildEditMessageLiveLocationParams(ALatitude, ALongitude, AOptions);
  try
    Result := ExecEditMessageLiveLocation(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.EditMessageLiveLocation(ALatitude: Double; ALongitude: Double): ITgMessage;
begin
  Result := EditMessageLiveLocation(ALatitude, ALongitude,
  Default(TTgEditMessageLiveLocationOptions));
end;

function TTgApi.EditMessageLiveLocationAsync(ALatitude: Double; ALongitude: Double;
  const AOptions: TTgEditMessageLiveLocationOptions; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecEditMessageLiveLocation;
  Result := RunAsyncCall<ITgMessage>(BuildEditMessageLiveLocationParams(ALatitude, ALongitude, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.EditMessageLiveLocationAsync(ALatitude: Double; ALongitude: Double;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
begin
  Result := EditMessageLiveLocationAsync(ALatitude, ALongitude,
  Default(TTgEditMessageLiveLocationOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryEditMessageLiveLocation(ALatitude: Double; ALongitude: Double;
  const AOptions: TTgEditMessageLiveLocationOptions; out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := EditMessageLiveLocation(ALatitude, ALongitude, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryEditMessageLiveLocation(ALatitude: Double; ALongitude: Double;
  out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryEditMessageLiveLocation(ALatitude, ALongitude,
  Default(TTgEditMessageLiveLocationOptions), AResult, AError);
end;

function TTgApi.BuildEditMessageLiveLocationVariant1Params(const AChatId: TTgChatId;
  AMessageId: Int64; ALatitude: Double; ALongitude: Double;
  const AOptions: TTgEditMessageLiveLocationOptions): TTgParams;
var
  LOptions: TTgEditMessageLiveLocationOptions;
begin
  LOptions := AOptions;
  LOptions.ChatId := AChatId;
  LOptions.MessageId := AMessageId;
  Result := BuildEditMessageLiveLocationParams(ALatitude, ALongitude, LOptions);
end;

function TTgApi.EditMessageLiveLocation(const AChatId: TTgChatId; AMessageId: Int64;
  ALatitude: Double; ALongitude: Double;
  const AOptions: TTgEditMessageLiveLocationOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildEditMessageLiveLocationVariant1Params(AChatId, AMessageId, ALatitude, ALongitude,
    AOptions);
  try
    Result := ExecEditMessageLiveLocation(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.EditMessageLiveLocation(const AChatId: TTgChatId; AMessageId: Int64;
  ALatitude: Double; ALongitude: Double): ITgMessage;
begin
  Result := EditMessageLiveLocation(AChatId, AMessageId, ALatitude, ALongitude,
  Default(TTgEditMessageLiveLocationOptions));
end;

function TTgApi.EditMessageLiveLocationAsync(const AChatId: TTgChatId; AMessageId: Int64;
  ALatitude: Double; ALongitude: Double; const AOptions: TTgEditMessageLiveLocationOptions;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecEditMessageLiveLocation;
  Result := RunAsyncCall<ITgMessage>(BuildEditMessageLiveLocationVariant1Params(AChatId, AMessageId, ALatitude, ALongitude, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.EditMessageLiveLocationAsync(const AChatId: TTgChatId; AMessageId: Int64;
  ALatitude: Double; ALongitude: Double; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := EditMessageLiveLocationAsync(AChatId, AMessageId, ALatitude, ALongitude,
  Default(TTgEditMessageLiveLocationOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryEditMessageLiveLocation(const AChatId: TTgChatId; AMessageId: Int64;
  ALatitude: Double; ALongitude: Double; const AOptions: TTgEditMessageLiveLocationOptions;
  out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := EditMessageLiveLocation(AChatId, AMessageId, ALatitude, ALongitude, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryEditMessageLiveLocation(const AChatId: TTgChatId; AMessageId: Int64;
  ALatitude: Double; ALongitude: Double; out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryEditMessageLiveLocation(AChatId, AMessageId, ALatitude, ALongitude,
  Default(TTgEditMessageLiveLocationOptions), AResult, AError);
end;

function TTgApi.BuildEditMessageLiveLocationVariant2Params(const AInlineMessageId: string;
  ALatitude: Double; ALongitude: Double;
  const AOptions: TTgEditMessageLiveLocationOptions): TTgParams;
var
  LOptions: TTgEditMessageLiveLocationOptions;
begin
  LOptions := AOptions;
  LOptions.InlineMessageId := AInlineMessageId;
  Result := BuildEditMessageLiveLocationParams(ALatitude, ALongitude, LOptions);
end;

function TTgApi.ExecEditMessageLiveLocationVariant2(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('editMessageLiveLocation', AParams);
  Result := TTgDto.ResultBool(LValue, 'editMessageLiveLocation');
end;

function TTgApi.EditInlineMessageLiveLocation(const AInlineMessageId: string; ALatitude: Double;
  ALongitude: Double; const AOptions: TTgEditMessageLiveLocationOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildEditMessageLiveLocationVariant2Params(AInlineMessageId, ALatitude, ALongitude,
    AOptions);
  try
    Result := ExecEditMessageLiveLocationVariant2(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.EditInlineMessageLiveLocation(const AInlineMessageId: string; ALatitude: Double;
  ALongitude: Double): Boolean;
begin
  Result := EditInlineMessageLiveLocation(AInlineMessageId, ALatitude, ALongitude,
  Default(TTgEditMessageLiveLocationOptions));
end;

function TTgApi.EditInlineMessageLiveLocationAsync(const AInlineMessageId: string;
  ALatitude: Double; ALongitude: Double; const AOptions: TTgEditMessageLiveLocationOptions;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecEditMessageLiveLocationVariant2;
  Result := RunAsyncCall<Boolean>(BuildEditMessageLiveLocationVariant2Params(AInlineMessageId, ALatitude, ALongitude, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.EditInlineMessageLiveLocationAsync(const AInlineMessageId: string;
  ALatitude: Double; ALongitude: Double; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := EditInlineMessageLiveLocationAsync(AInlineMessageId, ALatitude, ALongitude,
  Default(TTgEditMessageLiveLocationOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryEditInlineMessageLiveLocation(const AInlineMessageId: string; ALatitude: Double;
  ALongitude: Double; const AOptions: TTgEditMessageLiveLocationOptions;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    EditInlineMessageLiveLocation(AInlineMessageId, ALatitude, ALongitude, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryEditInlineMessageLiveLocation(const AInlineMessageId: string; ALatitude: Double;
  ALongitude: Double; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryEditInlineMessageLiveLocation(AInlineMessageId, ALatitude, ALongitude,
  Default(TTgEditMessageLiveLocationOptions), AError);
end;

function TTgApi.BuildStopMessageLiveLocationParams(const AOptions: TTgStopMessageLiveLocationOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecStopMessageLiveLocation(AParams: TTgParams): ITgMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('stopMessageLiveLocation', AParams);
  Result := TTgDto.ResultObjectOrTrue<ITgMessage>(LValue, 'stopMessageLiveLocation', TgMakeMessage);
end;

function TTgApi.StopMessageLiveLocation(const AOptions: TTgStopMessageLiveLocationOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildStopMessageLiveLocationParams(AOptions);
  try
    Result := ExecStopMessageLiveLocation(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.StopMessageLiveLocation: ITgMessage;
begin
  Result := StopMessageLiveLocation(Default(TTgStopMessageLiveLocationOptions));
end;

function TTgApi.StopMessageLiveLocationAsync(const AOptions: TTgStopMessageLiveLocationOptions;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecStopMessageLiveLocation;
  Result := RunAsyncCall<ITgMessage>(BuildStopMessageLiveLocationParams(AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.StopMessageLiveLocationAsync(const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := StopMessageLiveLocationAsync(Default(TTgStopMessageLiveLocationOptions), AOnSuccess,
  AOnError);
end;

function TTgApi.TryStopMessageLiveLocation(const AOptions: TTgStopMessageLiveLocationOptions;
  out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := StopMessageLiveLocation(AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryStopMessageLiveLocation(out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryStopMessageLiveLocation(Default(TTgStopMessageLiveLocationOptions), AResult, AError);
end;

function TTgApi.BuildStopMessageLiveLocationVariant1Params(const AChatId: TTgChatId;
  AMessageId: Int64; const AOptions: TTgStopMessageLiveLocationOptions): TTgParams;
var
  LOptions: TTgStopMessageLiveLocationOptions;
begin
  LOptions := AOptions;
  LOptions.ChatId := AChatId;
  LOptions.MessageId := AMessageId;
  Result := BuildStopMessageLiveLocationParams(LOptions);
end;

function TTgApi.StopMessageLiveLocation(const AChatId: TTgChatId; AMessageId: Int64;
  const AOptions: TTgStopMessageLiveLocationOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildStopMessageLiveLocationVariant1Params(AChatId, AMessageId, AOptions);
  try
    Result := ExecStopMessageLiveLocation(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.StopMessageLiveLocation(const AChatId: TTgChatId; AMessageId: Int64): ITgMessage;
begin
  Result := StopMessageLiveLocation(AChatId, AMessageId,
  Default(TTgStopMessageLiveLocationOptions));
end;

function TTgApi.StopMessageLiveLocationAsync(const AChatId: TTgChatId; AMessageId: Int64;
  const AOptions: TTgStopMessageLiveLocationOptions; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecStopMessageLiveLocation;
  Result := RunAsyncCall<ITgMessage>(BuildStopMessageLiveLocationVariant1Params(AChatId, AMessageId, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.StopMessageLiveLocationAsync(const AChatId: TTgChatId; AMessageId: Int64;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
begin
  Result := StopMessageLiveLocationAsync(AChatId, AMessageId,
  Default(TTgStopMessageLiveLocationOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryStopMessageLiveLocation(const AChatId: TTgChatId; AMessageId: Int64;
  const AOptions: TTgStopMessageLiveLocationOptions; out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := StopMessageLiveLocation(AChatId, AMessageId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryStopMessageLiveLocation(const AChatId: TTgChatId; AMessageId: Int64;
  out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryStopMessageLiveLocation(AChatId, AMessageId,
  Default(TTgStopMessageLiveLocationOptions), AResult, AError);
end;

function TTgApi.BuildStopMessageLiveLocationVariant2Params(const AInlineMessageId: string;
  const AOptions: TTgStopMessageLiveLocationOptions): TTgParams;
var
  LOptions: TTgStopMessageLiveLocationOptions;
begin
  LOptions := AOptions;
  LOptions.InlineMessageId := AInlineMessageId;
  Result := BuildStopMessageLiveLocationParams(LOptions);
end;

function TTgApi.ExecStopMessageLiveLocationVariant2(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('stopMessageLiveLocation', AParams);
  Result := TTgDto.ResultBool(LValue, 'stopMessageLiveLocation');
end;

function TTgApi.StopInlineMessageLiveLocation(const AInlineMessageId: string;
  const AOptions: TTgStopMessageLiveLocationOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildStopMessageLiveLocationVariant2Params(AInlineMessageId, AOptions);
  try
    Result := ExecStopMessageLiveLocationVariant2(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.StopInlineMessageLiveLocation(const AInlineMessageId: string): Boolean;
begin
  Result := StopInlineMessageLiveLocation(AInlineMessageId,
  Default(TTgStopMessageLiveLocationOptions));
end;

function TTgApi.StopInlineMessageLiveLocationAsync(const AInlineMessageId: string;
  const AOptions: TTgStopMessageLiveLocationOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecStopMessageLiveLocationVariant2;
  Result := RunAsyncCall<Boolean>(BuildStopMessageLiveLocationVariant2Params(AInlineMessageId, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.StopInlineMessageLiveLocationAsync(const AInlineMessageId: string;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
begin
  Result := StopInlineMessageLiveLocationAsync(AInlineMessageId,
  Default(TTgStopMessageLiveLocationOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryStopInlineMessageLiveLocation(const AInlineMessageId: string;
  const AOptions: TTgStopMessageLiveLocationOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    StopInlineMessageLiveLocation(AInlineMessageId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryStopInlineMessageLiveLocation(const AInlineMessageId: string;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryStopInlineMessageLiveLocation(AInlineMessageId,
  Default(TTgStopMessageLiveLocationOptions), AError);
end;

function TTgApi.BuildEditMessageChecklistParams(const ABusinessConnectionId: string;
  const AChatId: TTgChatId; AMessageId: Int64; const AChecklist: ITgInputChecklist;
  const AOptions: TTgEditMessageChecklistOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('business_connection_id', ABusinessConnectionId);
    Result.AddChatId('chat_id', AChatId);
    Result.Add('message_id', AMessageId);
    Result.AddJson('checklist', TTgDto.Serialize(AChecklist, Result));
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecEditMessageChecklist(AParams: TTgParams): ITgMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('editMessageChecklist', AParams);
  Result := TTgDto.ResultObject<ITgMessage>(LValue, 'editMessageChecklist', TgMakeMessage);
end;

function TTgApi.EditMessageChecklist(const ABusinessConnectionId: string; const AChatId: TTgChatId;
  AMessageId: Int64; const AChecklist: ITgInputChecklist;
  const AOptions: TTgEditMessageChecklistOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildEditMessageChecklistParams(ABusinessConnectionId, AChatId, AMessageId, AChecklist,
    AOptions);
  try
    Result := ExecEditMessageChecklist(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.EditMessageChecklist(const ABusinessConnectionId: string; const AChatId: TTgChatId;
  AMessageId: Int64; const AChecklist: ITgInputChecklist): ITgMessage;
begin
  Result := EditMessageChecklist(ABusinessConnectionId, AChatId, AMessageId, AChecklist,
  Default(TTgEditMessageChecklistOptions));
end;

function TTgApi.EditMessageChecklistAsync(const ABusinessConnectionId: string;
  const AChatId: TTgChatId; AMessageId: Int64; const AChecklist: ITgInputChecklist;
  const AOptions: TTgEditMessageChecklistOptions; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecEditMessageChecklist;
  Result := RunAsyncCall<ITgMessage>(BuildEditMessageChecklistParams(ABusinessConnectionId, AChatId, AMessageId, AChecklist, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.EditMessageChecklistAsync(const ABusinessConnectionId: string;
  const AChatId: TTgChatId; AMessageId: Int64; const AChecklist: ITgInputChecklist;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
begin
  Result := EditMessageChecklistAsync(ABusinessConnectionId, AChatId, AMessageId, AChecklist,
  Default(TTgEditMessageChecklistOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryEditMessageChecklist(const ABusinessConnectionId: string;
  const AChatId: TTgChatId; AMessageId: Int64; const AChecklist: ITgInputChecklist;
  const AOptions: TTgEditMessageChecklistOptions; out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := EditMessageChecklist(ABusinessConnectionId, AChatId, AMessageId, AChecklist,
      AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryEditMessageChecklist(const ABusinessConnectionId: string;
  const AChatId: TTgChatId; AMessageId: Int64; const AChecklist: ITgInputChecklist;
  out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryEditMessageChecklist(ABusinessConnectionId, AChatId, AMessageId, AChecklist,
  Default(TTgEditMessageChecklistOptions), AResult, AError);
end;

function TTgApi.BuildEditMessageReplyMarkupParams(const AOptions: TTgEditMessageReplyMarkupOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecEditMessageReplyMarkup(AParams: TTgParams): ITgMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('editMessageReplyMarkup', AParams);
  Result := TTgDto.ResultObjectOrTrue<ITgMessage>(LValue, 'editMessageReplyMarkup', TgMakeMessage);
end;

function TTgApi.EditMessageReplyMarkup(const AOptions: TTgEditMessageReplyMarkupOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildEditMessageReplyMarkupParams(AOptions);
  try
    Result := ExecEditMessageReplyMarkup(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.EditMessageReplyMarkup: ITgMessage;
begin
  Result := EditMessageReplyMarkup(Default(TTgEditMessageReplyMarkupOptions));
end;

function TTgApi.EditMessageReplyMarkupAsync(const AOptions: TTgEditMessageReplyMarkupOptions;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecEditMessageReplyMarkup;
  Result := RunAsyncCall<ITgMessage>(BuildEditMessageReplyMarkupParams(AOptions), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.EditMessageReplyMarkupAsync(const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := EditMessageReplyMarkupAsync(Default(TTgEditMessageReplyMarkupOptions), AOnSuccess,
  AOnError);
end;

function TTgApi.TryEditMessageReplyMarkup(const AOptions: TTgEditMessageReplyMarkupOptions;
  out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := EditMessageReplyMarkup(AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryEditMessageReplyMarkup(out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryEditMessageReplyMarkup(Default(TTgEditMessageReplyMarkupOptions), AResult, AError);
end;

function TTgApi.BuildEditMessageReplyMarkupVariant1Params(const AChatId: TTgChatId;
  AMessageId: Int64; const AReplyMarkup: ITgInlineKeyboardMarkup;
  const AOptions: TTgEditMessageReplyMarkupOptions): TTgParams;
var
  LOptions: TTgEditMessageReplyMarkupOptions;
begin
  LOptions := AOptions;
  LOptions.ChatId := AChatId;
  LOptions.MessageId := AMessageId;
  LOptions.ReplyMarkup := AReplyMarkup;
  Result := BuildEditMessageReplyMarkupParams(LOptions);
end;

function TTgApi.EditMessageReplyMarkup(const AChatId: TTgChatId; AMessageId: Int64;
  const AReplyMarkup: ITgInlineKeyboardMarkup;
  const AOptions: TTgEditMessageReplyMarkupOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildEditMessageReplyMarkupVariant1Params(AChatId, AMessageId, AReplyMarkup, AOptions);
  try
    Result := ExecEditMessageReplyMarkup(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.EditMessageReplyMarkup(const AChatId: TTgChatId; AMessageId: Int64;
  const AReplyMarkup: ITgInlineKeyboardMarkup): ITgMessage;
begin
  Result := EditMessageReplyMarkup(AChatId, AMessageId, AReplyMarkup,
  Default(TTgEditMessageReplyMarkupOptions));
end;

function TTgApi.EditMessageReplyMarkupAsync(const AChatId: TTgChatId; AMessageId: Int64;
  const AReplyMarkup: ITgInlineKeyboardMarkup; const AOptions: TTgEditMessageReplyMarkupOptions;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecEditMessageReplyMarkup;
  Result := RunAsyncCall<ITgMessage>(BuildEditMessageReplyMarkupVariant1Params(AChatId, AMessageId, AReplyMarkup, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.EditMessageReplyMarkupAsync(const AChatId: TTgChatId; AMessageId: Int64;
  const AReplyMarkup: ITgInlineKeyboardMarkup; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := EditMessageReplyMarkupAsync(AChatId, AMessageId, AReplyMarkup,
  Default(TTgEditMessageReplyMarkupOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryEditMessageReplyMarkup(const AChatId: TTgChatId; AMessageId: Int64;
  const AReplyMarkup: ITgInlineKeyboardMarkup; const AOptions: TTgEditMessageReplyMarkupOptions;
  out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := EditMessageReplyMarkup(AChatId, AMessageId, AReplyMarkup, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryEditMessageReplyMarkup(const AChatId: TTgChatId; AMessageId: Int64;
  const AReplyMarkup: ITgInlineKeyboardMarkup; out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryEditMessageReplyMarkup(AChatId, AMessageId, AReplyMarkup,
  Default(TTgEditMessageReplyMarkupOptions), AResult, AError);
end;

function TTgApi.BuildEditMessageReplyMarkupVariant2Params(const AInlineMessageId: string;
  const AReplyMarkup: ITgInlineKeyboardMarkup;
  const AOptions: TTgEditMessageReplyMarkupOptions): TTgParams;
var
  LOptions: TTgEditMessageReplyMarkupOptions;
begin
  LOptions := AOptions;
  LOptions.InlineMessageId := AInlineMessageId;
  LOptions.ReplyMarkup := AReplyMarkup;
  Result := BuildEditMessageReplyMarkupParams(LOptions);
end;

function TTgApi.ExecEditMessageReplyMarkupVariant2(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('editMessageReplyMarkup', AParams);
  Result := TTgDto.ResultBool(LValue, 'editMessageReplyMarkup');
end;

function TTgApi.EditInlineMessageReplyMarkup(const AInlineMessageId: string;
  const AReplyMarkup: ITgInlineKeyboardMarkup;
  const AOptions: TTgEditMessageReplyMarkupOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildEditMessageReplyMarkupVariant2Params(AInlineMessageId, AReplyMarkup, AOptions);
  try
    Result := ExecEditMessageReplyMarkupVariant2(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.EditInlineMessageReplyMarkup(const AInlineMessageId: string;
  const AReplyMarkup: ITgInlineKeyboardMarkup): Boolean;
begin
  Result := EditInlineMessageReplyMarkup(AInlineMessageId, AReplyMarkup,
  Default(TTgEditMessageReplyMarkupOptions));
end;

function TTgApi.EditInlineMessageReplyMarkupAsync(const AInlineMessageId: string;
  const AReplyMarkup: ITgInlineKeyboardMarkup; const AOptions: TTgEditMessageReplyMarkupOptions;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecEditMessageReplyMarkupVariant2;
  Result := RunAsyncCall<Boolean>(BuildEditMessageReplyMarkupVariant2Params(AInlineMessageId, AReplyMarkup, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.EditInlineMessageReplyMarkupAsync(const AInlineMessageId: string;
  const AReplyMarkup: ITgInlineKeyboardMarkup; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := EditInlineMessageReplyMarkupAsync(AInlineMessageId, AReplyMarkup,
  Default(TTgEditMessageReplyMarkupOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryEditInlineMessageReplyMarkup(const AInlineMessageId: string;
  const AReplyMarkup: ITgInlineKeyboardMarkup; const AOptions: TTgEditMessageReplyMarkupOptions;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    EditInlineMessageReplyMarkup(AInlineMessageId, AReplyMarkup, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryEditInlineMessageReplyMarkup(const AInlineMessageId: string;
  const AReplyMarkup: ITgInlineKeyboardMarkup; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryEditInlineMessageReplyMarkup(AInlineMessageId, AReplyMarkup,
  Default(TTgEditMessageReplyMarkupOptions), AError);
end;

function TTgApi.BuildStopPollParams(const AChatId: TTgChatId; AMessageId: Int64;
  const AOptions: TTgStopPollOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('message_id', AMessageId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecStopPoll(AParams: TTgParams): ITgPoll;
var
  LValue: TJSONValue;
begin
  LValue := Call('stopPoll', AParams);
  Result := TTgDto.ResultObject<ITgPoll>(LValue, 'stopPoll', TgMakePoll);
end;

function TTgApi.StopPoll(const AChatId: TTgChatId; AMessageId: Int64;
  const AOptions: TTgStopPollOptions): ITgPoll;
var
  LParams: TTgParams;
begin
  LParams := BuildStopPollParams(AChatId, AMessageId, AOptions);
  try
    Result := ExecStopPoll(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.StopPoll(const AChatId: TTgChatId; AMessageId: Int64): ITgPoll;
begin
  Result := StopPoll(AChatId, AMessageId, Default(TTgStopPollOptions));
end;

function TTgApi.StopPollAsync(const AChatId: TTgChatId; AMessageId: Int64;
  const AOptions: TTgStopPollOptions; const AOnSuccess: TProc<ITgPoll>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgPoll>;
begin
  LExec := ExecStopPoll;
  Result := RunAsyncCall<ITgPoll>(BuildStopPollParams(AChatId, AMessageId, AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.StopPollAsync(const AChatId: TTgChatId; AMessageId: Int64;
  const AOnSuccess: TProc<ITgPoll>; const AOnError: TProc<Exception>): ITask;
begin
  Result := StopPollAsync(AChatId, AMessageId, Default(TTgStopPollOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryStopPoll(const AChatId: TTgChatId; AMessageId: Int64;
  const AOptions: TTgStopPollOptions; out AResult: ITgPoll; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgPoll);
  AError := TTgErrorInfo.Empty;
  try
    AResult := StopPoll(AChatId, AMessageId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryStopPoll(const AChatId: TTgChatId; AMessageId: Int64; out AResult: ITgPoll;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryStopPoll(AChatId, AMessageId, Default(TTgStopPollOptions), AResult, AError);
end;

function TTgApi.BuildEditEphemeralMessageTextParams(const AChatId: TTgChatId;
  AReceiverUserId: Int64; AEphemeralMessageId: Int64;
  const AOptions: TTgEditEphemeralMessageTextOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('receiver_user_id', AReceiverUserId);
    Result.Add('ephemeral_message_id', AEphemeralMessageId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecEditEphemeralMessageText(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('editEphemeralMessageText', AParams);
  Result := TTgDto.ResultBool(LValue, 'editEphemeralMessageText');
end;

function TTgApi.EditEphemeralMessageText(const AChatId: TTgChatId; AReceiverUserId: Int64;
  AEphemeralMessageId: Int64; const AOptions: TTgEditEphemeralMessageTextOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildEditEphemeralMessageTextParams(AChatId, AReceiverUserId, AEphemeralMessageId,
    AOptions);
  try
    Result := ExecEditEphemeralMessageText(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.EditEphemeralMessageText(const AChatId: TTgChatId; AReceiverUserId: Int64;
  AEphemeralMessageId: Int64): Boolean;
begin
  Result := EditEphemeralMessageText(AChatId, AReceiverUserId, AEphemeralMessageId,
  Default(TTgEditEphemeralMessageTextOptions));
end;

function TTgApi.EditEphemeralMessageTextAsync(const AChatId: TTgChatId; AReceiverUserId: Int64;
  AEphemeralMessageId: Int64; const AOptions: TTgEditEphemeralMessageTextOptions;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecEditEphemeralMessageText;
  Result := RunAsyncCall<Boolean>(BuildEditEphemeralMessageTextParams(AChatId, AReceiverUserId, AEphemeralMessageId, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.EditEphemeralMessageTextAsync(const AChatId: TTgChatId; AReceiverUserId: Int64;
  AEphemeralMessageId: Int64; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := EditEphemeralMessageTextAsync(AChatId, AReceiverUserId, AEphemeralMessageId,
  Default(TTgEditEphemeralMessageTextOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryEditEphemeralMessageText(const AChatId: TTgChatId; AReceiverUserId: Int64;
  AEphemeralMessageId: Int64; const AOptions: TTgEditEphemeralMessageTextOptions;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    EditEphemeralMessageText(AChatId, AReceiverUserId, AEphemeralMessageId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryEditEphemeralMessageText(const AChatId: TTgChatId; AReceiverUserId: Int64;
  AEphemeralMessageId: Int64; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryEditEphemeralMessageText(AChatId, AReceiverUserId, AEphemeralMessageId,
  Default(TTgEditEphemeralMessageTextOptions), AError);
end;

function TTgApi.BuildEditEphemeralMessageMediaParams(const AChatId: TTgChatId;
  AReceiverUserId: Int64; AEphemeralMessageId: Int64; const AMedia: TTgInputMedia;
  const AOptions: TTgEditEphemeralMessageMediaOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('receiver_user_id', AReceiverUserId);
    Result.Add('ephemeral_message_id', AEphemeralMessageId);
    Result.AddJson('media', TTgDto.Serialize(AMedia.Value, Result));
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecEditEphemeralMessageMedia(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('editEphemeralMessageMedia', AParams);
  Result := TTgDto.ResultBool(LValue, 'editEphemeralMessageMedia');
end;

function TTgApi.EditEphemeralMessageMedia(const AChatId: TTgChatId; AReceiverUserId: Int64;
  AEphemeralMessageId: Int64; const AMedia: TTgInputMedia;
  const AOptions: TTgEditEphemeralMessageMediaOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildEditEphemeralMessageMediaParams(AChatId, AReceiverUserId, AEphemeralMessageId,
    AMedia, AOptions);
  try
    Result := ExecEditEphemeralMessageMedia(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.EditEphemeralMessageMedia(const AChatId: TTgChatId; AReceiverUserId: Int64;
  AEphemeralMessageId: Int64; const AMedia: TTgInputMedia): Boolean;
begin
  Result := EditEphemeralMessageMedia(AChatId, AReceiverUserId, AEphemeralMessageId, AMedia,
  Default(TTgEditEphemeralMessageMediaOptions));
end;

function TTgApi.EditEphemeralMessageMediaAsync(const AChatId: TTgChatId; AReceiverUserId: Int64;
  AEphemeralMessageId: Int64; const AMedia: TTgInputMedia;
  const AOptions: TTgEditEphemeralMessageMediaOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecEditEphemeralMessageMedia;
  Result := RunAsyncCall<Boolean>(BuildEditEphemeralMessageMediaParams(AChatId, AReceiverUserId, AEphemeralMessageId, AMedia, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.EditEphemeralMessageMediaAsync(const AChatId: TTgChatId; AReceiverUserId: Int64;
  AEphemeralMessageId: Int64; const AMedia: TTgInputMedia; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := EditEphemeralMessageMediaAsync(AChatId, AReceiverUserId, AEphemeralMessageId, AMedia,
  Default(TTgEditEphemeralMessageMediaOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryEditEphemeralMessageMedia(const AChatId: TTgChatId; AReceiverUserId: Int64;
  AEphemeralMessageId: Int64; const AMedia: TTgInputMedia;
  const AOptions: TTgEditEphemeralMessageMediaOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    EditEphemeralMessageMedia(AChatId, AReceiverUserId, AEphemeralMessageId, AMedia, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryEditEphemeralMessageMedia(const AChatId: TTgChatId; AReceiverUserId: Int64;
  AEphemeralMessageId: Int64; const AMedia: TTgInputMedia; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryEditEphemeralMessageMedia(AChatId, AReceiverUserId, AEphemeralMessageId, AMedia,
  Default(TTgEditEphemeralMessageMediaOptions), AError);
end;

function TTgApi.BuildEditEphemeralMessageCaptionParams(const AChatId: TTgChatId;
  AReceiverUserId: Int64; AEphemeralMessageId: Int64;
  const AOptions: TTgEditEphemeralMessageCaptionOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('receiver_user_id', AReceiverUserId);
    Result.Add('ephemeral_message_id', AEphemeralMessageId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecEditEphemeralMessageCaption(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('editEphemeralMessageCaption', AParams);
  Result := TTgDto.ResultBool(LValue, 'editEphemeralMessageCaption');
end;

function TTgApi.EditEphemeralMessageCaption(const AChatId: TTgChatId; AReceiverUserId: Int64;
  AEphemeralMessageId: Int64; const AOptions: TTgEditEphemeralMessageCaptionOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildEditEphemeralMessageCaptionParams(AChatId, AReceiverUserId, AEphemeralMessageId,
    AOptions);
  try
    Result := ExecEditEphemeralMessageCaption(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.EditEphemeralMessageCaption(const AChatId: TTgChatId; AReceiverUserId: Int64;
  AEphemeralMessageId: Int64): Boolean;
begin
  Result := EditEphemeralMessageCaption(AChatId, AReceiverUserId, AEphemeralMessageId,
  Default(TTgEditEphemeralMessageCaptionOptions));
end;

function TTgApi.EditEphemeralMessageCaptionAsync(const AChatId: TTgChatId; AReceiverUserId: Int64;
  AEphemeralMessageId: Int64; const AOptions: TTgEditEphemeralMessageCaptionOptions;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecEditEphemeralMessageCaption;
  Result := RunAsyncCall<Boolean>(BuildEditEphemeralMessageCaptionParams(AChatId, AReceiverUserId, AEphemeralMessageId, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.EditEphemeralMessageCaptionAsync(const AChatId: TTgChatId; AReceiverUserId: Int64;
  AEphemeralMessageId: Int64; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := EditEphemeralMessageCaptionAsync(AChatId, AReceiverUserId, AEphemeralMessageId,
  Default(TTgEditEphemeralMessageCaptionOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryEditEphemeralMessageCaption(const AChatId: TTgChatId; AReceiverUserId: Int64;
  AEphemeralMessageId: Int64; const AOptions: TTgEditEphemeralMessageCaptionOptions;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    EditEphemeralMessageCaption(AChatId, AReceiverUserId, AEphemeralMessageId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryEditEphemeralMessageCaption(const AChatId: TTgChatId; AReceiverUserId: Int64;
  AEphemeralMessageId: Int64; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryEditEphemeralMessageCaption(AChatId, AReceiverUserId, AEphemeralMessageId,
  Default(TTgEditEphemeralMessageCaptionOptions), AError);
end;

function TTgApi.BuildEditEphemeralMessageReplyMarkupParams(const AChatId: TTgChatId;
  AReceiverUserId: Int64; AEphemeralMessageId: Int64;
  const AOptions: TTgEditEphemeralMessageReplyMarkupOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('receiver_user_id', AReceiverUserId);
    Result.Add('ephemeral_message_id', AEphemeralMessageId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecEditEphemeralMessageReplyMarkup(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('editEphemeralMessageReplyMarkup', AParams);
  Result := TTgDto.ResultBool(LValue, 'editEphemeralMessageReplyMarkup');
end;

function TTgApi.EditEphemeralMessageReplyMarkup(const AChatId: TTgChatId; AReceiverUserId: Int64;
  AEphemeralMessageId: Int64; const AOptions: TTgEditEphemeralMessageReplyMarkupOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildEditEphemeralMessageReplyMarkupParams(AChatId, AReceiverUserId,
    AEphemeralMessageId, AOptions);
  try
    Result := ExecEditEphemeralMessageReplyMarkup(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.EditEphemeralMessageReplyMarkup(const AChatId: TTgChatId; AReceiverUserId: Int64;
  AEphemeralMessageId: Int64): Boolean;
begin
  Result := EditEphemeralMessageReplyMarkup(AChatId, AReceiverUserId, AEphemeralMessageId,
  Default(TTgEditEphemeralMessageReplyMarkupOptions));
end;

function TTgApi.EditEphemeralMessageReplyMarkupAsync(const AChatId: TTgChatId;
  AReceiverUserId: Int64; AEphemeralMessageId: Int64;
  const AOptions: TTgEditEphemeralMessageReplyMarkupOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecEditEphemeralMessageReplyMarkup;
  Result := RunAsyncCall<Boolean>(BuildEditEphemeralMessageReplyMarkupParams(AChatId, AReceiverUserId, AEphemeralMessageId, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.EditEphemeralMessageReplyMarkupAsync(const AChatId: TTgChatId;
  AReceiverUserId: Int64; AEphemeralMessageId: Int64; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := EditEphemeralMessageReplyMarkupAsync(AChatId, AReceiverUserId, AEphemeralMessageId,
  Default(TTgEditEphemeralMessageReplyMarkupOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryEditEphemeralMessageReplyMarkup(const AChatId: TTgChatId; AReceiverUserId: Int64;
  AEphemeralMessageId: Int64; const AOptions: TTgEditEphemeralMessageReplyMarkupOptions;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    EditEphemeralMessageReplyMarkup(AChatId, AReceiverUserId, AEphemeralMessageId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryEditEphemeralMessageReplyMarkup(const AChatId: TTgChatId; AReceiverUserId: Int64;
  AEphemeralMessageId: Int64; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryEditEphemeralMessageReplyMarkup(AChatId, AReceiverUserId, AEphemeralMessageId,
  Default(TTgEditEphemeralMessageReplyMarkupOptions), AError);
end;

function TTgApi.BuildApproveSuggestedPostParams(AChatId: Int64; AMessageId: Int64;
  const AOptions: TTgApproveSuggestedPostOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('chat_id', AChatId);
    Result.Add('message_id', AMessageId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecApproveSuggestedPost(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('approveSuggestedPost', AParams);
  Result := TTgDto.ResultBool(LValue, 'approveSuggestedPost');
end;

function TTgApi.ApproveSuggestedPost(AChatId: Int64; AMessageId: Int64;
  const AOptions: TTgApproveSuggestedPostOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildApproveSuggestedPostParams(AChatId, AMessageId, AOptions);
  try
    Result := ExecApproveSuggestedPost(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.ApproveSuggestedPost(AChatId: Int64; AMessageId: Int64): Boolean;
begin
  Result := ApproveSuggestedPost(AChatId, AMessageId, Default(TTgApproveSuggestedPostOptions));
end;

function TTgApi.ApproveSuggestedPostAsync(AChatId: Int64; AMessageId: Int64;
  const AOptions: TTgApproveSuggestedPostOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecApproveSuggestedPost;
  Result := RunAsyncCall<Boolean>(BuildApproveSuggestedPostParams(AChatId, AMessageId, AOptions),
    LExec, AOnSuccess, AOnError);
end;

function TTgApi.ApproveSuggestedPostAsync(AChatId: Int64; AMessageId: Int64;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
begin
  Result := ApproveSuggestedPostAsync(AChatId, AMessageId, Default(TTgApproveSuggestedPostOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TryApproveSuggestedPost(AChatId: Int64; AMessageId: Int64;
  const AOptions: TTgApproveSuggestedPostOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    ApproveSuggestedPost(AChatId, AMessageId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryApproveSuggestedPost(AChatId: Int64; AMessageId: Int64;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryApproveSuggestedPost(AChatId, AMessageId, Default(TTgApproveSuggestedPostOptions),
  AError);
end;

function TTgApi.BuildDeclineSuggestedPostParams(AChatId: Int64; AMessageId: Int64;
  const AOptions: TTgDeclineSuggestedPostOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('chat_id', AChatId);
    Result.Add('message_id', AMessageId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecDeclineSuggestedPost(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('declineSuggestedPost', AParams);
  Result := TTgDto.ResultBool(LValue, 'declineSuggestedPost');
end;

function TTgApi.DeclineSuggestedPost(AChatId: Int64; AMessageId: Int64;
  const AOptions: TTgDeclineSuggestedPostOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildDeclineSuggestedPostParams(AChatId, AMessageId, AOptions);
  try
    Result := ExecDeclineSuggestedPost(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.DeclineSuggestedPost(AChatId: Int64; AMessageId: Int64): Boolean;
begin
  Result := DeclineSuggestedPost(AChatId, AMessageId, Default(TTgDeclineSuggestedPostOptions));
end;

function TTgApi.DeclineSuggestedPostAsync(AChatId: Int64; AMessageId: Int64;
  const AOptions: TTgDeclineSuggestedPostOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecDeclineSuggestedPost;
  Result := RunAsyncCall<Boolean>(BuildDeclineSuggestedPostParams(AChatId, AMessageId, AOptions),
    LExec, AOnSuccess, AOnError);
end;

function TTgApi.DeclineSuggestedPostAsync(AChatId: Int64; AMessageId: Int64;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
begin
  Result := DeclineSuggestedPostAsync(AChatId, AMessageId, Default(TTgDeclineSuggestedPostOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TryDeclineSuggestedPost(AChatId: Int64; AMessageId: Int64;
  const AOptions: TTgDeclineSuggestedPostOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    DeclineSuggestedPost(AChatId, AMessageId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryDeclineSuggestedPost(AChatId: Int64; AMessageId: Int64;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryDeclineSuggestedPost(AChatId, AMessageId, Default(TTgDeclineSuggestedPostOptions),
  AError);
end;

function TTgApi.BuildDeleteMessageParams(const AChatId: TTgChatId; AMessageId: Int64): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('message_id', AMessageId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecDeleteMessage(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('deleteMessage', AParams);
  Result := TTgDto.ResultBool(LValue, 'deleteMessage');
end;

function TTgApi.DeleteMessage(const AChatId: TTgChatId; AMessageId: Int64): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildDeleteMessageParams(AChatId, AMessageId);
  try
    Result := ExecDeleteMessage(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.DeleteMessageAsync(const AChatId: TTgChatId; AMessageId: Int64;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecDeleteMessage;
  Result := RunAsyncCall<Boolean>(BuildDeleteMessageParams(AChatId, AMessageId), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.TryDeleteMessage(const AChatId: TTgChatId; AMessageId: Int64;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    DeleteMessage(AChatId, AMessageId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildDeleteMessagesParams(const AChatId: TTgChatId;
  const AMessageIds: TArray<Int64>): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.AddInt64s('message_ids', AMessageIds);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecDeleteMessages(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('deleteMessages', AParams);
  Result := TTgDto.ResultBool(LValue, 'deleteMessages');
end;

function TTgApi.DeleteMessages(const AChatId: TTgChatId; const AMessageIds: TArray<Int64>): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildDeleteMessagesParams(AChatId, AMessageIds);
  try
    Result := ExecDeleteMessages(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.DeleteMessagesAsync(const AChatId: TTgChatId; const AMessageIds: TArray<Int64>;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecDeleteMessages;
  Result := RunAsyncCall<Boolean>(BuildDeleteMessagesParams(AChatId, AMessageIds), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.TryDeleteMessages(const AChatId: TTgChatId; const AMessageIds: TArray<Int64>;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    DeleteMessages(AChatId, AMessageIds);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildDeleteEphemeralMessageParams(const AChatId: TTgChatId; AReceiverUserId: Int64;
  AEphemeralMessageId: Int64): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('receiver_user_id', AReceiverUserId);
    Result.Add('ephemeral_message_id', AEphemeralMessageId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecDeleteEphemeralMessage(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('deleteEphemeralMessage', AParams);
  Result := TTgDto.ResultBool(LValue, 'deleteEphemeralMessage');
end;

function TTgApi.DeleteEphemeralMessage(const AChatId: TTgChatId; AReceiverUserId: Int64;
  AEphemeralMessageId: Int64): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildDeleteEphemeralMessageParams(AChatId, AReceiverUserId, AEphemeralMessageId);
  try
    Result := ExecDeleteEphemeralMessage(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.DeleteEphemeralMessageAsync(const AChatId: TTgChatId; AReceiverUserId: Int64;
  AEphemeralMessageId: Int64; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecDeleteEphemeralMessage;
  Result := RunAsyncCall<Boolean>(BuildDeleteEphemeralMessageParams(AChatId, AReceiverUserId, AEphemeralMessageId), LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryDeleteEphemeralMessage(const AChatId: TTgChatId; AReceiverUserId: Int64;
  AEphemeralMessageId: Int64; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    DeleteEphemeralMessage(AChatId, AReceiverUserId, AEphemeralMessageId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildDeleteMessageReactionParams(const AChatId: TTgChatId; AMessageId: Int64;
  const AOptions: TTgDeleteMessageReactionOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('message_id', AMessageId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecDeleteMessageReaction(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('deleteMessageReaction', AParams);
  Result := TTgDto.ResultBool(LValue, 'deleteMessageReaction');
end;

function TTgApi.DeleteMessageReaction(const AChatId: TTgChatId; AMessageId: Int64;
  const AOptions: TTgDeleteMessageReactionOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildDeleteMessageReactionParams(AChatId, AMessageId, AOptions);
  try
    Result := ExecDeleteMessageReaction(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.DeleteMessageReaction(const AChatId: TTgChatId; AMessageId: Int64): Boolean;
begin
  Result := DeleteMessageReaction(AChatId, AMessageId, Default(TTgDeleteMessageReactionOptions));
end;

function TTgApi.DeleteMessageReactionAsync(const AChatId: TTgChatId; AMessageId: Int64;
  const AOptions: TTgDeleteMessageReactionOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecDeleteMessageReaction;
  Result := RunAsyncCall<Boolean>(BuildDeleteMessageReactionParams(AChatId, AMessageId, AOptions),
    LExec, AOnSuccess, AOnError);
end;

function TTgApi.DeleteMessageReactionAsync(const AChatId: TTgChatId; AMessageId: Int64;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
begin
  Result := DeleteMessageReactionAsync(AChatId, AMessageId,
  Default(TTgDeleteMessageReactionOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryDeleteMessageReaction(const AChatId: TTgChatId; AMessageId: Int64;
  const AOptions: TTgDeleteMessageReactionOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    DeleteMessageReaction(AChatId, AMessageId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryDeleteMessageReaction(const AChatId: TTgChatId; AMessageId: Int64;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryDeleteMessageReaction(AChatId, AMessageId, Default(TTgDeleteMessageReactionOptions),
  AError);
end;

function TTgApi.BuildDeleteAllMessageReactionsParams(const AChatId: TTgChatId;
  const AOptions: TTgDeleteAllMessageReactionsOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecDeleteAllMessageReactions(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('deleteAllMessageReactions', AParams);
  Result := TTgDto.ResultBool(LValue, 'deleteAllMessageReactions');
end;

function TTgApi.DeleteAllMessageReactions(const AChatId: TTgChatId;
  const AOptions: TTgDeleteAllMessageReactionsOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildDeleteAllMessageReactionsParams(AChatId, AOptions);
  try
    Result := ExecDeleteAllMessageReactions(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.DeleteAllMessageReactions(const AChatId: TTgChatId): Boolean;
begin
  Result := DeleteAllMessageReactions(AChatId, Default(TTgDeleteAllMessageReactionsOptions));
end;

function TTgApi.DeleteAllMessageReactionsAsync(const AChatId: TTgChatId;
  const AOptions: TTgDeleteAllMessageReactionsOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecDeleteAllMessageReactions;
  Result := RunAsyncCall<Boolean>(BuildDeleteAllMessageReactionsParams(AChatId, AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.DeleteAllMessageReactionsAsync(const AChatId: TTgChatId;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
begin
  Result := DeleteAllMessageReactionsAsync(AChatId, Default(TTgDeleteAllMessageReactionsOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TryDeleteAllMessageReactions(const AChatId: TTgChatId;
  const AOptions: TTgDeleteAllMessageReactionsOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    DeleteAllMessageReactions(AChatId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryDeleteAllMessageReactions(const AChatId: TTgChatId;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryDeleteAllMessageReactions(AChatId, Default(TTgDeleteAllMessageReactionsOptions),
  AError);
end;

function TTgApi.BuildSendStickerParams(const AChatId: TTgChatId; const ASticker: TTgInputFile;
  const AOptions: TTgSendStickerOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.AddFile('sticker', ASticker);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSendSticker(AParams: TTgParams): ITgMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('sendSticker', AParams);
  Result := TTgDto.ResultObject<ITgMessage>(LValue, 'sendSticker', TgMakeMessage);
end;

function TTgApi.SendSticker(const AChatId: TTgChatId; const ASticker: TTgInputFile;
  const AOptions: TTgSendStickerOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildSendStickerParams(AChatId, ASticker, AOptions);
  try
    Result := ExecSendSticker(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SendSticker(const AChatId: TTgChatId; const ASticker: TTgInputFile): ITgMessage;
begin
  Result := SendSticker(AChatId, ASticker, Default(TTgSendStickerOptions));
end;

function TTgApi.SendStickerAsync(const AChatId: TTgChatId; const ASticker: TTgInputFile;
  const AOptions: TTgSendStickerOptions; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecSendSticker;
  Result := RunAsyncCall<ITgMessage>(BuildSendStickerParams(AChatId, ASticker, AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.SendStickerAsync(const AChatId: TTgChatId; const ASticker: TTgInputFile;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
begin
  Result := SendStickerAsync(AChatId, ASticker, Default(TTgSendStickerOptions), AOnSuccess,
  AOnError);
end;

function TTgApi.TrySendSticker(const AChatId: TTgChatId; const ASticker: TTgInputFile;
  const AOptions: TTgSendStickerOptions; out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := SendSticker(AChatId, ASticker, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySendSticker(const AChatId: TTgChatId; const ASticker: TTgInputFile;
  out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySendSticker(AChatId, ASticker, Default(TTgSendStickerOptions), AResult, AError);
end;

function TTgApi.BuildGetStickerSetParams(const AName: string): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('name', AName);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecGetStickerSet(AParams: TTgParams): ITgStickerSet;
var
  LValue: TJSONValue;
begin
  LValue := Call('getStickerSet', AParams);
  Result := TTgDto.ResultObject<ITgStickerSet>(LValue, 'getStickerSet', TgMakeStickerSet);
end;

function TTgApi.GetStickerSet(const AName: string): ITgStickerSet;
var
  LParams: TTgParams;
begin
  LParams := BuildGetStickerSetParams(AName);
  try
    Result := ExecGetStickerSet(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.GetStickerSetAsync(const AName: string; const AOnSuccess: TProc<ITgStickerSet>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgStickerSet>;
begin
  LExec := ExecGetStickerSet;
  Result := RunAsyncCall<ITgStickerSet>(BuildGetStickerSetParams(AName), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.TryGetStickerSet(const AName: string; out AResult: ITgStickerSet;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgStickerSet);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetStickerSet(AName);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildGetCustomEmojiStickersParams(const ACustomEmojiIds: TArray<string>): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddStrings('custom_emoji_ids', ACustomEmojiIds);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecGetCustomEmojiStickers(AParams: TTgParams): TArray<ITgSticker>;
var
  LValue: TJSONValue;
begin
  LValue := Call('getCustomEmojiStickers', AParams);
  Result := TTgDto.ResultArray<ITgSticker>(LValue, 'getCustomEmojiStickers', TgMakeSticker);
end;

function TTgApi.GetCustomEmojiStickers(const ACustomEmojiIds: TArray<string>): TArray<ITgSticker>;
var
  LParams: TTgParams;
begin
  LParams := BuildGetCustomEmojiStickersParams(ACustomEmojiIds);
  try
    Result := ExecGetCustomEmojiStickers(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.GetCustomEmojiStickersAsync(const ACustomEmojiIds: TArray<string>;
  const AOnSuccess: TProc<TArray<ITgSticker>>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<TArray<ITgSticker>>;
begin
  LExec := ExecGetCustomEmojiStickers;
  Result := RunAsyncCall<TArray<ITgSticker>>(BuildGetCustomEmojiStickersParams(ACustomEmojiIds),
    LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryGetCustomEmojiStickers(const ACustomEmojiIds: TArray<string>;
  out AResult: TArray<ITgSticker>; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(TArray<ITgSticker>);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetCustomEmojiStickers(ACustomEmojiIds);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildUploadStickerFileParams(AUserId: Int64; const ASticker: TTgInputFile;
  const AStickerFormat: string): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('user_id', AUserId);
    Result.AddFile('sticker', ASticker);
    Result.Add('sticker_format', AStickerFormat);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecUploadStickerFile(AParams: TTgParams): ITgFile;
var
  LValue: TJSONValue;
begin
  LValue := Call('uploadStickerFile', AParams);
  Result := TTgDto.ResultObject<ITgFile>(LValue, 'uploadStickerFile', TgMakeFile);
end;

function TTgApi.UploadStickerFile(AUserId: Int64; const ASticker: TTgInputFile;
  const AStickerFormat: string): ITgFile;
var
  LParams: TTgParams;
begin
  LParams := BuildUploadStickerFileParams(AUserId, ASticker, AStickerFormat);
  try
    Result := ExecUploadStickerFile(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.UploadStickerFileAsync(AUserId: Int64; const ASticker: TTgInputFile;
  const AStickerFormat: string; const AOnSuccess: TProc<ITgFile>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgFile>;
begin
  LExec := ExecUploadStickerFile;
  Result := RunAsyncCall<ITgFile>(BuildUploadStickerFileParams(AUserId, ASticker, AStickerFormat),
    LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryUploadStickerFile(AUserId: Int64; const ASticker: TTgInputFile;
  const AStickerFormat: string; out AResult: ITgFile; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgFile);
  AError := TTgErrorInfo.Empty;
  try
    AResult := UploadStickerFile(AUserId, ASticker, AStickerFormat);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildCreateNewStickerSetParams(AUserId: Int64; const AName: string;
  const ATitle: string; const AStickers: array of ITgInputSticker;
  const AOptions: TTgCreateNewStickerSetOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('user_id', AUserId);
    Result.Add('name', AName);
    Result.Add('title', ATitle);
    Result.AddJson('stickers',
      TTgDto.SerializeArray(TTgDto.ToIntf<ITgInputSticker>(AStickers), Result, 'stickers'));
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecCreateNewStickerSet(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('createNewStickerSet', AParams);
  Result := TTgDto.ResultBool(LValue, 'createNewStickerSet');
end;

function TTgApi.CreateNewStickerSet(AUserId: Int64; const AName: string; const ATitle: string;
  const AStickers: array of ITgInputSticker;
  const AOptions: TTgCreateNewStickerSetOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildCreateNewStickerSetParams(AUserId, AName, ATitle, AStickers, AOptions);
  try
    Result := ExecCreateNewStickerSet(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.CreateNewStickerSet(AUserId: Int64; const AName: string; const ATitle: string;
  const AStickers: array of ITgInputSticker): Boolean;
begin
  Result := CreateNewStickerSet(AUserId, AName, ATitle, AStickers,
  Default(TTgCreateNewStickerSetOptions));
end;

function TTgApi.CreateNewStickerSetAsync(AUserId: Int64; const AName: string; const ATitle: string;
  const AStickers: array of ITgInputSticker; const AOptions: TTgCreateNewStickerSetOptions;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecCreateNewStickerSet;
  Result := RunAsyncCall<Boolean>(BuildCreateNewStickerSetParams(AUserId, AName, ATitle, AStickers, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.CreateNewStickerSetAsync(AUserId: Int64; const AName: string; const ATitle: string;
  const AStickers: array of ITgInputSticker; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := CreateNewStickerSetAsync(AUserId, AName, ATitle, AStickers,
  Default(TTgCreateNewStickerSetOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryCreateNewStickerSet(AUserId: Int64; const AName: string; const ATitle: string;
  const AStickers: array of ITgInputSticker; const AOptions: TTgCreateNewStickerSetOptions;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    CreateNewStickerSet(AUserId, AName, ATitle, AStickers, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryCreateNewStickerSet(AUserId: Int64; const AName: string; const ATitle: string;
  const AStickers: array of ITgInputSticker; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryCreateNewStickerSet(AUserId, AName, ATitle, AStickers,
  Default(TTgCreateNewStickerSetOptions), AError);
end;

function TTgApi.BuildAddStickerToSetParams(AUserId: Int64; const AName: string;
  const ASticker: ITgInputSticker): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('user_id', AUserId);
    Result.Add('name', AName);
    Result.AddJson('sticker', TTgDto.Serialize(ASticker, Result));
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecAddStickerToSet(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('addStickerToSet', AParams);
  Result := TTgDto.ResultBool(LValue, 'addStickerToSet');
end;

function TTgApi.AddStickerToSet(AUserId: Int64; const AName: string;
  const ASticker: ITgInputSticker): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildAddStickerToSetParams(AUserId, AName, ASticker);
  try
    Result := ExecAddStickerToSet(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.AddStickerToSetAsync(AUserId: Int64; const AName: string;
  const ASticker: ITgInputSticker; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecAddStickerToSet;
  Result := RunAsyncCall<Boolean>(BuildAddStickerToSetParams(AUserId, AName, ASticker), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.TryAddStickerToSet(AUserId: Int64; const AName: string;
  const ASticker: ITgInputSticker; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    AddStickerToSet(AUserId, AName, ASticker);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildSetStickerPositionInSetParams(const ASticker: string;
  APosition: Integer): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('sticker', ASticker);
    Result.Add('position', APosition);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetStickerPositionInSet(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setStickerPositionInSet', AParams);
  Result := TTgDto.ResultBool(LValue, 'setStickerPositionInSet');
end;

function TTgApi.SetStickerPositionInSet(const ASticker: string; APosition: Integer): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetStickerPositionInSetParams(ASticker, APosition);
  try
    Result := ExecSetStickerPositionInSet(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetStickerPositionInSetAsync(const ASticker: string; APosition: Integer;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetStickerPositionInSet;
  Result := RunAsyncCall<Boolean>(BuildSetStickerPositionInSetParams(ASticker, APosition), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.TrySetStickerPositionInSet(const ASticker: string; APosition: Integer;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetStickerPositionInSet(ASticker, APosition);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildDeleteStickerFromSetParams(const ASticker: string): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('sticker', ASticker);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecDeleteStickerFromSet(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('deleteStickerFromSet', AParams);
  Result := TTgDto.ResultBool(LValue, 'deleteStickerFromSet');
end;

function TTgApi.DeleteStickerFromSet(const ASticker: string): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildDeleteStickerFromSetParams(ASticker);
  try
    Result := ExecDeleteStickerFromSet(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.DeleteStickerFromSetAsync(const ASticker: string; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecDeleteStickerFromSet;
  Result := RunAsyncCall<Boolean>(BuildDeleteStickerFromSetParams(ASticker), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.TryDeleteStickerFromSet(const ASticker: string; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    DeleteStickerFromSet(ASticker);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildReplaceStickerInSetParams(AUserId: Int64; const AName: string;
  const AOldSticker: string; const ASticker: ITgInputSticker): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('user_id', AUserId);
    Result.Add('name', AName);
    Result.Add('old_sticker', AOldSticker);
    Result.AddJson('sticker', TTgDto.Serialize(ASticker, Result));
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecReplaceStickerInSet(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('replaceStickerInSet', AParams);
  Result := TTgDto.ResultBool(LValue, 'replaceStickerInSet');
end;

function TTgApi.ReplaceStickerInSet(AUserId: Int64; const AName: string; const AOldSticker: string;
  const ASticker: ITgInputSticker): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildReplaceStickerInSetParams(AUserId, AName, AOldSticker, ASticker);
  try
    Result := ExecReplaceStickerInSet(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.ReplaceStickerInSetAsync(AUserId: Int64; const AName: string;
  const AOldSticker: string; const ASticker: ITgInputSticker; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecReplaceStickerInSet;
  Result := RunAsyncCall<Boolean>(BuildReplaceStickerInSetParams(AUserId, AName, AOldSticker, ASticker), LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryReplaceStickerInSet(AUserId: Int64; const AName: string;
  const AOldSticker: string; const ASticker: ITgInputSticker; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    ReplaceStickerInSet(AUserId, AName, AOldSticker, ASticker);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildSetStickerEmojiListParams(const ASticker: string;
  const AEmojiList: TArray<string>): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('sticker', ASticker);
    Result.AddStrings('emoji_list', AEmojiList);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetStickerEmojiList(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setStickerEmojiList', AParams);
  Result := TTgDto.ResultBool(LValue, 'setStickerEmojiList');
end;

function TTgApi.SetStickerEmojiList(const ASticker: string;
  const AEmojiList: TArray<string>): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetStickerEmojiListParams(ASticker, AEmojiList);
  try
    Result := ExecSetStickerEmojiList(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetStickerEmojiListAsync(const ASticker: string; const AEmojiList: TArray<string>;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetStickerEmojiList;
  Result := RunAsyncCall<Boolean>(BuildSetStickerEmojiListParams(ASticker, AEmojiList), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.TrySetStickerEmojiList(const ASticker: string; const AEmojiList: TArray<string>;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetStickerEmojiList(ASticker, AEmojiList);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildSetStickerKeywordsParams(const ASticker: string;
  const AOptions: TTgSetStickerKeywordsOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('sticker', ASticker);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetStickerKeywords(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setStickerKeywords', AParams);
  Result := TTgDto.ResultBool(LValue, 'setStickerKeywords');
end;

function TTgApi.SetStickerKeywords(const ASticker: string;
  const AOptions: TTgSetStickerKeywordsOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetStickerKeywordsParams(ASticker, AOptions);
  try
    Result := ExecSetStickerKeywords(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetStickerKeywords(const ASticker: string): Boolean;
begin
  Result := SetStickerKeywords(ASticker, Default(TTgSetStickerKeywordsOptions));
end;

function TTgApi.SetStickerKeywordsAsync(const ASticker: string;
  const AOptions: TTgSetStickerKeywordsOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetStickerKeywords;
  Result := RunAsyncCall<Boolean>(BuildSetStickerKeywordsParams(ASticker, AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.SetStickerKeywordsAsync(const ASticker: string; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := SetStickerKeywordsAsync(ASticker, Default(TTgSetStickerKeywordsOptions), AOnSuccess,
  AOnError);
end;

function TTgApi.TrySetStickerKeywords(const ASticker: string;
  const AOptions: TTgSetStickerKeywordsOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetStickerKeywords(ASticker, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySetStickerKeywords(const ASticker: string; out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySetStickerKeywords(ASticker, Default(TTgSetStickerKeywordsOptions), AError);
end;

function TTgApi.BuildSetStickerMaskPositionParams(const ASticker: string;
  const AOptions: TTgSetStickerMaskPositionOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('sticker', ASticker);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetStickerMaskPosition(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setStickerMaskPosition', AParams);
  Result := TTgDto.ResultBool(LValue, 'setStickerMaskPosition');
end;

function TTgApi.SetStickerMaskPosition(const ASticker: string;
  const AOptions: TTgSetStickerMaskPositionOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetStickerMaskPositionParams(ASticker, AOptions);
  try
    Result := ExecSetStickerMaskPosition(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetStickerMaskPosition(const ASticker: string): Boolean;
begin
  Result := SetStickerMaskPosition(ASticker, Default(TTgSetStickerMaskPositionOptions));
end;

function TTgApi.SetStickerMaskPositionAsync(const ASticker: string;
  const AOptions: TTgSetStickerMaskPositionOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetStickerMaskPosition;
  Result := RunAsyncCall<Boolean>(BuildSetStickerMaskPositionParams(ASticker, AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.SetStickerMaskPositionAsync(const ASticker: string;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
begin
  Result := SetStickerMaskPositionAsync(ASticker, Default(TTgSetStickerMaskPositionOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TrySetStickerMaskPosition(const ASticker: string;
  const AOptions: TTgSetStickerMaskPositionOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetStickerMaskPosition(ASticker, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySetStickerMaskPosition(const ASticker: string;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySetStickerMaskPosition(ASticker, Default(TTgSetStickerMaskPositionOptions), AError);
end;

function TTgApi.BuildSetStickerSetTitleParams(const AName: string; const ATitle: string): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('name', AName);
    Result.Add('title', ATitle);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetStickerSetTitle(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setStickerSetTitle', AParams);
  Result := TTgDto.ResultBool(LValue, 'setStickerSetTitle');
end;

function TTgApi.SetStickerSetTitle(const AName: string; const ATitle: string): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetStickerSetTitleParams(AName, ATitle);
  try
    Result := ExecSetStickerSetTitle(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetStickerSetTitleAsync(const AName: string; const ATitle: string;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetStickerSetTitle;
  Result := RunAsyncCall<Boolean>(BuildSetStickerSetTitleParams(AName, ATitle), LExec, AOnSuccess,
    AOnError);
end;

function TTgApi.TrySetStickerSetTitle(const AName: string; const ATitle: string;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetStickerSetTitle(AName, ATitle);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildSetStickerSetThumbnailParams(const AName: string; AUserId: Int64;
  const AFormat: string; const AOptions: TTgSetStickerSetThumbnailOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('name', AName);
    Result.Add('user_id', AUserId);
    Result.Add('format', AFormat);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetStickerSetThumbnail(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setStickerSetThumbnail', AParams);
  Result := TTgDto.ResultBool(LValue, 'setStickerSetThumbnail');
end;

function TTgApi.SetStickerSetThumbnail(const AName: string; AUserId: Int64; const AFormat: string;
  const AOptions: TTgSetStickerSetThumbnailOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetStickerSetThumbnailParams(AName, AUserId, AFormat, AOptions);
  try
    Result := ExecSetStickerSetThumbnail(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetStickerSetThumbnail(const AName: string; AUserId: Int64;
  const AFormat: string): Boolean;
begin
  Result := SetStickerSetThumbnail(AName, AUserId, AFormat,
  Default(TTgSetStickerSetThumbnailOptions));
end;

function TTgApi.SetStickerSetThumbnailAsync(const AName: string; AUserId: Int64;
  const AFormat: string; const AOptions: TTgSetStickerSetThumbnailOptions;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetStickerSetThumbnail;
  Result := RunAsyncCall<Boolean>(BuildSetStickerSetThumbnailParams(AName, AUserId, AFormat, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.SetStickerSetThumbnailAsync(const AName: string; AUserId: Int64;
  const AFormat: string; const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
begin
  Result := SetStickerSetThumbnailAsync(AName, AUserId, AFormat,
  Default(TTgSetStickerSetThumbnailOptions), AOnSuccess, AOnError);
end;

function TTgApi.TrySetStickerSetThumbnail(const AName: string; AUserId: Int64;
  const AFormat: string; const AOptions: TTgSetStickerSetThumbnailOptions;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetStickerSetThumbnail(AName, AUserId, AFormat, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySetStickerSetThumbnail(const AName: string; AUserId: Int64;
  const AFormat: string; out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySetStickerSetThumbnail(AName, AUserId, AFormat,
  Default(TTgSetStickerSetThumbnailOptions), AError);
end;

function TTgApi.BuildSetCustomEmojiStickerSetThumbnailParams(const AName: string;
  const AOptions: TTgSetCustomEmojiStickerSetThumbnailOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('name', AName);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetCustomEmojiStickerSetThumbnail(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setCustomEmojiStickerSetThumbnail', AParams);
  Result := TTgDto.ResultBool(LValue, 'setCustomEmojiStickerSetThumbnail');
end;

function TTgApi.SetCustomEmojiStickerSetThumbnail(const AName: string;
  const AOptions: TTgSetCustomEmojiStickerSetThumbnailOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetCustomEmojiStickerSetThumbnailParams(AName, AOptions);
  try
    Result := ExecSetCustomEmojiStickerSetThumbnail(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetCustomEmojiStickerSetThumbnail(const AName: string): Boolean;
begin
  Result := SetCustomEmojiStickerSetThumbnail(AName,
  Default(TTgSetCustomEmojiStickerSetThumbnailOptions));
end;

function TTgApi.SetCustomEmojiStickerSetThumbnailAsync(const AName: string;
  const AOptions: TTgSetCustomEmojiStickerSetThumbnailOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetCustomEmojiStickerSetThumbnail;
  Result := RunAsyncCall<Boolean>(BuildSetCustomEmojiStickerSetThumbnailParams(AName, AOptions),
    LExec, AOnSuccess, AOnError);
end;

function TTgApi.SetCustomEmojiStickerSetThumbnailAsync(const AName: string;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
begin
  Result := SetCustomEmojiStickerSetThumbnailAsync(AName,
  Default(TTgSetCustomEmojiStickerSetThumbnailOptions), AOnSuccess, AOnError);
end;

function TTgApi.TrySetCustomEmojiStickerSetThumbnail(const AName: string;
  const AOptions: TTgSetCustomEmojiStickerSetThumbnailOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetCustomEmojiStickerSetThumbnail(AName, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySetCustomEmojiStickerSetThumbnail(const AName: string;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySetCustomEmojiStickerSetThumbnail(AName,
  Default(TTgSetCustomEmojiStickerSetThumbnailOptions), AError);
end;

function TTgApi.BuildDeleteStickerSetParams(const AName: string): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('name', AName);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecDeleteStickerSet(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('deleteStickerSet', AParams);
  Result := TTgDto.ResultBool(LValue, 'deleteStickerSet');
end;

function TTgApi.DeleteStickerSet(const AName: string): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildDeleteStickerSetParams(AName);
  try
    Result := ExecDeleteStickerSet(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.DeleteStickerSetAsync(const AName: string; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecDeleteStickerSet;
  Result := RunAsyncCall<Boolean>(BuildDeleteStickerSetParams(AName), LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryDeleteStickerSet(const AName: string; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    DeleteStickerSet(AName);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildSendRichMessageParams(const AChatId: TTgChatId;
  const ARichMessage: ITgInputRichMessage; const AOptions: TTgSendRichMessageOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.AddJson('rich_message', TTgDto.Serialize(ARichMessage, Result));
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSendRichMessage(AParams: TTgParams): ITgMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('sendRichMessage', AParams);
  Result := TTgDto.ResultObject<ITgMessage>(LValue, 'sendRichMessage', TgMakeMessage);
end;

function TTgApi.SendRichMessage(const AChatId: TTgChatId; const ARichMessage: ITgInputRichMessage;
  const AOptions: TTgSendRichMessageOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildSendRichMessageParams(AChatId, ARichMessage, AOptions);
  try
    Result := ExecSendRichMessage(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SendRichMessage(const AChatId: TTgChatId;
  const ARichMessage: ITgInputRichMessage): ITgMessage;
begin
  Result := SendRichMessage(AChatId, ARichMessage, Default(TTgSendRichMessageOptions));
end;

function TTgApi.SendRichMessageAsync(const AChatId: TTgChatId;
  const ARichMessage: ITgInputRichMessage; const AOptions: TTgSendRichMessageOptions;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecSendRichMessage;
  Result := RunAsyncCall<ITgMessage>(BuildSendRichMessageParams(AChatId, ARichMessage, AOptions),
    LExec, AOnSuccess, AOnError);
end;

function TTgApi.SendRichMessageAsync(const AChatId: TTgChatId;
  const ARichMessage: ITgInputRichMessage; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := SendRichMessageAsync(AChatId, ARichMessage, Default(TTgSendRichMessageOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TrySendRichMessage(const AChatId: TTgChatId;
  const ARichMessage: ITgInputRichMessage; const AOptions: TTgSendRichMessageOptions;
  out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := SendRichMessage(AChatId, ARichMessage, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySendRichMessage(const AChatId: TTgChatId;
  const ARichMessage: ITgInputRichMessage; out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySendRichMessage(AChatId, ARichMessage, Default(TTgSendRichMessageOptions), AResult,
  AError);
end;

function TTgApi.BuildSendRichMessageDraftParams(AChatId: Int64; ADraftId: Int64;
  const ARichMessage: ITgInputRichMessage;
  const AOptions: TTgSendRichMessageDraftOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('chat_id', AChatId);
    Result.Add('draft_id', ADraftId);
    Result.AddJson('rich_message', TTgDto.Serialize(ARichMessage, Result));
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSendRichMessageDraft(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('sendRichMessageDraft', AParams);
  Result := TTgDto.ResultBool(LValue, 'sendRichMessageDraft');
end;

function TTgApi.SendRichMessageDraft(AChatId: Int64; ADraftId: Int64;
  const ARichMessage: ITgInputRichMessage; const AOptions: TTgSendRichMessageDraftOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSendRichMessageDraftParams(AChatId, ADraftId, ARichMessage, AOptions);
  try
    Result := ExecSendRichMessageDraft(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SendRichMessageDraft(AChatId: Int64; ADraftId: Int64;
  const ARichMessage: ITgInputRichMessage): Boolean;
begin
  Result := SendRichMessageDraft(AChatId, ADraftId, ARichMessage,
  Default(TTgSendRichMessageDraftOptions));
end;

function TTgApi.SendRichMessageDraftAsync(AChatId: Int64; ADraftId: Int64;
  const ARichMessage: ITgInputRichMessage; const AOptions: TTgSendRichMessageDraftOptions;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSendRichMessageDraft;
  Result := RunAsyncCall<Boolean>(BuildSendRichMessageDraftParams(AChatId, ADraftId, ARichMessage, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.SendRichMessageDraftAsync(AChatId: Int64; ADraftId: Int64;
  const ARichMessage: ITgInputRichMessage; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := SendRichMessageDraftAsync(AChatId, ADraftId, ARichMessage,
  Default(TTgSendRichMessageDraftOptions), AOnSuccess, AOnError);
end;

function TTgApi.TrySendRichMessageDraft(AChatId: Int64; ADraftId: Int64;
  const ARichMessage: ITgInputRichMessage; const AOptions: TTgSendRichMessageDraftOptions;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SendRichMessageDraft(AChatId, ADraftId, ARichMessage, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySendRichMessageDraft(AChatId: Int64; ADraftId: Int64;
  const ARichMessage: ITgInputRichMessage; out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySendRichMessageDraft(AChatId, ADraftId, ARichMessage,
  Default(TTgSendRichMessageDraftOptions), AError);
end;

function TTgApi.BuildAnswerInlineQueryParams(const AInlineQueryId: string;
  const AResults: array of TTgInlineQueryResult;
  const AOptions: TTgAnswerInlineQueryOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('inline_query_id', AInlineQueryId);
    Result.AddJson('results',
      TTgDto.SerializeArray(TTgInlineQueryResult.Values(AResults), Result, 'results'));
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecAnswerInlineQuery(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('answerInlineQuery', AParams);
  Result := TTgDto.ResultBool(LValue, 'answerInlineQuery');
end;

function TTgApi.AnswerInlineQuery(const AInlineQueryId: string;
  const AResults: array of TTgInlineQueryResult;
  const AOptions: TTgAnswerInlineQueryOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildAnswerInlineQueryParams(AInlineQueryId, AResults, AOptions);
  try
    Result := ExecAnswerInlineQuery(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.AnswerInlineQuery(const AInlineQueryId: string;
  const AResults: array of TTgInlineQueryResult): Boolean;
begin
  Result := AnswerInlineQuery(AInlineQueryId, AResults, Default(TTgAnswerInlineQueryOptions));
end;

function TTgApi.AnswerInlineQueryAsync(const AInlineQueryId: string;
  const AResults: array of TTgInlineQueryResult; const AOptions: TTgAnswerInlineQueryOptions;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecAnswerInlineQuery;
  Result := RunAsyncCall<Boolean>(BuildAnswerInlineQueryParams(AInlineQueryId, AResults, AOptions),
    LExec, AOnSuccess, AOnError);
end;

function TTgApi.AnswerInlineQueryAsync(const AInlineQueryId: string;
  const AResults: array of TTgInlineQueryResult; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := AnswerInlineQueryAsync(AInlineQueryId, AResults, Default(TTgAnswerInlineQueryOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TryAnswerInlineQuery(const AInlineQueryId: string;
  const AResults: array of TTgInlineQueryResult; const AOptions: TTgAnswerInlineQueryOptions;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    AnswerInlineQuery(AInlineQueryId, AResults, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryAnswerInlineQuery(const AInlineQueryId: string;
  const AResults: array of TTgInlineQueryResult; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryAnswerInlineQuery(AInlineQueryId, AResults, Default(TTgAnswerInlineQueryOptions),
  AError);
end;

function TTgApi.BuildSendInvoiceParams(const AChatId: TTgChatId; const ATitle: string;
  const ADescription: string; const APayload: string; const ACurrency: string;
  const APrices: array of ITgLabeledPrice; const AOptions: TTgSendInvoiceOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('title', ATitle);
    Result.Add('description', ADescription);
    Result.Add('payload', APayload);
    Result.Add('currency', ACurrency);
    Result.AddJson('prices',
      TTgDto.SerializeArray(TTgDto.ToIntf<ITgLabeledPrice>(APrices), Result, 'prices'));
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSendInvoice(AParams: TTgParams): ITgMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('sendInvoice', AParams);
  Result := TTgDto.ResultObject<ITgMessage>(LValue, 'sendInvoice', TgMakeMessage);
end;

function TTgApi.SendInvoice(const AChatId: TTgChatId; const ATitle: string;
  const ADescription: string; const APayload: string; const ACurrency: string;
  const APrices: array of ITgLabeledPrice; const AOptions: TTgSendInvoiceOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildSendInvoiceParams(AChatId, ATitle, ADescription, APayload, ACurrency, APrices,
    AOptions);
  try
    Result := ExecSendInvoice(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SendInvoice(const AChatId: TTgChatId; const ATitle: string;
  const ADescription: string; const APayload: string; const ACurrency: string;
  const APrices: array of ITgLabeledPrice): ITgMessage;
begin
  Result := SendInvoice(AChatId, ATitle, ADescription, APayload, ACurrency, APrices,
  Default(TTgSendInvoiceOptions));
end;

function TTgApi.SendInvoiceAsync(const AChatId: TTgChatId; const ATitle: string;
  const ADescription: string; const APayload: string; const ACurrency: string;
  const APrices: array of ITgLabeledPrice; const AOptions: TTgSendInvoiceOptions;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecSendInvoice;
  Result := RunAsyncCall<ITgMessage>(BuildSendInvoiceParams(AChatId, ATitle, ADescription, APayload, ACurrency, APrices, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.SendInvoiceAsync(const AChatId: TTgChatId; const ATitle: string;
  const ADescription: string; const APayload: string; const ACurrency: string;
  const APrices: array of ITgLabeledPrice; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := SendInvoiceAsync(AChatId, ATitle, ADescription, APayload, ACurrency, APrices,
  Default(TTgSendInvoiceOptions), AOnSuccess, AOnError);
end;

function TTgApi.TrySendInvoice(const AChatId: TTgChatId; const ATitle: string;
  const ADescription: string; const APayload: string; const ACurrency: string;
  const APrices: array of ITgLabeledPrice; const AOptions: TTgSendInvoiceOptions;
  out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := SendInvoice(AChatId, ATitle, ADescription, APayload, ACurrency, APrices, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySendInvoice(const AChatId: TTgChatId; const ATitle: string;
  const ADescription: string; const APayload: string; const ACurrency: string;
  const APrices: array of ITgLabeledPrice; out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySendInvoice(AChatId, ATitle, ADescription, APayload, ACurrency, APrices,
  Default(TTgSendInvoiceOptions), AResult, AError);
end;

function TTgApi.BuildCreateInvoiceLinkParams(const ATitle: string; const ADescription: string;
  const APayload: string; const ACurrency: string; const APrices: array of ITgLabeledPrice;
  const AOptions: TTgCreateInvoiceLinkOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('title', ATitle);
    Result.Add('description', ADescription);
    Result.Add('payload', APayload);
    Result.Add('currency', ACurrency);
    Result.AddJson('prices',
      TTgDto.SerializeArray(TTgDto.ToIntf<ITgLabeledPrice>(APrices), Result, 'prices'));
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecCreateInvoiceLink(AParams: TTgParams): string;
var
  LValue: TJSONValue;
begin
  LValue := Call('createInvoiceLink', AParams);
  Result := TTgDto.ResultStr(LValue, 'createInvoiceLink');
end;

function TTgApi.CreateInvoiceLink(const ATitle: string; const ADescription: string;
  const APayload: string; const ACurrency: string; const APrices: array of ITgLabeledPrice;
  const AOptions: TTgCreateInvoiceLinkOptions): string;
var
  LParams: TTgParams;
begin
  LParams := BuildCreateInvoiceLinkParams(ATitle, ADescription, APayload, ACurrency, APrices,
    AOptions);
  try
    Result := ExecCreateInvoiceLink(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.CreateInvoiceLink(const ATitle: string; const ADescription: string;
  const APayload: string; const ACurrency: string; const APrices: array of ITgLabeledPrice): string;
begin
  Result := CreateInvoiceLink(ATitle, ADescription, APayload, ACurrency, APrices,
  Default(TTgCreateInvoiceLinkOptions));
end;

function TTgApi.CreateInvoiceLinkAsync(const ATitle: string; const ADescription: string;
  const APayload: string; const ACurrency: string; const APrices: array of ITgLabeledPrice;
  const AOptions: TTgCreateInvoiceLinkOptions; const AOnSuccess: TProc<string>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<string>;
begin
  LExec := ExecCreateInvoiceLink;
  Result := RunAsyncCall<string>(BuildCreateInvoiceLinkParams(ATitle, ADescription, APayload, ACurrency, APrices, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.CreateInvoiceLinkAsync(const ATitle: string; const ADescription: string;
  const APayload: string; const ACurrency: string; const APrices: array of ITgLabeledPrice;
  const AOnSuccess: TProc<string>; const AOnError: TProc<Exception>): ITask;
begin
  Result := CreateInvoiceLinkAsync(ATitle, ADescription, APayload, ACurrency, APrices,
  Default(TTgCreateInvoiceLinkOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryCreateInvoiceLink(const ATitle: string; const ADescription: string;
  const APayload: string; const ACurrency: string; const APrices: array of ITgLabeledPrice;
  const AOptions: TTgCreateInvoiceLinkOptions; out AResult: string;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(string);
  AError := TTgErrorInfo.Empty;
  try
    AResult := CreateInvoiceLink(ATitle, ADescription, APayload, ACurrency, APrices, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryCreateInvoiceLink(const ATitle: string; const ADescription: string;
  const APayload: string; const ACurrency: string; const APrices: array of ITgLabeledPrice;
  out AResult: string; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryCreateInvoiceLink(ATitle, ADescription, APayload, ACurrency, APrices,
  Default(TTgCreateInvoiceLinkOptions), AResult, AError);
end;

function TTgApi.BuildAnswerShippingQueryParams(const AShippingQueryId: string; AOk: Boolean;
  const AOptions: TTgAnswerShippingQueryOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('shipping_query_id', AShippingQueryId);
    Result.Add('ok', AOk);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecAnswerShippingQuery(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('answerShippingQuery', AParams);
  Result := TTgDto.ResultBool(LValue, 'answerShippingQuery');
end;

function TTgApi.AnswerShippingQuery(const AShippingQueryId: string; AOk: Boolean;
  const AOptions: TTgAnswerShippingQueryOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildAnswerShippingQueryParams(AShippingQueryId, AOk, AOptions);
  try
    Result := ExecAnswerShippingQuery(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.AnswerShippingQuery(const AShippingQueryId: string; AOk: Boolean): Boolean;
begin
  Result := AnswerShippingQuery(AShippingQueryId, AOk, Default(TTgAnswerShippingQueryOptions));
end;

function TTgApi.AnswerShippingQueryAsync(const AShippingQueryId: string; AOk: Boolean;
  const AOptions: TTgAnswerShippingQueryOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecAnswerShippingQuery;
  Result := RunAsyncCall<Boolean>(BuildAnswerShippingQueryParams(AShippingQueryId, AOk, AOptions),
    LExec, AOnSuccess, AOnError);
end;

function TTgApi.AnswerShippingQueryAsync(const AShippingQueryId: string; AOk: Boolean;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
begin
  Result := AnswerShippingQueryAsync(AShippingQueryId, AOk, Default(TTgAnswerShippingQueryOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TryAnswerShippingQuery(const AShippingQueryId: string; AOk: Boolean;
  const AOptions: TTgAnswerShippingQueryOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    AnswerShippingQuery(AShippingQueryId, AOk, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryAnswerShippingQuery(const AShippingQueryId: string; AOk: Boolean;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryAnswerShippingQuery(AShippingQueryId, AOk, Default(TTgAnswerShippingQueryOptions),
  AError);
end;

function TTgApi.BuildAnswerPreCheckoutQueryParams(const APreCheckoutQueryId: string; AOk: Boolean;
  const AOptions: TTgAnswerPreCheckoutQueryOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('pre_checkout_query_id', APreCheckoutQueryId);
    Result.Add('ok', AOk);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecAnswerPreCheckoutQuery(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('answerPreCheckoutQuery', AParams);
  Result := TTgDto.ResultBool(LValue, 'answerPreCheckoutQuery');
end;

function TTgApi.AnswerPreCheckoutQuery(const APreCheckoutQueryId: string; AOk: Boolean;
  const AOptions: TTgAnswerPreCheckoutQueryOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildAnswerPreCheckoutQueryParams(APreCheckoutQueryId, AOk, AOptions);
  try
    Result := ExecAnswerPreCheckoutQuery(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.AnswerPreCheckoutQuery(const APreCheckoutQueryId: string; AOk: Boolean): Boolean;
begin
  Result := AnswerPreCheckoutQuery(APreCheckoutQueryId, AOk,
  Default(TTgAnswerPreCheckoutQueryOptions));
end;

function TTgApi.AnswerPreCheckoutQueryAsync(const APreCheckoutQueryId: string; AOk: Boolean;
  const AOptions: TTgAnswerPreCheckoutQueryOptions; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecAnswerPreCheckoutQuery;
  Result := RunAsyncCall<Boolean>(BuildAnswerPreCheckoutQueryParams(APreCheckoutQueryId, AOk, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.AnswerPreCheckoutQueryAsync(const APreCheckoutQueryId: string; AOk: Boolean;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
begin
  Result := AnswerPreCheckoutQueryAsync(APreCheckoutQueryId, AOk,
  Default(TTgAnswerPreCheckoutQueryOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryAnswerPreCheckoutQuery(const APreCheckoutQueryId: string; AOk: Boolean;
  const AOptions: TTgAnswerPreCheckoutQueryOptions; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    AnswerPreCheckoutQuery(APreCheckoutQueryId, AOk, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryAnswerPreCheckoutQuery(const APreCheckoutQueryId: string; AOk: Boolean;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryAnswerPreCheckoutQuery(APreCheckoutQueryId, AOk,
  Default(TTgAnswerPreCheckoutQueryOptions), AError);
end;

function TTgApi.ExecGetMyStarBalance(AParams: TTgParams): ITgStarAmount;
var
  LValue: TJSONValue;
begin
  LValue := Call('getMyStarBalance', AParams);
  Result := TTgDto.ResultObject<ITgStarAmount>(LValue, 'getMyStarBalance', TgMakeStarAmount);
end;

function TTgApi.GetMyStarBalance: ITgStarAmount;
begin
  Result := ExecGetMyStarBalance(nil);
end;

function TTgApi.GetMyStarBalanceAsync(const AOnSuccess: TProc<ITgStarAmount>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgStarAmount>;
begin
  LExec := ExecGetMyStarBalance;
  Result := RunAsyncCall<ITgStarAmount>(nil, LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryGetMyStarBalance(out AResult: ITgStarAmount; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgStarAmount);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetMyStarBalance;
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildGetStarTransactionsParams(const AOptions: TTgGetStarTransactionsOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecGetStarTransactions(AParams: TTgParams): ITgStarTransactions;
var
  LValue: TJSONValue;
begin
  LValue := Call('getStarTransactions', AParams);
  Result := TTgDto.ResultObject<ITgStarTransactions>(LValue, 'getStarTransactions',
    TgMakeStarTransactions);
end;

function TTgApi.GetStarTransactions(const AOptions: TTgGetStarTransactionsOptions): ITgStarTransactions;
var
  LParams: TTgParams;
begin
  LParams := BuildGetStarTransactionsParams(AOptions);
  try
    Result := ExecGetStarTransactions(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.GetStarTransactions: ITgStarTransactions;
begin
  Result := GetStarTransactions(Default(TTgGetStarTransactionsOptions));
end;

function TTgApi.GetStarTransactionsAsync(const AOptions: TTgGetStarTransactionsOptions;
  const AOnSuccess: TProc<ITgStarTransactions>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgStarTransactions>;
begin
  LExec := ExecGetStarTransactions;
  Result := RunAsyncCall<ITgStarTransactions>(BuildGetStarTransactionsParams(AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.GetStarTransactionsAsync(const AOnSuccess: TProc<ITgStarTransactions>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := GetStarTransactionsAsync(Default(TTgGetStarTransactionsOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryGetStarTransactions(const AOptions: TTgGetStarTransactionsOptions;
  out AResult: ITgStarTransactions; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgStarTransactions);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetStarTransactions(AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryGetStarTransactions(out AResult: ITgStarTransactions;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryGetStarTransactions(Default(TTgGetStarTransactionsOptions), AResult, AError);
end;

function TTgApi.BuildRefundStarPaymentParams(AUserId: Int64;
  const ATelegramPaymentChargeId: string): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('user_id', AUserId);
    Result.Add('telegram_payment_charge_id', ATelegramPaymentChargeId);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecRefundStarPayment(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('refundStarPayment', AParams);
  Result := TTgDto.ResultBool(LValue, 'refundStarPayment');
end;

function TTgApi.RefundStarPayment(AUserId: Int64; const ATelegramPaymentChargeId: string): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildRefundStarPaymentParams(AUserId, ATelegramPaymentChargeId);
  try
    Result := ExecRefundStarPayment(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.RefundStarPaymentAsync(AUserId: Int64; const ATelegramPaymentChargeId: string;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecRefundStarPayment;
  Result := RunAsyncCall<Boolean>(BuildRefundStarPaymentParams(AUserId, ATelegramPaymentChargeId),
    LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryRefundStarPayment(AUserId: Int64; const ATelegramPaymentChargeId: string;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    RefundStarPayment(AUserId, ATelegramPaymentChargeId);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildEditUserStarSubscriptionParams(AUserId: Int64;
  const ATelegramPaymentChargeId: string; AIsCanceled: Boolean): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('user_id', AUserId);
    Result.Add('telegram_payment_charge_id', ATelegramPaymentChargeId);
    Result.Add('is_canceled', AIsCanceled);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecEditUserStarSubscription(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('editUserStarSubscription', AParams);
  Result := TTgDto.ResultBool(LValue, 'editUserStarSubscription');
end;

function TTgApi.EditUserStarSubscription(AUserId: Int64; const ATelegramPaymentChargeId: string;
  AIsCanceled: Boolean): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildEditUserStarSubscriptionParams(AUserId, ATelegramPaymentChargeId, AIsCanceled);
  try
    Result := ExecEditUserStarSubscription(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.EditUserStarSubscriptionAsync(AUserId: Int64;
  const ATelegramPaymentChargeId: string; AIsCanceled: Boolean; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecEditUserStarSubscription;
  Result := RunAsyncCall<Boolean>(BuildEditUserStarSubscriptionParams(AUserId, ATelegramPaymentChargeId, AIsCanceled), LExec, AOnSuccess, AOnError);
end;

function TTgApi.TryEditUserStarSubscription(AUserId: Int64; const ATelegramPaymentChargeId: string;
  AIsCanceled: Boolean; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    EditUserStarSubscription(AUserId, ATelegramPaymentChargeId, AIsCanceled);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildSetPassportDataErrorsParams(AUserId: Int64;
  const AErrors: array of TTgPassportElementError): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('user_id', AUserId);
    Result.AddJson('errors',
      TTgDto.SerializeArray(TTgPassportElementError.Values(AErrors), Result, 'errors'));
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetPassportDataErrors(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setPassportDataErrors', AParams);
  Result := TTgDto.ResultBool(LValue, 'setPassportDataErrors');
end;

function TTgApi.SetPassportDataErrors(AUserId: Int64;
  const AErrors: array of TTgPassportElementError): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetPassportDataErrorsParams(AUserId, AErrors);
  try
    Result := ExecSetPassportDataErrors(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetPassportDataErrorsAsync(AUserId: Int64;
  const AErrors: array of TTgPassportElementError; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetPassportDataErrors;
  Result := RunAsyncCall<Boolean>(BuildSetPassportDataErrorsParams(AUserId, AErrors), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.TrySetPassportDataErrors(AUserId: Int64;
  const AErrors: array of TTgPassportElementError; out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetPassportDataErrors(AUserId, AErrors);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.BuildSendGameParams(const AChatId: TTgChatId; const AGameShortName: string;
  const AOptions: TTgSendGameOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.AddChatId('chat_id', AChatId);
    Result.Add('game_short_name', AGameShortName);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSendGame(AParams: TTgParams): ITgMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('sendGame', AParams);
  Result := TTgDto.ResultObject<ITgMessage>(LValue, 'sendGame', TgMakeMessage);
end;

function TTgApi.SendGame(const AChatId: TTgChatId; const AGameShortName: string;
  const AOptions: TTgSendGameOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildSendGameParams(AChatId, AGameShortName, AOptions);
  try
    Result := ExecSendGame(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SendGame(const AChatId: TTgChatId; const AGameShortName: string): ITgMessage;
begin
  Result := SendGame(AChatId, AGameShortName, Default(TTgSendGameOptions));
end;

function TTgApi.SendGameAsync(const AChatId: TTgChatId; const AGameShortName: string;
  const AOptions: TTgSendGameOptions; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecSendGame;
  Result := RunAsyncCall<ITgMessage>(BuildSendGameParams(AChatId, AGameShortName, AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.SendGameAsync(const AChatId: TTgChatId; const AGameShortName: string;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
begin
  Result := SendGameAsync(AChatId, AGameShortName, Default(TTgSendGameOptions), AOnSuccess,
  AOnError);
end;

function TTgApi.TrySendGame(const AChatId: TTgChatId; const AGameShortName: string;
  const AOptions: TTgSendGameOptions; out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := SendGame(AChatId, AGameShortName, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySendGame(const AChatId: TTgChatId; const AGameShortName: string;
  out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySendGame(AChatId, AGameShortName, Default(TTgSendGameOptions), AResult, AError);
end;

function TTgApi.BuildSetGameScoreParams(AUserId: Int64; AScore: Integer;
  const AOptions: TTgSetGameScoreOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('user_id', AUserId);
    Result.Add('score', AScore);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecSetGameScore(AParams: TTgParams): ITgMessage;
var
  LValue: TJSONValue;
begin
  LValue := Call('setGameScore', AParams);
  Result := TTgDto.ResultObjectOrTrue<ITgMessage>(LValue, 'setGameScore', TgMakeMessage);
end;

function TTgApi.SetGameScore(AUserId: Int64; AScore: Integer;
  const AOptions: TTgSetGameScoreOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildSetGameScoreParams(AUserId, AScore, AOptions);
  try
    Result := ExecSetGameScore(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetGameScore(AUserId: Int64; AScore: Integer): ITgMessage;
begin
  Result := SetGameScore(AUserId, AScore, Default(TTgSetGameScoreOptions));
end;

function TTgApi.SetGameScoreAsync(AUserId: Int64; AScore: Integer;
  const AOptions: TTgSetGameScoreOptions; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecSetGameScore;
  Result := RunAsyncCall<ITgMessage>(BuildSetGameScoreParams(AUserId, AScore, AOptions), LExec,
    AOnSuccess, AOnError);
end;

function TTgApi.SetGameScoreAsync(AUserId: Int64; AScore: Integer;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
begin
  Result := SetGameScoreAsync(AUserId, AScore, Default(TTgSetGameScoreOptions), AOnSuccess,
  AOnError);
end;

function TTgApi.TrySetGameScore(AUserId: Int64; AScore: Integer;
  const AOptions: TTgSetGameScoreOptions; out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := SetGameScore(AUserId, AScore, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySetGameScore(AUserId: Int64; AScore: Integer; out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySetGameScore(AUserId, AScore, Default(TTgSetGameScoreOptions), AResult, AError);
end;

function TTgApi.BuildSetGameScoreVariant1Params(AUserId: Int64; AScore: Integer; AChatId: Int64;
  AMessageId: Int64; const AOptions: TTgSetGameScoreOptions): TTgParams;
var
  LOptions: TTgSetGameScoreOptions;
begin
  LOptions := AOptions;
  LOptions.ChatId := AChatId;
  LOptions.MessageId := AMessageId;
  Result := BuildSetGameScoreParams(AUserId, AScore, LOptions);
end;

function TTgApi.SetGameScore(AUserId: Int64; AScore: Integer; AChatId: Int64; AMessageId: Int64;
  const AOptions: TTgSetGameScoreOptions): ITgMessage;
var
  LParams: TTgParams;
begin
  LParams := BuildSetGameScoreVariant1Params(AUserId, AScore, AChatId, AMessageId, AOptions);
  try
    Result := ExecSetGameScore(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetGameScore(AUserId: Int64; AScore: Integer; AChatId: Int64;
  AMessageId: Int64): ITgMessage;
begin
  Result := SetGameScore(AUserId, AScore, AChatId, AMessageId, Default(TTgSetGameScoreOptions));
end;

function TTgApi.SetGameScoreAsync(AUserId: Int64; AScore: Integer; AChatId: Int64;
  AMessageId: Int64; const AOptions: TTgSetGameScoreOptions; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<ITgMessage>;
begin
  LExec := ExecSetGameScore;
  Result := RunAsyncCall<ITgMessage>(BuildSetGameScoreVariant1Params(AUserId, AScore, AChatId, AMessageId, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.SetGameScoreAsync(AUserId: Int64; AScore: Integer; AChatId: Int64;
  AMessageId: Int64; const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
begin
  Result := SetGameScoreAsync(AUserId, AScore, AChatId, AMessageId, Default(TTgSetGameScoreOptions),
  AOnSuccess, AOnError);
end;

function TTgApi.TrySetGameScore(AUserId: Int64; AScore: Integer; AChatId: Int64; AMessageId: Int64;
  const AOptions: TTgSetGameScoreOptions; out AResult: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(ITgMessage);
  AError := TTgErrorInfo.Empty;
  try
    AResult := SetGameScore(AUserId, AScore, AChatId, AMessageId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySetGameScore(AUserId: Int64; AScore: Integer; AChatId: Int64; AMessageId: Int64;
  out AResult: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySetGameScore(AUserId, AScore, AChatId, AMessageId, Default(TTgSetGameScoreOptions),
  AResult, AError);
end;

function TTgApi.BuildSetGameScoreVariant2Params(AUserId: Int64; AScore: Integer;
  const AInlineMessageId: string; const AOptions: TTgSetGameScoreOptions): TTgParams;
var
  LOptions: TTgSetGameScoreOptions;
begin
  LOptions := AOptions;
  LOptions.InlineMessageId := AInlineMessageId;
  Result := BuildSetGameScoreParams(AUserId, AScore, LOptions);
end;

function TTgApi.ExecSetGameScoreVariant2(AParams: TTgParams): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := Call('setGameScore', AParams);
  Result := TTgDto.ResultBool(LValue, 'setGameScore');
end;

function TTgApi.SetInlineGameScore(AUserId: Int64; AScore: Integer; const AInlineMessageId: string;
  const AOptions: TTgSetGameScoreOptions): Boolean;
var
  LParams: TTgParams;
begin
  LParams := BuildSetGameScoreVariant2Params(AUserId, AScore, AInlineMessageId, AOptions);
  try
    Result := ExecSetGameScoreVariant2(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.SetInlineGameScore(AUserId: Int64; AScore: Integer;
  const AInlineMessageId: string): Boolean;
begin
  Result := SetInlineGameScore(AUserId, AScore, AInlineMessageId, Default(TTgSetGameScoreOptions));
end;

function TTgApi.SetInlineGameScoreAsync(AUserId: Int64; AScore: Integer;
  const AInlineMessageId: string; const AOptions: TTgSetGameScoreOptions;
  const AOnSuccess: TProc<Boolean>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<Boolean>;
begin
  LExec := ExecSetGameScoreVariant2;
  Result := RunAsyncCall<Boolean>(BuildSetGameScoreVariant2Params(AUserId, AScore, AInlineMessageId, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.SetInlineGameScoreAsync(AUserId: Int64; AScore: Integer;
  const AInlineMessageId: string; const AOnSuccess: TProc<Boolean>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := SetInlineGameScoreAsync(AUserId, AScore, AInlineMessageId,
  Default(TTgSetGameScoreOptions), AOnSuccess, AOnError);
end;

function TTgApi.TrySetInlineGameScore(AUserId: Int64; AScore: Integer;
  const AInlineMessageId: string; const AOptions: TTgSetGameScoreOptions;
  out AError: TTgErrorInfo): Boolean;
begin
  AError := TTgErrorInfo.Empty;
  try
    SetInlineGameScore(AUserId, AScore, AInlineMessageId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TrySetInlineGameScore(AUserId: Int64; AScore: Integer;
  const AInlineMessageId: string; out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySetInlineGameScore(AUserId, AScore, AInlineMessageId,
  Default(TTgSetGameScoreOptions), AError);
end;

function TTgApi.BuildGetGameHighScoresParams(AUserId: Int64;
  const AOptions: TTgGetGameHighScoresOptions): TTgParams;
begin
  Result := TTgParams.Create;
  try
    Result.Add('user_id', AUserId);
    AOptions.ApplyTo(Result);
  except
    Result.Free;
    raise;
  end;
end;

function TTgApi.ExecGetGameHighScores(AParams: TTgParams): TArray<ITgGameHighScore>;
var
  LValue: TJSONValue;
begin
  LValue := Call('getGameHighScores', AParams);
  Result := TTgDto.ResultArray<ITgGameHighScore>(LValue, 'getGameHighScores', TgMakeGameHighScore);
end;

function TTgApi.GetGameHighScores(AUserId: Int64;
  const AOptions: TTgGetGameHighScoresOptions): TArray<ITgGameHighScore>;
var
  LParams: TTgParams;
begin
  LParams := BuildGetGameHighScoresParams(AUserId, AOptions);
  try
    Result := ExecGetGameHighScores(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.GetGameHighScores(AUserId: Int64): TArray<ITgGameHighScore>;
begin
  Result := GetGameHighScores(AUserId, Default(TTgGetGameHighScoresOptions));
end;

function TTgApi.GetGameHighScoresAsync(AUserId: Int64; const AOptions: TTgGetGameHighScoresOptions;
  const AOnSuccess: TProc<TArray<ITgGameHighScore>>; const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<TArray<ITgGameHighScore>>;
begin
  LExec := ExecGetGameHighScores;
  Result := RunAsyncCall<TArray<ITgGameHighScore>>(BuildGetGameHighScoresParams(AUserId, AOptions),
    LExec, AOnSuccess, AOnError);
end;

function TTgApi.GetGameHighScoresAsync(AUserId: Int64;
  const AOnSuccess: TProc<TArray<ITgGameHighScore>>; const AOnError: TProc<Exception>): ITask;
begin
  Result := GetGameHighScoresAsync(AUserId, Default(TTgGetGameHighScoresOptions), AOnSuccess,
  AOnError);
end;

function TTgApi.TryGetGameHighScores(AUserId: Int64; const AOptions: TTgGetGameHighScoresOptions;
  out AResult: TArray<ITgGameHighScore>; out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(TArray<ITgGameHighScore>);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetGameHighScores(AUserId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryGetGameHighScores(AUserId: Int64; out AResult: TArray<ITgGameHighScore>;
  out AError: TTgErrorInfo): Boolean;
begin
  Result := TryGetGameHighScores(AUserId, Default(TTgGetGameHighScoresOptions), AResult, AError);
end;

function TTgApi.BuildGetGameHighScoresVariant1Params(AUserId: Int64; AChatId: Int64;
  AMessageId: Int64; const AOptions: TTgGetGameHighScoresOptions): TTgParams;
var
  LOptions: TTgGetGameHighScoresOptions;
begin
  LOptions := AOptions;
  LOptions.ChatId := AChatId;
  LOptions.MessageId := AMessageId;
  Result := BuildGetGameHighScoresParams(AUserId, LOptions);
end;

function TTgApi.GetGameHighScores(AUserId: Int64; AChatId: Int64; AMessageId: Int64;
  const AOptions: TTgGetGameHighScoresOptions): TArray<ITgGameHighScore>;
var
  LParams: TTgParams;
begin
  LParams := BuildGetGameHighScoresVariant1Params(AUserId, AChatId, AMessageId, AOptions);
  try
    Result := ExecGetGameHighScores(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.GetGameHighScores(AUserId: Int64; AChatId: Int64;
  AMessageId: Int64): TArray<ITgGameHighScore>;
begin
  Result := GetGameHighScores(AUserId, AChatId, AMessageId, Default(TTgGetGameHighScoresOptions));
end;

function TTgApi.GetGameHighScoresAsync(AUserId: Int64; AChatId: Int64; AMessageId: Int64;
  const AOptions: TTgGetGameHighScoresOptions; const AOnSuccess: TProc<TArray<ITgGameHighScore>>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<TArray<ITgGameHighScore>>;
begin
  LExec := ExecGetGameHighScores;
  Result := RunAsyncCall<TArray<ITgGameHighScore>>(BuildGetGameHighScoresVariant1Params(AUserId, AChatId, AMessageId, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.GetGameHighScoresAsync(AUserId: Int64; AChatId: Int64; AMessageId: Int64;
  const AOnSuccess: TProc<TArray<ITgGameHighScore>>; const AOnError: TProc<Exception>): ITask;
begin
  Result := GetGameHighScoresAsync(AUserId, AChatId, AMessageId,
  Default(TTgGetGameHighScoresOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryGetGameHighScores(AUserId: Int64; AChatId: Int64; AMessageId: Int64;
  const AOptions: TTgGetGameHighScoresOptions; out AResult: TArray<ITgGameHighScore>;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(TArray<ITgGameHighScore>);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetGameHighScores(AUserId, AChatId, AMessageId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryGetGameHighScores(AUserId: Int64; AChatId: Int64; AMessageId: Int64;
  out AResult: TArray<ITgGameHighScore>; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryGetGameHighScores(AUserId, AChatId, AMessageId, Default(TTgGetGameHighScoresOptions),
  AResult, AError);
end;

function TTgApi.BuildGetGameHighScoresVariant2Params(AUserId: Int64; const AInlineMessageId: string;
  const AOptions: TTgGetGameHighScoresOptions): TTgParams;
var
  LOptions: TTgGetGameHighScoresOptions;
begin
  LOptions := AOptions;
  LOptions.InlineMessageId := AInlineMessageId;
  Result := BuildGetGameHighScoresParams(AUserId, LOptions);
end;

function TTgApi.GetInlineGameHighScores(AUserId: Int64; const AInlineMessageId: string;
  const AOptions: TTgGetGameHighScoresOptions): TArray<ITgGameHighScore>;
var
  LParams: TTgParams;
begin
  LParams := BuildGetGameHighScoresVariant2Params(AUserId, AInlineMessageId, AOptions);
  try
    Result := ExecGetGameHighScores(LParams);
  finally
    LParams.Free;
  end;
end;

function TTgApi.GetInlineGameHighScores(AUserId: Int64;
  const AInlineMessageId: string): TArray<ITgGameHighScore>;
begin
  Result := GetInlineGameHighScores(AUserId, AInlineMessageId,
  Default(TTgGetGameHighScoresOptions));
end;

function TTgApi.GetInlineGameHighScoresAsync(AUserId: Int64; const AInlineMessageId: string;
  const AOptions: TTgGetGameHighScoresOptions; const AOnSuccess: TProc<TArray<ITgGameHighScore>>;
  const AOnError: TProc<Exception>): ITask;
var
  LExec: TTgExecFunc<TArray<ITgGameHighScore>>;
begin
  LExec := ExecGetGameHighScores;
  Result := RunAsyncCall<TArray<ITgGameHighScore>>(BuildGetGameHighScoresVariant2Params(AUserId, AInlineMessageId, AOptions), LExec, AOnSuccess, AOnError);
end;

function TTgApi.GetInlineGameHighScoresAsync(AUserId: Int64; const AInlineMessageId: string;
  const AOnSuccess: TProc<TArray<ITgGameHighScore>>; const AOnError: TProc<Exception>): ITask;
begin
  Result := GetInlineGameHighScoresAsync(AUserId, AInlineMessageId,
  Default(TTgGetGameHighScoresOptions), AOnSuccess, AOnError);
end;

function TTgApi.TryGetInlineGameHighScores(AUserId: Int64; const AInlineMessageId: string;
  const AOptions: TTgGetGameHighScoresOptions; out AResult: TArray<ITgGameHighScore>;
  out AError: TTgErrorInfo): Boolean;
begin
  AResult := Default(TArray<ITgGameHighScore>);
  AError := TTgErrorInfo.Empty;
  try
    AResult := GetInlineGameHighScores(AUserId, AInlineMessageId, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

function TTgApi.TryGetInlineGameHighScores(AUserId: Int64; const AInlineMessageId: string;
  out AResult: TArray<ITgGameHighScore>; out AError: TTgErrorInfo): Boolean;
begin
  Result := TryGetInlineGameHighScores(AUserId, AInlineMessageId,
  Default(TTgGetGameHighScoresOptions), AResult, AError);
end;

