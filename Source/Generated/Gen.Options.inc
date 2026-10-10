// Gen.Options.inc — необязательные параметры методов.
// Сгенерировано TgBotGen по Telegram Bot API 10.3 (August 24, 2026). Не редактируйте вручную.

  /// <summary>
  ///   Необязательные параметры getUpdates. Неинициализированная запись пуста
  ///   (Default(TTgGetUpdatesOptions)).
  /// </summary>
  TTgGetUpdatesOptions = record
    /// <summary>
    ///   Identifier of the first update to be returned. Must be greater by one than the highest
    ///   among the identifiers of previously received updates. By default, updates starting with
    ///   the earliest unconfirmed update are returned. An update is considered confirmed as soon as
    ///   getUpdates is called with an offset higher than its update_id. The negative offset can be
    ///   specified to retrieve updates starting from -offset update from the end of the updates
    ///   queue. All previous updates will be forgotten.
    /// </summary>
    Offset: TTgOptional<Int64>;
    /// <summary>
    ///   Limits the number of updates to be retrieved. Values between 1-100 are accepted. Defaults
    ///   to 100.
    /// </summary>
    Limit: TTgOptional<Integer>;
    /// <summary>
    ///   Timeout in seconds for long polling. Defaults to 0, i.e. usual short polling. Should be
    ///   positive, short polling should be used for testing purposes only.
    /// </summary>
    Timeout: TTgOptional<Integer>;
    /// <summary>
    ///   A JSON-serialized list of the update types you want your bot to receive. For example,
    ///   specify ["message", "edited_channel_post", "callback_query"] to only receive updates of
    ///   these types. See Update for a complete list of available update types. Specify an empty
    ///   list to receive all update types except chat_member, message_reaction, and
    ///   message_reaction_count (default). If not specified, the previous setting will be used.
    ///   Please note that this parameter doesn't affect updates created before the call to
    ///   getUpdates, so unwanted updates may be received for a short period of time. Не задано —
    ///   параметр не передаётся; [] — передаётся пустой список.
    /// </summary>
    AllowedUpdates: TTgOptional<TArray<string>>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры setWebhook. Неинициализированная запись пуста
  ///   (Default(TTgSetWebhookOptions)).
  /// </summary>
  TTgSetWebhookOptions = record
    /// <summary>
    ///   Upload your public key certificate so that the root certificate in use can be checked. See
    ///   our self-signed guide for details.
    /// </summary>
    Certificate: TTgInputFile;
    /// <summary>
    ///   The fixed IP address which will be used to send webhook requests instead of the IP address
    ///   resolved through DNS
    /// </summary>
    IpAddress: TTgOptional<string>;
    /// <summary>
    ///   The maximum allowed number of simultaneous HTTPS connections to the webhook for update
    ///   delivery, 1-100. Defaults to 40. Use lower values to limit the load on your bot's server,
    ///   and higher values to increase your bot's throughput.
    /// </summary>
    MaxConnections: TTgOptional<Integer>;
    /// <summary>
    ///   A JSON-serialized list of the update types you want your bot to receive. For example,
    ///   specify ["message", "edited_channel_post", "callback_query"] to only receive updates of
    ///   these types. See Update for a complete list of available update types. Specify an empty
    ///   list to receive all update types except chat_member, message_reaction, and
    ///   message_reaction_count (default). If not specified, the previous setting will be used.
    ///   Please note that this parameter doesn't affect updates created before the call to the
    ///   setWebhook, so unwanted updates may be received for a short period of time. Не задано —
    ///   параметр не передаётся; [] — передаётся пустой список.
    /// </summary>
    AllowedUpdates: TTgOptional<TArray<string>>;
    /// <summary>Pass True to drop all pending updates</summary>
    DropPendingUpdates: TTgOptional<Boolean>;
    /// <summary>
    ///   A secret token to be sent in a header “X-Telegram-Bot-Api-Secret-Token” in every webhook
    ///   request, 1-256 characters. Only characters A-Z, a-z, 0-9, _ and - are allowed. The header
    ///   is useful to ensure that the request comes from a webhook set by you.
    /// </summary>
    SecretToken: TTgOptional<string>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры deleteWebhook. Неинициализированная запись пуста
  ///   (Default(TTgDeleteWebhookOptions)).
  /// </summary>
  TTgDeleteWebhookOptions = record
    /// <summary>Pass True to drop all pending updates</summary>
    DropPendingUpdates: TTgOptional<Boolean>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры sendMessage. Неинициализированная запись пуста
  ///   (Default(TTgSendMessageOptions)).
  /// </summary>
  TTgSendMessageOptions = record
    /// <summary>
    ///   Unique identifier of the business connection on behalf of which the message will be sent
    /// </summary>
    BusinessConnectionId: TTgOptional<string>;
    /// <summary>
    ///   Unique identifier for the target message thread (topic) of a forum; for forum supergroups
    ///   and private chats of bots with forum topic mode enabled only
    /// </summary>
    MessageThreadId: TTgOptional<Int64>;
    /// <summary>
    ///   Identifier of the direct messages topic to which the message will be sent; required if the
    ///   message is sent to a direct messages chat
    /// </summary>
    DirectMessagesTopicId: TTgOptional<Int64>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the ephemeral message to send
    /// </summary>
    EphemeralMessageParameters: ITgEphemeralMessageParameters;
    /// <summary>
    ///   Mode for parsing entities in the message text. See formatting options for more details.
    /// </summary>
    ParseMode: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized list of special entities that appear in message text, which can be
    ///   specified instead of parse_mode Не задано — параметр не передаётся; [] — передаётся пустой
    ///   список.
    /// </summary>
    Entities: TTgOptional<TArray<ITgMessageEntity>>;
    /// <summary>Link preview generation options for the message</summary>
    LinkPreviewOptions: ITgLinkPreviewOptions;
    /// <summary>
    ///   Sends the message silently. Users will receive a notification with no sound.
    /// </summary>
    DisableNotification: TTgOptional<Boolean>;
    /// <summary>
    ///   Protects the contents of the sent message from forwarding and saving
    /// </summary>
    ProtectContent: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to allow up to 1000 messages per second, ignoring broadcasting limits for a fee
    ///   of 0.1 Telegram Stars per message. The relevant Stars will be withdrawn from the bot's
    ///   balance.
    /// </summary>
    AllowPaidBroadcast: TTgOptional<Boolean>;
    /// <summary>
    ///   Unique identifier of the message effect to be added to the message; for private chats only
    /// </summary>
    MessageEffectId: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the suggested post to send; for
    ///   direct messages chats only. If the message is sent as a reply to another suggested post,
    ///   then that suggested post is automatically declined.
    /// </summary>
    SuggestedPostParameters: ITgSuggestedPostParameters;
    /// <summary>Description of the message to reply to</summary>
    ReplyParameters: ITgReplyParameters;
    /// <summary>
    ///   Additional interface options. A JSON-serialized object for an inline keyboard, custom
    ///   reply keyboard, instructions to remove a reply keyboard or to force a reply from the user.
    ///   Построитель: TTgKeyboard.Inline…, TTgKeyboard.Reply…, TTgKeyboard.Remove,
    ///   TTgKeyboard.ForceReply.
    /// </summary>
    ReplyMarkup: TTgReplyMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры forwardMessage. Неинициализированная запись пуста
  ///   (Default(TTgForwardMessageOptions)).
  /// </summary>
  TTgForwardMessageOptions = record
    /// <summary>
    ///   Unique identifier for the target message thread (topic) of a forum; for forum supergroups
    ///   and private chats of bots with forum topic mode enabled only
    /// </summary>
    MessageThreadId: TTgOptional<Int64>;
    /// <summary>
    ///   Identifier of the direct messages topic to which the message will be forwarded; required
    ///   if the message is forwarded to a direct messages chat
    /// </summary>
    DirectMessagesTopicId: TTgOptional<Int64>;
    /// <summary>New start timestamp for the forwarded video in the message</summary>
    VideoStartTimestamp: TTgOptional<Integer>;
    /// <summary>
    ///   Sends the message silently. Users will receive a notification with no sound.
    /// </summary>
    DisableNotification: TTgOptional<Boolean>;
    /// <summary>
    ///   Protects the contents of the forwarded message from forwarding and saving
    /// </summary>
    ProtectContent: TTgOptional<Boolean>;
    /// <summary>
    ///   Unique identifier of the message effect to be added to the message; only available when
    ///   forwarding to private chats
    /// </summary>
    MessageEffectId: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the suggested post to send; for
    ///   direct messages chats only
    /// </summary>
    SuggestedPostParameters: ITgSuggestedPostParameters;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры forwardMessages. Неинициализированная запись пуста
  ///   (Default(TTgForwardMessagesOptions)).
  /// </summary>
  TTgForwardMessagesOptions = record
    /// <summary>
    ///   Unique identifier for the target message thread (topic) of a forum; for forum supergroups
    ///   and private chats of bots with forum topic mode enabled only
    /// </summary>
    MessageThreadId: TTgOptional<Int64>;
    /// <summary>
    ///   Identifier of the direct messages topic to which the messages will be forwarded; required
    ///   if the messages are forwarded to a direct messages chat
    /// </summary>
    DirectMessagesTopicId: TTgOptional<Int64>;
    /// <summary>
    ///   Sends the messages silently. Users will receive a notification with no sound.
    /// </summary>
    DisableNotification: TTgOptional<Boolean>;
    /// <summary>
    ///   Protects the contents of the forwarded messages from forwarding and saving
    /// </summary>
    ProtectContent: TTgOptional<Boolean>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры copyMessage. Неинициализированная запись пуста
  ///   (Default(TTgCopyMessageOptions)).
  /// </summary>
  TTgCopyMessageOptions = record
    /// <summary>
    ///   Unique identifier for the target message thread (topic) of a forum; for forum supergroups
    ///   and private chats of bots with forum topic mode enabled only
    /// </summary>
    MessageThreadId: TTgOptional<Int64>;
    /// <summary>
    ///   Identifier of the direct messages topic to which the message will be sent; required if the
    ///   message is sent to a direct messages chat
    /// </summary>
    DirectMessagesTopicId: TTgOptional<Int64>;
    /// <summary>New start timestamp for the copied video in the message</summary>
    VideoStartTimestamp: TTgOptional<Integer>;
    /// <summary>
    ///   New caption for media, 0-1024 characters after entities parsing. If not specified, the
    ///   original caption is kept.
    /// </summary>
    Caption: TTgOptional<string>;
    /// <summary>
    ///   Mode for parsing entities in the new caption. See formatting options for more details.
    /// </summary>
    ParseMode: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized list of special entities that appear in the new caption, which can be
    ///   specified instead of parse_mode Не задано — параметр не передаётся; [] — передаётся пустой
    ///   список.
    /// </summary>
    CaptionEntities: TTgOptional<TArray<ITgMessageEntity>>;
    /// <summary>
    ///   Pass True if the caption must be shown above the message media. Ignored if a new caption
    ///   isn't specified.
    /// </summary>
    ShowCaptionAboveMedia: TTgOptional<Boolean>;
    /// <summary>
    ///   Sends the message silently. Users will receive a notification with no sound.
    /// </summary>
    DisableNotification: TTgOptional<Boolean>;
    /// <summary>
    ///   Protects the contents of the sent message from forwarding and saving
    /// </summary>
    ProtectContent: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to allow up to 1000 messages per second, ignoring broadcasting limits for a fee
    ///   of 0.1 Telegram Stars per message. The relevant Stars will be withdrawn from the bot's
    ///   balance.
    /// </summary>
    AllowPaidBroadcast: TTgOptional<Boolean>;
    /// <summary>
    ///   Unique identifier of the message effect to be added to the message; only available when
    ///   copying to private chats
    /// </summary>
    MessageEffectId: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the suggested post to send; for
    ///   direct messages chats only. If the message is sent as a reply to another suggested post,
    ///   then that suggested post is automatically declined.
    /// </summary>
    SuggestedPostParameters: ITgSuggestedPostParameters;
    /// <summary>Description of the message to reply to</summary>
    ReplyParameters: ITgReplyParameters;
    /// <summary>
    ///   Additional interface options. A JSON-serialized object for an inline keyboard, custom
    ///   reply keyboard, instructions to remove a reply keyboard or to force a reply from the user.
    ///   Построитель: TTgKeyboard.Inline…, TTgKeyboard.Reply…, TTgKeyboard.Remove,
    ///   TTgKeyboard.ForceReply.
    /// </summary>
    ReplyMarkup: TTgReplyMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры copyMessages. Неинициализированная запись пуста
  ///   (Default(TTgCopyMessagesOptions)).
  /// </summary>
  TTgCopyMessagesOptions = record
    /// <summary>
    ///   Unique identifier for the target message thread (topic) of a forum; for forum supergroups
    ///   and private chats of bots with forum topic mode enabled only
    /// </summary>
    MessageThreadId: TTgOptional<Int64>;
    /// <summary>
    ///   Identifier of the direct messages topic to which the messages will be sent; required if
    ///   the messages are sent to a direct messages chat
    /// </summary>
    DirectMessagesTopicId: TTgOptional<Int64>;
    /// <summary>
    ///   Sends the messages silently. Users will receive a notification with no sound.
    /// </summary>
    DisableNotification: TTgOptional<Boolean>;
    /// <summary>
    ///   Protects the contents of the sent messages from forwarding and saving
    /// </summary>
    ProtectContent: TTgOptional<Boolean>;
    /// <summary>Pass True to copy the messages without their captions</summary>
    RemoveCaption: TTgOptional<Boolean>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры sendPhoto. Неинициализированная запись пуста
  ///   (Default(TTgSendPhotoOptions)).
  /// </summary>
  TTgSendPhotoOptions = record
    /// <summary>
    ///   Unique identifier of the business connection on behalf of which the message will be sent
    /// </summary>
    BusinessConnectionId: TTgOptional<string>;
    /// <summary>
    ///   Unique identifier for the target message thread (topic) of a forum; for forum supergroups
    ///   and private chats of bots with forum topic mode enabled only
    /// </summary>
    MessageThreadId: TTgOptional<Int64>;
    /// <summary>
    ///   Identifier of the direct messages topic to which the message will be sent; required if the
    ///   message is sent to a direct messages chat
    /// </summary>
    DirectMessagesTopicId: TTgOptional<Int64>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the ephemeral message to send
    /// </summary>
    EphemeralMessageParameters: ITgEphemeralMessageParameters;
    /// <summary>
    ///   Photo caption (may also be used when resending photos by file_id), 0-1024 characters after
    ///   entities parsing
    /// </summary>
    Caption: TTgOptional<string>;
    /// <summary>
    ///   Mode for parsing entities in the photo caption. See formatting options for more details.
    /// </summary>
    ParseMode: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized list of special entities that appear in the caption, which can be
    ///   specified instead of parse_mode Не задано — параметр не передаётся; [] — передаётся пустой
    ///   список.
    /// </summary>
    CaptionEntities: TTgOptional<TArray<ITgMessageEntity>>;
    /// <summary>Pass True if the caption must be shown above the message media</summary>
    ShowCaptionAboveMedia: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if the photo needs to be covered with a spoiler animation
    /// </summary>
    HasSpoiler: TTgOptional<Boolean>;
    /// <summary>
    ///   Sends the message silently. Users will receive a notification with no sound.
    /// </summary>
    DisableNotification: TTgOptional<Boolean>;
    /// <summary>
    ///   Protects the contents of the sent message from forwarding and saving
    /// </summary>
    ProtectContent: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to allow up to 1000 messages per second, ignoring broadcasting limits for a fee
    ///   of 0.1 Telegram Stars per message. The relevant Stars will be withdrawn from the bot's
    ///   balance.
    /// </summary>
    AllowPaidBroadcast: TTgOptional<Boolean>;
    /// <summary>
    ///   Unique identifier of the message effect to be added to the message; for private chats only
    /// </summary>
    MessageEffectId: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the suggested post to send; for
    ///   direct messages chats only. If the message is sent as a reply to another suggested post,
    ///   then that suggested post is automatically declined.
    /// </summary>
    SuggestedPostParameters: ITgSuggestedPostParameters;
    /// <summary>Description of the message to reply to</summary>
    ReplyParameters: ITgReplyParameters;
    /// <summary>
    ///   Additional interface options. A JSON-serialized object for an inline keyboard, custom
    ///   reply keyboard, instructions to remove a reply keyboard or to force a reply from the user.
    ///   Построитель: TTgKeyboard.Inline…, TTgKeyboard.Reply…, TTgKeyboard.Remove,
    ///   TTgKeyboard.ForceReply.
    /// </summary>
    ReplyMarkup: TTgReplyMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры sendLivePhoto. Неинициализированная запись пуста
  ///   (Default(TTgSendLivePhotoOptions)).
  /// </summary>
  TTgSendLivePhotoOptions = record
    /// <summary>
    ///   Unique identifier of the business connection on behalf of which the message will be sent
    /// </summary>
    BusinessConnectionId: TTgOptional<string>;
    /// <summary>
    ///   Unique identifier for the target message thread (topic) of a forum; for forum supergroups
    ///   and private chats of bots with forum topic mode enabled only
    /// </summary>
    MessageThreadId: TTgOptional<Int64>;
    /// <summary>
    ///   Identifier of the direct messages topic to which the message will be sent; required if the
    ///   message is sent to a direct messages chat
    /// </summary>
    DirectMessagesTopicId: TTgOptional<Int64>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the ephemeral message to send
    /// </summary>
    EphemeralMessageParameters: ITgEphemeralMessageParameters;
    /// <summary>
    ///   Video caption (may also be used when resending videos by file_id), 0-1024 characters after
    ///   entities parsing
    /// </summary>
    Caption: TTgOptional<string>;
    /// <summary>
    ///   Mode for parsing entities in the video caption. See formatting options for more details.
    /// </summary>
    ParseMode: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized list of special entities that appear in the caption, which can be
    ///   specified instead of parse_mode Не задано — параметр не передаётся; [] — передаётся пустой
    ///   список.
    /// </summary>
    CaptionEntities: TTgOptional<TArray<ITgMessageEntity>>;
    /// <summary>Pass True if the caption must be shown above the message media</summary>
    ShowCaptionAboveMedia: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if the video needs to be covered with a spoiler animation
    /// </summary>
    HasSpoiler: TTgOptional<Boolean>;
    /// <summary>
    ///   Sends the message silently. Users will receive a notification with no sound.
    /// </summary>
    DisableNotification: TTgOptional<Boolean>;
    /// <summary>
    ///   Protects the contents of the sent message from forwarding and saving
    /// </summary>
    ProtectContent: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to allow up to 1000 messages per second, ignoring broadcasting limits for a fee
    ///   of 0.1 Telegram Stars per message. The relevant Stars will be withdrawn from the bot's
    ///   balance.
    /// </summary>
    AllowPaidBroadcast: TTgOptional<Boolean>;
    /// <summary>
    ///   Unique identifier of the message effect to be added to the message; for private chats only
    /// </summary>
    MessageEffectId: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the suggested post to send; for
    ///   direct messages chats only. If the message is sent as a reply to another suggested post,
    ///   then that suggested post is automatically declined.
    /// </summary>
    SuggestedPostParameters: ITgSuggestedPostParameters;
    /// <summary>Description of the message to reply to</summary>
    ReplyParameters: ITgReplyParameters;
    /// <summary>
    ///   Additional interface options. A JSON-serialized object for an inline keyboard, custom
    ///   reply keyboard, instructions to remove a reply keyboard or to force a reply from the user.
    ///   Построитель: TTgKeyboard.Inline…, TTgKeyboard.Reply…, TTgKeyboard.Remove,
    ///   TTgKeyboard.ForceReply.
    /// </summary>
    ReplyMarkup: TTgReplyMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры sendAudio. Неинициализированная запись пуста
  ///   (Default(TTgSendAudioOptions)).
  /// </summary>
  TTgSendAudioOptions = record
    /// <summary>
    ///   Unique identifier of the business connection on behalf of which the message will be sent
    /// </summary>
    BusinessConnectionId: TTgOptional<string>;
    /// <summary>
    ///   Unique identifier for the target message thread (topic) of a forum; for forum supergroups
    ///   and private chats of bots with forum topic mode enabled only
    /// </summary>
    MessageThreadId: TTgOptional<Int64>;
    /// <summary>
    ///   Identifier of the direct messages topic to which the message will be sent; required if the
    ///   message is sent to a direct messages chat
    /// </summary>
    DirectMessagesTopicId: TTgOptional<Int64>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the ephemeral message to send
    /// </summary>
    EphemeralMessageParameters: ITgEphemeralMessageParameters;
    /// <summary>Audio caption, 0-1024 characters after entities parsing</summary>
    Caption: TTgOptional<string>;
    /// <summary>
    ///   Mode for parsing entities in the audio caption. See formatting options for more details.
    /// </summary>
    ParseMode: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized list of special entities that appear in the caption, which can be
    ///   specified instead of parse_mode Не задано — параметр не передаётся; [] — передаётся пустой
    ///   список.
    /// </summary>
    CaptionEntities: TTgOptional<TArray<ITgMessageEntity>>;
    /// <summary>Duration of the audio in seconds</summary>
    Duration: TTgOptional<Integer>;
    /// <summary>Performer</summary>
    Performer: TTgOptional<string>;
    /// <summary>Track name</summary>
    Title: TTgOptional<string>;
    /// <summary>
    ///   Thumbnail of the file sent; can be ignored if thumbnail generation for the file is
    ///   supported server-side. The thumbnail should be in JPEG format and less than 200 kB in
    ///   size. A thumbnail's width and height should not exceed 320. Ignored if the file is not
    ///   uploaded using multipart/form-data. Thumbnails can't be reused and can be only uploaded as
    ///   a new file, so you can pass “attach://&lt;file_attach_name&gt;” if the thumbnail was
    ///   uploaded using multipart/form-data under &lt;file_attach_name&gt;. More information on
    ///   Sending Files »
    /// </summary>
    Thumbnail: TTgInputFile;
    /// <summary>
    ///   Sends the message silently. Users will receive a notification with no sound.
    /// </summary>
    DisableNotification: TTgOptional<Boolean>;
    /// <summary>
    ///   Protects the contents of the sent message from forwarding and saving
    /// </summary>
    ProtectContent: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to allow up to 1000 messages per second, ignoring broadcasting limits for a fee
    ///   of 0.1 Telegram Stars per message. The relevant Stars will be withdrawn from the bot's
    ///   balance.
    /// </summary>
    AllowPaidBroadcast: TTgOptional<Boolean>;
    /// <summary>
    ///   Unique identifier of the message effect to be added to the message; for private chats only
    /// </summary>
    MessageEffectId: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the suggested post to send; for
    ///   direct messages chats only. If the message is sent as a reply to another suggested post,
    ///   then that suggested post is automatically declined.
    /// </summary>
    SuggestedPostParameters: ITgSuggestedPostParameters;
    /// <summary>Description of the message to reply to</summary>
    ReplyParameters: ITgReplyParameters;
    /// <summary>
    ///   Additional interface options. A JSON-serialized object for an inline keyboard, custom
    ///   reply keyboard, instructions to remove a reply keyboard or to force a reply from the user.
    ///   Построитель: TTgKeyboard.Inline…, TTgKeyboard.Reply…, TTgKeyboard.Remove,
    ///   TTgKeyboard.ForceReply.
    /// </summary>
    ReplyMarkup: TTgReplyMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры sendDocument. Неинициализированная запись пуста
  ///   (Default(TTgSendDocumentOptions)).
  /// </summary>
  TTgSendDocumentOptions = record
    /// <summary>
    ///   Unique identifier of the business connection on behalf of which the message will be sent
    /// </summary>
    BusinessConnectionId: TTgOptional<string>;
    /// <summary>
    ///   Unique identifier for the target message thread (topic) of a forum; for forum supergroups
    ///   and private chats of bots with forum topic mode enabled only
    /// </summary>
    MessageThreadId: TTgOptional<Int64>;
    /// <summary>
    ///   Identifier of the direct messages topic to which the message will be sent; required if the
    ///   message is sent to a direct messages chat
    /// </summary>
    DirectMessagesTopicId: TTgOptional<Int64>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the ephemeral message to send
    /// </summary>
    EphemeralMessageParameters: ITgEphemeralMessageParameters;
    /// <summary>
    ///   Thumbnail of the file sent; can be ignored if thumbnail generation for the file is
    ///   supported server-side. The thumbnail should be in JPEG format and less than 200 kB in
    ///   size. A thumbnail's width and height should not exceed 320. Ignored if the file is not
    ///   uploaded using multipart/form-data. Thumbnails can't be reused and can be only uploaded as
    ///   a new file, so you can pass “attach://&lt;file_attach_name&gt;” if the thumbnail was
    ///   uploaded using multipart/form-data under &lt;file_attach_name&gt;. More information on
    ///   Sending Files »
    /// </summary>
    Thumbnail: TTgInputFile;
    /// <summary>
    ///   Document caption (may also be used when resending documents by file_id), 0-1024 characters
    ///   after entities parsing
    /// </summary>
    Caption: TTgOptional<string>;
    /// <summary>
    ///   Mode for parsing entities in the document caption. See formatting options for more
    ///   details.
    /// </summary>
    ParseMode: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized list of special entities that appear in the caption, which can be
    ///   specified instead of parse_mode Не задано — параметр не передаётся; [] — передаётся пустой
    ///   список.
    /// </summary>
    CaptionEntities: TTgOptional<TArray<ITgMessageEntity>>;
    /// <summary>
    ///   Disables automatic server-side content type detection for files uploaded using
    ///   multipart/form-data
    /// </summary>
    DisableContentTypeDetection: TTgOptional<Boolean>;
    /// <summary>
    ///   Sends the message silently. Users will receive a notification with no sound.
    /// </summary>
    DisableNotification: TTgOptional<Boolean>;
    /// <summary>
    ///   Protects the contents of the sent message from forwarding and saving
    /// </summary>
    ProtectContent: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to allow up to 1000 messages per second, ignoring broadcasting limits for a fee
    ///   of 0.1 Telegram Stars per message. The relevant Stars will be withdrawn from the bot's
    ///   balance.
    /// </summary>
    AllowPaidBroadcast: TTgOptional<Boolean>;
    /// <summary>
    ///   Unique identifier of the message effect to be added to the message; for private chats only
    /// </summary>
    MessageEffectId: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the suggested post to send; for
    ///   direct messages chats only. If the message is sent as a reply to another suggested post,
    ///   then that suggested post is automatically declined.
    /// </summary>
    SuggestedPostParameters: ITgSuggestedPostParameters;
    /// <summary>Description of the message to reply to</summary>
    ReplyParameters: ITgReplyParameters;
    /// <summary>
    ///   Additional interface options. A JSON-serialized object for an inline keyboard, custom
    ///   reply keyboard, instructions to remove a reply keyboard or to force a reply from the user.
    ///   Построитель: TTgKeyboard.Inline…, TTgKeyboard.Reply…, TTgKeyboard.Remove,
    ///   TTgKeyboard.ForceReply.
    /// </summary>
    ReplyMarkup: TTgReplyMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры sendVideo. Неинициализированная запись пуста
  ///   (Default(TTgSendVideoOptions)).
  /// </summary>
  TTgSendVideoOptions = record
    /// <summary>
    ///   Unique identifier of the business connection on behalf of which the message will be sent
    /// </summary>
    BusinessConnectionId: TTgOptional<string>;
    /// <summary>
    ///   Unique identifier for the target message thread (topic) of a forum; for forum supergroups
    ///   and private chats of bots with forum topic mode enabled only
    /// </summary>
    MessageThreadId: TTgOptional<Int64>;
    /// <summary>
    ///   Identifier of the direct messages topic to which the message will be sent; required if the
    ///   message is sent to a direct messages chat
    /// </summary>
    DirectMessagesTopicId: TTgOptional<Int64>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the ephemeral message to send
    /// </summary>
    EphemeralMessageParameters: ITgEphemeralMessageParameters;
    /// <summary>Duration of sent video in seconds</summary>
    Duration: TTgOptional<Integer>;
    /// <summary>Video width</summary>
    Width: TTgOptional<Integer>;
    /// <summary>Video height</summary>
    Height: TTgOptional<Integer>;
    /// <summary>
    ///   Thumbnail of the file sent; can be ignored if thumbnail generation for the file is
    ///   supported server-side. The thumbnail should be in JPEG format and less than 200 kB in
    ///   size. A thumbnail's width and height should not exceed 320. Ignored if the file is not
    ///   uploaded using multipart/form-data. Thumbnails can't be reused and can be only uploaded as
    ///   a new file, so you can pass “attach://&lt;file_attach_name&gt;” if the thumbnail was
    ///   uploaded using multipart/form-data under &lt;file_attach_name&gt;. More information on
    ///   Sending Files »
    /// </summary>
    Thumbnail: TTgInputFile;
    /// <summary>
    ///   Cover for the video in the message. Pass a file_id to send a file that exists on the
    ///   Telegram servers (recommended), pass an HTTP URL for Telegram to get a file from the
    ///   Internet, or pass “attach://&lt;file_attach_name&gt;” to upload a new one using
    ///   multipart/form-data under &lt;file_attach_name&gt; name. More information on Sending Files
    ///   »
    /// </summary>
    Cover: TTgInputFile;
    /// <summary>Start timestamp for the video in the message</summary>
    StartTimestamp: TTgOptional<Integer>;
    /// <summary>
    ///   Video caption (may also be used when resending videos by file_id), 0-1024 characters after
    ///   entities parsing
    /// </summary>
    Caption: TTgOptional<string>;
    /// <summary>
    ///   Mode for parsing entities in the video caption. See formatting options for more details.
    /// </summary>
    ParseMode: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized list of special entities that appear in the caption, which can be
    ///   specified instead of parse_mode Не задано — параметр не передаётся; [] — передаётся пустой
    ///   список.
    /// </summary>
    CaptionEntities: TTgOptional<TArray<ITgMessageEntity>>;
    /// <summary>Pass True if the caption must be shown above the message media</summary>
    ShowCaptionAboveMedia: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if the video needs to be covered with a spoiler animation
    /// </summary>
    HasSpoiler: TTgOptional<Boolean>;
    /// <summary>Pass True if the uploaded video is suitable for streaming</summary>
    SupportsStreaming: TTgOptional<Boolean>;
    /// <summary>
    ///   Sends the message silently. Users will receive a notification with no sound.
    /// </summary>
    DisableNotification: TTgOptional<Boolean>;
    /// <summary>
    ///   Protects the contents of the sent message from forwarding and saving
    /// </summary>
    ProtectContent: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to allow up to 1000 messages per second, ignoring broadcasting limits for a fee
    ///   of 0.1 Telegram Stars per message. The relevant Stars will be withdrawn from the bot's
    ///   balance.
    /// </summary>
    AllowPaidBroadcast: TTgOptional<Boolean>;
    /// <summary>
    ///   Unique identifier of the message effect to be added to the message; for private chats only
    /// </summary>
    MessageEffectId: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the suggested post to send; for
    ///   direct messages chats only. If the message is sent as a reply to another suggested post,
    ///   then that suggested post is automatically declined.
    /// </summary>
    SuggestedPostParameters: ITgSuggestedPostParameters;
    /// <summary>Description of the message to reply to</summary>
    ReplyParameters: ITgReplyParameters;
    /// <summary>
    ///   Additional interface options. A JSON-serialized object for an inline keyboard, custom
    ///   reply keyboard, instructions to remove a reply keyboard or to force a reply from the user.
    ///   Построитель: TTgKeyboard.Inline…, TTgKeyboard.Reply…, TTgKeyboard.Remove,
    ///   TTgKeyboard.ForceReply.
    /// </summary>
    ReplyMarkup: TTgReplyMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры sendAnimation. Неинициализированная запись пуста
  ///   (Default(TTgSendAnimationOptions)).
  /// </summary>
  TTgSendAnimationOptions = record
    /// <summary>
    ///   Unique identifier of the business connection on behalf of which the message will be sent
    /// </summary>
    BusinessConnectionId: TTgOptional<string>;
    /// <summary>
    ///   Unique identifier for the target message thread (topic) of a forum; for forum supergroups
    ///   and private chats of bots with forum topic mode enabled only
    /// </summary>
    MessageThreadId: TTgOptional<Int64>;
    /// <summary>
    ///   Identifier of the direct messages topic to which the message will be sent; required if the
    ///   message is sent to a direct messages chat
    /// </summary>
    DirectMessagesTopicId: TTgOptional<Int64>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the ephemeral message to send
    /// </summary>
    EphemeralMessageParameters: ITgEphemeralMessageParameters;
    /// <summary>Duration of sent animation in seconds</summary>
    Duration: TTgOptional<Integer>;
    /// <summary>Animation width</summary>
    Width: TTgOptional<Integer>;
    /// <summary>Animation height</summary>
    Height: TTgOptional<Integer>;
    /// <summary>
    ///   Thumbnail of the file sent; can be ignored if thumbnail generation for the file is
    ///   supported server-side. The thumbnail should be in JPEG format and less than 200 kB in
    ///   size. A thumbnail's width and height should not exceed 320. Ignored if the file is not
    ///   uploaded using multipart/form-data. Thumbnails can't be reused and can be only uploaded as
    ///   a new file, so you can pass “attach://&lt;file_attach_name&gt;” if the thumbnail was
    ///   uploaded using multipart/form-data under &lt;file_attach_name&gt;. More information on
    ///   Sending Files »
    /// </summary>
    Thumbnail: TTgInputFile;
    /// <summary>
    ///   Animation caption (may also be used when resending animation by file_id), 0-1024
    ///   characters after entities parsing
    /// </summary>
    Caption: TTgOptional<string>;
    /// <summary>
    ///   Mode for parsing entities in the animation caption. See formatting options for more
    ///   details.
    /// </summary>
    ParseMode: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized list of special entities that appear in the caption, which can be
    ///   specified instead of parse_mode Не задано — параметр не передаётся; [] — передаётся пустой
    ///   список.
    /// </summary>
    CaptionEntities: TTgOptional<TArray<ITgMessageEntity>>;
    /// <summary>Pass True if the caption must be shown above the message media</summary>
    ShowCaptionAboveMedia: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if the animation needs to be covered with a spoiler animation
    /// </summary>
    HasSpoiler: TTgOptional<Boolean>;
    /// <summary>
    ///   Sends the message silently. Users will receive a notification with no sound.
    /// </summary>
    DisableNotification: TTgOptional<Boolean>;
    /// <summary>
    ///   Protects the contents of the sent message from forwarding and saving
    /// </summary>
    ProtectContent: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to allow up to 1000 messages per second, ignoring broadcasting limits for a fee
    ///   of 0.1 Telegram Stars per message. The relevant Stars will be withdrawn from the bot's
    ///   balance.
    /// </summary>
    AllowPaidBroadcast: TTgOptional<Boolean>;
    /// <summary>
    ///   Unique identifier of the message effect to be added to the message; for private chats only
    /// </summary>
    MessageEffectId: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the suggested post to send; for
    ///   direct messages chats only. If the message is sent as a reply to another suggested post,
    ///   then that suggested post is automatically declined.
    /// </summary>
    SuggestedPostParameters: ITgSuggestedPostParameters;
    /// <summary>Description of the message to reply to</summary>
    ReplyParameters: ITgReplyParameters;
    /// <summary>
    ///   Additional interface options. A JSON-serialized object for an inline keyboard, custom
    ///   reply keyboard, instructions to remove a reply keyboard or to force a reply from the user.
    ///   Построитель: TTgKeyboard.Inline…, TTgKeyboard.Reply…, TTgKeyboard.Remove,
    ///   TTgKeyboard.ForceReply.
    /// </summary>
    ReplyMarkup: TTgReplyMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры sendVoice. Неинициализированная запись пуста
  ///   (Default(TTgSendVoiceOptions)).
  /// </summary>
  TTgSendVoiceOptions = record
    /// <summary>
    ///   Unique identifier of the business connection on behalf of which the message will be sent
    /// </summary>
    BusinessConnectionId: TTgOptional<string>;
    /// <summary>
    ///   Unique identifier for the target message thread (topic) of a forum; for forum supergroups
    ///   and private chats of bots with forum topic mode enabled only
    /// </summary>
    MessageThreadId: TTgOptional<Int64>;
    /// <summary>
    ///   Identifier of the direct messages topic to which the message will be sent; required if the
    ///   message is sent to a direct messages chat
    /// </summary>
    DirectMessagesTopicId: TTgOptional<Int64>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the ephemeral message to send
    /// </summary>
    EphemeralMessageParameters: ITgEphemeralMessageParameters;
    /// <summary>Voice message caption, 0-1024 characters after entities parsing</summary>
    Caption: TTgOptional<string>;
    /// <summary>
    ///   Mode for parsing entities in the voice message caption. See formatting options for more
    ///   details.
    /// </summary>
    ParseMode: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized list of special entities that appear in the caption, which can be
    ///   specified instead of parse_mode Не задано — параметр не передаётся; [] — передаётся пустой
    ///   список.
    /// </summary>
    CaptionEntities: TTgOptional<TArray<ITgMessageEntity>>;
    /// <summary>Duration of the voice message in seconds</summary>
    Duration: TTgOptional<Integer>;
    /// <summary>
    ///   Sends the message silently. Users will receive a notification with no sound.
    /// </summary>
    DisableNotification: TTgOptional<Boolean>;
    /// <summary>
    ///   Protects the contents of the sent message from forwarding and saving
    /// </summary>
    ProtectContent: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to allow up to 1000 messages per second, ignoring broadcasting limits for a fee
    ///   of 0.1 Telegram Stars per message. The relevant Stars will be withdrawn from the bot's
    ///   balance.
    /// </summary>
    AllowPaidBroadcast: TTgOptional<Boolean>;
    /// <summary>
    ///   Unique identifier of the message effect to be added to the message; for private chats only
    /// </summary>
    MessageEffectId: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the suggested post to send; for
    ///   direct messages chats only. If the message is sent as a reply to another suggested post,
    ///   then that suggested post is automatically declined.
    /// </summary>
    SuggestedPostParameters: ITgSuggestedPostParameters;
    /// <summary>Description of the message to reply to</summary>
    ReplyParameters: ITgReplyParameters;
    /// <summary>
    ///   Additional interface options. A JSON-serialized object for an inline keyboard, custom
    ///   reply keyboard, instructions to remove a reply keyboard or to force a reply from the user.
    ///   Построитель: TTgKeyboard.Inline…, TTgKeyboard.Reply…, TTgKeyboard.Remove,
    ///   TTgKeyboard.ForceReply.
    /// </summary>
    ReplyMarkup: TTgReplyMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры sendVideoNote. Неинициализированная запись пуста
  ///   (Default(TTgSendVideoNoteOptions)).
  /// </summary>
  TTgSendVideoNoteOptions = record
    /// <summary>
    ///   Unique identifier of the business connection on behalf of which the message will be sent
    /// </summary>
    BusinessConnectionId: TTgOptional<string>;
    /// <summary>
    ///   Unique identifier for the target message thread (topic) of a forum; for forum supergroups
    ///   and private chats of bots with forum topic mode enabled only
    /// </summary>
    MessageThreadId: TTgOptional<Int64>;
    /// <summary>
    ///   Identifier of the direct messages topic to which the message will be sent; required if the
    ///   message is sent to a direct messages chat
    /// </summary>
    DirectMessagesTopicId: TTgOptional<Int64>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the ephemeral message to send
    /// </summary>
    EphemeralMessageParameters: ITgEphemeralMessageParameters;
    /// <summary>Duration of sent video in seconds</summary>
    Duration: TTgOptional<Integer>;
    /// <summary>Video width and height, i.e. diameter of the video message</summary>
    Length: TTgOptional<Integer>;
    /// <summary>
    ///   Thumbnail of the file sent; can be ignored if thumbnail generation for the file is
    ///   supported server-side. The thumbnail should be in JPEG format and less than 200 kB in
    ///   size. A thumbnail's width and height should not exceed 320. Ignored if the file is not
    ///   uploaded using multipart/form-data. Thumbnails can't be reused and can be only uploaded as
    ///   a new file, so you can pass “attach://&lt;file_attach_name&gt;” if the thumbnail was
    ///   uploaded using multipart/form-data under &lt;file_attach_name&gt;. More information on
    ///   Sending Files »
    /// </summary>
    Thumbnail: TTgInputFile;
    /// <summary>
    ///   Sends the message silently. Users will receive a notification with no sound.
    /// </summary>
    DisableNotification: TTgOptional<Boolean>;
    /// <summary>
    ///   Protects the contents of the sent message from forwarding and saving
    /// </summary>
    ProtectContent: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to allow up to 1000 messages per second, ignoring broadcasting limits for a fee
    ///   of 0.1 Telegram Stars per message. The relevant Stars will be withdrawn from the bot's
    ///   balance.
    /// </summary>
    AllowPaidBroadcast: TTgOptional<Boolean>;
    /// <summary>
    ///   Unique identifier of the message effect to be added to the message; for private chats only
    /// </summary>
    MessageEffectId: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the suggested post to send; for
    ///   direct messages chats only. If the message is sent as a reply to another suggested post,
    ///   then that suggested post is automatically declined.
    /// </summary>
    SuggestedPostParameters: ITgSuggestedPostParameters;
    /// <summary>Description of the message to reply to</summary>
    ReplyParameters: ITgReplyParameters;
    /// <summary>
    ///   Additional interface options. A JSON-serialized object for an inline keyboard, custom
    ///   reply keyboard, instructions to remove a reply keyboard or to force a reply from the user.
    ///   Построитель: TTgKeyboard.Inline…, TTgKeyboard.Reply…, TTgKeyboard.Remove,
    ///   TTgKeyboard.ForceReply.
    /// </summary>
    ReplyMarkup: TTgReplyMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры sendPaidMedia. Неинициализированная запись пуста
  ///   (Default(TTgSendPaidMediaOptions)).
  /// </summary>
  TTgSendPaidMediaOptions = record
    /// <summary>
    ///   Unique identifier of the business connection on behalf of which the message will be sent
    /// </summary>
    BusinessConnectionId: TTgOptional<string>;
    /// <summary>
    ///   Unique identifier for the target message thread (topic) of a forum; for forum supergroups
    ///   and private chats of bots with forum topic mode enabled only
    /// </summary>
    MessageThreadId: TTgOptional<Int64>;
    /// <summary>
    ///   Identifier of the direct messages topic to which the message will be sent; required if the
    ///   message is sent to a direct messages chat
    /// </summary>
    DirectMessagesTopicId: TTgOptional<Int64>;
    /// <summary>
    ///   Bot-defined paid media payload, 0-128 bytes. This will not be displayed to the user, use
    ///   it for your internal processes.
    /// </summary>
    Payload: TTgOptional<string>;
    /// <summary>Media caption, 0-1024 characters after entities parsing</summary>
    Caption: TTgOptional<string>;
    /// <summary>
    ///   Mode for parsing entities in the media caption. See formatting options for more details.
    /// </summary>
    ParseMode: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized list of special entities that appear in the caption, which can be
    ///   specified instead of parse_mode Не задано — параметр не передаётся; [] — передаётся пустой
    ///   список.
    /// </summary>
    CaptionEntities: TTgOptional<TArray<ITgMessageEntity>>;
    /// <summary>Pass True if the caption must be shown above the message media</summary>
    ShowCaptionAboveMedia: TTgOptional<Boolean>;
    /// <summary>
    ///   Sends the message silently. Users will receive a notification with no sound.
    /// </summary>
    DisableNotification: TTgOptional<Boolean>;
    /// <summary>
    ///   Protects the contents of the sent message from forwarding and saving
    /// </summary>
    ProtectContent: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to allow up to 1000 messages per second, ignoring broadcasting limits for a fee
    ///   of 0.1 Telegram Stars per message. The relevant Stars will be withdrawn from the bot's
    ///   balance.
    /// </summary>
    AllowPaidBroadcast: TTgOptional<Boolean>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the suggested post to send; for
    ///   direct messages chats only. If the message is sent as a reply to another suggested post,
    ///   then that suggested post is automatically declined.
    /// </summary>
    SuggestedPostParameters: ITgSuggestedPostParameters;
    /// <summary>Description of the message to reply to</summary>
    ReplyParameters: ITgReplyParameters;
    /// <summary>
    ///   Additional interface options. A JSON-serialized object for an inline keyboard, custom
    ///   reply keyboard, instructions to remove a reply keyboard or to force a reply from the user.
    ///   Построитель: TTgKeyboard.Inline…, TTgKeyboard.Reply…, TTgKeyboard.Remove,
    ///   TTgKeyboard.ForceReply.
    /// </summary>
    ReplyMarkup: TTgReplyMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры sendMediaGroup. Неинициализированная запись пуста
  ///   (Default(TTgSendMediaGroupOptions)).
  /// </summary>
  TTgSendMediaGroupOptions = record
    /// <summary>
    ///   Unique identifier of the business connection on behalf of which the message will be sent
    /// </summary>
    BusinessConnectionId: TTgOptional<string>;
    /// <summary>
    ///   Unique identifier for the target message thread (topic) of a forum; for forum supergroups
    ///   and private chats of bots with forum topic mode enabled only
    /// </summary>
    MessageThreadId: TTgOptional<Int64>;
    /// <summary>
    ///   Identifier of the direct messages topic to which the messages will be sent; required if
    ///   the messages are sent to a direct messages chat
    /// </summary>
    DirectMessagesTopicId: TTgOptional<Int64>;
    /// <summary>
    ///   Sends messages silently. Users will receive a notification with no sound.
    /// </summary>
    DisableNotification: TTgOptional<Boolean>;
    /// <summary>
    ///   Protects the contents of the sent messages from forwarding and saving
    /// </summary>
    ProtectContent: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to allow up to 1000 messages per second, ignoring broadcasting limits for a fee
    ///   of 0.1 Telegram Stars per message. The relevant Stars will be withdrawn from the bot's
    ///   balance.
    /// </summary>
    AllowPaidBroadcast: TTgOptional<Boolean>;
    /// <summary>
    ///   Unique identifier of the message effect to be added to the message; for private chats only
    /// </summary>
    MessageEffectId: TTgOptional<string>;
    /// <summary>Description of the message to reply to</summary>
    ReplyParameters: ITgReplyParameters;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры sendLocation. Неинициализированная запись пуста
  ///   (Default(TTgSendLocationOptions)).
  /// </summary>
  TTgSendLocationOptions = record
    /// <summary>
    ///   Unique identifier of the business connection on behalf of which the message will be sent
    /// </summary>
    BusinessConnectionId: TTgOptional<string>;
    /// <summary>
    ///   Unique identifier for the target message thread (topic) of a forum; for forum supergroups
    ///   and private chats of bots with forum topic mode enabled only
    /// </summary>
    MessageThreadId: TTgOptional<Int64>;
    /// <summary>
    ///   Identifier of the direct messages topic to which the message will be sent; required if the
    ///   message is sent to a direct messages chat
    /// </summary>
    DirectMessagesTopicId: TTgOptional<Int64>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the ephemeral message to send
    /// </summary>
    EphemeralMessageParameters: ITgEphemeralMessageParameters;
    /// <summary>
    ///   The radius of uncertainty for the location, measured in meters; 0-1500
    /// </summary>
    HorizontalAccuracy: TTgOptional<Double>;
    /// <summary>
    ///   Period in seconds during which the location will be updated (see Live Locations), must be
    ///   between 60 and 86400, or 0x7FFFFFFF for live locations that can be edited indefinitely.
    ///   Must be 0 for ephemeral messages.
    /// </summary>
    LivePeriod: TTgOptional<Integer>;
    /// <summary>
    ///   For live locations, a direction in which the user is moving, in degrees. Must be between 1
    ///   and 360 if specified.
    /// </summary>
    Heading: TTgOptional<Integer>;
    /// <summary>
    ///   For live locations, a maximum distance for proximity alerts about approaching another chat
    ///   member, in meters. Must be between 1 and 100000 if specified.
    /// </summary>
    ProximityAlertRadius: TTgOptional<Integer>;
    /// <summary>
    ///   Sends the message silently. Users will receive a notification with no sound.
    /// </summary>
    DisableNotification: TTgOptional<Boolean>;
    /// <summary>
    ///   Protects the contents of the sent message from forwarding and saving
    /// </summary>
    ProtectContent: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to allow up to 1000 messages per second, ignoring broadcasting limits for a fee
    ///   of 0.1 Telegram Stars per message. The relevant Stars will be withdrawn from the bot's
    ///   balance.
    /// </summary>
    AllowPaidBroadcast: TTgOptional<Boolean>;
    /// <summary>
    ///   Unique identifier of the message effect to be added to the message; for private chats only
    /// </summary>
    MessageEffectId: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the suggested post to send; for
    ///   direct messages chats only. If the message is sent as a reply to another suggested post,
    ///   then that suggested post is automatically declined.
    /// </summary>
    SuggestedPostParameters: ITgSuggestedPostParameters;
    /// <summary>Description of the message to reply to</summary>
    ReplyParameters: ITgReplyParameters;
    /// <summary>
    ///   Additional interface options. A JSON-serialized object for an inline keyboard, custom
    ///   reply keyboard, instructions to remove a reply keyboard or to force a reply from the user.
    ///   Построитель: TTgKeyboard.Inline…, TTgKeyboard.Reply…, TTgKeyboard.Remove,
    ///   TTgKeyboard.ForceReply.
    /// </summary>
    ReplyMarkup: TTgReplyMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры sendVenue. Неинициализированная запись пуста
  ///   (Default(TTgSendVenueOptions)).
  /// </summary>
  TTgSendVenueOptions = record
    /// <summary>
    ///   Unique identifier of the business connection on behalf of which the message will be sent
    /// </summary>
    BusinessConnectionId: TTgOptional<string>;
    /// <summary>
    ///   Unique identifier for the target message thread (topic) of a forum; for forum supergroups
    ///   and private chats of bots with forum topic mode enabled only
    /// </summary>
    MessageThreadId: TTgOptional<Int64>;
    /// <summary>
    ///   Identifier of the direct messages topic to which the message will be sent; required if the
    ///   message is sent to a direct messages chat
    /// </summary>
    DirectMessagesTopicId: TTgOptional<Int64>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the ephemeral message to send
    /// </summary>
    EphemeralMessageParameters: ITgEphemeralMessageParameters;
    /// <summary>Foursquare identifier of the venue</summary>
    FoursquareId: TTgOptional<string>;
    /// <summary>
    ///   Foursquare type of the venue, if known. (For example, “arts_entertainment/default”,
    ///   “arts_entertainment/aquarium” or “food/icecream”.)
    /// </summary>
    FoursquareType: TTgOptional<string>;
    /// <summary>Google Places identifier of the venue</summary>
    GooglePlaceId: TTgOptional<string>;
    /// <summary>Google Places type of the venue. (See supported types.)</summary>
    GooglePlaceType: TTgOptional<string>;
    /// <summary>
    ///   Sends the message silently. Users will receive a notification with no sound.
    /// </summary>
    DisableNotification: TTgOptional<Boolean>;
    /// <summary>
    ///   Protects the contents of the sent message from forwarding and saving
    /// </summary>
    ProtectContent: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to allow up to 1000 messages per second, ignoring broadcasting limits for a fee
    ///   of 0.1 Telegram Stars per message. The relevant Stars will be withdrawn from the bot's
    ///   balance.
    /// </summary>
    AllowPaidBroadcast: TTgOptional<Boolean>;
    /// <summary>
    ///   Unique identifier of the message effect to be added to the message; for private chats only
    /// </summary>
    MessageEffectId: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the suggested post to send; for
    ///   direct messages chats only. If the message is sent as a reply to another suggested post,
    ///   then that suggested post is automatically declined.
    /// </summary>
    SuggestedPostParameters: ITgSuggestedPostParameters;
    /// <summary>Description of the message to reply to</summary>
    ReplyParameters: ITgReplyParameters;
    /// <summary>
    ///   Additional interface options. A JSON-serialized object for an inline keyboard, custom
    ///   reply keyboard, instructions to remove a reply keyboard or to force a reply from the user.
    ///   Построитель: TTgKeyboard.Inline…, TTgKeyboard.Reply…, TTgKeyboard.Remove,
    ///   TTgKeyboard.ForceReply.
    /// </summary>
    ReplyMarkup: TTgReplyMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры sendContact. Неинициализированная запись пуста
  ///   (Default(TTgSendContactOptions)).
  /// </summary>
  TTgSendContactOptions = record
    /// <summary>
    ///   Unique identifier of the business connection on behalf of which the message will be sent
    /// </summary>
    BusinessConnectionId: TTgOptional<string>;
    /// <summary>
    ///   Unique identifier for the target message thread (topic) of a forum; for forum supergroups
    ///   and private chats of bots with forum topic mode enabled only
    /// </summary>
    MessageThreadId: TTgOptional<Int64>;
    /// <summary>
    ///   Identifier of the direct messages topic to which the message will be sent; required if the
    ///   message is sent to a direct messages chat
    /// </summary>
    DirectMessagesTopicId: TTgOptional<Int64>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the ephemeral message to send
    /// </summary>
    EphemeralMessageParameters: ITgEphemeralMessageParameters;
    /// <summary>Contact's last name</summary>
    LastName: TTgOptional<string>;
    /// <summary>
    ///   Additional data about the contact in the form of a vCard, 0-2048 bytes
    /// </summary>
    Vcard: TTgOptional<string>;
    /// <summary>
    ///   Sends the message silently. Users will receive a notification with no sound.
    /// </summary>
    DisableNotification: TTgOptional<Boolean>;
    /// <summary>
    ///   Protects the contents of the sent message from forwarding and saving
    /// </summary>
    ProtectContent: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to allow up to 1000 messages per second, ignoring broadcasting limits for a fee
    ///   of 0.1 Telegram Stars per message. The relevant Stars will be withdrawn from the bot's
    ///   balance.
    /// </summary>
    AllowPaidBroadcast: TTgOptional<Boolean>;
    /// <summary>
    ///   Unique identifier of the message effect to be added to the message; for private chats only
    /// </summary>
    MessageEffectId: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the suggested post to send; for
    ///   direct messages chats only. If the message is sent as a reply to another suggested post,
    ///   then that suggested post is automatically declined.
    /// </summary>
    SuggestedPostParameters: ITgSuggestedPostParameters;
    /// <summary>Description of the message to reply to</summary>
    ReplyParameters: ITgReplyParameters;
    /// <summary>
    ///   Additional interface options. A JSON-serialized object for an inline keyboard, custom
    ///   reply keyboard, instructions to remove a reply keyboard or to force a reply from the user.
    ///   Построитель: TTgKeyboard.Inline…, TTgKeyboard.Reply…, TTgKeyboard.Remove,
    ///   TTgKeyboard.ForceReply.
    /// </summary>
    ReplyMarkup: TTgReplyMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры sendPoll. Неинициализированная запись пуста
  ///   (Default(TTgSendPollOptions)).
  /// </summary>
  TTgSendPollOptions = record
    /// <summary>
    ///   Unique identifier of the business connection on behalf of which the message will be sent
    /// </summary>
    BusinessConnectionId: TTgOptional<string>;
    /// <summary>
    ///   Unique identifier for the target message thread (topic) of a forum; for forum supergroups
    ///   and private chats of bots with forum topic mode enabled only
    /// </summary>
    MessageThreadId: TTgOptional<Int64>;
    /// <summary>
    ///   Mode for parsing entities in the question. See formatting options for more details.
    ///   Currently, only custom emoji entities are allowed.
    /// </summary>
    QuestionParseMode: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized list of special entities that appear in the poll question. It can be
    ///   specified instead of question_parse_mode. Не задано — параметр не передаётся; [] —
    ///   передаётся пустой список.
    /// </summary>
    QuestionEntities: TTgOptional<TArray<ITgMessageEntity>>;
    /// <summary>True, if the poll needs to be anonymous, defaults to True</summary>
    IsAnonymous: TTgOptional<Boolean>;
    /// <summary>Poll type, “quiz” or “regular”, defaults to “regular”</summary>
    PollType: TTgOptional<string>;
    /// <summary>Pass True if the poll allows multiple answers, defaults to False</summary>
    AllowsMultipleAnswers: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if the poll allows to change chosen answer options, defaults to False for
    ///   quizzes and to True for regular polls
    /// </summary>
    AllowsRevoting: TTgOptional<Boolean>;
    /// <summary>Pass True if the poll options must be shown in random order</summary>
    ShuffleOptions: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if answer options can be added to the poll after creation; not supported for
    ///   anonymous polls and quizzes
    /// </summary>
    AllowAddingOptions: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if poll results must be shown only after the poll closes
    /// </summary>
    HideResultsUntilCloses: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if voting is limited to users who have been members of the chat where the poll
    ///   is being sent for more than 24 hours; for channel chats only
    /// </summary>
    MembersOnly: TTgOptional<Boolean>;
    /// <summary>
    ///   A JSON-serialized list of 0-12 two-letter ISO 3166-1 alpha-2 country codes indicating the
    ///   countries from which users can vote in the poll; for channel chats only. Use “FT” as a
    ///   country code to allow users with anonymous numbers to vote. If omitted or empty, then
    ///   users from any country can participate in the poll. Не задано — параметр не передаётся; []
    ///   — передаётся пустой список.
    /// </summary>
    CountryCodes: TTgOptional<TArray<string>>;
    /// <summary>
    ///   A JSON-serialized list of monotonically increasing 0-based identifiers of the correct
    ///   answer options, required for polls in quiz mode Не задано — параметр не передаётся; [] —
    ///   передаётся пустой список.
    /// </summary>
    CorrectOptionIds: TTgOptional<TArray<Int64>>;
    /// <summary>
    ///   Text that is shown when a user chooses an incorrect answer or taps on the lamp icon in a
    ///   quiz-style poll, 0-200 characters with at most 2 line feeds after entities parsing
    /// </summary>
    Explanation: TTgOptional<string>;
    /// <summary>
    ///   Mode for parsing entities in the explanation. See formatting options for more details.
    /// </summary>
    ExplanationParseMode: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized list of special entities that appear in the poll explanation. It can be
    ///   specified instead of explanation_parse_mode. Не задано — параметр не передаётся; [] —
    ///   передаётся пустой список.
    /// </summary>
    ExplanationEntities: TTgOptional<TArray<ITgMessageEntity>>;
    /// <summary>Media added to the quiz explanation</summary>
    ExplanationMedia: TTgInputPollMedia;
    /// <summary>
    ///   Amount of time in seconds the poll will be active after creation, 5-2628000. Can't be used
    ///   together with close_date.
    /// </summary>
    OpenPeriod: TTgOptional<Integer>;
    /// <summary>
    ///   Point in time (Unix timestamp) when the poll will be automatically closed. Must be at
    ///   least 5 and no more than 2628000 seconds in the future. Can't be used together with
    ///   open_period.
    /// </summary>
    CloseDate: TTgOptional<Int64>;
    /// <summary>
    ///   Pass True if the poll needs to be immediately closed. This can be useful for poll preview.
    /// </summary>
    IsClosed: TTgOptional<Boolean>;
    /// <summary>
    ///   Description of the poll to be sent, 0-1024 characters after entities parsing
    /// </summary>
    Description: TTgOptional<string>;
    /// <summary>
    ///   Mode for parsing entities in the poll description. See formatting options for more
    ///   details.
    /// </summary>
    DescriptionParseMode: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized list of special entities that appear in the poll description, which can
    ///   be specified instead of description_parse_mode Не задано — параметр не передаётся; [] —
    ///   передаётся пустой список.
    /// </summary>
    DescriptionEntities: TTgOptional<TArray<ITgMessageEntity>>;
    /// <summary>Media added to the poll description</summary>
    Media: TTgInputPollMedia;
    /// <summary>
    ///   Sends the message silently. Users will receive a notification with no sound.
    /// </summary>
    DisableNotification: TTgOptional<Boolean>;
    /// <summary>
    ///   Protects the contents of the sent message from forwarding and saving
    /// </summary>
    ProtectContent: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to allow up to 1000 messages per second, ignoring broadcasting limits for a fee
    ///   of 0.1 Telegram Stars per message. The relevant Stars will be withdrawn from the bot's
    ///   balance.
    /// </summary>
    AllowPaidBroadcast: TTgOptional<Boolean>;
    /// <summary>
    ///   Unique identifier of the message effect to be added to the message; for private chats only
    /// </summary>
    MessageEffectId: TTgOptional<string>;
    /// <summary>Description of the message to reply to</summary>
    ReplyParameters: ITgReplyParameters;
    /// <summary>
    ///   Additional interface options. A JSON-serialized object for an inline keyboard, custom
    ///   reply keyboard, instructions to remove a reply keyboard or to force a reply from the user.
    ///   Построитель: TTgKeyboard.Inline…, TTgKeyboard.Reply…, TTgKeyboard.Remove,
    ///   TTgKeyboard.ForceReply.
    /// </summary>
    ReplyMarkup: TTgReplyMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры sendChecklist. Неинициализированная запись пуста
  ///   (Default(TTgSendChecklistOptions)).
  /// </summary>
  TTgSendChecklistOptions = record
    /// <summary>
    ///   Sends the message silently. Users will receive a notification with no sound.
    /// </summary>
    DisableNotification: TTgOptional<Boolean>;
    /// <summary>
    ///   Protects the contents of the sent message from forwarding and saving
    /// </summary>
    ProtectContent: TTgOptional<Boolean>;
    /// <summary>
    ///   Unique identifier of the message effect to be added to the message
    /// </summary>
    MessageEffectId: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized object for description of the message to reply to
    /// </summary>
    ReplyParameters: ITgReplyParameters;
    /// <summary>
    ///   A JSON-serialized object for an inline keyboard. Только инлайн-клавиатура
    ///   (ITgInlineKeyboardMarkup): TTgKeyboard.Inline.Row.Button(…) или
    ///   TTgInlineKeyboardMarkup.Create; обычная клавиатура, Remove и ForceReply здесь не
    ///   принимаются.
    /// </summary>
    ReplyMarkup: ITgInlineKeyboardMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры sendDice. Неинициализированная запись пуста
  ///   (Default(TTgSendDiceOptions)).
  /// </summary>
  TTgSendDiceOptions = record
    /// <summary>
    ///   Unique identifier of the business connection on behalf of which the message will be sent
    /// </summary>
    BusinessConnectionId: TTgOptional<string>;
    /// <summary>
    ///   Unique identifier for the target message thread (topic) of a forum; for forum supergroups
    ///   and private chats of bots with forum topic mode enabled only
    /// </summary>
    MessageThreadId: TTgOptional<Int64>;
    /// <summary>
    ///   Identifier of the direct messages topic to which the message will be sent; required if the
    ///   message is sent to a direct messages chat
    /// </summary>
    DirectMessagesTopicId: TTgOptional<Int64>;
    /// <summary>
    ///   Emoji on which the dice throw animation is based. Currently, must be one of “🎲”, “🎯”,
    ///   “🏀”, “⚽”, “🎳”, or “🎰”. Dice can have values 1-6 for “🎲”, “🎯” and “🎳”, values 1-5 for
    ///   “🏀” and “⚽”, and values 1-64 for “🎰”. Defaults to “🎲”.
    /// </summary>
    Emoji: TTgOptional<string>;
    /// <summary>
    ///   Sends the message silently. Users will receive a notification with no sound.
    /// </summary>
    DisableNotification: TTgOptional<Boolean>;
    /// <summary>Protects the contents of the sent message from forwarding</summary>
    ProtectContent: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to allow up to 1000 messages per second, ignoring broadcasting limits for a fee
    ///   of 0.1 Telegram Stars per message. The relevant Stars will be withdrawn from the bot's
    ///   balance.
    /// </summary>
    AllowPaidBroadcast: TTgOptional<Boolean>;
    /// <summary>
    ///   Unique identifier of the message effect to be added to the message; for private chats only
    /// </summary>
    MessageEffectId: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the suggested post to send; for
    ///   direct messages chats only. If the message is sent as a reply to another suggested post,
    ///   then that suggested post is automatically declined.
    /// </summary>
    SuggestedPostParameters: ITgSuggestedPostParameters;
    /// <summary>Description of the message to reply to</summary>
    ReplyParameters: ITgReplyParameters;
    /// <summary>
    ///   Additional interface options. A JSON-serialized object for an inline keyboard, custom
    ///   reply keyboard, instructions to remove a reply keyboard or to force a reply from the user.
    ///   Построитель: TTgKeyboard.Inline…, TTgKeyboard.Reply…, TTgKeyboard.Remove,
    ///   TTgKeyboard.ForceReply.
    /// </summary>
    ReplyMarkup: TTgReplyMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры sendMessageDraft. Неинициализированная запись пуста
  ///   (Default(TTgSendMessageDraftOptions)).
  /// </summary>
  TTgSendMessageDraftOptions = record
    /// <summary>Unique identifier for the target message thread</summary>
    MessageThreadId: TTgOptional<Int64>;
    /// <summary>
    ///   Text of the message to be sent, 0-4096 characters after entities parsing. Pass an empty
    ///   text to show a “Thinking…” placeholder.
    /// </summary>
    Text: TTgOptional<string>;
    /// <summary>
    ///   Mode for parsing entities in the message text. See formatting options for more details.
    /// </summary>
    ParseMode: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized list of special entities that appear in message text, which can be
    ///   specified instead of parse_mode Не задано — параметр не передаётся; [] — передаётся пустой
    ///   список.
    /// </summary>
    Entities: TTgOptional<TArray<ITgMessageEntity>>;
    /// <summary>
    ///   Pass True to show the user a button to stop further drafts. The bot will receive an Update
    ///   “stopped_message_generation” if the user presses the button.
    /// </summary>
    CanStop: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to keep the draft in the chat when the button is pressed. The draft will still
    ///   disappear after a short time or if the bot sends a message. To fully preserve the partial
    ///   draft, the bot should send it as a new message.
    /// </summary>
    KeepOnStop: TTgOptional<Boolean>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры sendChatAction. Неинициализированная запись пуста
  ///   (Default(TTgSendChatActionOptions)).
  /// </summary>
  TTgSendChatActionOptions = record
    /// <summary>
    ///   Unique identifier of the business connection on behalf of which the action will be sent
    /// </summary>
    BusinessConnectionId: TTgOptional<string>;
    /// <summary>
    ///   Unique identifier for the target message thread or topic of a forum; for supergroups and
    ///   private chats of bots with forum topic mode enabled only
    /// </summary>
    MessageThreadId: TTgOptional<Int64>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры setMessageReaction. Неинициализированная запись пуста
  ///   (Default(TTgSetMessageReactionOptions)).
  /// </summary>
  TTgSetMessageReactionOptions = record
    /// <summary>
    ///   A JSON-serialized list of reaction types to set on the message. Currently, as non-premium
    ///   users, bots can set up to one reaction per message. A custom emoji reaction can be used if
    ///   it is either already present on the message or explicitly allowed by chat administrators.
    ///   Paid reactions can't be used by bots. Не задано — параметр не передаётся; [] — передаётся
    ///   пустой список. Элементы приводите к ITgReactionType: [ITgReactionType(A),
    ///   ITgReactionType(B)] или TArray&lt;ITgReactionType&gt;.Create(A, B).
    /// </summary>
    Reaction: TTgOptional<TArray<ITgReactionType>>;
    /// <summary>Pass True to set the reaction with a big animation</summary>
    IsBig: TTgOptional<Boolean>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры getUserProfilePhotos. Неинициализированная запись пуста
  ///   (Default(TTgGetUserProfilePhotosOptions)).
  /// </summary>
  TTgGetUserProfilePhotosOptions = record
    /// <summary>
    ///   Sequential number of the first photo to be returned. By default, all photos are returned.
    /// </summary>
    Offset: TTgOptional<Integer>;
    /// <summary>
    ///   Limits the number of photos to be retrieved. Values between 1-100 are accepted. Defaults
    ///   to 100.
    /// </summary>
    Limit: TTgOptional<Integer>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры getUserProfileAudios. Неинициализированная запись пуста
  ///   (Default(TTgGetUserProfileAudiosOptions)).
  /// </summary>
  TTgGetUserProfileAudiosOptions = record
    /// <summary>
    ///   Sequential number of the first audio to be returned. By default, all audios are returned.
    /// </summary>
    Offset: TTgOptional<Integer>;
    /// <summary>
    ///   Limits the number of audios to be retrieved. Values between 1-100 are accepted. Defaults
    ///   to 100.
    /// </summary>
    Limit: TTgOptional<Integer>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры setUserEmojiStatus. Неинициализированная запись пуста
  ///   (Default(TTgSetUserEmojiStatusOptions)).
  /// </summary>
  TTgSetUserEmojiStatusOptions = record
    /// <summary>
    ///   Custom emoji identifier of the emoji status to set. Pass an empty string to remove the
    ///   status.
    /// </summary>
    EmojiStatusCustomEmojiId: TTgOptional<string>;
    /// <summary>Expiration date of the emoji status, if any</summary>
    EmojiStatusExpirationDate: TTgOptional<Int64>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры banChatMember. Неинициализированная запись пуста
  ///   (Default(TTgBanChatMemberOptions)).
  /// </summary>
  TTgBanChatMemberOptions = record
    /// <summary>
    ///   Date when the user will be unbanned; Unix time. If user is banned for more than 366 days
    ///   or less than 30 seconds from the current time they are considered to be banned forever.
    ///   Applied for supergroups and channels only.
    /// </summary>
    UntilDate: TTgOptional<Int64>;
    /// <summary>
    ///   Pass True to delete all messages from the chat for the user that is being removed. If
    ///   False, the user will be able to see messages in the group that were sent before the user
    ///   was removed. Always True for supergroups and channels.
    /// </summary>
    RevokeMessages: TTgOptional<Boolean>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры unbanChatMember. Неинициализированная запись пуста
  ///   (Default(TTgUnbanChatMemberOptions)).
  /// </summary>
  TTgUnbanChatMemberOptions = record
    /// <summary>Do nothing if the user is not banned</summary>
    OnlyIfBanned: TTgOptional<Boolean>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры restrictChatMember. Неинициализированная запись пуста
  ///   (Default(TTgRestrictChatMemberOptions)).
  /// </summary>
  TTgRestrictChatMemberOptions = record
    /// <summary>
    ///   Pass True if chat permissions are set independently. Otherwise, the
    ///   can_send_other_messages and can_add_web_page_previews permissions will imply the
    ///   can_send_messages, can_send_audios, can_send_documents, can_send_photos, can_send_videos,
    ///   can_send_video_notes, and can_send_voice_notes permissions; the can_send_polls permission
    ///   will imply the can_send_messages permission.
    /// </summary>
    UseIndependentChatPermissions: TTgOptional<Boolean>;
    /// <summary>
    ///   Date when restrictions will be lifted for the user; Unix time. If user is restricted for
    ///   more than 366 days or less than 30 seconds from the current time, they are considered to
    ///   be restricted forever.
    /// </summary>
    UntilDate: TTgOptional<Int64>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры promoteChatMember. Неинициализированная запись пуста
  ///   (Default(TTgPromoteChatMemberOptions)).
  /// </summary>
  TTgPromoteChatMemberOptions = record
    /// <summary>Pass True if the administrator's presence in the chat is hidden</summary>
    IsAnonymous: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if the administrator can access the chat event log, get boost list, see hidden
    ///   supergroup and channel members, report spam messages, ignore slow mode, and send messages
    ///   to the chat without paying Telegram Stars. Implied by any other administrator privilege.
    /// </summary>
    CanManageChat: TTgOptional<Boolean>;
    /// <summary>Pass True if the administrator can delete messages of other users</summary>
    CanDeleteMessages: TTgOptional<Boolean>;
    /// <summary>Pass True if the administrator can manage video chats</summary>
    CanManageVideoChats: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if the administrator can restrict, ban or unban chat members, or access
    ///   supergroup statistics. For backward compatibility, defaults to True for promotions of
    ///   channel administrators.
    /// </summary>
    CanRestrictMembers: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if the administrator can add new administrators with a subset of their own
    ///   privileges or demote administrators that they have promoted, directly or indirectly
    ///   (promoted by administrators that were appointed by him)
    /// </summary>
    CanPromoteMembers: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if the administrator can change chat title, photo and other settings
    /// </summary>
    CanChangeInfo: TTgOptional<Boolean>;
    /// <summary>Pass True if the administrator can invite new users to the chat</summary>
    CanInviteUsers: TTgOptional<Boolean>;
    /// <summary>Pass True if the administrator can post stories to the chat</summary>
    CanPostStories: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if the administrator can edit stories posted by other users, post stories to the
    ///   chat page, pin chat stories, and access the chat's story archive
    /// </summary>
    CanEditStories: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if the administrator can delete stories posted by other users
    /// </summary>
    CanDeleteStories: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if the administrator can post messages in the channel, approve suggested posts,
    ///   or access channel statistics; for channels only
    /// </summary>
    CanPostMessages: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if the administrator can edit messages of other users and can pin messages; for
    ///   channels only
    /// </summary>
    CanEditMessages: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if the administrator can pin messages; for supergroups only
    /// </summary>
    CanPinMessages: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if the user is allowed to create, rename, close, and reopen forum topics; for
    ///   supergroups only
    /// </summary>
    CanManageTopics: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if the administrator can manage direct messages within the channel and decline
    ///   suggested posts; for channels only
    /// </summary>
    CanManageDirectMessages: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if the administrator can edit the tags of regular members; for groups and
    ///   supergroups only
    /// </summary>
    CanManageTags: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if the administrator can manage chat welcome messages or directly send them in
    ///   the case of bots
    /// </summary>
    CanSendWelcomeMessages: TTgOptional<Boolean>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры setChatMemberTag. Неинициализированная запись пуста
  ///   (Default(TTgSetChatMemberTagOptions)).
  /// </summary>
  TTgSetChatMemberTagOptions = record
    /// <summary>New tag for the member; 0-16 characters, emoji are not allowed</summary>
    Tag: TTgOptional<string>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры setChatPermissions. Неинициализированная запись пуста
  ///   (Default(TTgSetChatPermissionsOptions)).
  /// </summary>
  TTgSetChatPermissionsOptions = record
    /// <summary>
    ///   Pass True if chat permissions are set independently. Otherwise, the
    ///   can_send_other_messages and can_add_web_page_previews permissions will imply the
    ///   can_send_messages, can_send_audios, can_send_documents, can_send_photos, can_send_videos,
    ///   can_send_video_notes, and can_send_voice_notes permissions; the can_send_polls permission
    ///   will imply the can_send_messages permission.
    /// </summary>
    UseIndependentChatPermissions: TTgOptional<Boolean>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры createChatInviteLink. Неинициализированная запись пуста
  ///   (Default(TTgCreateChatInviteLinkOptions)).
  /// </summary>
  TTgCreateChatInviteLinkOptions = record
    /// <summary>Invite link name; 0-32 characters</summary>
    Name: TTgOptional<string>;
    /// <summary>Point in time (Unix timestamp) when the link will expire</summary>
    ExpireDate: TTgOptional<Int64>;
    /// <summary>
    ///   The maximum number of users that can be members of the chat simultaneously after joining
    ///   the chat via this invite link; 1-99999
    /// </summary>
    MemberLimit: TTgOptional<Integer>;
    /// <summary>
    ///   True, if users joining the chat via the link need to be approved by chat administrators.
    ///   If True, member_limit can't be specified.
    /// </summary>
    CreatesJoinRequest: TTgOptional<Boolean>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры editChatInviteLink. Неинициализированная запись пуста
  ///   (Default(TTgEditChatInviteLinkOptions)).
  /// </summary>
  TTgEditChatInviteLinkOptions = record
    /// <summary>Invite link name; 0-32 characters</summary>
    Name: TTgOptional<string>;
    /// <summary>Point in time (Unix timestamp) when the link will expire</summary>
    ExpireDate: TTgOptional<Int64>;
    /// <summary>
    ///   The maximum number of users that can be members of the chat simultaneously after joining
    ///   the chat via this invite link; 1-99999
    /// </summary>
    MemberLimit: TTgOptional<Integer>;
    /// <summary>
    ///   True, if users joining the chat via the link need to be approved by chat administrators.
    ///   If True, member_limit can't be specified.
    /// </summary>
    CreatesJoinRequest: TTgOptional<Boolean>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры createChatSubscriptionInviteLink. Неинициализированная запись пуста
  ///   (Default(TTgCreateChatSubscriptionInviteLinkOptions)).
  /// </summary>
  TTgCreateChatSubscriptionInviteLinkOptions = record
    /// <summary>Invite link name; 0-32 characters</summary>
    Name: TTgOptional<string>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры editChatSubscriptionInviteLink. Неинициализированная запись пуста
  ///   (Default(TTgEditChatSubscriptionInviteLinkOptions)).
  /// </summary>
  TTgEditChatSubscriptionInviteLinkOptions = record
    /// <summary>Invite link name; 0-32 characters</summary>
    Name: TTgOptional<string>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры setChatDescription. Неинициализированная запись пуста
  ///   (Default(TTgSetChatDescriptionOptions)).
  /// </summary>
  TTgSetChatDescriptionOptions = record
    /// <summary>New chat description, 0-255 characters</summary>
    Description: TTgOptional<string>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры pinChatMessage. Неинициализированная запись пуста
  ///   (Default(TTgPinChatMessageOptions)).
  /// </summary>
  TTgPinChatMessageOptions = record
    /// <summary>
    ///   Unique identifier of the business connection on behalf of which the message will be pinned
    /// </summary>
    BusinessConnectionId: TTgOptional<string>;
    /// <summary>
    ///   Pass True if it is not necessary to send a notification to all chat members about the new
    ///   pinned message. Notifications are always disabled in channels and private chats.
    /// </summary>
    DisableNotification: TTgOptional<Boolean>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры unpinChatMessage. Неинициализированная запись пуста
  ///   (Default(TTgUnpinChatMessageOptions)).
  /// </summary>
  TTgUnpinChatMessageOptions = record
    /// <summary>
    ///   Unique identifier of the business connection on behalf of which the message will be
    ///   unpinned
    /// </summary>
    BusinessConnectionId: TTgOptional<string>;
    /// <summary>
    ///   Identifier of the message to unpin. Required if business_connection_id is specified. If
    ///   not specified, the most recent pinned message (by sending date) will be unpinned.
    /// </summary>
    MessageId: TTgOptional<Int64>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры getChatAdministrators. Неинициализированная запись пуста
  ///   (Default(TTgGetChatAdministratorsOptions)).
  /// </summary>
  TTgGetChatAdministratorsOptions = record
    /// <summary>
    ///   Pass True to additionally receive all bots that are administrators of the chat. By
    ///   default, bots other than the current bot are omitted.
    /// </summary>
    ReturnBots: TTgOptional<Boolean>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры createForumTopic. Неинициализированная запись пуста
  ///   (Default(TTgCreateForumTopicOptions)).
  /// </summary>
  TTgCreateForumTopicOptions = record
    /// <summary>
    ///   Color of the topic icon in RGB format. Currently, must be one of 7322096 (0x6FB9F0),
    ///   16766590 (0xFFD67E), 13338331 (0xCB86DB), 9367192 (0x8EEE98), 16749490 (0xFF93B2), or
    ///   16478047 (0xFB6F5F).
    /// </summary>
    IconColor: TTgOptional<Integer>;
    /// <summary>
    ///   Unique identifier of the custom emoji shown as the topic icon. Use
    ///   getForumTopicIconStickers to get all allowed custom emoji identifiers.
    /// </summary>
    IconCustomEmojiId: TTgOptional<string>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры editForumTopic. Неинициализированная запись пуста
  ///   (Default(TTgEditForumTopicOptions)).
  /// </summary>
  TTgEditForumTopicOptions = record
    /// <summary>
    ///   New topic name, 0-128 characters. If not specified or empty, the current name of the topic
    ///   will be kept.
    /// </summary>
    Name: TTgOptional<string>;
    /// <summary>
    ///   New unique identifier of the custom emoji shown as the topic icon. Use
    ///   getForumTopicIconStickers to get all allowed custom emoji identifiers. Pass an empty
    ///   string to remove the icon. If not specified, the current icon will be kept.
    /// </summary>
    IconCustomEmojiId: TTgOptional<string>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры answerCallbackQuery. Неинициализированная запись пуста
  ///   (Default(TTgAnswerCallbackQueryOptions)).
  /// </summary>
  TTgAnswerCallbackQueryOptions = record
    /// <summary>
    ///   Text of the notification. If not specified, nothing will be shown to the user, 0-200
    ///   characters.
    /// </summary>
    Text: TTgOptional<string>;
    /// <summary>
    ///   If True, an alert will be shown by the client instead of a notification at the top of the
    ///   chat screen. Defaults to False.
    /// </summary>
    ShowAlert: TTgOptional<Boolean>;
    /// <summary>
    ///   URL that will be opened by the user's client. If you have created a Game and accepted the
    ///   conditions via @BotFather, specify the URL that opens your game - note that this will only
    ///   work if the query comes from a callback_game button. Otherwise, you may use links like
    ///   t.me/your_bot?start=XXXX that open your bot with a parameter.
    /// </summary>
    Url: TTgOptional<string>;
    /// <summary>
    ///   The maximum amount of time in seconds that the result of the callback query may be cached
    ///   client-side. Defaults to 0.
    /// </summary>
    CacheTime: TTgOptional<Integer>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры setManagedBotAccessSettings. Неинициализированная запись пуста
  ///   (Default(TTgSetManagedBotAccessSettingsOptions)).
  /// </summary>
  TTgSetManagedBotAccessSettingsOptions = record
    /// <summary>
    ///   A JSON-serialized list of up to 10 identifiers of users who will have access to the bot in
    ///   addition to its owner. Ignored if is_access_restricted is False. Не задано — параметр не
    ///   передаётся; [] — передаётся пустой список.
    /// </summary>
    AddedUserIds: TTgOptional<TArray<Int64>>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры setMyCommands. Неинициализированная запись пуста
  ///   (Default(TTgSetMyCommandsOptions)).
  /// </summary>
  TTgSetMyCommandsOptions = record
    /// <summary>
    ///   A JSON-serialized object, describing scope of users for which the commands are relevant.
    ///   Defaults to BotCommandScopeDefault.
    /// </summary>
    Scope: TTgBotCommandScope;
    /// <summary>
    ///   A two-letter ISO 639-1 language code. If empty, commands will be applied to all users from
    ///   the given scope, for whose language there are no dedicated commands.
    /// </summary>
    LanguageCode: TTgOptional<string>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры deleteMyCommands. Неинициализированная запись пуста
  ///   (Default(TTgDeleteMyCommandsOptions)).
  /// </summary>
  TTgDeleteMyCommandsOptions = record
    /// <summary>
    ///   A JSON-serialized object, describing scope of users for which the commands are relevant.
    ///   Defaults to BotCommandScopeDefault.
    /// </summary>
    Scope: TTgBotCommandScope;
    /// <summary>
    ///   A two-letter ISO 639-1 language code. If empty, commands will be applied to all users from
    ///   the given scope, for whose language there are no dedicated commands.
    /// </summary>
    LanguageCode: TTgOptional<string>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры getMyCommands. Неинициализированная запись пуста
  ///   (Default(TTgGetMyCommandsOptions)).
  /// </summary>
  TTgGetMyCommandsOptions = record
    /// <summary>
    ///   A JSON-serialized object, describing scope of users. Defaults to BotCommandScopeDefault.
    /// </summary>
    Scope: TTgBotCommandScope;
    /// <summary>A two-letter ISO 639-1 language code or an empty string</summary>
    LanguageCode: TTgOptional<string>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры setMyName. Неинициализированная запись пуста
  ///   (Default(TTgSetMyNameOptions)).
  /// </summary>
  TTgSetMyNameOptions = record
    /// <summary>
    ///   New bot name; 0-64 characters. Pass an empty string to remove the dedicated name for the
    ///   given language.
    /// </summary>
    Name: TTgOptional<string>;
    /// <summary>
    ///   A two-letter ISO 639-1 language code. If empty, the name will be shown to all users for
    ///   whose language there is no dedicated name.
    /// </summary>
    LanguageCode: TTgOptional<string>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры getMyName. Неинициализированная запись пуста
  ///   (Default(TTgGetMyNameOptions)).
  /// </summary>
  TTgGetMyNameOptions = record
    /// <summary>A two-letter ISO 639-1 language code or an empty string</summary>
    LanguageCode: TTgOptional<string>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры setMyDescription. Неинициализированная запись пуста
  ///   (Default(TTgSetMyDescriptionOptions)).
  /// </summary>
  TTgSetMyDescriptionOptions = record
    /// <summary>
    ///   New bot description; 0-512 characters. Pass an empty string to remove the dedicated
    ///   description for the given language.
    /// </summary>
    Description: TTgOptional<string>;
    /// <summary>
    ///   A two-letter ISO 639-1 language code. If empty, the description will be applied to all
    ///   users for whose language there is no dedicated description.
    /// </summary>
    LanguageCode: TTgOptional<string>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры getMyDescription. Неинициализированная запись пуста
  ///   (Default(TTgGetMyDescriptionOptions)).
  /// </summary>
  TTgGetMyDescriptionOptions = record
    /// <summary>A two-letter ISO 639-1 language code or an empty string</summary>
    LanguageCode: TTgOptional<string>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры setMyShortDescription. Неинициализированная запись пуста
  ///   (Default(TTgSetMyShortDescriptionOptions)).
  /// </summary>
  TTgSetMyShortDescriptionOptions = record
    /// <summary>
    ///   New short description for the bot; 0-120 characters. Pass an empty string to remove the
    ///   dedicated short description for the given language.
    /// </summary>
    ShortDescription: TTgOptional<string>;
    /// <summary>
    ///   A two-letter ISO 639-1 language code. If empty, the short description will be applied to
    ///   all users for whose language there is no dedicated short description.
    /// </summary>
    LanguageCode: TTgOptional<string>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры getMyShortDescription. Неинициализированная запись пуста
  ///   (Default(TTgGetMyShortDescriptionOptions)).
  /// </summary>
  TTgGetMyShortDescriptionOptions = record
    /// <summary>A two-letter ISO 639-1 language code or an empty string</summary>
    LanguageCode: TTgOptional<string>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры setChatMenuButton. Неинициализированная запись пуста
  ///   (Default(TTgSetChatMenuButtonOptions)).
  /// </summary>
  TTgSetChatMenuButtonOptions = record
    /// <summary>
    ///   Unique identifier for the target private chat. If not specified, the bot's default menu
    ///   button will be changed.
    /// </summary>
    ChatId: TTgOptional<Int64>;
    /// <summary>
    ///   A JSON-serialized object for the bot's new menu button. Defaults to MenuButtonDefault.
    /// </summary>
    MenuButton: ITgMenuButton;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры getChatMenuButton. Неинициализированная запись пуста
  ///   (Default(TTgGetChatMenuButtonOptions)).
  /// </summary>
  TTgGetChatMenuButtonOptions = record
    /// <summary>
    ///   Unique identifier for the target private chat. If not specified, the bot's default menu
    ///   button will be returned.
    /// </summary>
    ChatId: TTgOptional<Int64>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры setMyDefaultAdministratorRights. Неинициализированная запись пуста
  ///   (Default(TTgSetMyDefaultAdministratorRightsOptions)).
  /// </summary>
  TTgSetMyDefaultAdministratorRightsOptions = record
    /// <summary>
    ///   A JSON-serialized object describing new default administrator rights. If not specified,
    ///   the default administrator rights will be cleared.
    /// </summary>
    Rights: ITgChatAdministratorRights;
    /// <summary>
    ///   Pass True to change the default administrator rights of the bot in channels. Otherwise,
    ///   the default administrator rights of the bot for groups and supergroups will be changed.
    /// </summary>
    ForChannels: TTgOptional<Boolean>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры getMyDefaultAdministratorRights. Неинициализированная запись пуста
  ///   (Default(TTgGetMyDefaultAdministratorRightsOptions)).
  /// </summary>
  TTgGetMyDefaultAdministratorRightsOptions = record
    /// <summary>
    ///   Pass True to get default administrator rights of the bot in channels. Otherwise, default
    ///   administrator rights of the bot for groups and supergroups will be returned.
    /// </summary>
    ForChannels: TTgOptional<Boolean>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры sendGift. Неинициализированная запись пуста
  ///   (Default(TTgSendGiftOptions)).
  /// </summary>
  TTgSendGiftOptions = record
    /// <summary>
    ///   Required if chat_id is not specified. Unique identifier of the target user who will
    ///   receive the gift.
    /// </summary>
    UserId: TTgOptional<Int64>;
    /// <summary>
    ///   Required if user_id is not specified. Unique identifier for the chat or username of the
    ///   channel (in the format @username) that will receive the gift.
    /// </summary>
    ChatId: TTgChatId;
    /// <summary>
    ///   Pass True to pay for the gift upgrade from the bot's balance, thereby making the upgrade
    ///   free for the receiver
    /// </summary>
    PayForUpgrade: TTgOptional<Boolean>;
    /// <summary>Text that will be shown along with the gift; 0-128 characters</summary>
    Text: TTgOptional<string>;
    /// <summary>
    ///   Mode for parsing entities in the text. See formatting options for more details. Entities
    ///   other than “bold”, “italic”, “underline”, “strikethrough”, “spoiler”, “custom_emoji”, and
    ///   “date_time” are ignored.
    /// </summary>
    TextParseMode: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized list of special entities that appear in the gift text. It can be
    ///   specified instead of text_parse_mode. Entities other than “bold”, “italic”, “underline”,
    ///   “strikethrough”, “spoiler”, “custom_emoji”, and “date_time” are ignored. Не задано —
    ///   параметр не передаётся; [] — передаётся пустой список.
    /// </summary>
    TextEntities: TTgOptional<TArray<ITgMessageEntity>>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры giftPremiumSubscription. Неинициализированная запись пуста
  ///   (Default(TTgGiftPremiumSubscriptionOptions)).
  /// </summary>
  TTgGiftPremiumSubscriptionOptions = record
    /// <summary>
    ///   Text that will be shown along with the service message about the subscription; 0-128
    ///   characters
    /// </summary>
    Text: TTgOptional<string>;
    /// <summary>
    ///   Mode for parsing entities in the text. See formatting options for more details. Entities
    ///   other than “bold”, “italic”, “underline”, “strikethrough”, “spoiler”, “custom_emoji”, and
    ///   “date_time” are ignored.
    /// </summary>
    TextParseMode: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized list of special entities that appear in the gift text. It can be
    ///   specified instead of text_parse_mode. Entities other than “bold”, “italic”, “underline”,
    ///   “strikethrough”, “spoiler”, “custom_emoji”, and “date_time” are ignored. Не задано —
    ///   параметр не передаётся; [] — передаётся пустой список.
    /// </summary>
    TextEntities: TTgOptional<TArray<ITgMessageEntity>>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры verifyUser. Неинициализированная запись пуста
  ///   (Default(TTgVerifyUserOptions)).
  /// </summary>
  TTgVerifyUserOptions = record
    /// <summary>
    ///   Custom description for the verification; 0-70 characters. Must be empty if the
    ///   organization isn't allowed to provide a custom verification description.
    /// </summary>
    CustomDescription: TTgOptional<string>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры verifyChat. Неинициализированная запись пуста
  ///   (Default(TTgVerifyChatOptions)).
  /// </summary>
  TTgVerifyChatOptions = record
    /// <summary>
    ///   Custom description for the verification; 0-70 characters. Must be empty if the
    ///   organization isn't allowed to provide a custom verification description.
    /// </summary>
    CustomDescription: TTgOptional<string>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры setBusinessAccountName. Неинициализированная запись пуста
  ///   (Default(TTgSetBusinessAccountNameOptions)).
  /// </summary>
  TTgSetBusinessAccountNameOptions = record
    /// <summary>
    ///   The new value of the last name for the business account; 0-64 characters
    /// </summary>
    LastName: TTgOptional<string>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры setBusinessAccountUsername. Неинициализированная запись пуста
  ///   (Default(TTgSetBusinessAccountUsernameOptions)).
  /// </summary>
  TTgSetBusinessAccountUsernameOptions = record
    /// <summary>
    ///   The new value of the username for the business account; 0-32 characters
    /// </summary>
    Username: TTgOptional<string>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры setBusinessAccountBio. Неинициализированная запись пуста
  ///   (Default(TTgSetBusinessAccountBioOptions)).
  /// </summary>
  TTgSetBusinessAccountBioOptions = record
    /// <summary>
    ///   The new value of the bio for the business account; 0-140 characters
    /// </summary>
    Bio: TTgOptional<string>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры setBusinessAccountProfilePhoto. Неинициализированная запись пуста
  ///   (Default(TTgSetBusinessAccountProfilePhotoOptions)).
  /// </summary>
  TTgSetBusinessAccountProfilePhotoOptions = record
    /// <summary>
    ///   Pass True to set the public photo, which will be visible even if the main photo is hidden
    ///   by the business account's privacy settings. An account can have only one public photo.
    /// </summary>
    IsPublic: TTgOptional<Boolean>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры removeBusinessAccountProfilePhoto. Неинициализированная запись
  ///   пуста (Default(TTgRemoveBusinessAccountProfilePhotoOptions)).
  /// </summary>
  TTgRemoveBusinessAccountProfilePhotoOptions = record
    /// <summary>
    ///   Pass True to remove the public photo, which is visible even if the main photo is hidden by
    ///   the business account's privacy settings. After the main photo is removed, the previous
    ///   profile photo (if present) becomes the main photo.
    /// </summary>
    IsPublic: TTgOptional<Boolean>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры getBusinessAccountGifts. Неинициализированная запись пуста
  ///   (Default(TTgGetBusinessAccountGiftsOptions)).
  /// </summary>
  TTgGetBusinessAccountGiftsOptions = record
    /// <summary>
    ///   Pass True to exclude gifts that aren't saved to the account's profile page
    /// </summary>
    ExcludeUnsaved: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to exclude gifts that are saved to the account's profile page
    /// </summary>
    ExcludeSaved: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to exclude gifts that can be purchased an unlimited number of times
    /// </summary>
    ExcludeUnlimited: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to exclude gifts that can be purchased a limited number of times and can be
    ///   upgraded to unique
    /// </summary>
    ExcludeLimitedUpgradable: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to exclude gifts that can be purchased a limited number of times and can't be
    ///   upgraded to unique
    /// </summary>
    ExcludeLimitedNonUpgradable: TTgOptional<Boolean>;
    /// <summary>Pass True to exclude unique gifts</summary>
    ExcludeUnique: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to exclude gifts that were assigned from the TON blockchain and can't be resold
    ///   or transferred in Telegram
    /// </summary>
    ExcludeFromBlockchain: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to sort results by gift price instead of send date. Sorting is applied before
    ///   pagination.
    /// </summary>
    SortByPrice: TTgOptional<Boolean>;
    /// <summary>
    ///   Offset of the first entry to return as received from the previous request; use empty
    ///   string to get the first chunk of results
    /// </summary>
    Offset: TTgOptional<string>;
    /// <summary>
    ///   The maximum number of gifts to be returned; 1-100. Defaults to 100.
    /// </summary>
    Limit: TTgOptional<Integer>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры getUserGifts. Неинициализированная запись пуста
  ///   (Default(TTgGetUserGiftsOptions)).
  /// </summary>
  TTgGetUserGiftsOptions = record
    /// <summary>
    ///   Pass True to exclude gifts that can be purchased an unlimited number of times
    /// </summary>
    ExcludeUnlimited: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to exclude gifts that can be purchased a limited number of times and can be
    ///   upgraded to unique
    /// </summary>
    ExcludeLimitedUpgradable: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to exclude gifts that can be purchased a limited number of times and can't be
    ///   upgraded to unique
    /// </summary>
    ExcludeLimitedNonUpgradable: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to exclude gifts that were assigned from the TON blockchain and can't be resold
    ///   or transferred in Telegram
    /// </summary>
    ExcludeFromBlockchain: TTgOptional<Boolean>;
    /// <summary>Pass True to exclude unique gifts</summary>
    ExcludeUnique: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to sort results by gift price instead of send date. Sorting is applied before
    ///   pagination.
    /// </summary>
    SortByPrice: TTgOptional<Boolean>;
    /// <summary>
    ///   Offset of the first entry to return as received from the previous request; use an empty
    ///   string to get the first chunk of results
    /// </summary>
    Offset: TTgOptional<string>;
    /// <summary>
    ///   The maximum number of gifts to be returned; 1-100. Defaults to 100.
    /// </summary>
    Limit: TTgOptional<Integer>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры getChatGifts. Неинициализированная запись пуста
  ///   (Default(TTgGetChatGiftsOptions)).
  /// </summary>
  TTgGetChatGiftsOptions = record
    /// <summary>
    ///   Pass True to exclude gifts that aren't saved to the chat's profile page. Always True,
    ///   unless the bot has the can_post_messages administrator right in the channel.
    /// </summary>
    ExcludeUnsaved: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to exclude gifts that are saved to the chat's profile page. Always False, unless
    ///   the bot has the can_post_messages administrator right in the channel.
    /// </summary>
    ExcludeSaved: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to exclude gifts that can be purchased an unlimited number of times
    /// </summary>
    ExcludeUnlimited: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to exclude gifts that can be purchased a limited number of times and can be
    ///   upgraded to unique
    /// </summary>
    ExcludeLimitedUpgradable: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to exclude gifts that can be purchased a limited number of times and can't be
    ///   upgraded to unique
    /// </summary>
    ExcludeLimitedNonUpgradable: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to exclude gifts that were assigned from the TON blockchain and can't be resold
    ///   or transferred in Telegram
    /// </summary>
    ExcludeFromBlockchain: TTgOptional<Boolean>;
    /// <summary>Pass True to exclude unique gifts</summary>
    ExcludeUnique: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to sort results by gift price instead of send date. Sorting is applied before
    ///   pagination.
    /// </summary>
    SortByPrice: TTgOptional<Boolean>;
    /// <summary>
    ///   Offset of the first entry to return as received from the previous request; use an empty
    ///   string to get the first chunk of results
    /// </summary>
    Offset: TTgOptional<string>;
    /// <summary>
    ///   The maximum number of gifts to be returned; 1-100. Defaults to 100.
    /// </summary>
    Limit: TTgOptional<Integer>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры upgradeGift. Неинициализированная запись пуста
  ///   (Default(TTgUpgradeGiftOptions)).
  /// </summary>
  TTgUpgradeGiftOptions = record
    /// <summary>
    ///   Pass True to keep the original gift text, sender and receiver in the upgraded gift
    /// </summary>
    KeepOriginalDetails: TTgOptional<Boolean>;
    /// <summary>
    ///   The amount of Telegram Stars that will be paid for the upgrade from the business account
    ///   balance. If gift.prepaid_upgrade_star_count &gt; 0, then pass 0, otherwise, the
    ///   can_transfer_stars business bot right is required and gift.upgrade_star_count must be
    ///   passed.
    /// </summary>
    StarCount: TTgOptional<Integer>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры transferGift. Неинициализированная запись пуста
  ///   (Default(TTgTransferGiftOptions)).
  /// </summary>
  TTgTransferGiftOptions = record
    /// <summary>
    ///   The amount of Telegram Stars that will be paid for the transfer from the business account
    ///   balance. If positive, then the can_transfer_stars business bot right is required.
    /// </summary>
    StarCount: TTgOptional<Integer>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры postStory. Неинициализированная запись пуста
  ///   (Default(TTgPostStoryOptions)).
  /// </summary>
  TTgPostStoryOptions = record
    /// <summary>Caption of the story, 0-2048 characters after entities parsing</summary>
    Caption: TTgOptional<string>;
    /// <summary>
    ///   Mode for parsing entities in the story caption. See formatting options for more details.
    /// </summary>
    ParseMode: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized list of special entities that appear in the caption, which can be
    ///   specified instead of parse_mode Не задано — параметр не передаётся; [] — передаётся пустой
    ///   список.
    /// </summary>
    CaptionEntities: TTgOptional<TArray<ITgMessageEntity>>;
    /// <summary>
    ///   A JSON-serialized list of clickable areas to be shown on the story Не задано — параметр не
    ///   передаётся; [] — передаётся пустой список.
    /// </summary>
    Areas: TTgOptional<TArray<ITgStoryArea>>;
    /// <summary>Pass True to keep the story accessible after it expires</summary>
    PostToChatPage: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if the content of the story must be protected from forwarding and screenshotting
    /// </summary>
    ProtectContent: TTgOptional<Boolean>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры repostStory. Неинициализированная запись пуста
  ///   (Default(TTgRepostStoryOptions)).
  /// </summary>
  TTgRepostStoryOptions = record
    /// <summary>Pass True to keep the story accessible after it expires</summary>
    PostToChatPage: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if the content of the story must be protected from forwarding and screenshotting
    /// </summary>
    ProtectContent: TTgOptional<Boolean>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры editStory. Неинициализированная запись пуста
  ///   (Default(TTgEditStoryOptions)).
  /// </summary>
  TTgEditStoryOptions = record
    /// <summary>Caption of the story, 0-2048 characters after entities parsing</summary>
    Caption: TTgOptional<string>;
    /// <summary>
    ///   Mode for parsing entities in the story caption. See formatting options for more details.
    /// </summary>
    ParseMode: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized list of special entities that appear in the caption, which can be
    ///   specified instead of parse_mode Не задано — параметр не передаётся; [] — передаётся пустой
    ///   список.
    /// </summary>
    CaptionEntities: TTgOptional<TArray<ITgMessageEntity>>;
    /// <summary>
    ///   A JSON-serialized list of clickable areas to be shown on the story Не задано — параметр не
    ///   передаётся; [] — передаётся пустой список.
    /// </summary>
    Areas: TTgOptional<TArray<ITgStoryArea>>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры savePreparedInlineMessage. Неинициализированная запись пуста
  ///   (Default(TTgSavePreparedInlineMessageOptions)).
  /// </summary>
  TTgSavePreparedInlineMessageOptions = record
    /// <summary>Pass True if the message can be sent to private chats with users</summary>
    AllowUserChats: TTgOptional<Boolean>;
    /// <summary>Pass True if the message can be sent to private chats with bots</summary>
    AllowBotChats: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if the message can be sent to group and supergroup chats
    /// </summary>
    AllowGroupChats: TTgOptional<Boolean>;
    /// <summary>Pass True if the message can be sent to channel chats</summary>
    AllowChannelChats: TTgOptional<Boolean>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры editMessageText. Неинициализированная запись пуста
  ///   (Default(TTgEditMessageTextOptions)).
  /// </summary>
  TTgEditMessageTextOptions = record
    /// <summary>
    ///   Unique identifier of the business connection on behalf of which the message to be edited
    ///   was sent
    /// </summary>
    BusinessConnectionId: TTgOptional<string>;
    /// <summary>
    ///   Required if inline_message_id is not specified. Unique identifier for the target chat or
    ///   username of the target bot, supergroup or channel in the format @username.
    /// </summary>
    ChatId: TTgChatId;
    /// <summary>
    ///   Required if inline_message_id is not specified. Identifier of the message to edit.
    /// </summary>
    MessageId: TTgOptional<Int64>;
    /// <summary>
    ///   Required if chat_id and message_id are not specified. Identifier of the inline message.
    /// </summary>
    InlineMessageId: TTgOptional<string>;
    /// <summary>
    ///   New text of the message, 1-4096 characters after entity parsing; required if rich_message
    ///   isn't specified
    /// </summary>
    Text: TTgOptional<string>;
    /// <summary>
    ///   Mode for parsing entities in the message text. See formatting options for more details.
    /// </summary>
    ParseMode: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized list of special entities that appear in message text, which can be
    ///   specified instead of parse_mode Не задано — параметр не передаётся; [] — передаётся пустой
    ///   список.
    /// </summary>
    Entities: TTgOptional<TArray<ITgMessageEntity>>;
    /// <summary>Link preview generation options for the message</summary>
    LinkPreviewOptions: ITgLinkPreviewOptions;
    /// <summary>
    ///   New rich content of the message; required if text isn't specified. Direct upload of new
    ///   files and explicit upload of files by a URL isn't supported when an inline message is
    ///   edited.
    /// </summary>
    RichMessage: ITgInputRichMessage;
    /// <summary>
    ///   A JSON-serialized object for an inline keyboard. Только инлайн-клавиатура
    ///   (ITgInlineKeyboardMarkup): TTgKeyboard.Inline.Row.Button(…) или
    ///   TTgInlineKeyboardMarkup.Create; обычная клавиатура, Remove и ForceReply здесь не
    ///   принимаются.
    /// </summary>
    ReplyMarkup: ITgInlineKeyboardMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры editMessageCaption. Неинициализированная запись пуста
  ///   (Default(TTgEditMessageCaptionOptions)).
  /// </summary>
  TTgEditMessageCaptionOptions = record
    /// <summary>
    ///   Unique identifier of the business connection on behalf of which the message to be edited
    ///   was sent
    /// </summary>
    BusinessConnectionId: TTgOptional<string>;
    /// <summary>
    ///   Required if inline_message_id is not specified. Unique identifier for the target chat or
    ///   username of the target bot, supergroup or channel in the format @username.
    /// </summary>
    ChatId: TTgChatId;
    /// <summary>
    ///   Required if inline_message_id is not specified. Identifier of the message to edit.
    /// </summary>
    MessageId: TTgOptional<Int64>;
    /// <summary>
    ///   Required if chat_id and message_id are not specified. Identifier of the inline message.
    /// </summary>
    InlineMessageId: TTgOptional<string>;
    /// <summary>
    ///   New caption of the message, 0-1024 characters after entities parsing
    /// </summary>
    Caption: TTgOptional<string>;
    /// <summary>
    ///   Mode for parsing entities in the message caption. See formatting options for more details.
    /// </summary>
    ParseMode: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized list of special entities that appear in the caption, which can be
    ///   specified instead of parse_mode Не задано — параметр не передаётся; [] — передаётся пустой
    ///   список.
    /// </summary>
    CaptionEntities: TTgOptional<TArray<ITgMessageEntity>>;
    /// <summary>
    ///   Pass True if the caption must be shown above the message media. Supported only for
    ///   animation, photo and video messages.
    /// </summary>
    ShowCaptionAboveMedia: TTgOptional<Boolean>;
    /// <summary>
    ///   A JSON-serialized object for an inline keyboard. Только инлайн-клавиатура
    ///   (ITgInlineKeyboardMarkup): TTgKeyboard.Inline.Row.Button(…) или
    ///   TTgInlineKeyboardMarkup.Create; обычная клавиатура, Remove и ForceReply здесь не
    ///   принимаются.
    /// </summary>
    ReplyMarkup: ITgInlineKeyboardMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры editMessageMedia. Неинициализированная запись пуста
  ///   (Default(TTgEditMessageMediaOptions)).
  /// </summary>
  TTgEditMessageMediaOptions = record
    /// <summary>
    ///   Unique identifier of the business connection on behalf of which the message to be edited
    ///   was sent
    /// </summary>
    BusinessConnectionId: TTgOptional<string>;
    /// <summary>
    ///   Required if inline_message_id is not specified. Unique identifier for the target chat or
    ///   username of the target bot, supergroup or channel in the format @username.
    /// </summary>
    ChatId: TTgChatId;
    /// <summary>
    ///   Required if inline_message_id is not specified. Identifier of the message to edit.
    /// </summary>
    MessageId: TTgOptional<Int64>;
    /// <summary>
    ///   Required if chat_id and message_id are not specified. Identifier of the inline message.
    /// </summary>
    InlineMessageId: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized object for a new inline keyboard. Только инлайн-клавиатура
    ///   (ITgInlineKeyboardMarkup): TTgKeyboard.Inline.Row.Button(…) или
    ///   TTgInlineKeyboardMarkup.Create; обычная клавиатура, Remove и ForceReply здесь не
    ///   принимаются.
    /// </summary>
    ReplyMarkup: ITgInlineKeyboardMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры editMessageLiveLocation. Неинициализированная запись пуста
  ///   (Default(TTgEditMessageLiveLocationOptions)).
  /// </summary>
  TTgEditMessageLiveLocationOptions = record
    /// <summary>
    ///   Unique identifier of the business connection on behalf of which the message to be edited
    ///   was sent
    /// </summary>
    BusinessConnectionId: TTgOptional<string>;
    /// <summary>
    ///   Required if inline_message_id is not specified. Unique identifier for the target chat or
    ///   username of the target bot, supergroup or channel in the format @username.
    /// </summary>
    ChatId: TTgChatId;
    /// <summary>
    ///   Required if inline_message_id is not specified. Identifier of the message to edit.
    /// </summary>
    MessageId: TTgOptional<Int64>;
    /// <summary>
    ///   Required if chat_id and message_id are not specified. Identifier of the inline message.
    /// </summary>
    InlineMessageId: TTgOptional<string>;
    /// <summary>
    ///   New period in seconds during which the location can be updated, starting from the message
    ///   send date. If 0x7FFFFFFF is specified, then the location can be updated forever.
    ///   Otherwise, the new value must not exceed the current live_period by more than a day, and
    ///   the live location expiration date must remain within the next 90 days. If not specified,
    ///   then live_period remains unchanged.
    /// </summary>
    LivePeriod: TTgOptional<Integer>;
    /// <summary>
    ///   The radius of uncertainty for the location, measured in meters; 0-1500
    /// </summary>
    HorizontalAccuracy: TTgOptional<Double>;
    /// <summary>
    ///   Direction in which the user is moving, in degrees. Must be between 1 and 360 if specified.
    /// </summary>
    Heading: TTgOptional<Integer>;
    /// <summary>
    ///   The maximum distance for proximity alerts about approaching another chat member, in
    ///   meters. Must be between 1 and 100000 if specified.
    /// </summary>
    ProximityAlertRadius: TTgOptional<Integer>;
    /// <summary>
    ///   A JSON-serialized object for a new inline keyboard. Только инлайн-клавиатура
    ///   (ITgInlineKeyboardMarkup): TTgKeyboard.Inline.Row.Button(…) или
    ///   TTgInlineKeyboardMarkup.Create; обычная клавиатура, Remove и ForceReply здесь не
    ///   принимаются.
    /// </summary>
    ReplyMarkup: ITgInlineKeyboardMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры stopMessageLiveLocation. Неинициализированная запись пуста
  ///   (Default(TTgStopMessageLiveLocationOptions)).
  /// </summary>
  TTgStopMessageLiveLocationOptions = record
    /// <summary>
    ///   Unique identifier of the business connection on behalf of which the message to be edited
    ///   was sent
    /// </summary>
    BusinessConnectionId: TTgOptional<string>;
    /// <summary>
    ///   Required if inline_message_id is not specified. Unique identifier for the target chat or
    ///   username of the target bot, supergroup or channel in the format @username.
    /// </summary>
    ChatId: TTgChatId;
    /// <summary>
    ///   Required if inline_message_id is not specified. Identifier of the message with live
    ///   location to stop.
    /// </summary>
    MessageId: TTgOptional<Int64>;
    /// <summary>
    ///   Required if chat_id and message_id are not specified. Identifier of the inline message.
    /// </summary>
    InlineMessageId: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized object for a new inline keyboard. Только инлайн-клавиатура
    ///   (ITgInlineKeyboardMarkup): TTgKeyboard.Inline.Row.Button(…) или
    ///   TTgInlineKeyboardMarkup.Create; обычная клавиатура, Remove и ForceReply здесь не
    ///   принимаются.
    /// </summary>
    ReplyMarkup: ITgInlineKeyboardMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры editMessageChecklist. Неинициализированная запись пуста
  ///   (Default(TTgEditMessageChecklistOptions)).
  /// </summary>
  TTgEditMessageChecklistOptions = record
    /// <summary>
    ///   A JSON-serialized object for the new inline keyboard for the message. Только
    ///   инлайн-клавиатура (ITgInlineKeyboardMarkup): TTgKeyboard.Inline.Row.Button(…) или
    ///   TTgInlineKeyboardMarkup.Create; обычная клавиатура, Remove и ForceReply здесь не
    ///   принимаются.
    /// </summary>
    ReplyMarkup: ITgInlineKeyboardMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры editMessageReplyMarkup. Неинициализированная запись пуста
  ///   (Default(TTgEditMessageReplyMarkupOptions)).
  /// </summary>
  TTgEditMessageReplyMarkupOptions = record
    /// <summary>
    ///   Unique identifier of the business connection on behalf of which the message to be edited
    ///   was sent
    /// </summary>
    BusinessConnectionId: TTgOptional<string>;
    /// <summary>
    ///   Required if inline_message_id is not specified. Unique identifier for the target chat or
    ///   username of the target bot, supergroup or channel in the format @username.
    /// </summary>
    ChatId: TTgChatId;
    /// <summary>
    ///   Required if inline_message_id is not specified. Identifier of the message to edit.
    /// </summary>
    MessageId: TTgOptional<Int64>;
    /// <summary>
    ///   Required if chat_id and message_id are not specified. Identifier of the inline message.
    /// </summary>
    InlineMessageId: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized object for an inline keyboard. Только инлайн-клавиатура
    ///   (ITgInlineKeyboardMarkup): TTgKeyboard.Inline.Row.Button(…) или
    ///   TTgInlineKeyboardMarkup.Create; обычная клавиатура, Remove и ForceReply здесь не
    ///   принимаются.
    /// </summary>
    ReplyMarkup: ITgInlineKeyboardMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры stopPoll. Неинициализированная запись пуста
  ///   (Default(TTgStopPollOptions)).
  /// </summary>
  TTgStopPollOptions = record
    /// <summary>
    ///   Unique identifier of the business connection on behalf of which the message to be edited
    ///   was sent
    /// </summary>
    BusinessConnectionId: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized object for a new message inline keyboard. Только инлайн-клавиатура
    ///   (ITgInlineKeyboardMarkup): TTgKeyboard.Inline.Row.Button(…) или
    ///   TTgInlineKeyboardMarkup.Create; обычная клавиатура, Remove и ForceReply здесь не
    ///   принимаются.
    /// </summary>
    ReplyMarkup: ITgInlineKeyboardMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры editEphemeralMessageText. Неинициализированная запись пуста
  ///   (Default(TTgEditEphemeralMessageTextOptions)).
  /// </summary>
  TTgEditEphemeralMessageTextOptions = record
    /// <summary>
    ///   New text of the message, 1-4096 characters after entity parsing; required if rich_message
    ///   isn't specified
    /// </summary>
    Text: TTgOptional<string>;
    /// <summary>
    ///   Mode for parsing entities in the message text. See formatting options for more details.
    /// </summary>
    ParseMode: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized list of special entities that appear in message text, which can be
    ///   specified instead of parse_mode Не задано — параметр не передаётся; [] — передаётся пустой
    ///   список.
    /// </summary>
    Entities: TTgOptional<TArray<ITgMessageEntity>>;
    /// <summary>New rich content of the message; required if text isn't specified</summary>
    RichMessage: ITgInputRichMessage;
    /// <summary>Link preview generation options for the message</summary>
    LinkPreviewOptions: ITgLinkPreviewOptions;
    /// <summary>
    ///   A JSON-serialized object for an inline keyboard. Только инлайн-клавиатура
    ///   (ITgInlineKeyboardMarkup): TTgKeyboard.Inline.Row.Button(…) или
    ///   TTgInlineKeyboardMarkup.Create; обычная клавиатура, Remove и ForceReply здесь не
    ///   принимаются.
    /// </summary>
    ReplyMarkup: ITgInlineKeyboardMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры editEphemeralMessageMedia. Неинициализированная запись пуста
  ///   (Default(TTgEditEphemeralMessageMediaOptions)).
  /// </summary>
  TTgEditEphemeralMessageMediaOptions = record
    /// <summary>
    ///   A JSON-serialized object for an inline keyboard. Только инлайн-клавиатура
    ///   (ITgInlineKeyboardMarkup): TTgKeyboard.Inline.Row.Button(…) или
    ///   TTgInlineKeyboardMarkup.Create; обычная клавиатура, Remove и ForceReply здесь не
    ///   принимаются.
    /// </summary>
    ReplyMarkup: ITgInlineKeyboardMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры editEphemeralMessageCaption. Неинициализированная запись пуста
  ///   (Default(TTgEditEphemeralMessageCaptionOptions)).
  /// </summary>
  TTgEditEphemeralMessageCaptionOptions = record
    /// <summary>
    ///   New caption of the message, 0-1024 characters after entities parsing
    /// </summary>
    Caption: TTgOptional<string>;
    /// <summary>
    ///   Mode for parsing entities in the message caption. See formatting options for more details.
    /// </summary>
    ParseMode: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized list of special entities that appear in the caption, which can be
    ///   specified instead of parse_mode Не задано — параметр не передаётся; [] — передаётся пустой
    ///   список.
    /// </summary>
    CaptionEntities: TTgOptional<TArray<ITgMessageEntity>>;
    /// <summary>
    ///   Pass True if the caption must be shown above the message media. Supported only for
    ///   animation, photo and video messages.
    /// </summary>
    ShowCaptionAboveMedia: TTgOptional<Boolean>;
    /// <summary>
    ///   A JSON-serialized object for an inline keyboard. Только инлайн-клавиатура
    ///   (ITgInlineKeyboardMarkup): TTgKeyboard.Inline.Row.Button(…) или
    ///   TTgInlineKeyboardMarkup.Create; обычная клавиатура, Remove и ForceReply здесь не
    ///   принимаются.
    /// </summary>
    ReplyMarkup: ITgInlineKeyboardMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры editEphemeralMessageReplyMarkup. Неинициализированная запись пуста
  ///   (Default(TTgEditEphemeralMessageReplyMarkupOptions)).
  /// </summary>
  TTgEditEphemeralMessageReplyMarkupOptions = record
    /// <summary>
    ///   A JSON-serialized object for an inline keyboard. Только инлайн-клавиатура
    ///   (ITgInlineKeyboardMarkup): TTgKeyboard.Inline.Row.Button(…) или
    ///   TTgInlineKeyboardMarkup.Create; обычная клавиатура, Remove и ForceReply здесь не
    ///   принимаются.
    /// </summary>
    ReplyMarkup: ITgInlineKeyboardMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры approveSuggestedPost. Неинициализированная запись пуста
  ///   (Default(TTgApproveSuggestedPostOptions)).
  /// </summary>
  TTgApproveSuggestedPostOptions = record
    /// <summary>
    ///   Point in time (Unix timestamp) when the post is expected to be published; omit if the date
    ///   has already been specified when the suggested post was created. If specified, then the
    ///   date must be not more than 2678400 seconds (30 days) in the future.
    /// </summary>
    SendDate: TTgOptional<Int64>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры declineSuggestedPost. Неинициализированная запись пуста
  ///   (Default(TTgDeclineSuggestedPostOptions)).
  /// </summary>
  TTgDeclineSuggestedPostOptions = record
    /// <summary>Comment for the creator of the suggested post; 0-128 characters</summary>
    Comment: TTgOptional<string>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры deleteMessageReaction. Неинициализированная запись пуста
  ///   (Default(TTgDeleteMessageReactionOptions)).
  /// </summary>
  TTgDeleteMessageReactionOptions = record
    /// <summary>
    ///   Identifier of the user whose reaction will be removed, if the reaction was added by a user
    /// </summary>
    UserId: TTgOptional<Int64>;
    /// <summary>
    ///   Identifier of the chat whose reaction will be removed, if the reaction was added by a chat
    /// </summary>
    ActorChatId: TTgOptional<Int64>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры deleteAllMessageReactions. Неинициализированная запись пуста
  ///   (Default(TTgDeleteAllMessageReactionsOptions)).
  /// </summary>
  TTgDeleteAllMessageReactionsOptions = record
    /// <summary>
    ///   Identifier of the user whose reactions will be removed, if the reactions were added by a
    ///   user
    /// </summary>
    UserId: TTgOptional<Int64>;
    /// <summary>
    ///   Identifier of the chat whose reactions will be removed, if the reactions were added by a
    ///   chat
    /// </summary>
    ActorChatId: TTgOptional<Int64>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры sendSticker. Неинициализированная запись пуста
  ///   (Default(TTgSendStickerOptions)).
  /// </summary>
  TTgSendStickerOptions = record
    /// <summary>
    ///   Unique identifier of the business connection on behalf of which the message will be sent
    /// </summary>
    BusinessConnectionId: TTgOptional<string>;
    /// <summary>
    ///   Unique identifier for the target message thread (topic) of a forum; for forum supergroups
    ///   and private chats of bots with forum topic mode enabled only
    /// </summary>
    MessageThreadId: TTgOptional<Int64>;
    /// <summary>
    ///   Identifier of the direct messages topic to which the message will be sent; required if the
    ///   message is sent to a direct messages chat
    /// </summary>
    DirectMessagesTopicId: TTgOptional<Int64>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the ephemeral message to send
    /// </summary>
    EphemeralMessageParameters: ITgEphemeralMessageParameters;
    /// <summary>
    ///   Emoji associated with the sticker; only for just uploaded stickers
    /// </summary>
    Emoji: TTgOptional<string>;
    /// <summary>
    ///   Sends the message silently. Users will receive a notification with no sound.
    /// </summary>
    DisableNotification: TTgOptional<Boolean>;
    /// <summary>
    ///   Protects the contents of the sent message from forwarding and saving
    /// </summary>
    ProtectContent: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to allow up to 1000 messages per second, ignoring broadcasting limits for a fee
    ///   of 0.1 Telegram Stars per message. The relevant Stars will be withdrawn from the bot's
    ///   balance.
    /// </summary>
    AllowPaidBroadcast: TTgOptional<Boolean>;
    /// <summary>
    ///   Unique identifier of the message effect to be added to the message; for private chats only
    /// </summary>
    MessageEffectId: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the suggested post to send; for
    ///   direct messages chats only. If the message is sent as a reply to another suggested post,
    ///   then that suggested post is automatically declined.
    /// </summary>
    SuggestedPostParameters: ITgSuggestedPostParameters;
    /// <summary>Description of the message to reply to</summary>
    ReplyParameters: ITgReplyParameters;
    /// <summary>
    ///   Additional interface options. A JSON-serialized object for an inline keyboard, custom
    ///   reply keyboard, instructions to remove a reply keyboard or to force a reply from the user.
    ///   Построитель: TTgKeyboard.Inline…, TTgKeyboard.Reply…, TTgKeyboard.Remove,
    ///   TTgKeyboard.ForceReply.
    /// </summary>
    ReplyMarkup: TTgReplyMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры createNewStickerSet. Неинициализированная запись пуста
  ///   (Default(TTgCreateNewStickerSetOptions)).
  /// </summary>
  TTgCreateNewStickerSetOptions = record
    /// <summary>
    ///   Type of stickers in the set, pass “regular”, “mask”, or “custom_emoji”. By default, a
    ///   regular sticker set is created.
    /// </summary>
    StickerType: TTgOptional<string>;
    /// <summary>
    ///   Pass True if stickers in the sticker set must be repainted to the color of text when used
    ///   in messages, the accent color if used as emoji status, white on chat photos, or another
    ///   appropriate color based on context; for custom emoji sticker sets only
    /// </summary>
    NeedsRepainting: TTgOptional<Boolean>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры setStickerKeywords. Неинициализированная запись пуста
  ///   (Default(TTgSetStickerKeywordsOptions)).
  /// </summary>
  TTgSetStickerKeywordsOptions = record
    /// <summary>
    ///   A JSON-serialized list of 0-20 search keywords for the sticker with total length of up to
    ///   64 characters Не задано — параметр не передаётся; [] — передаётся пустой список.
    /// </summary>
    Keywords: TTgOptional<TArray<string>>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры setStickerMaskPosition. Неинициализированная запись пуста
  ///   (Default(TTgSetStickerMaskPositionOptions)).
  /// </summary>
  TTgSetStickerMaskPositionOptions = record
    /// <summary>
    ///   A JSON-serialized object with the position where the mask should be placed on faces. Omit
    ///   the parameter to remove the mask position.
    /// </summary>
    MaskPosition: ITgMaskPosition;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры setStickerSetThumbnail. Неинициализированная запись пуста
  ///   (Default(TTgSetStickerSetThumbnailOptions)).
  /// </summary>
  TTgSetStickerSetThumbnailOptions = record
    /// <summary>
    ///   A .WEBP or .PNG image with the thumbnail, must be up to 128 kilobytes in size and have a
    ///   width and height of exactly 100px, or a .TGS animation with a thumbnail up to 32 kilobytes
    ///   in size (see https://core.telegram.org/stickers#animation-requirements for animated
    ///   sticker technical requirements), or a .WEBM video with the thumbnail up to 32 kilobytes in
    ///   size; see https://core.telegram.org/stickers#video-requirements for video sticker
    ///   technical requirements. Pass a file_id as a String to send a file that already exists on
    ///   the Telegram servers, pass an HTTP URL as a String for Telegram to get a file from the
    ///   Internet, or upload a new one using multipart/form-data. More information on Sending Files
    ///   ». Animated and video sticker set thumbnails can't be uploaded via HTTP URL. If omitted,
    ///   then the thumbnail is dropped and the first sticker is used as the thumbnail.
    /// </summary>
    Thumbnail: TTgInputFile;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры setCustomEmojiStickerSetThumbnail. Неинициализированная запись
  ///   пуста (Default(TTgSetCustomEmojiStickerSetThumbnailOptions)).
  /// </summary>
  TTgSetCustomEmojiStickerSetThumbnailOptions = record
    /// <summary>
    ///   Custom emoji identifier of a sticker from the sticker set; pass an empty string to drop
    ///   the thumbnail and use the first sticker as the thumbnail
    /// </summary>
    CustomEmojiId: TTgOptional<string>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры sendRichMessage. Неинициализированная запись пуста
  ///   (Default(TTgSendRichMessageOptions)).
  /// </summary>
  TTgSendRichMessageOptions = record
    /// <summary>
    ///   Unique identifier of the business connection on behalf of which the message will be sent.
    ///   Bot can send rich messages on behalf of a business account only if the corresponding user
    ///   can send rich messages.
    /// </summary>
    BusinessConnectionId: TTgOptional<string>;
    /// <summary>
    ///   Unique identifier for the target message thread (topic) of a forum; for forum supergroups
    ///   and private chats of bots with forum topic mode enabled only
    /// </summary>
    MessageThreadId: TTgOptional<Int64>;
    /// <summary>
    ///   Identifier of the direct messages topic to which the message will be sent; required if the
    ///   message is sent to a direct messages chat
    /// </summary>
    DirectMessagesTopicId: TTgOptional<Int64>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the ephemeral message to send
    /// </summary>
    EphemeralMessageParameters: ITgEphemeralMessageParameters;
    /// <summary>
    ///   Sends the message silently. Users will receive a notification with no sound.
    /// </summary>
    DisableNotification: TTgOptional<Boolean>;
    /// <summary>
    ///   Protects the contents of the sent message from forwarding and saving
    /// </summary>
    ProtectContent: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to allow up to 1000 messages per second, ignoring broadcasting limits for a fee
    ///   of 0.1 Telegram Stars per message. The relevant Stars will be withdrawn from the bot's
    ///   balance.
    /// </summary>
    AllowPaidBroadcast: TTgOptional<Boolean>;
    /// <summary>
    ///   Unique identifier of the message effect to be added to the message; for private chats only
    /// </summary>
    MessageEffectId: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the suggested post to send; for
    ///   direct messages chats only. If the message is sent as a reply to another suggested post,
    ///   then that suggested post is automatically declined.
    /// </summary>
    SuggestedPostParameters: ITgSuggestedPostParameters;
    /// <summary>Description of the message to reply to</summary>
    ReplyParameters: ITgReplyParameters;
    /// <summary>
    ///   Additional interface options. A JSON-serialized object for an inline keyboard, custom
    ///   reply keyboard, instructions to remove a reply keyboard or to force a reply from the user.
    ///   Построитель: TTgKeyboard.Inline…, TTgKeyboard.Reply…, TTgKeyboard.Remove,
    ///   TTgKeyboard.ForceReply.
    /// </summary>
    ReplyMarkup: TTgReplyMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры sendRichMessageDraft. Неинициализированная запись пуста
  ///   (Default(TTgSendRichMessageDraftOptions)).
  /// </summary>
  TTgSendRichMessageDraftOptions = record
    /// <summary>Unique identifier for the target message thread</summary>
    MessageThreadId: TTgOptional<Int64>;
    /// <summary>
    ///   Pass True to show the user a button to stop further drafts. The bot will receive an Update
    ///   “stopped_message_generation” if the user presses the button.
    /// </summary>
    CanStop: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to keep the draft in the chat when the button is pressed. The draft will still
    ///   disappear after a short time or if the bot sends a message. To fully preserve the partial
    ///   draft, the bot should send it as a new message.
    /// </summary>
    KeepOnStop: TTgOptional<Boolean>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры answerInlineQuery. Неинициализированная запись пуста
  ///   (Default(TTgAnswerInlineQueryOptions)).
  /// </summary>
  TTgAnswerInlineQueryOptions = record
    /// <summary>
    ///   The maximum amount of time in seconds that the result of the inline query may be cached on
    ///   the server. Defaults to 300.
    /// </summary>
    CacheTime: TTgOptional<Integer>;
    /// <summary>
    ///   Pass True if results may be cached on the server side only for the user that sent the
    ///   query. By default, results may be returned to any user who sends the same query.
    /// </summary>
    IsPersonal: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass the offset that a client should send in the next query with the same text to receive
    ///   more results. Pass an empty string if there are no more results or if you don't support
    ///   pagination. Offset length can't exceed 64 bytes.
    /// </summary>
    NextOffset: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized object describing a button to be shown above inline query results
    /// </summary>
    Button: ITgInlineQueryResultsButton;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры sendInvoice. Неинициализированная запись пуста
  ///   (Default(TTgSendInvoiceOptions)).
  /// </summary>
  TTgSendInvoiceOptions = record
    /// <summary>
    ///   Unique identifier for the target message thread (topic) of a forum; for forum supergroups
    ///   and private chats of bots with forum topic mode enabled only
    /// </summary>
    MessageThreadId: TTgOptional<Int64>;
    /// <summary>
    ///   Identifier of the direct messages topic to which the message will be sent; required if the
    ///   message is sent to a direct messages chat
    /// </summary>
    DirectMessagesTopicId: TTgOptional<Int64>;
    /// <summary>
    ///   Payment provider token, obtained via @BotFather. Pass an empty string for payments in
    ///   Telegram Stars.
    /// </summary>
    ProviderToken: TTgOptional<string>;
    /// <summary>
    ///   The maximum accepted amount for tips in the smallest units of the currency (integer, not
    ///   float/double). For example, for a maximum tip of US$ 1.45 pass max_tip_amount = 145. See
    ///   the exp parameter in currencies.json, it shows the number of digits past the decimal point
    ///   for each currency (2 for the majority of currencies). Defaults to 0. Not supported for
    ///   payments in Telegram Stars.
    /// </summary>
    MaxTipAmount: TTgOptional<Integer>;
    /// <summary>
    ///   A JSON-serialized Array of suggested amounts of tips in the smallest units of the currency
    ///   (integer, not float/double). At most 4 suggested tip amounts can be specified. The
    ///   suggested tip amounts must be positive, passed in a strictly increased order and must not
    ///   exceed max_tip_amount. Не задано — параметр не передаётся; [] — передаётся пустой список.
    /// </summary>
    SuggestedTipAmounts: TTgOptional<TArray<Integer>>;
    /// <summary>
    ///   Unique deep-linking parameter. If left empty, forwarded copies of the sent message will
    ///   have a Pay button, allowing multiple users to pay directly from the forwarded message,
    ///   using the same invoice. If non-empty, forwarded copies of the sent message will have a URL
    ///   button with a deep link to the bot (instead of a Pay button), with the value used as the
    ///   start parameter.
    /// </summary>
    StartParameter: TTgOptional<string>;
    /// <summary>
    ///   JSON-serialized data about the invoice, which will be shared with the payment provider. A
    ///   detailed description of required fields should be provided by the payment provider.
    /// </summary>
    ProviderData: TTgOptional<string>;
    /// <summary>
    ///   URL of the product photo for the invoice. Can be a photo of the goods or a marketing image
    ///   for a service. People like it better when they see what they are paying for.
    /// </summary>
    PhotoUrl: TTgOptional<string>;
    /// <summary>Photo size in bytes</summary>
    PhotoSize: TTgOptional<Integer>;
    /// <summary>Photo width</summary>
    PhotoWidth: TTgOptional<Integer>;
    /// <summary>Photo height</summary>
    PhotoHeight: TTgOptional<Integer>;
    /// <summary>
    ///   Pass True if you require the user's full name to complete the order. Ignored for payments
    ///   in Telegram Stars.
    /// </summary>
    NeedName: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if you require the user's phone number to complete the order. Ignored for
    ///   payments in Telegram Stars.
    /// </summary>
    NeedPhoneNumber: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if you require the user's email address to complete the order. Ignored for
    ///   payments in Telegram Stars.
    /// </summary>
    NeedEmail: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if you require the user's shipping address to complete the order. Ignored for
    ///   payments in Telegram Stars.
    /// </summary>
    NeedShippingAddress: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if the user's phone number should be sent to the provider. Ignored for payments
    ///   in Telegram Stars.
    /// </summary>
    SendPhoneNumberToProvider: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if the user's email address should be sent to the provider. Ignored for payments
    ///   in Telegram Stars.
    /// </summary>
    SendEmailToProvider: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if the final price depends on the shipping method. Ignored for payments in
    ///   Telegram Stars.
    /// </summary>
    IsFlexible: TTgOptional<Boolean>;
    /// <summary>
    ///   Sends the message silently. Users will receive a notification with no sound.
    /// </summary>
    DisableNotification: TTgOptional<Boolean>;
    /// <summary>
    ///   Protects the contents of the sent message from forwarding and saving
    /// </summary>
    ProtectContent: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to allow up to 1000 messages per second, ignoring broadcasting limits for a fee
    ///   of 0.1 Telegram Stars per message. The relevant Stars will be withdrawn from the bot's
    ///   balance.
    /// </summary>
    AllowPaidBroadcast: TTgOptional<Boolean>;
    /// <summary>
    ///   Unique identifier of the message effect to be added to the message; for private chats only
    /// </summary>
    MessageEffectId: TTgOptional<string>;
    /// <summary>
    ///   A JSON-serialized object containing the parameters of the suggested post to send; for
    ///   direct messages chats only. If the message is sent as a reply to another suggested post,
    ///   then that suggested post is automatically declined.
    /// </summary>
    SuggestedPostParameters: ITgSuggestedPostParameters;
    /// <summary>Description of the message to reply to</summary>
    ReplyParameters: ITgReplyParameters;
    /// <summary>
    ///   A JSON-serialized object for an inline keyboard. If empty, one 'Pay total price' button
    ///   will be shown. If not empty, the first button must be a Pay button. Только
    ///   инлайн-клавиатура (ITgInlineKeyboardMarkup): TTgKeyboard.Inline.Row.Button(…) или
    ///   TTgInlineKeyboardMarkup.Create; обычная клавиатура, Remove и ForceReply здесь не
    ///   принимаются.
    /// </summary>
    ReplyMarkup: ITgInlineKeyboardMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры createInvoiceLink. Неинициализированная запись пуста
  ///   (Default(TTgCreateInvoiceLinkOptions)).
  /// </summary>
  TTgCreateInvoiceLinkOptions = record
    /// <summary>
    ///   Unique identifier of the business connection on behalf of which the link will be created.
    ///   For payments in Telegram Stars only.
    /// </summary>
    BusinessConnectionId: TTgOptional<string>;
    /// <summary>
    ///   Payment provider token, obtained via @BotFather. Pass an empty string for payments in
    ///   Telegram Stars.
    /// </summary>
    ProviderToken: TTgOptional<string>;
    /// <summary>
    ///   The number of seconds the subscription will be active for before the next payment. The
    ///   currency must be set to “XTR” (Telegram Stars) if the parameter is used. Currently, it
    ///   must always be 2592000 (30 days) if specified. Any number of subscriptions can be active
    ///   for a given bot at the same time, including multiple concurrent subscriptions from the
    ///   same user. Subscription price must no exceed 10000 Telegram Stars.
    /// </summary>
    SubscriptionPeriod: TTgOptional<Integer>;
    /// <summary>
    ///   The maximum accepted amount for tips in the smallest units of the currency (integer, not
    ///   float/double). For example, for a maximum tip of US$ 1.45 pass max_tip_amount = 145. See
    ///   the exp parameter in currencies.json, it shows the number of digits past the decimal point
    ///   for each currency (2 for the majority of currencies). Defaults to 0. Not supported for
    ///   payments in Telegram Stars.
    /// </summary>
    MaxTipAmount: TTgOptional<Integer>;
    /// <summary>
    ///   A JSON-serialized Array of suggested amounts of tips in the smallest units of the currency
    ///   (integer, not float/double). At most 4 suggested tip amounts can be specified. The
    ///   suggested tip amounts must be positive, passed in a strictly increased order and must not
    ///   exceed max_tip_amount. Не задано — параметр не передаётся; [] — передаётся пустой список.
    /// </summary>
    SuggestedTipAmounts: TTgOptional<TArray<Integer>>;
    /// <summary>
    ///   JSON-serialized data about the invoice, which will be shared with the payment provider. A
    ///   detailed description of required fields should be provided by the payment provider.
    /// </summary>
    ProviderData: TTgOptional<string>;
    /// <summary>
    ///   URL of the product photo for the invoice. Can be a photo of the goods or a marketing image
    ///   for a service.
    /// </summary>
    PhotoUrl: TTgOptional<string>;
    /// <summary>Photo size in bytes</summary>
    PhotoSize: TTgOptional<Integer>;
    /// <summary>Photo width</summary>
    PhotoWidth: TTgOptional<Integer>;
    /// <summary>Photo height</summary>
    PhotoHeight: TTgOptional<Integer>;
    /// <summary>
    ///   Pass True if you require the user's full name to complete the order. Ignored for payments
    ///   in Telegram Stars.
    /// </summary>
    NeedName: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if you require the user's phone number to complete the order. Ignored for
    ///   payments in Telegram Stars.
    /// </summary>
    NeedPhoneNumber: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if you require the user's email address to complete the order. Ignored for
    ///   payments in Telegram Stars.
    /// </summary>
    NeedEmail: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if you require the user's shipping address to complete the order. Ignored for
    ///   payments in Telegram Stars.
    /// </summary>
    NeedShippingAddress: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if the user's phone number should be sent to the provider. Ignored for payments
    ///   in Telegram Stars.
    /// </summary>
    SendPhoneNumberToProvider: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if the user's email address should be sent to the provider. Ignored for payments
    ///   in Telegram Stars.
    /// </summary>
    SendEmailToProvider: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if the final price depends on the shipping method. Ignored for payments in
    ///   Telegram Stars.
    /// </summary>
    IsFlexible: TTgOptional<Boolean>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры answerShippingQuery. Неинициализированная запись пуста
  ///   (Default(TTgAnswerShippingQueryOptions)).
  /// </summary>
  TTgAnswerShippingQueryOptions = record
    /// <summary>
    ///   Required if ok is True. A JSON-serialized Array of available shipping options. Не задано —
    ///   параметр не передаётся; [] — передаётся пустой список.
    /// </summary>
    ShippingOptions: TTgOptional<TArray<ITgShippingOption>>;
    /// <summary>
    ///   Required if ok is False. Error message in human readable form that explains why it is
    ///   impossible to complete the order (e.g. “Sorry, delivery to your desired address is
    ///   unavailable”). Telegram will display this message to the user.
    /// </summary>
    ErrorMessage: TTgOptional<string>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры answerPreCheckoutQuery. Неинициализированная запись пуста
  ///   (Default(TTgAnswerPreCheckoutQueryOptions)).
  /// </summary>
  TTgAnswerPreCheckoutQueryOptions = record
    /// <summary>
    ///   Required if ok is False. Error message in human readable form that explains the reason for
    ///   failure to proceed with the checkout (e.g. "Sorry, somebody just bought the last of our
    ///   amazing black T-shirts while you were busy filling out your payment details. Please choose
    ///   a different color or garment!"). Telegram will display this message to the user.
    /// </summary>
    ErrorMessage: TTgOptional<string>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры getStarTransactions. Неинициализированная запись пуста
  ///   (Default(TTgGetStarTransactionsOptions)).
  /// </summary>
  TTgGetStarTransactionsOptions = record
    /// <summary>Number of transactions to skip in the response</summary>
    Offset: TTgOptional<Integer>;
    /// <summary>
    ///   The maximum number of transactions to be retrieved. Values between 1-100 are accepted.
    ///   Defaults to 100.
    /// </summary>
    Limit: TTgOptional<Integer>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры sendGame. Неинициализированная запись пуста
  ///   (Default(TTgSendGameOptions)).
  /// </summary>
  TTgSendGameOptions = record
    /// <summary>
    ///   Unique identifier of the business connection on behalf of which the message will be sent
    /// </summary>
    BusinessConnectionId: TTgOptional<string>;
    /// <summary>
    ///   Unique identifier for the target message thread (topic) of a forum; for forum supergroups
    ///   and private chats of bots with forum topic mode enabled only
    /// </summary>
    MessageThreadId: TTgOptional<Int64>;
    /// <summary>
    ///   Sends the message silently. Users will receive a notification with no sound.
    /// </summary>
    DisableNotification: TTgOptional<Boolean>;
    /// <summary>
    ///   Protects the contents of the sent message from forwarding and saving
    /// </summary>
    ProtectContent: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True to allow up to 1000 messages per second, ignoring broadcasting limits for a fee
    ///   of 0.1 Telegram Stars per message. The relevant Stars will be withdrawn from the bot's
    ///   balance.
    /// </summary>
    AllowPaidBroadcast: TTgOptional<Boolean>;
    /// <summary>
    ///   Unique identifier of the message effect to be added to the message; for private chats only
    /// </summary>
    MessageEffectId: TTgOptional<string>;
    /// <summary>Description of the message to reply to</summary>
    ReplyParameters: ITgReplyParameters;
    /// <summary>
    ///   A JSON-serialized object for an inline keyboard. If empty, one 'Play game_title' button
    ///   will be shown. If not empty, the first button must launch the game. Только
    ///   инлайн-клавиатура (ITgInlineKeyboardMarkup): TTgKeyboard.Inline.Row.Button(…) или
    ///   TTgInlineKeyboardMarkup.Create; обычная клавиатура, Remove и ForceReply здесь не
    ///   принимаются.
    /// </summary>
    ReplyMarkup: ITgInlineKeyboardMarkup;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры setGameScore. Неинициализированная запись пуста
  ///   (Default(TTgSetGameScoreOptions)).
  /// </summary>
  TTgSetGameScoreOptions = record
    /// <summary>
    ///   Pass True if the high score is allowed to decrease. This can be useful when fixing
    ///   mistakes or banning cheaters.
    /// </summary>
    Force: TTgOptional<Boolean>;
    /// <summary>
    ///   Pass True if the game message should not be automatically edited to include the current
    ///   scoreboard
    /// </summary>
    DisableEditMessage: TTgOptional<Boolean>;
    /// <summary>
    ///   Required if inline_message_id is not specified. Unique identifier for the target chat.
    /// </summary>
    ChatId: TTgOptional<Int64>;
    /// <summary>
    ///   Required if inline_message_id is not specified. Identifier of the sent message.
    /// </summary>
    MessageId: TTgOptional<Int64>;
    /// <summary>
    ///   Required if chat_id and message_id are not specified. Identifier of the inline message.
    /// </summary>
    InlineMessageId: TTgOptional<string>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Необязательные параметры getGameHighScores. Неинициализированная запись пуста
  ///   (Default(TTgGetGameHighScoresOptions)).
  /// </summary>
  TTgGetGameHighScoresOptions = record
    /// <summary>
    ///   Required if inline_message_id is not specified. Unique identifier for the target chat.
    /// </summary>
    ChatId: TTgOptional<Int64>;
    /// <summary>
    ///   Required if inline_message_id is not specified. Identifier of the sent message.
    /// </summary>
    MessageId: TTgOptional<Int64>;
    /// <summary>
    ///   Required if chat_id and message_id are not specified. Identifier of the inline message.
    /// </summary>
    InlineMessageId: TTgOptional<string>;
    /// <summary>Добавляет заданные параметры в запрос.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

