// Gen.Enums.inc — виды полиморфных типов и записи констант.
// Сгенерировано TgBotGen по Telegram Bot API 10.3 (August 24, 2026). Не редактируйте вручную.

  /// <summary>
  ///   Вид объекта MaybeInaccessibleMessage (свойство Kind интерфейса ITgMaybeInaccessibleMessage).
  /// </summary>
  TTgMaybeInaccessibleMessageKind = (
    /// <summary>Значение, неизвестное этой версии библиотеки.</summary>
    Unknown,
    /// <summary>Message.</summary>
    Message,
    /// <summary>InaccessibleMessage.</summary>
    InaccessibleMessage
  );

  /// <summary>
  ///   Вид объекта MessageOrigin (свойство Kind интерфейса ITgMessageOrigin).
  /// </summary>
  TTgMessageOriginKind = (
    /// <summary>Значение, неизвестное этой версии библиотеки.</summary>
    Unknown,
    /// <summary>MessageOriginUser (type = "user").</summary>
    User,
    /// <summary>MessageOriginHiddenUser (type = "hidden_user").</summary>
    HiddenUser,
    /// <summary>MessageOriginChat (type = "chat").</summary>
    Chat,
    /// <summary>MessageOriginChannel (type = "channel").</summary>
    Channel
  );

  /// <summary>Вид объекта PaidMedia (свойство Kind интерфейса ITgPaidMedia).</summary>
  TTgPaidMediaKind = (
    /// <summary>Значение, неизвестное этой версии библиотеки.</summary>
    Unknown,
    /// <summary>PaidMediaLivePhoto (type = "live_photo").</summary>
    LivePhoto,
    /// <summary>PaidMediaPhoto (type = "photo").</summary>
    Photo,
    /// <summary>PaidMediaPreview (type = "preview").</summary>
    Preview,
    /// <summary>PaidMediaVideo (type = "video").</summary>
    Video
  );

  /// <summary>
  ///   Вид объекта BackgroundFill (свойство Kind интерфейса ITgBackgroundFill).
  /// </summary>
  TTgBackgroundFillKind = (
    /// <summary>Значение, неизвестное этой версии библиотеки.</summary>
    Unknown,
    /// <summary>BackgroundFillSolid (type = "solid").</summary>
    Solid,
    /// <summary>BackgroundFillGradient (type = "gradient").</summary>
    Gradient,
    /// <summary>BackgroundFillFreeformGradient (type = "freeform_gradient").</summary>
    FreeformGradient
  );

  /// <summary>
  ///   Вид объекта BackgroundType (свойство Kind интерфейса ITgBackgroundType).
  /// </summary>
  TTgBackgroundTypeKind = (
    /// <summary>Значение, неизвестное этой версии библиотеки.</summary>
    Unknown,
    /// <summary>BackgroundTypeFill (type = "fill").</summary>
    Fill,
    /// <summary>BackgroundTypeWallpaper (type = "wallpaper").</summary>
    Wallpaper,
    /// <summary>BackgroundTypePattern (type = "pattern").</summary>
    Pattern,
    /// <summary>BackgroundTypeChatTheme (type = "chat_theme").</summary>
    ChatTheme
  );

  /// <summary>Вид объекта ChatMember (свойство Kind интерфейса ITgChatMember).</summary>
  TTgChatMemberKind = (
    /// <summary>Значение, неизвестное этой версии библиотеки.</summary>
    Unknown,
    /// <summary>ChatMemberOwner (status = "creator").</summary>
    Owner,
    /// <summary>ChatMemberAdministrator (status = "administrator").</summary>
    Administrator,
    /// <summary>ChatMemberMember (status = "member").</summary>
    Member,
    /// <summary>ChatMemberRestricted (status = "restricted").</summary>
    Restricted,
    /// <summary>ChatMemberLeft (status = "left").</summary>
    Left,
    /// <summary>ChatMemberBanned (status = "kicked").</summary>
    Banned
  );

  /// <summary>
  ///   Вид объекта ReactionType (свойство Kind интерфейса ITgReactionType).
  /// </summary>
  TTgReactionTypeKind = (
    /// <summary>Значение, неизвестное этой версии библиотеки.</summary>
    Unknown,
    /// <summary>ReactionTypeEmoji (type = "emoji").</summary>
    Emoji,
    /// <summary>ReactionTypeCustomEmoji (type = "custom_emoji").</summary>
    CustomEmoji,
    /// <summary>ReactionTypePaid (type = "paid").</summary>
    Paid
  );

  /// <summary>Вид объекта OwnedGift (свойство Kind интерфейса ITgOwnedGift).</summary>
  TTgOwnedGiftKind = (
    /// <summary>Значение, неизвестное этой версии библиотеки.</summary>
    Unknown,
    /// <summary>OwnedGiftRegular (type = "regular").</summary>
    Regular,
    /// <summary>OwnedGiftUnique (type = "unique").</summary>
    Unique
  );

  /// <summary>Вид объекта MenuButton (свойство Kind интерфейса ITgMenuButton).</summary>
  TTgMenuButtonKind = (
    /// <summary>Значение, неизвестное этой версии библиотеки.</summary>
    Unknown,
    /// <summary>MenuButtonCommands (type = "commands").</summary>
    Commands,
    /// <summary>MenuButtonWebApp (type = "web_app").</summary>
    WebApp,
    /// <summary>MenuButtonDefault (type = "default").</summary>
    Default
  );

  /// <summary>
  ///   Вид объекта ChatBoostSource (свойство Kind интерфейса ITgChatBoostSource).
  /// </summary>
  TTgChatBoostSourceKind = (
    /// <summary>Значение, неизвестное этой версии библиотеки.</summary>
    Unknown,
    /// <summary>ChatBoostSourcePremium (source = "premium").</summary>
    Premium,
    /// <summary>ChatBoostSourceGiftCode (source = "gift_code").</summary>
    GiftCode,
    /// <summary>ChatBoostSourceGiveaway (source = "giveaway").</summary>
    Giveaway
  );

  /// <summary>Вид объекта RichText (свойство Kind интерфейса ITgRichText).</summary>
  TTgRichTextKind = (
    /// <summary>Значение, неизвестное этой версии библиотеки.</summary>
    Unknown,
    /// <summary>RichTextBold (type = "bold").</summary>
    Bold,
    /// <summary>RichTextItalic (type = "italic").</summary>
    Italic,
    /// <summary>RichTextUnderline (type = "underline").</summary>
    Underline,
    /// <summary>RichTextStrikethrough (type = "strikethrough").</summary>
    Strikethrough,
    /// <summary>RichTextSpoiler (type = "spoiler").</summary>
    Spoiler,
    /// <summary>RichTextDateTime (type = "date_time").</summary>
    DateTime,
    /// <summary>RichTextTextMention (type = "text_mention").</summary>
    TextMention,
    /// <summary>RichTextSubscript (type = "subscript").</summary>
    Subscript,
    /// <summary>RichTextSuperscript (type = "superscript").</summary>
    Superscript,
    /// <summary>RichTextMarked (type = "marked").</summary>
    Marked,
    /// <summary>RichTextCode (type = "code").</summary>
    Code,
    /// <summary>RichTextCustomEmoji (type = "custom_emoji").</summary>
    CustomEmoji,
    /// <summary>
    ///   RichTextMathematicalExpression (type = "mathematical_expression").
    /// </summary>
    MathematicalExpression,
    /// <summary>RichTextUrl (type = "url").</summary>
    Url,
    /// <summary>RichTextEmailAddress (type = "email_address").</summary>
    EmailAddress,
    /// <summary>RichTextPhoneNumber (type = "phone_number").</summary>
    PhoneNumber,
    /// <summary>RichTextBankCardNumber (type = "bank_card_number").</summary>
    BankCardNumber,
    /// <summary>RichTextMention (type = "mention").</summary>
    Mention,
    /// <summary>RichTextHashtag (type = "hashtag").</summary>
    Hashtag,
    /// <summary>RichTextCashtag (type = "cashtag").</summary>
    Cashtag,
    /// <summary>RichTextBotCommand (type = "bot_command").</summary>
    BotCommand,
    /// <summary>RichTextButton (type = "button").</summary>
    Button,
    /// <summary>RichTextAnchor (type = "anchor").</summary>
    Anchor,
    /// <summary>RichTextAnchorLink (type = "anchor_link").</summary>
    AnchorLink,
    /// <summary>RichTextReference (type = "reference").</summary>
    Reference,
    /// <summary>RichTextReferenceLink (type = "reference_link").</summary>
    ReferenceLink,
    /// <summary>RichTextPlain.</summary>
    Plain,
    /// <summary>RichTextList.</summary>
    List
  );

  /// <summary>Вид объекта RichBlock (свойство Kind интерфейса ITgRichBlock).</summary>
  TTgRichBlockKind = (
    /// <summary>Значение, неизвестное этой версии библиотеки.</summary>
    Unknown,
    /// <summary>RichBlockParagraph (type = "paragraph").</summary>
    Paragraph,
    /// <summary>RichBlockSectionHeading (type = "heading").</summary>
    SectionHeading,
    /// <summary>RichBlockPreformatted (type = "pre").</summary>
    Preformatted,
    /// <summary>RichBlockFooter (type = "footer").</summary>
    Footer,
    /// <summary>RichBlockDivider (type = "divider").</summary>
    Divider,
    /// <summary>
    ///   RichBlockMathematicalExpression (type = "mathematical_expression").
    /// </summary>
    MathematicalExpression,
    /// <summary>RichBlockAnchor (type = "anchor").</summary>
    Anchor,
    /// <summary>RichBlockList (type = "list").</summary>
    List,
    /// <summary>RichBlockBlockQuotation (type = "blockquote").</summary>
    BlockQuotation,
    /// <summary>
    ///   RichBlockExpandableBlockQuotation (type = "expandable_blockquote").
    /// </summary>
    ExpandableBlockQuotation,
    /// <summary>RichBlockPullQuotation (type = "pullquote").</summary>
    PullQuotation,
    /// <summary>RichBlockCollage (type = "collage").</summary>
    Collage,
    /// <summary>RichBlockSlideshow (type = "slideshow").</summary>
    Slideshow,
    /// <summary>RichBlockTable (type = "table").</summary>
    Table,
    /// <summary>RichBlockDetails (type = "details").</summary>
    Details,
    /// <summary>RichBlockMap (type = "map").</summary>
    Map,
    /// <summary>RichBlockButtons (type = "buttons").</summary>
    Buttons,
    /// <summary>RichBlockAnimation (type = "animation").</summary>
    Animation,
    /// <summary>RichBlockAudio (type = "audio").</summary>
    Audio,
    /// <summary>RichBlockDocument (type = "document").</summary>
    Document,
    /// <summary>RichBlockPhoto (type = "photo").</summary>
    Photo,
    /// <summary>RichBlockVideo (type = "video").</summary>
    Video,
    /// <summary>RichBlockVoiceNote (type = "voice_note").</summary>
    VoiceNote,
    /// <summary>RichBlockThinking (type = "thinking").</summary>
    Thinking
  );

  /// <summary>
  ///   Вид объекта RevenueWithdrawalState (свойство Kind интерфейса ITgRevenueWithdrawalState).
  /// </summary>
  TTgRevenueWithdrawalStateKind = (
    /// <summary>Значение, неизвестное этой версии библиотеки.</summary>
    Unknown,
    /// <summary>RevenueWithdrawalStatePending (type = "pending").</summary>
    Pending,
    /// <summary>RevenueWithdrawalStateSucceeded (type = "succeeded").</summary>
    Succeeded,
    /// <summary>RevenueWithdrawalStateFailed (type = "failed").</summary>
    Failed
  );

  /// <summary>
  ///   Вид объекта TransactionPartner (свойство Kind интерфейса ITgTransactionPartner).
  /// </summary>
  TTgTransactionPartnerKind = (
    /// <summary>Значение, неизвестное этой версии библиотеки.</summary>
    Unknown,
    /// <summary>TransactionPartnerUser (type = "user").</summary>
    User,
    /// <summary>TransactionPartnerChat (type = "chat").</summary>
    Chat,
    /// <summary>TransactionPartnerAffiliateProgram (type = "affiliate_program").</summary>
    AffiliateProgram,
    /// <summary>TransactionPartnerFragment (type = "fragment").</summary>
    Fragment,
    /// <summary>TransactionPartnerTelegramAds (type = "telegram_ads").</summary>
    TelegramAds,
    /// <summary>TransactionPartnerTelegramApi (type = "telegram_api").</summary>
    TelegramApi,
    /// <summary>TransactionPartnerOther (type = "other").</summary>
    Other
  );

  /// <summary>Режимы разметки текста (parse_mode).</summary>
  TTgParseMode = record
  const
    Html = 'HTML';
    MarkdownV2 = 'MarkdownV2';
    Markdown = 'Markdown';
  end;

  /// <summary>Типы чатов (Chat.type).</summary>
  TTgChatType = record
  const
    &Private = 'private';
    Group = 'group';
    Supergroup = 'supergroup';
    Channel = 'channel';
  end;

  /// <summary>Действия для sendChatAction.</summary>
  TTgChatAction = record
  const
    Typing = 'typing';
    UploadPhoto = 'upload_photo';
    RecordVideo = 'record_video';
    UploadVideo = 'upload_video';
    RecordVoice = 'record_voice';
    UploadVoice = 'upload_voice';
    UploadDocument = 'upload_document';
    ChooseSticker = 'choose_sticker';
    FindLocation = 'find_location';
    RecordVideoNote = 'record_video_note';
    UploadVideoNote = 'upload_video_note';
  end;

  /// <summary>Типы сущностей сообщения (MessageEntity.type).</summary>
  TTgMessageEntityType = record
  const
    Mention = 'mention';
    Hashtag = 'hashtag';
    Cashtag = 'cashtag';
    BotCommand = 'bot_command';
    Url = 'url';
    Email = 'email';
    PhoneNumber = 'phone_number';
    Bold = 'bold';
    Italic = 'italic';
    Underline = 'underline';
    Strikethrough = 'strikethrough';
    Spoiler = 'spoiler';
    Blockquote = 'blockquote';
    ExpandableBlockquote = 'expandable_blockquote';
    Code = 'code';
    Pre = 'pre';
    TextLink = 'text_link';
    TextMention = 'text_mention';
    CustomEmoji = 'custom_emoji';
    DateTime = 'date_time';
  end;

  /// <summary>Типы опросов (sendPoll.type, Poll.type).</summary>
  TTgPollType = record
  const
    Regular = 'regular';
    Quiz = 'quiz';
  end;

  /// <summary>Типы стикеров (Sticker.type).</summary>
  TTgStickerType = record
  const
    Regular = 'regular';
    Mask = 'mask';
    CustomEmoji = 'custom_emoji';
  end;

  /// <summary>Типы обновлений (значения allowed_updates), по полям Update.</summary>
  TTgUpdateType = record
  const
    Message = 'message';
    EditedMessage = 'edited_message';
    ChannelPost = 'channel_post';
    EditedChannelPost = 'edited_channel_post';
    BusinessConnection = 'business_connection';
    BusinessMessage = 'business_message';
    EditedBusinessMessage = 'edited_business_message';
    DeletedBusinessMessages = 'deleted_business_messages';
    GuestMessage = 'guest_message';
    MessageReaction = 'message_reaction';
    MessageReactionCount = 'message_reaction_count';
    InlineQuery = 'inline_query';
    ChosenInlineResult = 'chosen_inline_result';
    CallbackQuery = 'callback_query';
    ShippingQuery = 'shipping_query';
    PreCheckoutQuery = 'pre_checkout_query';
    PurchasedPaidMedia = 'purchased_paid_media';
    Poll = 'poll';
    PollAnswer = 'poll_answer';
    MyChatMember = 'my_chat_member';
    ChatMember = 'chat_member';
    ChatJoinRequest = 'chat_join_request';
    ChatBoost = 'chat_boost';
    RemovedChatBoost = 'removed_chat_boost';
    ManagedBot = 'managed_bot';
    Subscription = 'subscription';
    StoppedMessageGeneration = 'stopped_message_generation';
  end;

