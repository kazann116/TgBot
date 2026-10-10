// Gen.Intf.inc — интерфейсы объектов Bot API (база раньше вариантов).
// Сгенерировано TgBotGen по Telegram Bot API 10.3 (August 24, 2026). Не редактируйте вручную.

  /// <summary>
  ///   This object represents an incoming update. At most one of the optional fields can be present
  ///   in any given update.
  /// </summary>
  ITgUpdate = interface(ITgJsonObject)
    ['{22DBE816-FD8E-5299-A762-E8F72A87EEB1}']
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
    /// <summary>
    ///   The update's unique identifier. Update identifiers start from a certain positive number
    ///   and increase sequentially. This identifier becomes especially handy if you're using
    ///   webhooks, since it allows you to ignore repeated updates or to restore the correct update
    ///   sequence, should they get out of order. If there are no new updates for at least a week,
    ///   then identifier of the next update will be chosen randomly instead of sequentially.
    /// </summary>
    property UpdateId: Int64 read GetUpdateId;
    /// <summary>
    ///   Optional. New incoming message of any kind - text, photo, sticker, etc.
    /// </summary>
    property Message: ITgMessage read GetMessage;
    /// <summary>
    ///   Optional. New version of a message that is known to the bot and was edited. This update
    ///   may at times be triggered by changes to message fields that are either unavailable or not
    ///   actively used by your bot.
    /// </summary>
    property EditedMessage: ITgMessage read GetEditedMessage;
    /// <summary>
    ///   Optional. New incoming channel post of any kind - text, photo, sticker, etc.
    /// </summary>
    property ChannelPost: ITgMessage read GetChannelPost;
    /// <summary>
    ///   Optional. New version of a channel post that is known to the bot and was edited. This
    ///   update may at times be triggered by changes to message fields that are either unavailable
    ///   or not actively used by your bot.
    /// </summary>
    property EditedChannelPost: ITgMessage read GetEditedChannelPost;
    /// <summary>
    ///   Optional. The bot was connected to or disconnected from a business account, or a user
    ///   edited an existing connection with the bot
    /// </summary>
    property BusinessConnection: ITgBusinessConnection read GetBusinessConnection;
    /// <summary>Optional. New message from a connected business account</summary>
    property BusinessMessage: ITgMessage read GetBusinessMessage;
    /// <summary>
    ///   Optional. New version of a message from a connected business account
    /// </summary>
    property EditedBusinessMessage: ITgMessage read GetEditedBusinessMessage;
    /// <summary>Optional. Messages were deleted from a connected business account</summary>
    property DeletedBusinessMessages: ITgBusinessMessagesDeleted read GetDeletedBusinessMessages;
    /// <summary>
    ///   Optional. New guest message. The bot can use the field Message.guest_query_id and the
    ///   method answerGuestQuery to send a message in response.
    /// </summary>
    property GuestMessage: ITgMessage read GetGuestMessage;
    /// <summary>
    ///   Optional. A reaction to a message was changed by a user. The bot must be an administrator
    ///   in the chat and must explicitly specify "message_reaction" in the list of allowed_updates
    ///   to receive these updates. The update isn't received for reactions set by bots.
    /// </summary>
    property MessageReaction: ITgMessageReactionUpdated read GetMessageReaction;
    /// <summary>
    ///   Optional. Reactions to a message with anonymous reactions were changed. The bot must be an
    ///   administrator in the chat and must explicitly specify "message_reaction_count" in the list
    ///   of allowed_updates to receive these updates. The updates are grouped and can be sent with
    ///   delay up to a few minutes.
    /// </summary>
    property MessageReactionCount: ITgMessageReactionCountUpdated read GetMessageReactionCount;
    /// <summary>Optional. New incoming inline query</summary>
    property InlineQuery: ITgInlineQuery read GetInlineQuery;
    /// <summary>
    ///   Optional. The result of an inline query that was chosen by a user and sent to their chat
    ///   partner. Please see our documentation on the feedback collecting for details on how to
    ///   enable these updates for your bot.
    /// </summary>
    property ChosenInlineResult: ITgChosenInlineResult read GetChosenInlineResult;
    /// <summary>Optional. New incoming callback query</summary>
    property CallbackQuery: ITgCallbackQuery read GetCallbackQuery;
    /// <summary>
    ///   Optional. New incoming shipping query. Only for invoices with flexible price.
    /// </summary>
    property ShippingQuery: ITgShippingQuery read GetShippingQuery;
    /// <summary>
    ///   Optional. New incoming pre-checkout query. Contains full information about checkout.
    /// </summary>
    property PreCheckoutQuery: ITgPreCheckoutQuery read GetPreCheckoutQuery;
    /// <summary>
    ///   Optional. A user purchased paid media with a non-empty payload sent by the bot in a
    ///   non-channel chat
    /// </summary>
    property PurchasedPaidMedia: ITgPaidMediaPurchased read GetPurchasedPaidMedia;
    /// <summary>
    ///   Optional. New poll state. Bots receive only updates about manually stopped polls and
    ///   polls, which are sent by the bot.
    /// </summary>
    property Poll: ITgPoll read GetPoll;
    /// <summary>
    ///   Optional. A user changed their answer in a non-anonymous poll. Bots receive new votes only
    ///   in polls that were sent by the bot itself.
    /// </summary>
    property PollAnswer: ITgPollAnswer read GetPollAnswer;
    /// <summary>
    ///   Optional. The bot's chat member status was updated in a chat. For private chats, this
    ///   update is received only when the bot is blocked or unblocked by the user.
    /// </summary>
    property MyChatMember: ITgChatMemberUpdated read GetMyChatMember;
    /// <summary>
    ///   Optional. A chat member's status was updated in a chat. The bot must be an administrator
    ///   in the chat and must explicitly specify "chat_member" in the list of allowed_updates to
    ///   receive these updates.
    /// </summary>
    property ChatMember: ITgChatMemberUpdated read GetChatMember;
    /// <summary>
    ///   Optional. A request to join the chat has been sent. The bot must have the can_invite_users
    ///   administrator right in the chat to receive these updates.
    /// </summary>
    property ChatJoinRequest: ITgChatJoinRequest read GetChatJoinRequest;
    /// <summary>
    ///   Optional. A chat boost was added or changed. The bot must be an administrator in the chat
    ///   to receive these updates.
    /// </summary>
    property ChatBoost: ITgChatBoostUpdated read GetChatBoost;
    /// <summary>
    ///   Optional. A boost was removed from a chat. The bot must be an administrator in the chat to
    ///   receive these updates.
    /// </summary>
    property RemovedChatBoost: ITgChatBoostRemoved read GetRemovedChatBoost;
    /// <summary>
    ///   Optional. A new bot was created to be managed by the bot, or token or owner of a managed
    ///   bot was changed
    /// </summary>
    property ManagedBot: ITgManagedBotUpdated read GetManagedBot;
    /// <summary>Optional. User payment subscription has changed</summary>
    property Subscription: ITgBotSubscriptionUpdated read GetSubscription;
    /// <summary>
    ///   Optional. A user asked the bot to stop the generation of a message
    /// </summary>
    property StoppedMessageGeneration: ITgMessageGenerationStopped read GetStoppedMessageGeneration;
  end;

  /// <summary>Describes the current status of a webhook.</summary>
  ITgWebhookInfo = interface(ITgJsonObject)
    ['{F21228F7-D7CB-56F3-8784-0165A4DDC535}']
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
    /// <summary>Webhook URL, may be empty if webhook is not set up</summary>
    property Url: string read GetUrl;
    /// <summary>
    ///   True, if a custom certificate was provided for webhook certificate checks
    /// </summary>
    property HasCustomCertificate: Boolean read GetHasCustomCertificate;
    /// <summary>Number of updates awaiting delivery</summary>
    property PendingUpdateCount: Integer read GetPendingUpdateCount;
    /// <summary>Optional. Currently used webhook IP address</summary>
    property IpAddress: string read GetIpAddress;
    /// <summary>
    ///   Optional. Unix time for the most recent error that happened when trying to deliver an
    ///   update via webhook
    /// </summary>
    property LastErrorDate: Int64 read GetLastErrorDate;
    /// <summary>Поле last_error_date присутствует.</summary>
    property HasLastErrorDate: Boolean read GetHasLastErrorDate;
    /// <summary>
    ///   Optional. Error message in human-readable format for the most recent error that happened
    ///   when trying to deliver an update via webhook
    /// </summary>
    property LastErrorMessage: string read GetLastErrorMessage;
    /// <summary>
    ///   Optional. Unix time of the most recent error that happened when trying to synchronize
    ///   available updates with Telegram datacenters
    /// </summary>
    property LastSynchronizationErrorDate: Int64 read GetLastSynchronizationErrorDate;
    /// <summary>Поле last_synchronization_error_date присутствует.</summary>
    property HasLastSynchronizationErrorDate: Boolean read GetHasLastSynchronizationErrorDate;
    /// <summary>
    ///   Optional. The maximum allowed number of simultaneous HTTPS connections to the webhook for
    ///   update delivery
    /// </summary>
    property MaxConnections: Integer read GetMaxConnections;
    /// <summary>Поле max_connections присутствует.</summary>
    property HasMaxConnections: Boolean read GetHasMaxConnections;
    /// <summary>
    ///   Optional. A list of update types the bot is subscribed to. Defaults to all update types
    ///   except chat_member, message_reaction, and message_reaction_count.
    /// </summary>
    property AllowedUpdates: TArray<string> read GetAllowedUpdates;
  end;

  /// <summary>This object represents a Telegram user or bot.</summary>
  ITgUser = interface(ITgJsonObject)
    ['{8A3A205A-0DE7-5F42-AF6D-E5CBD02E2B70}']
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
    /// <summary>
    ///   Задаёт id: Unique identifier for this user or bot. This number may have more than 32
    ///   significant bits and some programming languages may have difficulty/silent defects in
    ///   interpreting it. But it has at most 52 significant bits, so a 64-bit integer or
    ///   double-precision float type are safe for storing this identifier. Значение копируется в
    ///   момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithId(AValue: Int64): ITgUser;
    /// <summary>
    ///   Задаёт is_bot: True, if this user is a bot. Значение копируется в момент вызова:
    ///   последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithIsBot(AValue: Boolean): ITgUser;
    /// <summary>
    ///   Задаёт first_name: User's or bot's first name. Значение копируется в момент вызова:
    ///   последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithFirstName(const AValue: string): ITgUser;
    /// <summary>
    ///   Задаёт last_name: Optional. User's or bot's last name. Значение копируется в момент
    ///   вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithLastName(const AValue: string): ITgUser;
    /// <summary>
    ///   Задаёт username: Optional. User's or bot's username. Значение копируется в момент вызова:
    ///   последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithUsername(const AValue: string): ITgUser;
    /// <summary>
    ///   Задаёт language_code: Optional. IETF language tag of the user's language. Значение
    ///   копируется в момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithLanguageCode(const AValue: string): ITgUser;
    /// <summary>
    ///   Задаёт is_premium: Optional. True, if this user is a Telegram Premium user. Значение
    ///   копируется в момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithIsPremium(AValue: Boolean): ITgUser;
    /// <summary>
    ///   Задаёт added_to_attachment_menu: Optional. True, if this user added the bot to the
    ///   attachment menu. Значение копируется в момент вызова: последующие изменения переданного
    ///   объекта на этот не влияют.
    /// </summary>
    function WithAddedToAttachmentMenu(AValue: Boolean): ITgUser;
    /// <summary>
    ///   Задаёт can_join_groups: Optional. True, if the bot can be invited to groups. Returned only
    ///   in getMe. Значение копируется в момент вызова: последующие изменения переданного объекта
    ///   на этот не влияют.
    /// </summary>
    function WithCanJoinGroups(AValue: Boolean): ITgUser;
    /// <summary>
    ///   Задаёт can_read_all_group_messages: Optional. True, if privacy mode is disabled for the
    ///   bot. Returned only in getMe. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithCanReadAllGroupMessages(AValue: Boolean): ITgUser;
    /// <summary>
    ///   Задаёт supports_guest_queries: Optional. True, if the bot supports guest queries from
    ///   chats it is not a member of. Returned only in getMe. Значение копируется в момент вызова:
    ///   последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithSupportsGuestQueries(AValue: Boolean): ITgUser;
    /// <summary>
    ///   Задаёт supports_inline_queries: Optional. True, if the bot supports inline queries.
    ///   Returned only in getMe. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithSupportsInlineQueries(AValue: Boolean): ITgUser;
    /// <summary>
    ///   Задаёт can_connect_to_business: Optional. True, if the bot can be connected to a user
    ///   account to manage it. Returned only in getMe. Значение копируется в момент вызова:
    ///   последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithCanConnectToBusiness(AValue: Boolean): ITgUser;
    /// <summary>
    ///   Задаёт has_main_web_app: Optional. True, if the bot has a main Web App. Returned only in
    ///   getMe. Значение копируется в момент вызова: последующие изменения переданного объекта на
    ///   этот не влияют.
    /// </summary>
    function WithHasMainWebApp(AValue: Boolean): ITgUser;
    /// <summary>
    ///   Задаёт has_topics_enabled: Optional. True, if the bot has forum topic mode enabled in
    ///   private chats. Returned only in getMe. Значение копируется в момент вызова: последующие
    ///   изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithHasTopicsEnabled(AValue: Boolean): ITgUser;
    /// <summary>
    ///   Задаёт allows_users_to_create_topics: Optional. True, if the bot allows users to create
    ///   and delete topics in private chats. Returned only in getMe. Значение копируется в момент
    ///   вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithAllowsUsersToCreateTopics(AValue: Boolean): ITgUser;
    /// <summary>
    ///   Задаёт can_manage_bots: Optional. True, if other bots can be created to be controlled by
    ///   the bot. Returned only in getMe. Значение копируется в момент вызова: последующие
    ///   изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithCanManageBots(AValue: Boolean): ITgUser;
    /// <summary>
    ///   Задаёт supports_join_request_queries: Optional. True, if the bot supports join request
    ///   queries and can be assigned to process them. Returned only in getMe. Значение копируется в
    ///   момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithSupportsJoinRequestQueries(AValue: Boolean): ITgUser;
    /// <summary>
    ///   Unique identifier for this user or bot. This number may have more than 32 significant bits
    ///   and some programming languages may have difficulty/silent defects in interpreting it. But
    ///   it has at most 52 significant bits, so a 64-bit integer or double-precision float type are
    ///   safe for storing this identifier.
    /// </summary>
    property Id: Int64 read GetId;
    /// <summary>True, if this user is a bot</summary>
    property IsBot: Boolean read GetIsBot;
    /// <summary>User's or bot's first name</summary>
    property FirstName: string read GetFirstName;
    /// <summary>Optional. User's or bot's last name</summary>
    property LastName: string read GetLastName;
    /// <summary>Optional. User's or bot's username</summary>
    property Username: string read GetUsername;
    /// <summary>Optional. IETF language tag of the user's language</summary>
    property LanguageCode: string read GetLanguageCode;
    /// <summary>Optional. True, if this user is a Telegram Premium user</summary>
    property IsPremium: Boolean read GetIsPremium;
    /// <summary>Optional. True, if this user added the bot to the attachment menu</summary>
    property AddedToAttachmentMenu: Boolean read GetAddedToAttachmentMenu;
    /// <summary>
    ///   Optional. True, if the bot can be invited to groups. Returned only in getMe.
    /// </summary>
    property CanJoinGroups: Boolean read GetCanJoinGroups;
    /// <summary>Поле can_join_groups присутствует.</summary>
    property HasCanJoinGroups: Boolean read GetHasCanJoinGroups;
    /// <summary>
    ///   Optional. True, if privacy mode is disabled for the bot. Returned only in getMe.
    /// </summary>
    property CanReadAllGroupMessages: Boolean read GetCanReadAllGroupMessages;
    /// <summary>Поле can_read_all_group_messages присутствует.</summary>
    property HasCanReadAllGroupMessages: Boolean read GetHasCanReadAllGroupMessages;
    /// <summary>
    ///   Optional. True, if the bot supports guest queries from chats it is not a member of.
    ///   Returned only in getMe.
    /// </summary>
    property SupportsGuestQueries: Boolean read GetSupportsGuestQueries;
    /// <summary>Поле supports_guest_queries присутствует.</summary>
    property HasSupportsGuestQueries: Boolean read GetHasSupportsGuestQueries;
    /// <summary>
    ///   Optional. True, if the bot supports inline queries. Returned only in getMe.
    /// </summary>
    property SupportsInlineQueries: Boolean read GetSupportsInlineQueries;
    /// <summary>Поле supports_inline_queries присутствует.</summary>
    property HasSupportsInlineQueries: Boolean read GetHasSupportsInlineQueries;
    /// <summary>
    ///   Optional. True, if the bot can be connected to a user account to manage it. Returned only
    ///   in getMe.
    /// </summary>
    property CanConnectToBusiness: Boolean read GetCanConnectToBusiness;
    /// <summary>Поле can_connect_to_business присутствует.</summary>
    property HasCanConnectToBusiness: Boolean read GetHasCanConnectToBusiness;
    /// <summary>
    ///   Optional. True, if the bot has a main Web App. Returned only in getMe.
    /// </summary>
    property HasMainWebApp: Boolean read GetHasMainWebApp;
    /// <summary>
    ///   Optional. True, if the bot has forum topic mode enabled in private chats. Returned only in
    ///   getMe.
    /// </summary>
    property HasTopicsEnabled: Boolean read GetHasTopicsEnabled;
    /// <summary>
    ///   Optional. True, if the bot allows users to create and delete topics in private chats.
    ///   Returned only in getMe.
    /// </summary>
    property AllowsUsersToCreateTopics: Boolean read GetAllowsUsersToCreateTopics;
    /// <summary>Поле allows_users_to_create_topics присутствует.</summary>
    property HasAllowsUsersToCreateTopics: Boolean read GetHasAllowsUsersToCreateTopics;
    /// <summary>
    ///   Optional. True, if other bots can be created to be controlled by the bot. Returned only in
    ///   getMe.
    /// </summary>
    property CanManageBots: Boolean read GetCanManageBots;
    /// <summary>Поле can_manage_bots присутствует.</summary>
    property HasCanManageBots: Boolean read GetHasCanManageBots;
    /// <summary>
    ///   Optional. True, if the bot supports join request queries and can be assigned to process
    ///   them. Returned only in getMe.
    /// </summary>
    property SupportsJoinRequestQueries: Boolean read GetSupportsJoinRequestQueries;
    /// <summary>Поле supports_join_request_queries присутствует.</summary>
    property HasSupportsJoinRequestQueries: Boolean read GetHasSupportsJoinRequestQueries;
  end;

  /// <summary>This object represents a chat.</summary>
  ITgChat = interface(ITgJsonObject)
    ['{A82244DC-8BDD-5B2D-AE25-1B402F93EDA7}']
    function GetId: Int64;
    function GetChatType: string;
    function GetTitle: string;
    function GetUsername: string;
    function GetFirstName: string;
    function GetLastName: string;
    function GetIsForum: Boolean;
    function GetIsDirectMessages: Boolean;
    /// <summary>
    ///   Unique identifier for this chat. This number may have more than 32 significant bits and
    ///   some programming languages may have difficulty/silent defects in interpreting it. But it
    ///   has at most 52 significant bits, so a signed 64-bit integer or double-precision float type
    ///   are safe for storing this identifier.
    /// </summary>
    property Id: Int64 read GetId;
    /// <summary>
    ///   Type of the chat, can be either “private”, “group”, “supergroup” or “channel”
    /// </summary>
    property ChatType: string read GetChatType;
    /// <summary>Optional. Title, for supergroups, channels and group chats</summary>
    property Title: string read GetTitle;
    /// <summary>
    ///   Optional. Username, for private chats, supergroups and channels if available
    /// </summary>
    property Username: string read GetUsername;
    /// <summary>Optional. First name of the other party in a private chat</summary>
    property FirstName: string read GetFirstName;
    /// <summary>Optional. Last name of the other party in a private chat</summary>
    property LastName: string read GetLastName;
    /// <summary>
    ///   Optional. True, if the supergroup chat is a forum (has topics enabled)
    /// </summary>
    property IsForum: Boolean read GetIsForum;
    /// <summary>
    ///   Optional. True, if the chat is the direct messages chat of a channel
    /// </summary>
    property IsDirectMessages: Boolean read GetIsDirectMessages;
  end;

  /// <summary>This object contains full information about a chat.</summary>
  ITgChatFullInfo = interface(ITgJsonObject)
    ['{B5914F4D-E659-5C3B-B22A-E94E6C993CBE}']
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
    /// <summary>
    ///   Unique identifier for this chat. This number may have more than 32 significant bits and
    ///   some programming languages may have difficulty/silent defects in interpreting it. But it
    ///   has at most 52 significant bits, so a signed 64-bit integer or double-precision float type
    ///   are safe for storing this identifier.
    /// </summary>
    property Id: Int64 read GetId;
    /// <summary>
    ///   Type of the chat, can be either “private”, “group”, “supergroup” or “channel”
    /// </summary>
    property ChatFullInfoType: string read GetChatFullInfoType;
    /// <summary>Optional. Title, for supergroups, channels and group chats</summary>
    property Title: string read GetTitle;
    /// <summary>
    ///   Optional. Username, for private chats, supergroups and channels if available
    /// </summary>
    property Username: string read GetUsername;
    /// <summary>Optional. First name of the other party in a private chat</summary>
    property FirstName: string read GetFirstName;
    /// <summary>Optional. Last name of the other party in a private chat</summary>
    property LastName: string read GetLastName;
    /// <summary>
    ///   Optional. True, if the supergroup chat is a forum (has topics enabled)
    /// </summary>
    property IsForum: Boolean read GetIsForum;
    /// <summary>
    ///   Optional. True, if the chat is the direct messages chat of a channel
    /// </summary>
    property IsDirectMessages: Boolean read GetIsDirectMessages;
    /// <summary>
    ///   Identifier of the accent color for the chat name and backgrounds of the chat photo, reply
    ///   header, and link preview. See accent colors for more details.
    /// </summary>
    property AccentColorId: Int64 read GetAccentColorId;
    /// <summary>
    ///   The maximum number of reactions that can be set on a message in the chat
    /// </summary>
    property MaxReactionCount: Integer read GetMaxReactionCount;
    /// <summary>Optional. Chat photo</summary>
    property Photo: ITgChatPhoto read GetPhoto;
    /// <summary>
    ///   Optional. If non-empty, the list of all active chat usernames; for private chats,
    ///   supergroups and channels
    /// </summary>
    property ActiveUsernames: TArray<string> read GetActiveUsernames;
    /// <summary>Optional. For private chats, the date of birth of the user</summary>
    property Birthdate: ITgBirthdate read GetBirthdate;
    /// <summary>
    ///   Optional. For private chats with business accounts, the intro of the business
    /// </summary>
    property BusinessIntro: ITgBusinessIntro read GetBusinessIntro;
    /// <summary>
    ///   Optional. For private chats with business accounts, the location of the business
    /// </summary>
    property BusinessLocation: ITgBusinessLocation read GetBusinessLocation;
    /// <summary>
    ///   Optional. For private chats with business accounts, the opening hours of the business
    /// </summary>
    property BusinessOpeningHours: ITgBusinessOpeningHours read GetBusinessOpeningHours;
    /// <summary>Optional. For private chats, the personal channel of the user</summary>
    property PersonalChat: ITgChat read GetPersonalChat;
    /// <summary>
    ///   Optional. Information about the corresponding channel chat; for direct messages chats only
    /// </summary>
    property ParentChat: ITgChat read GetParentChat;
    /// <summary>
    ///   Optional. List of available reactions allowed in the chat. If omitted, then all emoji
    ///   reactions are allowed.
    /// </summary>
    property AvailableReactions: TArray<ITgReactionType> read GetAvailableReactions;
    /// <summary>
    ///   Optional. Custom emoji identifier of the emoji chosen by the chat for the reply header and
    ///   link preview background
    /// </summary>
    property BackgroundCustomEmojiId: string read GetBackgroundCustomEmojiId;
    /// <summary>
    ///   Optional. Identifier of the accent color for the chat's profile background. See profile
    ///   accent colors for more details.
    /// </summary>
    property ProfileAccentColorId: Int64 read GetProfileAccentColorId;
    /// <summary>Поле profile_accent_color_id присутствует.</summary>
    property HasProfileAccentColorId: Boolean read GetHasProfileAccentColorId;
    /// <summary>
    ///   Optional. Custom emoji identifier of the emoji chosen by the chat for its profile
    ///   background
    /// </summary>
    property ProfileBackgroundCustomEmojiId: string read GetProfileBackgroundCustomEmojiId;
    /// <summary>
    ///   Optional. Custom emoji identifier of the emoji status of the chat or the other party in a
    ///   private chat
    /// </summary>
    property EmojiStatusCustomEmojiId: string read GetEmojiStatusCustomEmojiId;
    /// <summary>
    ///   Optional. Expiration date of the emoji status of the chat or the other party in a private
    ///   chat, in Unix time, if any
    /// </summary>
    property EmojiStatusExpirationDate: Int64 read GetEmojiStatusExpirationDate;
    /// <summary>Поле emoji_status_expiration_date присутствует.</summary>
    property HasEmojiStatusExpirationDate: Boolean read GetHasEmojiStatusExpirationDate;
    /// <summary>Optional. Bio of the other party in a private chat</summary>
    property Bio: string read GetBio;
    /// <summary>
    ///   Optional. True, if privacy settings of the other party in the private chat allows to use
    ///   tg://user?id=&lt;user_id&gt; links only in chats with the user
    /// </summary>
    property HasPrivateForwards: Boolean read GetHasPrivateForwards;
    /// <summary>
    ///   Optional. True, if the privacy settings of the other party restrict sending voice and
    ///   video note messages in the private chat
    /// </summary>
    property HasRestrictedVoiceAndVideoMessages: Boolean read GetHasRestrictedVoiceAndVideoMessages;
    /// <summary>
    ///   Optional. True, if users need to join the supergroup before they can send messages
    /// </summary>
    property JoinToSendMessages: Boolean read GetJoinToSendMessages;
    /// <summary>
    ///   Optional. True, if all users directly joining the supergroup without using an invite link
    ///   need to be approved by supergroup administrators
    /// </summary>
    property JoinByRequest: Boolean read GetJoinByRequest;
    /// <summary>Optional. Description, for groups, supergroups and channel chats</summary>
    property Description: string read GetDescription;
    /// <summary>
    ///   Optional. Primary invite link, for groups, supergroups and channel chats
    /// </summary>
    property InviteLink: string read GetInviteLink;
    /// <summary>Optional. The most recent pinned message (by sending date)</summary>
    property PinnedMessage: ITgMessage read GetPinnedMessage;
    /// <summary>
    ///   Optional. Default chat member permissions, for groups and supergroups
    /// </summary>
    property Permissions: ITgChatPermissions read GetPermissions;
    /// <summary>
    ///   Information about types of gifts that are accepted by the chat or by the corresponding
    ///   user for private chats
    /// </summary>
    property AcceptedGiftTypes: ITgAcceptedGiftTypes read GetAcceptedGiftTypes;
    /// <summary>
    ///   Optional. True, if paid media messages can be sent or forwarded to the channel chat. The
    ///   field is available only for channel chats.
    /// </summary>
    property CanSendPaidMedia: Boolean read GetCanSendPaidMedia;
    /// <summary>
    ///   Optional. For supergroups, the minimum allowed delay between consecutive messages sent by
    ///   each unprivileged user; in seconds
    /// </summary>
    property SlowModeDelay: Integer read GetSlowModeDelay;
    /// <summary>Поле slow_mode_delay присутствует.</summary>
    property HasSlowModeDelay: Boolean read GetHasSlowModeDelay;
    /// <summary>
    ///   Optional. For supergroups, the minimum number of boosts that a non-administrator user
    ///   needs to add in order to ignore slow mode and chat permissions
    /// </summary>
    property UnrestrictBoostCount: Integer read GetUnrestrictBoostCount;
    /// <summary>Поле unrestrict_boost_count присутствует.</summary>
    property HasUnrestrictBoostCount: Boolean read GetHasUnrestrictBoostCount;
    /// <summary>
    ///   Optional. The time after which all messages sent to the chat will be automatically
    ///   deleted; in seconds
    /// </summary>
    property MessageAutoDeleteTime: Integer read GetMessageAutoDeleteTime;
    /// <summary>Поле message_auto_delete_time присутствует.</summary>
    property HasMessageAutoDeleteTime: Boolean read GetHasMessageAutoDeleteTime;
    /// <summary>
    ///   Optional. True, if aggressive anti-spam checks are enabled in the supergroup. The field is
    ///   only available to chat administrators.
    /// </summary>
    property HasAggressiveAntiSpamEnabled: Boolean read GetHasAggressiveAntiSpamEnabled;
    /// <summary>
    ///   Optional. True, if non-administrators can only get the list of bots and administrators in
    ///   the chat
    /// </summary>
    property HasHiddenMembers: Boolean read GetHasHiddenMembers;
    /// <summary>
    ///   Optional. True, if messages from the chat can't be forwarded to other chats
    /// </summary>
    property HasProtectedContent: Boolean read GetHasProtectedContent;
    /// <summary>
    ///   Optional. True, if new chat members will have access to old messages; available only to
    ///   chat administrators
    /// </summary>
    property HasVisibleHistory: Boolean read GetHasVisibleHistory;
    /// <summary>Optional. For supergroups, name of the group sticker set</summary>
    property StickerSetName: string read GetStickerSetName;
    /// <summary>Optional. True, if the bot can change the group sticker set</summary>
    property CanSetStickerSet: Boolean read GetCanSetStickerSet;
    /// <summary>
    ///   Optional. For supergroups, the name of the group's custom emoji sticker set. Custom emoji
    ///   from this set can be used by all users and bots in the group.
    /// </summary>
    property CustomEmojiStickerSetName: string read GetCustomEmojiStickerSetName;
    /// <summary>
    ///   Optional. Unique identifier for the linked chat, i.e. the discussion group identifier for
    ///   a channel and vice versa; for supergroups and channel chats. This identifier may be
    ///   greater than 32 bits and some programming languages may have difficulty/silent defects in
    ///   interpreting it. But it is smaller than 52 bits, so a signed 64 bit integer or
    ///   double-precision float type are safe for storing this identifier.
    /// </summary>
    property LinkedChatId: Int64 read GetLinkedChatId;
    /// <summary>Поле linked_chat_id присутствует.</summary>
    property HasLinkedChatId: Boolean read GetHasLinkedChatId;
    /// <summary>
    ///   Optional. For supergroups, the location to which the supergroup is connected
    /// </summary>
    property Location: ITgChatLocation read GetLocation;
    /// <summary>Optional. For private chats, the rating of the user if any</summary>
    property Rating: ITgUserRating read GetRating;
    /// <summary>
    ///   Optional. For private chats, the first audio added to the profile of the user
    /// </summary>
    property FirstProfileAudio: ITgAudio read GetFirstProfileAudio;
    /// <summary>
    ///   Optional. The color scheme based on a unique gift that must be used for the chat's name,
    ///   message replies and link previews
    /// </summary>
    property UniqueGiftColors: ITgUniqueGiftColors read GetUniqueGiftColors;
    /// <summary>
    ///   Optional. The number of Telegram Stars a general user has to pay to send a message to the
    ///   chat
    /// </summary>
    property PaidMessageStarCount: Integer read GetPaidMessageStarCount;
    /// <summary>Поле paid_message_star_count присутствует.</summary>
    property HasPaidMessageStarCount: Boolean read GetHasPaidMessageStarCount;
    /// <summary>
    ///   Optional. The bot that processes join request queries in the chat. The field is only
    ///   available to chat administrators.
    /// </summary>
    property GuardBot: ITgUser read GetGuardBot;
    /// <summary>Optional. The Community to which the chat belongs</summary>
    property Community: ITgCommunity read GetCommunity;
  end;

  /// <summary>
  ///   This object describes a message that can be inaccessible to the bot. Виды (Kind, As*):
  ///   ITgMessage, ITgInaccessibleMessage.
  /// </summary>
  ITgMaybeInaccessibleMessage = interface(ITgJsonObject)
    ['{67D6EDB3-5750-55A2-97CE-4016795918D4}']
    function GetKind: TTgMaybeInaccessibleMessageKind;
    function GetKindText: string;
    function GetMessageId: Int64;
    function GetDate: Int64;
    function GetChat: ITgChat;
    /// <summary>ITgMessage или nil, если объект другого вида.</summary>
    function AsMessage: ITgMessage;
    /// <summary>ITgInaccessibleMessage или nil, если объект другого вида.</summary>
    function AsInaccessibleMessage: ITgInaccessibleMessage;
    /// <summary>Вид объекта (Unknown — неизвестный этой версии библиотеки).</summary>
    property Kind: TTgMaybeInaccessibleMessageKind read GetKind;
    /// <summary>
    ///   Значение поля date в JSON как есть (в т.ч. при Kind = Unknown); для вариантов-строк и
    ///   массивов — пустая строка.
    /// </summary>
    property KindText: string read GetKindText;
    /// <summary>
    ///   Unique message identifier inside this chat; 0 for ephemeral messages. In specific
    ///   instances (e.g., a message containing a video sent to a big chat), the server might
    ///   automatically schedule a message instead of sending it immediately. In such cases, this
    ///   field will be 0 and the relevant message will be unusable until it is actually sent.
    /// </summary>
    property MessageId: Int64 read GetMessageId;
    /// <summary>
    ///   Date the message was sent in Unix time. It is always a positive number, representing a
    ///   valid date.
    /// </summary>
    property Date: Int64 read GetDate;
    /// <summary>Chat the message belongs to</summary>
    property Chat: ITgChat read GetChat;
  end;

  /// <summary>This object represents a message.</summary>
  ITgMessage = interface(ITgMaybeInaccessibleMessage)
    ['{1205007E-2F0D-57B6-9CE5-C9776F0604EE}']
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
    /// <summary>
    ///   Optional. Unique identifier of a message thread or forum topic to which the message
    ///   belongs; for supergroups and private chats only
    /// </summary>
    property MessageThreadId: Int64 read GetMessageThreadId;
    /// <summary>Поле message_thread_id присутствует.</summary>
    property HasMessageThreadId: Boolean read GetHasMessageThreadId;
    /// <summary>
    ///   Optional. Information about the direct messages chat topic that contains the message
    /// </summary>
    property DirectMessagesTopic: ITgDirectMessagesTopic read GetDirectMessagesTopic;
    /// <summary>
    ///   Optional. Sender of the message; may be empty for messages sent to channels. For backward
    ///   compatibility, if the message was sent on behalf of a chat, the field contains a fake
    ///   sender user in non-channel chats.
    /// </summary>
    property From: ITgUser read GetFrom;
    /// <summary>
    ///   Optional. Sender of the message when sent on behalf of a chat. For example, the supergroup
    ///   itself for messages sent by its anonymous administrators or a linked channel for messages
    ///   automatically forwarded to the channel's discussion group. For backward compatibility, if
    ///   the message was sent on behalf of a chat, the field from contains a fake sender user in
    ///   non-channel chats.
    /// </summary>
    property SenderChat: ITgChat read GetSenderChat;
    /// <summary>
    ///   Optional. If the sender of the message boosted the chat, the number of boosts added by the
    ///   user
    /// </summary>
    property SenderBoostCount: Integer read GetSenderBoostCount;
    /// <summary>Поле sender_boost_count присутствует.</summary>
    property HasSenderBoostCount: Boolean read GetHasSenderBoostCount;
    /// <summary>
    ///   Optional. The bot that actually sent the message on behalf of the business account.
    ///   Available only for outgoing messages sent on behalf of the connected business account.
    /// </summary>
    property SenderBusinessBot: ITgUser read GetSenderBusinessBot;
    /// <summary>
    ///   Optional. Tag or custom title of the sender of the message; for supergroups only
    /// </summary>
    property SenderTag: string read GetSenderTag;
    /// <summary>
    ///   Optional. For ephemeral messages, the user who received the message
    /// </summary>
    property ReceiverUser: ITgUser read GetReceiverUser;
    /// <summary>
    ///   Optional. For ephemeral messages, identifier of the ephemeral message inside this chat.
    ///   The identifier may be reused for another ephemeral message after the message is deleted or
    ///   expires.
    /// </summary>
    property EphemeralMessageId: Int64 read GetEphemeralMessageId;
    /// <summary>Поле ephemeral_message_id присутствует.</summary>
    property HasEphemeralMessageId: Boolean read GetHasEphemeralMessageId;
    /// <summary>
    ///   Optional. The unique identifier for the guest query. Use this identifier with the method
    ///   answerGuestQuery to send a response message. If non-empty, the message belongs to the chat
    ///   where the guest bot was summoned, which may not coincide with other existing bot chats
    ///   sharing the same identifier.
    /// </summary>
    property GuestQueryId: string read GetGuestQueryId;
    /// <summary>
    ///   Optional. Unique identifier of the business connection from which the message was
    ///   received. If non-empty, the message belongs to a chat of the corresponding business
    ///   account that is independent from any potential bot chat which might share the same
    ///   identifier.
    /// </summary>
    property BusinessConnectionId: string read GetBusinessConnectionId;
    /// <summary>
    ///   Optional. Information about the original message for forwarded messages
    /// </summary>
    property ForwardOrigin: ITgMessageOrigin read GetForwardOrigin;
    /// <summary>
    ///   Optional. True, if the message is sent to a topic in a forum supergroup or a private chat
    ///   with the bot
    /// </summary>
    property IsTopicMessage: Boolean read GetIsTopicMessage;
    /// <summary>
    ///   Optional. True, if the message is a channel post that was automatically forwarded to the
    ///   connected discussion group
    /// </summary>
    property IsAutomaticForward: Boolean read GetIsAutomaticForward;
    /// <summary>
    ///   Optional. For replies in the same chat and message thread, the original message. Note that
    ///   the Message object in this field will not contain further reply_to_message fields even if
    ///   it itself is a reply. If the message is a reply to an ephemeral message, then this field
    ///   may be omitted.
    /// </summary>
    property ReplyToMessage: ITgMessage read GetReplyToMessage;
    /// <summary>
    ///   Optional. Information about the message that is being replied to, which may come from
    ///   another chat or forum topic
    /// </summary>
    property ExternalReply: ITgExternalReplyInfo read GetExternalReply;
    /// <summary>
    ///   Optional. For replies that quote part of the original message, the quoted part of the
    ///   message
    /// </summary>
    property Quote: ITgTextQuote read GetQuote;
    /// <summary>Optional. For replies to a story, the original story</summary>
    property ReplyToStory: ITgStory read GetReplyToStory;
    /// <summary>
    ///   Optional. Identifier of the specific checklist task that is being replied to
    /// </summary>
    property ReplyToChecklistTaskId: Int64 read GetReplyToChecklistTaskId;
    /// <summary>Поле reply_to_checklist_task_id присутствует.</summary>
    property HasReplyToChecklistTaskId: Boolean read GetHasReplyToChecklistTaskId;
    /// <summary>
    ///   Optional. Persistent identifier of the specific poll option that is being replied to
    /// </summary>
    property ReplyToPollOptionId: string read GetReplyToPollOptionId;
    /// <summary>Optional. Bot through which the message was sent</summary>
    property ViaBot: ITgUser read GetViaBot;
    /// <summary>
    ///   Optional. For a message sent by a guest bot, this is the user whose original message
    ///   triggered the bot's response
    /// </summary>
    property GuestBotCallerUser: ITgUser read GetGuestBotCallerUser;
    /// <summary>
    ///   Optional. For a message sent by a guest bot, this is the chat whose original message
    ///   triggered the bot's response
    /// </summary>
    property GuestBotCallerChat: ITgChat read GetGuestBotCallerChat;
    /// <summary>Optional. Date the message was last edited in Unix time</summary>
    property EditDate: Int64 read GetEditDate;
    /// <summary>Поле edit_date присутствует.</summary>
    property HasEditDate: Boolean read GetHasEditDate;
    /// <summary>Optional. True, if the message can't be forwarded</summary>
    property HasProtectedContent: Boolean read GetHasProtectedContent;
    /// <summary>
    ///   Optional. True, if the message was sent by an implicit action, for example, as an away or
    ///   a greeting business message, or as a scheduled message
    /// </summary>
    property IsFromOffline: Boolean read GetIsFromOffline;
    /// <summary>
    ///   Optional. True, if the message is a paid post. Note that such posts must not be deleted
    ///   for 24 hours to receive the payment and can't be edited.
    /// </summary>
    property IsPaidPost: Boolean read GetIsPaidPost;
    /// <summary>
    ///   Optional. The unique identifier inside this chat of a media message group this message
    ///   belongs to
    /// </summary>
    property MediaGroupId: string read GetMediaGroupId;
    /// <summary>
    ///   Optional. Signature of the post author for messages in channels, or the custom title of an
    ///   anonymous group administrator
    /// </summary>
    property AuthorSignature: string read GetAuthorSignature;
    /// <summary>
    ///   Optional. The number of Telegram Stars that were paid by the sender of the message to send
    ///   it
    /// </summary>
    property PaidStarCount: Integer read GetPaidStarCount;
    /// <summary>Поле paid_star_count присутствует.</summary>
    property HasPaidStarCount: Boolean read GetHasPaidStarCount;
    /// <summary>Optional. For text messages, the actual UTF-8 text of the message</summary>
    property Text: string read GetText;
    /// <summary>
    ///   Optional. For text messages, special entities like usernames, URLs, bot commands, etc.
    ///   that appear in the text
    /// </summary>
    property Entities: TArray<ITgMessageEntity> read GetEntities;
    /// <summary>
    ///   Optional. Options used for link preview generation for the message, if it is a text
    ///   message and link preview options were changed
    /// </summary>
    property LinkPreviewOptions: ITgLinkPreviewOptions read GetLinkPreviewOptions;
    /// <summary>
    ///   Optional. Information about suggested post parameters if the message is a suggested post
    ///   in a channel direct messages chat. If the message is an approved or declined suggested
    ///   post, then it can't be edited.
    /// </summary>
    property SuggestedPostInfo: ITgSuggestedPostInfo read GetSuggestedPostInfo;
    /// <summary>
    ///   Optional. Unique identifier of the message effect added to the message
    /// </summary>
    property EffectId: string read GetEffectId;
    /// <summary>Optional. Message is a rich formatted message</summary>
    property RichMessage: ITgRichMessage read GetRichMessage;
    /// <summary>
    ///   Optional. Message is an animation, information about the animation. For backward
    ///   compatibility, when this field is set, the document field will also be set.
    /// </summary>
    property Animation: ITgAnimation read GetAnimation;
    /// <summary>Optional. Message is an audio file, information about the file</summary>
    property Audio: ITgAudio read GetAudio;
    /// <summary>Optional. Message is a general file, information about the file</summary>
    property Document: ITgDocument read GetDocument;
    /// <summary>
    ///   Optional. Message is a live photo, information about the live photo. For backward
    ///   compatibility, when this field is set, the photo field will also be set.
    /// </summary>
    property LivePhoto: ITgLivePhoto read GetLivePhoto;
    /// <summary>
    ///   Optional. Message contains paid media; information about the paid media
    /// </summary>
    property PaidMedia: ITgPaidMediaInfo read GetPaidMedia;
    /// <summary>Optional. Message is a photo, available sizes of the photo</summary>
    property Photo: TArray<ITgPhotoSize> read GetPhoto;
    /// <summary>Optional. Message is a sticker, information about the sticker</summary>
    property Sticker: ITgSticker read GetSticker;
    /// <summary>Optional. Message is a forwarded story</summary>
    property Story: ITgStory read GetStory;
    /// <summary>Optional. Message is a video, information about the video</summary>
    property Video: ITgVideo read GetVideo;
    /// <summary>
    ///   Optional. Message is a video note, information about the video message
    /// </summary>
    property VideoNote: ITgVideoNote read GetVideoNote;
    /// <summary>Optional. Message is a voice message, information about the file</summary>
    property Voice: ITgVoice read GetVoice;
    /// <summary>
    ///   Optional. Caption for the animation, audio, document, paid media, photo, video or voice
    /// </summary>
    property Caption: string read GetCaption;
    /// <summary>
    ///   Optional. For messages with a caption, special entities like usernames, URLs, bot
    ///   commands, etc. that appear in the caption
    /// </summary>
    property CaptionEntities: TArray<ITgMessageEntity> read GetCaptionEntities;
    /// <summary>
    ///   Optional. True, if the caption must be shown above the message media
    /// </summary>
    property ShowCaptionAboveMedia: Boolean read GetShowCaptionAboveMedia;
    /// <summary>
    ///   Optional. True, if the message media is covered by a spoiler animation
    /// </summary>
    property HasMediaSpoiler: Boolean read GetHasMediaSpoiler;
    /// <summary>Optional. Message is a checklist</summary>
    property Checklist: ITgChecklist read GetChecklist;
    /// <summary>
    ///   Optional. Message is a shared contact, information about the contact
    /// </summary>
    property Contact: ITgContact read GetContact;
    /// <summary>Optional. Message is a dice with random value</summary>
    property Dice: ITgDice read GetDice;
    /// <summary>
    ///   Optional. Message is a game, information about the game. More about games »
    /// </summary>
    property Game: ITgGame read GetGame;
    /// <summary>Optional. Message is a native poll, information about the poll</summary>
    property Poll: ITgPoll read GetPoll;
    /// <summary>
    ///   Optional. Message is a venue, information about the venue. For backward compatibility,
    ///   when this field is set, the location field will also be set.
    /// </summary>
    property Venue: ITgVenue read GetVenue;
    /// <summary>
    ///   Optional. Message is a shared location, information about the location
    /// </summary>
    property Location: ITgLocation read GetLocation;
    /// <summary>
    ///   Optional. New members that were added to the group or supergroup and information about
    ///   them (the bot itself may be one of these members)
    /// </summary>
    property NewChatMembers: TArray<ITgUser> read GetNewChatMembers;
    /// <summary>
    ///   Optional. A member was removed from the group, information about them (this member may be
    ///   the bot itself)
    /// </summary>
    property LeftChatMember: ITgUser read GetLeftChatMember;
    /// <summary>Optional. Service message: chat owner has left</summary>
    property ChatOwnerLeft: ITgChatOwnerLeft read GetChatOwnerLeft;
    /// <summary>Optional. Service message: chat owner has changed</summary>
    property ChatOwnerChanged: ITgChatOwnerChanged read GetChatOwnerChanged;
    /// <summary>Optional. A chat title was changed to this value</summary>
    property NewChatTitle: string read GetNewChatTitle;
    /// <summary>Optional. A chat photo was change to this value</summary>
    property NewChatPhoto: TArray<ITgPhotoSize> read GetNewChatPhoto;
    /// <summary>Optional. Service message: the chat photo was deleted</summary>
    property DeleteChatPhoto: Boolean read GetDeleteChatPhoto;
    /// <summary>Optional. Service message: the group has been created</summary>
    property GroupChatCreated: Boolean read GetGroupChatCreated;
    /// <summary>
    ///   Optional. Service message: the supergroup has been created. This field can't be received
    ///   in a message coming through updates, because bot can't be a member of a supergroup when it
    ///   is created. It can only be found in reply_to_message if someone replies to a very first
    ///   message in a directly created supergroup.
    /// </summary>
    property SupergroupChatCreated: Boolean read GetSupergroupChatCreated;
    /// <summary>
    ///   Optional. Service message: the channel has been created. This field can't be received in a
    ///   message coming through updates, because bot can't be a member of a channel when it is
    ///   created. It can only be found in reply_to_message if someone replies to a very first
    ///   message in a channel.
    /// </summary>
    property ChannelChatCreated: Boolean read GetChannelChatCreated;
    /// <summary>
    ///   Optional. Service message: auto-delete timer settings changed in the chat
    /// </summary>
    property MessageAutoDeleteTimerChanged: ITgMessageAutoDeleteTimerChanged read GetMessageAutoDeleteTimerChanged;
    /// <summary>
    ///   Optional. The group has been migrated to a supergroup with the specified identifier. This
    ///   number may have more than 32 significant bits and some programming languages may have
    ///   difficulty/silent defects in interpreting it. But it has at most 52 significant bits, so a
    ///   signed 64-bit integer or double-precision float type are safe for storing this identifier.
    /// </summary>
    property MigrateToChatId: Int64 read GetMigrateToChatId;
    /// <summary>Поле migrate_to_chat_id присутствует.</summary>
    property HasMigrateToChatId: Boolean read GetHasMigrateToChatId;
    /// <summary>
    ///   Optional. The supergroup has been migrated from a group with the specified identifier.
    ///   This number may have more than 32 significant bits and some programming languages may have
    ///   difficulty/silent defects in interpreting it. But it has at most 52 significant bits, so a
    ///   signed 64-bit integer or double-precision float type are safe for storing this identifier.
    /// </summary>
    property MigrateFromChatId: Int64 read GetMigrateFromChatId;
    /// <summary>Поле migrate_from_chat_id присутствует.</summary>
    property HasMigrateFromChatId: Boolean read GetHasMigrateFromChatId;
    /// <summary>
    ///   Optional. Specified message was pinned. Note that the Message object in this field will
    ///   not contain further reply_to_message fields even if it itself is a reply.
    /// </summary>
    property PinnedMessage: ITgMaybeInaccessibleMessage read GetPinnedMessage;
    /// <summary>
    ///   Optional. Message is an invoice for a payment, information about the invoice. More about
    ///   payments »
    /// </summary>
    property Invoice: ITgInvoice read GetInvoice;
    /// <summary>
    ///   Optional. Message is a service message about a successful payment, information about the
    ///   payment. More about payments »
    /// </summary>
    property SuccessfulPayment: ITgSuccessfulPayment read GetSuccessfulPayment;
    /// <summary>
    ///   Optional. Message is a service message about a refunded payment, information about the
    ///   payment. More about payments »
    /// </summary>
    property RefundedPayment: ITgRefundedPayment read GetRefundedPayment;
    /// <summary>Optional. Service message: users were shared with the bot</summary>
    property UsersShared: ITgUsersShared read GetUsersShared;
    /// <summary>Optional. Service message: a chat was shared with the bot</summary>
    property ChatShared: ITgChatShared read GetChatShared;
    /// <summary>Optional. Service message: a regular gift was sent or received</summary>
    property Gift: ITgGiftInfo read GetGift;
    /// <summary>Optional. Service message: a unique gift was sent or received</summary>
    property UniqueGift: ITgUniqueGiftInfo read GetUniqueGift;
    /// <summary>
    ///   Optional. Service message: upgrade of a gift was purchased after the gift was sent
    /// </summary>
    property GiftUpgradeSent: ITgGiftInfo read GetGiftUpgradeSent;
    /// <summary>
    ///   Optional. The domain name of the website on which the user has logged in. More about
    ///   Telegram Login »
    /// </summary>
    property ConnectedWebsite: string read GetConnectedWebsite;
    /// <summary>
    ///   Optional. Service message: the user allowed the bot to write messages after adding it to
    ///   the attachment or side menu, launching a Web App from a link, or accepting an explicit
    ///   request from a Web App sent by the method requestWriteAccess
    /// </summary>
    property WriteAccessAllowed: ITgWriteAccessAllowed read GetWriteAccessAllowed;
    /// <summary>Optional. Telegram Passport data</summary>
    property PassportData: ITgPassportData read GetPassportData;
    /// <summary>
    ///   Optional. Service message: a user in the chat triggered another user's proximity alert
    ///   while sharing Live Location
    /// </summary>
    property ProximityAlertTriggered: ITgProximityAlertTriggered read GetProximityAlertTriggered;
    /// <summary>Optional. Service message: user boosted the chat</summary>
    property BoostAdded: ITgChatBoostAdded read GetBoostAdded;
    /// <summary>Optional. Service message: chat background set</summary>
    property ChatBackgroundSet: ITgChatBackground read GetChatBackgroundSet;
    /// <summary>
    ///   Optional. Service message: some tasks in a checklist were marked as done or not done
    /// </summary>
    property ChecklistTasksDone: ITgChecklistTasksDone read GetChecklistTasksDone;
    /// <summary>Optional. Service message: tasks were added to a checklist</summary>
    property ChecklistTasksAdded: ITgChecklistTasksAdded read GetChecklistTasksAdded;
    /// <summary>Optional. Service message: chat or bot added to a Community</summary>
    property CommunityChatAdded: ITgCommunityChatAdded read GetCommunityChatAdded;
    /// <summary>
    ///   Optional. Service message: chat was joined by a user from a Community
    /// </summary>
    property CommunityChatJoined: ITgCommunityChatJoined read GetCommunityChatJoined;
    /// <summary>Optional. Service message: chat or bot removed from a Community</summary>
    property CommunityChatRemoved: ITgCommunityChatRemoved read GetCommunityChatRemoved;
    /// <summary>
    ///   Optional. Service message: the price for paid messages in the corresponding direct
    ///   messages chat of a channel has changed
    /// </summary>
    property DirectMessagePriceChanged: ITgDirectMessagePriceChanged read GetDirectMessagePriceChanged;
    /// <summary>Optional. Service message: forum topic created</summary>
    property ForumTopicCreated: ITgForumTopicCreated read GetForumTopicCreated;
    /// <summary>Optional. Service message: forum topic edited</summary>
    property ForumTopicEdited: ITgForumTopicEdited read GetForumTopicEdited;
    /// <summary>Optional. Service message: forum topic closed</summary>
    property ForumTopicClosed: ITgForumTopicClosed read GetForumTopicClosed;
    /// <summary>Optional. Service message: forum topic reopened</summary>
    property ForumTopicReopened: ITgForumTopicReopened read GetForumTopicReopened;
    /// <summary>Optional. Service message: the 'General' forum topic hidden</summary>
    property GeneralForumTopicHidden: ITgGeneralForumTopicHidden read GetGeneralForumTopicHidden;
    /// <summary>Optional. Service message: the 'General' forum topic unhidden</summary>
    property GeneralForumTopicUnhidden: ITgGeneralForumTopicUnhidden read GetGeneralForumTopicUnhidden;
    /// <summary>Optional. Service message: a scheduled giveaway was created</summary>
    property GiveawayCreated: ITgGiveawayCreated read GetGiveawayCreated;
    /// <summary>Optional. The message is a scheduled giveaway message</summary>
    property Giveaway: ITgGiveaway read GetGiveaway;
    /// <summary>Optional. A giveaway with public winners was completed</summary>
    property GiveawayWinners: ITgGiveawayWinners read GetGiveawayWinners;
    /// <summary>
    ///   Optional. Service message: a giveaway without public winners was completed
    /// </summary>
    property GiveawayCompleted: ITgGiveawayCompleted read GetGiveawayCompleted;
    /// <summary>
    ///   Optional. Service message: user created a bot that will be managed by the current bot
    /// </summary>
    property ManagedBotCreated: ITgManagedBotCreated read GetManagedBotCreated;
    /// <summary>
    ///   Optional. Service message: the price for paid messages has changed in the chat
    /// </summary>
    property PaidMessagePriceChanged: ITgPaidMessagePriceChanged read GetPaidMessagePriceChanged;
    /// <summary>Optional. Service message: answer option was added to a poll</summary>
    property PollOptionAdded: ITgPollOptionAdded read GetPollOptionAdded;
    /// <summary>Optional. Service message: answer option was deleted from a poll</summary>
    property PollOptionDeleted: ITgPollOptionDeleted read GetPollOptionDeleted;
    /// <summary>Optional. Service message: a suggested post was approved</summary>
    property SuggestedPostApproved: ITgSuggestedPostApproved read GetSuggestedPostApproved;
    /// <summary>
    ///   Optional. Service message: approval of a suggested post has failed
    /// </summary>
    property SuggestedPostApprovalFailed: ITgSuggestedPostApprovalFailed read GetSuggestedPostApprovalFailed;
    /// <summary>Optional. Service message: a suggested post was declined</summary>
    property SuggestedPostDeclined: ITgSuggestedPostDeclined read GetSuggestedPostDeclined;
    /// <summary>
    ///   Optional. Service message: payment for a suggested post was received
    /// </summary>
    property SuggestedPostPaid: ITgSuggestedPostPaid read GetSuggestedPostPaid;
    /// <summary>
    ///   Optional. Service message: payment for a suggested post was refunded
    /// </summary>
    property SuggestedPostRefunded: ITgSuggestedPostRefunded read GetSuggestedPostRefunded;
    /// <summary>Optional. Service message: video chat scheduled</summary>
    property VideoChatScheduled: ITgVideoChatScheduled read GetVideoChatScheduled;
    /// <summary>Optional. Service message: video chat started</summary>
    property VideoChatStarted: ITgVideoChatStarted read GetVideoChatStarted;
    /// <summary>Optional. Service message: video chat ended</summary>
    property VideoChatEnded: ITgVideoChatEnded read GetVideoChatEnded;
    /// <summary>
    ///   Optional. Service message: new participants invited to a video chat
    /// </summary>
    property VideoChatParticipantsInvited: ITgVideoChatParticipantsInvited read GetVideoChatParticipantsInvited;
    /// <summary>Optional. Service message: data sent by a Web App</summary>
    property WebAppData: ITgWebAppData read GetWebAppData;
    /// <summary>
    ///   Optional. Inline keyboard attached to the message. login_url buttons are represented as
    ///   ordinary url buttons.
    /// </summary>
    property ReplyMarkup: ITgInlineKeyboardMarkup read GetReplyMarkup;
  end;

  /// <summary>This object represents a unique message identifier.</summary>
  ITgMessageId = interface(ITgJsonObject)
    ['{C6E7C2FD-FC44-5C90-931E-D778E12835A0}']
    function GetMessageId: Int64;
    /// <summary>
    ///   Unique message identifier. In specific instances (e.g., message containing a video sent to
    ///   a big chat), the server might automatically schedule a message instead of sending it
    ///   immediately. In such cases, this field will be 0 and the relevant message will be unusable
    ///   until it is actually sent.
    /// </summary>
    property MessageId: Int64 read GetMessageId;
  end;

  /// <summary>
  ///   This object describes a message that was deleted or is otherwise inaccessible to the bot.
  /// </summary>
  ITgInaccessibleMessage = interface(ITgMaybeInaccessibleMessage)
    ['{AAA5D842-460E-5CF2-95D3-73C4CACE949D}']
  end;

  /// <summary>
  ///   This object represents one special entity in a text message. For example, hashtags,
  ///   usernames, URLs, etc.
  /// </summary>
  ITgMessageEntity = interface(ITgJsonObject)
    ['{2425C611-E0B4-5EEA-9CF2-AD221A119DF9}']
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
    /// <summary>
    ///   Задаёт type: Type of the entity. Currently, can be “mention” (@username), “hashtag”
    ///   (#hashtag or #hashtag@chatusername), “cashtag” ($USD or $USD@chatusername), “bot_command”
    ///   (/start@jobs_bot), “url” (https://telegram.org), “email” (do-not-reply@telegram.org),
    ///   “phone_number” (+1-212-555-0123), “bold” (bold text), “italic” (italic text), “underline”
    ///   (underlined text), “strikethrough” (strikethrough text), “spoiler” (spoiler message),
    ///   “blockquote” (block quotation), “expandable_blockquote” (collapsed-by-default block
    ///   quotation), “code” (monowidth string), “pre” (monowidth block), “text_link” (for clickable
    ///   text URLs), “text_mention” (for users without usernames), “custom_emoji” (for inline
    ///   custom emoji stickers), or “date_time” (for formatted date and time). Значение копируется
    ///   в момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithMessageEntityType(const AValue: string): ITgMessageEntity;
    /// <summary>
    ///   Задаёт offset: Offset in UTF-16 code units to the start of the entity. Значение копируется
    ///   в момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithOffset(AValue: Integer): ITgMessageEntity;
    /// <summary>
    ///   Задаёт length: Length of the entity in UTF-16 code units. Значение копируется в момент
    ///   вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithLength(AValue: Integer): ITgMessageEntity;
    /// <summary>
    ///   Задаёт url: Optional. For “text_link” only, URL that will be opened after user taps on the
    ///   text. Значение копируется в момент вызова: последующие изменения переданного объекта на
    ///   этот не влияют.
    /// </summary>
    function WithUrl(const AValue: string): ITgMessageEntity;
    /// <summary>
    ///   Задаёт user: Optional. For “text_mention” only, the mentioned user. Значение копируется в
    ///   момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithUser(const AValue: ITgUser): ITgMessageEntity;
    /// <summary>
    ///   Задаёт language: Optional. For “pre” only, the programming language of the entity text.
    ///   Значение копируется в момент вызова: последующие изменения переданного объекта на этот не
    ///   влияют.
    /// </summary>
    function WithLanguage(const AValue: string): ITgMessageEntity;
    /// <summary>
    ///   Задаёт custom_emoji_id: Optional. For “custom_emoji” only, unique identifier of the custom
    ///   emoji. Use getCustomEmojiStickers to get full information about the sticker. Значение
    ///   копируется в момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithCustomEmojiId(const AValue: string): ITgMessageEntity;
    /// <summary>
    ///   Задаёт unix_time: Optional. For “date_time” only, the Unix time associated with the
    ///   entity. Значение копируется в момент вызова: последующие изменения переданного объекта на
    ///   этот не влияют.
    /// </summary>
    function WithUnixTime(AValue: Integer): ITgMessageEntity;
    /// <summary>
    ///   Задаёт date_time_format: Optional. For “date_time” only, the string that defines the
    ///   formatting of the date and time. See date-time entity formatting for more details.
    ///   Значение копируется в момент вызова: последующие изменения переданного объекта на этот не
    ///   влияют.
    /// </summary>
    function WithDateTimeFormat(const AValue: string): ITgMessageEntity;
    /// <summary>
    ///   Type of the entity. Currently, can be “mention” (@username), “hashtag” (#hashtag or
    ///   #hashtag@chatusername), “cashtag” ($USD or $USD@chatusername), “bot_command”
    ///   (/start@jobs_bot), “url” (https://telegram.org), “email” (do-not-reply@telegram.org),
    ///   “phone_number” (+1-212-555-0123), “bold” (bold text), “italic” (italic text), “underline”
    ///   (underlined text), “strikethrough” (strikethrough text), “spoiler” (spoiler message),
    ///   “blockquote” (block quotation), “expandable_blockquote” (collapsed-by-default block
    ///   quotation), “code” (monowidth string), “pre” (monowidth block), “text_link” (for clickable
    ///   text URLs), “text_mention” (for users without usernames), “custom_emoji” (for inline
    ///   custom emoji stickers), or “date_time” (for formatted date and time).
    /// </summary>
    property MessageEntityType: string read GetMessageEntityType;
    /// <summary>Offset in UTF-16 code units to the start of the entity</summary>
    property Offset: Integer read GetOffset;
    /// <summary>Length of the entity in UTF-16 code units</summary>
    property Length: Integer read GetLength;
    /// <summary>
    ///   Optional. For “text_link” only, URL that will be opened after user taps on the text
    /// </summary>
    property Url: string read GetUrl;
    /// <summary>Optional. For “text_mention” only, the mentioned user</summary>
    property User: ITgUser read GetUser;
    /// <summary>
    ///   Optional. For “pre” only, the programming language of the entity text
    /// </summary>
    property Language: string read GetLanguage;
    /// <summary>
    ///   Optional. For “custom_emoji” only, unique identifier of the custom emoji. Use
    ///   getCustomEmojiStickers to get full information about the sticker.
    /// </summary>
    property CustomEmojiId: string read GetCustomEmojiId;
    /// <summary>
    ///   Optional. For “date_time” only, the Unix time associated with the entity
    /// </summary>
    property UnixTime: Integer read GetUnixTime;
    /// <summary>Поле unix_time присутствует.</summary>
    property HasUnixTime: Boolean read GetHasUnixTime;
    /// <summary>
    ///   Optional. For “date_time” only, the string that defines the formatting of the date and
    ///   time. See date-time entity formatting for more details.
    /// </summary>
    property DateTimeFormat: string read GetDateTimeFormat;
  end;

  /// <summary>
  ///   This object contains information about the quoted part of a message that is replied to by
  ///   the given message.
  /// </summary>
  ITgTextQuote = interface(ITgJsonObject)
    ['{2F0A4F5D-59DA-517B-8565-EA85D5C5AB94}']
    function GetText: string;
    function GetEntities: TArray<ITgMessageEntity>;
    function GetPosition: Integer;
    function GetIsManual: Boolean;
    /// <summary>
    ///   Text of the quoted part of a message that is replied to by the given message
    /// </summary>
    property Text: string read GetText;
    /// <summary>
    ///   Optional. Special entities that appear in the quote. Currently, only bold, italic,
    ///   underline, strikethrough, spoiler, custom_emoji, and date_time entities are kept in
    ///   quotes.
    /// </summary>
    property Entities: TArray<ITgMessageEntity> read GetEntities;
    /// <summary>
    ///   Approximate quote position in the original message in UTF-16 code units as specified by
    ///   the sender
    /// </summary>
    property Position: Integer read GetPosition;
    /// <summary>
    ///   Optional. True, if the quote was chosen manually by the message sender. Otherwise, the
    ///   quote was added automatically by the server.
    /// </summary>
    property IsManual: Boolean read GetIsManual;
  end;

  /// <summary>
  ///   This object contains information about a message that is being replied to, which may come
  ///   from another chat or forum topic.
  /// </summary>
  ITgExternalReplyInfo = interface(ITgJsonObject)
    ['{52BF4F3E-64CB-51DD-8862-5B208A45960D}']
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
    /// <summary>Origin of the message replied to by the given message</summary>
    property Origin: ITgMessageOrigin read GetOrigin;
    /// <summary>
    ///   Optional. Chat the original message belongs to. Available only if the chat is a supergroup
    ///   or a channel.
    /// </summary>
    property Chat: ITgChat read GetChat;
    /// <summary>
    ///   Optional. Unique message identifier inside the original chat. Available only if the
    ///   original chat is a supergroup or a channel.
    /// </summary>
    property MessageId: Int64 read GetMessageId;
    /// <summary>Поле message_id присутствует.</summary>
    property HasMessageId: Boolean read GetHasMessageId;
    /// <summary>
    ///   Optional. Options used for link preview generation for the original message, if it is a
    ///   text message
    /// </summary>
    property LinkPreviewOptions: ITgLinkPreviewOptions read GetLinkPreviewOptions;
    /// <summary>
    ///   Optional. Message is an animation, information about the animation
    /// </summary>
    property Animation: ITgAnimation read GetAnimation;
    /// <summary>Optional. Message is an audio file, information about the file</summary>
    property Audio: ITgAudio read GetAudio;
    /// <summary>Optional. Message is a general file, information about the file</summary>
    property Document: ITgDocument read GetDocument;
    /// <summary>
    ///   Optional. Message is a live photo, information about the live photo
    /// </summary>
    property LivePhoto: ITgLivePhoto read GetLivePhoto;
    /// <summary>
    ///   Optional. Message contains paid media; information about the paid media
    /// </summary>
    property PaidMedia: ITgPaidMediaInfo read GetPaidMedia;
    /// <summary>Optional. Message is a photo, available sizes of the photo</summary>
    property Photo: TArray<ITgPhotoSize> read GetPhoto;
    /// <summary>Optional. Message is a sticker, information about the sticker</summary>
    property Sticker: ITgSticker read GetSticker;
    /// <summary>Optional. Message is a forwarded story</summary>
    property Story: ITgStory read GetStory;
    /// <summary>Optional. Message is a video, information about the video</summary>
    property Video: ITgVideo read GetVideo;
    /// <summary>
    ///   Optional. Message is a video note, information about the video message
    /// </summary>
    property VideoNote: ITgVideoNote read GetVideoNote;
    /// <summary>Optional. Message is a voice message, information about the file</summary>
    property Voice: ITgVoice read GetVoice;
    /// <summary>
    ///   Optional. True, if the message media is covered by a spoiler animation
    /// </summary>
    property HasMediaSpoiler: Boolean read GetHasMediaSpoiler;
    /// <summary>Optional. Message is a checklist</summary>
    property Checklist: ITgChecklist read GetChecklist;
    /// <summary>
    ///   Optional. Message is a shared contact, information about the contact
    /// </summary>
    property Contact: ITgContact read GetContact;
    /// <summary>Optional. Message is a dice with random value</summary>
    property Dice: ITgDice read GetDice;
    /// <summary>
    ///   Optional. Message is a game, information about the game. More about games »
    /// </summary>
    property Game: ITgGame read GetGame;
    /// <summary>
    ///   Optional. Message is a scheduled giveaway, information about the giveaway
    /// </summary>
    property Giveaway: ITgGiveaway read GetGiveaway;
    /// <summary>Optional. A giveaway with public winners was completed</summary>
    property GiveawayWinners: ITgGiveawayWinners read GetGiveawayWinners;
    /// <summary>
    ///   Optional. Message is an invoice for a payment, information about the invoice. More about
    ///   payments »
    /// </summary>
    property Invoice: ITgInvoice read GetInvoice;
    /// <summary>
    ///   Optional. Message is a shared location, information about the location
    /// </summary>
    property Location: ITgLocation read GetLocation;
    /// <summary>Optional. Message is a native poll, information about the poll</summary>
    property Poll: ITgPoll read GetPoll;
    /// <summary>Optional. Message is a venue, information about the venue</summary>
    property Venue: ITgVenue read GetVenue;
  end;

  /// <summary>Describes reply parameters for the message that is being sent.</summary>
  ITgReplyParameters = interface(ITgOutObject)
    ['{04BA0ED0-655D-5DB6-BF08-D6D7C8FBBB2C}']
    /// <summary>
    ///   Задаёт message_id: Optional. Identifier of the message that will be replied to in the
    ///   current chat, or in the chat chat_id if it is specified. Required if ephemeral_message_id
    ///   isn't specified.
    /// </summary>
    function WithMessageId(AValue: Int64): ITgReplyParameters;
    /// <summary>
    ///   Задаёт chat_id: Optional. If the message to be replied to is from a different chat, unique
    ///   identifier for the chat or username of the bot, supergroup or channel in the format
    ///   @username. Not supported for messages sent on behalf of a business account, messages from
    ///   channel direct messages chats and ephemeral messages.
    /// </summary>
    function WithChatId(const AValue: TTgChatId): ITgReplyParameters;
    /// <summary>
    ///   Задаёт ephemeral_message_id: Optional. Identifier of the incoming ephemeral message that
    ///   will be replied to in the current chat. A reply to an ephemeral message must itself be an
    ///   ephemeral message. An ephemeral message may only be replied to within 15 seconds of being
    ///   sent. Required if message_id isn't specified.
    /// </summary>
    function WithEphemeralMessageId(AValue: Int64): ITgReplyParameters;
    /// <summary>
    ///   Задаёт allow_sending_without_reply: Optional. Pass True if the message should be sent even
    ///   if the specified message to be replied to is not found. Always False for replies in
    ///   another chat or forum topic, and sent ephemeral messages. Always True for messages sent on
    ///   behalf of a business account.
    /// </summary>
    function WithAllowSendingWithoutReply(AValue: Boolean): ITgReplyParameters;
    /// <summary>
    ///   Задаёт quote: Optional. Quoted part of the message to be replied to; 0-1024 characters
    ///   after entities parsing. The quote must be an exact substring of the message to be replied
    ///   to, including bold, italic, underline, strikethrough, spoiler, custom_emoji, and date_time
    ///   entities. The message will fail to send if the quote isn't found in the original message.
    ///   Ignored for ephemeral messages.
    /// </summary>
    function WithQuote(const AValue: string): ITgReplyParameters;
    /// <summary>
    ///   Задаёт quote_parse_mode: Optional. Mode for parsing entities in the quote. See formatting
    ///   options for more details.
    /// </summary>
    function WithQuoteParseMode(const AValue: string): ITgReplyParameters;
    /// <summary>
    ///   Задаёт quote_entities: Optional. A JSON-serialized list of special entities that appear in
    ///   the quote. It can be specified instead of quote_parse_mode.
    /// </summary>
    function WithQuoteEntities(const AValue: array of ITgMessageEntity): ITgReplyParameters;
    /// <summary>
    ///   Задаёт quote_position: Optional. Position of the quote in the original message in UTF-16
    ///   code units
    /// </summary>
    function WithQuotePosition(AValue: Integer): ITgReplyParameters;
    /// <summary>
    ///   Задаёт checklist_task_id: Optional. Identifier of the specific checklist task to be
    ///   replied to
    /// </summary>
    function WithChecklistTaskId(AValue: Int64): ITgReplyParameters;
    /// <summary>
    ///   Задаёт poll_option_id: Optional. Persistent identifier of the specific poll option to be
    ///   replied to
    /// </summary>
    function WithPollOptionId(const AValue: string): ITgReplyParameters;
  end;

  ITgEphemeralMessageParameters = interface(ITgOutObject)
    ['{CE342FF6-7EDE-5C37-B742-3A2A6D2CE22A}']
    /// <summary>
    ///   Задаёт receiver_user_id: Identifier of the user who will receive the message. It is not
    ///   guaranteed that the user will receive the message, especially if they are offline. See
    ///   here for more details.
    /// </summary>
    function WithReceiverUserId(AValue: Int64): ITgEphemeralMessageParameters;
    /// <summary>
    ///   Задаёт callback_query_id: Optional. Identifier of the callback query which triggered the
    ///   message, if any
    /// </summary>
    function WithCallbackQueryId(const AValue: string): ITgEphemeralMessageParameters;
    /// <summary>
    ///   Задаёт replace_callback_query_message: Optional. Pass True if the ephemeral message must
    ///   be shown in place of the original message. Must be False for callback queries from
    ///   ephemeral messages, which must be edited using regular editEphemeralMessage… methods.
    /// </summary>
    function WithReplaceCallbackQueryMessage(AValue: Boolean): ITgEphemeralMessageParameters;
  end;

  /// <summary>
  ///   This object describes the origin of a message. Виды (Kind, As*): ITgMessageOriginUser,
  ///   ITgMessageOriginHiddenUser, ITgMessageOriginChat, ITgMessageOriginChannel.
  /// </summary>
  ITgMessageOrigin = interface(ITgJsonObject)
    ['{8D437786-67B0-5221-AD8A-FFC8A2E067A4}']
    function GetKind: TTgMessageOriginKind;
    function GetKindText: string;
    function GetDate: Int64;
    /// <summary>ITgMessageOriginUser или nil, если объект другого вида.</summary>
    function AsUser: ITgMessageOriginUser;
    /// <summary>ITgMessageOriginHiddenUser или nil, если объект другого вида.</summary>
    function AsHiddenUser: ITgMessageOriginHiddenUser;
    /// <summary>ITgMessageOriginChat или nil, если объект другого вида.</summary>
    function AsChat: ITgMessageOriginChat;
    /// <summary>ITgMessageOriginChannel или nil, если объект другого вида.</summary>
    function AsChannel: ITgMessageOriginChannel;
    /// <summary>Вид объекта (Unknown — неизвестный этой версии библиотеки).</summary>
    property Kind: TTgMessageOriginKind read GetKind;
    /// <summary>
    ///   Значение поля type в JSON как есть (в т.ч. при Kind = Unknown); для вариантов-строк и
    ///   массивов — пустая строка.
    /// </summary>
    property KindText: string read GetKindText;
    /// <summary>Date the message was sent originally in Unix time</summary>
    property Date: Int64 read GetDate;
  end;

  /// <summary>The message was originally sent by a known user.</summary>
  ITgMessageOriginUser = interface(ITgMessageOrigin)
    ['{25736D23-5BDE-5B32-B831-A2DE7D267433}']
    function GetSenderUser: ITgUser;
    /// <summary>User that sent the message originally</summary>
    property SenderUser: ITgUser read GetSenderUser;
  end;

  /// <summary>The message was originally sent by an unknown user.</summary>
  ITgMessageOriginHiddenUser = interface(ITgMessageOrigin)
    ['{70A270BE-9E3A-56BA-81A0-3193BD1E0640}']
    function GetSenderUserName: string;
    /// <summary>Name of the user that sent the message originally</summary>
    property SenderUserName: string read GetSenderUserName;
  end;

  /// <summary>
  ///   The message was originally sent on behalf of a chat to a group chat.
  /// </summary>
  ITgMessageOriginChat = interface(ITgMessageOrigin)
    ['{217B675F-328E-50EF-A88A-1E961095AB80}']
    function GetSenderChat: ITgChat;
    function GetAuthorSignature: string;
    /// <summary>Chat that sent the message originally</summary>
    property SenderChat: ITgChat read GetSenderChat;
    /// <summary>
    ///   Optional. For messages originally sent by an anonymous chat administrator, original
    ///   message author signature
    /// </summary>
    property AuthorSignature: string read GetAuthorSignature;
  end;

  /// <summary>The message was originally sent to a channel chat.</summary>
  ITgMessageOriginChannel = interface(ITgMessageOrigin)
    ['{E327AEA4-67F9-57A3-823B-DED8FB8FF493}']
    function GetChat: ITgChat;
    function GetMessageId: Int64;
    function GetAuthorSignature: string;
    /// <summary>Channel chat to which the message was originally sent</summary>
    property Chat: ITgChat read GetChat;
    /// <summary>Unique message identifier inside the chat</summary>
    property MessageId: Int64 read GetMessageId;
    /// <summary>Optional. Signature of the original post author</summary>
    property AuthorSignature: string read GetAuthorSignature;
  end;

  /// <summary>
  ///   This object represents one size of a photo or a file / sticker thumbnail.
  /// </summary>
  ITgPhotoSize = interface(ITgJsonObject)
    ['{ED012B43-F842-5EAD-A258-A8FA4C8DEE90}']
    function GetFileId: string;
    function GetFileUniqueId: string;
    function GetWidth: Integer;
    function GetHeight: Integer;
    function GetFileSize: Int64;
    function GetHasFileSize: Boolean;
    /// <summary>
    ///   Identifier for this file, which can be used to download or reuse the file
    /// </summary>
    property FileId: string read GetFileId;
    /// <summary>
    ///   Unique identifier for this file, which is supposed to be the same over time and for
    ///   different bots. Can't be used to download or reuse the file.
    /// </summary>
    property FileUniqueId: string read GetFileUniqueId;
    /// <summary>Photo width</summary>
    property Width: Integer read GetWidth;
    /// <summary>Photo height</summary>
    property Height: Integer read GetHeight;
    /// <summary>Optional. File size in bytes</summary>
    property FileSize: Int64 read GetFileSize;
    /// <summary>Поле file_size присутствует.</summary>
    property HasFileSize: Boolean read GetHasFileSize;
  end;

  /// <summary>
  ///   This object represents an animation file (GIF or H.264/MPEG-4 AVC video without sound).
  /// </summary>
  ITgAnimation = interface(ITgJsonObject)
    ['{5719861D-4B64-57E5-B0BD-32E412E4D686}']
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
    /// <summary>
    ///   Identifier for this file, which can be used to download or reuse the file
    /// </summary>
    property FileId: string read GetFileId;
    /// <summary>
    ///   Unique identifier for this file, which is supposed to be the same over time and for
    ///   different bots. Can't be used to download or reuse the file.
    /// </summary>
    property FileUniqueId: string read GetFileUniqueId;
    /// <summary>Video width as defined by the sender</summary>
    property Width: Integer read GetWidth;
    /// <summary>Video height as defined by the sender</summary>
    property Height: Integer read GetHeight;
    /// <summary>Duration of the video in seconds as defined by the sender</summary>
    property Duration: Integer read GetDuration;
    /// <summary>Optional. Animation thumbnail as defined by the sender</summary>
    property Thumbnail: ITgPhotoSize read GetThumbnail;
    /// <summary>Optional. Original animation filename as defined by the sender</summary>
    property FileName: string read GetFileName;
    /// <summary>Optional. MIME type of the file as defined by the sender</summary>
    property MimeType: string read GetMimeType;
    /// <summary>
    ///   Optional. File size in bytes. It can be bigger than 2^31 and some programming languages
    ///   may have difficulty/silent defects in interpreting it. But it has at most 52 significant
    ///   bits, so a signed 64-bit integer or double-precision float type are safe for storing this
    ///   value.
    /// </summary>
    property FileSize: Int64 read GetFileSize;
    /// <summary>Поле file_size присутствует.</summary>
    property HasFileSize: Boolean read GetHasFileSize;
  end;

  /// <summary>
  ///   This object represents an audio file to be treated as music by the Telegram clients.
  /// </summary>
  ITgAudio = interface(ITgJsonObject)
    ['{9E1AC75F-F1FE-5DF0-854A-F66691620A22}']
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
    /// <summary>
    ///   Identifier for this file, which can be used to download or reuse the file
    /// </summary>
    property FileId: string read GetFileId;
    /// <summary>
    ///   Unique identifier for this file, which is supposed to be the same over time and for
    ///   different bots. Can't be used to download or reuse the file.
    /// </summary>
    property FileUniqueId: string read GetFileUniqueId;
    /// <summary>Duration of the audio in seconds as defined by the sender</summary>
    property Duration: Integer read GetDuration;
    /// <summary>
    ///   Optional. Performer of the audio as defined by the sender or by audio tags
    /// </summary>
    property Performer: string read GetPerformer;
    /// <summary>
    ///   Optional. Title of the audio as defined by the sender or by audio tags
    /// </summary>
    property Title: string read GetTitle;
    /// <summary>Optional. Original filename as defined by the sender</summary>
    property FileName: string read GetFileName;
    /// <summary>Optional. MIME type of the file as defined by the sender</summary>
    property MimeType: string read GetMimeType;
    /// <summary>
    ///   Optional. File size in bytes. It can be bigger than 2^31 and some programming languages
    ///   may have difficulty/silent defects in interpreting it. But it has at most 52 significant
    ///   bits, so a signed 64-bit integer or double-precision float type are safe for storing this
    ///   value.
    /// </summary>
    property FileSize: Int64 read GetFileSize;
    /// <summary>Поле file_size присутствует.</summary>
    property HasFileSize: Boolean read GetHasFileSize;
    /// <summary>
    ///   Optional. Thumbnail of the album cover to which the music file belongs
    /// </summary>
    property Thumbnail: ITgPhotoSize read GetThumbnail;
  end;

  /// <summary>
  ///   This object represents a general file (as opposed to photos, voice messages and audio
  ///   files).
  /// </summary>
  ITgDocument = interface(ITgJsonObject)
    ['{6ECF8047-64BB-50B0-A2B1-ECEA2018A1D1}']
    function GetFileId: string;
    function GetFileUniqueId: string;
    function GetThumbnail: ITgPhotoSize;
    function GetFileName: string;
    function GetMimeType: string;
    function GetFileSize: Int64;
    function GetHasFileSize: Boolean;
    /// <summary>
    ///   Identifier for this file, which can be used to download or reuse the file
    /// </summary>
    property FileId: string read GetFileId;
    /// <summary>
    ///   Unique identifier for this file, which is supposed to be the same over time and for
    ///   different bots. Can't be used to download or reuse the file.
    /// </summary>
    property FileUniqueId: string read GetFileUniqueId;
    /// <summary>Optional. Document thumbnail as defined by the sender</summary>
    property Thumbnail: ITgPhotoSize read GetThumbnail;
    /// <summary>Optional. Original filename as defined by the sender</summary>
    property FileName: string read GetFileName;
    /// <summary>Optional. MIME type of the file as defined by the sender</summary>
    property MimeType: string read GetMimeType;
    /// <summary>
    ///   Optional. File size in bytes. It can be bigger than 2^31 and some programming languages
    ///   may have difficulty/silent defects in interpreting it. But it has at most 52 significant
    ///   bits, so a signed 64-bit integer or double-precision float type are safe for storing this
    ///   value.
    /// </summary>
    property FileSize: Int64 read GetFileSize;
    /// <summary>Поле file_size присутствует.</summary>
    property HasFileSize: Boolean read GetHasFileSize;
  end;

  /// <summary>This object represents a live photo.</summary>
  ITgLivePhoto = interface(ITgJsonObject)
    ['{C9B0606A-F065-5704-B97C-5E63DA28ECB0}']
    function GetPhoto: TArray<ITgPhotoSize>;
    function GetFileId: string;
    function GetFileUniqueId: string;
    function GetWidth: Integer;
    function GetHeight: Integer;
    function GetDuration: Integer;
    function GetMimeType: string;
    function GetFileSize: Int64;
    function GetHasFileSize: Boolean;
    /// <summary>Optional. Available sizes of the corresponding static photo</summary>
    property Photo: TArray<ITgPhotoSize> read GetPhoto;
    /// <summary>
    ///   Identifier for the video file which can be used to download or reuse the file
    /// </summary>
    property FileId: string read GetFileId;
    /// <summary>
    ///   Unique identifier for the video file which is supposed to be the same over time and for
    ///   different bots. Can't be used to download or reuse the file.
    /// </summary>
    property FileUniqueId: string read GetFileUniqueId;
    /// <summary>Video width as defined by the sender</summary>
    property Width: Integer read GetWidth;
    /// <summary>Video height as defined by the sender</summary>
    property Height: Integer read GetHeight;
    /// <summary>Duration of the video in seconds as defined by the sender</summary>
    property Duration: Integer read GetDuration;
    /// <summary>Optional. MIME type of the file as defined by the sender</summary>
    property MimeType: string read GetMimeType;
    /// <summary>
    ///   Optional. File size in bytes. It can be bigger than 2^31 and some programming languages
    ///   may have difficulty/silent defects in interpreting it. But it has at most 52 significant
    ///   bits, so a signed 64-bit integer or double-precision float type are safe for storing this
    ///   value.
    /// </summary>
    property FileSize: Int64 read GetFileSize;
    /// <summary>Поле file_size присутствует.</summary>
    property HasFileSize: Boolean read GetHasFileSize;
  end;

  /// <summary>This object represents a story.</summary>
  ITgStory = interface(ITgJsonObject)
    ['{73FDB564-6BA7-5FB0-9507-512AD191B051}']
    function GetChat: ITgChat;
    function GetId: Int64;
    /// <summary>Chat that posted the story</summary>
    property Chat: ITgChat read GetChat;
    /// <summary>Unique identifier for the story in the chat</summary>
    property Id: Int64 read GetId;
  end;

  /// <summary>This object represents a video file of a specific quality.</summary>
  ITgVideoQuality = interface(ITgJsonObject)
    ['{59ED4A4A-6D96-5865-8C90-73C934ECF98C}']
    function GetFileId: string;
    function GetFileUniqueId: string;
    function GetWidth: Integer;
    function GetHeight: Integer;
    function GetCodec: string;
    function GetFileSize: Int64;
    function GetHasFileSize: Boolean;
    /// <summary>
    ///   Identifier for this file, which can be used to download or reuse the file
    /// </summary>
    property FileId: string read GetFileId;
    /// <summary>
    ///   Unique identifier for this file, which is supposed to be the same over time and for
    ///   different bots. Can't be used to download or reuse the file.
    /// </summary>
    property FileUniqueId: string read GetFileUniqueId;
    /// <summary>Video width</summary>
    property Width: Integer read GetWidth;
    /// <summary>Video height</summary>
    property Height: Integer read GetHeight;
    /// <summary>
    ///   Codec that was used to encode the video, for example, “h264”, “h265”, or “av01”
    /// </summary>
    property Codec: string read GetCodec;
    /// <summary>
    ///   Optional. File size in bytes. It can be bigger than 2^31 and some programming languages
    ///   may have difficulty/silent defects in interpreting it. But it has at most 52 significant
    ///   bits, so a signed 64-bit integer or double-precision float type are safe for storing this
    ///   value.
    /// </summary>
    property FileSize: Int64 read GetFileSize;
    /// <summary>Поле file_size присутствует.</summary>
    property HasFileSize: Boolean read GetHasFileSize;
  end;

  /// <summary>This object represents a video file.</summary>
  ITgVideo = interface(ITgJsonObject)
    ['{95F726B5-F69B-593E-85AB-AFFFA7737FA4}']
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
    /// <summary>
    ///   Identifier for this file, which can be used to download or reuse the file
    /// </summary>
    property FileId: string read GetFileId;
    /// <summary>
    ///   Unique identifier for this file, which is supposed to be the same over time and for
    ///   different bots. Can't be used to download or reuse the file.
    /// </summary>
    property FileUniqueId: string read GetFileUniqueId;
    /// <summary>Video width as defined by the sender</summary>
    property Width: Integer read GetWidth;
    /// <summary>Video height as defined by the sender</summary>
    property Height: Integer read GetHeight;
    /// <summary>Duration of the video in seconds as defined by the sender</summary>
    property Duration: Integer read GetDuration;
    /// <summary>Optional. Video thumbnail</summary>
    property Thumbnail: ITgPhotoSize read GetThumbnail;
    /// <summary>
    ///   Optional. Available sizes of the cover of the video in the message
    /// </summary>
    property Cover: TArray<ITgPhotoSize> read GetCover;
    /// <summary>
    ///   Optional. Timestamp in seconds from which the video will play in the message
    /// </summary>
    property StartTimestamp: Integer read GetStartTimestamp;
    /// <summary>Поле start_timestamp присутствует.</summary>
    property HasStartTimestamp: Boolean read GetHasStartTimestamp;
    /// <summary>Optional. List of available qualities of the video</summary>
    property Qualities: TArray<ITgVideoQuality> read GetQualities;
    /// <summary>Optional. Original filename as defined by the sender</summary>
    property FileName: string read GetFileName;
    /// <summary>Optional. MIME type of the file as defined by the sender</summary>
    property MimeType: string read GetMimeType;
    /// <summary>
    ///   Optional. File size in bytes. It can be bigger than 2^31 and some programming languages
    ///   may have difficulty/silent defects in interpreting it. But it has at most 52 significant
    ///   bits, so a signed 64-bit integer or double-precision float type are safe for storing this
    ///   value.
    /// </summary>
    property FileSize: Int64 read GetFileSize;
    /// <summary>Поле file_size присутствует.</summary>
    property HasFileSize: Boolean read GetHasFileSize;
  end;

  /// <summary>This object represents a video message.</summary>
  ITgVideoNote = interface(ITgJsonObject)
    ['{0022B811-5572-5C93-A26B-4FE76CCF55D3}']
    function GetFileId: string;
    function GetFileUniqueId: string;
    function GetLength: Integer;
    function GetDuration: Integer;
    function GetThumbnail: ITgPhotoSize;
    function GetFileSize: Int64;
    function GetHasFileSize: Boolean;
    /// <summary>
    ///   Identifier for this file, which can be used to download or reuse the file
    /// </summary>
    property FileId: string read GetFileId;
    /// <summary>
    ///   Unique identifier for this file, which is supposed to be the same over time and for
    ///   different bots. Can't be used to download or reuse the file.
    /// </summary>
    property FileUniqueId: string read GetFileUniqueId;
    /// <summary>
    ///   Video width and height (diameter of the video message) as defined by the sender
    /// </summary>
    property Length: Integer read GetLength;
    /// <summary>Duration of the video in seconds as defined by the sender</summary>
    property Duration: Integer read GetDuration;
    /// <summary>Optional. Video thumbnail</summary>
    property Thumbnail: ITgPhotoSize read GetThumbnail;
    /// <summary>Optional. File size in bytes</summary>
    property FileSize: Int64 read GetFileSize;
    /// <summary>Поле file_size присутствует.</summary>
    property HasFileSize: Boolean read GetHasFileSize;
  end;

  /// <summary>This object represents a voice note.</summary>
  ITgVoice = interface(ITgJsonObject)
    ['{EE986769-5BF4-5061-A9B2-6DED9AC158C7}']
    function GetFileId: string;
    function GetFileUniqueId: string;
    function GetDuration: Integer;
    function GetMimeType: string;
    function GetFileSize: Int64;
    function GetHasFileSize: Boolean;
    /// <summary>
    ///   Identifier for this file, which can be used to download or reuse the file
    /// </summary>
    property FileId: string read GetFileId;
    /// <summary>
    ///   Unique identifier for this file, which is supposed to be the same over time and for
    ///   different bots. Can't be used to download or reuse the file.
    /// </summary>
    property FileUniqueId: string read GetFileUniqueId;
    /// <summary>Duration of the audio in seconds as defined by the sender</summary>
    property Duration: Integer read GetDuration;
    /// <summary>Optional. MIME type of the file as defined by the sender</summary>
    property MimeType: string read GetMimeType;
    /// <summary>
    ///   Optional. File size in bytes. It can be bigger than 2^31 and some programming languages
    ///   may have difficulty/silent defects in interpreting it. But it has at most 52 significant
    ///   bits, so a signed 64-bit integer or double-precision float type are safe for storing this
    ///   value.
    /// </summary>
    property FileSize: Int64 read GetFileSize;
    /// <summary>Поле file_size присутствует.</summary>
    property HasFileSize: Boolean read GetHasFileSize;
  end;

  /// <summary>Describes the paid media added to a message.</summary>
  ITgPaidMediaInfo = interface(ITgJsonObject)
    ['{2E8F1151-5C7C-5DD9-A50E-0B0410DAB46D}']
    function GetStarCount: Integer;
    function GetPaidMedia: TArray<ITgPaidMedia>;
    /// <summary>
    ///   The number of Telegram Stars that must be paid to buy access to the media
    /// </summary>
    property StarCount: Integer read GetStarCount;
    /// <summary>Information about the paid media</summary>
    property PaidMedia: TArray<ITgPaidMedia> read GetPaidMedia;
  end;

  /// <summary>
  ///   This object describes paid media. Виды (Kind, As*): ITgPaidMediaLivePhoto,
  ///   ITgPaidMediaPhoto, ITgPaidMediaPreview, ITgPaidMediaVideo.
  /// </summary>
  ITgPaidMedia = interface(ITgJsonObject)
    ['{26DA45AE-4EF5-56BD-849A-EEAE080F6B0A}']
    function GetKind: TTgPaidMediaKind;
    function GetKindText: string;
    /// <summary>ITgPaidMediaLivePhoto или nil, если объект другого вида.</summary>
    function AsLivePhoto: ITgPaidMediaLivePhoto;
    /// <summary>ITgPaidMediaPhoto или nil, если объект другого вида.</summary>
    function AsPhoto: ITgPaidMediaPhoto;
    /// <summary>ITgPaidMediaPreview или nil, если объект другого вида.</summary>
    function AsPreview: ITgPaidMediaPreview;
    /// <summary>ITgPaidMediaVideo или nil, если объект другого вида.</summary>
    function AsVideo: ITgPaidMediaVideo;
    /// <summary>Вид объекта (Unknown — неизвестный этой версии библиотеки).</summary>
    property Kind: TTgPaidMediaKind read GetKind;
    /// <summary>
    ///   Значение поля type в JSON как есть (в т.ч. при Kind = Unknown); для вариантов-строк и
    ///   массивов — пустая строка.
    /// </summary>
    property KindText: string read GetKindText;
  end;

  /// <summary>The paid media is a live photo.</summary>
  ITgPaidMediaLivePhoto = interface(ITgPaidMedia)
    ['{69E9B366-6746-5E0E-9132-8E71A1EAF2A7}']
    function GetLivePhoto: ITgLivePhoto;
    /// <summary>The photo</summary>
    property LivePhoto: ITgLivePhoto read GetLivePhoto;
  end;

  /// <summary>The paid media is a photo.</summary>
  ITgPaidMediaPhoto = interface(ITgPaidMedia)
    ['{AAC0F28D-346A-56C5-AFA6-4C8BD12D1F60}']
    function GetPhoto: TArray<ITgPhotoSize>;
    /// <summary>The photo</summary>
    property Photo: TArray<ITgPhotoSize> read GetPhoto;
  end;

  /// <summary>The paid media isn't available before the payment.</summary>
  ITgPaidMediaPreview = interface(ITgPaidMedia)
    ['{E6B7F775-B60B-5FE2-AD3F-7B8E64ED55ED}']
    function GetWidth: Integer;
    function GetHasWidth: Boolean;
    function GetHeight: Integer;
    function GetHasHeight: Boolean;
    function GetDuration: Integer;
    function GetHasDuration: Boolean;
    /// <summary>Optional. Media width as defined by the sender</summary>
    property Width: Integer read GetWidth;
    /// <summary>Поле width присутствует.</summary>
    property HasWidth: Boolean read GetHasWidth;
    /// <summary>Optional. Media height as defined by the sender</summary>
    property Height: Integer read GetHeight;
    /// <summary>Поле height присутствует.</summary>
    property HasHeight: Boolean read GetHasHeight;
    /// <summary>
    ///   Optional. Duration of the media in seconds as defined by the sender
    /// </summary>
    property Duration: Integer read GetDuration;
    /// <summary>Поле duration присутствует.</summary>
    property HasDuration: Boolean read GetHasDuration;
  end;

  /// <summary>The paid media is a video.</summary>
  ITgPaidMediaVideo = interface(ITgPaidMedia)
    ['{EC2ADBB0-2DDC-5A99-8C9F-1F7F690C9BB2}']
    function GetVideo: ITgVideo;
    /// <summary>The video</summary>
    property Video: ITgVideo read GetVideo;
  end;

  /// <summary>This object represents a phone contact.</summary>
  ITgContact = interface(ITgJsonObject)
    ['{DEE7B24E-AC39-532C-9FFF-AFCBF4EEE37A}']
    function GetPhoneNumber: string;
    function GetFirstName: string;
    function GetLastName: string;
    function GetUserId: Int64;
    function GetHasUserId: Boolean;
    function GetVcard: string;
    /// <summary>Contact's phone number</summary>
    property PhoneNumber: string read GetPhoneNumber;
    /// <summary>Contact's first name</summary>
    property FirstName: string read GetFirstName;
    /// <summary>Optional. Contact's last name</summary>
    property LastName: string read GetLastName;
    /// <summary>
    ///   Optional. Contact's user identifier in Telegram. This number may have more than 32
    ///   significant bits and some programming languages may have difficulty/silent defects in
    ///   interpreting it. But it has at most 52 significant bits, so a 64-bit integer or
    ///   double-precision float type are safe for storing this identifier.
    /// </summary>
    property UserId: Int64 read GetUserId;
    /// <summary>Поле user_id присутствует.</summary>
    property HasUserId: Boolean read GetHasUserId;
    /// <summary>
    ///   Optional. Additional data about the contact in the form of a vCard
    /// </summary>
    property Vcard: string read GetVcard;
  end;

  /// <summary>
  ///   This object represents an animated emoji that displays a random value.
  /// </summary>
  ITgDice = interface(ITgJsonObject)
    ['{88C06696-41AC-56CD-AEEF-2B5711A1AA29}']
    function GetEmoji: string;
    function GetValue: Integer;
    /// <summary>Emoji on which the dice throw animation is based</summary>
    property Emoji: string read GetEmoji;
    /// <summary>
    ///   Value of the dice, 1-6 for “🎲”, “🎯” and “🎳” base emoji, 1-5 for “🏀” and “⚽” base
    ///   emoji, 1-64 for “🎰” base emoji
    /// </summary>
    property Value: Integer read GetValue;
  end;

  /// <summary>Represents an HTTP link.</summary>
  ITgLink = interface(ITgJsonObject)
    ['{DA756022-A82C-5D68-A86C-E8E6FD202819}']
    function GetUrl: string;
    /// <summary>URL of the link</summary>
    property Url: string read GetUrl;
  end;

  /// <summary>
  ///   At most one of the optional fields can be present in any given object.
  /// </summary>
  ITgPollMedia = interface(ITgJsonObject)
    ['{35EA1F9D-ECE4-5160-BC6C-0E25B0C247AE}']
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
    /// <summary>Optional. Media is an animation, information about the animation</summary>
    property Animation: ITgAnimation read GetAnimation;
    /// <summary>
    ///   Optional. Media is an audio file, information about the file; currently, can't be received
    ///   in a poll option
    /// </summary>
    property Audio: ITgAudio read GetAudio;
    /// <summary>
    ///   Optional. Media is a general file, information about the file; currently, can't be
    ///   received in a poll option
    /// </summary>
    property Document: ITgDocument read GetDocument;
    /// <summary>Optional. The HTTP link attached to the poll option</summary>
    property Link: ITgLink read GetLink;
    /// <summary>Optional. Media is a live photo, information about the live photo</summary>
    property LivePhoto: ITgLivePhoto read GetLivePhoto;
    /// <summary>
    ///   Optional. Media is a shared location, information about the location
    /// </summary>
    property Location: ITgLocation read GetLocation;
    /// <summary>Optional. Media is a photo, available sizes of the photo</summary>
    property Photo: TArray<ITgPhotoSize> read GetPhoto;
    /// <summary>
    ///   Optional. Media is a sticker, information about the sticker; currently, for poll options
    ///   only
    /// </summary>
    property Sticker: ITgSticker read GetSticker;
    /// <summary>Optional. Media is a venue, information about the venue</summary>
    property Venue: ITgVenue read GetVenue;
    /// <summary>Optional. Media is a video, information about the video</summary>
    property Video: ITgVideo read GetVideo;
  end;

  /// <summary>This object contains information about one answer option in a poll.</summary>
  ITgPollOption = interface(ITgJsonObject)
    ['{114B2154-411F-5E70-8ADE-55EF880A9B13}']
    function GetPersistentId: string;
    function GetText: string;
    function GetTextEntities: TArray<ITgMessageEntity>;
    function GetMedia: ITgPollMedia;
    function GetVoterCount: Integer;
    function GetAddedByUser: ITgUser;
    function GetAddedByChat: ITgChat;
    function GetAdditionDate: Int64;
    function GetHasAdditionDate: Boolean;
    /// <summary>
    ///   Unique identifier of the option, persistent on option addition and deletion
    /// </summary>
    property PersistentId: string read GetPersistentId;
    /// <summary>Option text, 1-100 characters</summary>
    property Text: string read GetText;
    /// <summary>
    ///   Optional. Special entities that appear in the option text. Currently, only custom emoji
    ///   entities are allowed in poll option texts
    /// </summary>
    property TextEntities: TArray<ITgMessageEntity> read GetTextEntities;
    /// <summary>Optional. Media added to the poll option</summary>
    property Media: ITgPollMedia read GetMedia;
    /// <summary>Number of users who voted for this option; may be 0 if unknown</summary>
    property VoterCount: Integer read GetVoterCount;
    /// <summary>
    ///   Optional. User who added the option; omitted if the option wasn't added by a user after
    ///   poll creation
    /// </summary>
    property AddedByUser: ITgUser read GetAddedByUser;
    /// <summary>
    ///   Optional. Chat that added the option; omitted if the option wasn't added by a chat after
    ///   poll creation
    /// </summary>
    property AddedByChat: ITgChat read GetAddedByChat;
    /// <summary>
    ///   Optional. Point in time (Unix timestamp) when the option was added; omitted if the option
    ///   existed in the original poll
    /// </summary>
    property AdditionDate: Int64 read GetAdditionDate;
    /// <summary>Поле addition_date присутствует.</summary>
    property HasAdditionDate: Boolean read GetHasAdditionDate;
  end;

  /// <summary>
  ///   This object contains information about one answer option in a poll to be sent.
  /// </summary>
  ITgInputPollOption = interface(ITgOutObject)
    ['{CF211323-6B8E-5B18-969A-94587F2F6BEC}']
    /// <summary>Задаёт text: Option text, 1-100 characters</summary>
    function WithText(const AValue: string): ITgInputPollOption;
    /// <summary>
    ///   Задаёт text_parse_mode: Optional. Mode for parsing entities in the text. See formatting
    ///   options for more details. Currently, only custom emoji entities are allowed.
    /// </summary>
    function WithTextParseMode(const AValue: string): ITgInputPollOption;
    /// <summary>
    ///   Задаёт text_entities: Optional. A JSON-serialized list of special entities that appear in
    ///   the poll option text. It can be specified instead of text_parse_mode.
    /// </summary>
    function WithTextEntities(const AValue: array of ITgMessageEntity): ITgInputPollOption;
    /// <summary>Задаёт media: Optional. Media added to the poll option</summary>
    function WithMedia(const AValue: TTgInputPollOptionMedia): ITgInputPollOption;
  end;

  /// <summary>This object represents an answer of a user in a non-anonymous poll.</summary>
  ITgPollAnswer = interface(ITgJsonObject)
    ['{519400F2-63FA-536D-A75D-8A972727D9F1}']
    function GetPollId: string;
    function GetVoterChat: ITgChat;
    function GetUser: ITgUser;
    function GetOptionIds: TArray<Int64>;
    function GetOptionPersistentIds: TArray<string>;
    /// <summary>Unique poll identifier</summary>
    property PollId: string read GetPollId;
    /// <summary>
    ///   Optional. The chat that changed the answer to the poll, if the voter is anonymous
    /// </summary>
    property VoterChat: ITgChat read GetVoterChat;
    /// <summary>
    ///   Optional. The user that changed the answer to the poll, if the voter isn't anonymous
    /// </summary>
    property User: ITgUser read GetUser;
    /// <summary>
    ///   0-based identifiers of chosen answer options. May be empty if the vote was retracted.
    /// </summary>
    property OptionIds: TArray<Int64> read GetOptionIds;
    /// <summary>
    ///   Persistent identifiers of the chosen answer options. May be empty if the vote was
    ///   retracted.
    /// </summary>
    property OptionPersistentIds: TArray<string> read GetOptionPersistentIds;
  end;

  /// <summary>This object contains information about a poll.</summary>
  ITgPoll = interface(ITgJsonObject)
    ['{4519CEEC-B5E3-5E8F-A746-8F1B668954FB}']
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
    /// <summary>Unique poll identifier</summary>
    property Id: string read GetId;
    /// <summary>Poll question, 1-300 characters</summary>
    property Question: string read GetQuestion;
    /// <summary>
    ///   Optional. Special entities that appear in the question. Currently, only custom emoji
    ///   entities are allowed in poll questions
    /// </summary>
    property QuestionEntities: TArray<ITgMessageEntity> read GetQuestionEntities;
    /// <summary>List of poll options</summary>
    property Options: TArray<ITgPollOption> read GetOptions;
    /// <summary>Total number of users that voted in the poll</summary>
    property TotalVoterCount: Integer read GetTotalVoterCount;
    /// <summary>True, if the poll is closed</summary>
    property IsClosed: Boolean read GetIsClosed;
    /// <summary>True, if the poll is anonymous</summary>
    property IsAnonymous: Boolean read GetIsAnonymous;
    /// <summary>Poll type, currently can be “regular” or “quiz”</summary>
    property PollType: string read GetPollType;
    /// <summary>True, if the poll allows multiple answers</summary>
    property AllowsMultipleAnswers: Boolean read GetAllowsMultipleAnswers;
    /// <summary>True, if the poll allows to change the chosen answer options</summary>
    property AllowsRevoting: Boolean read GetAllowsRevoting;
    /// <summary>
    ///   True if voting is limited to users who have been members of the chat where the poll was
    ///   originally sent for more than 24 hours
    /// </summary>
    property MembersOnly: Boolean read GetMembersOnly;
    /// <summary>
    ///   Optional. A list of two-letter ISO 3166-1 alpha-2 country codes indicating the countries
    ///   from which users can vote in the poll. The country code “FT” is used for users with
    ///   anonymous numbers. If omitted, then users from any country can participate in the poll.
    /// </summary>
    property CountryCodes: TArray<string> read GetCountryCodes;
    /// <summary>
    ///   Optional. Array of 0-based identifiers of the correct answer options. Available only for
    ///   polls in quiz mode which are closed or were sent (not forwarded) by the bot or to the
    ///   private chat with the bot.
    /// </summary>
    property CorrectOptionIds: TArray<Int64> read GetCorrectOptionIds;
    /// <summary>
    ///   Optional. Text that is shown when a user chooses an incorrect answer or taps on the lamp
    ///   icon in a quiz-style poll, 0-200 characters
    /// </summary>
    property Explanation: string read GetExplanation;
    /// <summary>
    ///   Optional. Special entities like usernames, URLs, bot commands, etc. that appear in the
    ///   explanation
    /// </summary>
    property ExplanationEntities: TArray<ITgMessageEntity> read GetExplanationEntities;
    /// <summary>Optional. Media added to the quiz explanation</summary>
    property ExplanationMedia: ITgPollMedia read GetExplanationMedia;
    /// <summary>
    ///   Optional. Amount of time in seconds the poll will be active after creation
    /// </summary>
    property OpenPeriod: Integer read GetOpenPeriod;
    /// <summary>Поле open_period присутствует.</summary>
    property HasOpenPeriod: Boolean read GetHasOpenPeriod;
    /// <summary>
    ///   Optional. Point in time (Unix timestamp) when the poll will be automatically closed
    /// </summary>
    property CloseDate: Int64 read GetCloseDate;
    /// <summary>Поле close_date присутствует.</summary>
    property HasCloseDate: Boolean read GetHasCloseDate;
    /// <summary>
    ///   Optional. Description of the poll; for polls inside the Message object only
    /// </summary>
    property Description: string read GetDescription;
    /// <summary>
    ///   Optional. Special entities like usernames, URLs, bot commands, etc. that appear in the
    ///   description
    /// </summary>
    property DescriptionEntities: TArray<ITgMessageEntity> read GetDescriptionEntities;
    /// <summary>
    ///   Optional. Media added to the poll description; for polls inside the Message object only
    /// </summary>
    property Media: ITgPollMedia read GetMedia;
  end;

  /// <summary>Describes a task in a checklist.</summary>
  ITgChecklistTask = interface(ITgJsonObject)
    ['{49264AB8-6A05-56A2-95DB-C7F284066DE1}']
    function GetId: Int64;
    function GetText: string;
    function GetTextEntities: TArray<ITgMessageEntity>;
    function GetCompletedByUser: ITgUser;
    function GetCompletedByChat: ITgChat;
    function GetCompletionDate: Int64;
    function GetHasCompletionDate: Boolean;
    /// <summary>Unique identifier of the task</summary>
    property Id: Int64 read GetId;
    /// <summary>Text of the task</summary>
    property Text: string read GetText;
    /// <summary>Optional. Special entities that appear in the task text</summary>
    property TextEntities: TArray<ITgMessageEntity> read GetTextEntities;
    /// <summary>
    ///   Optional. User that completed the task; omitted if the task wasn't completed by a user
    /// </summary>
    property CompletedByUser: ITgUser read GetCompletedByUser;
    /// <summary>
    ///   Optional. Chat that completed the task; omitted if the task wasn't completed by a chat
    /// </summary>
    property CompletedByChat: ITgChat read GetCompletedByChat;
    /// <summary>
    ///   Optional. Point in time (Unix timestamp) when the task was completed; 0 if the task wasn't
    ///   completed
    /// </summary>
    property CompletionDate: Int64 read GetCompletionDate;
    /// <summary>Поле completion_date присутствует.</summary>
    property HasCompletionDate: Boolean read GetHasCompletionDate;
  end;

  /// <summary>Describes a checklist.</summary>
  ITgChecklist = interface(ITgJsonObject)
    ['{1EC58CF1-B2B4-568A-84E2-656E313E7B2E}']
    function GetTitle: string;
    function GetTitleEntities: TArray<ITgMessageEntity>;
    function GetTasks: TArray<ITgChecklistTask>;
    function GetOthersCanAddTasks: Boolean;
    function GetOthersCanMarkTasksAsDone: Boolean;
    /// <summary>Title of the checklist</summary>
    property Title: string read GetTitle;
    /// <summary>Optional. Special entities that appear in the checklist title</summary>
    property TitleEntities: TArray<ITgMessageEntity> read GetTitleEntities;
    /// <summary>List of tasks in the checklist</summary>
    property Tasks: TArray<ITgChecklistTask> read GetTasks;
    /// <summary>
    ///   Optional. True, if users other than the creator of the list can add tasks to the list
    /// </summary>
    property OthersCanAddTasks: Boolean read GetOthersCanAddTasks;
    /// <summary>
    ///   Optional. True, if users other than the creator of the list can mark tasks as done or not
    ///   done
    /// </summary>
    property OthersCanMarkTasksAsDone: Boolean read GetOthersCanMarkTasksAsDone;
  end;

  /// <summary>Describes a task to add to a checklist.</summary>
  ITgInputChecklistTask = interface(ITgOutObject)
    ['{A1138E4C-08FF-5199-BAB2-694899B60CAD}']
    /// <summary>
    ///   Задаёт id: Unique identifier of the task; must be positive and unique among all task
    ///   identifiers currently present in the checklist
    /// </summary>
    function WithId(AValue: Int64): ITgInputChecklistTask;
    /// <summary>
    ///   Задаёт text: Text of the task; 1-100 characters after entities parsing
    /// </summary>
    function WithText(const AValue: string): ITgInputChecklistTask;
    /// <summary>
    ///   Задаёт parse_mode: Optional. Mode for parsing entities in the text. See formatting options
    ///   for more details.
    /// </summary>
    function WithParseMode(const AValue: string): ITgInputChecklistTask;
    /// <summary>
    ///   Задаёт text_entities: Optional. List of special entities that appear in the text, which
    ///   can be specified instead of parse_mode. Currently, only bold, italic, underline,
    ///   strikethrough, spoiler, custom_emoji, and date_time entities are allowed.
    /// </summary>
    function WithTextEntities(const AValue: array of ITgMessageEntity): ITgInputChecklistTask;
  end;

  /// <summary>Describes a checklist to create.</summary>
  ITgInputChecklist = interface(ITgOutObject)
    ['{2C71F666-CBB6-5782-877E-CB7416753988}']
    /// <summary>
    ///   Задаёт title: Title of the checklist; 1-255 characters after entities parsing
    /// </summary>
    function WithTitle(const AValue: string): ITgInputChecklist;
    /// <summary>
    ///   Задаёт parse_mode: Optional. Mode for parsing entities in the title. See formatting
    ///   options for more details.
    /// </summary>
    function WithParseMode(const AValue: string): ITgInputChecklist;
    /// <summary>
    ///   Задаёт title_entities: Optional. List of special entities that appear in the title, which
    ///   can be specified instead of parse_mode. Currently, only bold, italic, underline,
    ///   strikethrough, spoiler, custom_emoji, and date_time entities are allowed.
    /// </summary>
    function WithTitleEntities(const AValue: array of ITgMessageEntity): ITgInputChecklist;
    /// <summary>Задаёт tasks: List of 1-30 tasks in the checklist</summary>
    function WithTasks(const AValue: array of ITgInputChecklistTask): ITgInputChecklist;
    /// <summary>
    ///   Задаёт others_can_add_tasks: Optional. Pass True if other users can add tasks to the
    ///   checklist
    /// </summary>
    function WithOthersCanAddTasks(AValue: Boolean): ITgInputChecklist;
    /// <summary>
    ///   Задаёт others_can_mark_tasks_as_done: Optional. Pass True if other users can mark tasks as
    ///   done or not done in the checklist
    /// </summary>
    function WithOthersCanMarkTasksAsDone(AValue: Boolean): ITgInputChecklist;
  end;

  /// <summary>This object represents a point on the map.</summary>
  ITgLocation = interface(ITgJsonObject)
    ['{E82165F8-0709-5D3C-AD2A-70AD911EC7B1}']
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
    /// <summary>
    ///   Задаёт latitude: Latitude as defined by the sender. Значение копируется в момент вызова:
    ///   последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithLatitude(AValue: Double): ITgLocation;
    /// <summary>
    ///   Задаёт longitude: Longitude as defined by the sender. Значение копируется в момент вызова:
    ///   последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithLongitude(AValue: Double): ITgLocation;
    /// <summary>
    ///   Задаёт horizontal_accuracy: Optional. The radius of uncertainty for the location, measured
    ///   in meters; 0-1500. Значение копируется в момент вызова: последующие изменения переданного
    ///   объекта на этот не влияют.
    /// </summary>
    function WithHorizontalAccuracy(AValue: Double): ITgLocation;
    /// <summary>
    ///   Задаёт live_period: Optional. Time relative to the message sending date, during which the
    ///   location can be updated; in seconds. For active live locations only. Значение копируется в
    ///   момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithLivePeriod(AValue: Integer): ITgLocation;
    /// <summary>
    ///   Задаёт heading: Optional. The direction in which user is moving, in degrees; 1-360. For
    ///   active live locations only. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithHeading(AValue: Integer): ITgLocation;
    /// <summary>
    ///   Задаёт proximity_alert_radius: Optional. The maximum distance for proximity alerts about
    ///   approaching another chat member, in meters. For sent live locations only. Значение
    ///   копируется в момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithProximityAlertRadius(AValue: Integer): ITgLocation;
    /// <summary>Latitude as defined by the sender</summary>
    property Latitude: Double read GetLatitude;
    /// <summary>Longitude as defined by the sender</summary>
    property Longitude: Double read GetLongitude;
    /// <summary>
    ///   Optional. The radius of uncertainty for the location, measured in meters; 0-1500
    /// </summary>
    property HorizontalAccuracy: Double read GetHorizontalAccuracy;
    /// <summary>Поле horizontal_accuracy присутствует.</summary>
    property HasHorizontalAccuracy: Boolean read GetHasHorizontalAccuracy;
    /// <summary>
    ///   Optional. Time relative to the message sending date, during which the location can be
    ///   updated; in seconds. For active live locations only.
    /// </summary>
    property LivePeriod: Integer read GetLivePeriod;
    /// <summary>Поле live_period присутствует.</summary>
    property HasLivePeriod: Boolean read GetHasLivePeriod;
    /// <summary>
    ///   Optional. The direction in which user is moving, in degrees; 1-360. For active live
    ///   locations only.
    /// </summary>
    property Heading: Integer read GetHeading;
    /// <summary>Поле heading присутствует.</summary>
    property HasHeading: Boolean read GetHasHeading;
    /// <summary>
    ///   Optional. The maximum distance for proximity alerts about approaching another chat member,
    ///   in meters. For sent live locations only.
    /// </summary>
    property ProximityAlertRadius: Integer read GetProximityAlertRadius;
    /// <summary>Поле proximity_alert_radius присутствует.</summary>
    property HasProximityAlertRadius: Boolean read GetHasProximityAlertRadius;
  end;

  /// <summary>This object represents a venue.</summary>
  ITgVenue = interface(ITgJsonObject)
    ['{65BC4A09-82A8-5E03-B928-B34D0AFC92E4}']
    function GetLocation: ITgLocation;
    function GetTitle: string;
    function GetAddress: string;
    function GetFoursquareId: string;
    function GetFoursquareType: string;
    function GetGooglePlaceId: string;
    function GetGooglePlaceType: string;
    /// <summary>Venue location. Can't be a live location.</summary>
    property Location: ITgLocation read GetLocation;
    /// <summary>Name of the venue</summary>
    property Title: string read GetTitle;
    /// <summary>Address of the venue</summary>
    property Address: string read GetAddress;
    /// <summary>Optional. Foursquare identifier of the venue</summary>
    property FoursquareId: string read GetFoursquareId;
    /// <summary>
    ///   Optional. Foursquare type of the venue. (For example, “arts_entertainment/default”,
    ///   “arts_entertainment/aquarium” or “food/icecream”.)
    /// </summary>
    property FoursquareType: string read GetFoursquareType;
    /// <summary>Optional. Google Places identifier of the venue</summary>
    property GooglePlaceId: string read GetGooglePlaceId;
    /// <summary>Optional. Google Places type of the venue. (See supported types.)</summary>
    property GooglePlaceType: string read GetGooglePlaceType;
  end;

  /// <summary>Describes data sent from a Web App to the bot.</summary>
  ITgWebAppData = interface(ITgJsonObject)
    ['{94C70173-BC13-529D-9B75-40C5263EECC2}']
    function GetData: string;
    function GetButtonText: string;
    /// <summary>
    ///   The data. Be aware that a bad client can send arbitrary data in this field.
    /// </summary>
    property Data: string read GetData;
    /// <summary>
    ///   Text of the web_app keyboard button from which the Web App was opened. Be aware that a bad
    ///   client can send arbitrary data in this field.
    /// </summary>
    property ButtonText: string read GetButtonText;
  end;

  /// <summary>
  ///   This object represents the content of a service message, sent whenever a user in the chat
  ///   triggers a proximity alert set by another user.
  /// </summary>
  ITgProximityAlertTriggered = interface(ITgJsonObject)
    ['{1AAF70B8-EA27-5D21-9283-E6F8BF21D582}']
    function GetTraveler: ITgUser;
    function GetWatcher: ITgUser;
    function GetDistance: Integer;
    /// <summary>User that triggered the alert</summary>
    property Traveler: ITgUser read GetTraveler;
    /// <summary>User that set the alert</summary>
    property Watcher: ITgUser read GetWatcher;
    /// <summary>The distance between the users</summary>
    property Distance: Integer read GetDistance;
  end;

  /// <summary>
  ///   This object represents a service message about a change in auto-delete timer settings.
  /// </summary>
  ITgMessageAutoDeleteTimerChanged = interface(ITgJsonObject)
    ['{BA67E0C5-ACF6-52C6-81ED-4C174CB04B12}']
    function GetMessageAutoDeleteTime: Integer;
    /// <summary>New auto-delete time for messages in the chat; in seconds</summary>
    property MessageAutoDeleteTime: Integer read GetMessageAutoDeleteTime;
  end;

  /// <summary>
  ///   This object contains information about the bot that was created to be managed by the current
  ///   bot.
  /// </summary>
  ITgManagedBotCreated = interface(ITgJsonObject)
    ['{24FFA25C-AAE0-5510-A890-19FB2BC59625}']
    function GetBot: ITgUser;
    /// <summary>
    ///   Information about the bot. The bot's token can be fetched using the method
    ///   getManagedBotToken.
    /// </summary>
    property Bot: ITgUser read GetBot;
  end;

  /// <summary>
  ///   This object contains information about the creation, token update, or owner update of a bot
  ///   that is managed by the current bot.
  /// </summary>
  ITgManagedBotUpdated = interface(ITgJsonObject)
    ['{5D068209-945B-57E6-A3CC-37B4CD854A67}']
    function GetUser: ITgUser;
    function GetBot: ITgUser;
    /// <summary>User that created the bot</summary>
    property User: ITgUser read GetUser;
    /// <summary>
    ///   Information about the bot. Token of the bot can be fetched using the method
    ///   getManagedBotToken.
    /// </summary>
    property Bot: ITgUser read GetBot;
  end;

  /// <summary>
  ///   This object contains information about changes to a user payment subscription toward the
  ///   current bot.
  /// </summary>
  ITgBotSubscriptionUpdated = interface(ITgJsonObject)
    ['{FEC03794-3E41-51AB-B7D2-453A195C2FE0}']
    function GetUser: ITgUser;
    function GetInvoicePayload: string;
    function GetState: string;
    /// <summary>User who subscribed for payments toward the bot</summary>
    property User: ITgUser read GetUser;
    /// <summary>Bot-specified invoice payload</summary>
    property InvoicePayload: string read GetInvoicePayload;
    /// <summary>
    ///   The new state of the subscription. Currently, it can be one of “canceled” if the user
    ///   canceled the subscription, “active” if the user re-enabled a previously canceled
    ///   subscription, or “failed” if payment for the subscription failed.
    /// </summary>
    property State: string read GetState;
  end;

  /// <summary>
  ///   This object describes an update about a user stopping message generation.
  /// </summary>
  ITgMessageGenerationStopped = interface(ITgJsonObject)
    ['{FFE815FB-98B6-5D87-817D-160C2EA15130}']
    function GetChat: ITgChat;
    function GetMessageThreadId: Int64;
    function GetHasMessageThreadId: Boolean;
    function GetDraftId: Int64;
    /// <summary>Chat in which the message is generated</summary>
    property Chat: ITgChat read GetChat;
    /// <summary>
    ///   Optional. Unique identifier of the message thread in which the message is generated
    /// </summary>
    property MessageThreadId: Int64 read GetMessageThreadId;
    /// <summary>Поле message_thread_id присутствует.</summary>
    property HasMessageThreadId: Boolean read GetHasMessageThreadId;
    /// <summary>Unique identifier of the message draft which was stopped</summary>
    property DraftId: Int64 read GetDraftId;
  end;

  /// <summary>Describes a service message about an option added to a poll.</summary>
  ITgPollOptionAdded = interface(ITgJsonObject)
    ['{87EAED59-D7FA-55AA-A41C-C1231069BAF7}']
    function GetPollMessage: ITgMaybeInaccessibleMessage;
    function GetOptionPersistentId: string;
    function GetOptionText: string;
    function GetOptionTextEntities: TArray<ITgMessageEntity>;
    /// <summary>
    ///   Optional. Message containing the poll to which the option was added, if known. Note that
    ///   the Message object in this field will not contain the reply_to_message field even if it
    ///   itself is a reply.
    /// </summary>
    property PollMessage: ITgMaybeInaccessibleMessage read GetPollMessage;
    /// <summary>Unique identifier of the added option</summary>
    property OptionPersistentId: string read GetOptionPersistentId;
    /// <summary>Option text</summary>
    property OptionText: string read GetOptionText;
    /// <summary>Optional. Special entities that appear in the option_text</summary>
    property OptionTextEntities: TArray<ITgMessageEntity> read GetOptionTextEntities;
  end;

  /// <summary>Describes a service message about an option deleted from a poll.</summary>
  ITgPollOptionDeleted = interface(ITgJsonObject)
    ['{30179A55-CCE2-5038-8B36-E1CFFB4481E7}']
    function GetPollMessage: ITgMaybeInaccessibleMessage;
    function GetOptionPersistentId: string;
    function GetOptionText: string;
    function GetOptionTextEntities: TArray<ITgMessageEntity>;
    /// <summary>
    ///   Optional. Message containing the poll from which the option was deleted, if known. Note
    ///   that the Message object in this field will not contain the reply_to_message field even if
    ///   it itself is a reply.
    /// </summary>
    property PollMessage: ITgMaybeInaccessibleMessage read GetPollMessage;
    /// <summary>Unique identifier of the deleted option</summary>
    property OptionPersistentId: string read GetOptionPersistentId;
    /// <summary>Option text</summary>
    property OptionText: string read GetOptionText;
    /// <summary>Optional. Special entities that appear in the option_text</summary>
    property OptionTextEntities: TArray<ITgMessageEntity> read GetOptionTextEntities;
  end;

  /// <summary>
  ///   This object represents a service message about a user boosting a chat.
  /// </summary>
  ITgChatBoostAdded = interface(ITgJsonObject)
    ['{E537B9B8-236D-5C64-B81B-11E848419B27}']
    function GetBoostCount: Integer;
    /// <summary>Number of boosts added by the user</summary>
    property BoostCount: Integer read GetBoostCount;
  end;

  /// <summary>
  ///   This object describes the way a background is filled based on the selected colors. Виды
  ///   (Kind, As*): ITgBackgroundFillSolid, ITgBackgroundFillGradient,
  ///   ITgBackgroundFillFreeformGradient.
  /// </summary>
  ITgBackgroundFill = interface(ITgJsonObject)
    ['{8051DFE1-0107-5D5C-9252-B162686EA6DE}']
    function GetKind: TTgBackgroundFillKind;
    function GetKindText: string;
    /// <summary>ITgBackgroundFillSolid или nil, если объект другого вида.</summary>
    function AsSolid: ITgBackgroundFillSolid;
    /// <summary>ITgBackgroundFillGradient или nil, если объект другого вида.</summary>
    function AsGradient: ITgBackgroundFillGradient;
    /// <summary>
    ///   ITgBackgroundFillFreeformGradient или nil, если объект другого вида.
    /// </summary>
    function AsFreeformGradient: ITgBackgroundFillFreeformGradient;
    /// <summary>Вид объекта (Unknown — неизвестный этой версии библиотеки).</summary>
    property Kind: TTgBackgroundFillKind read GetKind;
    /// <summary>
    ///   Значение поля type в JSON как есть (в т.ч. при Kind = Unknown); для вариантов-строк и
    ///   массивов — пустая строка.
    /// </summary>
    property KindText: string read GetKindText;
  end;

  /// <summary>The background is filled using the selected color.</summary>
  ITgBackgroundFillSolid = interface(ITgBackgroundFill)
    ['{07C2CC70-1270-5158-9557-F38EC90FB833}']
    function GetColor: Integer;
    /// <summary>The color of the background fill in the RGB24 format</summary>
    property Color: Integer read GetColor;
  end;

  /// <summary>The background is a gradient fill.</summary>
  ITgBackgroundFillGradient = interface(ITgBackgroundFill)
    ['{92099FA0-D910-5708-A6DF-E87962700FE1}']
    function GetTopColor: Integer;
    function GetBottomColor: Integer;
    function GetRotationAngle: Integer;
    /// <summary>Top color of the gradient in the RGB24 format</summary>
    property TopColor: Integer read GetTopColor;
    /// <summary>Bottom color of the gradient in the RGB24 format</summary>
    property BottomColor: Integer read GetBottomColor;
    /// <summary>Clockwise rotation angle of the background fill in degrees; 0-359</summary>
    property RotationAngle: Integer read GetRotationAngle;
  end;

  /// <summary>
  ///   The background is a freeform gradient that rotates after every message in the chat.
  /// </summary>
  ITgBackgroundFillFreeformGradient = interface(ITgBackgroundFill)
    ['{4778FA6F-65AD-5631-BFA8-CB48A2E8B534}']
    function GetColors: TArray<Integer>;
    /// <summary>
    ///   A list of the 3 or 4 base colors that are used to generate the freeform gradient in the
    ///   RGB24 format
    /// </summary>
    property Colors: TArray<Integer> read GetColors;
  end;

  /// <summary>
  ///   This object describes the type of a background. Виды (Kind, As*): ITgBackgroundTypeFill,
  ///   ITgBackgroundTypeWallpaper, ITgBackgroundTypePattern, ITgBackgroundTypeChatTheme.
  /// </summary>
  ITgBackgroundType = interface(ITgJsonObject)
    ['{348372E2-CDEA-54ED-BC9D-38F6F2319D1C}']
    function GetKind: TTgBackgroundTypeKind;
    function GetKindText: string;
    /// <summary>ITgBackgroundTypeFill или nil, если объект другого вида.</summary>
    function AsFill: ITgBackgroundTypeFill;
    /// <summary>ITgBackgroundTypeWallpaper или nil, если объект другого вида.</summary>
    function AsWallpaper: ITgBackgroundTypeWallpaper;
    /// <summary>ITgBackgroundTypePattern или nil, если объект другого вида.</summary>
    function AsPattern: ITgBackgroundTypePattern;
    /// <summary>ITgBackgroundTypeChatTheme или nil, если объект другого вида.</summary>
    function AsChatTheme: ITgBackgroundTypeChatTheme;
    /// <summary>Вид объекта (Unknown — неизвестный этой версии библиотеки).</summary>
    property Kind: TTgBackgroundTypeKind read GetKind;
    /// <summary>
    ///   Значение поля type в JSON как есть (в т.ч. при Kind = Unknown); для вариантов-строк и
    ///   массивов — пустая строка.
    /// </summary>
    property KindText: string read GetKindText;
  end;

  /// <summary>
  ///   The background is automatically filled based on the selected colors.
  /// </summary>
  ITgBackgroundTypeFill = interface(ITgBackgroundType)
    ['{50645EA8-0444-5F67-8384-743B64FDA9F5}']
    function GetFill: ITgBackgroundFill;
    function GetDarkThemeDimming: Integer;
    /// <summary>The background fill</summary>
    property Fill: ITgBackgroundFill read GetFill;
    /// <summary>Dimming of the background in dark themes, as a percentage; 0-100</summary>
    property DarkThemeDimming: Integer read GetDarkThemeDimming;
  end;

  /// <summary>The background is a wallpaper in the JPEG format.</summary>
  ITgBackgroundTypeWallpaper = interface(ITgBackgroundType)
    ['{A646CBC6-1CD7-5AD6-861A-32BDDB51F46C}']
    function GetDocument: ITgDocument;
    function GetDarkThemeDimming: Integer;
    function GetIsBlurred: Boolean;
    function GetIsMoving: Boolean;
    /// <summary>Document with the wallpaper</summary>
    property Document: ITgDocument read GetDocument;
    /// <summary>Dimming of the background in dark themes, as a percentage; 0-100</summary>
    property DarkThemeDimming: Integer read GetDarkThemeDimming;
    /// <summary>
    ///   Optional. True, if the wallpaper is downscaled to fit in a 450x450 square and then
    ///   box-blurred with radius 12
    /// </summary>
    property IsBlurred: Boolean read GetIsBlurred;
    /// <summary>
    ///   Optional. True, if the background moves slightly when the device is tilted
    /// </summary>
    property IsMoving: Boolean read GetIsMoving;
  end;

  /// <summary>
  ///   The background is a .PNG or .TGV (gzipped subset of SVG with MIME type
  ///   “application/x-tgwallpattern”) pattern to be combined with the background fill chosen by the
  ///   user.
  /// </summary>
  ITgBackgroundTypePattern = interface(ITgBackgroundType)
    ['{BE71E0F7-4192-533F-8FDC-5C5D68512CC6}']
    function GetDocument: ITgDocument;
    function GetFill: ITgBackgroundFill;
    function GetIntensity: Integer;
    function GetIsInverted: Boolean;
    function GetIsMoving: Boolean;
    /// <summary>Document with the pattern</summary>
    property Document: ITgDocument read GetDocument;
    /// <summary>The background fill that is combined with the pattern</summary>
    property Fill: ITgBackgroundFill read GetFill;
    /// <summary>
    ///   Intensity of the pattern when it is shown above the filled background; 0-100
    /// </summary>
    property Intensity: Integer read GetIntensity;
    /// <summary>
    ///   Optional. True, if the background fill must be applied only to the pattern itself. All
    ///   other pixels are black in this case. For dark themes only.
    /// </summary>
    property IsInverted: Boolean read GetIsInverted;
    /// <summary>
    ///   Optional. True, if the background moves slightly when the device is tilted
    /// </summary>
    property IsMoving: Boolean read GetIsMoving;
  end;

  /// <summary>The background is taken directly from a built-in chat theme.</summary>
  ITgBackgroundTypeChatTheme = interface(ITgBackgroundType)
    ['{3923C583-8C3C-534C-A786-0C2DDFA4D0C5}']
    function GetThemeName: string;
    /// <summary>Name of the chat theme, which is usually an emoji</summary>
    property ThemeName: string read GetThemeName;
  end;

  /// <summary>This object represents a chat background.</summary>
  ITgChatBackground = interface(ITgJsonObject)
    ['{36B3DC85-A8B3-580F-992A-277BE8A3BCA6}']
    function GetChatBackgroundType: ITgBackgroundType;
    /// <summary>Type of the background</summary>
    property ChatBackgroundType: ITgBackgroundType read GetChatBackgroundType;
  end;

  /// <summary>
  ///   Describes a service message about checklist tasks marked as done or not done.
  /// </summary>
  ITgChecklistTasksDone = interface(ITgJsonObject)
    ['{902DDA29-61C3-50C4-B9B0-75CE2CF0ED47}']
    function GetChecklistMessage: ITgMessage;
    function GetMarkedAsDoneTaskIds: TArray<Int64>;
    function GetMarkedAsNotDoneTaskIds: TArray<Int64>;
    /// <summary>
    ///   Optional. Message containing the checklist whose tasks were marked as done or not done.
    ///   Note that the Message object in this field will not contain the reply_to_message field
    ///   even if it itself is a reply.
    /// </summary>
    property ChecklistMessage: ITgMessage read GetChecklistMessage;
    /// <summary>Optional. Identifiers of the tasks that were marked as done</summary>
    property MarkedAsDoneTaskIds: TArray<Int64> read GetMarkedAsDoneTaskIds;
    /// <summary>Optional. Identifiers of the tasks that were marked as not done</summary>
    property MarkedAsNotDoneTaskIds: TArray<Int64> read GetMarkedAsNotDoneTaskIds;
  end;

  /// <summary>Describes a service message about tasks added to a checklist.</summary>
  ITgChecklistTasksAdded = interface(ITgJsonObject)
    ['{042FED31-332A-5F34-B0E1-F45B90FE9ACE}']
    function GetChecklistMessage: ITgMessage;
    function GetTasks: TArray<ITgChecklistTask>;
    /// <summary>
    ///   Optional. Message containing the checklist to which the tasks were added. Note that the
    ///   Message object in this field will not contain the reply_to_message field even if it itself
    ///   is a reply.
    /// </summary>
    property ChecklistMessage: ITgMessage read GetChecklistMessage;
    /// <summary>List of tasks added to the checklist</summary>
    property Tasks: TArray<ITgChecklistTask> read GetTasks;
  end;

  /// <summary>
  ///   Describes a service message about a chat or a bot being added to a community.
  /// </summary>
  ITgCommunityChatAdded = interface(ITgJsonObject)
    ['{353BDA6F-242F-5160-BA83-3A3D69BC2254}']
    function GetCommunity: ITgCommunity;
    /// <summary>The new community to which the chat or the bot belongs</summary>
    property Community: ITgCommunity read GetCommunity;
  end;

  /// <summary>
  ///   Describes a service message about a chat being joined by a user from a community.
  /// </summary>
  ITgCommunityChatJoined = interface(ITgJsonObject)
    ['{301B115F-3FE5-5860-9B32-A1934A550524}']
    function GetCommunity: ITgCommunity;
    /// <summary>The community from which the chat was joined</summary>
    property Community: ITgCommunity read GetCommunity;
  end;

  /// <summary>
  ///   Describes a service message about a chat or a bot being removed from a community. Currently
  ///   holds no information.
  /// </summary>
  ITgCommunityChatRemoved = interface(ITgJsonObject)
    ['{0566506E-8A55-5EA4-BE36-79E1A502E47C}']
  end;

  /// <summary>
  ///   This object represents a service message about a new forum topic created in the chat.
  /// </summary>
  ITgForumTopicCreated = interface(ITgJsonObject)
    ['{05B0DD5B-35F3-5737-84EA-09AC59139424}']
    function GetName: string;
    function GetIconColor: Integer;
    function GetIconCustomEmojiId: string;
    function GetIsNameImplicit: Boolean;
    /// <summary>Name of the topic</summary>
    property Name: string read GetName;
    /// <summary>Color of the topic icon in RGB format</summary>
    property IconColor: Integer read GetIconColor;
    /// <summary>
    ///   Optional. Unique identifier of the custom emoji shown as the topic icon
    /// </summary>
    property IconCustomEmojiId: string read GetIconCustomEmojiId;
    /// <summary>
    ///   Optional. True, if the name of the topic wasn't specified explicitly by its creator and
    ///   likely needs to be changed by the bot
    /// </summary>
    property IsNameImplicit: Boolean read GetIsNameImplicit;
  end;

  /// <summary>
  ///   This object represents a service message about a forum topic closed in the chat. Currently
  ///   holds no information.
  /// </summary>
  ITgForumTopicClosed = interface(ITgJsonObject)
    ['{1E2ADA97-6116-5429-82E8-515B8AD2A57C}']
  end;

  /// <summary>
  ///   This object represents a service message about an edited forum topic.
  /// </summary>
  ITgForumTopicEdited = interface(ITgJsonObject)
    ['{EEEF45AD-ED9D-55E4-A13C-793B5EA023DA}']
    function GetName: string;
    function GetIconCustomEmojiId: string;
    /// <summary>Optional. New name of the topic, if it was edited</summary>
    property Name: string read GetName;
    /// <summary>
    ///   Optional. New identifier of the custom emoji shown as the topic icon, if it was edited; an
    ///   empty string if the icon was removed
    /// </summary>
    property IconCustomEmojiId: string read GetIconCustomEmojiId;
  end;

  /// <summary>
  ///   This object represents a service message about a forum topic reopened in the chat. Currently
  ///   holds no information.
  /// </summary>
  ITgForumTopicReopened = interface(ITgJsonObject)
    ['{60CD3190-9951-5459-A529-41426C9E1546}']
  end;

  /// <summary>
  ///   This object represents a service message about General forum topic hidden in the chat.
  ///   Currently holds no information.
  /// </summary>
  ITgGeneralForumTopicHidden = interface(ITgJsonObject)
    ['{CBB65940-2128-5588-9EBC-9B60FED0DEB1}']
  end;

  /// <summary>
  ///   This object represents a service message about General forum topic unhidden in the chat.
  ///   Currently holds no information.
  /// </summary>
  ITgGeneralForumTopicUnhidden = interface(ITgJsonObject)
    ['{098D086B-0036-5D4A-90DD-57D74ED49FCF}']
  end;

  /// <summary>
  ///   This object contains information about a user that was shared with the bot using a
  ///   KeyboardButtonRequestUsers button.
  /// </summary>
  ITgSharedUser = interface(ITgJsonObject)
    ['{884D6043-72C2-5590-B3C6-AD9FA28B1293}']
    function GetUserId: Int64;
    function GetFirstName: string;
    function GetLastName: string;
    function GetUsername: string;
    function GetPhoto: TArray<ITgPhotoSize>;
    /// <summary>
    ///   Identifier of the shared user. This number may have more than 32 significant bits and some
    ///   programming languages may have difficulty/silent defects in interpreting it. But it has at
    ///   most 52 significant bits, so 64-bit integers or double-precision float types are safe for
    ///   storing these identifiers. The bot may not have access to the user and could be unable to
    ///   use this identifier, unless the user is already known to the bot by some other means.
    /// </summary>
    property UserId: Int64 read GetUserId;
    /// <summary>
    ///   Optional. First name of the user, if the name was requested by the bot
    /// </summary>
    property FirstName: string read GetFirstName;
    /// <summary>
    ///   Optional. Last name of the user, if the name was requested by the bot
    /// </summary>
    property LastName: string read GetLastName;
    /// <summary>
    ///   Optional. Username of the user, if the username was requested by the bot
    /// </summary>
    property Username: string read GetUsername;
    /// <summary>
    ///   Optional. Available sizes of the chat photo, if the photo was requested by the bot
    /// </summary>
    property Photo: TArray<ITgPhotoSize> read GetPhoto;
  end;

  /// <summary>
  ///   This object contains information about the users whose identifiers were shared with the bot
  ///   using a KeyboardButtonRequestUsers button.
  /// </summary>
  ITgUsersShared = interface(ITgJsonObject)
    ['{AEC99089-282B-5536-8928-0A8ACC7B9B0A}']
    function GetRequestId: Int64;
    function GetUsers: TArray<ITgSharedUser>;
    /// <summary>Identifier of the request</summary>
    property RequestId: Int64 read GetRequestId;
    /// <summary>Information about users shared with the bot</summary>
    property Users: TArray<ITgSharedUser> read GetUsers;
  end;

  /// <summary>
  ///   This object contains information about a chat that was shared with the bot using a
  ///   KeyboardButtonRequestChat button.
  /// </summary>
  ITgChatShared = interface(ITgJsonObject)
    ['{EFB4F618-71D0-5858-98CC-E030FCFDC588}']
    function GetRequestId: Int64;
    function GetChatId: Int64;
    function GetTitle: string;
    function GetUsername: string;
    function GetPhoto: TArray<ITgPhotoSize>;
    /// <summary>Identifier of the request</summary>
    property RequestId: Int64 read GetRequestId;
    /// <summary>
    ///   Identifier of the shared chat. This number may have more than 32 significant bits and some
    ///   programming languages may have difficulty/silent defects in interpreting it. But it has at
    ///   most 52 significant bits, so a 64-bit integer or double-precision float type are safe for
    ///   storing this identifier. The bot may not have access to the chat and could be unable to
    ///   use this identifier, unless the chat is already known to the bot by some other means.
    /// </summary>
    property ChatId: Int64 read GetChatId;
    /// <summary>
    ///   Optional. Title of the chat, if the title was requested by the bot
    /// </summary>
    property Title: string read GetTitle;
    /// <summary>
    ///   Optional. Username of the chat, if the username was requested by the bot and available
    /// </summary>
    property Username: string read GetUsername;
    /// <summary>
    ///   Optional. Available sizes of the chat photo, if the photo was requested by the bot
    /// </summary>
    property Photo: TArray<ITgPhotoSize> read GetPhoto;
  end;

  /// <summary>
  ///   This object represents a service message about a user allowing a bot to write messages after
  ///   adding it to the attachment menu, launching a Web App from a link, or accepting an explicit
  ///   request from a Web App sent by the method requestWriteAccess.
  /// </summary>
  ITgWriteAccessAllowed = interface(ITgJsonObject)
    ['{6BDCECC3-7BFD-5379-A988-AC9EF5E5E879}']
    function GetFromRequest: Boolean;
    function GetHasFromRequest: Boolean;
    function GetWebAppName: string;
    function GetFromAttachmentMenu: Boolean;
    function GetHasFromAttachmentMenu: Boolean;
    /// <summary>
    ///   Optional. True, if the access was granted after the user accepted an explicit request from
    ///   a Web App sent by the method requestWriteAccess
    /// </summary>
    property FromRequest: Boolean read GetFromRequest;
    /// <summary>Поле from_request присутствует.</summary>
    property HasFromRequest: Boolean read GetHasFromRequest;
    /// <summary>
    ///   Optional. Name of the Web App, if the access was granted when the Web App was launched
    ///   from a link
    /// </summary>
    property WebAppName: string read GetWebAppName;
    /// <summary>
    ///   Optional. True, if the access was granted when the bot was added to the attachment or side
    ///   menu
    /// </summary>
    property FromAttachmentMenu: Boolean read GetFromAttachmentMenu;
    /// <summary>Поле from_attachment_menu присутствует.</summary>
    property HasFromAttachmentMenu: Boolean read GetHasFromAttachmentMenu;
  end;

  /// <summary>
  ///   This object represents a service message about a video chat scheduled in the chat.
  /// </summary>
  ITgVideoChatScheduled = interface(ITgJsonObject)
    ['{75BDC9D5-070A-5143-8B6D-C51717ED01AE}']
    function GetStartDate: Int64;
    /// <summary>
    ///   Point in time (Unix timestamp) when the video chat is supposed to be started by a chat
    ///   administrator
    /// </summary>
    property StartDate: Int64 read GetStartDate;
  end;

  /// <summary>
  ///   This object represents a service message about a video chat started in the chat. Currently
  ///   holds no information.
  /// </summary>
  ITgVideoChatStarted = interface(ITgJsonObject)
    ['{FCE201A1-F6B1-5A49-BAA2-903FD1E00778}']
  end;

  /// <summary>
  ///   This object represents a service message about a video chat ended in the chat.
  /// </summary>
  ITgVideoChatEnded = interface(ITgJsonObject)
    ['{27FFCBF2-C0E0-5076-8461-CDFB6D3946F8}']
    function GetDuration: Integer;
    /// <summary>Video chat duration in seconds</summary>
    property Duration: Integer read GetDuration;
  end;

  /// <summary>
  ///   This object represents a service message about new members invited to a video chat.
  /// </summary>
  ITgVideoChatParticipantsInvited = interface(ITgJsonObject)
    ['{469AC4C0-26FF-574D-AB3A-D637D97ABF52}']
    function GetUsers: TArray<ITgUser>;
    /// <summary>New members that were invited to the video chat</summary>
    property Users: TArray<ITgUser> read GetUsers;
  end;

  /// <summary>
  ///   Describes a service message about a change in the price of paid messages within a chat.
  /// </summary>
  ITgPaidMessagePriceChanged = interface(ITgJsonObject)
    ['{9053AF61-BA69-579F-88F3-6BB174111480}']
    function GetPaidMessageStarCount: Integer;
    /// <summary>
    ///   The new number of Telegram Stars that must be paid by non-administrator users of the
    ///   supergroup chat for each sent message
    /// </summary>
    property PaidMessageStarCount: Integer read GetPaidMessageStarCount;
  end;

  /// <summary>
  ///   Describes a service message about a change in the price of direct messages sent to a channel
  ///   chat.
  /// </summary>
  ITgDirectMessagePriceChanged = interface(ITgJsonObject)
    ['{A6FD4D90-5F82-55CF-9131-5024D7B5B6D6}']
    function GetAreDirectMessagesEnabled: Boolean;
    function GetDirectMessageStarCount: Integer;
    function GetHasDirectMessageStarCount: Boolean;
    /// <summary>
    ///   True, if direct messages are enabled for the channel chat; False otherwise
    /// </summary>
    property AreDirectMessagesEnabled: Boolean read GetAreDirectMessagesEnabled;
    /// <summary>
    ///   Optional. The new number of Telegram Stars that must be paid by users for each direct
    ///   message sent to the channel. Does not apply to users who have been exempted by
    ///   administrators. Defaults to 0.
    /// </summary>
    property DirectMessageStarCount: Integer read GetDirectMessageStarCount;
    /// <summary>Поле direct_message_star_count присутствует.</summary>
    property HasDirectMessageStarCount: Boolean read GetHasDirectMessageStarCount;
  end;

  /// <summary>Describes a service message about the approval of a suggested post.</summary>
  ITgSuggestedPostApproved = interface(ITgJsonObject)
    ['{EAD27A61-A97D-5935-B780-FC8F8C3D1B22}']
    function GetSuggestedPostMessage: ITgMessage;
    function GetPrice: ITgSuggestedPostPrice;
    function GetSendDate: Int64;
    /// <summary>
    ///   Optional. Message containing the suggested post. Note that the Message object in this
    ///   field will not contain the reply_to_message field even if it itself is a reply.
    /// </summary>
    property SuggestedPostMessage: ITgMessage read GetSuggestedPostMessage;
    /// <summary>Optional. Amount paid for the post</summary>
    property Price: ITgSuggestedPostPrice read GetPrice;
    /// <summary>Date when the post will be published</summary>
    property SendDate: Int64 read GetSendDate;
  end;

  /// <summary>
  ///   Describes a service message about the failed approval of a suggested post. Currently, only
  ///   caused by insufficient user funds at the time of approval.
  /// </summary>
  ITgSuggestedPostApprovalFailed = interface(ITgJsonObject)
    ['{76417862-3374-55F3-94E3-883D48800E41}']
    function GetSuggestedPostMessage: ITgMessage;
    function GetPrice: ITgSuggestedPostPrice;
    /// <summary>
    ///   Optional. Message containing the suggested post whose approval has failed. Note that the
    ///   Message object in this field will not contain the reply_to_message field even if it itself
    ///   is a reply.
    /// </summary>
    property SuggestedPostMessage: ITgMessage read GetSuggestedPostMessage;
    /// <summary>Expected price of the post</summary>
    property Price: ITgSuggestedPostPrice read GetPrice;
  end;

  /// <summary>
  ///   Describes a service message about the rejection of a suggested post.
  /// </summary>
  ITgSuggestedPostDeclined = interface(ITgJsonObject)
    ['{22EFB48E-9C7F-52AE-AA67-7AF06F3B5D85}']
    function GetSuggestedPostMessage: ITgMessage;
    function GetComment: string;
    /// <summary>
    ///   Optional. Message containing the suggested post. Note that the Message object in this
    ///   field will not contain the reply_to_message field even if it itself is a reply.
    /// </summary>
    property SuggestedPostMessage: ITgMessage read GetSuggestedPostMessage;
    /// <summary>Optional. Comment with which the post was declined</summary>
    property Comment: string read GetComment;
  end;

  /// <summary>
  ///   Describes a service message about a successful payment for a suggested post.
  /// </summary>
  ITgSuggestedPostPaid = interface(ITgJsonObject)
    ['{6095A4B4-17EA-5843-BDD6-B1C3EC9502B0}']
    function GetSuggestedPostMessage: ITgMessage;
    function GetCurrency: string;
    function GetAmount: Integer;
    function GetHasAmount: Boolean;
    function GetStarAmount: ITgStarAmount;
    /// <summary>
    ///   Optional. Message containing the suggested post. Note that the Message object in this
    ///   field will not contain the reply_to_message field even if it itself is a reply.
    /// </summary>
    property SuggestedPostMessage: ITgMessage read GetSuggestedPostMessage;
    /// <summary>
    ///   Currency in which the payment was made. Currently, one of “XTR” for Telegram Stars or
    ///   “TON” for TON grams.
    /// </summary>
    property Currency: string read GetCurrency;
    /// <summary>
    ///   Optional. The amount of the currency that was received by the channel in nanograms; for
    ///   payments in TON grams only
    /// </summary>
    property Amount: Integer read GetAmount;
    /// <summary>Поле amount присутствует.</summary>
    property HasAmount: Boolean read GetHasAmount;
    /// <summary>
    ///   Optional. The amount of Telegram Stars that was received by the channel; for payments in
    ///   Telegram Stars only
    /// </summary>
    property StarAmount: ITgStarAmount read GetStarAmount;
  end;

  /// <summary>
  ///   Describes a service message about a payment refund for a suggested post.
  /// </summary>
  ITgSuggestedPostRefunded = interface(ITgJsonObject)
    ['{A6CF6E3A-2834-532D-AD74-8C9196F21818}']
    function GetSuggestedPostMessage: ITgMessage;
    function GetReason: string;
    /// <summary>
    ///   Optional. Message containing the suggested post. Note that the Message object in this
    ///   field will not contain the reply_to_message field even if it itself is a reply.
    /// </summary>
    property SuggestedPostMessage: ITgMessage read GetSuggestedPostMessage;
    /// <summary>
    ///   Reason for the refund. Currently, one of “post_deleted” if the post was deleted within 24
    ///   hours of being posted or removed from scheduled messages without being posted, or
    ///   “payment_refunded” if the payer refunded their payment.
    /// </summary>
    property Reason: string read GetReason;
  end;

  /// <summary>
  ///   This object represents a service message about the creation of a scheduled giveaway.
  /// </summary>
  ITgGiveawayCreated = interface(ITgJsonObject)
    ['{DA28ACCE-5931-571F-BC98-47562A365D12}']
    function GetPrizeStarCount: Integer;
    function GetHasPrizeStarCount: Boolean;
    /// <summary>
    ///   Optional. The number of Telegram Stars to be split between giveaway winners; for Telegram
    ///   Star giveaways only
    /// </summary>
    property PrizeStarCount: Integer read GetPrizeStarCount;
    /// <summary>Поле prize_star_count присутствует.</summary>
    property HasPrizeStarCount: Boolean read GetHasPrizeStarCount;
  end;

  /// <summary>This object represents a message about a scheduled giveaway.</summary>
  ITgGiveaway = interface(ITgJsonObject)
    ['{D8912650-7093-5190-AC73-E15F71A48F66}']
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
    /// <summary>
    ///   The list of chats which the user must join to participate in the giveaway
    /// </summary>
    property Chats: TArray<ITgChat> read GetChats;
    /// <summary>
    ///   Point in time (Unix timestamp) when winners of the giveaway will be selected
    /// </summary>
    property WinnersSelectionDate: Int64 read GetWinnersSelectionDate;
    /// <summary>
    ///   The number of users which are supposed to be selected as winners of the giveaway
    /// </summary>
    property WinnerCount: Integer read GetWinnerCount;
    /// <summary>
    ///   Optional. True, if only users who join the chats after the giveaway started should be
    ///   eligible to win
    /// </summary>
    property OnlyNewMembers: Boolean read GetOnlyNewMembers;
    /// <summary>
    ///   Optional. True, if the list of giveaway winners will be visible to everyone
    /// </summary>
    property HasPublicWinners: Boolean read GetHasPublicWinners;
    /// <summary>Optional. Description of additional giveaway prize</summary>
    property PrizeDescription: string read GetPrizeDescription;
    /// <summary>
    ///   Optional. A list of two-letter ISO 3166-1 alpha-2 country codes indicating the countries
    ///   from which eligible users for the giveaway must come. If empty, then all users can
    ///   participate in the giveaway. Users with a phone number that was bought on Fragment can
    ///   always participate in giveaways.
    /// </summary>
    property CountryCodes: TArray<string> read GetCountryCodes;
    /// <summary>
    ///   Optional. The number of Telegram Stars to be split between giveaway winners; for Telegram
    ///   Star giveaways only
    /// </summary>
    property PrizeStarCount: Integer read GetPrizeStarCount;
    /// <summary>Поле prize_star_count присутствует.</summary>
    property HasPrizeStarCount: Boolean read GetHasPrizeStarCount;
    /// <summary>
    ///   Optional. The number of months the Telegram Premium subscription won from the giveaway
    ///   will be active for; for Telegram Premium giveaways only
    /// </summary>
    property PremiumSubscriptionMonthCount: Integer read GetPremiumSubscriptionMonthCount;
    /// <summary>Поле premium_subscription_month_count присутствует.</summary>
    property HasPremiumSubscriptionMonthCount: Boolean read GetHasPremiumSubscriptionMonthCount;
  end;

  /// <summary>
  ///   This object represents a message about the completion of a giveaway with public winners.
  /// </summary>
  ITgGiveawayWinners = interface(ITgJsonObject)
    ['{1D88F85D-2E3F-5646-A4A2-98CDA4E3BEFF}']
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
    /// <summary>The chat that created the giveaway</summary>
    property Chat: ITgChat read GetChat;
    /// <summary>Identifier of the message with the giveaway in the chat</summary>
    property GiveawayMessageId: Int64 read GetGiveawayMessageId;
    /// <summary>
    ///   Point in time (Unix timestamp) when winners of the giveaway were selected
    /// </summary>
    property WinnersSelectionDate: Int64 read GetWinnersSelectionDate;
    /// <summary>Total number of winners in the giveaway</summary>
    property WinnerCount: Integer read GetWinnerCount;
    /// <summary>List of up to 100 winners of the giveaway</summary>
    property Winners: TArray<ITgUser> read GetWinners;
    /// <summary>
    ///   Optional. The number of other chats the user had to join in order to be eligible for the
    ///   giveaway
    /// </summary>
    property AdditionalChatCount: Integer read GetAdditionalChatCount;
    /// <summary>Поле additional_chat_count присутствует.</summary>
    property HasAdditionalChatCount: Boolean read GetHasAdditionalChatCount;
    /// <summary>
    ///   Optional. The number of Telegram Stars that were split between giveaway winners; for
    ///   Telegram Star giveaways only
    /// </summary>
    property PrizeStarCount: Integer read GetPrizeStarCount;
    /// <summary>Поле prize_star_count присутствует.</summary>
    property HasPrizeStarCount: Boolean read GetHasPrizeStarCount;
    /// <summary>
    ///   Optional. The number of months the Telegram Premium subscription won from the giveaway
    ///   will be active for; for Telegram Premium giveaways only
    /// </summary>
    property PremiumSubscriptionMonthCount: Integer read GetPremiumSubscriptionMonthCount;
    /// <summary>Поле premium_subscription_month_count присутствует.</summary>
    property HasPremiumSubscriptionMonthCount: Boolean read GetHasPremiumSubscriptionMonthCount;
    /// <summary>Optional. Number of undistributed prizes</summary>
    property UnclaimedPrizeCount: Integer read GetUnclaimedPrizeCount;
    /// <summary>Поле unclaimed_prize_count присутствует.</summary>
    property HasUnclaimedPrizeCount: Boolean read GetHasUnclaimedPrizeCount;
    /// <summary>
    ///   Optional. True, if only users who had joined the chats after the giveaway started were
    ///   eligible to win
    /// </summary>
    property OnlyNewMembers: Boolean read GetOnlyNewMembers;
    /// <summary>
    ///   Optional. True, if the giveaway was canceled because the payment for it was refunded
    /// </summary>
    property WasRefunded: Boolean read GetWasRefunded;
    /// <summary>Optional. Description of additional giveaway prize</summary>
    property PrizeDescription: string read GetPrizeDescription;
  end;

  /// <summary>
  ///   This object represents a service message about the completion of a giveaway without public
  ///   winners.
  /// </summary>
  ITgGiveawayCompleted = interface(ITgJsonObject)
    ['{A5F10F7D-DD4A-5650-801E-8228467A1582}']
    function GetWinnerCount: Integer;
    function GetUnclaimedPrizeCount: Integer;
    function GetHasUnclaimedPrizeCount: Boolean;
    function GetGiveawayMessage: ITgMessage;
    function GetIsStarGiveaway: Boolean;
    /// <summary>Number of winners in the giveaway</summary>
    property WinnerCount: Integer read GetWinnerCount;
    /// <summary>Optional. Number of undistributed prizes</summary>
    property UnclaimedPrizeCount: Integer read GetUnclaimedPrizeCount;
    /// <summary>Поле unclaimed_prize_count присутствует.</summary>
    property HasUnclaimedPrizeCount: Boolean read GetHasUnclaimedPrizeCount;
    /// <summary>
    ///   Optional. Message with the giveaway that was completed, if it wasn't deleted
    /// </summary>
    property GiveawayMessage: ITgMessage read GetGiveawayMessage;
    /// <summary>
    ///   Optional. True, if the giveaway is a Telegram Star giveaway. Otherwise, currently, the
    ///   giveaway is a Telegram Premium giveaway.
    /// </summary>
    property IsStarGiveaway: Boolean read GetIsStarGiveaway;
  end;

  /// <summary>Describes the options used for link preview generation.</summary>
  ITgLinkPreviewOptions = interface(ITgJsonObject)
    ['{0223AF1C-FB77-5B12-B297-5408E8293714}']
    function GetIsDisabled: Boolean;
    function GetHasIsDisabled: Boolean;
    function GetUrl: string;
    function GetPreferSmallMedia: Boolean;
    function GetHasPreferSmallMedia: Boolean;
    function GetPreferLargeMedia: Boolean;
    function GetHasPreferLargeMedia: Boolean;
    function GetShowAboveText: Boolean;
    function GetHasShowAboveText: Boolean;
    /// <summary>
    ///   Задаёт is_disabled: Optional. True, if the link preview is disabled. Значение копируется в
    ///   момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithIsDisabled(AValue: Boolean): ITgLinkPreviewOptions;
    /// <summary>
    ///   Задаёт url: Optional. URL to use for the link preview. If empty, then the first URL found
    ///   in the message text will be used. Значение копируется в момент вызова: последующие
    ///   изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithUrl(const AValue: string): ITgLinkPreviewOptions;
    /// <summary>
    ///   Задаёт prefer_small_media: Optional. True, if the media in the link preview is supposed to
    ///   be shrunk; ignored if the URL isn't explicitly specified or media size change isn't
    ///   supported for the preview. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithPreferSmallMedia(AValue: Boolean): ITgLinkPreviewOptions;
    /// <summary>
    ///   Задаёт prefer_large_media: Optional. True, if the media in the link preview is supposed to
    ///   be enlarged; ignored if the URL isn't explicitly specified or media size change isn't
    ///   supported for the preview. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithPreferLargeMedia(AValue: Boolean): ITgLinkPreviewOptions;
    /// <summary>
    ///   Задаёт show_above_text: Optional. True, if the link preview must be shown above the
    ///   message text; otherwise, the link preview will be shown below the message text. Значение
    ///   копируется в момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithShowAboveText(AValue: Boolean): ITgLinkPreviewOptions;
    /// <summary>Optional. True, if the link preview is disabled</summary>
    property IsDisabled: Boolean read GetIsDisabled;
    /// <summary>Поле is_disabled присутствует.</summary>
    property HasIsDisabled: Boolean read GetHasIsDisabled;
    /// <summary>
    ///   Optional. URL to use for the link preview. If empty, then the first URL found in the
    ///   message text will be used.
    /// </summary>
    property Url: string read GetUrl;
    /// <summary>
    ///   Optional. True, if the media in the link preview is supposed to be shrunk; ignored if the
    ///   URL isn't explicitly specified or media size change isn't supported for the preview
    /// </summary>
    property PreferSmallMedia: Boolean read GetPreferSmallMedia;
    /// <summary>Поле prefer_small_media присутствует.</summary>
    property HasPreferSmallMedia: Boolean read GetHasPreferSmallMedia;
    /// <summary>
    ///   Optional. True, if the media in the link preview is supposed to be enlarged; ignored if
    ///   the URL isn't explicitly specified or media size change isn't supported for the preview
    /// </summary>
    property PreferLargeMedia: Boolean read GetPreferLargeMedia;
    /// <summary>Поле prefer_large_media присутствует.</summary>
    property HasPreferLargeMedia: Boolean read GetHasPreferLargeMedia;
    /// <summary>
    ///   Optional. True, if the link preview must be shown above the message text; otherwise, the
    ///   link preview will be shown below the message text
    /// </summary>
    property ShowAboveText: Boolean read GetShowAboveText;
    /// <summary>Поле show_above_text присутствует.</summary>
    property HasShowAboveText: Boolean read GetHasShowAboveText;
  end;

  /// <summary>Describes the price of a suggested post.</summary>
  ITgSuggestedPostPrice = interface(ITgJsonObject)
    ['{A6AFC2EF-A81E-533D-9064-10D47630012A}']
    function GetCurrency: string;
    function GetAmount: Integer;
    /// <summary>
    ///   Задаёт currency: Currency in which the post will be paid. Currently, must be one of “XTR”
    ///   for Telegram Stars or “TON” for TON grams. Значение копируется в момент вызова:
    ///   последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithCurrency(const AValue: string): ITgSuggestedPostPrice;
    /// <summary>
    ///   Задаёт amount: The amount of the currency that will be paid for the post in the smallest
    ///   units of the currency, i.e. Telegram Stars or nanograms. Currently, price in Telegram
    ///   Stars must be between 5 and 100000, and price in nanograms must be between 10000000 and
    ///   10000000000000. Значение копируется в момент вызова: последующие изменения переданного
    ///   объекта на этот не влияют.
    /// </summary>
    function WithAmount(AValue: Integer): ITgSuggestedPostPrice;
    /// <summary>
    ///   Currency in which the post will be paid. Currently, must be one of “XTR” for Telegram
    ///   Stars or “TON” for TON grams.
    /// </summary>
    property Currency: string read GetCurrency;
    /// <summary>
    ///   The amount of the currency that will be paid for the post in the smallest units of the
    ///   currency, i.e. Telegram Stars or nanograms. Currently, price in Telegram Stars must be
    ///   between 5 and 100000, and price in nanograms must be between 10000000 and 10000000000000.
    /// </summary>
    property Amount: Integer read GetAmount;
  end;

  /// <summary>Contains information about a suggested post.</summary>
  ITgSuggestedPostInfo = interface(ITgJsonObject)
    ['{E4C68ABD-8C83-582B-B649-B17BCCFBA7AB}']
    function GetState: string;
    function GetPrice: ITgSuggestedPostPrice;
    function GetSendDate: Int64;
    function GetHasSendDate: Boolean;
    /// <summary>
    ///   State of the suggested post. Currently, it can be one of “pending”, “approved”,
    ///   “declined”.
    /// </summary>
    property State: string read GetState;
    /// <summary>
    ///   Optional. Proposed price of the post. If the field is omitted, then the post is unpaid.
    /// </summary>
    property Price: ITgSuggestedPostPrice read GetPrice;
    /// <summary>
    ///   Optional. Proposed send date of the post. If the field is omitted, then the post can be
    ///   published at any time within 30 days at the sole discretion of the user or administrator
    ///   who approves it.
    /// </summary>
    property SendDate: Int64 read GetSendDate;
    /// <summary>Поле send_date присутствует.</summary>
    property HasSendDate: Boolean read GetHasSendDate;
  end;

  /// <summary>Contains parameters of a post that is being suggested by the bot.</summary>
  ITgSuggestedPostParameters = interface(ITgOutObject)
    ['{1570074B-E0FB-5A4F-A24B-4F3F10AFC217}']
    /// <summary>
    ///   Задаёт price: Optional. Proposed price for the post. If the field is omitted, then the
    ///   post is unpaid.
    /// </summary>
    function WithPrice(const AValue: ITgSuggestedPostPrice): ITgSuggestedPostParameters;
    /// <summary>
    ///   Задаёт send_date: Optional. Proposed send date of the post. If specified, then the date
    ///   must be between 300 second and 2678400 seconds (30 days) in the future. If the field is
    ///   omitted, then the post can be published at any time within 30 days at the sole discretion
    ///   of the user who approves it.
    /// </summary>
    function WithSendDate(AValue: Int64): ITgSuggestedPostParameters;
  end;

  /// <summary>Describes a topic of a direct messages chat.</summary>
  ITgDirectMessagesTopic = interface(ITgJsonObject)
    ['{B1DED2D7-DB9A-5E14-BAA2-F0FBBC944887}']
    function GetTopicId: Int64;
    function GetUser: ITgUser;
    /// <summary>
    ///   Unique identifier of the topic. This number may have more than 32 significant bits and
    ///   some programming languages may have difficulty/silent defects in interpreting it. But it
    ///   has at most 52 significant bits, so a 64-bit integer or double-precision float type are
    ///   safe for storing this identifier.
    /// </summary>
    property TopicId: Int64 read GetTopicId;
    /// <summary>
    ///   Optional. Information about the user that created the topic. Currently, it is always
    ///   present.
    /// </summary>
    property User: ITgUser read GetUser;
  end;

  /// <summary>This object represent a user's profile pictures.</summary>
  ITgUserProfilePhotos = interface(ITgJsonObject)
    ['{9E5143F8-0D5B-52C2-8DB9-9DB248987188}']
    function GetTotalCount: Integer;
    function GetPhotos: TArray<TArray<ITgPhotoSize>>;
    /// <summary>Total number of profile pictures the target user has</summary>
    property TotalCount: Integer read GetTotalCount;
    /// <summary>Requested profile pictures (in up to 4 sizes each)</summary>
    property Photos: TArray<TArray<ITgPhotoSize>> read GetPhotos;
  end;

  /// <summary>This object represents the audios displayed on a user's profile.</summary>
  ITgUserProfileAudios = interface(ITgJsonObject)
    ['{4D727725-2FFB-56C3-AC5E-84150D76C872}']
    function GetTotalCount: Integer;
    function GetAudios: TArray<ITgAudio>;
    /// <summary>Total number of profile audios for the target user</summary>
    property TotalCount: Integer read GetTotalCount;
    /// <summary>Requested profile audios</summary>
    property Audios: TArray<ITgAudio> read GetAudios;
  end;

  /// <summary>
  ///   This object represents a file ready to be downloaded. The file can be downloaded via the
  ///   link https://api.telegram.org/file/bot&lt;token&gt;/&lt;file_path&gt;. It is guaranteed that
  ///   the link will be valid for at least 1 hour. When the link expires, a new one can be
  ///   requested by calling getFile. The maximum file size to download is 20 MB
  /// </summary>
  ITgFile = interface(ITgJsonObject)
    ['{7781A9B1-8282-5296-98C6-E42D53AD7BD9}']
    function GetFileId: string;
    function GetFileUniqueId: string;
    function GetFileSize: Int64;
    function GetHasFileSize: Boolean;
    function GetFilePath: string;
    /// <summary>
    ///   Identifier for this file, which can be used to download or reuse the file
    /// </summary>
    property FileId: string read GetFileId;
    /// <summary>
    ///   Unique identifier for this file, which is supposed to be the same over time and for
    ///   different bots. Can't be used to download or reuse the file.
    /// </summary>
    property FileUniqueId: string read GetFileUniqueId;
    /// <summary>
    ///   Optional. File size in bytes. It can be bigger than 2^31 and some programming languages
    ///   may have difficulty/silent defects in interpreting it. But it has at most 52 significant
    ///   bits, so a signed 64-bit integer or double-precision float type are safe for storing this
    ///   value.
    /// </summary>
    property FileSize: Int64 read GetFileSize;
    /// <summary>Поле file_size присутствует.</summary>
    property HasFileSize: Boolean read GetHasFileSize;
    /// <summary>
    ///   Optional. File path. Use https://api.telegram.org/file/bot&lt;token&gt;/&lt;file_path&gt;
    ///   to get the file.
    /// </summary>
    property FilePath: string read GetFilePath;
  end;

  /// <summary>Describes a Web App.</summary>
  ITgWebAppInfo = interface(ITgJsonObject)
    ['{DEA79CEF-CB3B-5DB6-884F-945983128D71}']
    function GetUrl: string;
    /// <summary>
    ///   Задаёт url: An HTTPS URL of a Web App to be opened with additional data as specified in
    ///   Initializing Web Apps. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithUrl(const AValue: string): ITgWebAppInfo;
    /// <summary>
    ///   An HTTPS URL of a Web App to be opened with additional data as specified in Initializing
    ///   Web Apps
    /// </summary>
    property Url: string read GetUrl;
  end;

  /// <summary>
  ///   This object represents a custom keyboard with reply options (see Introduction to bots for
  ///   details and examples). Not supported in channels and for messages sent on behalf of a
  ///   business account.
  /// </summary>
  ITgReplyKeyboardMarkup = interface(ITgOutObject)
    ['{4A709219-94F2-5624-9300-AE4B7A71E649}']
    /// <summary>
    ///   Задаёт keyboard: Array of button rows, each represented by an Array of KeyboardButton
    ///   objects
    /// </summary>
    function WithKeyboard(const AValue: array of TArray<ITgKeyboardButton>): ITgReplyKeyboardMarkup;
    /// <summary>Добавляет строку в keyboard.</summary>
    function WithKeyboardRow(const ARow: array of ITgKeyboardButton): ITgReplyKeyboardMarkup;
    /// <summary>
    ///   Задаёт is_persistent: Optional. Requests clients to always show the keyboard when the
    ///   regular keyboard is hidden. Defaults to False, in which case the custom keyboard can be
    ///   hidden and opened with a keyboard icon.
    /// </summary>
    function WithIsPersistent(AValue: Boolean): ITgReplyKeyboardMarkup;
    /// <summary>
    ///   Задаёт resize_keyboard: Optional. Requests clients to resize the keyboard vertically for
    ///   optimal fit (e.g., make the keyboard smaller if there are just two rows of buttons).
    ///   Defaults to False, in which case the custom keyboard is always of the same height as the
    ///   app's standard keyboard.
    /// </summary>
    function WithResizeKeyboard(AValue: Boolean): ITgReplyKeyboardMarkup;
    /// <summary>
    ///   Задаёт one_time_keyboard: Optional. Requests clients to hide the keyboard as soon as it's
    ///   been used. The keyboard will still be available, but clients will automatically display
    ///   the usual letter-keyboard in the chat - the user can press a special button in the input
    ///   field to see the custom keyboard again. Defaults to False.
    /// </summary>
    function WithOneTimeKeyboard(AValue: Boolean): ITgReplyKeyboardMarkup;
    /// <summary>
    ///   Задаёт input_field_placeholder: Optional. The placeholder to be shown in the input field
    ///   when the keyboard is active; 1-64 characters
    /// </summary>
    function WithInputFieldPlaceholder(const AValue: string): ITgReplyKeyboardMarkup;
    /// <summary>
    ///   Задаёт selective: Optional. Use this parameter if you want to show the keyboard to
    ///   specific users only. Targets: 1) users that are @mentioned in the text of the Message
    ///   object; 2) if the bot's message is a reply to a message in the same chat and forum topic,
    ///   sender of the original message.
    /// </summary>
    function WithSelective(AValue: Boolean): ITgReplyKeyboardMarkup;
    /// <summary>
    ///   Задаёт force_reply: Optional. Pass True if the reply interface must be shown to the user,
    ///   as if they had manually selected the bot's message and tapped 'Reply'
    /// </summary>
    function WithForceReply(AValue: Boolean): ITgReplyKeyboardMarkup;
  end;

  /// <summary>
  ///   This object represents one button of the reply keyboard. At most one of the fields other
  ///   than text, icon_custom_emoji_id, and style must be used to specify the type of the button.
  ///   For simple text buttons, String can be used instead of this object to specify the button
  ///   text.
  /// </summary>
  ITgKeyboardButton = interface(ITgOutObject)
    ['{25971DC4-68B8-5A55-B2CF-5E929906F48A}']
    /// <summary>
    ///   Задаёт text: Text of the button. If none of the fields other than text,
    ///   icon_custom_emoji_id, and style are used, it will be sent as a message when the button is
    ///   pressed.
    /// </summary>
    function WithText(const AValue: string): ITgKeyboardButton;
    /// <summary>
    ///   Задаёт icon_custom_emoji_id: Optional. Unique identifier of the custom emoji shown before
    ///   the text of the button. Can only be used by bots that purchased additional usernames on
    ///   Fragment or in the messages directly sent by the bot to private, group and supergroup
    ///   chats if the owner of the bot has a Telegram Premium subscription.
    /// </summary>
    function WithIconCustomEmojiId(const AValue: string): ITgKeyboardButton;
    /// <summary>
    ///   Задаёт style: Optional. Style of the button. Must be one of “danger” (red), “success”
    ///   (green) or “primary” (blue). If omitted, then an app-specific style is used.
    /// </summary>
    function WithStyle(const AValue: string): ITgKeyboardButton;
    /// <summary>
    ///   Задаёт request_users: Optional. If specified, pressing the button will open a list of
    ///   suitable users. Identifiers of selected users will be sent to the bot in a “users_shared”
    ///   service message. Available in private chats only.
    /// </summary>
    function WithRequestUsers(const AValue: ITgKeyboardButtonRequestUsers): ITgKeyboardButton;
    /// <summary>
    ///   Задаёт request_chat: Optional. If specified, pressing the button will open a list of
    ///   suitable chats. Tapping on a chat will send its identifier to the bot in a “chat_shared”
    ///   service message. Available in private chats only.
    /// </summary>
    function WithRequestChat(const AValue: ITgKeyboardButtonRequestChat): ITgKeyboardButton;
    /// <summary>
    ///   Задаёт request_managed_bot: Optional. If specified, pressing the button will ask the user
    ///   to create and share a bot that will be managed by the current bot. Available for bots that
    ///   enabled management of other bots in the @BotFather Mini App. Available in private chats
    ///   only.
    /// </summary>
    function WithRequestManagedBot(const AValue: ITgKeyboardButtonRequestManagedBot): ITgKeyboardButton;
    /// <summary>
    ///   Задаёт request_contact: Optional. If True, the user's phone number will be sent as a
    ///   contact when the button is pressed. Available in private chats only.
    /// </summary>
    function WithRequestContact(AValue: Boolean): ITgKeyboardButton;
    /// <summary>
    ///   Задаёт request_location: Optional. If True, the user's current location will be sent when
    ///   the button is pressed. Available in private chats only.
    /// </summary>
    function WithRequestLocation(AValue: Boolean): ITgKeyboardButton;
    /// <summary>
    ///   Задаёт request_poll: Optional. If specified, the user will be asked to create a poll and
    ///   send it to the bot when the button is pressed. Available in private chats only.
    /// </summary>
    function WithRequestPoll(const AValue: ITgKeyboardButtonPollType): ITgKeyboardButton;
    /// <summary>
    ///   Задаёт web_app: Optional. If specified, the described Web App will be launched when the
    ///   button is pressed. The Web App will be able to send a “web_app_data” service message.
    ///   Available in private chats only.
    /// </summary>
    function WithWebApp(const AValue: ITgWebAppInfo): ITgKeyboardButton;
  end;

  /// <summary>
  ///   This object defines the criteria used to request suitable users. Information about the
  ///   selected users will be shared with the bot when the corresponding button is pressed. More
  ///   about requesting users »
  /// </summary>
  ITgKeyboardButtonRequestUsers = interface(ITgOutObject)
    ['{38E2A4B7-5960-51B3-A6C4-61C76808A3A4}']
    /// <summary>
    ///   Задаёт request_id: Signed 32-bit identifier of the request that will be received back in
    ///   the UsersShared object. Must be unique within the message.
    /// </summary>
    function WithRequestId(AValue: Int64): ITgKeyboardButtonRequestUsers;
    /// <summary>
    ///   Задаёт user_is_bot: Optional. Pass True to request bots, pass False to request regular
    ///   users. If not specified, no additional restrictions are applied.
    /// </summary>
    function WithUserIsBot(AValue: Boolean): ITgKeyboardButtonRequestUsers;
    /// <summary>
    ///   Задаёт user_is_premium: Optional. Pass True to request premium users, pass False to
    ///   request non-premium users. If not specified, no additional restrictions are applied.
    /// </summary>
    function WithUserIsPremium(AValue: Boolean): ITgKeyboardButtonRequestUsers;
    /// <summary>
    ///   Задаёт max_quantity: Optional. The maximum number of users to be selected; 1-10. Defaults
    ///   to 1.
    /// </summary>
    function WithMaxQuantity(AValue: Integer): ITgKeyboardButtonRequestUsers;
    /// <summary>
    ///   Задаёт request_name: Optional. Pass True to request the users' first and last names
    /// </summary>
    function WithRequestName(AValue: Boolean): ITgKeyboardButtonRequestUsers;
    /// <summary>
    ///   Задаёт request_username: Optional. Pass True to request the users' usernames
    /// </summary>
    function WithRequestUsername(AValue: Boolean): ITgKeyboardButtonRequestUsers;
    /// <summary>
    ///   Задаёт request_photo: Optional. Pass True to request the users' photos
    /// </summary>
    function WithRequestPhoto(AValue: Boolean): ITgKeyboardButtonRequestUsers;
  end;

  /// <summary>
  ///   This object defines the criteria used to request a suitable chat. Information about the
  ///   selected chat will be shared with the bot when the corresponding button is pressed. The bot
  ///   will be granted requested rights in the chat if appropriate. More about requesting chats ».
  /// </summary>
  ITgKeyboardButtonRequestChat = interface(ITgOutObject)
    ['{63C16A82-AB61-5A73-AA72-4146D4D4A80D}']
    /// <summary>
    ///   Задаёт request_id: Signed 32-bit identifier of the request, which will be received back in
    ///   the ChatShared object. Must be unique within the message.
    /// </summary>
    function WithRequestId(AValue: Int64): ITgKeyboardButtonRequestChat;
    /// <summary>
    ///   Задаёт chat_is_channel: Pass True to request a channel chat, pass False to request a group
    ///   or a supergroup chat
    /// </summary>
    function WithChatIsChannel(AValue: Boolean): ITgKeyboardButtonRequestChat;
    /// <summary>
    ///   Задаёт chat_is_forum: Optional. Pass True to request a forum supergroup, pass False to
    ///   request a non-forum chat. If not specified, no additional restrictions are applied.
    /// </summary>
    function WithChatIsForum(AValue: Boolean): ITgKeyboardButtonRequestChat;
    /// <summary>
    ///   Задаёт chat_has_username: Optional. Pass True to request a supergroup or a channel with a
    ///   username, pass False to request a chat without a username. If not specified, no additional
    ///   restrictions are applied.
    /// </summary>
    function WithChatHasUsername(AValue: Boolean): ITgKeyboardButtonRequestChat;
    /// <summary>
    ///   Задаёт chat_is_created: Optional. Pass True to request a chat owned by the user.
    ///   Otherwise, no additional restrictions are applied.
    /// </summary>
    function WithChatIsCreated(AValue: Boolean): ITgKeyboardButtonRequestChat;
    /// <summary>
    ///   Задаёт user_administrator_rights: Optional. A JSON-serialized object listing the required
    ///   administrator rights of the user in the chat. The rights must be a superset of
    ///   bot_administrator_rights. If not specified, no additional restrictions are applied.
    /// </summary>
    function WithUserAdministratorRights(const AValue: ITgChatAdministratorRights): ITgKeyboardButtonRequestChat;
    /// <summary>
    ///   Задаёт bot_administrator_rights: Optional. A JSON-serialized object listing the required
    ///   administrator rights of the bot in the chat. The rights must be a subset of
    ///   user_administrator_rights. If not specified, no additional restrictions are applied.
    /// </summary>
    function WithBotAdministratorRights(const AValue: ITgChatAdministratorRights): ITgKeyboardButtonRequestChat;
    /// <summary>
    ///   Задаёт bot_is_member: Optional. Pass True to request a chat with the bot as a member.
    ///   Otherwise, no additional restrictions are applied.
    /// </summary>
    function WithBotIsMember(AValue: Boolean): ITgKeyboardButtonRequestChat;
    /// <summary>
    ///   Задаёт request_title: Optional. Pass True to request the chat's title
    /// </summary>
    function WithRequestTitle(AValue: Boolean): ITgKeyboardButtonRequestChat;
    /// <summary>
    ///   Задаёт request_username: Optional. Pass True to request the chat's username
    /// </summary>
    function WithRequestUsername(AValue: Boolean): ITgKeyboardButtonRequestChat;
    /// <summary>
    ///   Задаёт request_photo: Optional. Pass True to request the chat's photo
    /// </summary>
    function WithRequestPhoto(AValue: Boolean): ITgKeyboardButtonRequestChat;
  end;

  /// <summary>
  ///   This object defines the parameters for the creation of a managed bot. Information about the
  ///   created bot will be shared with the bot using the update managed_bot and a Message with the
  ///   field managed_bot_created.
  /// </summary>
  ITgKeyboardButtonRequestManagedBot = interface(ITgOutObject)
    ['{E67069F2-3BF8-5683-9223-CD19AFAD4BEA}']
    /// <summary>
    ///   Задаёт request_id: Signed 32-bit identifier of the request. Must be unique within the
    ///   message.
    /// </summary>
    function WithRequestId(AValue: Int64): ITgKeyboardButtonRequestManagedBot;
    /// <summary>Задаёт suggested_name: Optional. Suggested name for the bot</summary>
    function WithSuggestedName(const AValue: string): ITgKeyboardButtonRequestManagedBot;
    /// <summary>
    ///   Задаёт suggested_username: Optional. Suggested username for the bot
    /// </summary>
    function WithSuggestedUsername(const AValue: string): ITgKeyboardButtonRequestManagedBot;
  end;

  /// <summary>
  ///   This object represents type of a poll, which is allowed to be created and sent when the
  ///   corresponding button is pressed.
  /// </summary>
  ITgKeyboardButtonPollType = interface(ITgOutObject)
    ['{8B30EE4C-17D4-59D0-B2F4-07A4E57C6626}']
    /// <summary>
    ///   Задаёт type: Optional. If quiz is passed, the user will be allowed to create only polls in
    ///   the quiz mode. If regular is passed, only regular polls will be allowed. Otherwise, the
    ///   user will be allowed to create a poll of any type.
    /// </summary>
    function WithKeyboardButtonPollTypeType(const AValue: string): ITgKeyboardButtonPollType;
  end;

  /// <summary>
  ///   Upon receiving a message with this object, Telegram clients will remove the current custom
  ///   keyboard and display the default letter-keyboard. By default, custom keyboards are displayed
  ///   until a new keyboard is sent by a bot. An exception is made for one-time keyboards that are
  ///   hidden immediately after the user presses a button (see ReplyKeyboardMarkup). Not supported
  ///   in channels and for messages sent on behalf of a business account.
  /// </summary>
  ITgReplyKeyboardRemove = interface(ITgOutObject)
    ['{87C852D3-69CE-5013-8AC0-BF170B17D869}']
    /// <summary>
    ///   Задаёт selective: Optional. Use this parameter if you want to remove the keyboard for
    ///   specific users only. Targets: 1) users that are @mentioned in the text of the Message
    ///   object; 2) if the bot's message is a reply to a message in the same chat and forum topic,
    ///   sender of the original message.
    /// </summary>
    function WithSelective(AValue: Boolean): ITgReplyKeyboardRemove;
  end;

  /// <summary>
  ///   This object represents an inline keyboard that appears right next to the message it belongs
  ///   to.
  /// </summary>
  ITgInlineKeyboardMarkup = interface(ITgJsonObject)
    ['{E662936C-CF19-5689-AFB6-4E7960F208B4}']
    function GetInlineKeyboard: TArray<TArray<ITgInlineKeyboardButton>>;
    function GetForceReply: Boolean;
    function GetHasForceReply: Boolean;
    /// <summary>
    ///   Задаёт inline_keyboard: Array of button rows, each represented by an Array of
    ///   InlineKeyboardButton objects. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithInlineKeyboard(const AValue: array of TArray<ITgInlineKeyboardButton>): ITgInlineKeyboardMarkup;
    /// <summary>
    ///   Добавляет строку в inline_keyboard. Значение копируется в момент вызова: последующие
    ///   изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithInlineKeyboardRow(const ARow: array of ITgInlineKeyboardButton): ITgInlineKeyboardMarkup;
    /// <summary>
    ///   Задаёт force_reply: Optional. Pass True if the reply interface must be shown to the user,
    ///   as if they had manually selected the bot's message and tapped 'Reply'. The value of the
    ///   field can't be changed when the inline keyboard is edited. Значение копируется в момент
    ///   вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithForceReply(AValue: Boolean): ITgInlineKeyboardMarkup;
    /// <summary>
    ///   Array of button rows, each represented by an Array of InlineKeyboardButton objects
    /// </summary>
    property InlineKeyboard: TArray<TArray<ITgInlineKeyboardButton>> read GetInlineKeyboard;
    /// <summary>
    ///   Optional. Pass True if the reply interface must be shown to the user, as if they had
    ///   manually selected the bot's message and tapped 'Reply'. The value of the field can't be
    ///   changed when the inline keyboard is edited.
    /// </summary>
    property ForceReply: Boolean read GetForceReply;
    /// <summary>Поле force_reply присутствует.</summary>
    property HasForceReply: Boolean read GetHasForceReply;
  end;

  /// <summary>
  ///   This object represents one button of an inline keyboard. Exactly one of the fields other
  ///   than text, icon_custom_emoji_id, and style must be used to specify the type of the button.
  /// </summary>
  ITgInlineKeyboardButton = interface(ITgJsonObject)
    ['{F2FC84A3-BC8B-5739-9EF6-4C7590B01E34}']
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
    /// <summary>
    ///   Задаёт text: Label text on the button. Значение копируется в момент вызова: последующие
    ///   изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithText(const AValue: string): ITgInlineKeyboardButton;
    /// <summary>
    ///   Задаёт icon_custom_emoji_id: Optional. Unique identifier of the custom emoji shown before
    ///   the text of the button. Can only be used by bots that purchased additional usernames on
    ///   Fragment or in the messages directly sent by the bot to private, group and supergroup
    ///   chats if the owner of the bot has a Telegram Premium subscription. Значение копируется в
    ///   момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithIconCustomEmojiId(const AValue: string): ITgInlineKeyboardButton;
    /// <summary>
    ///   Задаёт style: Optional. Style of the button. Must be one of “danger” (red), “success”
    ///   (green) or “primary” (blue). If omitted, then an app-specific style is used. Значение
    ///   копируется в момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithStyle(const AValue: string): ITgInlineKeyboardButton;
    /// <summary>
    ///   Задаёт url: Optional. HTTP or tg:// URL to be opened when the button is pressed. Links
    ///   tg://user?id=&lt;user_id&gt; can be used to mention a user by their identifier without
    ///   using a username, if this is allowed by their privacy settings. Значение копируется в
    ///   момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithUrl(const AValue: string): ITgInlineKeyboardButton;
    /// <summary>
    ///   Задаёт callback_data: Optional. Data to be sent in a callback query to the bot when the
    ///   button is pressed, 1-64 bytes. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithCallbackData(const AValue: string): ITgInlineKeyboardButton;
    /// <summary>
    ///   Задаёт web_app: Optional. Description of the Web App that will be launched when the user
    ///   presses the button. The Web App will be able to send an arbitrary message on behalf of the
    ///   user using the method answerWebAppQuery. Available only in private chats between a user
    ///   and the bot. Not supported for messages sent on behalf of a business account. Значение
    ///   копируется в момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithWebApp(const AValue: ITgWebAppInfo): ITgInlineKeyboardButton;
    /// <summary>
    ///   Задаёт login_url: Optional. An HTTPS URL used to automatically authorize the user. Can be
    ///   used as a replacement for the Telegram Login Widget. Not supported for ephemeral messages.
    ///   Значение копируется в момент вызова: последующие изменения переданного объекта на этот не
    ///   влияют.
    /// </summary>
    function WithLoginUrl(const AValue: ITgLoginUrl): ITgInlineKeyboardButton;
    /// <summary>
    ///   Задаёт switch_inline_query: Optional. If set, pressing the button will prompt the user to
    ///   select one of their chats, open that chat and insert the bot's username and the specified
    ///   inline query in the input field. May be empty, in which case just the bot's username will
    ///   be inserted. Not supported for messages sent in channel direct messages chats and on
    ///   behalf of a business account. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithSwitchInlineQuery(const AValue: string): ITgInlineKeyboardButton;
    /// <summary>
    ///   Задаёт switch_inline_query_current_chat: Optional. If set, pressing the button will insert
    ///   the bot's username and the specified inline query in the current chat's input field. May
    ///   be empty, in which case only the bot's username will be inserted. Значение копируется в
    ///   момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithSwitchInlineQueryCurrentChat(const AValue: string): ITgInlineKeyboardButton;
    /// <summary>
    ///   Задаёт switch_inline_query_chosen_chat: Optional. If set, pressing the button will prompt
    ///   the user to select one of their chats of the specified type, open that chat and insert the
    ///   bot's username and the specified inline query in the input field. Not supported for
    ///   messages sent in channel direct messages chats and on behalf of a business account.
    ///   Значение копируется в момент вызова: последующие изменения переданного объекта на этот не
    ///   влияют.
    /// </summary>
    function WithSwitchInlineQueryChosenChat(const AValue: ITgSwitchInlineQueryChosenChat): ITgInlineKeyboardButton;
    /// <summary>
    ///   Задаёт copy_text: Optional. Description of the button that copies the specified text to
    ///   the clipboard. Значение копируется в момент вызова: последующие изменения переданного
    ///   объекта на этот не влияют.
    /// </summary>
    function WithCopyText(const AValue: ITgCopyTextButton): ITgInlineKeyboardButton;
    /// <summary>
    ///   Задаёт callback_game: Optional. Description of the game that will be launched when the
    ///   user presses the button. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithCallbackGame(const AValue: ITgCallbackGame): ITgInlineKeyboardButton;
    /// <summary>
    ///   Задаёт pay: Optional. Specify True, to send a Pay button. Substrings “⭐” and “XTR” in the
    ///   buttons's text will be replaced with a Telegram Star icon. Значение копируется в момент
    ///   вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithPay(AValue: Boolean): ITgInlineKeyboardButton;
    /// <summary>
    ///   Задаёт disabled: Optional. If set, then the button is disabled and does nothing. Значение
    ///   копируется в момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithDisabled(const AValue: ITgDisabledButton): ITgInlineKeyboardButton;
    /// <summary>Label text on the button</summary>
    property Text: string read GetText;
    /// <summary>
    ///   Optional. Unique identifier of the custom emoji shown before the text of the button. Can
    ///   only be used by bots that purchased additional usernames on Fragment or in the messages
    ///   directly sent by the bot to private, group and supergroup chats if the owner of the bot
    ///   has a Telegram Premium subscription.
    /// </summary>
    property IconCustomEmojiId: string read GetIconCustomEmojiId;
    /// <summary>
    ///   Optional. Style of the button. Must be one of “danger” (red), “success” (green) or
    ///   “primary” (blue). If omitted, then an app-specific style is used.
    /// </summary>
    property Style: string read GetStyle;
    /// <summary>
    ///   Optional. HTTP or tg:// URL to be opened when the button is pressed. Links
    ///   tg://user?id=&lt;user_id&gt; can be used to mention a user by their identifier without
    ///   using a username, if this is allowed by their privacy settings.
    /// </summary>
    property Url: string read GetUrl;
    /// <summary>
    ///   Optional. Data to be sent in a callback query to the bot when the button is pressed, 1-64
    ///   bytes
    /// </summary>
    property CallbackData: string read GetCallbackData;
    /// <summary>
    ///   Optional. Description of the Web App that will be launched when the user presses the
    ///   button. The Web App will be able to send an arbitrary message on behalf of the user using
    ///   the method answerWebAppQuery. Available only in private chats between a user and the bot.
    ///   Not supported for messages sent on behalf of a business account.
    /// </summary>
    property WebApp: ITgWebAppInfo read GetWebApp;
    /// <summary>
    ///   Optional. An HTTPS URL used to automatically authorize the user. Can be used as a
    ///   replacement for the Telegram Login Widget. Not supported for ephemeral messages.
    /// </summary>
    property LoginUrl: ITgLoginUrl read GetLoginUrl;
    /// <summary>
    ///   Optional. If set, pressing the button will prompt the user to select one of their chats,
    ///   open that chat and insert the bot's username and the specified inline query in the input
    ///   field. May be empty, in which case just the bot's username will be inserted. Not supported
    ///   for messages sent in channel direct messages chats and on behalf of a business account.
    /// </summary>
    property SwitchInlineQuery: string read GetSwitchInlineQuery;
    /// <summary>
    ///   Optional. If set, pressing the button will insert the bot's username and the specified
    ///   inline query in the current chat's input field. May be empty, in which case only the bot's
    ///   username will be inserted. This offers a quick way for the user to open your bot in inline
    ///   mode in the same chat - good for selecting something from multiple options. Not supported
    ///   in channels and for messages sent in channel direct messages chats and on behalf of a
    ///   business account.
    /// </summary>
    property SwitchInlineQueryCurrentChat: string read GetSwitchInlineQueryCurrentChat;
    /// <summary>
    ///   Optional. If set, pressing the button will prompt the user to select one of their chats of
    ///   the specified type, open that chat and insert the bot's username and the specified inline
    ///   query in the input field. Not supported for messages sent in channel direct messages chats
    ///   and on behalf of a business account.
    /// </summary>
    property SwitchInlineQueryChosenChat: ITgSwitchInlineQueryChosenChat read GetSwitchInlineQueryChosenChat;
    /// <summary>
    ///   Optional. Description of the button that copies the specified text to the clipboard
    /// </summary>
    property CopyText: ITgCopyTextButton read GetCopyText;
    /// <summary>
    ///   Optional. Description of the game that will be launched when the user presses the button.
    ///   NOTE: This type of button must always be the first button in the first row.
    /// </summary>
    property CallbackGame: ITgCallbackGame read GetCallbackGame;
    /// <summary>
    ///   Optional. Specify True, to send a Pay button. Substrings “⭐” and “XTR” in the buttons's
    ///   text will be replaced with a Telegram Star icon. NOTE: This type of button must always be
    ///   the first button in the first row and can only be used in invoice messages.
    /// </summary>
    property Pay: Boolean read GetPay;
    /// <summary>Поле pay присутствует.</summary>
    property HasPay: Boolean read GetHasPay;
    /// <summary>Optional. If set, then the button is disabled and does nothing</summary>
    property Disabled: ITgDisabledButton read GetDisabled;
  end;

  /// <summary>
  ///   This object represents a parameter of the inline keyboard button used to automatically
  ///   authorize a user. It serves as a great replacement for the Telegram Login Widget when the
  ///   user is coming from Telegram. All the user needs to do is tap/click a button and confirm
  ///   that they want to log in: TITLE Sample bot: @DiscussBot
  /// </summary>
  ITgLoginUrl = interface(ITgJsonObject)
    ['{683BD47B-FA50-5B62-8A63-5D72CB90D2B8}']
    function GetUrl: string;
    function GetForwardText: string;
    function GetBotUsername: string;
    function GetRequestWriteAccess: Boolean;
    function GetHasRequestWriteAccess: Boolean;
    /// <summary>
    ///   Задаёт url: An HTTPS URL to be opened with user authorization data added to the query
    ///   string when the button is pressed. If the user refuses to provide authorization data, the
    ///   original URL without information about the user will be opened. The data added is the same
    ///   as described in Receiving authorization data. Значение копируется в момент вызова:
    ///   последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithUrl(const AValue: string): ITgLoginUrl;
    /// <summary>
    ///   Задаёт forward_text: Optional. New text of the button in forwarded messages. Значение
    ///   копируется в момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithForwardText(const AValue: string): ITgLoginUrl;
    /// <summary>
    ///   Задаёт bot_username: Optional. Username of a bot, which will be used for user
    ///   authorization; not supported in RichMessageButton. See Setting up a bot for more details.
    ///   If not specified, the current bot's username will be assumed. The url's domain must be the
    ///   same as the domain linked with the bot. See Linking your domain to the bot for more
    ///   details. Значение копируется в момент вызова: последующие изменения переданного объекта на
    ///   этот не влияют.
    /// </summary>
    function WithBotUsername(const AValue: string): ITgLoginUrl;
    /// <summary>
    ///   Задаёт request_write_access: Optional. Pass True to request the permission for your bot to
    ///   send messages to the user. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithRequestWriteAccess(AValue: Boolean): ITgLoginUrl;
    /// <summary>
    ///   An HTTPS URL to be opened with user authorization data added to the query string when the
    ///   button is pressed. If the user refuses to provide authorization data, the original URL
    ///   without information about the user will be opened. The data added is the same as described
    ///   in Receiving authorization data. NOTE: You must always check the hash of the received data
    ///   to verify the authentication and the integrity of the data as described in Checking
    ///   authorization.
    /// </summary>
    property Url: string read GetUrl;
    /// <summary>Optional. New text of the button in forwarded messages</summary>
    property ForwardText: string read GetForwardText;
    /// <summary>
    ///   Optional. Username of a bot, which will be used for user authorization; not supported in
    ///   RichMessageButton. See Setting up a bot for more details. If not specified, the current
    ///   bot's username will be assumed. The url's domain must be the same as the domain linked
    ///   with the bot. See Linking your domain to the bot for more details.
    /// </summary>
    property BotUsername: string read GetBotUsername;
    /// <summary>
    ///   Optional. Pass True to request the permission for your bot to send messages to the user
    /// </summary>
    property RequestWriteAccess: Boolean read GetRequestWriteAccess;
    /// <summary>Поле request_write_access присутствует.</summary>
    property HasRequestWriteAccess: Boolean read GetHasRequestWriteAccess;
  end;

  /// <summary>
  ///   This object represents an inline button that switches the current user to inline mode in a
  ///   chosen chat, with an optional default inline query.
  /// </summary>
  ITgSwitchInlineQueryChosenChat = interface(ITgJsonObject)
    ['{D7E2907A-0693-599C-A6DA-C35B0DA4F5AF}']
    function GetQuery: string;
    function GetAllowUserChats: Boolean;
    function GetHasAllowUserChats: Boolean;
    function GetAllowBotChats: Boolean;
    function GetHasAllowBotChats: Boolean;
    function GetAllowGroupChats: Boolean;
    function GetHasAllowGroupChats: Boolean;
    function GetAllowChannelChats: Boolean;
    function GetHasAllowChannelChats: Boolean;
    /// <summary>
    ///   Задаёт query: Optional. The default inline query to be inserted in the input field. If
    ///   left empty, only the bot's username will be inserted. Значение копируется в момент вызова:
    ///   последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithQuery(const AValue: string): ITgSwitchInlineQueryChosenChat;
    /// <summary>
    ///   Задаёт allow_user_chats: Optional. True, if private chats with users can be chosen.
    ///   Значение копируется в момент вызова: последующие изменения переданного объекта на этот не
    ///   влияют.
    /// </summary>
    function WithAllowUserChats(AValue: Boolean): ITgSwitchInlineQueryChosenChat;
    /// <summary>
    ///   Задаёт allow_bot_chats: Optional. True, if private chats with bots can be chosen. Значение
    ///   копируется в момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithAllowBotChats(AValue: Boolean): ITgSwitchInlineQueryChosenChat;
    /// <summary>
    ///   Задаёт allow_group_chats: Optional. True, if group and supergroup chats can be chosen.
    ///   Значение копируется в момент вызова: последующие изменения переданного объекта на этот не
    ///   влияют.
    /// </summary>
    function WithAllowGroupChats(AValue: Boolean): ITgSwitchInlineQueryChosenChat;
    /// <summary>
    ///   Задаёт allow_channel_chats: Optional. True, if channel chats can be chosen. Значение
    ///   копируется в момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithAllowChannelChats(AValue: Boolean): ITgSwitchInlineQueryChosenChat;
    /// <summary>
    ///   Optional. The default inline query to be inserted in the input field. If left empty, only
    ///   the bot's username will be inserted.
    /// </summary>
    property Query: string read GetQuery;
    /// <summary>Optional. True, if private chats with users can be chosen</summary>
    property AllowUserChats: Boolean read GetAllowUserChats;
    /// <summary>Поле allow_user_chats присутствует.</summary>
    property HasAllowUserChats: Boolean read GetHasAllowUserChats;
    /// <summary>Optional. True, if private chats with bots can be chosen</summary>
    property AllowBotChats: Boolean read GetAllowBotChats;
    /// <summary>Поле allow_bot_chats присутствует.</summary>
    property HasAllowBotChats: Boolean read GetHasAllowBotChats;
    /// <summary>Optional. True, if group and supergroup chats can be chosen</summary>
    property AllowGroupChats: Boolean read GetAllowGroupChats;
    /// <summary>Поле allow_group_chats присутствует.</summary>
    property HasAllowGroupChats: Boolean read GetHasAllowGroupChats;
    /// <summary>Optional. True, if channel chats can be chosen</summary>
    property AllowChannelChats: Boolean read GetAllowChannelChats;
    /// <summary>Поле allow_channel_chats присутствует.</summary>
    property HasAllowChannelChats: Boolean read GetHasAllowChannelChats;
  end;

  /// <summary>
  ///   This object represents an inline keyboard button that copies specified text to the
  ///   clipboard.
  /// </summary>
  ITgCopyTextButton = interface(ITgJsonObject)
    ['{54E897B8-31F5-5C06-B37B-0F5E3EFFBED4}']
    function GetText: string;
    /// <summary>
    ///   Задаёт text: The text to be copied to the clipboard; 1-256 characters. Значение копируется
    ///   в момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithText(const AValue: string): ITgCopyTextButton;
    /// <summary>The text to be copied to the clipboard; 1-256 characters</summary>
    property Text: string read GetText;
  end;

  /// <summary>
  ///   This object represents a disabled button which does nothing. Currently holds no information.
  /// </summary>
  ITgDisabledButton = interface(ITgJsonObject)
    ['{309DFDAF-3D8A-549D-834F-38D5BCD89DD5}']
  end;

  /// <summary>
  ///   This object represents an incoming callback query from a callback button in an inline
  ///   keyboard. If the button that originated the query was attached to a message sent by the bot,
  ///   the field message will be present. If the button was attached to a message sent via the bot
  ///   (in inline mode), the field inline_message_id will be present. Exactly one of the fields
  ///   data or game_short_name will be present. NOTE: After the user presses a callback button,
  ///   Telegram clients will display a progress bar until you call answerCallbackQuery. It is,
  ///   therefore, necessary to react by calling answerCallbackQuery even if no notification to the
  ///   user is needed (e.g., without specifying any of the optional parameters).
  /// </summary>
  ITgCallbackQuery = interface(ITgJsonObject)
    ['{DB2BDF27-5C41-56CC-A65F-A017674D8ADA}']
    function GetId: string;
    function GetFrom: ITgUser;
    function GetMessage: ITgMaybeInaccessibleMessage;
    function GetInlineMessageId: string;
    function GetChatInstance: string;
    function GetData: string;
    function GetGameShortName: string;
    /// <summary>Unique identifier for this query</summary>
    property Id: string read GetId;
    /// <summary>Sender</summary>
    property From: ITgUser read GetFrom;
    /// <summary>
    ///   Optional. Message sent by the bot with the callback button that originated the query
    /// </summary>
    property Message: ITgMaybeInaccessibleMessage read GetMessage;
    /// <summary>
    ///   Optional. Identifier of the message sent via the bot in inline mode, that originated the
    ///   query
    /// </summary>
    property InlineMessageId: string read GetInlineMessageId;
    /// <summary>
    ///   Global identifier, uniquely corresponding to the chat to which the message with the
    ///   callback button was sent. Useful for high scores in games.
    /// </summary>
    property ChatInstance: string read GetChatInstance;
    /// <summary>
    ///   Optional. Data associated with the callback button. Be aware that the message originated
    ///   the query can contain no callback buttons with this data.
    /// </summary>
    property Data: string read GetData;
    /// <summary>
    ///   Optional. Short name of a Game to be returned, serves as the unique identifier for the
    ///   game
    /// </summary>
    property GameShortName: string read GetGameShortName;
  end;

  /// <summary>
  ///   Upon receiving a message with this object, Telegram clients will display a reply interface
  ///   to the user (act as if the user has selected the bot's message and tapped 'Reply'). This can
  ///   be extremely useful if you want to create user-friendly step-by-step interfaces without
  ///   having to sacrifice privacy mode. Not supported in channels and for messages sent on behalf
  ///   of a user account. Example: A poll bot for groups runs in privacy mode (only receives
  ///   commands, replies to its messages and mentions). There could be two ways to create a new
  ///   poll: - Explain the user how to send a command with parameters (e.g. /newpoll question
  ///   answer1 answer2). May be appealing for hardcore users but lacks modern day polish. - Guide
  ///   the user through a step-by-step process. 'Please send me your question', 'Cool, now let's
  ///   add the first answer option', 'Great. Keep adding answer options, then send /done when
  ///   you're ready'. The last option is definitely more attractive. And if you use ForceReply in
  ///   your bot's questions, it will receive the user's answers even if it only receives replies,
  ///   commands and mentions - without any extra work for the user.
  /// </summary>
  ITgForceReply = interface(ITgOutObject)
    ['{7E23D233-566D-511E-85EF-6B2F1AF19660}']
    /// <summary>
    ///   Задаёт input_field_placeholder: Optional. The placeholder to be shown in the input field
    ///   when the reply is active; 1-64 characters
    /// </summary>
    function WithInputFieldPlaceholder(const AValue: string): ITgForceReply;
    /// <summary>
    ///   Задаёт selective: Optional. Use this parameter if you want to force reply from specific
    ///   users only. Targets: 1) users that are @mentioned in the text of the Message object; 2) if
    ///   the bot's message is a reply to a message in the same chat and forum topic, sender of the
    ///   original message.
    /// </summary>
    function WithSelective(AValue: Boolean): ITgForceReply;
  end;

  /// <summary>Represents a community (a group of chats).</summary>
  ITgCommunity = interface(ITgJsonObject)
    ['{4CF496C6-64ED-5E90-9193-7650AD330104}']
    function GetId: Int64;
    function GetName: string;
    /// <summary>
    ///   Unique identifier for this community. This number may have more than 32 significant bits
    ///   and some programming languages may have difficulty/silent defects in interpreting it. But
    ///   it has at most 52 significant bits, so a signed 64-bit integer or double-precision float
    ///   type are safe for storing this identifier.
    /// </summary>
    property Id: Int64 read GetId;
    /// <summary>Name of the community</summary>
    property Name: string read GetName;
  end;

  /// <summary>This object represents a chat photo.</summary>
  ITgChatPhoto = interface(ITgJsonObject)
    ['{1DF07C68-4261-5DAB-9A91-E6CFB26E9D94}']
    function GetSmallFileId: string;
    function GetSmallFileUniqueId: string;
    function GetBigFileId: string;
    function GetBigFileUniqueId: string;
    /// <summary>
    ///   File identifier of small (160x160) chat photo. This file_id can be used only for photo
    ///   download and only for as long as the photo is not changed.
    /// </summary>
    property SmallFileId: string read GetSmallFileId;
    /// <summary>
    ///   Unique file identifier of small (160x160) chat photo, which is supposed to be the same
    ///   over time and for different bots. Can't be used to download or reuse the file.
    /// </summary>
    property SmallFileUniqueId: string read GetSmallFileUniqueId;
    /// <summary>
    ///   File identifier of big (640x640) chat photo. This file_id can be used only for photo
    ///   download and only for as long as the photo is not changed.
    /// </summary>
    property BigFileId: string read GetBigFileId;
    /// <summary>
    ///   Unique file identifier of big (640x640) chat photo, which is supposed to be the same over
    ///   time and for different bots. Can't be used to download or reuse the file.
    /// </summary>
    property BigFileUniqueId: string read GetBigFileUniqueId;
  end;

  /// <summary>Represents an invite link for a chat.</summary>
  ITgChatInviteLink = interface(ITgJsonObject)
    ['{F30272F9-BF38-554A-8B3E-4E3AECFC18FE}']
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
    /// <summary>
    ///   The invite link. If the link was created by another chat administrator, then the second
    ///   part of the link will be replaced with “…”.
    /// </summary>
    property InviteLink: string read GetInviteLink;
    /// <summary>Creator of the link</summary>
    property Creator: ITgUser read GetCreator;
    /// <summary>
    ///   True, if users joining the chat via the link need to be approved by chat administrators
    /// </summary>
    property CreatesJoinRequest: Boolean read GetCreatesJoinRequest;
    /// <summary>True, if the link is primary</summary>
    property IsPrimary: Boolean read GetIsPrimary;
    /// <summary>True, if the link is revoked</summary>
    property IsRevoked: Boolean read GetIsRevoked;
    /// <summary>Optional. Invite link name</summary>
    property Name: string read GetName;
    /// <summary>
    ///   Optional. Point in time (Unix timestamp) when the link will expire or has been expired
    /// </summary>
    property ExpireDate: Int64 read GetExpireDate;
    /// <summary>Поле expire_date присутствует.</summary>
    property HasExpireDate: Boolean read GetHasExpireDate;
    /// <summary>
    ///   Optional. The maximum number of users that can be members of the chat simultaneously after
    ///   joining the chat via this invite link; 1-99999
    /// </summary>
    property MemberLimit: Integer read GetMemberLimit;
    /// <summary>Поле member_limit присутствует.</summary>
    property HasMemberLimit: Boolean read GetHasMemberLimit;
    /// <summary>Optional. Number of pending join requests created using this link</summary>
    property PendingJoinRequestCount: Integer read GetPendingJoinRequestCount;
    /// <summary>Поле pending_join_request_count присутствует.</summary>
    property HasPendingJoinRequestCount: Boolean read GetHasPendingJoinRequestCount;
    /// <summary>
    ///   Optional. The number of seconds the subscription will be active for before the next
    ///   payment
    /// </summary>
    property SubscriptionPeriod: Integer read GetSubscriptionPeriod;
    /// <summary>Поле subscription_period присутствует.</summary>
    property HasSubscriptionPeriod: Boolean read GetHasSubscriptionPeriod;
    /// <summary>
    ///   Optional. The amount of Telegram Stars a user must pay initially and after each subsequent
    ///   subscription period to be a member of the chat using the link
    /// </summary>
    property SubscriptionPrice: Integer read GetSubscriptionPrice;
    /// <summary>Поле subscription_price присутствует.</summary>
    property HasSubscriptionPrice: Boolean read GetHasSubscriptionPrice;
  end;

  /// <summary>Represents the rights of an administrator in a chat.</summary>
  ITgChatAdministratorRights = interface(ITgJsonObject)
    ['{EAC0B840-FF45-5975-B70C-985171C08F09}']
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
    /// <summary>
    ///   Задаёт is_anonymous: True, if the user's presence in the chat is hidden. Значение
    ///   копируется в момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithIsAnonymous(AValue: Boolean): ITgChatAdministratorRights;
    /// <summary>
    ///   Задаёт can_manage_chat: True, if the administrator can access the chat event log, get
    ///   boost list, see hidden supergroup and channel members, report spam messages, ignore slow
    ///   mode, and send messages to the chat without paying Telegram Stars. Implied by any other
    ///   administrator privilege. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithCanManageChat(AValue: Boolean): ITgChatAdministratorRights;
    /// <summary>
    ///   Задаёт can_delete_messages: True, if the administrator can delete messages of other users.
    ///   Значение копируется в момент вызова: последующие изменения переданного объекта на этот не
    ///   влияют.
    /// </summary>
    function WithCanDeleteMessages(AValue: Boolean): ITgChatAdministratorRights;
    /// <summary>
    ///   Задаёт can_manage_video_chats: True, if the administrator can manage video chats. Значение
    ///   копируется в момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithCanManageVideoChats(AValue: Boolean): ITgChatAdministratorRights;
    /// <summary>
    ///   Задаёт can_restrict_members: True, if the administrator can restrict, ban or unban chat
    ///   members, or access supergroup statistics. Значение копируется в момент вызова: последующие
    ///   изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithCanRestrictMembers(AValue: Boolean): ITgChatAdministratorRights;
    /// <summary>
    ///   Задаёт can_promote_members: True, if the administrator can add new administrators with a
    ///   subset of their own privileges or demote administrators that they have promoted, directly
    ///   or indirectly (promoted by administrators that were appointed by the user). Значение
    ///   копируется в момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithCanPromoteMembers(AValue: Boolean): ITgChatAdministratorRights;
    /// <summary>
    ///   Задаёт can_change_info: True, if the user is allowed to change the chat title, photo and
    ///   other settings. Значение копируется в момент вызова: последующие изменения переданного
    ///   объекта на этот не влияют.
    /// </summary>
    function WithCanChangeInfo(AValue: Boolean): ITgChatAdministratorRights;
    /// <summary>
    ///   Задаёт can_invite_users: True, if the user is allowed to invite new users to the chat.
    ///   Значение копируется в момент вызова: последующие изменения переданного объекта на этот не
    ///   влияют.
    /// </summary>
    function WithCanInviteUsers(AValue: Boolean): ITgChatAdministratorRights;
    /// <summary>
    ///   Задаёт can_post_stories: True, if the administrator can post stories to the chat. Значение
    ///   копируется в момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithCanPostStories(AValue: Boolean): ITgChatAdministratorRights;
    /// <summary>
    ///   Задаёт can_edit_stories: True, if the administrator can edit stories posted by other
    ///   users, post stories to the chat page, pin chat stories, and access the chat's story
    ///   archive. Значение копируется в момент вызова: последующие изменения переданного объекта на
    ///   этот не влияют.
    /// </summary>
    function WithCanEditStories(AValue: Boolean): ITgChatAdministratorRights;
    /// <summary>
    ///   Задаёт can_delete_stories: True, if the administrator can delete stories posted by other
    ///   users. Значение копируется в момент вызова: последующие изменения переданного объекта на
    ///   этот не влияют.
    /// </summary>
    function WithCanDeleteStories(AValue: Boolean): ITgChatAdministratorRights;
    /// <summary>
    ///   Задаёт can_post_messages: Optional. True, if the administrator can post messages in the
    ///   channel, approve suggested posts, or access channel statistics; for channels only.
    ///   Значение копируется в момент вызова: последующие изменения переданного объекта на этот не
    ///   влияют.
    /// </summary>
    function WithCanPostMessages(AValue: Boolean): ITgChatAdministratorRights;
    /// <summary>
    ///   Задаёт can_edit_messages: Optional. True, if the administrator can edit messages of other
    ///   users and can pin messages; for channels only. Значение копируется в момент вызова:
    ///   последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithCanEditMessages(AValue: Boolean): ITgChatAdministratorRights;
    /// <summary>
    ///   Задаёт can_pin_messages: Optional. True, if the user is allowed to pin messages; for
    ///   groups and supergroups only. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithCanPinMessages(AValue: Boolean): ITgChatAdministratorRights;
    /// <summary>
    ///   Задаёт can_manage_topics: Optional. True, if the user is allowed to create, rename, close,
    ///   and reopen forum topics; for supergroups only. Значение копируется в момент вызова:
    ///   последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithCanManageTopics(AValue: Boolean): ITgChatAdministratorRights;
    /// <summary>
    ///   Задаёт can_manage_direct_messages: Optional. True, if the administrator can manage direct
    ///   messages of the channel and decline suggested posts; for channels only. Значение
    ///   копируется в момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithCanManageDirectMessages(AValue: Boolean): ITgChatAdministratorRights;
    /// <summary>
    ///   Задаёт can_manage_tags: Optional. True, if the administrator can edit the tags of regular
    ///   members; for groups and supergroups only. Значение копируется в момент вызова: последующие
    ///   изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithCanManageTags(AValue: Boolean): ITgChatAdministratorRights;
    /// <summary>
    ///   Задаёт can_send_welcome_messages: True, if the administrator can manage chat welcome
    ///   messages or directly send them in the case of bots. Значение копируется в момент вызова:
    ///   последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithCanSendWelcomeMessages(AValue: Boolean): ITgChatAdministratorRights;
    /// <summary>True, if the user's presence in the chat is hidden</summary>
    property IsAnonymous: Boolean read GetIsAnonymous;
    /// <summary>
    ///   True, if the administrator can access the chat event log, get boost list, see hidden
    ///   supergroup and channel members, report spam messages, ignore slow mode, and send messages
    ///   to the chat without paying Telegram Stars. Implied by any other administrator privilege.
    /// </summary>
    property CanManageChat: Boolean read GetCanManageChat;
    /// <summary>True, if the administrator can delete messages of other users</summary>
    property CanDeleteMessages: Boolean read GetCanDeleteMessages;
    /// <summary>True, if the administrator can manage video chats</summary>
    property CanManageVideoChats: Boolean read GetCanManageVideoChats;
    /// <summary>
    ///   True, if the administrator can restrict, ban or unban chat members, or access supergroup
    ///   statistics
    /// </summary>
    property CanRestrictMembers: Boolean read GetCanRestrictMembers;
    /// <summary>
    ///   True, if the administrator can add new administrators with a subset of their own
    ///   privileges or demote administrators that they have promoted, directly or indirectly
    ///   (promoted by administrators that were appointed by the user)
    /// </summary>
    property CanPromoteMembers: Boolean read GetCanPromoteMembers;
    /// <summary>
    ///   True, if the user is allowed to change the chat title, photo and other settings
    /// </summary>
    property CanChangeInfo: Boolean read GetCanChangeInfo;
    /// <summary>True, if the user is allowed to invite new users to the chat</summary>
    property CanInviteUsers: Boolean read GetCanInviteUsers;
    /// <summary>True, if the administrator can post stories to the chat</summary>
    property CanPostStories: Boolean read GetCanPostStories;
    /// <summary>
    ///   True, if the administrator can edit stories posted by other users, post stories to the
    ///   chat page, pin chat stories, and access the chat's story archive
    /// </summary>
    property CanEditStories: Boolean read GetCanEditStories;
    /// <summary>
    ///   True, if the administrator can delete stories posted by other users
    /// </summary>
    property CanDeleteStories: Boolean read GetCanDeleteStories;
    /// <summary>
    ///   Optional. True, if the administrator can post messages in the channel, approve suggested
    ///   posts, or access channel statistics; for channels only
    /// </summary>
    property CanPostMessages: Boolean read GetCanPostMessages;
    /// <summary>Поле can_post_messages присутствует.</summary>
    property HasCanPostMessages: Boolean read GetHasCanPostMessages;
    /// <summary>
    ///   Optional. True, if the administrator can edit messages of other users and can pin
    ///   messages; for channels only
    /// </summary>
    property CanEditMessages: Boolean read GetCanEditMessages;
    /// <summary>Поле can_edit_messages присутствует.</summary>
    property HasCanEditMessages: Boolean read GetHasCanEditMessages;
    /// <summary>
    ///   Optional. True, if the user is allowed to pin messages; for groups and supergroups only
    /// </summary>
    property CanPinMessages: Boolean read GetCanPinMessages;
    /// <summary>Поле can_pin_messages присутствует.</summary>
    property HasCanPinMessages: Boolean read GetHasCanPinMessages;
    /// <summary>
    ///   Optional. True, if the user is allowed to create, rename, close, and reopen forum topics;
    ///   for supergroups only
    /// </summary>
    property CanManageTopics: Boolean read GetCanManageTopics;
    /// <summary>Поле can_manage_topics присутствует.</summary>
    property HasCanManageTopics: Boolean read GetHasCanManageTopics;
    /// <summary>
    ///   Optional. True, if the administrator can manage direct messages of the channel and decline
    ///   suggested posts; for channels only
    /// </summary>
    property CanManageDirectMessages: Boolean read GetCanManageDirectMessages;
    /// <summary>Поле can_manage_direct_messages присутствует.</summary>
    property HasCanManageDirectMessages: Boolean read GetHasCanManageDirectMessages;
    /// <summary>
    ///   Optional. True, if the administrator can edit the tags of regular members; for groups and
    ///   supergroups only
    /// </summary>
    property CanManageTags: Boolean read GetCanManageTags;
    /// <summary>Поле can_manage_tags присутствует.</summary>
    property HasCanManageTags: Boolean read GetHasCanManageTags;
    /// <summary>
    ///   True, if the administrator can manage chat welcome messages or directly send them in the
    ///   case of bots
    /// </summary>
    property CanSendWelcomeMessages: Boolean read GetCanSendWelcomeMessages;
  end;

  /// <summary>This object represents changes in the status of a chat member.</summary>
  ITgChatMemberUpdated = interface(ITgJsonObject)
    ['{6539A5F1-0E44-5AB0-BBD5-68270393AB6E}']
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
    /// <summary>Chat the user belongs to</summary>
    property Chat: ITgChat read GetChat;
    /// <summary>Performer of the action, which resulted in the change</summary>
    property From: ITgUser read GetFrom;
    /// <summary>Date the change was done in Unix time</summary>
    property Date: Int64 read GetDate;
    /// <summary>Previous information about the chat member</summary>
    property OldChatMember: ITgChatMember read GetOldChatMember;
    /// <summary>New information about the chat member</summary>
    property NewChatMember: ITgChatMember read GetNewChatMember;
    /// <summary>
    ///   Optional. Chat invite link, which was used by the user to join the chat; for joining by
    ///   invite link events only
    /// </summary>
    property InviteLink: ITgChatInviteLink read GetInviteLink;
    /// <summary>
    ///   Optional. True, if the user joined the chat after sending a direct join request without
    ///   using an invite link and being approved by an administrator
    /// </summary>
    property ViaJoinRequest: Boolean read GetViaJoinRequest;
    /// <summary>Поле via_join_request присутствует.</summary>
    property HasViaJoinRequest: Boolean read GetHasViaJoinRequest;
    /// <summary>
    ///   Optional. True, if the user joined the chat via a chat folder invite link
    /// </summary>
    property ViaChatFolderInviteLink: Boolean read GetViaChatFolderInviteLink;
    /// <summary>Поле via_chat_folder_invite_link присутствует.</summary>
    property HasViaChatFolderInviteLink: Boolean read GetHasViaChatFolderInviteLink;
  end;

  /// <summary>
  ///   This object contains information about one member of a chat. Currently, the following 6
  ///   types of chat members are supported: Виды (Kind, As*): ITgChatMemberOwner,
  ///   ITgChatMemberAdministrator, ITgChatMemberMember, ITgChatMemberRestricted, ITgChatMemberLeft,
  ///   ITgChatMemberBanned.
  /// </summary>
  ITgChatMember = interface(ITgJsonObject)
    ['{A77AFCB0-EE7F-5487-82AB-2C2D44C32B7F}']
    function GetKind: TTgChatMemberKind;
    function GetKindText: string;
    function GetStatus: string;
    function GetUser: ITgUser;
    /// <summary>ITgChatMemberOwner или nil, если объект другого вида.</summary>
    function AsOwner: ITgChatMemberOwner;
    /// <summary>ITgChatMemberAdministrator или nil, если объект другого вида.</summary>
    function AsAdministrator: ITgChatMemberAdministrator;
    /// <summary>ITgChatMemberMember или nil, если объект другого вида.</summary>
    function AsMember: ITgChatMemberMember;
    /// <summary>ITgChatMemberRestricted или nil, если объект другого вида.</summary>
    function AsRestricted: ITgChatMemberRestricted;
    /// <summary>ITgChatMemberLeft или nil, если объект другого вида.</summary>
    function AsLeft: ITgChatMemberLeft;
    /// <summary>ITgChatMemberBanned или nil, если объект другого вида.</summary>
    function AsBanned: ITgChatMemberBanned;
    /// <summary>Вид объекта (Unknown — неизвестный этой версии библиотеки).</summary>
    property Kind: TTgChatMemberKind read GetKind;
    /// <summary>
    ///   Значение поля status в JSON как есть (в т.ч. при Kind = Unknown); для вариантов-строк и
    ///   массивов — пустая строка.
    /// </summary>
    property KindText: string read GetKindText;
    /// <summary>Значение поля status в JSON; вид объекта — свойство Kind.</summary>
    property Status: string read GetStatus;
    /// <summary>Information about the user</summary>
    property User: ITgUser read GetUser;
  end;

  /// <summary>
  ///   Represents a chat member that owns the chat and has all administrator privileges.
  /// </summary>
  ITgChatMemberOwner = interface(ITgChatMember)
    ['{97725070-5AFF-5070-AEEB-80F6BC18A74F}']
    function GetIsAnonymous: Boolean;
    function GetCustomTitle: string;
    /// <summary>True, if the user's presence in the chat is hidden</summary>
    property IsAnonymous: Boolean read GetIsAnonymous;
    /// <summary>Optional. Custom title for this user</summary>
    property CustomTitle: string read GetCustomTitle;
  end;

  /// <summary>Represents a chat member that has some additional privileges.</summary>
  ITgChatMemberAdministrator = interface(ITgChatMember)
    ['{BC68D5BE-2B9A-5D06-89A9-1F2DF6E6F57B}']
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
    /// <summary>
    ///   True, if the bot is allowed to edit administrator privileges of that user
    /// </summary>
    property CanBeEdited: Boolean read GetCanBeEdited;
    /// <summary>True, if the user's presence in the chat is hidden</summary>
    property IsAnonymous: Boolean read GetIsAnonymous;
    /// <summary>
    ///   True, if the administrator can access the chat event log, get boost list, see hidden
    ///   supergroup and channel members, report spam messages, ignore slow mode, and send messages
    ///   to the chat without paying Telegram Stars. Implied by any other administrator privilege.
    /// </summary>
    property CanManageChat: Boolean read GetCanManageChat;
    /// <summary>True, if the administrator can delete messages of other users</summary>
    property CanDeleteMessages: Boolean read GetCanDeleteMessages;
    /// <summary>True, if the administrator can manage video chats</summary>
    property CanManageVideoChats: Boolean read GetCanManageVideoChats;
    /// <summary>
    ///   True, if the administrator can restrict, ban or unban chat members, or access supergroup
    ///   statistics
    /// </summary>
    property CanRestrictMembers: Boolean read GetCanRestrictMembers;
    /// <summary>
    ///   True, if the administrator can add new administrators with a subset of their own
    ///   privileges or demote administrators that they have promoted, directly or indirectly
    ///   (promoted by administrators that were appointed by the user)
    /// </summary>
    property CanPromoteMembers: Boolean read GetCanPromoteMembers;
    /// <summary>
    ///   True, if the user is allowed to change the chat title, photo and other settings
    /// </summary>
    property CanChangeInfo: Boolean read GetCanChangeInfo;
    /// <summary>True, if the user is allowed to invite new users to the chat</summary>
    property CanInviteUsers: Boolean read GetCanInviteUsers;
    /// <summary>True, if the administrator can post stories to the chat</summary>
    property CanPostStories: Boolean read GetCanPostStories;
    /// <summary>
    ///   True, if the administrator can edit stories posted by other users, post stories to the
    ///   chat page, pin chat stories, and access the chat's story archive
    /// </summary>
    property CanEditStories: Boolean read GetCanEditStories;
    /// <summary>
    ///   True, if the administrator can delete stories posted by other users
    /// </summary>
    property CanDeleteStories: Boolean read GetCanDeleteStories;
    /// <summary>
    ///   Optional. True, if the administrator can post messages in the channel, approve suggested
    ///   posts, or access channel statistics; for channels only
    /// </summary>
    property CanPostMessages: Boolean read GetCanPostMessages;
    /// <summary>Поле can_post_messages присутствует.</summary>
    property HasCanPostMessages: Boolean read GetHasCanPostMessages;
    /// <summary>
    ///   Optional. True, if the administrator can edit messages of other users and can pin
    ///   messages; for channels only
    /// </summary>
    property CanEditMessages: Boolean read GetCanEditMessages;
    /// <summary>Поле can_edit_messages присутствует.</summary>
    property HasCanEditMessages: Boolean read GetHasCanEditMessages;
    /// <summary>
    ///   Optional. True, if the user is allowed to pin messages; for groups and supergroups only
    /// </summary>
    property CanPinMessages: Boolean read GetCanPinMessages;
    /// <summary>Поле can_pin_messages присутствует.</summary>
    property HasCanPinMessages: Boolean read GetHasCanPinMessages;
    /// <summary>
    ///   Optional. True, if the user is allowed to create, rename, close, and reopen forum topics;
    ///   for supergroups only
    /// </summary>
    property CanManageTopics: Boolean read GetCanManageTopics;
    /// <summary>Поле can_manage_topics присутствует.</summary>
    property HasCanManageTopics: Boolean read GetHasCanManageTopics;
    /// <summary>
    ///   Optional. True, if the administrator can manage direct messages of the channel and decline
    ///   suggested posts; for channels only
    /// </summary>
    property CanManageDirectMessages: Boolean read GetCanManageDirectMessages;
    /// <summary>Поле can_manage_direct_messages присутствует.</summary>
    property HasCanManageDirectMessages: Boolean read GetHasCanManageDirectMessages;
    /// <summary>
    ///   Optional. True, if the administrator can edit the tags of regular members; for groups and
    ///   supergroups only
    /// </summary>
    property CanManageTags: Boolean read GetCanManageTags;
    /// <summary>Поле can_manage_tags присутствует.</summary>
    property HasCanManageTags: Boolean read GetHasCanManageTags;
    /// <summary>
    ///   True, if the administrator can manage chat welcome messages or directly send them in the
    ///   case of bots
    /// </summary>
    property CanSendWelcomeMessages: Boolean read GetCanSendWelcomeMessages;
    /// <summary>Optional. Custom title for this user</summary>
    property CustomTitle: string read GetCustomTitle;
  end;

  /// <summary>
  ///   Represents a chat member that has no additional privileges or restrictions.
  /// </summary>
  ITgChatMemberMember = interface(ITgChatMember)
    ['{417DFFA4-9B82-56A7-9FAF-378846E66EEE}']
    function GetTag: string;
    function GetUntilDate: Int64;
    function GetHasUntilDate: Boolean;
    /// <summary>Optional. Tag of the member</summary>
    property Tag: string read GetTag;
    /// <summary>
    ///   Optional. Date when the user's subscription will expire; Unix time
    /// </summary>
    property UntilDate: Int64 read GetUntilDate;
    /// <summary>Поле until_date присутствует.</summary>
    property HasUntilDate: Boolean read GetHasUntilDate;
  end;

  /// <summary>
  ///   Represents a chat member that is under certain restrictions in the chat. Supergroups only.
  /// </summary>
  ITgChatMemberRestricted = interface(ITgChatMember)
    ['{1ACD17C8-6834-5CB2-9BBA-D8808E8696AD}']
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
    /// <summary>Optional. Tag of the member</summary>
    property Tag: string read GetTag;
    /// <summary>
    ///   True, if the user is a member of the chat at the moment of the request
    /// </summary>
    property IsMember: Boolean read GetIsMember;
    /// <summary>
    ///   True, if the user is allowed to send text messages, rich messages, contacts, giveaways,
    ///   giveaway winners, invoices, locations and venues
    /// </summary>
    property CanSendMessages: Boolean read GetCanSendMessages;
    /// <summary>True, if the user is allowed to send audios</summary>
    property CanSendAudios: Boolean read GetCanSendAudios;
    /// <summary>True, if the user is allowed to send documents</summary>
    property CanSendDocuments: Boolean read GetCanSendDocuments;
    /// <summary>True, if the user is allowed to send photos</summary>
    property CanSendPhotos: Boolean read GetCanSendPhotos;
    /// <summary>True, if the user is allowed to send videos</summary>
    property CanSendVideos: Boolean read GetCanSendVideos;
    /// <summary>True, if the user is allowed to send video notes</summary>
    property CanSendVideoNotes: Boolean read GetCanSendVideoNotes;
    /// <summary>True, if the user is allowed to send voice notes</summary>
    property CanSendVoiceNotes: Boolean read GetCanSendVoiceNotes;
    /// <summary>True, if the user is allowed to send polls and checklists</summary>
    property CanSendPolls: Boolean read GetCanSendPolls;
    /// <summary>
    ///   True, if the user is allowed to send animations, games, stickers and use inline bots
    /// </summary>
    property CanSendOtherMessages: Boolean read GetCanSendOtherMessages;
    /// <summary>
    ///   True, if the user is allowed to add web page previews to their messages
    /// </summary>
    property CanAddWebPagePreviews: Boolean read GetCanAddWebPagePreviews;
    /// <summary>True, if the user is allowed to react to messages</summary>
    property CanReactToMessages: Boolean read GetCanReactToMessages;
    /// <summary>True, if the user is allowed to edit their own tag</summary>
    property CanEditTag: Boolean read GetCanEditTag;
    /// <summary>
    ///   True, if the user is allowed to change the chat title, photo and other settings
    /// </summary>
    property CanChangeInfo: Boolean read GetCanChangeInfo;
    /// <summary>True, if the user is allowed to invite new users to the chat</summary>
    property CanInviteUsers: Boolean read GetCanInviteUsers;
    /// <summary>True, if the user is allowed to pin messages</summary>
    property CanPinMessages: Boolean read GetCanPinMessages;
    /// <summary>True, if the user is allowed to create forum topics</summary>
    property CanManageTopics: Boolean read GetCanManageTopics;
    /// <summary>
    ///   Date when restrictions will be lifted for this user; Unix time. If 0, then the user is
    ///   restricted forever.
    /// </summary>
    property UntilDate: Int64 read GetUntilDate;
  end;

  /// <summary>
  ///   Represents a chat member that isn't currently a member of the chat, but may join it
  ///   themselves.
  /// </summary>
  ITgChatMemberLeft = interface(ITgChatMember)
    ['{BB3C8962-ABD5-5955-AE8D-FE4863C4AF7B}']
  end;

  /// <summary>
  ///   Represents a chat member that was banned in the chat and can't return to the chat or view
  ///   chat messages.
  /// </summary>
  ITgChatMemberBanned = interface(ITgChatMember)
    ['{6CAB18E0-931D-5B68-8709-4FD3F3827D21}']
    function GetUntilDate: Int64;
    /// <summary>
    ///   Date when restrictions will be lifted for this user; Unix time. If 0, then the user is
    ///   banned forever.
    /// </summary>
    property UntilDate: Int64 read GetUntilDate;
  end;

  /// <summary>Represents a join request sent to a chat.</summary>
  ITgChatJoinRequest = interface(ITgJsonObject)
    ['{26F3D133-86D8-5F92-A80D-58CE689DB81D}']
    function GetChat: ITgChat;
    function GetFrom: ITgUser;
    function GetUserChatId: Int64;
    function GetDate: Int64;
    function GetBio: string;
    function GetInviteLink: ITgChatInviteLink;
    function GetQueryId: string;
    /// <summary>Chat to which the request was sent</summary>
    property Chat: ITgChat read GetChat;
    /// <summary>User that sent the join request</summary>
    property From: ITgUser read GetFrom;
    /// <summary>
    ///   Identifier of a private chat with the user who sent the join request. This number may have
    ///   more than 32 significant bits and some programming languages may have difficulty/silent
    ///   defects in interpreting it. But it has at most 52 significant bits, so a 64-bit integer or
    ///   double-precision float type are safe for storing this identifier. The bot can use this
    ///   identifier for 5 minutes to send messages until the join request is processed, assuming no
    ///   other administrator contacted the user.
    /// </summary>
    property UserChatId: Int64 read GetUserChatId;
    /// <summary>Date the request was sent in Unix time</summary>
    property Date: Int64 read GetDate;
    /// <summary>Optional. Bio of the user</summary>
    property Bio: string read GetBio;
    /// <summary>
    ///   Optional. Chat invite link that was used by the user to send the join request
    /// </summary>
    property InviteLink: ITgChatInviteLink read GetInviteLink;
    /// <summary>
    ///   Optional. Identifier of the join request query; for bots assigned to process join requests
    ///   only. If present, then the bot must call sendChatJoinRequestWebApp or directly call
    ///   answerChatJoinRequestQuery within 10 seconds.
    /// </summary>
    property QueryId: string read GetQueryId;
  end;

  /// <summary>
  ///   Describes actions that a non-administrator user is allowed to take in a chat.
  /// </summary>
  ITgChatPermissions = interface(ITgJsonObject)
    ['{C2398628-80B3-551C-B77E-C793308AA8CC}']
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
    /// <summary>
    ///   Задаёт can_send_messages: Optional. True, if the user is allowed to send text messages,
    ///   rich messages, contacts, giveaways, giveaway winners, invoices, locations and venues.
    ///   Значение копируется в момент вызова: последующие изменения переданного объекта на этот не
    ///   влияют.
    /// </summary>
    function WithCanSendMessages(AValue: Boolean): ITgChatPermissions;
    /// <summary>
    ///   Задаёт can_send_audios: Optional. True, if the user is allowed to send audios. Значение
    ///   копируется в момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithCanSendAudios(AValue: Boolean): ITgChatPermissions;
    /// <summary>
    ///   Задаёт can_send_documents: Optional. True, if the user is allowed to send documents.
    ///   Значение копируется в момент вызова: последующие изменения переданного объекта на этот не
    ///   влияют.
    /// </summary>
    function WithCanSendDocuments(AValue: Boolean): ITgChatPermissions;
    /// <summary>
    ///   Задаёт can_send_photos: Optional. True, if the user is allowed to send photos. Значение
    ///   копируется в момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithCanSendPhotos(AValue: Boolean): ITgChatPermissions;
    /// <summary>
    ///   Задаёт can_send_videos: Optional. True, if the user is allowed to send videos. Значение
    ///   копируется в момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithCanSendVideos(AValue: Boolean): ITgChatPermissions;
    /// <summary>
    ///   Задаёт can_send_video_notes: Optional. True, if the user is allowed to send video notes.
    ///   Значение копируется в момент вызова: последующие изменения переданного объекта на этот не
    ///   влияют.
    /// </summary>
    function WithCanSendVideoNotes(AValue: Boolean): ITgChatPermissions;
    /// <summary>
    ///   Задаёт can_send_voice_notes: Optional. True, if the user is allowed to send voice notes.
    ///   Значение копируется в момент вызова: последующие изменения переданного объекта на этот не
    ///   влияют.
    /// </summary>
    function WithCanSendVoiceNotes(AValue: Boolean): ITgChatPermissions;
    /// <summary>
    ///   Задаёт can_send_polls: Optional. True, if the user is allowed to send polls and
    ///   checklists. Значение копируется в момент вызова: последующие изменения переданного объекта
    ///   на этот не влияют.
    /// </summary>
    function WithCanSendPolls(AValue: Boolean): ITgChatPermissions;
    /// <summary>
    ///   Задаёт can_send_other_messages: Optional. True, if the user is allowed to send animations,
    ///   games, stickers and use inline bots. Значение копируется в момент вызова: последующие
    ///   изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithCanSendOtherMessages(AValue: Boolean): ITgChatPermissions;
    /// <summary>
    ///   Задаёт can_add_web_page_previews: Optional. True, if the user is allowed to add web page
    ///   previews to their messages. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithCanAddWebPagePreviews(AValue: Boolean): ITgChatPermissions;
    /// <summary>
    ///   Задаёт can_react_to_messages: Optional. True, if the user is allowed to react to messages.
    ///   If omitted, defaults to the value of can_send_messages. Значение копируется в момент
    ///   вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithCanReactToMessages(AValue: Boolean): ITgChatPermissions;
    /// <summary>
    ///   Задаёт can_edit_tag: Optional. True, if the user is allowed to edit their own tag. If
    ///   omitted, defaults to the value of can_pin_messages. Значение копируется в момент вызова:
    ///   последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithCanEditTag(AValue: Boolean): ITgChatPermissions;
    /// <summary>
    ///   Задаёт can_change_info: Optional. True, if the user is allowed to change the chat title,
    ///   photo and other settings. Ignored in public supergroups. Значение копируется в момент
    ///   вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithCanChangeInfo(AValue: Boolean): ITgChatPermissions;
    /// <summary>
    ///   Задаёт can_invite_users: Optional. True, if the user is allowed to invite new users to the
    ///   chat. Значение копируется в момент вызова: последующие изменения переданного объекта на
    ///   этот не влияют.
    /// </summary>
    function WithCanInviteUsers(AValue: Boolean): ITgChatPermissions;
    /// <summary>
    ///   Задаёт can_pin_messages: Optional. True, if the user is allowed to pin messages. Ignored
    ///   in public supergroups. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithCanPinMessages(AValue: Boolean): ITgChatPermissions;
    /// <summary>
    ///   Задаёт can_manage_topics: Optional. True, if the user is allowed to create forum topics.
    ///   If omitted, defaults to the value of can_pin_messages. Значение копируется в момент
    ///   вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithCanManageTopics(AValue: Boolean): ITgChatPermissions;
    /// <summary>
    ///   Optional. True, if the user is allowed to send text messages, rich messages, contacts,
    ///   giveaways, giveaway winners, invoices, locations and venues
    /// </summary>
    property CanSendMessages: Boolean read GetCanSendMessages;
    /// <summary>Поле can_send_messages присутствует.</summary>
    property HasCanSendMessages: Boolean read GetHasCanSendMessages;
    /// <summary>Optional. True, if the user is allowed to send audios</summary>
    property CanSendAudios: Boolean read GetCanSendAudios;
    /// <summary>Поле can_send_audios присутствует.</summary>
    property HasCanSendAudios: Boolean read GetHasCanSendAudios;
    /// <summary>Optional. True, if the user is allowed to send documents</summary>
    property CanSendDocuments: Boolean read GetCanSendDocuments;
    /// <summary>Поле can_send_documents присутствует.</summary>
    property HasCanSendDocuments: Boolean read GetHasCanSendDocuments;
    /// <summary>Optional. True, if the user is allowed to send photos</summary>
    property CanSendPhotos: Boolean read GetCanSendPhotos;
    /// <summary>Поле can_send_photos присутствует.</summary>
    property HasCanSendPhotos: Boolean read GetHasCanSendPhotos;
    /// <summary>Optional. True, if the user is allowed to send videos</summary>
    property CanSendVideos: Boolean read GetCanSendVideos;
    /// <summary>Поле can_send_videos присутствует.</summary>
    property HasCanSendVideos: Boolean read GetHasCanSendVideos;
    /// <summary>Optional. True, if the user is allowed to send video notes</summary>
    property CanSendVideoNotes: Boolean read GetCanSendVideoNotes;
    /// <summary>Поле can_send_video_notes присутствует.</summary>
    property HasCanSendVideoNotes: Boolean read GetHasCanSendVideoNotes;
    /// <summary>Optional. True, if the user is allowed to send voice notes</summary>
    property CanSendVoiceNotes: Boolean read GetCanSendVoiceNotes;
    /// <summary>Поле can_send_voice_notes присутствует.</summary>
    property HasCanSendVoiceNotes: Boolean read GetHasCanSendVoiceNotes;
    /// <summary>
    ///   Optional. True, if the user is allowed to send polls and checklists
    /// </summary>
    property CanSendPolls: Boolean read GetCanSendPolls;
    /// <summary>Поле can_send_polls присутствует.</summary>
    property HasCanSendPolls: Boolean read GetHasCanSendPolls;
    /// <summary>
    ///   Optional. True, if the user is allowed to send animations, games, stickers and use inline
    ///   bots
    /// </summary>
    property CanSendOtherMessages: Boolean read GetCanSendOtherMessages;
    /// <summary>Поле can_send_other_messages присутствует.</summary>
    property HasCanSendOtherMessages: Boolean read GetHasCanSendOtherMessages;
    /// <summary>
    ///   Optional. True, if the user is allowed to add web page previews to their messages
    /// </summary>
    property CanAddWebPagePreviews: Boolean read GetCanAddWebPagePreviews;
    /// <summary>Поле can_add_web_page_previews присутствует.</summary>
    property HasCanAddWebPagePreviews: Boolean read GetHasCanAddWebPagePreviews;
    /// <summary>
    ///   Optional. True, if the user is allowed to react to messages. If omitted, defaults to the
    ///   value of can_send_messages.
    /// </summary>
    property CanReactToMessages: Boolean read GetCanReactToMessages;
    /// <summary>Поле can_react_to_messages присутствует.</summary>
    property HasCanReactToMessages: Boolean read GetHasCanReactToMessages;
    /// <summary>
    ///   Optional. True, if the user is allowed to edit their own tag. If omitted, defaults to the
    ///   value of can_pin_messages.
    /// </summary>
    property CanEditTag: Boolean read GetCanEditTag;
    /// <summary>Поле can_edit_tag присутствует.</summary>
    property HasCanEditTag: Boolean read GetHasCanEditTag;
    /// <summary>
    ///   Optional. True, if the user is allowed to change the chat title, photo and other settings.
    ///   Ignored in public supergroups.
    /// </summary>
    property CanChangeInfo: Boolean read GetCanChangeInfo;
    /// <summary>Поле can_change_info присутствует.</summary>
    property HasCanChangeInfo: Boolean read GetHasCanChangeInfo;
    /// <summary>
    ///   Optional. True, if the user is allowed to invite new users to the chat
    /// </summary>
    property CanInviteUsers: Boolean read GetCanInviteUsers;
    /// <summary>Поле can_invite_users присутствует.</summary>
    property HasCanInviteUsers: Boolean read GetHasCanInviteUsers;
    /// <summary>
    ///   Optional. True, if the user is allowed to pin messages. Ignored in public supergroups.
    /// </summary>
    property CanPinMessages: Boolean read GetCanPinMessages;
    /// <summary>Поле can_pin_messages присутствует.</summary>
    property HasCanPinMessages: Boolean read GetHasCanPinMessages;
    /// <summary>
    ///   Optional. True, if the user is allowed to create forum topics. If omitted, defaults to the
    ///   value of can_pin_messages.
    /// </summary>
    property CanManageTopics: Boolean read GetCanManageTopics;
    /// <summary>Поле can_manage_topics присутствует.</summary>
    property HasCanManageTopics: Boolean read GetHasCanManageTopics;
  end;

  /// <summary>Describes the birthdate of a user.</summary>
  ITgBirthdate = interface(ITgJsonObject)
    ['{D103F6D5-E041-5DB5-8DB1-6DACB2A98073}']
    function GetDay: Integer;
    function GetMonth: Integer;
    function GetYear: Integer;
    function GetHasYear: Boolean;
    /// <summary>Day of the user's birth; 1-31</summary>
    property Day: Integer read GetDay;
    /// <summary>Month of the user's birth; 1-12</summary>
    property Month: Integer read GetMonth;
    /// <summary>Optional. Year of the user's birth</summary>
    property Year: Integer read GetYear;
    /// <summary>Поле year присутствует.</summary>
    property HasYear: Boolean read GetHasYear;
  end;

  /// <summary>
  ///   Contains information about the start page settings of a Telegram Business account.
  /// </summary>
  ITgBusinessIntro = interface(ITgJsonObject)
    ['{D3EB2BD2-BC88-5B7E-B7A8-A61730B088A3}']
    function GetTitle: string;
    function GetMessage: string;
    function GetSticker: ITgSticker;
    /// <summary>Optional. Title text of the business intro</summary>
    property Title: string read GetTitle;
    /// <summary>Optional. Message text of the business intro</summary>
    property Message: string read GetMessage;
    /// <summary>Optional. Sticker of the business intro</summary>
    property Sticker: ITgSticker read GetSticker;
  end;

  /// <summary>
  ///   Contains information about the location of a Telegram Business account.
  /// </summary>
  ITgBusinessLocation = interface(ITgJsonObject)
    ['{76103048-7F82-522E-9D26-9E741F419BCE}']
    function GetAddress: string;
    function GetLocation: ITgLocation;
    /// <summary>Address of the business</summary>
    property Address: string read GetAddress;
    /// <summary>Optional. Location of the business</summary>
    property Location: ITgLocation read GetLocation;
  end;

  /// <summary>Describes an interval of time during which a business is open.</summary>
  ITgBusinessOpeningHoursInterval = interface(ITgJsonObject)
    ['{0DC055F1-9B8F-5FBF-8567-4AEBE5E0AF05}']
    function GetOpeningMinute: Integer;
    function GetClosingMinute: Integer;
    /// <summary>
    ///   The minute's sequence number in a week, starting on Monday, marking the start of the time
    ///   interval during which the business is open; 0 - 7 * 24 * 60
    /// </summary>
    property OpeningMinute: Integer read GetOpeningMinute;
    /// <summary>
    ///   The minute's sequence number in a week, starting on Monday, marking the end of the time
    ///   interval during which the business is open; 0 - 8 * 24 * 60
    /// </summary>
    property ClosingMinute: Integer read GetClosingMinute;
  end;

  /// <summary>Describes the opening hours of a business.</summary>
  ITgBusinessOpeningHours = interface(ITgJsonObject)
    ['{CB73FE96-E687-5433-8F5C-5C38D08E7171}']
    function GetTimeZoneName: string;
    function GetOpeningHours: TArray<ITgBusinessOpeningHoursInterval>;
    /// <summary>
    ///   Unique name of the time zone for which the opening hours are defined
    /// </summary>
    property TimeZoneName: string read GetTimeZoneName;
    /// <summary>List of time intervals describing business opening hours</summary>
    property OpeningHours: TArray<ITgBusinessOpeningHoursInterval> read GetOpeningHours;
  end;

  /// <summary>
  ///   This object describes the rating of a user based on their Telegram Star spendings.
  /// </summary>
  ITgUserRating = interface(ITgJsonObject)
    ['{87EFC4AB-5844-5FEA-B76C-509B33BDD257}']
    function GetLevel: Integer;
    function GetRating: Integer;
    function GetCurrentLevelRating: Integer;
    function GetNextLevelRating: Integer;
    function GetHasNextLevelRating: Boolean;
    /// <summary>
    ///   Current level of the user, indicating their reliability when purchasing digital goods and
    ///   services. A higher level suggests a more trustworthy customer; a negative level is likely
    ///   reason for concern.
    /// </summary>
    property Level: Integer read GetLevel;
    /// <summary>
    ///   Numerical value of the user's rating; the higher the rating, the better
    /// </summary>
    property Rating: Integer read GetRating;
    /// <summary>The rating value required to get the current level</summary>
    property CurrentLevelRating: Integer read GetCurrentLevelRating;
    /// <summary>
    ///   Optional. The rating value required to get to the next level; omitted if the maximum level
    ///   was reached
    /// </summary>
    property NextLevelRating: Integer read GetNextLevelRating;
    /// <summary>Поле next_level_rating присутствует.</summary>
    property HasNextLevelRating: Boolean read GetHasNextLevelRating;
  end;

  /// <summary>Describes the position of a clickable area within a story.</summary>
  ITgStoryAreaPosition = interface(ITgOutObject)
    ['{A6C2647F-C622-55B3-9960-56737FCF8223}']
    /// <summary>
    ///   Задаёт x_percentage: The abscissa of the area's center, as a percentage of the media width
    /// </summary>
    function WithXPercentage(AValue: Double): ITgStoryAreaPosition;
    /// <summary>
    ///   Задаёт y_percentage: The ordinate of the area's center, as a percentage of the media
    ///   height
    /// </summary>
    function WithYPercentage(AValue: Double): ITgStoryAreaPosition;
    /// <summary>
    ///   Задаёт width_percentage: The width of the area's rectangle, as a percentage of the media
    ///   width
    /// </summary>
    function WithWidthPercentage(AValue: Double): ITgStoryAreaPosition;
    /// <summary>
    ///   Задаёт height_percentage: The height of the area's rectangle, as a percentage of the media
    ///   height
    /// </summary>
    function WithHeightPercentage(AValue: Double): ITgStoryAreaPosition;
    /// <summary>
    ///   Задаёт rotation_angle: The clockwise rotation angle of the rectangle, in degrees; 0-360
    /// </summary>
    function WithRotationAngle(AValue: Double): ITgStoryAreaPosition;
    /// <summary>
    ///   Задаёт corner_radius_percentage: The radius of the rectangle corner rounding, as a
    ///   percentage of the media width
    /// </summary>
    function WithCornerRadiusPercentage(AValue: Double): ITgStoryAreaPosition;
  end;

  /// <summary>Describes the physical address of a location.</summary>
  ITgLocationAddress = interface(ITgOutObject)
    ['{44FA2B3E-5456-568E-83D9-468D73F4CFC2}']
    /// <summary>
    ///   Задаёт country_code: The two-letter ISO 3166-1 alpha-2 country code of the country where
    ///   the location is located
    /// </summary>
    function WithCountryCode(const AValue: string): ITgLocationAddress;
    /// <summary>Задаёт state: Optional. State of the location</summary>
    function WithState(const AValue: string): ITgLocationAddress;
    /// <summary>Задаёт city: Optional. City of the location</summary>
    function WithCity(const AValue: string): ITgLocationAddress;
    /// <summary>Задаёт street: Optional. Street address of the location</summary>
    function WithStreet(const AValue: string): ITgLocationAddress;
  end;

  /// <summary>
  ///   Describes a story area pointing to a location. Currently, a story can have up to 10 location
  ///   areas.
  /// </summary>
  ITgStoryAreaTypeLocation = interface(ITgOutObject)
    ['{535940B4-799F-54FD-BC76-751B5DD66811}']
    /// <summary>Задаёт latitude: Location latitude in degrees</summary>
    function WithLatitude(AValue: Double): ITgStoryAreaTypeLocation;
    /// <summary>Задаёт longitude: Location longitude in degrees</summary>
    function WithLongitude(AValue: Double): ITgStoryAreaTypeLocation;
    /// <summary>Задаёт address: Optional. Address of the location</summary>
    function WithAddress(const AValue: ITgLocationAddress): ITgStoryAreaTypeLocation;
  end;

  /// <summary>
  ///   Describes a story area pointing to a suggested reaction. Currently, a story can have up to 5
  ///   suggested reaction areas.
  /// </summary>
  ITgStoryAreaTypeSuggestedReaction = interface(ITgOutObject)
    ['{6660B8FF-7EC2-5591-9AC9-C93C9F00B0FB}']
    /// <summary>Задаёт reaction_type: Type of the reaction</summary>
    function WithReactionType(const AValue: ITgReactionType): ITgStoryAreaTypeSuggestedReaction;
    /// <summary>
    ///   Задаёт is_dark: Optional. Pass True if the reaction area has a dark background
    /// </summary>
    function WithIsDark(AValue: Boolean): ITgStoryAreaTypeSuggestedReaction;
    /// <summary>
    ///   Задаёт is_flipped: Optional. Pass True if reaction area corner is flipped
    /// </summary>
    function WithIsFlipped(AValue: Boolean): ITgStoryAreaTypeSuggestedReaction;
  end;

  /// <summary>
  ///   Describes a story area pointing to an HTTP or tg:// link. Currently, a story can have up to
  ///   3 link areas.
  /// </summary>
  ITgStoryAreaTypeLink = interface(ITgOutObject)
    ['{6AB8AEBE-2411-5925-BEDD-97B5BC18DA8B}']
    /// <summary>
    ///   Задаёт url: HTTP or tg:// URL to be opened when the area is clicked
    /// </summary>
    function WithUrl(const AValue: string): ITgStoryAreaTypeLink;
  end;

  /// <summary>
  ///   Describes a story area containing weather information. Currently, a story can have up to 3
  ///   weather areas.
  /// </summary>
  ITgStoryAreaTypeWeather = interface(ITgOutObject)
    ['{D272B192-E84A-5D10-A974-AB778075C391}']
    /// <summary>Задаёт temperature: Temperature, in degree Celsius</summary>
    function WithTemperature(AValue: Double): ITgStoryAreaTypeWeather;
    /// <summary>Задаёт emoji: Emoji representing the weather</summary>
    function WithEmoji(const AValue: string): ITgStoryAreaTypeWeather;
    /// <summary>
    ///   Задаёт background_color: A color of the area background in the ARGB format
    /// </summary>
    function WithBackgroundColor(AValue: Integer): ITgStoryAreaTypeWeather;
  end;

  /// <summary>
  ///   Describes a story area pointing to a unique gift. Currently, a story can have at most 1
  ///   unique gift area.
  /// </summary>
  ITgStoryAreaTypeUniqueGift = interface(ITgOutObject)
    ['{C80A6E81-507C-5253-A86D-7EB565F55030}']
    /// <summary>Задаёт name: Unique name of the gift</summary>
    function WithName(const AValue: string): ITgStoryAreaTypeUniqueGift;
  end;

  /// <summary>Describes a clickable area on a story media.</summary>
  ITgStoryArea = interface(ITgOutObject)
    ['{60E96AD0-DA15-5395-B4C9-8EF1FA38A244}']
    /// <summary>Задаёт position: Position of the area</summary>
    function WithPosition(const AValue: ITgStoryAreaPosition): ITgStoryArea;
    /// <summary>Задаёт type: Type of the area</summary>
    function WithStoryAreaType(const AValue: TTgStoryAreaType): ITgStoryArea;
  end;

  /// <summary>Represents a location to which a chat is connected.</summary>
  ITgChatLocation = interface(ITgJsonObject)
    ['{24E7B4DC-EE87-5465-A896-41AA24FFDD62}']
    function GetLocation: ITgLocation;
    function GetAddress: string;
    /// <summary>
    ///   The location to which the supergroup is connected. Can't be a live location.
    /// </summary>
    property Location: ITgLocation read GetLocation;
    /// <summary>Location address; 1-64 characters, as defined by the chat owner</summary>
    property Address: string read GetAddress;
  end;

  /// <summary>
  ///   This object describes the type of a reaction. Виды (Kind, As*): ITgReactionTypeEmoji,
  ///   ITgReactionTypeCustomEmoji, ITgReactionTypePaid.
  /// </summary>
  ITgReactionType = interface(ITgJsonObject)
    ['{7045A15E-D214-52E9-A7C3-C66DFF2F72DB}']
    function GetKind: TTgReactionTypeKind;
    function GetKindText: string;
    /// <summary>ITgReactionTypeEmoji или nil, если объект другого вида.</summary>
    function AsEmoji: ITgReactionTypeEmoji;
    /// <summary>ITgReactionTypeCustomEmoji или nil, если объект другого вида.</summary>
    function AsCustomEmoji: ITgReactionTypeCustomEmoji;
    /// <summary>ITgReactionTypePaid или nil, если объект другого вида.</summary>
    function AsPaid: ITgReactionTypePaid;
    /// <summary>Вид объекта (Unknown — неизвестный этой версии библиотеки).</summary>
    property Kind: TTgReactionTypeKind read GetKind;
    /// <summary>
    ///   Значение поля type в JSON как есть (в т.ч. при Kind = Unknown); для вариантов-строк и
    ///   массивов — пустая строка.
    /// </summary>
    property KindText: string read GetKindText;
  end;

  /// <summary>The reaction is based on an emoji.</summary>
  ITgReactionTypeEmoji = interface(ITgReactionType)
    ['{91850038-55FB-53DC-92A1-78A50C8B5B99}']
    function GetEmoji: string;
    /// <summary>
    ///   Задаёт emoji: Reaction emoji. Currently, it can be one of "❤", "👍", "👎", "🔥", "🥰",
    ///   "👏", "😁", "🤔", "🤯", "😱", "🤬", "😢", "🎉", "🤩", "🤮", "💩", "🙏", "👌", "🕊", "🤡",
    ///   "🥱", "🥴", "😍", "🐳", "❤‍🔥", "🌚", "🌭", "💯", "🤣", "⚡", "🍌", "🏆", "💔", "🤨", "😐",
    ///   "🍓", "🍾", "💋", "🖕", "😈", "😴", "😭", "🤓", "👻", "👨‍💻", "👀", "🎃", "🙈", "😇",
    ///   "😨", "🤝", "✍", "🤗", "🫡", "🎅", "🎄", "☃", "💅", "🤪", "🗿", "🆒", "💘", "🙉", "🦄",
    ///   "😘", "💊", "🙊", "😎", "👾", "🤷‍♂", "🤷", "🤷‍♀", "😡". Значение копируется в момент
    ///   вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithEmoji(const AValue: string): ITgReactionTypeEmoji;
    /// <summary>
    ///   Reaction emoji. Currently, it can be one of "❤", "👍", "👎", "🔥", "🥰", "👏", "😁", "🤔",
    ///   "🤯", "😱", "🤬", "😢", "🎉", "🤩", "🤮", "💩", "🙏", "👌", "🕊", "🤡", "🥱", "🥴", "😍",
    ///   "🐳", "❤‍🔥", "🌚", "🌭", "💯", "🤣", "⚡", "🍌", "🏆", "💔", "🤨", "😐", "🍓", "🍾", "💋",
    ///   "🖕", "😈", "😴", "😭", "🤓", "👻", "👨‍💻", "👀", "🎃", "🙈", "😇", "😨", "🤝", "✍",
    ///   "🤗", "🫡", "🎅", "🎄", "☃", "💅", "🤪", "🗿", "🆒", "💘", "🙉", "🦄", "😘", "💊", "🙊",
    ///   "😎", "👾", "🤷‍♂", "🤷", "🤷‍♀", "😡".
    /// </summary>
    property Emoji: string read GetEmoji;
  end;

  /// <summary>The reaction is based on a custom emoji.</summary>
  ITgReactionTypeCustomEmoji = interface(ITgReactionType)
    ['{8F76B098-6CF3-5813-BF46-9F9C561C0694}']
    function GetCustomEmojiId: string;
    /// <summary>
    ///   Задаёт custom_emoji_id: Custom emoji identifier. Значение копируется в момент вызова:
    ///   последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithCustomEmojiId(const AValue: string): ITgReactionTypeCustomEmoji;
    /// <summary>Custom emoji identifier</summary>
    property CustomEmojiId: string read GetCustomEmojiId;
  end;

  /// <summary>The reaction is paid.</summary>
  ITgReactionTypePaid = interface(ITgReactionType)
    ['{9D03A9C1-7DB0-5E16-968E-0B664D7C4B6E}']
  end;

  /// <summary>
  ///   Represents a reaction added to a message along with the number of times it was added.
  /// </summary>
  ITgReactionCount = interface(ITgJsonObject)
    ['{CC47BE83-4D81-5E17-B325-6EC8681F1A26}']
    function GetReactionCountType: ITgReactionType;
    function GetTotalCount: Integer;
    /// <summary>Type of the reaction</summary>
    property ReactionCountType: ITgReactionType read GetReactionCountType;
    /// <summary>Number of times the reaction was added</summary>
    property TotalCount: Integer read GetTotalCount;
  end;

  /// <summary>
  ///   This object represents a change of a reaction on a message performed by a user.
  /// </summary>
  ITgMessageReactionUpdated = interface(ITgJsonObject)
    ['{E11EE1C8-B7AA-5F3A-BFD4-6FDE002F1B64}']
    function GetChat: ITgChat;
    function GetMessageId: Int64;
    function GetUser: ITgUser;
    function GetActorChat: ITgChat;
    function GetDate: Int64;
    function GetOldReaction: TArray<ITgReactionType>;
    function GetNewReaction: TArray<ITgReactionType>;
    /// <summary>The chat containing the message the user reacted to</summary>
    property Chat: ITgChat read GetChat;
    /// <summary>Unique identifier of the message inside the chat</summary>
    property MessageId: Int64 read GetMessageId;
    /// <summary>
    ///   Optional. The user that changed the reaction, if the user isn't anonymous
    /// </summary>
    property User: ITgUser read GetUser;
    /// <summary>
    ///   Optional. The chat on behalf of which the reaction was changed, if the user is anonymous
    /// </summary>
    property ActorChat: ITgChat read GetActorChat;
    /// <summary>Date of the change in Unix time</summary>
    property Date: Int64 read GetDate;
    /// <summary>Previous list of reaction types that were set by the user</summary>
    property OldReaction: TArray<ITgReactionType> read GetOldReaction;
    /// <summary>New list of reaction types that have been set by the user</summary>
    property NewReaction: TArray<ITgReactionType> read GetNewReaction;
  end;

  /// <summary>
  ///   This object represents reaction changes on a message with anonymous reactions.
  /// </summary>
  ITgMessageReactionCountUpdated = interface(ITgJsonObject)
    ['{FC640FB4-00A0-5722-826C-D8AED8759631}']
    function GetChat: ITgChat;
    function GetMessageId: Int64;
    function GetDate: Int64;
    function GetReactions: TArray<ITgReactionCount>;
    /// <summary>The chat containing the message</summary>
    property Chat: ITgChat read GetChat;
    /// <summary>Unique message identifier inside the chat</summary>
    property MessageId: Int64 read GetMessageId;
    /// <summary>Date of the change in Unix time</summary>
    property Date: Int64 read GetDate;
    /// <summary>List of reactions that are present on the message</summary>
    property Reactions: TArray<ITgReactionCount> read GetReactions;
  end;

  /// <summary>This object represents a forum topic.</summary>
  ITgForumTopic = interface(ITgJsonObject)
    ['{70597C58-68B3-5635-AFD0-E9C4BFE7B8A1}']
    function GetMessageThreadId: Int64;
    function GetName: string;
    function GetIconColor: Integer;
    function GetIconCustomEmojiId: string;
    function GetIsNameImplicit: Boolean;
    /// <summary>Unique identifier of the forum topic</summary>
    property MessageThreadId: Int64 read GetMessageThreadId;
    /// <summary>Name of the topic</summary>
    property Name: string read GetName;
    /// <summary>Color of the topic icon in RGB format</summary>
    property IconColor: Integer read GetIconColor;
    /// <summary>
    ///   Optional. Unique identifier of the custom emoji shown as the topic icon
    /// </summary>
    property IconCustomEmojiId: string read GetIconCustomEmojiId;
    /// <summary>
    ///   Optional. True, if the name of the topic wasn't specified explicitly by its creator and
    ///   likely needs to be changed by the bot
    /// </summary>
    property IsNameImplicit: Boolean read GetIsNameImplicit;
  end;

  /// <summary>This object describes the background of a gift.</summary>
  ITgGiftBackground = interface(ITgJsonObject)
    ['{7A9922A9-CA9D-5188-A004-B61B4793F322}']
    function GetCenterColor: Integer;
    function GetEdgeColor: Integer;
    function GetTextColor: Integer;
    /// <summary>Center color of the background in RGB format</summary>
    property CenterColor: Integer read GetCenterColor;
    /// <summary>Edge color of the background in RGB format</summary>
    property EdgeColor: Integer read GetEdgeColor;
    /// <summary>Text color of the background in RGB format</summary>
    property TextColor: Integer read GetTextColor;
  end;

  /// <summary>This object represents a gift that can be sent by the bot.</summary>
  ITgGift = interface(ITgJsonObject)
    ['{010117CC-F26E-5658-B077-0308682643C5}']
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
    /// <summary>Unique identifier of the gift</summary>
    property Id: string read GetId;
    /// <summary>The sticker that represents the gift</summary>
    property Sticker: ITgSticker read GetSticker;
    /// <summary>
    ///   The number of Telegram Stars that must be paid to send the sticker
    /// </summary>
    property StarCount: Integer read GetStarCount;
    /// <summary>
    ///   Optional. The number of Telegram Stars that must be paid to upgrade the gift to a unique
    ///   one
    /// </summary>
    property UpgradeStarCount: Integer read GetUpgradeStarCount;
    /// <summary>Поле upgrade_star_count присутствует.</summary>
    property HasUpgradeStarCount: Boolean read GetHasUpgradeStarCount;
    /// <summary>
    ///   Optional. True, if the gift can only be purchased by Telegram Premium subscribers
    /// </summary>
    property IsPremium: Boolean read GetIsPremium;
    /// <summary>
    ///   Optional. True, if the gift can be used (after being upgraded) to customize a user's
    ///   appearance
    /// </summary>
    property HasColors: Boolean read GetHasColors;
    /// <summary>
    ///   Optional. The total number of gifts of this type that can be sent by all users; for
    ///   limited gifts only
    /// </summary>
    property TotalCount: Integer read GetTotalCount;
    /// <summary>Поле total_count присутствует.</summary>
    property HasTotalCount: Boolean read GetHasTotalCount;
    /// <summary>
    ///   Optional. The number of remaining gifts of this type that can be sent by all users; for
    ///   limited gifts only
    /// </summary>
    property RemainingCount: Integer read GetRemainingCount;
    /// <summary>Поле remaining_count присутствует.</summary>
    property HasRemainingCount: Boolean read GetHasRemainingCount;
    /// <summary>
    ///   Optional. The total number of gifts of this type that can be sent by the bot; for limited
    ///   gifts only
    /// </summary>
    property PersonalTotalCount: Integer read GetPersonalTotalCount;
    /// <summary>Поле personal_total_count присутствует.</summary>
    property HasPersonalTotalCount: Boolean read GetHasPersonalTotalCount;
    /// <summary>
    ///   Optional. The number of remaining gifts of this type that can be sent by the bot; for
    ///   limited gifts only
    /// </summary>
    property PersonalRemainingCount: Integer read GetPersonalRemainingCount;
    /// <summary>Поле personal_remaining_count присутствует.</summary>
    property HasPersonalRemainingCount: Boolean read GetHasPersonalRemainingCount;
    /// <summary>Optional. Background of the gift</summary>
    property Background: ITgGiftBackground read GetBackground;
    /// <summary>
    ///   Optional. The total number of different unique gifts that can be obtained by upgrading the
    ///   gift
    /// </summary>
    property UniqueGiftVariantCount: Integer read GetUniqueGiftVariantCount;
    /// <summary>Поле unique_gift_variant_count присутствует.</summary>
    property HasUniqueGiftVariantCount: Boolean read GetHasUniqueGiftVariantCount;
    /// <summary>Optional. Information about the chat that published the gift</summary>
    property PublisherChat: ITgChat read GetPublisherChat;
  end;

  /// <summary>This object represent a list of gifts.</summary>
  ITgGifts = interface(ITgJsonObject)
    ['{FEEA9086-6A99-5360-80E9-ECA7FAD95C65}']
    function GetGifts: TArray<ITgGift>;
    /// <summary>The list of gifts</summary>
    property Gifts: TArray<ITgGift> read GetGifts;
  end;

  /// <summary>This object describes the model of a unique gift.</summary>
  ITgUniqueGiftModel = interface(ITgJsonObject)
    ['{D86E0E39-0143-55A4-860D-A034ACBA7992}']
    function GetName: string;
    function GetSticker: ITgSticker;
    function GetRarityPerMille: Integer;
    function GetRarity: string;
    /// <summary>Name of the model</summary>
    property Name: string read GetName;
    /// <summary>The sticker that represents the unique gift</summary>
    property Sticker: ITgSticker read GetSticker;
    /// <summary>
    ///   The number of unique gifts that receive this model for every 1000 gift upgrades. Always 0
    ///   for crafted gifts.
    /// </summary>
    property RarityPerMille: Integer read GetRarityPerMille;
    /// <summary>
    ///   Optional. Rarity of the model if it is a crafted model. Currently, can be “uncommon”,
    ///   “rare”, “epic”, or “legendary”.
    /// </summary>
    property Rarity: string read GetRarity;
  end;

  /// <summary>
  ///   This object describes the symbol shown on the pattern of a unique gift.
  /// </summary>
  ITgUniqueGiftSymbol = interface(ITgJsonObject)
    ['{7AF9E710-85F6-5475-8524-5C80AE6A006B}']
    function GetName: string;
    function GetSticker: ITgSticker;
    function GetRarityPerMille: Integer;
    /// <summary>Name of the symbol</summary>
    property Name: string read GetName;
    /// <summary>The sticker that represents the unique gift</summary>
    property Sticker: ITgSticker read GetSticker;
    /// <summary>
    ///   The number of unique gifts that receive this model for every 1000 gifts upgraded
    /// </summary>
    property RarityPerMille: Integer read GetRarityPerMille;
  end;

  /// <summary>This object describes the colors of the backdrop of a unique gift.</summary>
  ITgUniqueGiftBackdropColors = interface(ITgJsonObject)
    ['{4CCEA9CC-A919-5758-8C54-32FF21BADF98}']
    function GetCenterColor: Integer;
    function GetEdgeColor: Integer;
    function GetSymbolColor: Integer;
    function GetTextColor: Integer;
    /// <summary>The color in the center of the backdrop in RGB format</summary>
    property CenterColor: Integer read GetCenterColor;
    /// <summary>The color on the edges of the backdrop in RGB format</summary>
    property EdgeColor: Integer read GetEdgeColor;
    /// <summary>The color to be applied to the symbol in RGB format</summary>
    property SymbolColor: Integer read GetSymbolColor;
    /// <summary>The color for the text on the backdrop in RGB format</summary>
    property TextColor: Integer read GetTextColor;
  end;

  /// <summary>This object describes the backdrop of a unique gift.</summary>
  ITgUniqueGiftBackdrop = interface(ITgJsonObject)
    ['{8E9ABC9E-2A74-58F0-B633-C9BC90318360}']
    function GetName: string;
    function GetColors: ITgUniqueGiftBackdropColors;
    function GetRarityPerMille: Integer;
    /// <summary>Name of the backdrop</summary>
    property Name: string read GetName;
    /// <summary>Colors of the backdrop</summary>
    property Colors: ITgUniqueGiftBackdropColors read GetColors;
    /// <summary>
    ///   The number of unique gifts that receive this backdrop for every 1000 gifts upgraded
    /// </summary>
    property RarityPerMille: Integer read GetRarityPerMille;
  end;

  /// <summary>
  ///   This object contains information about the color scheme for a user's name, message replies
  ///   and link previews based on a unique gift.
  /// </summary>
  ITgUniqueGiftColors = interface(ITgJsonObject)
    ['{AD770BDD-C72A-5448-BC53-7222A7CC6CBE}']
    function GetModelCustomEmojiId: string;
    function GetSymbolCustomEmojiId: string;
    function GetLightThemeMainColor: Integer;
    function GetLightThemeOtherColors: TArray<Integer>;
    function GetDarkThemeMainColor: Integer;
    function GetDarkThemeOtherColors: TArray<Integer>;
    /// <summary>Custom emoji identifier of the unique gift's model</summary>
    property ModelCustomEmojiId: string read GetModelCustomEmojiId;
    /// <summary>Custom emoji identifier of the unique gift's symbol</summary>
    property SymbolCustomEmojiId: string read GetSymbolCustomEmojiId;
    /// <summary>Main color used in light themes; RGB format</summary>
    property LightThemeMainColor: Integer read GetLightThemeMainColor;
    /// <summary>List of 1-3 additional colors used in light themes; RGB format</summary>
    property LightThemeOtherColors: TArray<Integer> read GetLightThemeOtherColors;
    /// <summary>Main color used in dark themes; RGB format</summary>
    property DarkThemeMainColor: Integer read GetDarkThemeMainColor;
    /// <summary>List of 1-3 additional colors used in dark themes; RGB format</summary>
    property DarkThemeOtherColors: TArray<Integer> read GetDarkThemeOtherColors;
  end;

  /// <summary>
  ///   This object describes a unique gift that was upgraded from a regular gift.
  /// </summary>
  ITgUniqueGift = interface(ITgJsonObject)
    ['{2B4F3673-8709-5DE3-936B-B543569B6874}']
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
    /// <summary>Identifier of the regular gift from which the gift was upgraded</summary>
    property GiftId: string read GetGiftId;
    /// <summary>
    ///   Human-readable name of the regular gift from which this unique gift was upgraded
    /// </summary>
    property BaseName: string read GetBaseName;
    /// <summary>
    ///   Unique name of the gift. This name can be used in https://t.me/nft/... links and story
    ///   areas.
    /// </summary>
    property Name: string read GetName;
    /// <summary>
    ///   Unique number of the upgraded gift among gifts upgraded from the same regular gift
    /// </summary>
    property Number: Integer read GetNumber;
    /// <summary>Model of the gift</summary>
    property Model: ITgUniqueGiftModel read GetModel;
    /// <summary>Symbol of the gift</summary>
    property Symbol: ITgUniqueGiftSymbol read GetSymbol;
    /// <summary>Backdrop of the gift</summary>
    property Backdrop: ITgUniqueGiftBackdrop read GetBackdrop;
    /// <summary>
    ///   Optional. True, if the original regular gift was exclusively purchaseable by Telegram
    ///   Premium subscribers
    /// </summary>
    property IsPremium: Boolean read GetIsPremium;
    /// <summary>
    ///   Optional. True, if the gift was used to craft another gift and isn't available anymore
    /// </summary>
    property IsBurned: Boolean read GetIsBurned;
    /// <summary>
    ///   Optional. True, if the gift is assigned from the TON blockchain and can't be resold or
    ///   transferred in Telegram
    /// </summary>
    property IsFromBlockchain: Boolean read GetIsFromBlockchain;
    /// <summary>
    ///   Optional. The color scheme that can be used by the gift's owner for the chat's name,
    ///   replies to messages and link previews; for business account gifts and gifts that are
    ///   currently on sale only
    /// </summary>
    property Colors: ITgUniqueGiftColors read GetColors;
    /// <summary>Optional. Information about the chat that published the gift</summary>
    property PublisherChat: ITgChat read GetPublisherChat;
  end;

  /// <summary>
  ///   Describes a service message about a regular gift that was sent or received.
  /// </summary>
  ITgGiftInfo = interface(ITgJsonObject)
    ['{DC391E8B-441A-5C5F-9235-F75B71B6CD8E}']
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
    /// <summary>Information about the gift</summary>
    property Gift: ITgGift read GetGift;
    /// <summary>
    ///   Optional. Unique identifier of the received gift for the bot; only present for gifts
    ///   received on behalf of business accounts
    /// </summary>
    property OwnedGiftId: string read GetOwnedGiftId;
    /// <summary>
    ///   Optional. Number of Telegram Stars that can be claimed by the receiver by converting the
    ///   gift; omitted if conversion to Telegram Stars is impossible
    /// </summary>
    property ConvertStarCount: Integer read GetConvertStarCount;
    /// <summary>Поле convert_star_count присутствует.</summary>
    property HasConvertStarCount: Boolean read GetHasConvertStarCount;
    /// <summary>
    ///   Optional. Number of Telegram Stars that were prepaid for the ability to upgrade the gift
    /// </summary>
    property PrepaidUpgradeStarCount: Integer read GetPrepaidUpgradeStarCount;
    /// <summary>Поле prepaid_upgrade_star_count присутствует.</summary>
    property HasPrepaidUpgradeStarCount: Boolean read GetHasPrepaidUpgradeStarCount;
    /// <summary>
    ///   Optional. True, if the gift's upgrade was purchased after the gift was sent
    /// </summary>
    property IsUpgradeSeparate: Boolean read GetIsUpgradeSeparate;
    /// <summary>Optional. True, if the gift can be upgraded to a unique gift</summary>
    property CanBeUpgraded: Boolean read GetCanBeUpgraded;
    /// <summary>Optional. Text of the message that was added to the gift</summary>
    property Text: string read GetText;
    /// <summary>Optional. Special entities that appear in the text</summary>
    property Entities: TArray<ITgMessageEntity> read GetEntities;
    /// <summary>
    ///   Optional. True, if the sender and gift text are shown only to the gift receiver;
    ///   otherwise, everyone will be able to see them
    /// </summary>
    property IsPrivate: Boolean read GetIsPrivate;
    /// <summary>
    ///   Optional. Unique number reserved for this gift when upgraded. See the number field in
    ///   UniqueGift.
    /// </summary>
    property UniqueGiftNumber: Integer read GetUniqueGiftNumber;
    /// <summary>Поле unique_gift_number присутствует.</summary>
    property HasUniqueGiftNumber: Boolean read GetHasUniqueGiftNumber;
  end;

  /// <summary>
  ///   Describes a service message about a unique gift that was sent or received.
  /// </summary>
  ITgUniqueGiftInfo = interface(ITgJsonObject)
    ['{9912209F-90AD-5319-9956-07D3C5AFF57A}']
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
    /// <summary>Information about the gift</summary>
    property Gift: ITgUniqueGift read GetGift;
    /// <summary>
    ///   Origin of the gift. Currently, either “upgrade” for gifts upgraded from regular gifts,
    ///   “transfer” for gifts transferred from other users or channels, “resale” for gifts bought
    ///   from other users, “gifted_upgrade” for upgrades purchased after the gift was sent, or
    ///   “offer” for gifts bought or sold through gift purchase offers.
    /// </summary>
    property Origin: string read GetOrigin;
    /// <summary>Optional. Text of the message that was added to the gift</summary>
    property Text: string read GetText;
    /// <summary>Optional. Special entities that appear in the text</summary>
    property Entities: TArray<ITgMessageEntity> read GetEntities;
    /// <summary>
    ///   Optional. True, if the sender and gift text are shown only to the gift receiver;
    ///   otherwise, everyone will be able to see them
    /// </summary>
    property IsPrivate: Boolean read GetIsPrivate;
    /// <summary>
    ///   Optional. For gifts bought from other users, the currency in which the payment for the
    ///   gift was done. Currently, one of “XTR” for Telegram Stars or “TON” for TON grams.
    /// </summary>
    property LastResaleCurrency: string read GetLastResaleCurrency;
    /// <summary>
    ///   Optional. For gifts bought from other users, the price paid for the gift in either
    ///   Telegram Stars or nanograms
    /// </summary>
    property LastResaleAmount: Integer read GetLastResaleAmount;
    /// <summary>Поле last_resale_amount присутствует.</summary>
    property HasLastResaleAmount: Boolean read GetHasLastResaleAmount;
    /// <summary>
    ///   Optional. Unique identifier of the received gift for the bot; only present for gifts
    ///   received on behalf of business accounts
    /// </summary>
    property OwnedGiftId: string read GetOwnedGiftId;
    /// <summary>
    ///   Optional. Number of Telegram Stars that must be paid to transfer the gift; omitted if the
    ///   bot cannot transfer the gift
    /// </summary>
    property TransferStarCount: Integer read GetTransferStarCount;
    /// <summary>Поле transfer_star_count присутствует.</summary>
    property HasTransferStarCount: Boolean read GetHasTransferStarCount;
    /// <summary>
    ///   Optional. Point in time (Unix timestamp) when the gift can be transferred. If it is in the
    ///   past, then the gift can be transferred now.
    /// </summary>
    property NextTransferDate: Int64 read GetNextTransferDate;
    /// <summary>Поле next_transfer_date присутствует.</summary>
    property HasNextTransferDate: Boolean read GetHasNextTransferDate;
  end;

  /// <summary>
  ///   This object describes a gift received and owned by a user or a chat. Виды (Kind, As*):
  ///   ITgOwnedGiftRegular, ITgOwnedGiftUnique.
  /// </summary>
  ITgOwnedGift = interface(ITgJsonObject)
    ['{3F4DD313-E022-5B30-97D0-308561FDE6B7}']
    function GetKind: TTgOwnedGiftKind;
    function GetKindText: string;
    function GetOwnedGiftId: string;
    function GetSenderUser: ITgUser;
    function GetSendDate: Int64;
    function GetIsSaved: Boolean;
    /// <summary>ITgOwnedGiftRegular или nil, если объект другого вида.</summary>
    function AsRegular: ITgOwnedGiftRegular;
    /// <summary>ITgOwnedGiftUnique или nil, если объект другого вида.</summary>
    function AsUnique: ITgOwnedGiftUnique;
    /// <summary>Вид объекта (Unknown — неизвестный этой версии библиотеки).</summary>
    property Kind: TTgOwnedGiftKind read GetKind;
    /// <summary>
    ///   Значение поля type в JSON как есть (в т.ч. при Kind = Unknown); для вариантов-строк и
    ///   массивов — пустая строка.
    /// </summary>
    property KindText: string read GetKindText;
    /// <summary>
    ///   Optional. Unique identifier of the gift for the bot; for gifts received on behalf of
    ///   business accounts only
    /// </summary>
    property OwnedGiftId: string read GetOwnedGiftId;
    /// <summary>Optional. Sender of the gift if it is a known user</summary>
    property SenderUser: ITgUser read GetSenderUser;
    /// <summary>Date the gift was sent in Unix time</summary>
    property SendDate: Int64 read GetSendDate;
    /// <summary>
    ///   Optional. True, if the gift is displayed on the account's profile page; for gifts received
    ///   on behalf of business accounts only
    /// </summary>
    property IsSaved: Boolean read GetIsSaved;
  end;

  /// <summary>Describes a regular gift owned by a user or a chat.</summary>
  ITgOwnedGiftRegular = interface(ITgOwnedGift)
    ['{6A45A86C-F6D5-52F0-ABCB-F244B3C6E6E1}']
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
    /// <summary>Information about the regular gift</summary>
    property Gift: ITgGift read GetGift;
    /// <summary>Optional. Text of the message that was added to the gift</summary>
    property Text: string read GetText;
    /// <summary>Optional. Special entities that appear in the text</summary>
    property Entities: TArray<ITgMessageEntity> read GetEntities;
    /// <summary>
    ///   Optional. True, if the sender and gift text are shown only to the gift receiver;
    ///   otherwise, everyone will be able to see them
    /// </summary>
    property IsPrivate: Boolean read GetIsPrivate;
    /// <summary>
    ///   Optional. True, if the gift can be upgraded to a unique gift; for gifts received on behalf
    ///   of business accounts only
    /// </summary>
    property CanBeUpgraded: Boolean read GetCanBeUpgraded;
    /// <summary>
    ///   Optional. True, if the gift was refunded and isn't available anymore
    /// </summary>
    property WasRefunded: Boolean read GetWasRefunded;
    /// <summary>
    ///   Optional. Number of Telegram Stars that can be claimed by the receiver instead of the
    ///   gift; omitted if the gift cannot be converted to Telegram Stars; for gifts received on
    ///   behalf of business accounts only
    /// </summary>
    property ConvertStarCount: Integer read GetConvertStarCount;
    /// <summary>Поле convert_star_count присутствует.</summary>
    property HasConvertStarCount: Boolean read GetHasConvertStarCount;
    /// <summary>
    ///   Optional. Number of Telegram Stars that were paid for the ability to upgrade the gift
    /// </summary>
    property PrepaidUpgradeStarCount: Integer read GetPrepaidUpgradeStarCount;
    /// <summary>Поле prepaid_upgrade_star_count присутствует.</summary>
    property HasPrepaidUpgradeStarCount: Boolean read GetHasPrepaidUpgradeStarCount;
    /// <summary>
    ///   Optional. True, if the gift's upgrade was purchased after the gift was sent; for gifts
    ///   received on behalf of business accounts only
    /// </summary>
    property IsUpgradeSeparate: Boolean read GetIsUpgradeSeparate;
    /// <summary>
    ///   Optional. Unique number reserved for this gift when upgraded. See the number field in
    ///   UniqueGift.
    /// </summary>
    property UniqueGiftNumber: Integer read GetUniqueGiftNumber;
    /// <summary>Поле unique_gift_number присутствует.</summary>
    property HasUniqueGiftNumber: Boolean read GetHasUniqueGiftNumber;
  end;

  /// <summary>Describes a unique gift received and owned by a user or a chat.</summary>
  ITgOwnedGiftUnique = interface(ITgOwnedGift)
    ['{26A18099-7630-56E7-913E-B7960ECC1E98}']
    function GetGift: ITgUniqueGift;
    function GetCanBeTransferred: Boolean;
    function GetTransferStarCount: Integer;
    function GetHasTransferStarCount: Boolean;
    function GetNextTransferDate: Int64;
    function GetHasNextTransferDate: Boolean;
    /// <summary>Information about the unique gift</summary>
    property Gift: ITgUniqueGift read GetGift;
    /// <summary>
    ///   Optional. True, if the gift can be transferred to another owner; for gifts received on
    ///   behalf of business accounts only
    /// </summary>
    property CanBeTransferred: Boolean read GetCanBeTransferred;
    /// <summary>
    ///   Optional. Number of Telegram Stars that must be paid to transfer the gift; omitted if the
    ///   bot cannot transfer the gift
    /// </summary>
    property TransferStarCount: Integer read GetTransferStarCount;
    /// <summary>Поле transfer_star_count присутствует.</summary>
    property HasTransferStarCount: Boolean read GetHasTransferStarCount;
    /// <summary>
    ///   Optional. Point in time (Unix timestamp) when the gift can be transferred. If it is in the
    ///   past, then the gift can be transferred now.
    /// </summary>
    property NextTransferDate: Int64 read GetNextTransferDate;
    /// <summary>Поле next_transfer_date присутствует.</summary>
    property HasNextTransferDate: Boolean read GetHasNextTransferDate;
  end;

  /// <summary>Contains the list of gifts received and owned by a user or a chat.</summary>
  ITgOwnedGifts = interface(ITgJsonObject)
    ['{FAA16AD2-F854-555D-8033-85953275F20B}']
    function GetTotalCount: Integer;
    function GetGifts: TArray<ITgOwnedGift>;
    function GetNextOffset: string;
    /// <summary>The total number of gifts owned by the user or the chat</summary>
    property TotalCount: Integer read GetTotalCount;
    /// <summary>The list of gifts</summary>
    property Gifts: TArray<ITgOwnedGift> read GetGifts;
    /// <summary>
    ///   Optional. Offset for the next request. If empty, then there are no more results.
    /// </summary>
    property NextOffset: string read GetNextOffset;
  end;

  /// <summary>This object describes the access settings of a bot.</summary>
  ITgBotAccessSettings = interface(ITgJsonObject)
    ['{3D6973EF-CD6B-5993-B40F-E25BDE9AC8E7}']
    function GetIsAccessRestricted: Boolean;
    function GetAddedUsers: TArray<ITgUser>;
    /// <summary>
    ///   True, if only selected users can access the bot. The bot's owner can always access it.
    /// </summary>
    property IsAccessRestricted: Boolean read GetIsAccessRestricted;
    /// <summary>
    ///   Optional. The list of other users who have access to the bot if the access is restricted
    /// </summary>
    property AddedUsers: TArray<ITgUser> read GetAddedUsers;
  end;

  /// <summary>
  ///   This object describes the types of gifts that can be gifted to a user or a chat.
  /// </summary>
  ITgAcceptedGiftTypes = interface(ITgJsonObject)
    ['{00917428-98ED-59CA-BF0D-93FFE12D2ECE}']
    function GetUnlimitedGifts: Boolean;
    function GetLimitedGifts: Boolean;
    function GetUniqueGifts: Boolean;
    function GetPremiumSubscription: Boolean;
    function GetGiftsFromChannels: Boolean;
    /// <summary>
    ///   Задаёт unlimited_gifts: True, if unlimited regular gifts are accepted. Значение копируется
    ///   в момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithUnlimitedGifts(AValue: Boolean): ITgAcceptedGiftTypes;
    /// <summary>
    ///   Задаёт limited_gifts: True, if limited regular gifts are accepted. Значение копируется в
    ///   момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithLimitedGifts(AValue: Boolean): ITgAcceptedGiftTypes;
    /// <summary>
    ///   Задаёт unique_gifts: True, if unique gifts or gifts that can be upgraded to unique for
    ///   free are accepted. Значение копируется в момент вызова: последующие изменения переданного
    ///   объекта на этот не влияют.
    /// </summary>
    function WithUniqueGifts(AValue: Boolean): ITgAcceptedGiftTypes;
    /// <summary>
    ///   Задаёт premium_subscription: True, if a Telegram Premium subscription is accepted.
    ///   Значение копируется в момент вызова: последующие изменения переданного объекта на этот не
    ///   влияют.
    /// </summary>
    function WithPremiumSubscription(AValue: Boolean): ITgAcceptedGiftTypes;
    /// <summary>
    ///   Задаёт gifts_from_channels: True, if transfers of unique gifts from channels are accepted.
    ///   Значение копируется в момент вызова: последующие изменения переданного объекта на этот не
    ///   влияют.
    /// </summary>
    function WithGiftsFromChannels(AValue: Boolean): ITgAcceptedGiftTypes;
    /// <summary>True, if unlimited regular gifts are accepted</summary>
    property UnlimitedGifts: Boolean read GetUnlimitedGifts;
    /// <summary>True, if limited regular gifts are accepted</summary>
    property LimitedGifts: Boolean read GetLimitedGifts;
    /// <summary>
    ///   True, if unique gifts or gifts that can be upgraded to unique for free are accepted
    /// </summary>
    property UniqueGifts: Boolean read GetUniqueGifts;
    /// <summary>True, if a Telegram Premium subscription is accepted</summary>
    property PremiumSubscription: Boolean read GetPremiumSubscription;
    /// <summary>True, if transfers of unique gifts from channels are accepted</summary>
    property GiftsFromChannels: Boolean read GetGiftsFromChannels;
  end;

  /// <summary>Describes an amount of Telegram Stars.</summary>
  ITgStarAmount = interface(ITgJsonObject)
    ['{082C4F23-1CFF-5446-A36C-469EA9476791}']
    function GetAmount: Integer;
    function GetNanostarAmount: Integer;
    function GetHasNanostarAmount: Boolean;
    /// <summary>Integer amount of Telegram Stars, rounded to 0; can be negative</summary>
    property Amount: Integer read GetAmount;
    /// <summary>
    ///   Optional. The number of 1/1000000000 shares of Telegram Stars; from -999999999 to
    ///   999999999; can be negative if and only if amount is non-positive
    /// </summary>
    property NanostarAmount: Integer read GetNanostarAmount;
    /// <summary>Поле nanostar_amount присутствует.</summary>
    property HasNanostarAmount: Boolean read GetHasNanostarAmount;
  end;

  /// <summary>This object represents a bot command.</summary>
  ITgBotCommand = interface(ITgJsonObject)
    ['{1E6EBFB4-72AF-520E-AFE3-CF28CD84CD88}']
    function GetCommand: string;
    function GetDescription: string;
    function GetIsEphemeral: Boolean;
    function GetHasIsEphemeral: Boolean;
    /// <summary>
    ///   Задаёт command: Text of the command; 1-32 characters. Can contain only lowercase English
    ///   letters, digits and underscores. Значение копируется в момент вызова: последующие
    ///   изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithCommand(const AValue: string): ITgBotCommand;
    /// <summary>
    ///   Задаёт description: Description of the command; 1-256 characters. Значение копируется в
    ///   момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithDescription(const AValue: string): ITgBotCommand;
    /// <summary>
    ///   Задаёт is_ephemeral: Optional. True, if the command sends an ephemeral message, which can
    ///   be seen only by the sender of the message and the bot. Значение копируется в момент
    ///   вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithIsEphemeral(AValue: Boolean): ITgBotCommand;
    /// <summary>
    ///   Text of the command; 1-32 characters. Can contain only lowercase English letters, digits
    ///   and underscores.
    /// </summary>
    property Command: string read GetCommand;
    /// <summary>Description of the command; 1-256 characters</summary>
    property Description: string read GetDescription;
    /// <summary>
    ///   Optional. True, if the command sends an ephemeral message, which can be seen only by the
    ///   sender of the message and the bot
    /// </summary>
    property IsEphemeral: Boolean read GetIsEphemeral;
    /// <summary>Поле is_ephemeral присутствует.</summary>
    property HasIsEphemeral: Boolean read GetHasIsEphemeral;
  end;

  /// <summary>
  ///   Represents the default scope of bot commands. Default commands are used if no commands with
  ///   a narrower scope are specified for the user.
  /// </summary>
  ITgBotCommandScopeDefault = interface(ITgOutObject)
    ['{86B067A0-A5A5-5257-99D6-D5ABA6B32194}']
  end;

  /// <summary>Represents the scope of bot commands, covering all private chats.</summary>
  ITgBotCommandScopeAllPrivateChats = interface(ITgOutObject)
    ['{D5C1CB16-DB81-5F0C-AE54-EA408DDCF7F6}']
  end;

  /// <summary>
  ///   Represents the scope of bot commands, covering all group and supergroup chats.
  /// </summary>
  ITgBotCommandScopeAllGroupChats = interface(ITgOutObject)
    ['{AFB130E0-96CC-582C-A9B8-F93D17C751EC}']
  end;

  /// <summary>
  ///   Represents the scope of bot commands, covering all group and supergroup chat administrators.
  /// </summary>
  ITgBotCommandScopeAllChatAdministrators = interface(ITgOutObject)
    ['{9C167924-47E5-5510-AE86-E12430350EDB}']
  end;

  /// <summary>Represents the scope of bot commands, covering a specific chat.</summary>
  ITgBotCommandScopeChat = interface(ITgOutObject)
    ['{8BCE1BFF-4DD8-5539-9CDE-0D945ED1303C}']
    /// <summary>
    ///   Задаёт chat_id: Unique identifier for the target chat or username of the target supergroup
    ///   in the format @username. Channel direct messages chats and channel chats aren't supported.
    /// </summary>
    function WithChatId(const AValue: TTgChatId): ITgBotCommandScopeChat;
  end;

  /// <summary>
  ///   Represents the scope of bot commands, covering all administrators of a specific group or
  ///   supergroup chat.
  /// </summary>
  ITgBotCommandScopeChatAdministrators = interface(ITgOutObject)
    ['{693982C7-224B-57C3-A2AD-A6AD0A40825A}']
    /// <summary>
    ///   Задаёт chat_id: Unique identifier for the target chat or username of the target supergroup
    ///   in the format @username. Channel direct messages chats and channel chats aren't supported.
    /// </summary>
    function WithChatId(const AValue: TTgChatId): ITgBotCommandScopeChatAdministrators;
  end;

  /// <summary>
  ///   Represents the scope of bot commands, covering a specific member of a group or supergroup
  ///   chat.
  /// </summary>
  ITgBotCommandScopeChatMember = interface(ITgOutObject)
    ['{56D98D4D-FE17-5F07-A3DF-A7A8BE061A0E}']
    /// <summary>
    ///   Задаёт chat_id: Unique identifier for the target chat or username of the target supergroup
    ///   in the format @username. Channel direct messages chats and channel chats aren't supported.
    /// </summary>
    function WithChatId(const AValue: TTgChatId): ITgBotCommandScopeChatMember;
    /// <summary>Задаёт user_id: Unique identifier of the target user</summary>
    function WithUserId(AValue: Int64): ITgBotCommandScopeChatMember;
  end;

  /// <summary>This object represents the bot's name.</summary>
  ITgBotName = interface(ITgJsonObject)
    ['{E92475EF-AC62-5364-A8BB-4993B43C1D88}']
    function GetName: string;
    /// <summary>The bot's name</summary>
    property Name: string read GetName;
  end;

  /// <summary>This object represents the bot's description.</summary>
  ITgBotDescription = interface(ITgJsonObject)
    ['{A4F7023C-ED39-5C69-93DE-65F41836F36A}']
    function GetDescription: string;
    /// <summary>The bot's description</summary>
    property Description: string read GetDescription;
  end;

  /// <summary>This object represents the bot's short description.</summary>
  ITgBotShortDescription = interface(ITgJsonObject)
    ['{18424A4E-FB9A-5FCE-BD9B-21242A906511}']
    function GetShortDescription: string;
    /// <summary>The bot's short description</summary>
    property ShortDescription: string read GetShortDescription;
  end;

  /// <summary>
  ///   This object describes the bot's menu button in a private chat. If a menu button other than
  ///   MenuButtonDefault is set for a private chat, then it is applied in the chat. Otherwise the
  ///   default menu button is applied. By default, the menu button opens the list of bot commands.
  ///   Виды (Kind, As*): ITgMenuButtonCommands, ITgMenuButtonWebApp, ITgMenuButtonDefault.
  /// </summary>
  ITgMenuButton = interface(ITgJsonObject)
    ['{B39559A9-E722-536A-A758-FBC5C795442E}']
    function GetKind: TTgMenuButtonKind;
    function GetKindText: string;
    /// <summary>ITgMenuButtonCommands или nil, если объект другого вида.</summary>
    function AsCommands: ITgMenuButtonCommands;
    /// <summary>ITgMenuButtonWebApp или nil, если объект другого вида.</summary>
    function AsWebApp: ITgMenuButtonWebApp;
    /// <summary>ITgMenuButtonDefault или nil, если объект другого вида.</summary>
    function AsDefault: ITgMenuButtonDefault;
    /// <summary>Вид объекта (Unknown — неизвестный этой версии библиотеки).</summary>
    property Kind: TTgMenuButtonKind read GetKind;
    /// <summary>
    ///   Значение поля type в JSON как есть (в т.ч. при Kind = Unknown); для вариантов-строк и
    ///   массивов — пустая строка.
    /// </summary>
    property KindText: string read GetKindText;
  end;

  /// <summary>Represents a menu button, which opens the bot's list of commands.</summary>
  ITgMenuButtonCommands = interface(ITgMenuButton)
    ['{A734B8BF-39FF-54F3-80DC-8A5F4769C53C}']
  end;

  /// <summary>Represents a menu button, which launches a Web App.</summary>
  ITgMenuButtonWebApp = interface(ITgMenuButton)
    ['{A11C4ACE-D7DD-5983-BCD0-4DA7FED88F04}']
    function GetText: string;
    function GetWebApp: ITgWebAppInfo;
    /// <summary>
    ///   Задаёт text: Text on the button. Значение копируется в момент вызова: последующие
    ///   изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithText(const AValue: string): ITgMenuButtonWebApp;
    /// <summary>
    ///   Задаёт web_app: Description of the Web App that will be launched when the user presses the
    ///   button. The Web App will be able to send an arbitrary message on behalf of the user using
    ///   the method answerWebAppQuery. Alternatively, a t.me link to a Web App of the bot can be
    ///   specified in the object instead of the Web App's URL, in which case the Web App will be
    ///   opened as if the user pressed the link. Значение копируется в момент вызова: последующие
    ///   изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithWebApp(const AValue: ITgWebAppInfo): ITgMenuButtonWebApp;
    /// <summary>Text on the button</summary>
    property Text: string read GetText;
    /// <summary>
    ///   Description of the Web App that will be launched when the user presses the button. The Web
    ///   App will be able to send an arbitrary message on behalf of the user using the method
    ///   answerWebAppQuery. Alternatively, a t.me link to a Web App of the bot can be specified in
    ///   the object instead of the Web App's URL, in which case the Web App will be opened as if
    ///   the user pressed the link.
    /// </summary>
    property WebApp: ITgWebAppInfo read GetWebApp;
  end;

  /// <summary>Describes that no specific value for the menu button was set.</summary>
  ITgMenuButtonDefault = interface(ITgMenuButton)
    ['{65911A2F-60B5-58CF-B8EA-6BC4B10D3679}']
  end;

  /// <summary>
  ///   This object describes the source of a chat boost. Виды (Kind, As*):
  ///   ITgChatBoostSourcePremium, ITgChatBoostSourceGiftCode, ITgChatBoostSourceGiveaway.
  /// </summary>
  ITgChatBoostSource = interface(ITgJsonObject)
    ['{7106D179-6262-5AF6-8322-0BBAD38930FB}']
    function GetKind: TTgChatBoostSourceKind;
    function GetKindText: string;
    function GetSource: string;
    function GetUser: ITgUser;
    /// <summary>ITgChatBoostSourcePremium или nil, если объект другого вида.</summary>
    function AsPremium: ITgChatBoostSourcePremium;
    /// <summary>ITgChatBoostSourceGiftCode или nil, если объект другого вида.</summary>
    function AsGiftCode: ITgChatBoostSourceGiftCode;
    /// <summary>ITgChatBoostSourceGiveaway или nil, если объект другого вида.</summary>
    function AsGiveaway: ITgChatBoostSourceGiveaway;
    /// <summary>Вид объекта (Unknown — неизвестный этой версии библиотеки).</summary>
    property Kind: TTgChatBoostSourceKind read GetKind;
    /// <summary>
    ///   Значение поля source в JSON как есть (в т.ч. при Kind = Unknown); для вариантов-строк и
    ///   массивов — пустая строка.
    /// </summary>
    property KindText: string read GetKindText;
    /// <summary>Значение поля source в JSON; вид объекта — свойство Kind.</summary>
    property Source: string read GetSource;
    /// <summary>User that boosted the chat</summary>
    property User: ITgUser read GetUser;
  end;

  /// <summary>
  ///   The boost was obtained by subscribing to Telegram Premium or by gifting a Telegram Premium
  ///   subscription to another user.
  /// </summary>
  ITgChatBoostSourcePremium = interface(ITgChatBoostSource)
    ['{CFC765F5-9A19-5DE9-A239-C016AE33B5F6}']
  end;

  /// <summary>
  ///   The boost was obtained by the creation of Telegram Premium gift codes to boost a chat. Each
  ///   such code boosts the chat 4 times for the duration of the corresponding Telegram Premium
  ///   subscription.
  /// </summary>
  ITgChatBoostSourceGiftCode = interface(ITgChatBoostSource)
    ['{CCEDF2A5-196E-5033-85AA-A3E765CC4166}']
  end;

  /// <summary>
  ///   The boost was obtained by the creation of a Telegram Premium or a Telegram Star giveaway.
  ///   This boosts the chat 4 times for the duration of the corresponding Telegram Premium
  ///   subscription for Telegram Premium giveaways and prize_star_count / 500 times for one year
  ///   for Telegram Star giveaways.
  /// </summary>
  ITgChatBoostSourceGiveaway = interface(ITgChatBoostSource)
    ['{CDBAF96E-4AD7-5D32-A445-C04A8DE6793F}']
    function GetGiveawayMessageId: Int64;
    function GetPrizeStarCount: Integer;
    function GetHasPrizeStarCount: Boolean;
    function GetIsUnclaimed: Boolean;
    /// <summary>
    ///   Identifier of a message in the chat with the giveaway; the message could have been deleted
    ///   already. May be 0 if the message isn't sent yet.
    /// </summary>
    property GiveawayMessageId: Int64 read GetGiveawayMessageId;
    /// <summary>
    ///   Optional. The number of Telegram Stars to be split between giveaway winners; for Telegram
    ///   Star giveaways only
    /// </summary>
    property PrizeStarCount: Integer read GetPrizeStarCount;
    /// <summary>Поле prize_star_count присутствует.</summary>
    property HasPrizeStarCount: Boolean read GetHasPrizeStarCount;
    /// <summary>
    ///   Optional. True, if the giveaway was completed, but there was no user to win the prize
    /// </summary>
    property IsUnclaimed: Boolean read GetIsUnclaimed;
  end;

  /// <summary>This object contains information about a chat boost.</summary>
  ITgChatBoost = interface(ITgJsonObject)
    ['{540BF1B0-9BDD-5960-9FC6-1373D243F7A0}']
    function GetBoostId: string;
    function GetAddDate: Int64;
    function GetExpirationDate: Int64;
    function GetSource: ITgChatBoostSource;
    /// <summary>Unique identifier of the boost</summary>
    property BoostId: string read GetBoostId;
    /// <summary>Point in time (Unix timestamp) when the chat was boosted</summary>
    property AddDate: Int64 read GetAddDate;
    /// <summary>
    ///   Point in time (Unix timestamp) when the boost will automatically expire, unless the
    ///   booster's Telegram Premium subscription is prolonged
    /// </summary>
    property ExpirationDate: Int64 read GetExpirationDate;
    /// <summary>Source of the added boost</summary>
    property Source: ITgChatBoostSource read GetSource;
  end;

  /// <summary>This object represents a boost added to a chat or changed.</summary>
  ITgChatBoostUpdated = interface(ITgJsonObject)
    ['{5BFD5DDD-2C52-5874-84DC-281FEDDF6382}']
    function GetChat: ITgChat;
    function GetBoost: ITgChatBoost;
    /// <summary>Chat which was boosted</summary>
    property Chat: ITgChat read GetChat;
    /// <summary>Information about the chat boost</summary>
    property Boost: ITgChatBoost read GetBoost;
  end;

  /// <summary>This object represents a boost removed from a chat.</summary>
  ITgChatBoostRemoved = interface(ITgJsonObject)
    ['{7B763B8A-2C68-5478-B4B1-5917B24A8070}']
    function GetChat: ITgChat;
    function GetBoostId: string;
    function GetRemoveDate: Int64;
    function GetSource: ITgChatBoostSource;
    /// <summary>Chat which was boosted</summary>
    property Chat: ITgChat read GetChat;
    /// <summary>Unique identifier of the boost</summary>
    property BoostId: string read GetBoostId;
    /// <summary>Point in time (Unix timestamp) when the boost was removed</summary>
    property RemoveDate: Int64 read GetRemoveDate;
    /// <summary>Source of the removed boost</summary>
    property Source: ITgChatBoostSource read GetSource;
  end;

  /// <summary>Describes a service message about the chat owner leaving the chat.</summary>
  ITgChatOwnerLeft = interface(ITgJsonObject)
    ['{E31C2DF7-9BAE-58FB-A6D6-FAAAE5ED0EA3}']
    function GetNewOwner: ITgUser;
    /// <summary>
    ///   Optional. The user who will become the new owner of the chat if the previous owner does
    ///   not return to the chat
    /// </summary>
    property NewOwner: ITgUser read GetNewOwner;
  end;

  /// <summary>Describes a service message about an ownership change in the chat.</summary>
  ITgChatOwnerChanged = interface(ITgJsonObject)
    ['{C3A1B025-F4FB-5CBA-9257-3851CDD7C5BD}']
    function GetNewOwner: ITgUser;
    /// <summary>The new owner of the chat</summary>
    property NewOwner: ITgUser read GetNewOwner;
  end;

  /// <summary>This object represents a list of boosts added to a chat by a user.</summary>
  ITgUserChatBoosts = interface(ITgJsonObject)
    ['{11025645-062D-56F3-A8E3-BDBDD2683346}']
    function GetBoosts: TArray<ITgChatBoost>;
    /// <summary>The list of boosts added to the chat by the user</summary>
    property Boosts: TArray<ITgChatBoost> read GetBoosts;
  end;

  /// <summary>Represents the rights of a business bot.</summary>
  ITgBusinessBotRights = interface(ITgJsonObject)
    ['{6AC12C3B-AA92-5078-86BB-FC58BE7BF424}']
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
    /// <summary>
    ///   Optional. True, if the bot can send and edit messages in the private chats that had
    ///   incoming messages in the last 24 hours
    /// </summary>
    property CanReply: Boolean read GetCanReply;
    /// <summary>
    ///   Optional. True, if the bot can mark incoming private messages as read
    /// </summary>
    property CanReadMessages: Boolean read GetCanReadMessages;
    /// <summary>Optional. True, if the bot can delete messages sent by the bot</summary>
    property CanDeleteSentMessages: Boolean read GetCanDeleteSentMessages;
    /// <summary>
    ///   Optional. True, if the bot can delete all private messages in managed chats
    /// </summary>
    property CanDeleteAllMessages: Boolean read GetCanDeleteAllMessages;
    /// <summary>
    ///   Optional. True, if the bot can edit the first and last name of the business account
    /// </summary>
    property CanEditName: Boolean read GetCanEditName;
    /// <summary>
    ///   Optional. True, if the bot can edit the bio of the business account
    /// </summary>
    property CanEditBio: Boolean read GetCanEditBio;
    /// <summary>
    ///   Optional. True, if the bot can edit the profile photo of the business account
    /// </summary>
    property CanEditProfilePhoto: Boolean read GetCanEditProfilePhoto;
    /// <summary>
    ///   Optional. True, if the bot can edit the username of the business account
    /// </summary>
    property CanEditUsername: Boolean read GetCanEditUsername;
    /// <summary>
    ///   Optional. True, if the bot can change the privacy settings pertaining to gifts for the
    ///   business account
    /// </summary>
    property CanChangeGiftSettings: Boolean read GetCanChangeGiftSettings;
    /// <summary>
    ///   Optional. True, if the bot can view gifts and the amount of Telegram Stars owned by the
    ///   business account
    /// </summary>
    property CanViewGiftsAndStars: Boolean read GetCanViewGiftsAndStars;
    /// <summary>
    ///   Optional. True, if the bot can convert regular gifts owned by the business account to
    ///   Telegram Stars
    /// </summary>
    property CanConvertGiftsToStars: Boolean read GetCanConvertGiftsToStars;
    /// <summary>
    ///   Optional. True, if the bot can transfer and upgrade gifts owned by the business account
    /// </summary>
    property CanTransferAndUpgradeGifts: Boolean read GetCanTransferAndUpgradeGifts;
    /// <summary>
    ///   Optional. True, if the bot can transfer Telegram Stars received by the business account to
    ///   its own account, or use them to upgrade and transfer gifts
    /// </summary>
    property CanTransferStars: Boolean read GetCanTransferStars;
    /// <summary>
    ///   Optional. True, if the bot can post, edit and delete stories on behalf of the business
    ///   account
    /// </summary>
    property CanManageStories: Boolean read GetCanManageStories;
  end;

  /// <summary>Describes the connection of the bot with a business account.</summary>
  ITgBusinessConnection = interface(ITgJsonObject)
    ['{F70D6187-A7B4-59A8-BEE0-6AADBB428ABB}']
    function GetId: string;
    function GetUser: ITgUser;
    function GetUserChatId: Int64;
    function GetDate: Int64;
    function GetRights: ITgBusinessBotRights;
    function GetIsEnabled: Boolean;
    /// <summary>Unique identifier of the business connection</summary>
    property Id: string read GetId;
    /// <summary>Business account user that created the business connection</summary>
    property User: ITgUser read GetUser;
    /// <summary>
    ///   Identifier of a private chat with the user who created the business connection. This
    ///   number may have more than 32 significant bits and some programming languages may have
    ///   difficulty/silent defects in interpreting it. But it has at most 52 significant bits, so a
    ///   64-bit integer or double-precision float type are safe for storing this identifier.
    /// </summary>
    property UserChatId: Int64 read GetUserChatId;
    /// <summary>Date the connection was established in Unix time</summary>
    property Date: Int64 read GetDate;
    /// <summary>Optional. Rights of the business bot</summary>
    property Rights: ITgBusinessBotRights read GetRights;
    /// <summary>True, if the connection is active</summary>
    property IsEnabled: Boolean read GetIsEnabled;
  end;

  /// <summary>
  ///   This object is received when messages are deleted from a connected business account.
  /// </summary>
  ITgBusinessMessagesDeleted = interface(ITgJsonObject)
    ['{94463712-664E-5DE4-8EF2-504A7D4BBFB0}']
    function GetBusinessConnectionId: string;
    function GetChat: ITgChat;
    function GetMessageIds: TArray<Int64>;
    /// <summary>Unique identifier of the business connection</summary>
    property BusinessConnectionId: string read GetBusinessConnectionId;
    /// <summary>
    ///   Information about a chat in the business account. The bot may not have access to the chat
    ///   or the corresponding user.
    /// </summary>
    property Chat: ITgChat read GetChat;
    /// <summary>
    ///   The list of identifiers of deleted messages in the chat of the business account
    /// </summary>
    property MessageIds: TArray<Int64> read GetMessageIds;
  end;

  /// <summary>Describes an inline message sent by a Web App on behalf of a user.</summary>
  ITgSentWebAppMessage = interface(ITgJsonObject)
    ['{656D9EF6-96E1-550A-ACEC-DFBF1E7BDCA0}']
    function GetInlineMessageId: string;
    /// <summary>
    ///   Optional. Identifier of the sent inline message. Available only if there is an inline
    ///   keyboard attached to the message.
    /// </summary>
    property InlineMessageId: string read GetInlineMessageId;
  end;

  /// <summary>Describes an inline message sent by a guest bot.</summary>
  ITgSentGuestMessage = interface(ITgJsonObject)
    ['{92B65C1E-E12C-572B-B766-A6F7DF52D7A7}']
    function GetInlineMessageId: string;
    /// <summary>Identifier of the sent inline message</summary>
    property InlineMessageId: string read GetInlineMessageId;
  end;

  /// <summary>Describes an inline message to be sent by a user of a Mini App.</summary>
  ITgPreparedInlineMessage = interface(ITgJsonObject)
    ['{47801A31-3E4B-55A9-BB42-6B296F6ABD3C}']
    function GetId: string;
    function GetExpirationDate: Int64;
    /// <summary>Unique identifier of the prepared message</summary>
    property Id: string read GetId;
    /// <summary>
    ///   Expiration date of the prepared message, in Unix time. Expired prepared messages can no
    ///   longer be used.
    /// </summary>
    property ExpirationDate: Int64 read GetExpirationDate;
  end;

  /// <summary>Describes a keyboard button to be used by a user of a Mini App.</summary>
  ITgPreparedKeyboardButton = interface(ITgJsonObject)
    ['{3D654FD7-67F8-56E9-B661-C3C892261EC8}']
    function GetId: string;
    /// <summary>Unique identifier of the keyboard button</summary>
    property Id: string read GetId;
  end;

  /// <summary>Describes why a request was unsuccessful.</summary>
  ITgResponseParameters = interface(ITgJsonObject)
    ['{13A61379-B618-555C-A476-50A2ACCA742C}']
    function GetMigrateToChatId: Int64;
    function GetHasMigrateToChatId: Boolean;
    function GetRetryAfter: Integer;
    function GetHasRetryAfter: Boolean;
    /// <summary>
    ///   Optional. The group has been migrated to a supergroup with the specified identifier. This
    ///   number may have more than 32 significant bits and some programming languages may have
    ///   difficulty/silent defects in interpreting it. But it has at most 52 significant bits, so a
    ///   signed 64-bit integer or double-precision float type are safe for storing this identifier.
    /// </summary>
    property MigrateToChatId: Int64 read GetMigrateToChatId;
    /// <summary>Поле migrate_to_chat_id присутствует.</summary>
    property HasMigrateToChatId: Boolean read GetHasMigrateToChatId;
    /// <summary>
    ///   Optional. In case of exceeding flood control, the number of seconds left to wait before
    ///   the request can be repeated
    /// </summary>
    property RetryAfter: Integer read GetRetryAfter;
    /// <summary>Поле retry_after присутствует.</summary>
    property HasRetryAfter: Boolean read GetHasRetryAfter;
  end;

  /// <summary>
  ///   Represents an animation file (GIF or H.264/MPEG-4 AVC video without sound) to be sent.
  /// </summary>
  ITgInputMediaAnimation = interface(ITgOutObject)
    ['{A284BB4F-8A62-50FA-913A-D0A068877F0B}']
    /// <summary>
    ///   Задаёт media: File to send. Pass a file_id to send a file that exists on the Telegram
    ///   servers (recommended), pass an HTTP URL for Telegram to get a file from the Internet, or
    ///   pass “attach://&lt;file_attach_name&gt;” to upload a new one using multipart/form-data
    ///   under &lt;file_attach_name&gt; name. More information on Sending Files »
    /// </summary>
    function WithMedia(const AValue: TTgInputFile): ITgInputMediaAnimation;
    /// <summary>
    ///   Задаёт thumbnail: Optional. Thumbnail of the file sent; can be ignored if thumbnail
    ///   generation for the file is supported server-side. The thumbnail should be in JPEG format
    ///   and less than 200 kB in size. A thumbnail's width and height should not exceed 320.
    ///   Ignored if the file is not uploaded using multipart/form-data. Thumbnails can't be reused
    ///   and can be only uploaded as a new file, so you can pass
    ///   “attach://&lt;file_attach_name&gt;” if the thumbnail was uploaded using
    ///   multipart/form-data under &lt;file_attach_name&gt;. More information on Sending Files »
    /// </summary>
    function WithThumbnail(const AValue: TTgInputFile): ITgInputMediaAnimation;
    /// <summary>
    ///   Задаёт caption: Optional. Caption of the animation to be sent, 0-1024 characters after
    ///   entities parsing
    /// </summary>
    function WithCaption(const AValue: string): ITgInputMediaAnimation;
    /// <summary>
    ///   Задаёт parse_mode: Optional. Mode for parsing entities in the animation caption. See
    ///   formatting options for more details.
    /// </summary>
    function WithParseMode(const AValue: string): ITgInputMediaAnimation;
    /// <summary>
    ///   Задаёт caption_entities: Optional. List of special entities that appear in the caption,
    ///   which can be specified instead of parse_mode
    /// </summary>
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInputMediaAnimation;
    /// <summary>
    ///   Задаёт show_caption_above_media: Optional. Pass True if the caption must be shown above
    ///   the message media
    /// </summary>
    function WithShowCaptionAboveMedia(AValue: Boolean): ITgInputMediaAnimation;
    /// <summary>Задаёт width: Optional. Animation width</summary>
    function WithWidth(AValue: Integer): ITgInputMediaAnimation;
    /// <summary>Задаёт height: Optional. Animation height</summary>
    function WithHeight(AValue: Integer): ITgInputMediaAnimation;
    /// <summary>Задаёт duration: Optional. Animation duration in seconds</summary>
    function WithDuration(AValue: Integer): ITgInputMediaAnimation;
    /// <summary>
    ///   Задаёт has_spoiler: Optional. Pass True if the animation needs to be covered with a
    ///   spoiler animation
    /// </summary>
    function WithHasSpoiler(AValue: Boolean): ITgInputMediaAnimation;
  end;

  /// <summary>Represents an audio file to be treated as music to be sent.</summary>
  ITgInputMediaAudio = interface(ITgOutObject)
    ['{F9503EAE-3C4B-510B-B455-DD3FC06032D5}']
    /// <summary>
    ///   Задаёт media: File to send. Pass a file_id to send a file that exists on the Telegram
    ///   servers (recommended), pass an HTTP URL for Telegram to get a file from the Internet, or
    ///   pass “attach://&lt;file_attach_name&gt;” to upload a new one using multipart/form-data
    ///   under &lt;file_attach_name&gt; name. More information on Sending Files »
    /// </summary>
    function WithMedia(const AValue: TTgInputFile): ITgInputMediaAudio;
    /// <summary>
    ///   Задаёт thumbnail: Optional. Thumbnail of the file sent; can be ignored if thumbnail
    ///   generation for the file is supported server-side. The thumbnail should be in JPEG format
    ///   and less than 200 kB in size. A thumbnail's width and height should not exceed 320.
    ///   Ignored if the file is not uploaded using multipart/form-data. Thumbnails can't be reused
    ///   and can be only uploaded as a new file, so you can pass
    ///   “attach://&lt;file_attach_name&gt;” if the thumbnail was uploaded using
    ///   multipart/form-data under &lt;file_attach_name&gt;. More information on Sending Files »
    /// </summary>
    function WithThumbnail(const AValue: TTgInputFile): ITgInputMediaAudio;
    /// <summary>
    ///   Задаёт caption: Optional. Caption of the audio to be sent, 0-1024 characters after
    ///   entities parsing
    /// </summary>
    function WithCaption(const AValue: string): ITgInputMediaAudio;
    /// <summary>
    ///   Задаёт parse_mode: Optional. Mode for parsing entities in the audio caption. See
    ///   formatting options for more details.
    /// </summary>
    function WithParseMode(const AValue: string): ITgInputMediaAudio;
    /// <summary>
    ///   Задаёт caption_entities: Optional. List of special entities that appear in the caption,
    ///   which can be specified instead of parse_mode
    /// </summary>
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInputMediaAudio;
    /// <summary>Задаёт duration: Optional. Duration of the audio in seconds</summary>
    function WithDuration(AValue: Integer): ITgInputMediaAudio;
    /// <summary>Задаёт performer: Optional. Performer of the audio</summary>
    function WithPerformer(const AValue: string): ITgInputMediaAudio;
    /// <summary>Задаёт title: Optional. Title of the audio</summary>
    function WithTitle(const AValue: string): ITgInputMediaAudio;
  end;

  /// <summary>Represents a general file to be sent.</summary>
  ITgInputMediaDocument = interface(ITgOutObject)
    ['{87389015-B482-582C-93C9-11D3DEE44B3D}']
    /// <summary>
    ///   Задаёт media: File to send. Pass a file_id to send a file that exists on the Telegram
    ///   servers (recommended), pass an HTTP URL for Telegram to get a file from the Internet, or
    ///   pass “attach://&lt;file_attach_name&gt;” to upload a new one using multipart/form-data
    ///   under &lt;file_attach_name&gt; name. More information on Sending Files »
    /// </summary>
    function WithMedia(const AValue: TTgInputFile): ITgInputMediaDocument;
    /// <summary>
    ///   Задаёт thumbnail: Optional. Thumbnail of the file sent; can be ignored if thumbnail
    ///   generation for the file is supported server-side. The thumbnail should be in JPEG format
    ///   and less than 200 kB in size. A thumbnail's width and height should not exceed 320.
    ///   Ignored if the file is not uploaded using multipart/form-data. Thumbnails can't be reused
    ///   and can be only uploaded as a new file, so you can pass
    ///   “attach://&lt;file_attach_name&gt;” if the thumbnail was uploaded using
    ///   multipart/form-data under &lt;file_attach_name&gt;. More information on Sending Files »
    /// </summary>
    function WithThumbnail(const AValue: TTgInputFile): ITgInputMediaDocument;
    /// <summary>
    ///   Задаёт caption: Optional. Caption of the document to be sent, 0-1024 characters after
    ///   entities parsing
    /// </summary>
    function WithCaption(const AValue: string): ITgInputMediaDocument;
    /// <summary>
    ///   Задаёт parse_mode: Optional. Mode for parsing entities in the document caption. See
    ///   formatting options for more details.
    /// </summary>
    function WithParseMode(const AValue: string): ITgInputMediaDocument;
    /// <summary>
    ///   Задаёт caption_entities: Optional. List of special entities that appear in the caption,
    ///   which can be specified instead of parse_mode
    /// </summary>
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInputMediaDocument;
    /// <summary>
    ///   Задаёт disable_content_type_detection: Optional. Disables automatic server-side content
    ///   type detection for files uploaded using multipart/form-data. Always True, if the document
    ///   is sent as part of an album.
    /// </summary>
    function WithDisableContentTypeDetection(AValue: Boolean): ITgInputMediaDocument;
  end;

  /// <summary>Represents an HTTP link to be sent.</summary>
  ITgInputMediaLink = interface(ITgOutObject)
    ['{1B9A3DE2-39FB-545F-83CE-A4E0947171C2}']
    /// <summary>Задаёт url: HTTP URL of the link</summary>
    function WithUrl(const AValue: string): ITgInputMediaLink;
  end;

  /// <summary>Represents a live photo to be sent.</summary>
  ITgInputMediaLivePhoto = interface(ITgOutObject)
    ['{57D0F50F-DE80-5CA1-B6BF-E5E314D3BD2A}']
    /// <summary>
    ///   Задаёт media: Video of the live photo to send. Pass a file_id to send a file that exists
    ///   on the Telegram servers (recommended) or pass “attach://&lt;file_attach_name&gt;” to
    ///   upload a new one using multipart/form-data under &lt;file_attach_name&gt; name. More
    ///   information on Sending Files ». Sending live photos by a URL is currently unsupported.
    /// </summary>
    function WithMedia(const AValue: TTgInputFile): ITgInputMediaLivePhoto;
    /// <summary>
    ///   Задаёт photo: The static photo to send. Pass a file_id to send a file that exists on the
    ///   Telegram servers (recommended) or pass “attach://&lt;file_attach_name&gt;” to upload a new
    ///   one using multipart/form-data under &lt;file_attach_name&gt; name. More information on
    ///   Sending Files ». Sending live photos by a URL is currently unsupported.
    /// </summary>
    function WithPhoto(const AValue: TTgInputFile): ITgInputMediaLivePhoto;
    /// <summary>
    ///   Задаёт caption: Optional. Caption of the live photo to be sent, 0-1024 characters after
    ///   entities parsing
    /// </summary>
    function WithCaption(const AValue: string): ITgInputMediaLivePhoto;
    /// <summary>
    ///   Задаёт parse_mode: Optional. Mode for parsing entities in the live photo caption. See
    ///   formatting options for more details.
    /// </summary>
    function WithParseMode(const AValue: string): ITgInputMediaLivePhoto;
    /// <summary>
    ///   Задаёт caption_entities: Optional. List of special entities that appear in the caption,
    ///   which can be specified instead of parse_mode
    /// </summary>
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInputMediaLivePhoto;
    /// <summary>
    ///   Задаёт show_caption_above_media: Optional. Pass True if the caption must be shown above
    ///   the message media
    /// </summary>
    function WithShowCaptionAboveMedia(AValue: Boolean): ITgInputMediaLivePhoto;
    /// <summary>
    ///   Задаёт has_spoiler: Optional. Pass True if the live photo needs to be covered with a
    ///   spoiler animation
    /// </summary>
    function WithHasSpoiler(AValue: Boolean): ITgInputMediaLivePhoto;
  end;

  /// <summary>Represents a location to be sent.</summary>
  ITgInputMediaLocation = interface(ITgOutObject)
    ['{1FAE8B34-4B6B-592F-BF11-B5F388C2494A}']
    /// <summary>Задаёт latitude: Latitude of the location</summary>
    function WithLatitude(AValue: Double): ITgInputMediaLocation;
    /// <summary>Задаёт longitude: Longitude of the location</summary>
    function WithLongitude(AValue: Double): ITgInputMediaLocation;
    /// <summary>
    ///   Задаёт horizontal_accuracy: Optional. The radius of uncertainty for the location, measured
    ///   in meters; 0-1500
    /// </summary>
    function WithHorizontalAccuracy(AValue: Double): ITgInputMediaLocation;
  end;

  /// <summary>Represents a photo to be sent.</summary>
  ITgInputMediaPhoto = interface(ITgOutObject)
    ['{6C64C2D7-0C64-5B10-910D-48016FE9C70F}']
    /// <summary>
    ///   Задаёт media: File to send. Pass a file_id to send a file that exists on the Telegram
    ///   servers (recommended), pass an HTTP URL for Telegram to get a file from the Internet, or
    ///   pass “attach://&lt;file_attach_name&gt;” to upload a new one using multipart/form-data
    ///   under &lt;file_attach_name&gt; name. More information on Sending Files »
    /// </summary>
    function WithMedia(const AValue: TTgInputFile): ITgInputMediaPhoto;
    /// <summary>
    ///   Задаёт caption: Optional. Caption of the photo to be sent, 0-1024 characters after
    ///   entities parsing
    /// </summary>
    function WithCaption(const AValue: string): ITgInputMediaPhoto;
    /// <summary>
    ///   Задаёт parse_mode: Optional. Mode for parsing entities in the photo caption. See
    ///   formatting options for more details.
    /// </summary>
    function WithParseMode(const AValue: string): ITgInputMediaPhoto;
    /// <summary>
    ///   Задаёт caption_entities: Optional. List of special entities that appear in the caption,
    ///   which can be specified instead of parse_mode
    /// </summary>
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInputMediaPhoto;
    /// <summary>
    ///   Задаёт show_caption_above_media: Optional. Pass True if the caption must be shown above
    ///   the message media
    /// </summary>
    function WithShowCaptionAboveMedia(AValue: Boolean): ITgInputMediaPhoto;
    /// <summary>
    ///   Задаёт has_spoiler: Optional. Pass True if the photo needs to be covered with a spoiler
    ///   animation
    /// </summary>
    function WithHasSpoiler(AValue: Boolean): ITgInputMediaPhoto;
  end;

  /// <summary>Represents a sticker file to be sent.</summary>
  ITgInputMediaSticker = interface(ITgOutObject)
    ['{123F0A91-A06C-512A-B27B-DFF332DB0B15}']
    /// <summary>
    ///   Задаёт media: File to send. Pass a file_id to send a file that exists on the Telegram
    ///   servers (recommended), pass an HTTP URL for Telegram to get a .WEBP sticker from the
    ///   Internet, or pass “attach://&lt;file_attach_name&gt;” to upload a new .WEBP, .TGS, or
    ///   .WEBM sticker using multipart/form-data under &lt;file_attach_name&gt; name. More
    ///   information on Sending Files »
    /// </summary>
    function WithMedia(const AValue: TTgInputFile): ITgInputMediaSticker;
    /// <summary>
    ///   Задаёт emoji: Optional. Emoji associated with the sticker; only for just uploaded stickers
    /// </summary>
    function WithEmoji(const AValue: string): ITgInputMediaSticker;
  end;

  /// <summary>Represents a venue to be sent.</summary>
  ITgInputMediaVenue = interface(ITgOutObject)
    ['{A0B26333-4518-5475-8595-ECF29AD7D740}']
    /// <summary>Задаёт latitude: Latitude of the location</summary>
    function WithLatitude(AValue: Double): ITgInputMediaVenue;
    /// <summary>Задаёт longitude: Longitude of the location</summary>
    function WithLongitude(AValue: Double): ITgInputMediaVenue;
    /// <summary>Задаёт title: Name of the venue</summary>
    function WithTitle(const AValue: string): ITgInputMediaVenue;
    /// <summary>Задаёт address: Address of the venue</summary>
    function WithAddress(const AValue: string): ITgInputMediaVenue;
    /// <summary>
    ///   Задаёт foursquare_id: Optional. Foursquare identifier of the venue
    /// </summary>
    function WithFoursquareId(const AValue: string): ITgInputMediaVenue;
    /// <summary>
    ///   Задаёт foursquare_type: Optional. Foursquare type of the venue, if known. (For example,
    ///   “arts_entertainment/default”, “arts_entertainment/aquarium” or “food/icecream”.)
    /// </summary>
    function WithFoursquareType(const AValue: string): ITgInputMediaVenue;
    /// <summary>
    ///   Задаёт google_place_id: Optional. Google Places identifier of the venue
    /// </summary>
    function WithGooglePlaceId(const AValue: string): ITgInputMediaVenue;
    /// <summary>
    ///   Задаёт google_place_type: Optional. Google Places type of the venue. (See supported
    ///   types.)
    /// </summary>
    function WithGooglePlaceType(const AValue: string): ITgInputMediaVenue;
  end;

  /// <summary>Represents a video to be sent.</summary>
  ITgInputMediaVideo = interface(ITgOutObject)
    ['{5ED11DC0-D765-560A-BB57-268CF8DAAECE}']
    /// <summary>
    ///   Задаёт media: File to send. Pass a file_id to send a file that exists on the Telegram
    ///   servers (recommended), pass an HTTP URL for Telegram to get a file from the Internet, or
    ///   pass “attach://&lt;file_attach_name&gt;” to upload a new one using multipart/form-data
    ///   under &lt;file_attach_name&gt; name. More information on Sending Files »
    /// </summary>
    function WithMedia(const AValue: TTgInputFile): ITgInputMediaVideo;
    /// <summary>
    ///   Задаёт thumbnail: Optional. Thumbnail of the file sent; can be ignored if thumbnail
    ///   generation for the file is supported server-side. The thumbnail should be in JPEG format
    ///   and less than 200 kB in size. A thumbnail's width and height should not exceed 320.
    ///   Ignored if the file is not uploaded using multipart/form-data. Thumbnails can't be reused
    ///   and can be only uploaded as a new file, so you can pass
    ///   “attach://&lt;file_attach_name&gt;” if the thumbnail was uploaded using
    ///   multipart/form-data under &lt;file_attach_name&gt;. More information on Sending Files »
    /// </summary>
    function WithThumbnail(const AValue: TTgInputFile): ITgInputMediaVideo;
    /// <summary>
    ///   Задаёт cover: Optional. Cover for the video in the message. Pass a file_id to send a file
    ///   that exists on the Telegram servers (recommended), pass an HTTP URL for Telegram to get a
    ///   file from the Internet, or pass “attach://&lt;file_attach_name&gt;” to upload a new one
    ///   using multipart/form-data under &lt;file_attach_name&gt; name. More information on Sending
    ///   Files »
    /// </summary>
    function WithCover(const AValue: TTgInputFile): ITgInputMediaVideo;
    /// <summary>
    ///   Задаёт start_timestamp: Optional. Start timestamp for the video in the message
    /// </summary>
    function WithStartTimestamp(AValue: Integer): ITgInputMediaVideo;
    /// <summary>
    ///   Задаёт caption: Optional. Caption of the video to be sent, 0-1024 characters after
    ///   entities parsing
    /// </summary>
    function WithCaption(const AValue: string): ITgInputMediaVideo;
    /// <summary>
    ///   Задаёт parse_mode: Optional. Mode for parsing entities in the video caption. See
    ///   formatting options for more details.
    /// </summary>
    function WithParseMode(const AValue: string): ITgInputMediaVideo;
    /// <summary>
    ///   Задаёт caption_entities: Optional. List of special entities that appear in the caption,
    ///   which can be specified instead of parse_mode
    /// </summary>
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInputMediaVideo;
    /// <summary>
    ///   Задаёт show_caption_above_media: Optional. Pass True if the caption must be shown above
    ///   the message media
    /// </summary>
    function WithShowCaptionAboveMedia(AValue: Boolean): ITgInputMediaVideo;
    /// <summary>Задаёт width: Optional. Video width</summary>
    function WithWidth(AValue: Integer): ITgInputMediaVideo;
    /// <summary>Задаёт height: Optional. Video height</summary>
    function WithHeight(AValue: Integer): ITgInputMediaVideo;
    /// <summary>Задаёт duration: Optional. Video duration in seconds</summary>
    function WithDuration(AValue: Integer): ITgInputMediaVideo;
    /// <summary>
    ///   Задаёт supports_streaming: Optional. Pass True if the uploaded video is suitable for
    ///   streaming
    /// </summary>
    function WithSupportsStreaming(AValue: Boolean): ITgInputMediaVideo;
    /// <summary>
    ///   Задаёт has_spoiler: Optional. Pass True if the video needs to be covered with a spoiler
    ///   animation
    /// </summary>
    function WithHasSpoiler(AValue: Boolean): ITgInputMediaVideo;
  end;

  /// <summary>Represents a voice message file to be sent.</summary>
  ITgInputMediaVoiceNote = interface(ITgOutObject)
    ['{0FDFBBCD-E58D-5E26-8C96-6285ADDDC4D3}']
    /// <summary>
    ///   Задаёт media: File to send. Pass a file_id to send a file that exists on the Telegram
    ///   servers (recommended), pass an HTTP URL for Telegram to get a file from the Internet, or
    ///   pass "attach://&lt;file_attach_name&gt;" to upload a new one using multipart/form-data
    ///   under &lt;file_attach_name&gt; name. More information on Sending Files »
    /// </summary>
    function WithMedia(const AValue: TTgInputFile): ITgInputMediaVoiceNote;
    /// <summary>
    ///   Задаёт caption: Optional. Caption of the voice message to be sent, 0-1024 characters after
    ///   entities parsing
    /// </summary>
    function WithCaption(const AValue: string): ITgInputMediaVoiceNote;
    /// <summary>
    ///   Задаёт parse_mode: Optional. Mode for parsing entities in the voice message caption. See
    ///   formatting options for more details.
    /// </summary>
    function WithParseMode(const AValue: string): ITgInputMediaVoiceNote;
    /// <summary>
    ///   Задаёт caption_entities: Optional. List of special entities that appear in the caption,
    ///   which can be specified instead of parse_mode
    /// </summary>
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInputMediaVoiceNote;
    /// <summary>
    ///   Задаёт duration: Optional. Duration of the voice message in seconds
    /// </summary>
    function WithDuration(AValue: Integer): ITgInputMediaVoiceNote;
  end;

  /// <summary>The paid media to send is a live photo.</summary>
  ITgInputPaidMediaLivePhoto = interface(ITgOutObject)
    ['{634A0E51-C1A4-5A28-AF2F-AE9D38CE8519}']
    /// <summary>
    ///   Задаёт media: Video of the live photo to send. Pass a file_id to send a file that exists
    ///   on the Telegram servers (recommended) or pass “attach://&lt;file_attach_name&gt;” to
    ///   upload a new one using multipart/form-data under &lt;file_attach_name&gt; name. More
    ///   information on Sending Files ». Sending live photos by a URL is currently unsupported.
    /// </summary>
    function WithMedia(const AValue: TTgInputFile): ITgInputPaidMediaLivePhoto;
    /// <summary>
    ///   Задаёт photo: The static photo to send. Pass a file_id to send a file that exists on the
    ///   Telegram servers (recommended) or pass “attach://&lt;file_attach_name&gt;” to upload a new
    ///   one using multipart/form-data under &lt;file_attach_name&gt; name. More information on
    ///   Sending Files ». Sending live photos by a URL is currently unsupported.
    /// </summary>
    function WithPhoto(const AValue: TTgInputFile): ITgInputPaidMediaLivePhoto;
  end;

  /// <summary>The paid media to send is a photo.</summary>
  ITgInputPaidMediaPhoto = interface(ITgOutObject)
    ['{AEFB0DEC-DEA1-52DB-B03A-C0A4D75D552D}']
    /// <summary>
    ///   Задаёт media: File to send. Pass a file_id to send a file that exists on the Telegram
    ///   servers (recommended), pass an HTTP URL for Telegram to get a file from the Internet, or
    ///   pass “attach://&lt;file_attach_name&gt;” to upload a new one using multipart/form-data
    ///   under &lt;file_attach_name&gt; name. More information on Sending Files »
    /// </summary>
    function WithMedia(const AValue: TTgInputFile): ITgInputPaidMediaPhoto;
  end;

  /// <summary>The paid media to send is a video.</summary>
  ITgInputPaidMediaVideo = interface(ITgOutObject)
    ['{67C22D3A-260B-50B1-A042-6937B5494058}']
    /// <summary>
    ///   Задаёт media: File to send. Pass a file_id to send a file that exists on the Telegram
    ///   servers (recommended), pass an HTTP URL for Telegram to get a file from the Internet, or
    ///   pass “attach://&lt;file_attach_name&gt;” to upload a new one using multipart/form-data
    ///   under &lt;file_attach_name&gt; name. More information on Sending Files »
    /// </summary>
    function WithMedia(const AValue: TTgInputFile): ITgInputPaidMediaVideo;
    /// <summary>
    ///   Задаёт thumbnail: Optional. Thumbnail of the file sent; can be ignored if thumbnail
    ///   generation for the file is supported server-side. The thumbnail should be in JPEG format
    ///   and less than 200 kB in size. A thumbnail's width and height should not exceed 320.
    ///   Ignored if the file is not uploaded using multipart/form-data. Thumbnails can't be reused
    ///   and can be only uploaded as a new file, so you can pass
    ///   “attach://&lt;file_attach_name&gt;” if the thumbnail was uploaded using
    ///   multipart/form-data under &lt;file_attach_name&gt;. More information on Sending Files »
    /// </summary>
    function WithThumbnail(const AValue: TTgInputFile): ITgInputPaidMediaVideo;
    /// <summary>
    ///   Задаёт cover: Optional. Cover for the video in the message. Pass a file_id to send a file
    ///   that exists on the Telegram servers (recommended), pass an HTTP URL for Telegram to get a
    ///   file from the Internet, or pass “attach://&lt;file_attach_name&gt;” to upload a new one
    ///   using multipart/form-data under &lt;file_attach_name&gt; name. More information on Sending
    ///   Files »
    /// </summary>
    function WithCover(const AValue: TTgInputFile): ITgInputPaidMediaVideo;
    /// <summary>
    ///   Задаёт start_timestamp: Optional. Start timestamp for the video in the message
    /// </summary>
    function WithStartTimestamp(AValue: Integer): ITgInputPaidMediaVideo;
    /// <summary>Задаёт width: Optional. Video width</summary>
    function WithWidth(AValue: Integer): ITgInputPaidMediaVideo;
    /// <summary>Задаёт height: Optional. Video height</summary>
    function WithHeight(AValue: Integer): ITgInputPaidMediaVideo;
    /// <summary>Задаёт duration: Optional. Video duration in seconds</summary>
    function WithDuration(AValue: Integer): ITgInputPaidMediaVideo;
    /// <summary>
    ///   Задаёт supports_streaming: Optional. Pass True if the uploaded video is suitable for
    ///   streaming
    /// </summary>
    function WithSupportsStreaming(AValue: Boolean): ITgInputPaidMediaVideo;
  end;

  /// <summary>A static profile photo in the .JPG format.</summary>
  ITgInputProfilePhotoStatic = interface(ITgOutObject)
    ['{B2C5E813-E51E-5B54-9374-592E30961A80}']
    /// <summary>
    ///   Задаёт photo: The static profile photo. Profile photos can't be reused and can only be
    ///   uploaded as a new file, so you can pass “attach://&lt;file_attach_name&gt;” if the photo
    ///   was uploaded using multipart/form-data under &lt;file_attach_name&gt;. More information on
    ///   Sending Files »
    /// </summary>
    function WithPhoto(const AValue: TTgInputFile): ITgInputProfilePhotoStatic;
  end;

  /// <summary>An animated profile photo in the MPEG4 format.</summary>
  ITgInputProfilePhotoAnimated = interface(ITgOutObject)
    ['{365D956F-4282-55B9-AB4A-5D49B53BD5E0}']
    /// <summary>
    ///   Задаёт animation: The animated profile photo. Profile photos can't be reused and can only
    ///   be uploaded as a new file, so you can pass “attach://&lt;file_attach_name&gt;” if the
    ///   photo was uploaded using multipart/form-data under &lt;file_attach_name&gt;. More
    ///   information on Sending Files »
    /// </summary>
    function WithAnimation(const AValue: TTgInputFile): ITgInputProfilePhotoAnimated;
    /// <summary>
    ///   Задаёт main_frame_timestamp: Optional. Timestamp in seconds of the frame that will be used
    ///   as the static profile photo. Defaults to 0.0.
    /// </summary>
    function WithMainFrameTimestamp(AValue: Double): ITgInputProfilePhotoAnimated;
  end;

  /// <summary>Describes a photo to post as a story.</summary>
  ITgInputStoryContentPhoto = interface(ITgOutObject)
    ['{CF546D86-B85D-5588-99C5-5E7524279350}']
    /// <summary>
    ///   Задаёт photo: The photo to post as a story. The photo must be of the size 1080x1920 and
    ///   must not exceed 10 MB. The photo can't be reused and can only be uploaded as a new file,
    ///   so you can pass “attach://&lt;file_attach_name&gt;” if the photo was uploaded using
    ///   multipart/form-data under &lt;file_attach_name&gt;. More information on Sending Files »
    /// </summary>
    function WithPhoto(const AValue: TTgInputFile): ITgInputStoryContentPhoto;
  end;

  /// <summary>Describes a video to post as a story.</summary>
  ITgInputStoryContentVideo = interface(ITgOutObject)
    ['{AC7A1964-5119-5642-9962-57F1E5EDAA7F}']
    /// <summary>
    ///   Задаёт video: The video to post as a story. The video must be of the size 720x1280,
    ///   streamable, encoded with H.265 codec, with key frames added each second in the MPEG4
    ///   format, and must not exceed 30 MB. The video can't be reused and can only be uploaded as a
    ///   new file, so you can pass “attach://&lt;file_attach_name&gt;” if the video was uploaded
    ///   using multipart/form-data under &lt;file_attach_name&gt;. More information on Sending
    ///   Files »
    /// </summary>
    function WithVideo(const AValue: TTgInputFile): ITgInputStoryContentVideo;
    /// <summary>
    ///   Задаёт duration: Optional. Precise duration of the video in seconds; 0-60
    /// </summary>
    function WithDuration(AValue: Double): ITgInputStoryContentVideo;
    /// <summary>
    ///   Задаёт cover_frame_timestamp: Optional. Timestamp in seconds of the frame that will be
    ///   used as the static cover for the story. Defaults to 0.0.
    /// </summary>
    function WithCoverFrameTimestamp(AValue: Double): ITgInputStoryContentVideo;
    /// <summary>
    ///   Задаёт is_animation: Optional. Pass True if the video has no sound
    /// </summary>
    function WithIsAnimation(AValue: Boolean): ITgInputStoryContentVideo;
  end;

  /// <summary>This object represents a sticker.</summary>
  ITgSticker = interface(ITgJsonObject)
    ['{FA0AB803-7650-5415-B175-D9263920B2A7}']
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
    /// <summary>
    ///   Identifier for this file, which can be used to download or reuse the file
    /// </summary>
    property FileId: string read GetFileId;
    /// <summary>
    ///   Unique identifier for this file, which is supposed to be the same over time and for
    ///   different bots. Can't be used to download or reuse the file.
    /// </summary>
    property FileUniqueId: string read GetFileUniqueId;
    /// <summary>
    ///   Type of the sticker, currently one of “regular”, “mask”, “custom_emoji”. The type of the
    ///   sticker is independent from its format, which is determined by the fields is_animated and
    ///   is_video.
    /// </summary>
    property StickerType: string read GetStickerType;
    /// <summary>Sticker width</summary>
    property Width: Integer read GetWidth;
    /// <summary>Sticker height</summary>
    property Height: Integer read GetHeight;
    /// <summary>True, if the sticker is animated</summary>
    property IsAnimated: Boolean read GetIsAnimated;
    /// <summary>True, if the sticker is a video sticker</summary>
    property IsVideo: Boolean read GetIsVideo;
    /// <summary>Optional. Sticker thumbnail in the .WEBP or .JPG format</summary>
    property Thumbnail: ITgPhotoSize read GetThumbnail;
    /// <summary>Optional. Emoji associated with the sticker</summary>
    property Emoji: string read GetEmoji;
    /// <summary>Optional. Name of the sticker set to which the sticker belongs</summary>
    property SetName: string read GetSetName;
    /// <summary>
    ///   Optional. For premium regular stickers, premium animation for the sticker
    /// </summary>
    property PremiumAnimation: ITgFile read GetPremiumAnimation;
    /// <summary>
    ///   Optional. For mask stickers, the position where the mask should be placed
    /// </summary>
    property MaskPosition: ITgMaskPosition read GetMaskPosition;
    /// <summary>
    ///   Optional. For custom emoji stickers, unique identifier of the custom emoji
    /// </summary>
    property CustomEmojiId: string read GetCustomEmojiId;
    /// <summary>
    ///   Optional. True, if the sticker must be repainted to a text color in messages, the color of
    ///   the Telegram Premium badge in emoji status, white color on chat photos, or another
    ///   appropriate color in other places
    /// </summary>
    property NeedsRepainting: Boolean read GetNeedsRepainting;
    /// <summary>Optional. File size in bytes</summary>
    property FileSize: Int64 read GetFileSize;
    /// <summary>Поле file_size присутствует.</summary>
    property HasFileSize: Boolean read GetHasFileSize;
  end;

  /// <summary>This object represents a sticker set.</summary>
  ITgStickerSet = interface(ITgJsonObject)
    ['{4527A4A9-1AD4-5CB6-9998-D5EEEBF542A5}']
    function GetName: string;
    function GetTitle: string;
    function GetStickerType: string;
    function GetStickers: TArray<ITgSticker>;
    function GetThumbnail: ITgPhotoSize;
    /// <summary>Sticker set name</summary>
    property Name: string read GetName;
    /// <summary>Sticker set title</summary>
    property Title: string read GetTitle;
    /// <summary>
    ///   Type of stickers in the set, currently one of “regular”, “mask”, “custom_emoji”
    /// </summary>
    property StickerType: string read GetStickerType;
    /// <summary>List of all set stickers</summary>
    property Stickers: TArray<ITgSticker> read GetStickers;
    /// <summary>
    ///   Optional. Sticker set thumbnail in the .WEBP, .TGS, or .WEBM format
    /// </summary>
    property Thumbnail: ITgPhotoSize read GetThumbnail;
  end;

  /// <summary>
  ///   This object describes the position on faces where a mask should be placed by default.
  /// </summary>
  ITgMaskPosition = interface(ITgJsonObject)
    ['{0495DF94-31FE-5F7B-A6F4-2D25EFC97257}']
    function GetPoint: string;
    function GetXShift: Double;
    function GetYShift: Double;
    function GetScale: Double;
    /// <summary>
    ///   Задаёт point: The part of the face relative to which the mask should be placed. One of
    ///   “forehead”, “eyes”, “mouth”, or “chin”. Значение копируется в момент вызова: последующие
    ///   изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithPoint(const AValue: string): ITgMaskPosition;
    /// <summary>
    ///   Задаёт x_shift: Shift by X-axis measured in widths of the mask scaled to the face size,
    ///   from left to right. For example, choosing -1.0 will place mask just to the left of the
    ///   default mask position. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithXShift(AValue: Double): ITgMaskPosition;
    /// <summary>
    ///   Задаёт y_shift: Shift by Y-axis measured in heights of the mask scaled to the face size,
    ///   from top to bottom. For example, 1.0 will place the mask just below the default mask
    ///   position. Значение копируется в момент вызова: последующие изменения переданного объекта
    ///   на этот не влияют.
    /// </summary>
    function WithYShift(AValue: Double): ITgMaskPosition;
    /// <summary>
    ///   Задаёт scale: Mask scaling coefficient. For example, 2.0 means double size. Значение
    ///   копируется в момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithScale(AValue: Double): ITgMaskPosition;
    /// <summary>
    ///   The part of the face relative to which the mask should be placed. One of “forehead”,
    ///   “eyes”, “mouth”, or “chin”.
    /// </summary>
    property Point: string read GetPoint;
    /// <summary>
    ///   Shift by X-axis measured in widths of the mask scaled to the face size, from left to
    ///   right. For example, choosing -1.0 will place mask just to the left of the default mask
    ///   position.
    /// </summary>
    property XShift: Double read GetXShift;
    /// <summary>
    ///   Shift by Y-axis measured in heights of the mask scaled to the face size, from top to
    ///   bottom. For example, 1.0 will place the mask just below the default mask position.
    /// </summary>
    property YShift: Double read GetYShift;
    /// <summary>Mask scaling coefficient. For example, 2.0 means double size.</summary>
    property Scale: Double read GetScale;
  end;

  /// <summary>This object describes a sticker to be added to a sticker set.</summary>
  ITgInputSticker = interface(ITgOutObject)
    ['{ADCEC72C-3C0B-5417-BE54-EA4D8CA49DBB}']
    /// <summary>
    ///   Задаёт sticker: The added sticker. Pass a file_id as a String to send a file that already
    ///   exists on the Telegram servers, pass an HTTP URL as a String for Telegram to get a file
    ///   from the Internet, or pass “attach://&lt;file_attach_name&gt;” to upload a new file using
    ///   multipart/form-data under &lt;file_attach_name&gt; name. Animated and video stickers can't
    ///   be uploaded via HTTP URL. More information on Sending Files »
    /// </summary>
    function WithSticker(const AValue: TTgInputFile): ITgInputSticker;
    /// <summary>
    ///   Задаёт format: Format of the added sticker, must be one of “static” for a .WEBP or .PNG
    ///   image, “animated” for a .TGS animation, “video” for a .WEBM video
    /// </summary>
    function WithFormat(const AValue: string): ITgInputSticker;
    /// <summary>Задаёт emoji_list: List of 1-20 emoji associated with the sticker</summary>
    function WithEmojiList(const AValue: TArray<string>): ITgInputSticker;
    /// <summary>
    ///   Задаёт mask_position: Optional. Position where the mask should be placed on faces. For
    ///   “mask” stickers only.
    /// </summary>
    function WithMaskPosition(const AValue: ITgMaskPosition): ITgInputSticker;
    /// <summary>
    ///   Задаёт keywords: Optional. List of 0-20 search keywords for the sticker with total length
    ///   of up to 64 characters. For “regular” and “custom_emoji” stickers only.
    /// </summary>
    function WithKeywords(const AValue: TArray<string>): ITgInputSticker;
  end;

  /// <summary>Rich formatted message.</summary>
  ITgRichMessage = interface(ITgJsonObject)
    ['{D442AB61-081D-5F31-9524-0F1EF0CAD95D}']
    function GetBlocks: TArray<ITgRichBlock>;
    function GetIsRtl: Boolean;
    function GetHasIsRtl: Boolean;
    /// <summary>Content of the message</summary>
    property Blocks: TArray<ITgRichBlock> read GetBlocks;
    /// <summary>Optional. True, if the rich message must be shown right-to-left</summary>
    property IsRtl: Boolean read GetIsRtl;
    /// <summary>Поле is_rtl присутствует.</summary>
    property HasIsRtl: Boolean read GetHasIsRtl;
  end;

  /// <summary>
  ///   Describes a rich message to be sent. Exactly one of the fields html, markdown, or blocks
  ///   must be used.
  /// </summary>
  ITgInputRichMessage = interface(ITgOutObject)
    ['{1C08B76B-70BA-57EF-9D32-7B927D556654}']
    /// <summary>
    ///   Задаёт blocks: Optional. Content of the rich message to send described as a list of blocks
    /// </summary>
    function WithBlocks(const AValue: array of TTgInputRichBlock): ITgInputRichMessage;
    /// <summary>
    ///   Задаёт html: Optional. Content of the rich message to send described using HTML
    ///   formatting. See rich message formatting options for more details. Use media field to
    ///   specify the media used in the message.
    /// </summary>
    function WithHtml(const AValue: string): ITgInputRichMessage;
    /// <summary>
    ///   Задаёт markdown: Optional. Content of the rich message to send described using Markdown
    ///   formatting. See rich message formatting options for more details. Use media field to
    ///   specify the media used in the message.
    /// </summary>
    function WithMarkdown(const AValue: string): ITgInputRichMessage;
    /// <summary>
    ///   Задаёт media: Optional. List of media that are specified in the markdown or html fields
    ///   using tg://photo?id=, tg://video?id=, tg://document?id=, and tg://audio?id= links
    /// </summary>
    function WithMedia(const AValue: array of ITgInputRichMessageMedia): ITgInputRichMessage;
    /// <summary>
    ///   Задаёт is_rtl: Optional. Pass True if the rich message must be shown right-to-left
    /// </summary>
    function WithIsRtl(AValue: Boolean): ITgInputRichMessage;
    /// <summary>
    ///   Задаёт skip_entity_detection: Optional. Pass True to skip automatic detection of entities
    ///   (e.g., URLs, email addresses, username mentions, hashtags, cashtags, bot commands, or
    ///   phone numbers) in the text
    /// </summary>
    function WithSkipEntityDetection(AValue: Boolean): ITgInputRichMessage;
  end;

  /// <summary>Describes a media element embedded in an outgoing rich message.</summary>
  ITgInputRichMessageMedia = interface(ITgOutObject)
    ['{88E08CB5-EE6E-56CC-825E-BAF1F7E5653C}']
    /// <summary>
    ///   Задаёт id: Unique identifier of the media used in a tg://photo?id=, tg://video?id=,
    ///   tg://document?id=, or tg://audio?id= link. 1-64 characters, only A-Z, a-z, 0-9, _ and -
    ///   are allowed.
    /// </summary>
    function WithId(const AValue: string): ITgInputRichMessageMedia;
    /// <summary>
    ///   Задаёт media: The media to be sent. Everything except the media itself and its properties
    ///   is ignored.
    /// </summary>
    function WithMedia(const AValue: TTgInputRichMedia): ITgInputRichMessageMedia;
  end;

  /// <summary>
  ///   This object represents a button in a RichMessage. Exactly one of the fields other than text
  ///   and style must be used to specify the type of the button.
  /// </summary>
  ITgRichMessageButton = interface(ITgJsonObject)
    ['{D50106D9-6766-5FE5-A10A-E9DA92EC5D61}']
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
    /// <summary>
    ///   Задаёт text: Text of the button. May contain only plain text, RichTextCustomEmoji and
    ///   RichTextDateTime entities. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithText(const AValue: ITgRichText): ITgRichMessageButton;
    /// <summary>
    ///   Задаёт style: Optional. Style of the button. Must be one of “danger”, “success”,
    ///   “primary”, or “link” (the button is shown as a regular link without borders). Apps may use
    ///   theme-specific colors for the button background and text based on the style. The style
    ///   “link” is allowed only for callback buttons. Значение копируется в момент вызова:
    ///   последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithStyle(const AValue: string): ITgRichMessageButton;
    /// <summary>
    ///   Задаёт url: Optional. HTTP or tg:// URL to be opened when the button is pressed. Links
    ///   tg://user?id=&lt;user_id&gt; can be used to mention a user by their identifier without
    ///   using a username, if this is allowed by their privacy settings. Значение копируется в
    ///   момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithUrl(const AValue: string): ITgRichMessageButton;
    /// <summary>
    ///   Задаёт callback_data: Optional. Data to be sent in a callback query to the bot when the
    ///   button is pressed, 1-64 bytes. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithCallbackData(const AValue: string): ITgRichMessageButton;
    /// <summary>
    ///   Задаёт web_app: Optional. Description of the Web App that will be launched when the user
    ///   presses the button. The Web App will be able to send an arbitrary message on behalf of the
    ///   user using the method answerWebAppQuery. Available only in private chats between a user
    ///   and the bot. Not supported for messages sent on behalf of a business account. Значение
    ///   копируется в момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithWebApp(const AValue: ITgWebAppInfo): ITgRichMessageButton;
    /// <summary>
    ///   Задаёт login_url: Optional. An HTTPS URL used to automatically authorize the user. Can be
    ///   used as a replacement for the Telegram Login Widget. Not supported for ephemeral messages.
    ///   Значение копируется в момент вызова: последующие изменения переданного объекта на этот не
    ///   влияют.
    /// </summary>
    function WithLoginUrl(const AValue: ITgLoginUrl): ITgRichMessageButton;
    /// <summary>
    ///   Задаёт switch_inline_query: Optional. If set, pressing the button will prompt the user to
    ///   select one of their chats, open that chat and insert the bot's username and the specified
    ///   inline query in the input field. May be empty, in which case just the bot's username will
    ///   be inserted. Not supported for messages sent in channel direct messages chats and on
    ///   behalf of a business account. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithSwitchInlineQuery(const AValue: string): ITgRichMessageButton;
    /// <summary>
    ///   Задаёт switch_inline_query_current_chat: Optional. If set, pressing the button will insert
    ///   the bot's username and the specified inline query in the current chat's input field. May
    ///   be empty, in which case only the bot's username will be inserted. Not supported in
    ///   channels and for messages sent in channel direct messages chats and on behalf of a
    ///   business account. Значение копируется в момент вызова: последующие изменения переданного
    ///   объекта на этот не влияют.
    /// </summary>
    function WithSwitchInlineQueryCurrentChat(const AValue: string): ITgRichMessageButton;
    /// <summary>
    ///   Задаёт switch_inline_query_chosen_chat: Optional. If set, pressing the button will prompt
    ///   the user to select one of their chats of the specified type, open that chat and insert the
    ///   bot's username and the specified inline query in the input field. Not supported for
    ///   messages sent in channel direct messages chats and on behalf of a business account.
    ///   Значение копируется в момент вызова: последующие изменения переданного объекта на этот не
    ///   влияют.
    /// </summary>
    function WithSwitchInlineQueryChosenChat(const AValue: ITgSwitchInlineQueryChosenChat): ITgRichMessageButton;
    /// <summary>
    ///   Задаёт copy_text: Optional. A button that copies the specified text to the clipboard.
    ///   Значение копируется в момент вызова: последующие изменения переданного объекта на этот не
    ///   влияют.
    /// </summary>
    function WithCopyText(const AValue: ITgCopyTextButton): ITgRichMessageButton;
    /// <summary>
    ///   Задаёт disabled: Optional. If set, then the button is disabled and does nothing. Значение
    ///   копируется в момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithDisabled(const AValue: ITgDisabledButton): ITgRichMessageButton;
    /// <summary>
    ///   Text of the button. May contain only plain text, RichTextCustomEmoji and RichTextDateTime
    ///   entities.
    /// </summary>
    property Text: ITgRichText read GetText;
    /// <summary>
    ///   Optional. Style of the button. Must be one of “danger”, “success”, “primary”, or “link”
    ///   (the button is shown as a regular link without borders). Apps may use theme-specific
    ///   colors for the button background and text based on the style. The style “link” is allowed
    ///   only for callback buttons.
    /// </summary>
    property Style: string read GetStyle;
    /// <summary>
    ///   Optional. HTTP or tg:// URL to be opened when the button is pressed. Links
    ///   tg://user?id=&lt;user_id&gt; can be used to mention a user by their identifier without
    ///   using a username, if this is allowed by their privacy settings.
    /// </summary>
    property Url: string read GetUrl;
    /// <summary>
    ///   Optional. Data to be sent in a callback query to the bot when the button is pressed, 1-64
    ///   bytes
    /// </summary>
    property CallbackData: string read GetCallbackData;
    /// <summary>
    ///   Optional. Description of the Web App that will be launched when the user presses the
    ///   button. The Web App will be able to send an arbitrary message on behalf of the user using
    ///   the method answerWebAppQuery. Available only in private chats between a user and the bot.
    ///   Not supported for messages sent on behalf of a business account.
    /// </summary>
    property WebApp: ITgWebAppInfo read GetWebApp;
    /// <summary>
    ///   Optional. An HTTPS URL used to automatically authorize the user. Can be used as a
    ///   replacement for the Telegram Login Widget. Not supported for ephemeral messages.
    /// </summary>
    property LoginUrl: ITgLoginUrl read GetLoginUrl;
    /// <summary>
    ///   Optional. If set, pressing the button will prompt the user to select one of their chats,
    ///   open that chat and insert the bot's username and the specified inline query in the input
    ///   field. May be empty, in which case just the bot's username will be inserted. Not supported
    ///   for messages sent in channel direct messages chats and on behalf of a business account.
    /// </summary>
    property SwitchInlineQuery: string read GetSwitchInlineQuery;
    /// <summary>
    ///   Optional. If set, pressing the button will insert the bot's username and the specified
    ///   inline query in the current chat's input field. May be empty, in which case only the bot's
    ///   username will be inserted. Not supported in channels and for messages sent in channel
    ///   direct messages chats and on behalf of a business account.
    /// </summary>
    property SwitchInlineQueryCurrentChat: string read GetSwitchInlineQueryCurrentChat;
    /// <summary>
    ///   Optional. If set, pressing the button will prompt the user to select one of their chats of
    ///   the specified type, open that chat and insert the bot's username and the specified inline
    ///   query in the input field. Not supported for messages sent in channel direct messages chats
    ///   and on behalf of a business account.
    /// </summary>
    property SwitchInlineQueryChosenChat: ITgSwitchInlineQueryChosenChat read GetSwitchInlineQueryChosenChat;
    /// <summary>
    ///   Optional. A button that copies the specified text to the clipboard
    /// </summary>
    property CopyText: ITgCopyTextButton read GetCopyText;
    /// <summary>Optional. If set, then the button is disabled and does nothing</summary>
    property Disabled: ITgDisabledButton read GetDisabled;
  end;

  /// <summary>
  ///   This object represents a rich formatted text. Currently, it can be either a String for plain
  ///   text, an Array of RichText, or any of the following types: Виды (Kind, As*):
  ///   ITgRichTextBold, ITgRichTextItalic, ITgRichTextUnderline, ITgRichTextStrikethrough,
  ///   ITgRichTextSpoiler, ITgRichTextDateTime, ITgRichTextTextMention, ITgRichTextSubscript,
  ///   ITgRichTextSuperscript, ITgRichTextMarked, ITgRichTextCode, ITgRichTextCustomEmoji,
  ///   ITgRichTextMathematicalExpression, ITgRichTextUrl, ITgRichTextEmailAddress,
  ///   ITgRichTextPhoneNumber, ITgRichTextBankCardNumber, ITgRichTextMention, ITgRichTextHashtag,
  ///   ITgRichTextCashtag, ITgRichTextBotCommand, ITgRichTextButton, ITgRichTextAnchor,
  ///   ITgRichTextAnchorLink, ITgRichTextReference, ITgRichTextReferenceLink, ITgRichTextPlain,
  ///   ITgRichTextList.
  /// </summary>
  ITgRichText = interface(ITgJsonObject)
    ['{F8881D0A-0A08-5257-9BAA-4C51F2701B24}']
    function GetKind: TTgRichTextKind;
    function GetKindText: string;
    /// <summary>ITgRichTextBold или nil, если объект другого вида.</summary>
    function AsBold: ITgRichTextBold;
    /// <summary>ITgRichTextItalic или nil, если объект другого вида.</summary>
    function AsItalic: ITgRichTextItalic;
    /// <summary>ITgRichTextUnderline или nil, если объект другого вида.</summary>
    function AsUnderline: ITgRichTextUnderline;
    /// <summary>ITgRichTextStrikethrough или nil, если объект другого вида.</summary>
    function AsStrikethrough: ITgRichTextStrikethrough;
    /// <summary>ITgRichTextSpoiler или nil, если объект другого вида.</summary>
    function AsSpoiler: ITgRichTextSpoiler;
    /// <summary>ITgRichTextDateTime или nil, если объект другого вида.</summary>
    function AsDateTime: ITgRichTextDateTime;
    /// <summary>ITgRichTextTextMention или nil, если объект другого вида.</summary>
    function AsTextMention: ITgRichTextTextMention;
    /// <summary>ITgRichTextSubscript или nil, если объект другого вида.</summary>
    function AsSubscript: ITgRichTextSubscript;
    /// <summary>ITgRichTextSuperscript или nil, если объект другого вида.</summary>
    function AsSuperscript: ITgRichTextSuperscript;
    /// <summary>ITgRichTextMarked или nil, если объект другого вида.</summary>
    function AsMarked: ITgRichTextMarked;
    /// <summary>ITgRichTextCode или nil, если объект другого вида.</summary>
    function AsCode: ITgRichTextCode;
    /// <summary>ITgRichTextCustomEmoji или nil, если объект другого вида.</summary>
    function AsCustomEmoji: ITgRichTextCustomEmoji;
    /// <summary>
    ///   ITgRichTextMathematicalExpression или nil, если объект другого вида.
    /// </summary>
    function AsMathematicalExpression: ITgRichTextMathematicalExpression;
    /// <summary>ITgRichTextUrl или nil, если объект другого вида.</summary>
    function AsUrl: ITgRichTextUrl;
    /// <summary>ITgRichTextEmailAddress или nil, если объект другого вида.</summary>
    function AsEmailAddress: ITgRichTextEmailAddress;
    /// <summary>ITgRichTextPhoneNumber или nil, если объект другого вида.</summary>
    function AsPhoneNumber: ITgRichTextPhoneNumber;
    /// <summary>ITgRichTextBankCardNumber или nil, если объект другого вида.</summary>
    function AsBankCardNumber: ITgRichTextBankCardNumber;
    /// <summary>ITgRichTextMention или nil, если объект другого вида.</summary>
    function AsMention: ITgRichTextMention;
    /// <summary>ITgRichTextHashtag или nil, если объект другого вида.</summary>
    function AsHashtag: ITgRichTextHashtag;
    /// <summary>ITgRichTextCashtag или nil, если объект другого вида.</summary>
    function AsCashtag: ITgRichTextCashtag;
    /// <summary>ITgRichTextBotCommand или nil, если объект другого вида.</summary>
    function AsBotCommand: ITgRichTextBotCommand;
    /// <summary>ITgRichTextButton или nil, если объект другого вида.</summary>
    function AsButton: ITgRichTextButton;
    /// <summary>ITgRichTextAnchor или nil, если объект другого вида.</summary>
    function AsAnchor: ITgRichTextAnchor;
    /// <summary>ITgRichTextAnchorLink или nil, если объект другого вида.</summary>
    function AsAnchorLink: ITgRichTextAnchorLink;
    /// <summary>ITgRichTextReference или nil, если объект другого вида.</summary>
    function AsReference: ITgRichTextReference;
    /// <summary>ITgRichTextReferenceLink или nil, если объект другого вида.</summary>
    function AsReferenceLink: ITgRichTextReferenceLink;
    /// <summary>ITgRichTextPlain или nil, если объект другого вида.</summary>
    function AsPlain: ITgRichTextPlain;
    /// <summary>ITgRichTextList или nil, если объект другого вида.</summary>
    function AsList: ITgRichTextList;
    /// <summary>Вид объекта (Unknown — неизвестный этой версии библиотеки).</summary>
    property Kind: TTgRichTextKind read GetKind;
    /// <summary>
    ///   Значение поля type в JSON как есть (в т.ч. при Kind = Unknown); для вариантов-строк и
    ///   массивов — пустая строка.
    /// </summary>
    property KindText: string read GetKindText;
  end;

  /// <summary>RichText: простой текст (JSON-строка).</summary>
  ITgRichTextPlain = interface(ITgRichText)
    ['{8E87D37F-8336-580F-9383-642ADC906EEF}']
    function GetText: string;
    /// <summary>Текст.</summary>
    property Text: string read GetText;
  end;

  /// <summary>RichText: последовательность фрагментов (JSON-массив).</summary>
  ITgRichTextList = interface(ITgRichText)
    ['{1BD43010-9051-52FF-91A1-CFDA43859753}']
    function GetItems: TArray<ITgRichText>;
    /// <summary>Фрагменты.</summary>
    property Items: TArray<ITgRichText> read GetItems;
  end;

  /// <summary>A bold text.</summary>
  ITgRichTextBold = interface(ITgRichText)
    ['{F5AABF17-CE91-5F82-94BD-1886B58A343C}']
    function GetText: ITgRichText;
    /// <summary>
    ///   Задаёт text: The text. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithText(const AValue: ITgRichText): ITgRichTextBold;
    /// <summary>The text</summary>
    property Text: ITgRichText read GetText;
  end;

  /// <summary>An italicized text.</summary>
  ITgRichTextItalic = interface(ITgRichText)
    ['{FEE23DB1-B88B-5926-989C-3755C35B346E}']
    function GetText: ITgRichText;
    /// <summary>
    ///   Задаёт text: The text. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithText(const AValue: ITgRichText): ITgRichTextItalic;
    /// <summary>The text</summary>
    property Text: ITgRichText read GetText;
  end;

  /// <summary>An underlined text.</summary>
  ITgRichTextUnderline = interface(ITgRichText)
    ['{66666858-7684-5BF1-9342-5882A6A31123}']
    function GetText: ITgRichText;
    /// <summary>
    ///   Задаёт text: The text. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithText(const AValue: ITgRichText): ITgRichTextUnderline;
    /// <summary>The text</summary>
    property Text: ITgRichText read GetText;
  end;

  /// <summary>A strikethrough text.</summary>
  ITgRichTextStrikethrough = interface(ITgRichText)
    ['{AD8D16B3-8F6F-5684-A0DA-0B105B98BB52}']
    function GetText: ITgRichText;
    /// <summary>
    ///   Задаёт text: The text. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithText(const AValue: ITgRichText): ITgRichTextStrikethrough;
    /// <summary>The text</summary>
    property Text: ITgRichText read GetText;
  end;

  /// <summary>A text covered by a spoiler.</summary>
  ITgRichTextSpoiler = interface(ITgRichText)
    ['{1AF9CEC6-CE33-5C4A-9D5C-A6F1CFA3ED45}']
    function GetText: ITgRichText;
    /// <summary>
    ///   Задаёт text: The text. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithText(const AValue: ITgRichText): ITgRichTextSpoiler;
    /// <summary>The text</summary>
    property Text: ITgRichText read GetText;
  end;

  /// <summary>Formatted date and time.</summary>
  ITgRichTextDateTime = interface(ITgRichText)
    ['{D41AE48E-2641-5E99-AA1C-112ED3EFFC37}']
    function GetText: ITgRichText;
    function GetUnixTime: Integer;
    function GetDateTimeFormat: string;
    /// <summary>
    ///   Задаёт text: The text. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithText(const AValue: ITgRichText): ITgRichTextDateTime;
    /// <summary>
    ///   Задаёт unix_time: The Unix time associated with the entity. Значение копируется в момент
    ///   вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithUnixTime(AValue: Integer): ITgRichTextDateTime;
    /// <summary>
    ///   Задаёт date_time_format: The string that defines the formatting of the date and time. See
    ///   date-time entity formatting for more details. Значение копируется в момент вызова:
    ///   последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithDateTimeFormat(const AValue: string): ITgRichTextDateTime;
    /// <summary>The text</summary>
    property Text: ITgRichText read GetText;
    /// <summary>The Unix time associated with the entity</summary>
    property UnixTime: Integer read GetUnixTime;
    /// <summary>
    ///   The string that defines the formatting of the date and time. See date-time entity
    ///   formatting for more details.
    /// </summary>
    property DateTimeFormat: string read GetDateTimeFormat;
  end;

  /// <summary>A mention of a Telegram user by their identifier.</summary>
  ITgRichTextTextMention = interface(ITgRichText)
    ['{DACA171A-C2F7-563B-8595-EA2C488F9887}']
    function GetText: ITgRichText;
    function GetUser: ITgUser;
    /// <summary>
    ///   Задаёт text: The text. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithText(const AValue: ITgRichText): ITgRichTextTextMention;
    /// <summary>
    ///   Задаёт user: The mentioned user. Значение копируется в момент вызова: последующие
    ///   изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithUser(const AValue: ITgUser): ITgRichTextTextMention;
    /// <summary>The text</summary>
    property Text: ITgRichText read GetText;
    /// <summary>The mentioned user</summary>
    property User: ITgUser read GetUser;
  end;

  /// <summary>A subscript text.</summary>
  ITgRichTextSubscript = interface(ITgRichText)
    ['{9AFA5309-D471-59D1-9CD3-01FB5531A49E}']
    function GetText: ITgRichText;
    /// <summary>
    ///   Задаёт text: The text. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithText(const AValue: ITgRichText): ITgRichTextSubscript;
    /// <summary>The text</summary>
    property Text: ITgRichText read GetText;
  end;

  /// <summary>A superscript text.</summary>
  ITgRichTextSuperscript = interface(ITgRichText)
    ['{BEF809B1-8A9E-5B18-9089-FFB2FB274479}']
    function GetText: ITgRichText;
    /// <summary>
    ///   Задаёт text: The text. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithText(const AValue: ITgRichText): ITgRichTextSuperscript;
    /// <summary>The text</summary>
    property Text: ITgRichText read GetText;
  end;

  /// <summary>A marked text.</summary>
  ITgRichTextMarked = interface(ITgRichText)
    ['{941A3D5F-5335-530A-ACA4-ECC97D1B99F1}']
    function GetText: ITgRichText;
    /// <summary>
    ///   Задаёт text: The text. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithText(const AValue: ITgRichText): ITgRichTextMarked;
    /// <summary>The text</summary>
    property Text: ITgRichText read GetText;
  end;

  /// <summary>A monowidth text.</summary>
  ITgRichTextCode = interface(ITgRichText)
    ['{40148802-5709-5F2C-92C6-8781FA34B78B}']
    function GetText: ITgRichText;
    /// <summary>
    ///   Задаёт text: The text. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithText(const AValue: ITgRichText): ITgRichTextCode;
    /// <summary>The text</summary>
    property Text: ITgRichText read GetText;
  end;

  /// <summary>A custom emoji.</summary>
  ITgRichTextCustomEmoji = interface(ITgRichText)
    ['{FE8742BD-9D94-52C2-B425-36F1902BD888}']
    function GetCustomEmojiId: string;
    function GetAlternativeText: string;
    /// <summary>
    ///   Задаёт custom_emoji_id: Unique identifier of the custom emoji. Use getCustomEmojiStickers
    ///   to get full information about the sticker. Значение копируется в момент вызова:
    ///   последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithCustomEmojiId(const AValue: string): ITgRichTextCustomEmoji;
    /// <summary>
    ///   Задаёт alternative_text: Alternative emoji for the custom emoji. Значение копируется в
    ///   момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithAlternativeText(const AValue: string): ITgRichTextCustomEmoji;
    /// <summary>
    ///   Unique identifier of the custom emoji. Use getCustomEmojiStickers to get full information
    ///   about the sticker.
    /// </summary>
    property CustomEmojiId: string read GetCustomEmojiId;
    /// <summary>Alternative emoji for the custom emoji</summary>
    property AlternativeText: string read GetAlternativeText;
  end;

  /// <summary>A mathematical expression.</summary>
  ITgRichTextMathematicalExpression = interface(ITgRichText)
    ['{D8822034-6E10-5163-A442-3E524EC22DA9}']
    function GetExpression: string;
    /// <summary>
    ///   Задаёт expression: The expression in LaTeX format. Значение копируется в момент вызова:
    ///   последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithExpression(const AValue: string): ITgRichTextMathematicalExpression;
    /// <summary>The expression in LaTeX format</summary>
    property Expression: string read GetExpression;
  end;

  /// <summary>A text with a link.</summary>
  ITgRichTextUrl = interface(ITgRichText)
    ['{31C9FA71-987C-51A5-8FCD-4BEF3ADF6488}']
    function GetText: ITgRichText;
    function GetUrl: string;
    /// <summary>
    ///   Задаёт text: The text. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithText(const AValue: ITgRichText): ITgRichTextUrl;
    /// <summary>
    ///   Задаёт url: URL of the link. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithUrl(const AValue: string): ITgRichTextUrl;
    /// <summary>The text</summary>
    property Text: ITgRichText read GetText;
    /// <summary>URL of the link</summary>
    property Url: string read GetUrl;
  end;

  /// <summary>A text with an email address.</summary>
  ITgRichTextEmailAddress = interface(ITgRichText)
    ['{31F70C97-1227-583F-A714-ACB37810F662}']
    function GetText: ITgRichText;
    function GetEmailAddress: string;
    /// <summary>
    ///   Задаёт text: The text. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithText(const AValue: ITgRichText): ITgRichTextEmailAddress;
    /// <summary>
    ///   Задаёт email_address: The email address. Значение копируется в момент вызова: последующие
    ///   изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithEmailAddress(const AValue: string): ITgRichTextEmailAddress;
    /// <summary>The text</summary>
    property Text: ITgRichText read GetText;
    /// <summary>The email address</summary>
    property EmailAddress: string read GetEmailAddress;
  end;

  /// <summary>A text with a phone number.</summary>
  ITgRichTextPhoneNumber = interface(ITgRichText)
    ['{46FF3401-5D58-5403-90F4-A98C07556CF0}']
    function GetText: ITgRichText;
    function GetPhoneNumber: string;
    /// <summary>
    ///   Задаёт text: The text. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithText(const AValue: ITgRichText): ITgRichTextPhoneNumber;
    /// <summary>
    ///   Задаёт phone_number: The phone number. Значение копируется в момент вызова: последующие
    ///   изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithPhoneNumber(const AValue: string): ITgRichTextPhoneNumber;
    /// <summary>The text</summary>
    property Text: ITgRichText read GetText;
    /// <summary>The phone number</summary>
    property PhoneNumber: string read GetPhoneNumber;
  end;

  /// <summary>A text with a bank card number.</summary>
  ITgRichTextBankCardNumber = interface(ITgRichText)
    ['{DA1F8B8A-CD5A-5ED8-96B1-21ABD3536781}']
    function GetText: ITgRichText;
    function GetBankCardNumber: string;
    /// <summary>
    ///   Задаёт text: The text. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithText(const AValue: ITgRichText): ITgRichTextBankCardNumber;
    /// <summary>
    ///   Задаёт bank_card_number: The bank card number. Значение копируется в момент вызова:
    ///   последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithBankCardNumber(const AValue: string): ITgRichTextBankCardNumber;
    /// <summary>The text</summary>
    property Text: ITgRichText read GetText;
    /// <summary>The bank card number</summary>
    property BankCardNumber: string read GetBankCardNumber;
  end;

  /// <summary>A mention by a username.</summary>
  ITgRichTextMention = interface(ITgRichText)
    ['{59AA0061-A0CE-5359-AEDC-46ADBE515F34}']
    function GetText: ITgRichText;
    function GetUsername: string;
    /// <summary>
    ///   Задаёт text: The text. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithText(const AValue: ITgRichText): ITgRichTextMention;
    /// <summary>
    ///   Задаёт username: The username. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithUsername(const AValue: string): ITgRichTextMention;
    /// <summary>The text</summary>
    property Text: ITgRichText read GetText;
    /// <summary>The username</summary>
    property Username: string read GetUsername;
  end;

  /// <summary>A hashtag.</summary>
  ITgRichTextHashtag = interface(ITgRichText)
    ['{76F8D22B-C0D3-5410-82D5-1413A882560C}']
    function GetText: ITgRichText;
    function GetHashtag: string;
    /// <summary>
    ///   Задаёт text: The text. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithText(const AValue: ITgRichText): ITgRichTextHashtag;
    /// <summary>
    ///   Задаёт hashtag: The hashtag. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithHashtag(const AValue: string): ITgRichTextHashtag;
    /// <summary>The text</summary>
    property Text: ITgRichText read GetText;
    /// <summary>The hashtag</summary>
    property Hashtag: string read GetHashtag;
  end;

  /// <summary>A cashtag.</summary>
  ITgRichTextCashtag = interface(ITgRichText)
    ['{3F27BF00-7449-5643-8D94-57C643EEE76E}']
    function GetText: ITgRichText;
    function GetCashtag: string;
    /// <summary>
    ///   Задаёт text: The text. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithText(const AValue: ITgRichText): ITgRichTextCashtag;
    /// <summary>
    ///   Задаёт cashtag: The cashtag. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithCashtag(const AValue: string): ITgRichTextCashtag;
    /// <summary>The text</summary>
    property Text: ITgRichText read GetText;
    /// <summary>The cashtag</summary>
    property Cashtag: string read GetCashtag;
  end;

  /// <summary>A bot command.</summary>
  ITgRichTextBotCommand = interface(ITgRichText)
    ['{B1A1D21D-D3E4-553C-BB6C-DB3FBDAC9D0A}']
    function GetText: ITgRichText;
    function GetBotCommand: string;
    /// <summary>
    ///   Задаёт text: The text. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithText(const AValue: ITgRichText): ITgRichTextBotCommand;
    /// <summary>
    ///   Задаёт bot_command: The bot command. Значение копируется в момент вызова: последующие
    ///   изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithBotCommand(const AValue: string): ITgRichTextBotCommand;
    /// <summary>The text</summary>
    property Text: ITgRichText read GetText;
    /// <summary>The bot command</summary>
    property BotCommand: string read GetBotCommand;
  end;

  /// <summary>A button.</summary>
  ITgRichTextButton = interface(ITgRichText)
    ['{C1993CA6-5DBB-50D1-B5DF-B9C2FE1889BF}']
    function GetButton: ITgRichMessageButton;
    /// <summary>
    ///   Задаёт button: The button. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithButton(const AValue: ITgRichMessageButton): ITgRichTextButton;
    /// <summary>The button</summary>
    property Button: ITgRichMessageButton read GetButton;
  end;

  /// <summary>An anchor.</summary>
  ITgRichTextAnchor = interface(ITgRichText)
    ['{D58B8C7A-8790-58E3-AF6B-9D0B22785C45}']
    function GetName: string;
    /// <summary>
    ///   Задаёт name: The name of the anchor. Значение копируется в момент вызова: последующие
    ///   изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithName(const AValue: string): ITgRichTextAnchor;
    /// <summary>The name of the anchor</summary>
    property Name: string read GetName;
  end;

  /// <summary>A link to an anchor.</summary>
  ITgRichTextAnchorLink = interface(ITgRichText)
    ['{65063195-A6AB-5E59-B0F7-7EC1280DDAC1}']
    function GetText: ITgRichText;
    function GetAnchorName: string;
    /// <summary>
    ///   Задаёт text: The link text. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithText(const AValue: ITgRichText): ITgRichTextAnchorLink;
    /// <summary>
    ///   Задаёт anchor_name: The name of the anchor. If the name is empty, then the link brings
    ///   back to the top of the message. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithAnchorName(const AValue: string): ITgRichTextAnchorLink;
    /// <summary>The link text</summary>
    property Text: ITgRichText read GetText;
    /// <summary>
    ///   The name of the anchor. If the name is empty, then the link brings back to the top of the
    ///   message.
    /// </summary>
    property AnchorName: string read GetAnchorName;
  end;

  /// <summary>A reference.</summary>
  ITgRichTextReference = interface(ITgRichText)
    ['{C5373BD1-ABFC-5C3A-8EE8-71F3A4E56F07}']
    function GetText: ITgRichText;
    function GetName: string;
    /// <summary>
    ///   Задаёт text: Text of the reference. Значение копируется в момент вызова: последующие
    ///   изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithText(const AValue: ITgRichText): ITgRichTextReference;
    /// <summary>
    ///   Задаёт name: The name of the reference. Значение копируется в момент вызова: последующие
    ///   изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithName(const AValue: string): ITgRichTextReference;
    /// <summary>Text of the reference</summary>
    property Text: ITgRichText read GetText;
    /// <summary>The name of the reference</summary>
    property Name: string read GetName;
  end;

  /// <summary>A link to a reference.</summary>
  ITgRichTextReferenceLink = interface(ITgRichText)
    ['{C9D4974F-AE91-5FDE-8254-27C1961F2E91}']
    function GetText: ITgRichText;
    function GetReferenceName: string;
    /// <summary>
    ///   Задаёт text: The link text. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithText(const AValue: ITgRichText): ITgRichTextReferenceLink;
    /// <summary>
    ///   Задаёт reference_name: The name of the reference. Значение копируется в момент вызова:
    ///   последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithReferenceName(const AValue: string): ITgRichTextReferenceLink;
    /// <summary>The link text</summary>
    property Text: ITgRichText read GetText;
    /// <summary>The name of the reference</summary>
    property ReferenceName: string read GetReferenceName;
  end;

  /// <summary>Caption of a rich formatted block.</summary>
  ITgRichBlockCaption = interface(ITgJsonObject)
    ['{4DA0254D-B5F1-5624-8BB6-3BF8DAE5A456}']
    function GetText: ITgRichText;
    function GetCredit: ITgRichText;
    /// <summary>
    ///   Задаёт text: Block caption. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithText(const AValue: ITgRichText): ITgRichBlockCaption;
    /// <summary>
    ///   Задаёт credit: Optional. Block credit which corresponds to the HTML tag &lt;cite&gt;.
    ///   Значение копируется в момент вызова: последующие изменения переданного объекта на этот не
    ///   влияют.
    /// </summary>
    function WithCredit(const AValue: ITgRichText): ITgRichBlockCaption;
    /// <summary>Block caption</summary>
    property Text: ITgRichText read GetText;
    /// <summary>
    ///   Optional. Block credit which corresponds to the HTML tag &lt;cite&gt;
    /// </summary>
    property Credit: ITgRichText read GetCredit;
  end;

  /// <summary>Cell in a table.</summary>
  ITgRichBlockTableCell = interface(ITgJsonObject)
    ['{227E3A08-0D5E-578E-A1FD-C53D8C45CCBB}']
    function GetText: ITgRichText;
    function GetIsHeader: Boolean;
    function GetColspan: Integer;
    function GetHasColspan: Boolean;
    function GetRowspan: Integer;
    function GetHasRowspan: Boolean;
    function GetAlign: string;
    function GetValign: string;
    /// <summary>
    ///   Задаёт text: Optional. Text in the cell. If omitted, then the cell is invisible. Значение
    ///   копируется в момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithText(const AValue: ITgRichText): ITgRichBlockTableCell;
    /// <summary>
    ///   Задаёт is_header: Optional. True, if the cell is a header cell. Значение копируется в
    ///   момент вызова: последующие изменения переданного объекта на этот не влияют.
    /// </summary>
    function WithIsHeader(AValue: Boolean): ITgRichBlockTableCell;
    /// <summary>
    ///   Задаёт colspan: Optional. The number of columns the cell spans if it is bigger than 1.
    ///   Значение копируется в момент вызова: последующие изменения переданного объекта на этот не
    ///   влияют.
    /// </summary>
    function WithColspan(AValue: Integer): ITgRichBlockTableCell;
    /// <summary>
    ///   Задаёт rowspan: Optional. The number of rows the cell spans if it is bigger than 1.
    ///   Значение копируется в момент вызова: последующие изменения переданного объекта на этот не
    ///   влияют.
    /// </summary>
    function WithRowspan(AValue: Integer): ITgRichBlockTableCell;
    /// <summary>
    ///   Задаёт align: Horizontal cell content alignment. Currently, must be one of “left”,
    ///   “center”, or “right”. Значение копируется в момент вызова: последующие изменения
    ///   переданного объекта на этот не влияют.
    /// </summary>
    function WithAlign(const AValue: string): ITgRichBlockTableCell;
    /// <summary>
    ///   Задаёт valign: Vertical cell content alignment. Currently, must be one of “top”, “middle”,
    ///   or “bottom”. Значение копируется в момент вызова: последующие изменения переданного
    ///   объекта на этот не влияют.
    /// </summary>
    function WithValign(const AValue: string): ITgRichBlockTableCell;
    /// <summary>
    ///   Optional. Text in the cell. If omitted, then the cell is invisible.
    /// </summary>
    property Text: ITgRichText read GetText;
    /// <summary>Optional. True, if the cell is a header cell</summary>
    property IsHeader: Boolean read GetIsHeader;
    /// <summary>
    ///   Optional. The number of columns the cell spans if it is bigger than 1
    /// </summary>
    property Colspan: Integer read GetColspan;
    /// <summary>Поле colspan присутствует.</summary>
    property HasColspan: Boolean read GetHasColspan;
    /// <summary>
    ///   Optional. The number of rows the cell spans if it is bigger than 1
    /// </summary>
    property Rowspan: Integer read GetRowspan;
    /// <summary>Поле rowspan присутствует.</summary>
    property HasRowspan: Boolean read GetHasRowspan;
    /// <summary>
    ///   Horizontal cell content alignment. Currently, must be one of “left”, “center”, or “right”.
    /// </summary>
    property Align: string read GetAlign;
    /// <summary>
    ///   Vertical cell content alignment. Currently, must be one of “top”, “middle”, or “bottom”.
    /// </summary>
    property Valign: string read GetValign;
  end;

  /// <summary>An item of a list.</summary>
  ITgRichBlockListItem = interface(ITgJsonObject)
    ['{66F56AA4-66F7-58B6-875A-C212831CFCCF}']
    function GetRichBlockListItemLabel: string;
    function GetBlocks: TArray<ITgRichBlock>;
    function GetHasCheckbox: Boolean;
    function GetIsChecked: Boolean;
    function GetValue: Integer;
    function GetHasValue: Boolean;
    function GetRichBlockListItemType: string;
    /// <summary>Label of the item</summary>
    property RichBlockListItemLabel: string read GetRichBlockListItemLabel;
    /// <summary>The content of the item</summary>
    property Blocks: TArray<ITgRichBlock> read GetBlocks;
    /// <summary>Optional. True, if the item has a checkbox</summary>
    property HasCheckbox: Boolean read GetHasCheckbox;
    /// <summary>Optional. True, if the item has a checked checkbox</summary>
    property IsChecked: Boolean read GetIsChecked;
    /// <summary>Optional. For ordered lists, the numeric value of the item label</summary>
    property Value: Integer read GetValue;
    /// <summary>Поле value присутствует.</summary>
    property HasValue: Boolean read GetHasValue;
    /// <summary>
    ///   Optional. For ordered lists, the type of the item label; must be one of “a” for lowercase
    ///   letters, “A” for uppercase letters, “i” for lowercase Roman numerals, “I” for uppercase
    ///   Roman numerals, or “1” for decimal numbers
    /// </summary>
    property RichBlockListItemType: string read GetRichBlockListItemType;
  end;

  /// <summary>
  ///   This object represents a block in a rich formatted message. Currently, it can be any of the
  ///   following types: Виды (Kind, As*): ITgRichBlockParagraph, ITgRichBlockSectionHeading,
  ///   ITgRichBlockPreformatted, ITgRichBlockFooter, ITgRichBlockDivider,
  ///   ITgRichBlockMathematicalExpression, ITgRichBlockAnchor, ITgRichBlockList,
  ///   ITgRichBlockBlockQuotation, ITgRichBlockExpandableBlockQuotation, ITgRichBlockPullQuotation,
  ///   ITgRichBlockCollage, ITgRichBlockSlideshow, ITgRichBlockTable, ITgRichBlockDetails,
  ///   ITgRichBlockMap, ITgRichBlockButtons, ITgRichBlockAnimation, ITgRichBlockAudio,
  ///   ITgRichBlockDocument, ITgRichBlockPhoto, ITgRichBlockVideo, ITgRichBlockVoiceNote,
  ///   ITgRichBlockThinking.
  /// </summary>
  ITgRichBlock = interface(ITgJsonObject)
    ['{765C4F82-6F60-57BA-AD97-3BDED137E736}']
    function GetKind: TTgRichBlockKind;
    function GetKindText: string;
    /// <summary>ITgRichBlockParagraph или nil, если объект другого вида.</summary>
    function AsParagraph: ITgRichBlockParagraph;
    /// <summary>ITgRichBlockSectionHeading или nil, если объект другого вида.</summary>
    function AsSectionHeading: ITgRichBlockSectionHeading;
    /// <summary>ITgRichBlockPreformatted или nil, если объект другого вида.</summary>
    function AsPreformatted: ITgRichBlockPreformatted;
    /// <summary>ITgRichBlockFooter или nil, если объект другого вида.</summary>
    function AsFooter: ITgRichBlockFooter;
    /// <summary>ITgRichBlockDivider или nil, если объект другого вида.</summary>
    function AsDivider: ITgRichBlockDivider;
    /// <summary>
    ///   ITgRichBlockMathematicalExpression или nil, если объект другого вида.
    /// </summary>
    function AsMathematicalExpression: ITgRichBlockMathematicalExpression;
    /// <summary>ITgRichBlockAnchor или nil, если объект другого вида.</summary>
    function AsAnchor: ITgRichBlockAnchor;
    /// <summary>ITgRichBlockList или nil, если объект другого вида.</summary>
    function AsList: ITgRichBlockList;
    /// <summary>ITgRichBlockBlockQuotation или nil, если объект другого вида.</summary>
    function AsBlockQuotation: ITgRichBlockBlockQuotation;
    /// <summary>
    ///   ITgRichBlockExpandableBlockQuotation или nil, если объект другого вида.
    /// </summary>
    function AsExpandableBlockQuotation: ITgRichBlockExpandableBlockQuotation;
    /// <summary>ITgRichBlockPullQuotation или nil, если объект другого вида.</summary>
    function AsPullQuotation: ITgRichBlockPullQuotation;
    /// <summary>ITgRichBlockCollage или nil, если объект другого вида.</summary>
    function AsCollage: ITgRichBlockCollage;
    /// <summary>ITgRichBlockSlideshow или nil, если объект другого вида.</summary>
    function AsSlideshow: ITgRichBlockSlideshow;
    /// <summary>ITgRichBlockTable или nil, если объект другого вида.</summary>
    function AsTable: ITgRichBlockTable;
    /// <summary>ITgRichBlockDetails или nil, если объект другого вида.</summary>
    function AsDetails: ITgRichBlockDetails;
    /// <summary>ITgRichBlockMap или nil, если объект другого вида.</summary>
    function AsMap: ITgRichBlockMap;
    /// <summary>ITgRichBlockButtons или nil, если объект другого вида.</summary>
    function AsButtons: ITgRichBlockButtons;
    /// <summary>ITgRichBlockAnimation или nil, если объект другого вида.</summary>
    function AsAnimation: ITgRichBlockAnimation;
    /// <summary>ITgRichBlockAudio или nil, если объект другого вида.</summary>
    function AsAudio: ITgRichBlockAudio;
    /// <summary>ITgRichBlockDocument или nil, если объект другого вида.</summary>
    function AsDocument: ITgRichBlockDocument;
    /// <summary>ITgRichBlockPhoto или nil, если объект другого вида.</summary>
    function AsPhoto: ITgRichBlockPhoto;
    /// <summary>ITgRichBlockVideo или nil, если объект другого вида.</summary>
    function AsVideo: ITgRichBlockVideo;
    /// <summary>ITgRichBlockVoiceNote или nil, если объект другого вида.</summary>
    function AsVoiceNote: ITgRichBlockVoiceNote;
    /// <summary>ITgRichBlockThinking или nil, если объект другого вида.</summary>
    function AsThinking: ITgRichBlockThinking;
    /// <summary>Вид объекта (Unknown — неизвестный этой версии библиотеки).</summary>
    property Kind: TTgRichBlockKind read GetKind;
    /// <summary>
    ///   Значение поля type в JSON как есть (в т.ч. при Kind = Unknown); для вариантов-строк и
    ///   массивов — пустая строка.
    /// </summary>
    property KindText: string read GetKindText;
  end;

  /// <summary>A text paragraph, corresponding to the HTML tag &lt;p&gt;.</summary>
  ITgRichBlockParagraph = interface(ITgRichBlock)
    ['{0751587B-741F-5B20-B1C4-69671F948355}']
    function GetText: ITgRichText;
    /// <summary>Text of the block</summary>
    property Text: ITgRichText read GetText;
  end;

  /// <summary>
  ///   A section heading, corresponding to the HTML tags &lt;h1&gt;, &lt;h2&gt;, &lt;h3&gt;,
  ///   &lt;h4&gt;, &lt;h5&gt;, or &lt;h6&gt;.
  /// </summary>
  ITgRichBlockSectionHeading = interface(ITgRichBlock)
    ['{B08FCA5C-2AB4-5A75-9217-2929085CB5F1}']
    function GetText: ITgRichText;
    function GetSize: Integer;
    /// <summary>Text of the block</summary>
    property Text: ITgRichText read GetText;
    /// <summary>
    ///   Relative size of the text font; 1-6, 1 is the largest, 6 is the smallest
    /// </summary>
    property Size: Integer read GetSize;
  end;

  /// <summary>
  ///   A preformatted text block, corresponding to the nested HTML tags &lt;pre&gt; and
  ///   &lt;code&gt;.
  /// </summary>
  ITgRichBlockPreformatted = interface(ITgRichBlock)
    ['{3AB59ED9-9EDC-5C29-A0EC-2E5D1EABD0CC}']
    function GetText: ITgRichText;
    function GetLanguage: string;
    /// <summary>Text of the block</summary>
    property Text: ITgRichText read GetText;
    /// <summary>Optional. The programming language of the text</summary>
    property Language: string read GetLanguage;
  end;

  /// <summary>A footer, corresponding to the HTML tag &lt;footer&gt;.</summary>
  ITgRichBlockFooter = interface(ITgRichBlock)
    ['{4F98ABD7-E1AF-5C70-B00E-F59626B98937}']
    function GetText: ITgRichText;
    /// <summary>Text of the block</summary>
    property Text: ITgRichText read GetText;
  end;

  /// <summary>A divider, corresponding to the HTML tag &lt;hr/&gt;.</summary>
  ITgRichBlockDivider = interface(ITgRichBlock)
    ['{A0B5CDA1-E272-5084-A538-016DC35F3878}']
  end;

  /// <summary>
  ///   A block with a mathematical expression in LaTeX format, corresponding to the custom HTML tag
  ///   &lt;tg-math-block&gt;.
  /// </summary>
  ITgRichBlockMathematicalExpression = interface(ITgRichBlock)
    ['{012CC4F0-FE6B-5FBF-80BB-3A213711F2C2}']
    function GetExpression: string;
    /// <summary>The mathematical expression in LaTeX format</summary>
    property Expression: string read GetExpression;
  end;

  /// <summary>
  ///   A block with an anchor, corresponding to the HTML tag &lt;a&gt; with the attribute name.
  /// </summary>
  ITgRichBlockAnchor = interface(ITgRichBlock)
    ['{FC8A9728-2764-5EE1-AF44-B156E94F4E2C}']
    function GetName: string;
    /// <summary>The name of the anchor</summary>
    property Name: string read GetName;
  end;

  /// <summary>
  ///   A list of blocks, corresponding to the HTML tag &lt;ul&gt; or &lt;ol&gt; with multiple
  ///   nested tags &lt;li&gt;.
  /// </summary>
  ITgRichBlockList = interface(ITgRichBlock)
    ['{0687803C-7C3E-56E9-808E-FFF904AB3A5F}']
    function GetItems: TArray<ITgRichBlockListItem>;
    /// <summary>Items of the list</summary>
    property Items: TArray<ITgRichBlockListItem> read GetItems;
  end;

  /// <summary>
  ///   A block quotation, corresponding to the HTML tag &lt;blockquote&gt;.
  /// </summary>
  ITgRichBlockBlockQuotation = interface(ITgRichBlock)
    ['{B33F3B7D-672B-5E79-B80B-2341B913CEBA}']
    function GetBlocks: TArray<ITgRichBlock>;
    function GetCredit: ITgRichText;
    /// <summary>Content of the block</summary>
    property Blocks: TArray<ITgRichBlock> read GetBlocks;
    /// <summary>Optional. Credit of the block</summary>
    property Credit: ITgRichText read GetCredit;
  end;

  /// <summary>
  ///   A block quotation, corresponding to the HTML tag &lt;blockquote&gt; with custom attribute
  ///   "expandable".
  /// </summary>
  ITgRichBlockExpandableBlockQuotation = interface(ITgRichBlock)
    ['{4317B4CD-F17D-5196-8257-BF19B42B1607}']
    function GetText: ITgRichText;
    function GetCredit: ITgRichText;
    /// <summary>Content of the block</summary>
    property Text: ITgRichText read GetText;
    /// <summary>Optional. Credit of the block</summary>
    property Credit: ITgRichText read GetCredit;
  end;

  /// <summary>
  ///   A quotation with centered text, loosely corresponding to the HTML tag &lt;aside&gt;.
  /// </summary>
  ITgRichBlockPullQuotation = interface(ITgRichBlock)
    ['{A241C384-BB01-59B8-A645-4F3A8B01D8B0}']
    function GetText: ITgRichText;
    function GetCredit: ITgRichText;
    /// <summary>Text of the block</summary>
    property Text: ITgRichText read GetText;
    /// <summary>Optional. Credit of the block</summary>
    property Credit: ITgRichText read GetCredit;
  end;

  /// <summary>A collage, corresponding to the custom HTML tag &lt;tg-collage&gt;.</summary>
  ITgRichBlockCollage = interface(ITgRichBlock)
    ['{A3B07B6D-6BC5-5959-9CD3-E0FFB335A7C3}']
    function GetBlocks: TArray<ITgRichBlock>;
    function GetCaption: ITgRichBlockCaption;
    /// <summary>Elements of the collage</summary>
    property Blocks: TArray<ITgRichBlock> read GetBlocks;
    /// <summary>Optional. Caption of the block</summary>
    property Caption: ITgRichBlockCaption read GetCaption;
  end;

  /// <summary>
  ///   A slideshow, corresponding to the custom HTML tag &lt;tg-slideshow&gt;.
  /// </summary>
  ITgRichBlockSlideshow = interface(ITgRichBlock)
    ['{9C245E8C-20F3-59EF-BCD0-3BEF2E539B9C}']
    function GetBlocks: TArray<ITgRichBlock>;
    function GetCaption: ITgRichBlockCaption;
    /// <summary>Elements of the slideshow</summary>
    property Blocks: TArray<ITgRichBlock> read GetBlocks;
    /// <summary>Optional. Caption of the block</summary>
    property Caption: ITgRichBlockCaption read GetCaption;
  end;

  /// <summary>A table, corresponding to the HTML tag &lt;table&gt;.</summary>
  ITgRichBlockTable = interface(ITgRichBlock)
    ['{91DFE5BE-4B4A-5801-AD86-DBBD92C16212}']
    function GetCells: TArray<TArray<ITgRichBlockTableCell>>;
    function GetIsBordered: Boolean;
    function GetIsStriped: Boolean;
    function GetIsCompact: Boolean;
    function GetCaption: ITgRichText;
    /// <summary>Cells of the table</summary>
    property Cells: TArray<TArray<ITgRichBlockTableCell>> read GetCells;
    /// <summary>Optional. True, if the table has borders</summary>
    property IsBordered: Boolean read GetIsBordered;
    /// <summary>Optional. True, if the table is striped</summary>
    property IsStriped: Boolean read GetIsStriped;
    /// <summary>Optional. True, if table cells have smaller indents</summary>
    property IsCompact: Boolean read GetIsCompact;
    /// <summary>Optional. Caption of the table</summary>
    property Caption: ITgRichText read GetCaption;
  end;

  /// <summary>
  ///   An expandable block for details disclosure, corresponding to the HTML tag &lt;details&gt;.
  /// </summary>
  ITgRichBlockDetails = interface(ITgRichBlock)
    ['{FBA75864-4EB6-5A57-8F3E-B40C7122DBD6}']
    function GetSummary: ITgRichText;
    function GetBlocks: TArray<ITgRichBlock>;
    function GetIsOpen: Boolean;
    /// <summary>Always shown summary of the block</summary>
    property Summary: ITgRichText read GetSummary;
    /// <summary>Content of the block</summary>
    property Blocks: TArray<ITgRichBlock> read GetBlocks;
    /// <summary>Optional. True, if the content of the block is visible by default</summary>
    property IsOpen: Boolean read GetIsOpen;
  end;

  /// <summary>
  ///   A block with a map, corresponding to the custom HTML tag &lt;tg-map&gt;.
  /// </summary>
  ITgRichBlockMap = interface(ITgRichBlock)
    ['{35B6B22A-27DB-5D35-9A52-6D3C134369C0}']
    function GetLocation: ITgLocation;
    function GetZoom: Integer;
    function GetWidth: Integer;
    function GetHeight: Integer;
    function GetCaption: ITgRichBlockCaption;
    /// <summary>Location of the center of the map</summary>
    property Location: ITgLocation read GetLocation;
    /// <summary>Map zoom level</summary>
    property Zoom: Integer read GetZoom;
    /// <summary>Expected width of the map</summary>
    property Width: Integer read GetWidth;
    /// <summary>Expected height of the map</summary>
    property Height: Integer read GetHeight;
    /// <summary>Optional. Caption of the block</summary>
    property Caption: ITgRichBlockCaption read GetCaption;
  end;

  /// <summary>
  ///   A block containing a list of buttons that are shown in one row, corresponding to the custom
  ///   HTML tag &lt;tg-button-row&gt;.
  /// </summary>
  ITgRichBlockButtons = interface(ITgRichBlock)
    ['{8E30DBB5-A671-58F8-93F5-11CC6D16BC29}']
    function GetButtons: TArray<ITgRichMessageButton>;
    function GetAlign: string;
    /// <summary>The buttons</summary>
    property Buttons: TArray<ITgRichMessageButton> read GetButtons;
    /// <summary>
    ///   Optional. Horizontal alignment of the buttons. Currently, must be one of “left”, “center”,
    ///   or “right”.
    /// </summary>
    property Align: string read GetAlign;
  end;

  /// <summary>
  ///   A block with an animation, corresponding to the HTML tag &lt;video&gt;.
  /// </summary>
  ITgRichBlockAnimation = interface(ITgRichBlock)
    ['{D57E59C9-ADF5-50C5-A740-C54C90B26961}']
    function GetAnimation: ITgAnimation;
    function GetHasSpoiler: Boolean;
    function GetCaption: ITgRichBlockCaption;
    /// <summary>The animation</summary>
    property Animation: ITgAnimation read GetAnimation;
    /// <summary>
    ///   Optional. True, if the media preview is covered by a spoiler animation
    /// </summary>
    property HasSpoiler: Boolean read GetHasSpoiler;
    /// <summary>Optional. Caption of the block</summary>
    property Caption: ITgRichBlockCaption read GetCaption;
  end;

  /// <summary>
  ///   A block with a music file, corresponding to the HTML tag &lt;audio&gt;.
  /// </summary>
  ITgRichBlockAudio = interface(ITgRichBlock)
    ['{B72E0F93-01F1-5B0B-92BF-7CCEC3843214}']
    function GetAudio: ITgAudio;
    function GetCaption: ITgRichBlockCaption;
    /// <summary>The audio</summary>
    property Audio: ITgAudio read GetAudio;
    /// <summary>Optional. Caption of the block</summary>
    property Caption: ITgRichBlockCaption read GetCaption;
  end;

  /// <summary>
  ///   A block with a general file, corresponding to the custom HTML tag &lt;tg-document&gt;.
  /// </summary>
  ITgRichBlockDocument = interface(ITgRichBlock)
    ['{DD38BD9D-C9E7-5E10-84C9-D60BF9743C9D}']
    function GetDocument: ITgDocument;
    function GetCaption: ITgRichBlockCaption;
    /// <summary>The document</summary>
    property Document: ITgDocument read GetDocument;
    /// <summary>Optional. Caption of the block</summary>
    property Caption: ITgRichBlockCaption read GetCaption;
  end;

  /// <summary>A block with a photo, corresponding to the HTML tag &lt;img&gt;.</summary>
  ITgRichBlockPhoto = interface(ITgRichBlock)
    ['{8C73A541-E6F7-56BD-A3C4-70C13353FA17}']
    function GetPhoto: TArray<ITgPhotoSize>;
    function GetHasSpoiler: Boolean;
    function GetCaption: ITgRichBlockCaption;
    /// <summary>Available sizes of the photo</summary>
    property Photo: TArray<ITgPhotoSize> read GetPhoto;
    /// <summary>
    ///   Optional. True, if the media preview is covered by a spoiler animation
    /// </summary>
    property HasSpoiler: Boolean read GetHasSpoiler;
    /// <summary>Optional. Caption of the block</summary>
    property Caption: ITgRichBlockCaption read GetCaption;
  end;

  /// <summary>A block with a video, corresponding to the HTML tag &lt;video&gt;.</summary>
  ITgRichBlockVideo = interface(ITgRichBlock)
    ['{F433598C-AF43-57C3-A9C7-B9F35B97AD7A}']
    function GetVideo: ITgVideo;
    function GetHasSpoiler: Boolean;
    function GetCaption: ITgRichBlockCaption;
    /// <summary>The video</summary>
    property Video: ITgVideo read GetVideo;
    /// <summary>
    ///   Optional. True, if the media preview is covered by a spoiler animation
    /// </summary>
    property HasSpoiler: Boolean read GetHasSpoiler;
    /// <summary>Optional. Caption of the block</summary>
    property Caption: ITgRichBlockCaption read GetCaption;
  end;

  /// <summary>
  ///   A block with a voice note, corresponding to the HTML tag &lt;audio&gt;.
  /// </summary>
  ITgRichBlockVoiceNote = interface(ITgRichBlock)
    ['{BE25D79C-F1EA-5AF4-A026-CBDB07FAEE1E}']
    function GetVoiceNote: ITgVoice;
    function GetCaption: ITgRichBlockCaption;
    /// <summary>The voice note</summary>
    property VoiceNote: ITgVoice read GetVoiceNote;
    /// <summary>Optional. Caption of the block</summary>
    property Caption: ITgRichBlockCaption read GetCaption;
  end;

  /// <summary>
  ///   A block with a “Thinking…” placeholder, corresponding to the custom HTML tag
  ///   &lt;tg-thinking&gt;. The block may be used only in sendRichMessageDraft, therefore it can't
  ///   be received in messages. See https://t.me/addemoji/AIActions for examples of custom emoji
  ///   that are recommended for usage in the block.
  /// </summary>
  ITgRichBlockThinking = interface(ITgRichBlock)
    ['{4EC2CEF8-1DCB-50A2-B666-3977ED23E3C6}']
    function GetText: ITgRichText;
    /// <summary>
    ///   Text of the block. See https://t.me/addemoji/AIActions for examples of custom emoji that
    ///   are recommended for usage in the block.
    /// </summary>
    property Text: ITgRichText read GetText;
  end;

  /// <summary>An item of a list to be sent.</summary>
  ITgInputRichBlockListItem = interface(ITgOutObject)
    ['{4F634A0A-80F7-5CBF-B066-DF371E0CA793}']
    /// <summary>Задаёт blocks: The content of the item</summary>
    function WithBlocks(const AValue: array of TTgInputRichBlock): ITgInputRichBlockListItem;
    /// <summary>
    ///   Задаёт has_checkbox: Optional. Pass True if the item has a checkbox
    /// </summary>
    function WithHasCheckbox(AValue: Boolean): ITgInputRichBlockListItem;
    /// <summary>
    ///   Задаёт is_checked: Optional. Pass True if the item has a checked checkbox
    /// </summary>
    function WithIsChecked(AValue: Boolean): ITgInputRichBlockListItem;
    /// <summary>
    ///   Задаёт value: Optional. For ordered lists, the numeric value of the item label
    /// </summary>
    function WithValue(AValue: Integer): ITgInputRichBlockListItem;
    /// <summary>
    ///   Задаёт type: Optional. For ordered lists, the type of the item label; must be one of “a”
    ///   for lowercase letters, “A” for uppercase letters, “i” for lowercase Roman numerals, “I”
    ///   for uppercase Roman numerals, or “1” for decimal numbers
    /// </summary>
    function WithInputRichBlockListItemType(const AValue: string): ITgInputRichBlockListItem;
  end;

  /// <summary>A text paragraph, corresponding to the HTML tag &lt;p&gt;.</summary>
  ITgInputRichBlockParagraph = interface(ITgOutObject)
    ['{064FF6B4-9AF5-5DFD-BBE4-5D82D4F5769A}']
    /// <summary>Задаёт text: Text of the block</summary>
    function WithText(const AValue: ITgRichText): ITgInputRichBlockParagraph;
  end;

  /// <summary>
  ///   A section heading, corresponding to the HTML tags &lt;h1&gt;, &lt;h2&gt;, &lt;h3&gt;,
  ///   &lt;h4&gt;, &lt;h5&gt;, or &lt;h6&gt;.
  /// </summary>
  ITgInputRichBlockSectionHeading = interface(ITgOutObject)
    ['{DB8F204B-B4C3-58D1-A848-1B8BDF6179AD}']
    /// <summary>Задаёт text: Text of the block</summary>
    function WithText(const AValue: ITgRichText): ITgInputRichBlockSectionHeading;
    /// <summary>
    ///   Задаёт size: Relative size of the text font; 1-6, 1 is the largest, 6 is the smallest
    /// </summary>
    function WithSize(AValue: Integer): ITgInputRichBlockSectionHeading;
  end;

  /// <summary>
  ///   A preformatted text block, corresponding to the nested HTML tags &lt;pre&gt; and
  ///   &lt;code&gt;.
  /// </summary>
  ITgInputRichBlockPreformatted = interface(ITgOutObject)
    ['{5693FADD-F9BD-5966-AD2B-F85F274D722A}']
    /// <summary>Задаёт text: Text of the block</summary>
    function WithText(const AValue: ITgRichText): ITgInputRichBlockPreformatted;
    /// <summary>Задаёт language: Optional. The programming language of the text</summary>
    function WithLanguage(const AValue: string): ITgInputRichBlockPreformatted;
  end;

  /// <summary>A footer, corresponding to the HTML tag &lt;footer&gt;.</summary>
  ITgInputRichBlockFooter = interface(ITgOutObject)
    ['{8AA5C656-55DF-59CB-B091-5D259C51B278}']
    /// <summary>Задаёт text: Text of the block</summary>
    function WithText(const AValue: ITgRichText): ITgInputRichBlockFooter;
  end;

  /// <summary>A divider, corresponding to the HTML tag &lt;hr/&gt;.</summary>
  ITgInputRichBlockDivider = interface(ITgOutObject)
    ['{9311E606-468E-50E9-A9CF-5BD8A82B3334}']
  end;

  /// <summary>
  ///   A block with a mathematical expression in LaTeX format, corresponding to the custom HTML tag
  ///   &lt;tg-math-block&gt;.
  /// </summary>
  ITgInputRichBlockMathematicalExpression = interface(ITgOutObject)
    ['{6CCBD887-3192-5B0F-9326-4643DDFC9435}']
    /// <summary>Задаёт expression: The mathematical expression in LaTeX format</summary>
    function WithExpression(const AValue: string): ITgInputRichBlockMathematicalExpression;
  end;

  /// <summary>
  ///   A block with an anchor, corresponding to the HTML tag &lt;a&gt; with the attribute name.
  /// </summary>
  ITgInputRichBlockAnchor = interface(ITgOutObject)
    ['{CEC40BD7-30B1-588B-81F8-C16D90462A23}']
    /// <summary>Задаёт name: The name of the anchor</summary>
    function WithName(const AValue: string): ITgInputRichBlockAnchor;
  end;

  /// <summary>
  ///   A list of blocks, corresponding to the HTML tag &lt;ul&gt; or &lt;ol&gt; with multiple
  ///   nested tags &lt;li&gt;.
  /// </summary>
  ITgInputRichBlockList = interface(ITgOutObject)
    ['{00B5F4FB-B56D-5024-8844-03C0609A039B}']
    /// <summary>Задаёт items: Items of the list</summary>
    function WithItems(const AValue: array of ITgInputRichBlockListItem): ITgInputRichBlockList;
  end;

  /// <summary>
  ///   A block quotation, corresponding to the HTML tag &lt;blockquote&gt;.
  /// </summary>
  ITgInputRichBlockBlockQuotation = interface(ITgOutObject)
    ['{16A80053-AB22-56AF-B2EA-61E528A16307}']
    /// <summary>Задаёт blocks: Content of the block</summary>
    function WithBlocks(const AValue: array of TTgInputRichBlock): ITgInputRichBlockBlockQuotation;
    /// <summary>Задаёт credit: Optional. Credit of the block</summary>
    function WithCredit(const AValue: ITgRichText): ITgInputRichBlockBlockQuotation;
  end;

  /// <summary>
  ///   A block quotation, corresponding to the HTML tag &lt;blockquote&gt; with custom attribute
  ///   "expandable".
  /// </summary>
  ITgInputRichBlockExpandableBlockQuotation = interface(ITgOutObject)
    ['{1B8BBB09-7A3E-58B1-B41C-6252E89528A1}']
    /// <summary>Задаёт text: Content of the block</summary>
    function WithText(const AValue: ITgRichText): ITgInputRichBlockExpandableBlockQuotation;
    /// <summary>Задаёт credit: Optional. Credit of the block</summary>
    function WithCredit(const AValue: ITgRichText): ITgInputRichBlockExpandableBlockQuotation;
  end;

  /// <summary>
  ///   A quotation with centered text, loosely corresponding to the HTML tag &lt;aside&gt;.
  /// </summary>
  ITgInputRichBlockPullQuotation = interface(ITgOutObject)
    ['{705E5154-C59C-5933-816B-16ECC8AAB4A2}']
    /// <summary>Задаёт text: Text of the block</summary>
    function WithText(const AValue: ITgRichText): ITgInputRichBlockPullQuotation;
    /// <summary>Задаёт credit: Optional. Credit of the block</summary>
    function WithCredit(const AValue: ITgRichText): ITgInputRichBlockPullQuotation;
  end;

  /// <summary>A collage, corresponding to the custom HTML tag &lt;tg-collage&gt;.</summary>
  ITgInputRichBlockCollage = interface(ITgOutObject)
    ['{C4828EB5-2D08-50FA-AC35-32EFAB2D7BD9}']
    /// <summary>Задаёт blocks: Elements of the collage</summary>
    function WithBlocks(const AValue: array of TTgInputRichBlock): ITgInputRichBlockCollage;
    /// <summary>Задаёт caption: Optional. Caption of the block</summary>
    function WithCaption(const AValue: ITgRichBlockCaption): ITgInputRichBlockCollage;
  end;

  /// <summary>
  ///   A slideshow, corresponding to the custom HTML tag &lt;tg-slideshow&gt;.
  /// </summary>
  ITgInputRichBlockSlideshow = interface(ITgOutObject)
    ['{2C2815E8-64A2-567A-906B-48C928A5C131}']
    /// <summary>Задаёт blocks: Elements of the slideshow</summary>
    function WithBlocks(const AValue: array of TTgInputRichBlock): ITgInputRichBlockSlideshow;
    /// <summary>Задаёт caption: Optional. Caption of the block</summary>
    function WithCaption(const AValue: ITgRichBlockCaption): ITgInputRichBlockSlideshow;
  end;

  /// <summary>A table, corresponding to the HTML tag &lt;table&gt;.</summary>
  ITgInputRichBlockTable = interface(ITgOutObject)
    ['{8AAF31CF-0150-567D-8C31-6E0751C6E5E7}']
    /// <summary>Задаёт cells: Cells of the table</summary>
    function WithCells(const AValue: array of TArray<ITgRichBlockTableCell>): ITgInputRichBlockTable;
    /// <summary>Добавляет строку в cells.</summary>
    function WithCellsRow(const ARow: array of ITgRichBlockTableCell): ITgInputRichBlockTable;
    /// <summary>Задаёт is_bordered: Optional. Pass True if the table has borders</summary>
    function WithIsBordered(AValue: Boolean): ITgInputRichBlockTable;
    /// <summary>Задаёт is_striped: Optional. Pass True if the table is striped</summary>
    function WithIsStriped(AValue: Boolean): ITgInputRichBlockTable;
    /// <summary>
    ///   Задаёт is_compact: Optional. Pass True if table cells must have smaller indents
    /// </summary>
    function WithIsCompact(AValue: Boolean): ITgInputRichBlockTable;
    /// <summary>Задаёт caption: Optional. Caption of the table</summary>
    function WithCaption(const AValue: ITgRichText): ITgInputRichBlockTable;
  end;

  /// <summary>
  ///   An expandable block for details disclosure, corresponding to the HTML tag &lt;details&gt;.
  /// </summary>
  ITgInputRichBlockDetails = interface(ITgOutObject)
    ['{F64BFA11-3602-50ED-9967-4E44AFC52A5A}']
    /// <summary>Задаёт summary: Always shown summary of the block</summary>
    function WithSummary(const AValue: ITgRichText): ITgInputRichBlockDetails;
    /// <summary>Задаёт blocks: Content of the block</summary>
    function WithBlocks(const AValue: array of TTgInputRichBlock): ITgInputRichBlockDetails;
    /// <summary>
    ///   Задаёт is_open: Optional. Pass True if the content of the block is visible by default
    /// </summary>
    function WithIsOpen(AValue: Boolean): ITgInputRichBlockDetails;
  end;

  /// <summary>
  ///   A block with a map, corresponding to the custom HTML tag &lt;tg-map&gt;. The map's width and
  ///   height must not exceed 10000 in total. The width and height ratio must be at most 20.
  /// </summary>
  ITgInputRichBlockMap = interface(ITgOutObject)
    ['{F2C3913D-FFD5-5D1B-B71E-6CB08C410949}']
    /// <summary>Задаёт location: Location of the center of the map</summary>
    function WithLocation(const AValue: ITgLocation): ITgInputRichBlockMap;
    /// <summary>Задаёт zoom: Optional. Map zoom level; 0-24</summary>
    function WithZoom(AValue: Integer): ITgInputRichBlockMap;
    /// <summary>Задаёт width: Optional. Map width; 0-10000</summary>
    function WithWidth(AValue: Integer): ITgInputRichBlockMap;
    /// <summary>Задаёт height: Optional. Map height; 0-10000</summary>
    function WithHeight(AValue: Integer): ITgInputRichBlockMap;
    /// <summary>Задаёт caption: Optional. Caption of the block</summary>
    function WithCaption(const AValue: ITgRichBlockCaption): ITgInputRichBlockMap;
  end;

  /// <summary>
  ///   A block containing a list of buttons that are shown in one row, corresponding to the custom
  ///   HTML tag &lt;tg-button-row&gt;.
  /// </summary>
  ITgInputRichBlockButtons = interface(ITgOutObject)
    ['{05CEDB62-8E2D-5CDA-AA8F-2F00A7E1EA33}']
    /// <summary>Задаёт buttons: List of 1-8 buttons to send</summary>
    function WithButtons(const AValue: array of ITgRichMessageButton): ITgInputRichBlockButtons;
    /// <summary>
    ///   Задаёт align: Optional. Horizontal alignment of the buttons. Currently, must be one of
    ///   “left”, “center”, or “right”.
    /// </summary>
    function WithAlign(const AValue: string): ITgInputRichBlockButtons;
  end;

  /// <summary>
  ///   A block with an animation, corresponding to the HTML tag &lt;video&gt;.
  /// </summary>
  ITgInputRichBlockAnimation = interface(ITgOutObject)
    ['{4D068624-B9D8-51FC-90BE-A8FAB18C1EB7}']
    /// <summary>Задаёт animation: The animation. Caption is ignored.</summary>
    function WithAnimation(const AValue: ITgInputMediaAnimation): ITgInputRichBlockAnimation;
    /// <summary>Задаёт caption: Optional. Caption of the block</summary>
    function WithCaption(const AValue: ITgRichBlockCaption): ITgInputRichBlockAnimation;
  end;

  /// <summary>
  ///   A block with a music file, corresponding to the HTML tag &lt;audio&gt;.
  /// </summary>
  ITgInputRichBlockAudio = interface(ITgOutObject)
    ['{CA122118-5DF1-5289-BB5D-83A8472F1BB4}']
    /// <summary>Задаёт audio: The audio. Caption is ignored.</summary>
    function WithAudio(const AValue: ITgInputMediaAudio): ITgInputRichBlockAudio;
    /// <summary>Задаёт caption: Optional. Caption of the block</summary>
    function WithCaption(const AValue: ITgRichBlockCaption): ITgInputRichBlockAudio;
  end;

  /// <summary>
  ///   A block with a general file, corresponding to the custom HTML tag &lt;tg-document&gt;.
  /// </summary>
  ITgInputRichBlockDocument = interface(ITgOutObject)
    ['{1C2131E2-5A77-50AC-9237-581C5E1E0AF8}']
    /// <summary>Задаёт document: The document. Caption is ignored.</summary>
    function WithDocument(const AValue: ITgInputMediaDocument): ITgInputRichBlockDocument;
    /// <summary>Задаёт caption: Optional. Caption of the block</summary>
    function WithCaption(const AValue: ITgRichBlockCaption): ITgInputRichBlockDocument;
  end;

  /// <summary>A block with a photo, corresponding to the HTML tag &lt;img&gt;.</summary>
  ITgInputRichBlockPhoto = interface(ITgOutObject)
    ['{8022AE96-B7FA-5D71-A540-0EE1549CA312}']
    /// <summary>Задаёт photo: The photo. Caption is ignored.</summary>
    function WithPhoto(const AValue: ITgInputMediaPhoto): ITgInputRichBlockPhoto;
    /// <summary>Задаёт caption: Optional. Caption of the block</summary>
    function WithCaption(const AValue: ITgRichBlockCaption): ITgInputRichBlockPhoto;
  end;

  /// <summary>A block with a video, corresponding to the HTML tag &lt;video&gt;.</summary>
  ITgInputRichBlockVideo = interface(ITgOutObject)
    ['{55E70C52-20BA-5185-9CEA-6519032248F0}']
    /// <summary>Задаёт video: The video. Caption is ignored.</summary>
    function WithVideo(const AValue: ITgInputMediaVideo): ITgInputRichBlockVideo;
    /// <summary>Задаёт caption: Optional. Caption of the block</summary>
    function WithCaption(const AValue: ITgRichBlockCaption): ITgInputRichBlockVideo;
  end;

  /// <summary>
  ///   A block with a voice note, corresponding to the HTML tag &lt;audio&gt;.
  /// </summary>
  ITgInputRichBlockVoiceNote = interface(ITgOutObject)
    ['{4231066A-0181-5F16-889D-C27D87B03A4C}']
    /// <summary>Задаёт voice_note: The voice note. Caption is ignored.</summary>
    function WithVoiceNote(const AValue: ITgInputMediaVoiceNote): ITgInputRichBlockVoiceNote;
    /// <summary>Задаёт caption: Optional. Caption of the block</summary>
    function WithCaption(const AValue: ITgRichBlockCaption): ITgInputRichBlockVoiceNote;
  end;

  /// <summary>
  ///   A block with a “Thinking…” placeholder, corresponding to the custom HTML tag
  ///   &lt;tg-thinking&gt;. The block may be used only in sendRichMessageDraft, therefore it can't
  ///   be received in messages. See https://t.me/addemoji/AIActions for examples of custom emoji
  ///   that are recommended for usage in the block.
  /// </summary>
  ITgInputRichBlockThinking = interface(ITgOutObject)
    ['{E7E78889-F182-5580-81CC-9B2498B19E84}']
    /// <summary>
    ///   Задаёт text: Text of the block. See https://t.me/addemoji/AIActions for examples of custom
    ///   emoji that are recommended for usage in the block.
    /// </summary>
    function WithText(const AValue: ITgRichText): ITgInputRichBlockThinking;
  end;

  /// <summary>
  ///   This object represents an incoming inline query. When the user sends an empty query, your
  ///   bot could return some default or trending results.
  /// </summary>
  ITgInlineQuery = interface(ITgJsonObject)
    ['{D7C47DB5-DC14-5759-96F7-D43416831870}']
    function GetId: string;
    function GetFrom: ITgUser;
    function GetQuery: string;
    function GetOffset: string;
    function GetChatType: string;
    function GetLocation: ITgLocation;
    /// <summary>Unique identifier for this query</summary>
    property Id: string read GetId;
    /// <summary>Sender</summary>
    property From: ITgUser read GetFrom;
    /// <summary>Text of the query (up to 256 characters)</summary>
    property Query: string read GetQuery;
    /// <summary>
    ///   Offset of the results to be returned, can be controlled by the bot
    /// </summary>
    property Offset: string read GetOffset;
    /// <summary>
    ///   Optional. Type of the chat from which the inline query was sent. Can be either “sender”
    ///   for a private chat with the inline query sender, “private”, “group”, “supergroup”, or
    ///   “channel”. The chat type should be always known for requests sent from official clients
    ///   and most third-party clients, unless the request was sent from a secret chat.
    /// </summary>
    property ChatType: string read GetChatType;
    /// <summary>
    ///   Optional. Sender location, only for bots that request user location
    /// </summary>
    property Location: ITgLocation read GetLocation;
  end;

  /// <summary>
  ///   This object represents a button to be shown above inline query results. You must use exactly
  ///   one of the optional fields.
  /// </summary>
  ITgInlineQueryResultsButton = interface(ITgOutObject)
    ['{8B87E6C8-1319-5572-9201-BC9A5E9BE70D}']
    /// <summary>Задаёт text: Label text on the button</summary>
    function WithText(const AValue: string): ITgInlineQueryResultsButton;
    /// <summary>
    ///   Задаёт web_app: Optional. Description of the Web App that will be launched when the user
    ///   presses the button. The Web App will be able to switch back to the inline mode using the
    ///   method switchInlineQuery inside the Web App.
    /// </summary>
    function WithWebApp(const AValue: ITgWebAppInfo): ITgInlineQueryResultsButton;
    /// <summary>
    ///   Задаёт start_parameter: Optional. Deep-linking parameter for the /start message sent to
    ///   the bot when a user presses the button. 1-64 characters, only A-Z, a-z, 0-9, _ and - are
    ///   allowed.
    /// </summary>
    function WithStartParameter(const AValue: string): ITgInlineQueryResultsButton;
  end;

  /// <summary>Represents a link to an article or web page.</summary>
  ITgInlineQueryResultArticle = interface(ITgOutObject)
    ['{11EF2164-74AD-5B83-8489-AFA38A1655C6}']
    /// <summary>Задаёт id: Unique identifier for this result, 1-64 Bytes</summary>
    function WithId(const AValue: string): ITgInlineQueryResultArticle;
    /// <summary>Задаёт title: Title of the result</summary>
    function WithTitle(const AValue: string): ITgInlineQueryResultArticle;
    /// <summary>Задаёт input_message_content: Content of the message to be sent</summary>
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultArticle;
    /// <summary>
    ///   Задаёт reply_markup: Optional. Inline keyboard attached to the message
    /// </summary>
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultArticle;
    /// <summary>Задаёт url: Optional. URL of the result</summary>
    function WithUrl(const AValue: string): ITgInlineQueryResultArticle;
    /// <summary>Задаёт description: Optional. Short description of the result</summary>
    function WithDescription(const AValue: string): ITgInlineQueryResultArticle;
    /// <summary>
    ///   Задаёт thumbnail_url: Optional. Url of the thumbnail for the result
    /// </summary>
    function WithThumbnailUrl(const AValue: string): ITgInlineQueryResultArticle;
    /// <summary>Задаёт thumbnail_width: Optional. Thumbnail width</summary>
    function WithThumbnailWidth(AValue: Integer): ITgInlineQueryResultArticle;
    /// <summary>Задаёт thumbnail_height: Optional. Thumbnail height</summary>
    function WithThumbnailHeight(AValue: Integer): ITgInlineQueryResultArticle;
  end;

  /// <summary>
  ///   Represents a link to a photo. By default, this photo will be sent by the user with optional
  ///   caption. Alternatively, you can use input_message_content to send a message with the
  ///   specified content instead of the photo.
  /// </summary>
  ITgInlineQueryResultPhoto = interface(ITgOutObject)
    ['{1325E468-5AB0-52FB-8641-B453FE9ACD6F}']
    /// <summary>Задаёт id: Unique identifier for this result, 1-64 bytes</summary>
    function WithId(const AValue: string): ITgInlineQueryResultPhoto;
    /// <summary>
    ///   Задаёт photo_url: A valid URL of the photo. Photo must be in JPEG format. Photo size must
    ///   not exceed 5MB.
    /// </summary>
    function WithPhotoUrl(const AValue: string): ITgInlineQueryResultPhoto;
    /// <summary>Задаёт thumbnail_url: URL of the thumbnail for the photo</summary>
    function WithThumbnailUrl(const AValue: string): ITgInlineQueryResultPhoto;
    /// <summary>Задаёт photo_width: Optional. Width of the photo</summary>
    function WithPhotoWidth(AValue: Integer): ITgInlineQueryResultPhoto;
    /// <summary>Задаёт photo_height: Optional. Height of the photo</summary>
    function WithPhotoHeight(AValue: Integer): ITgInlineQueryResultPhoto;
    /// <summary>Задаёт title: Optional. Title for the result</summary>
    function WithTitle(const AValue: string): ITgInlineQueryResultPhoto;
    /// <summary>Задаёт description: Optional. Short description of the result</summary>
    function WithDescription(const AValue: string): ITgInlineQueryResultPhoto;
    /// <summary>
    ///   Задаёт caption: Optional. Caption of the photo to be sent, 0-1024 characters after
    ///   entities parsing
    /// </summary>
    function WithCaption(const AValue: string): ITgInlineQueryResultPhoto;
    /// <summary>
    ///   Задаёт parse_mode: Optional. Mode for parsing entities in the photo caption. See
    ///   formatting options for more details.
    /// </summary>
    function WithParseMode(const AValue: string): ITgInlineQueryResultPhoto;
    /// <summary>
    ///   Задаёт caption_entities: Optional. List of special entities that appear in the caption,
    ///   which can be specified instead of parse_mode
    /// </summary>
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultPhoto;
    /// <summary>
    ///   Задаёт show_caption_above_media: Optional. Pass True if the caption must be shown above
    ///   the message media
    /// </summary>
    function WithShowCaptionAboveMedia(AValue: Boolean): ITgInlineQueryResultPhoto;
    /// <summary>
    ///   Задаёт reply_markup: Optional. Inline keyboard attached to the message
    /// </summary>
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultPhoto;
    /// <summary>
    ///   Задаёт input_message_content: Optional. Content of the message to be sent instead of the
    ///   photo
    /// </summary>
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultPhoto;
  end;

  /// <summary>
  ///   Represents a link to an animated GIF file. By default, this animated GIF file will be sent
  ///   by the user with optional caption. Alternatively, you can use input_message_content to send
  ///   a message with the specified content instead of the animation.
  /// </summary>
  ITgInlineQueryResultGif = interface(ITgOutObject)
    ['{F20A2888-29AB-5342-BF0C-DC3ECDD867F6}']
    /// <summary>Задаёт id: Unique identifier for this result, 1-64 bytes</summary>
    function WithId(const AValue: string): ITgInlineQueryResultGif;
    /// <summary>Задаёт gif_url: A valid URL for the GIF file</summary>
    function WithGifUrl(const AValue: string): ITgInlineQueryResultGif;
    /// <summary>Задаёт gif_width: Optional. Width of the GIF</summary>
    function WithGifWidth(AValue: Integer): ITgInlineQueryResultGif;
    /// <summary>Задаёт gif_height: Optional. Height of the GIF</summary>
    function WithGifHeight(AValue: Integer): ITgInlineQueryResultGif;
    /// <summary>Задаёт gif_duration: Optional. Duration of the GIF in seconds</summary>
    function WithGifDuration(AValue: Integer): ITgInlineQueryResultGif;
    /// <summary>
    ///   Задаёт thumbnail_url: URL of the static (JPEG or GIF) or animated (MPEG4) thumbnail for
    ///   the result
    /// </summary>
    function WithThumbnailUrl(const AValue: string): ITgInlineQueryResultGif;
    /// <summary>
    ///   Задаёт thumbnail_mime_type: Optional. MIME type of the thumbnail, must be one of
    ///   “image/jpeg”, “image/gif”, or “video/mp4”. Defaults to “image/jpeg”.
    /// </summary>
    function WithThumbnailMimeType(const AValue: string): ITgInlineQueryResultGif;
    /// <summary>Задаёт title: Optional. Title for the result</summary>
    function WithTitle(const AValue: string): ITgInlineQueryResultGif;
    /// <summary>
    ///   Задаёт caption: Optional. Caption of the GIF file to be sent, 0-1024 characters after
    ///   entities parsing
    /// </summary>
    function WithCaption(const AValue: string): ITgInlineQueryResultGif;
    /// <summary>
    ///   Задаёт parse_mode: Optional. Mode for parsing entities in the caption. See formatting
    ///   options for more details.
    /// </summary>
    function WithParseMode(const AValue: string): ITgInlineQueryResultGif;
    /// <summary>
    ///   Задаёт caption_entities: Optional. List of special entities that appear in the caption,
    ///   which can be specified instead of parse_mode
    /// </summary>
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultGif;
    /// <summary>
    ///   Задаёт show_caption_above_media: Optional. Pass True if the caption must be shown above
    ///   the message media
    /// </summary>
    function WithShowCaptionAboveMedia(AValue: Boolean): ITgInlineQueryResultGif;
    /// <summary>
    ///   Задаёт reply_markup: Optional. Inline keyboard attached to the message
    /// </summary>
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultGif;
    /// <summary>
    ///   Задаёт input_message_content: Optional. Content of the message to be sent instead of the
    ///   GIF animation
    /// </summary>
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultGif;
  end;

  /// <summary>
  ///   Represents a link to a video animation (H.264/MPEG-4 AVC video without sound). By default,
  ///   this animated MPEG-4 file will be sent by the user with optional caption. Alternatively, you
  ///   can use input_message_content to send a message with the specified content instead of the
  ///   animation.
  /// </summary>
  ITgInlineQueryResultMpeg4Gif = interface(ITgOutObject)
    ['{A7FCF866-2C40-5A5F-81F0-20F45ACB4727}']
    /// <summary>Задаёт id: Unique identifier for this result, 1-64 bytes</summary>
    function WithId(const AValue: string): ITgInlineQueryResultMpeg4Gif;
    /// <summary>Задаёт mpeg4_url: A valid URL for the MPEG4 file</summary>
    function WithMpeg4Url(const AValue: string): ITgInlineQueryResultMpeg4Gif;
    /// <summary>Задаёт mpeg4_width: Optional. Video width</summary>
    function WithMpeg4Width(AValue: Integer): ITgInlineQueryResultMpeg4Gif;
    /// <summary>Задаёт mpeg4_height: Optional. Video height</summary>
    function WithMpeg4Height(AValue: Integer): ITgInlineQueryResultMpeg4Gif;
    /// <summary>Задаёт mpeg4_duration: Optional. Video duration in seconds</summary>
    function WithMpeg4Duration(AValue: Integer): ITgInlineQueryResultMpeg4Gif;
    /// <summary>
    ///   Задаёт thumbnail_url: URL of the static (JPEG or GIF) or animated (MPEG4) thumbnail for
    ///   the result
    /// </summary>
    function WithThumbnailUrl(const AValue: string): ITgInlineQueryResultMpeg4Gif;
    /// <summary>
    ///   Задаёт thumbnail_mime_type: Optional. MIME type of the thumbnail, must be one of
    ///   “image/jpeg”, “image/gif”, or “video/mp4”. Defaults to “image/jpeg”.
    /// </summary>
    function WithThumbnailMimeType(const AValue: string): ITgInlineQueryResultMpeg4Gif;
    /// <summary>Задаёт title: Optional. Title for the result</summary>
    function WithTitle(const AValue: string): ITgInlineQueryResultMpeg4Gif;
    /// <summary>
    ///   Задаёт caption: Optional. Caption of the MPEG-4 file to be sent, 0-1024 characters after
    ///   entities parsing
    /// </summary>
    function WithCaption(const AValue: string): ITgInlineQueryResultMpeg4Gif;
    /// <summary>
    ///   Задаёт parse_mode: Optional. Mode for parsing entities in the caption. See formatting
    ///   options for more details.
    /// </summary>
    function WithParseMode(const AValue: string): ITgInlineQueryResultMpeg4Gif;
    /// <summary>
    ///   Задаёт caption_entities: Optional. List of special entities that appear in the caption,
    ///   which can be specified instead of parse_mode
    /// </summary>
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultMpeg4Gif;
    /// <summary>
    ///   Задаёт show_caption_above_media: Optional. Pass True if the caption must be shown above
    ///   the message media
    /// </summary>
    function WithShowCaptionAboveMedia(AValue: Boolean): ITgInlineQueryResultMpeg4Gif;
    /// <summary>
    ///   Задаёт reply_markup: Optional. Inline keyboard attached to the message
    /// </summary>
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultMpeg4Gif;
    /// <summary>
    ///   Задаёт input_message_content: Optional. Content of the message to be sent instead of the
    ///   video animation
    /// </summary>
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultMpeg4Gif;
  end;

  /// <summary>
  ///   Represents a link to a page containing an embedded video player or a video file. By default,
  ///   this video file will be sent by the user with an optional caption. Alternatively, you can
  ///   use input_message_content to send a message with the specified content instead of the video.
  ///   If an InlineQueryResultVideo message contains an embedded video (e.g., YouTube), you must
  ///   replace its content using input_message_content.
  /// </summary>
  ITgInlineQueryResultVideo = interface(ITgOutObject)
    ['{764E3546-7D47-5FC6-B07E-33934E27041E}']
    /// <summary>Задаёт id: Unique identifier for this result, 1-64 bytes</summary>
    function WithId(const AValue: string): ITgInlineQueryResultVideo;
    /// <summary>
    ///   Задаёт video_url: A valid URL for the embedded video player or video file
    /// </summary>
    function WithVideoUrl(const AValue: string): ITgInlineQueryResultVideo;
    /// <summary>
    ///   Задаёт mime_type: MIME type of the content of the video URL, “text/html” or “video/mp4”
    /// </summary>
    function WithMimeType(const AValue: string): ITgInlineQueryResultVideo;
    /// <summary>
    ///   Задаёт thumbnail_url: URL of the thumbnail (JPEG only) for the video
    /// </summary>
    function WithThumbnailUrl(const AValue: string): ITgInlineQueryResultVideo;
    /// <summary>Задаёт title: Title for the result</summary>
    function WithTitle(const AValue: string): ITgInlineQueryResultVideo;
    /// <summary>
    ///   Задаёт caption: Optional. Caption of the video to be sent, 0-1024 characters after
    ///   entities parsing
    /// </summary>
    function WithCaption(const AValue: string): ITgInlineQueryResultVideo;
    /// <summary>
    ///   Задаёт parse_mode: Optional. Mode for parsing entities in the video caption. See
    ///   formatting options for more details.
    /// </summary>
    function WithParseMode(const AValue: string): ITgInlineQueryResultVideo;
    /// <summary>
    ///   Задаёт caption_entities: Optional. List of special entities that appear in the caption,
    ///   which can be specified instead of parse_mode
    /// </summary>
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultVideo;
    /// <summary>
    ///   Задаёт show_caption_above_media: Optional. Pass True if the caption must be shown above
    ///   the message media
    /// </summary>
    function WithShowCaptionAboveMedia(AValue: Boolean): ITgInlineQueryResultVideo;
    /// <summary>Задаёт video_width: Optional. Video width</summary>
    function WithVideoWidth(AValue: Integer): ITgInlineQueryResultVideo;
    /// <summary>Задаёт video_height: Optional. Video height</summary>
    function WithVideoHeight(AValue: Integer): ITgInlineQueryResultVideo;
    /// <summary>Задаёт video_duration: Optional. Video duration in seconds</summary>
    function WithVideoDuration(AValue: Integer): ITgInlineQueryResultVideo;
    /// <summary>Задаёт description: Optional. Short description of the result</summary>
    function WithDescription(const AValue: string): ITgInlineQueryResultVideo;
    /// <summary>
    ///   Задаёт reply_markup: Optional. Inline keyboard attached to the message
    /// </summary>
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultVideo;
    /// <summary>
    ///   Задаёт input_message_content: Optional. Content of the message to be sent instead of the
    ///   video. This field is required if InlineQueryResultVideo is used to send an HTML-page as a
    ///   result (e.g., a YouTube video).
    /// </summary>
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultVideo;
  end;

  /// <summary>
  ///   Represents a link to an MP3 audio file. By default, this audio file will be sent by the
  ///   user. Alternatively, you can use input_message_content to send a message with the specified
  ///   content instead of the audio.
  /// </summary>
  ITgInlineQueryResultAudio = interface(ITgOutObject)
    ['{D63199E3-C220-5AC1-9BCF-113D22115410}']
    /// <summary>Задаёт id: Unique identifier for this result, 1-64 bytes</summary>
    function WithId(const AValue: string): ITgInlineQueryResultAudio;
    /// <summary>Задаёт audio_url: A valid URL for the audio file</summary>
    function WithAudioUrl(const AValue: string): ITgInlineQueryResultAudio;
    /// <summary>Задаёт title: Title</summary>
    function WithTitle(const AValue: string): ITgInlineQueryResultAudio;
    /// <summary>
    ///   Задаёт caption: Optional. Caption, 0-1024 characters after entities parsing
    /// </summary>
    function WithCaption(const AValue: string): ITgInlineQueryResultAudio;
    /// <summary>
    ///   Задаёт parse_mode: Optional. Mode for parsing entities in the audio caption. See
    ///   formatting options for more details.
    /// </summary>
    function WithParseMode(const AValue: string): ITgInlineQueryResultAudio;
    /// <summary>
    ///   Задаёт caption_entities: Optional. List of special entities that appear in the caption,
    ///   which can be specified instead of parse_mode
    /// </summary>
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultAudio;
    /// <summary>Задаёт performer: Optional. Performer</summary>
    function WithPerformer(const AValue: string): ITgInlineQueryResultAudio;
    /// <summary>Задаёт audio_duration: Optional. Audio duration in seconds</summary>
    function WithAudioDuration(AValue: Integer): ITgInlineQueryResultAudio;
    /// <summary>
    ///   Задаёт reply_markup: Optional. Inline keyboard attached to the message
    /// </summary>
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultAudio;
    /// <summary>
    ///   Задаёт input_message_content: Optional. Content of the message to be sent instead of the
    ///   audio
    /// </summary>
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultAudio;
  end;

  /// <summary>
  ///   Represents a link to a voice recording in an .OGG container encoded with OPUS. By default,
  ///   this voice recording will be sent by the user. Alternatively, you can use
  ///   input_message_content to send a message with the specified content instead of the the voice
  ///   message.
  /// </summary>
  ITgInlineQueryResultVoice = interface(ITgOutObject)
    ['{3E0BEC34-D9DA-5E7B-BD7A-1B66C4858DBF}']
    /// <summary>Задаёт id: Unique identifier for this result, 1-64 bytes</summary>
    function WithId(const AValue: string): ITgInlineQueryResultVoice;
    /// <summary>Задаёт voice_url: A valid URL for the voice recording</summary>
    function WithVoiceUrl(const AValue: string): ITgInlineQueryResultVoice;
    /// <summary>Задаёт title: Recording title</summary>
    function WithTitle(const AValue: string): ITgInlineQueryResultVoice;
    /// <summary>
    ///   Задаёт caption: Optional. Caption, 0-1024 characters after entities parsing
    /// </summary>
    function WithCaption(const AValue: string): ITgInlineQueryResultVoice;
    /// <summary>
    ///   Задаёт parse_mode: Optional. Mode for parsing entities in the voice message caption. See
    ///   formatting options for more details.
    /// </summary>
    function WithParseMode(const AValue: string): ITgInlineQueryResultVoice;
    /// <summary>
    ///   Задаёт caption_entities: Optional. List of special entities that appear in the caption,
    ///   which can be specified instead of parse_mode
    /// </summary>
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultVoice;
    /// <summary>Задаёт voice_duration: Optional. Recording duration in seconds</summary>
    function WithVoiceDuration(AValue: Integer): ITgInlineQueryResultVoice;
    /// <summary>
    ///   Задаёт reply_markup: Optional. Inline keyboard attached to the message
    /// </summary>
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultVoice;
    /// <summary>
    ///   Задаёт input_message_content: Optional. Content of the message to be sent instead of the
    ///   voice recording
    /// </summary>
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultVoice;
  end;

  /// <summary>
  ///   Represents a link to a file. By default, this file will be sent by the user with an optional
  ///   caption. Alternatively, you can use input_message_content to send a message with the
  ///   specified content instead of the file. Currently, only .PDF and .ZIP files can be sent using
  ///   this method.
  /// </summary>
  ITgInlineQueryResultDocument = interface(ITgOutObject)
    ['{84436D31-082F-5E51-8749-F15F7D865628}']
    /// <summary>Задаёт id: Unique identifier for this result, 1-64 bytes</summary>
    function WithId(const AValue: string): ITgInlineQueryResultDocument;
    /// <summary>Задаёт title: Title for the result</summary>
    function WithTitle(const AValue: string): ITgInlineQueryResultDocument;
    /// <summary>
    ///   Задаёт caption: Optional. Caption of the document to be sent, 0-1024 characters after
    ///   entities parsing
    /// </summary>
    function WithCaption(const AValue: string): ITgInlineQueryResultDocument;
    /// <summary>
    ///   Задаёт parse_mode: Optional. Mode for parsing entities in the document caption. See
    ///   formatting options for more details.
    /// </summary>
    function WithParseMode(const AValue: string): ITgInlineQueryResultDocument;
    /// <summary>
    ///   Задаёт caption_entities: Optional. List of special entities that appear in the caption,
    ///   which can be specified instead of parse_mode
    /// </summary>
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultDocument;
    /// <summary>Задаёт document_url: A valid URL for the file</summary>
    function WithDocumentUrl(const AValue: string): ITgInlineQueryResultDocument;
    /// <summary>
    ///   Задаёт mime_type: MIME type of the content of the file, either “application/pdf” or
    ///   “application/zip”
    /// </summary>
    function WithMimeType(const AValue: string): ITgInlineQueryResultDocument;
    /// <summary>Задаёт description: Optional. Short description of the result</summary>
    function WithDescription(const AValue: string): ITgInlineQueryResultDocument;
    /// <summary>
    ///   Задаёт reply_markup: Optional. Inline keyboard attached to the message
    /// </summary>
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultDocument;
    /// <summary>
    ///   Задаёт input_message_content: Optional. Content of the message to be sent instead of the
    ///   file
    /// </summary>
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultDocument;
    /// <summary>
    ///   Задаёт thumbnail_url: Optional. URL of the thumbnail (JPEG only) for the file
    /// </summary>
    function WithThumbnailUrl(const AValue: string): ITgInlineQueryResultDocument;
    /// <summary>Задаёт thumbnail_width: Optional. Thumbnail width</summary>
    function WithThumbnailWidth(AValue: Integer): ITgInlineQueryResultDocument;
    /// <summary>Задаёт thumbnail_height: Optional. Thumbnail height</summary>
    function WithThumbnailHeight(AValue: Integer): ITgInlineQueryResultDocument;
  end;

  /// <summary>
  ///   Represents a location on a map. By default, the location will be sent by the user.
  ///   Alternatively, you can use input_message_content to send a message with the specified
  ///   content instead of the location.
  /// </summary>
  ITgInlineQueryResultLocation = interface(ITgOutObject)
    ['{35ADC7AC-32B6-54A7-8B19-E1C888DFA832}']
    /// <summary>Задаёт id: Unique identifier for this result, 1-64 Bytes</summary>
    function WithId(const AValue: string): ITgInlineQueryResultLocation;
    /// <summary>Задаёт latitude: Location latitude in degrees</summary>
    function WithLatitude(AValue: Double): ITgInlineQueryResultLocation;
    /// <summary>Задаёт longitude: Location longitude in degrees</summary>
    function WithLongitude(AValue: Double): ITgInlineQueryResultLocation;
    /// <summary>Задаёт title: Location title</summary>
    function WithTitle(const AValue: string): ITgInlineQueryResultLocation;
    /// <summary>
    ///   Задаёт horizontal_accuracy: Optional. The radius of uncertainty for the location, measured
    ///   in meters; 0-1500
    /// </summary>
    function WithHorizontalAccuracy(AValue: Double): ITgInlineQueryResultLocation;
    /// <summary>
    ///   Задаёт live_period: Optional. Period in seconds during which the location can be updated,
    ///   must be between 60 and 86400, or 0x7FFFFFFF for live locations that can be edited
    ///   indefinitely
    /// </summary>
    function WithLivePeriod(AValue: Integer): ITgInlineQueryResultLocation;
    /// <summary>
    ///   Задаёт heading: Optional. For live locations, a direction in which the user is moving, in
    ///   degrees. Must be between 1 and 360 if specified.
    /// </summary>
    function WithHeading(AValue: Integer): ITgInlineQueryResultLocation;
    /// <summary>
    ///   Задаёт proximity_alert_radius: Optional. For live locations, a maximum distance for
    ///   proximity alerts about approaching another chat member, in meters. Must be between 1 and
    ///   100000 if specified.
    /// </summary>
    function WithProximityAlertRadius(AValue: Integer): ITgInlineQueryResultLocation;
    /// <summary>
    ///   Задаёт reply_markup: Optional. Inline keyboard attached to the message
    /// </summary>
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultLocation;
    /// <summary>
    ///   Задаёт input_message_content: Optional. Content of the message to be sent instead of the
    ///   location
    /// </summary>
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultLocation;
    /// <summary>
    ///   Задаёт thumbnail_url: Optional. Url of the thumbnail for the result
    /// </summary>
    function WithThumbnailUrl(const AValue: string): ITgInlineQueryResultLocation;
    /// <summary>Задаёт thumbnail_width: Optional. Thumbnail width</summary>
    function WithThumbnailWidth(AValue: Integer): ITgInlineQueryResultLocation;
    /// <summary>Задаёт thumbnail_height: Optional. Thumbnail height</summary>
    function WithThumbnailHeight(AValue: Integer): ITgInlineQueryResultLocation;
  end;

  /// <summary>
  ///   Represents a venue. By default, the venue will be sent by the user. Alternatively, you can
  ///   use input_message_content to send a message with the specified content instead of the venue.
  /// </summary>
  ITgInlineQueryResultVenue = interface(ITgOutObject)
    ['{280F5306-8089-5693-82AF-011CC85DC846}']
    /// <summary>Задаёт id: Unique identifier for this result, 1-64 Bytes</summary>
    function WithId(const AValue: string): ITgInlineQueryResultVenue;
    /// <summary>Задаёт latitude: Latitude of the venue location in degrees</summary>
    function WithLatitude(AValue: Double): ITgInlineQueryResultVenue;
    /// <summary>Задаёт longitude: Longitude of the venue location in degrees</summary>
    function WithLongitude(AValue: Double): ITgInlineQueryResultVenue;
    /// <summary>Задаёт title: Title of the venue</summary>
    function WithTitle(const AValue: string): ITgInlineQueryResultVenue;
    /// <summary>Задаёт address: Address of the venue</summary>
    function WithAddress(const AValue: string): ITgInlineQueryResultVenue;
    /// <summary>
    ///   Задаёт foursquare_id: Optional. Foursquare identifier of the venue if known
    /// </summary>
    function WithFoursquareId(const AValue: string): ITgInlineQueryResultVenue;
    /// <summary>
    ///   Задаёт foursquare_type: Optional. Foursquare type of the venue, if known. (For example,
    ///   “arts_entertainment/default”, “arts_entertainment/aquarium” or “food/icecream”.)
    /// </summary>
    function WithFoursquareType(const AValue: string): ITgInlineQueryResultVenue;
    /// <summary>
    ///   Задаёт google_place_id: Optional. Google Places identifier of the venue
    /// </summary>
    function WithGooglePlaceId(const AValue: string): ITgInlineQueryResultVenue;
    /// <summary>
    ///   Задаёт google_place_type: Optional. Google Places type of the venue. (See supported
    ///   types.)
    /// </summary>
    function WithGooglePlaceType(const AValue: string): ITgInlineQueryResultVenue;
    /// <summary>
    ///   Задаёт reply_markup: Optional. Inline keyboard attached to the message
    /// </summary>
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultVenue;
    /// <summary>
    ///   Задаёт input_message_content: Optional. Content of the message to be sent instead of the
    ///   venue
    /// </summary>
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultVenue;
    /// <summary>
    ///   Задаёт thumbnail_url: Optional. Url of the thumbnail for the result
    /// </summary>
    function WithThumbnailUrl(const AValue: string): ITgInlineQueryResultVenue;
    /// <summary>Задаёт thumbnail_width: Optional. Thumbnail width</summary>
    function WithThumbnailWidth(AValue: Integer): ITgInlineQueryResultVenue;
    /// <summary>Задаёт thumbnail_height: Optional. Thumbnail height</summary>
    function WithThumbnailHeight(AValue: Integer): ITgInlineQueryResultVenue;
  end;

  /// <summary>
  ///   Represents a contact with a phone number. By default, this contact will be sent by the user.
  ///   Alternatively, you can use input_message_content to send a message with the specified
  ///   content instead of the contact.
  /// </summary>
  ITgInlineQueryResultContact = interface(ITgOutObject)
    ['{1647DBF7-0245-5107-8283-2C4F424279B8}']
    /// <summary>Задаёт id: Unique identifier for this result, 1-64 Bytes</summary>
    function WithId(const AValue: string): ITgInlineQueryResultContact;
    /// <summary>Задаёт phone_number: Contact's phone number</summary>
    function WithPhoneNumber(const AValue: string): ITgInlineQueryResultContact;
    /// <summary>Задаёт first_name: Contact's first name</summary>
    function WithFirstName(const AValue: string): ITgInlineQueryResultContact;
    /// <summary>Задаёт last_name: Optional. Contact's last name</summary>
    function WithLastName(const AValue: string): ITgInlineQueryResultContact;
    /// <summary>
    ///   Задаёт vcard: Optional. Additional data about the contact in the form of a vCard, 0-2048
    ///   bytes
    /// </summary>
    function WithVcard(const AValue: string): ITgInlineQueryResultContact;
    /// <summary>
    ///   Задаёт reply_markup: Optional. Inline keyboard attached to the message
    /// </summary>
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultContact;
    /// <summary>
    ///   Задаёт input_message_content: Optional. Content of the message to be sent instead of the
    ///   contact
    /// </summary>
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultContact;
    /// <summary>
    ///   Задаёт thumbnail_url: Optional. Url of the thumbnail for the result
    /// </summary>
    function WithThumbnailUrl(const AValue: string): ITgInlineQueryResultContact;
    /// <summary>Задаёт thumbnail_width: Optional. Thumbnail width</summary>
    function WithThumbnailWidth(AValue: Integer): ITgInlineQueryResultContact;
    /// <summary>Задаёт thumbnail_height: Optional. Thumbnail height</summary>
    function WithThumbnailHeight(AValue: Integer): ITgInlineQueryResultContact;
  end;

  /// <summary>Represents a Game.</summary>
  ITgInlineQueryResultGame = interface(ITgOutObject)
    ['{06DF6042-CB78-5FE3-A8C9-11C0AB23DE8C}']
    /// <summary>Задаёт id: Unique identifier for this result, 1-64 bytes</summary>
    function WithId(const AValue: string): ITgInlineQueryResultGame;
    /// <summary>Задаёт game_short_name: Short name of the game</summary>
    function WithGameShortName(const AValue: string): ITgInlineQueryResultGame;
    /// <summary>
    ///   Задаёт reply_markup: Optional. Inline keyboard attached to the message
    /// </summary>
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultGame;
  end;

  /// <summary>
  ///   Represents a link to a photo stored on the Telegram servers. By default, this photo will be
  ///   sent by the user with an optional caption. Alternatively, you can use input_message_content
  ///   to send a message with the specified content instead of the photo.
  /// </summary>
  ITgInlineQueryResultCachedPhoto = interface(ITgOutObject)
    ['{22F7845B-F686-521B-ADA9-CE172715D597}']
    /// <summary>Задаёт id: Unique identifier for this result, 1-64 bytes</summary>
    function WithId(const AValue: string): ITgInlineQueryResultCachedPhoto;
    /// <summary>Задаёт photo_file_id: A valid file identifier of the photo</summary>
    function WithPhotoFileId(const AValue: string): ITgInlineQueryResultCachedPhoto;
    /// <summary>Задаёт title: Optional. Title for the result</summary>
    function WithTitle(const AValue: string): ITgInlineQueryResultCachedPhoto;
    /// <summary>Задаёт description: Optional. Short description of the result</summary>
    function WithDescription(const AValue: string): ITgInlineQueryResultCachedPhoto;
    /// <summary>
    ///   Задаёт caption: Optional. Caption of the photo to be sent, 0-1024 characters after
    ///   entities parsing
    /// </summary>
    function WithCaption(const AValue: string): ITgInlineQueryResultCachedPhoto;
    /// <summary>
    ///   Задаёт parse_mode: Optional. Mode for parsing entities in the photo caption. See
    ///   formatting options for more details.
    /// </summary>
    function WithParseMode(const AValue: string): ITgInlineQueryResultCachedPhoto;
    /// <summary>
    ///   Задаёт caption_entities: Optional. List of special entities that appear in the caption,
    ///   which can be specified instead of parse_mode
    /// </summary>
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultCachedPhoto;
    /// <summary>
    ///   Задаёт show_caption_above_media: Optional. Pass True if the caption must be shown above
    ///   the message media
    /// </summary>
    function WithShowCaptionAboveMedia(AValue: Boolean): ITgInlineQueryResultCachedPhoto;
    /// <summary>
    ///   Задаёт reply_markup: Optional. Inline keyboard attached to the message
    /// </summary>
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultCachedPhoto;
    /// <summary>
    ///   Задаёт input_message_content: Optional. Content of the message to be sent instead of the
    ///   photo
    /// </summary>
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultCachedPhoto;
  end;

  /// <summary>
  ///   Represents a link to an animated GIF file stored on the Telegram servers. By default, this
  ///   animated GIF file will be sent by the user with an optional caption. Alternatively, you can
  ///   use input_message_content to send a message with specified content instead of the animation.
  /// </summary>
  ITgInlineQueryResultCachedGif = interface(ITgOutObject)
    ['{753F5494-4B1B-5122-9B68-5E878EA58242}']
    /// <summary>Задаёт id: Unique identifier for this result, 1-64 bytes</summary>
    function WithId(const AValue: string): ITgInlineQueryResultCachedGif;
    /// <summary>Задаёт gif_file_id: A valid file identifier for the GIF file</summary>
    function WithGifFileId(const AValue: string): ITgInlineQueryResultCachedGif;
    /// <summary>Задаёт title: Optional. Title for the result</summary>
    function WithTitle(const AValue: string): ITgInlineQueryResultCachedGif;
    /// <summary>
    ///   Задаёт caption: Optional. Caption of the GIF file to be sent, 0-1024 characters after
    ///   entities parsing
    /// </summary>
    function WithCaption(const AValue: string): ITgInlineQueryResultCachedGif;
    /// <summary>
    ///   Задаёт parse_mode: Optional. Mode for parsing entities in the caption. See formatting
    ///   options for more details.
    /// </summary>
    function WithParseMode(const AValue: string): ITgInlineQueryResultCachedGif;
    /// <summary>
    ///   Задаёт caption_entities: Optional. List of special entities that appear in the caption,
    ///   which can be specified instead of parse_mode
    /// </summary>
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultCachedGif;
    /// <summary>
    ///   Задаёт show_caption_above_media: Optional. Pass True if the caption must be shown above
    ///   the message media
    /// </summary>
    function WithShowCaptionAboveMedia(AValue: Boolean): ITgInlineQueryResultCachedGif;
    /// <summary>
    ///   Задаёт reply_markup: Optional. Inline keyboard attached to the message
    /// </summary>
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultCachedGif;
    /// <summary>
    ///   Задаёт input_message_content: Optional. Content of the message to be sent instead of the
    ///   GIF animation
    /// </summary>
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultCachedGif;
  end;

  /// <summary>
  ///   Represents a link to a video animation (H.264/MPEG-4 AVC video without sound) stored on the
  ///   Telegram servers. By default, this animated MPEG-4 file will be sent by the user with an
  ///   optional caption. Alternatively, you can use input_message_content to send a message with
  ///   the specified content instead of the animation.
  /// </summary>
  ITgInlineQueryResultCachedMpeg4Gif = interface(ITgOutObject)
    ['{05083B9C-86B5-5937-8B13-0883A8844A02}']
    /// <summary>Задаёт id: Unique identifier for this result, 1-64 bytes</summary>
    function WithId(const AValue: string): ITgInlineQueryResultCachedMpeg4Gif;
    /// <summary>Задаёт mpeg4_file_id: A valid file identifier for the MPEG4 file</summary>
    function WithMpeg4FileId(const AValue: string): ITgInlineQueryResultCachedMpeg4Gif;
    /// <summary>Задаёт title: Optional. Title for the result</summary>
    function WithTitle(const AValue: string): ITgInlineQueryResultCachedMpeg4Gif;
    /// <summary>
    ///   Задаёт caption: Optional. Caption of the MPEG-4 file to be sent, 0-1024 characters after
    ///   entities parsing
    /// </summary>
    function WithCaption(const AValue: string): ITgInlineQueryResultCachedMpeg4Gif;
    /// <summary>
    ///   Задаёт parse_mode: Optional. Mode for parsing entities in the caption. See formatting
    ///   options for more details.
    /// </summary>
    function WithParseMode(const AValue: string): ITgInlineQueryResultCachedMpeg4Gif;
    /// <summary>
    ///   Задаёт caption_entities: Optional. List of special entities that appear in the caption,
    ///   which can be specified instead of parse_mode
    /// </summary>
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultCachedMpeg4Gif;
    /// <summary>
    ///   Задаёт show_caption_above_media: Optional. Pass True if the caption must be shown above
    ///   the message media
    /// </summary>
    function WithShowCaptionAboveMedia(AValue: Boolean): ITgInlineQueryResultCachedMpeg4Gif;
    /// <summary>
    ///   Задаёт reply_markup: Optional. Inline keyboard attached to the message
    /// </summary>
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultCachedMpeg4Gif;
    /// <summary>
    ///   Задаёт input_message_content: Optional. Content of the message to be sent instead of the
    ///   video animation
    /// </summary>
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultCachedMpeg4Gif;
  end;

  /// <summary>
  ///   Represents a link to a sticker stored on the Telegram servers. By default, this sticker will
  ///   be sent by the user. Alternatively, you can use input_message_content to send a message with
  ///   the specified content instead of the sticker.
  /// </summary>
  ITgInlineQueryResultCachedSticker = interface(ITgOutObject)
    ['{DBC9BBE9-7DF5-53B0-BE7D-79B684001571}']
    /// <summary>Задаёт id: Unique identifier for this result, 1-64 bytes</summary>
    function WithId(const AValue: string): ITgInlineQueryResultCachedSticker;
    /// <summary>Задаёт sticker_file_id: A valid file identifier of the sticker</summary>
    function WithStickerFileId(const AValue: string): ITgInlineQueryResultCachedSticker;
    /// <summary>
    ///   Задаёт reply_markup: Optional. Inline keyboard attached to the message
    /// </summary>
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultCachedSticker;
    /// <summary>
    ///   Задаёт input_message_content: Optional. Content of the message to be sent instead of the
    ///   sticker
    /// </summary>
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultCachedSticker;
  end;

  /// <summary>
  ///   Represents a link to a file stored on the Telegram servers. By default, this file will be
  ///   sent by the user with an optional caption. Alternatively, you can use input_message_content
  ///   to send a message with the specified content instead of the file.
  /// </summary>
  ITgInlineQueryResultCachedDocument = interface(ITgOutObject)
    ['{BCF639EE-1FE3-546E-8320-BBA5721A2522}']
    /// <summary>Задаёт id: Unique identifier for this result, 1-64 bytes</summary>
    function WithId(const AValue: string): ITgInlineQueryResultCachedDocument;
    /// <summary>Задаёт title: Title for the result</summary>
    function WithTitle(const AValue: string): ITgInlineQueryResultCachedDocument;
    /// <summary>Задаёт document_file_id: A valid file identifier for the file</summary>
    function WithDocumentFileId(const AValue: string): ITgInlineQueryResultCachedDocument;
    /// <summary>Задаёт description: Optional. Short description of the result</summary>
    function WithDescription(const AValue: string): ITgInlineQueryResultCachedDocument;
    /// <summary>
    ///   Задаёт caption: Optional. Caption of the document to be sent, 0-1024 characters after
    ///   entities parsing
    /// </summary>
    function WithCaption(const AValue: string): ITgInlineQueryResultCachedDocument;
    /// <summary>
    ///   Задаёт parse_mode: Optional. Mode for parsing entities in the document caption. See
    ///   formatting options for more details.
    /// </summary>
    function WithParseMode(const AValue: string): ITgInlineQueryResultCachedDocument;
    /// <summary>
    ///   Задаёт caption_entities: Optional. List of special entities that appear in the caption,
    ///   which can be specified instead of parse_mode
    /// </summary>
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultCachedDocument;
    /// <summary>
    ///   Задаёт reply_markup: Optional. Inline keyboard attached to the message
    /// </summary>
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultCachedDocument;
    /// <summary>
    ///   Задаёт input_message_content: Optional. Content of the message to be sent instead of the
    ///   file
    /// </summary>
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultCachedDocument;
  end;

  /// <summary>
  ///   Represents a link to a video file stored on the Telegram servers. By default, this video
  ///   file will be sent by the user with an optional caption. Alternatively, you can use
  ///   input_message_content to send a message with the specified content instead of the video.
  /// </summary>
  ITgInlineQueryResultCachedVideo = interface(ITgOutObject)
    ['{295ED841-4ACE-56D9-902B-8482AE4A2817}']
    /// <summary>Задаёт id: Unique identifier for this result, 1-64 bytes</summary>
    function WithId(const AValue: string): ITgInlineQueryResultCachedVideo;
    /// <summary>Задаёт video_file_id: A valid file identifier for the video file</summary>
    function WithVideoFileId(const AValue: string): ITgInlineQueryResultCachedVideo;
    /// <summary>Задаёт title: Title for the result</summary>
    function WithTitle(const AValue: string): ITgInlineQueryResultCachedVideo;
    /// <summary>Задаёт description: Optional. Short description of the result</summary>
    function WithDescription(const AValue: string): ITgInlineQueryResultCachedVideo;
    /// <summary>
    ///   Задаёт caption: Optional. Caption of the video to be sent, 0-1024 characters after
    ///   entities parsing
    /// </summary>
    function WithCaption(const AValue: string): ITgInlineQueryResultCachedVideo;
    /// <summary>
    ///   Задаёт parse_mode: Optional. Mode for parsing entities in the video caption. See
    ///   formatting options for more details.
    /// </summary>
    function WithParseMode(const AValue: string): ITgInlineQueryResultCachedVideo;
    /// <summary>
    ///   Задаёт caption_entities: Optional. List of special entities that appear in the caption,
    ///   which can be specified instead of parse_mode
    /// </summary>
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultCachedVideo;
    /// <summary>
    ///   Задаёт show_caption_above_media: Optional. Pass True if the caption must be shown above
    ///   the message media
    /// </summary>
    function WithShowCaptionAboveMedia(AValue: Boolean): ITgInlineQueryResultCachedVideo;
    /// <summary>
    ///   Задаёт reply_markup: Optional. Inline keyboard attached to the message
    /// </summary>
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultCachedVideo;
    /// <summary>
    ///   Задаёт input_message_content: Optional. Content of the message to be sent instead of the
    ///   video
    /// </summary>
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultCachedVideo;
  end;

  /// <summary>
  ///   Represents a link to a voice message stored on the Telegram servers. By default, this voice
  ///   message will be sent by the user. Alternatively, you can use input_message_content to send a
  ///   message with the specified content instead of the voice message.
  /// </summary>
  ITgInlineQueryResultCachedVoice = interface(ITgOutObject)
    ['{01DC3521-8A14-5FF2-A3E7-90A7E1818010}']
    /// <summary>Задаёт id: Unique identifier for this result, 1-64 bytes</summary>
    function WithId(const AValue: string): ITgInlineQueryResultCachedVoice;
    /// <summary>
    ///   Задаёт voice_file_id: A valid file identifier for the voice message
    /// </summary>
    function WithVoiceFileId(const AValue: string): ITgInlineQueryResultCachedVoice;
    /// <summary>Задаёт title: Voice message title</summary>
    function WithTitle(const AValue: string): ITgInlineQueryResultCachedVoice;
    /// <summary>
    ///   Задаёт caption: Optional. Caption, 0-1024 characters after entities parsing
    /// </summary>
    function WithCaption(const AValue: string): ITgInlineQueryResultCachedVoice;
    /// <summary>
    ///   Задаёт parse_mode: Optional. Mode for parsing entities in the voice message caption. See
    ///   formatting options for more details.
    /// </summary>
    function WithParseMode(const AValue: string): ITgInlineQueryResultCachedVoice;
    /// <summary>
    ///   Задаёт caption_entities: Optional. List of special entities that appear in the caption,
    ///   which can be specified instead of parse_mode
    /// </summary>
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultCachedVoice;
    /// <summary>
    ///   Задаёт reply_markup: Optional. Inline keyboard attached to the message
    /// </summary>
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultCachedVoice;
    /// <summary>
    ///   Задаёт input_message_content: Optional. Content of the message to be sent instead of the
    ///   voice message
    /// </summary>
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultCachedVoice;
  end;

  /// <summary>
  ///   Represents a link to an MP3 audio file stored on the Telegram servers. By default, this
  ///   audio file will be sent by the user. Alternatively, you can use input_message_content to
  ///   send a message with the specified content instead of the audio.
  /// </summary>
  ITgInlineQueryResultCachedAudio = interface(ITgOutObject)
    ['{9612B06A-3499-5403-A1F1-F89D7609DE8F}']
    /// <summary>Задаёт id: Unique identifier for this result, 1-64 bytes</summary>
    function WithId(const AValue: string): ITgInlineQueryResultCachedAudio;
    /// <summary>Задаёт audio_file_id: A valid file identifier for the audio file</summary>
    function WithAudioFileId(const AValue: string): ITgInlineQueryResultCachedAudio;
    /// <summary>
    ///   Задаёт caption: Optional. Caption, 0-1024 characters after entities parsing
    /// </summary>
    function WithCaption(const AValue: string): ITgInlineQueryResultCachedAudio;
    /// <summary>
    ///   Задаёт parse_mode: Optional. Mode for parsing entities in the audio caption. See
    ///   formatting options for more details.
    /// </summary>
    function WithParseMode(const AValue: string): ITgInlineQueryResultCachedAudio;
    /// <summary>
    ///   Задаёт caption_entities: Optional. List of special entities that appear in the caption,
    ///   which can be specified instead of parse_mode
    /// </summary>
    function WithCaptionEntities(const AValue: array of ITgMessageEntity): ITgInlineQueryResultCachedAudio;
    /// <summary>
    ///   Задаёт reply_markup: Optional. Inline keyboard attached to the message
    /// </summary>
    function WithReplyMarkup(const AValue: ITgInlineKeyboardMarkup): ITgInlineQueryResultCachedAudio;
    /// <summary>
    ///   Задаёт input_message_content: Optional. Content of the message to be sent instead of the
    ///   audio
    /// </summary>
    function WithInputMessageContent(const AValue: TTgInputMessageContent): ITgInlineQueryResultCachedAudio;
  end;

  /// <summary>
  ///   Represents the content of a text message to be sent as the result of an inline query.
  /// </summary>
  ITgInputTextMessageContent = interface(ITgOutObject)
    ['{7F15D29D-B46A-5E85-83D0-4F27AEF4DD2D}']
    /// <summary>
    ///   Задаёт message_text: Text of the message to be sent, 1-4096 characters
    /// </summary>
    function WithMessageText(const AValue: string): ITgInputTextMessageContent;
    /// <summary>
    ///   Задаёт parse_mode: Optional. Mode for parsing entities in the message text. See formatting
    ///   options for more details.
    /// </summary>
    function WithParseMode(const AValue: string): ITgInputTextMessageContent;
    /// <summary>
    ///   Задаёт entities: Optional. List of special entities that appear in message text, which can
    ///   be specified instead of parse_mode
    /// </summary>
    function WithEntities(const AValue: array of ITgMessageEntity): ITgInputTextMessageContent;
    /// <summary>
    ///   Задаёт link_preview_options: Optional. Link preview generation options for the message
    /// </summary>
    function WithLinkPreviewOptions(const AValue: ITgLinkPreviewOptions): ITgInputTextMessageContent;
  end;

  /// <summary>
  ///   Represents the content of a rich message to be sent as the result of an inline query.
  /// </summary>
  ITgInputRichMessageContent = interface(ITgOutObject)
    ['{FBFB61FD-BBF0-5F2F-BDC5-2FD9C9F19620}']
    /// <summary>
    ///   Задаёт rich_message: The message to be sent. Only previously uploaded files may be used in
    ///   the message.
    /// </summary>
    function WithRichMessage(const AValue: ITgInputRichMessage): ITgInputRichMessageContent;
  end;

  /// <summary>
  ///   Represents the content of a location message to be sent as the result of an inline query.
  /// </summary>
  ITgInputLocationMessageContent = interface(ITgOutObject)
    ['{8805DB1D-7E4B-5943-941C-7235DC94981E}']
    /// <summary>Задаёт latitude: Latitude of the location in degrees</summary>
    function WithLatitude(AValue: Double): ITgInputLocationMessageContent;
    /// <summary>Задаёт longitude: Longitude of the location in degrees</summary>
    function WithLongitude(AValue: Double): ITgInputLocationMessageContent;
    /// <summary>
    ///   Задаёт horizontal_accuracy: Optional. The radius of uncertainty for the location, measured
    ///   in meters; 0-1500
    /// </summary>
    function WithHorizontalAccuracy(AValue: Double): ITgInputLocationMessageContent;
    /// <summary>
    ///   Задаёт live_period: Optional. Period in seconds during which the location can be updated,
    ///   must be between 60 and 86400, or 0x7FFFFFFF for live locations that can be edited
    ///   indefinitely
    /// </summary>
    function WithLivePeriod(AValue: Integer): ITgInputLocationMessageContent;
    /// <summary>
    ///   Задаёт heading: Optional. For live locations, a direction in which the user is moving, in
    ///   degrees. Must be between 1 and 360 if specified.
    /// </summary>
    function WithHeading(AValue: Integer): ITgInputLocationMessageContent;
    /// <summary>
    ///   Задаёт proximity_alert_radius: Optional. For live locations, a maximum distance for
    ///   proximity alerts about approaching another chat member, in meters. Must be between 1 and
    ///   100000 if specified.
    /// </summary>
    function WithProximityAlertRadius(AValue: Integer): ITgInputLocationMessageContent;
  end;

  /// <summary>
  ///   Represents the content of a venue message to be sent as the result of an inline query.
  /// </summary>
  ITgInputVenueMessageContent = interface(ITgOutObject)
    ['{76325C14-CEE5-543A-8E98-2650408C3335}']
    /// <summary>Задаёт latitude: Latitude of the venue in degrees</summary>
    function WithLatitude(AValue: Double): ITgInputVenueMessageContent;
    /// <summary>Задаёт longitude: Longitude of the venue in degrees</summary>
    function WithLongitude(AValue: Double): ITgInputVenueMessageContent;
    /// <summary>Задаёт title: Name of the venue</summary>
    function WithTitle(const AValue: string): ITgInputVenueMessageContent;
    /// <summary>Задаёт address: Address of the venue</summary>
    function WithAddress(const AValue: string): ITgInputVenueMessageContent;
    /// <summary>
    ///   Задаёт foursquare_id: Optional. Foursquare identifier of the venue, if known
    /// </summary>
    function WithFoursquareId(const AValue: string): ITgInputVenueMessageContent;
    /// <summary>
    ///   Задаёт foursquare_type: Optional. Foursquare type of the venue, if known. (For example,
    ///   “arts_entertainment/default”, “arts_entertainment/aquarium” or “food/icecream”.)
    /// </summary>
    function WithFoursquareType(const AValue: string): ITgInputVenueMessageContent;
    /// <summary>
    ///   Задаёт google_place_id: Optional. Google Places identifier of the venue
    /// </summary>
    function WithGooglePlaceId(const AValue: string): ITgInputVenueMessageContent;
    /// <summary>
    ///   Задаёт google_place_type: Optional. Google Places type of the venue. (See supported
    ///   types.)
    /// </summary>
    function WithGooglePlaceType(const AValue: string): ITgInputVenueMessageContent;
  end;

  /// <summary>
  ///   Represents the content of a contact message to be sent as the result of an inline query.
  /// </summary>
  ITgInputContactMessageContent = interface(ITgOutObject)
    ['{7C7E68C0-5561-5A2D-8AE2-CAC0B95881D7}']
    /// <summary>Задаёт phone_number: Contact's phone number</summary>
    function WithPhoneNumber(const AValue: string): ITgInputContactMessageContent;
    /// <summary>Задаёт first_name: Contact's first name</summary>
    function WithFirstName(const AValue: string): ITgInputContactMessageContent;
    /// <summary>Задаёт last_name: Optional. Contact's last name</summary>
    function WithLastName(const AValue: string): ITgInputContactMessageContent;
    /// <summary>
    ///   Задаёт vcard: Optional. Additional data about the contact in the form of a vCard, 0-2048
    ///   bytes
    /// </summary>
    function WithVcard(const AValue: string): ITgInputContactMessageContent;
  end;

  /// <summary>
  ///   Represents the content of an invoice message to be sent as the result of an inline query.
  /// </summary>
  ITgInputInvoiceMessageContent = interface(ITgOutObject)
    ['{21CA0C83-00B7-52BF-9E63-8ACA095EA050}']
    /// <summary>Задаёт title: Product name, 1-32 characters</summary>
    function WithTitle(const AValue: string): ITgInputInvoiceMessageContent;
    /// <summary>Задаёт description: Product description, 1-255 characters</summary>
    function WithDescription(const AValue: string): ITgInputInvoiceMessageContent;
    /// <summary>
    ///   Задаёт payload: Bot-defined invoice payload, 1-128 bytes. This will not be displayed to
    ///   the user, use it for your internal processes.
    /// </summary>
    function WithPayload(const AValue: string): ITgInputInvoiceMessageContent;
    /// <summary>
    ///   Задаёт provider_token: Optional. Payment provider token, obtained via @BotFather. Pass an
    ///   empty string for payments in Telegram Stars.
    /// </summary>
    function WithProviderToken(const AValue: string): ITgInputInvoiceMessageContent;
    /// <summary>
    ///   Задаёт currency: Three-letter ISO 4217 currency code, see more on currencies. Pass “XTR”
    ///   for payments in Telegram Stars.
    /// </summary>
    function WithCurrency(const AValue: string): ITgInputInvoiceMessageContent;
    /// <summary>
    ///   Задаёт prices: Price breakdown, a JSON-serialized list of components (e.g. product price,
    ///   tax, discount, delivery cost, delivery tax, bonus, etc.). Must contain exactly one item
    ///   for payments in Telegram Stars.
    /// </summary>
    function WithPrices(const AValue: array of ITgLabeledPrice): ITgInputInvoiceMessageContent;
    /// <summary>
    ///   Задаёт max_tip_amount: Optional. The maximum accepted amount for tips in the smallest
    ///   units of the currency (integer, not float/double). For example, for a maximum tip of US$
    ///   1.45 pass max_tip_amount = 145. See the exp parameter in currencies.json, it shows the
    ///   number of digits past the decimal point for each currency (2 for the majority of
    ///   currencies). Defaults to 0. Not supported for payments in Telegram Stars.
    /// </summary>
    function WithMaxTipAmount(AValue: Integer): ITgInputInvoiceMessageContent;
    /// <summary>
    ///   Задаёт suggested_tip_amounts: Optional. A JSON-serialized Array of suggested amounts of
    ///   tip in the smallest units of the currency (integer, not float/double). At most 4 suggested
    ///   tip amounts can be specified. The suggested tip amounts must be positive, passed in a
    ///   strictly increased order and must not exceed max_tip_amount.
    /// </summary>
    function WithSuggestedTipAmounts(const AValue: TArray<Integer>): ITgInputInvoiceMessageContent;
    /// <summary>
    ///   Задаёт provider_data: Optional. A JSON-serialized object for data about the invoice, which
    ///   will be shared with the payment provider. A detailed description of the required fields
    ///   should be provided by the payment provider.
    /// </summary>
    function WithProviderData(const AValue: string): ITgInputInvoiceMessageContent;
    /// <summary>
    ///   Задаёт photo_url: Optional. URL of the product photo for the invoice. Can be a photo of
    ///   the goods or a marketing image for a service.
    /// </summary>
    function WithPhotoUrl(const AValue: string): ITgInputInvoiceMessageContent;
    /// <summary>Задаёт photo_size: Optional. Photo size in bytes</summary>
    function WithPhotoSize(AValue: Integer): ITgInputInvoiceMessageContent;
    /// <summary>Задаёт photo_width: Optional. Photo width</summary>
    function WithPhotoWidth(AValue: Integer): ITgInputInvoiceMessageContent;
    /// <summary>Задаёт photo_height: Optional. Photo height</summary>
    function WithPhotoHeight(AValue: Integer): ITgInputInvoiceMessageContent;
    /// <summary>
    ///   Задаёт need_name: Optional. Pass True if you require the user's full name to complete the
    ///   order. Ignored for payments in Telegram Stars.
    /// </summary>
    function WithNeedName(AValue: Boolean): ITgInputInvoiceMessageContent;
    /// <summary>
    ///   Задаёт need_phone_number: Optional. Pass True if you require the user's phone number to
    ///   complete the order. Ignored for payments in Telegram Stars.
    /// </summary>
    function WithNeedPhoneNumber(AValue: Boolean): ITgInputInvoiceMessageContent;
    /// <summary>
    ///   Задаёт need_email: Optional. Pass True if you require the user's email address to complete
    ///   the order. Ignored for payments in Telegram Stars.
    /// </summary>
    function WithNeedEmail(AValue: Boolean): ITgInputInvoiceMessageContent;
    /// <summary>
    ///   Задаёт need_shipping_address: Optional. Pass True if you require the user's shipping
    ///   address to complete the order. Ignored for payments in Telegram Stars.
    /// </summary>
    function WithNeedShippingAddress(AValue: Boolean): ITgInputInvoiceMessageContent;
    /// <summary>
    ///   Задаёт send_phone_number_to_provider: Optional. Pass True if the user's phone number
    ///   should be sent to the provider. Ignored for payments in Telegram Stars.
    /// </summary>
    function WithSendPhoneNumberToProvider(AValue: Boolean): ITgInputInvoiceMessageContent;
    /// <summary>
    ///   Задаёт send_email_to_provider: Optional. Pass True if the user's email address should be
    ///   sent to the provider. Ignored for payments in Telegram Stars.
    /// </summary>
    function WithSendEmailToProvider(AValue: Boolean): ITgInputInvoiceMessageContent;
    /// <summary>
    ///   Задаёт is_flexible: Optional. Pass True if the final price depends on the shipping method.
    ///   Ignored for payments in Telegram Stars.
    /// </summary>
    function WithIsFlexible(AValue: Boolean): ITgInputInvoiceMessageContent;
  end;

  /// <summary>
  ///   Represents a result of an inline query that was chosen by the user and sent to their chat
  ///   partner. Note: It is necessary to enable inline feedback via @BotFather in order to receive
  ///   these objects in updates.
  /// </summary>
  ITgChosenInlineResult = interface(ITgJsonObject)
    ['{84E1BC7F-27AC-5BE1-8678-34134AB237A7}']
    function GetResultId: string;
    function GetFrom: ITgUser;
    function GetLocation: ITgLocation;
    function GetInlineMessageId: string;
    function GetQuery: string;
    /// <summary>The unique identifier for the result that was chosen</summary>
    property ResultId: string read GetResultId;
    /// <summary>The user that chose the result</summary>
    property From: ITgUser read GetFrom;
    /// <summary>
    ///   Optional. Sender location, only for bots that require user location
    /// </summary>
    property Location: ITgLocation read GetLocation;
    /// <summary>
    ///   Optional. Identifier of the sent inline message. Available only if there is an inline
    ///   keyboard attached to the message. Will be also received in callback queries and can be
    ///   used to edit the message.
    /// </summary>
    property InlineMessageId: string read GetInlineMessageId;
    /// <summary>The query that was used to obtain the result</summary>
    property Query: string read GetQuery;
  end;

  /// <summary>
  ///   This object represents a portion of the price for goods or services.
  /// </summary>
  ITgLabeledPrice = interface(ITgOutObject)
    ['{4700EF38-972C-5DCA-B695-2EE56539BFC2}']
    /// <summary>Задаёт label: Portion label</summary>
    function WithLabeledPriceLabel(const AValue: string): ITgLabeledPrice;
    /// <summary>
    ///   Задаёт amount: Price of the product in the smallest units of the currency (integer, not
    ///   float/double). For example, for a price of US$ 1.45 pass amount = 145. See the exp
    ///   parameter in currencies.json, it shows the number of digits past the decimal point for
    ///   each currency (2 for the majority of currencies).
    /// </summary>
    function WithAmount(AValue: Integer): ITgLabeledPrice;
  end;

  /// <summary>This object contains basic information about an invoice.</summary>
  ITgInvoice = interface(ITgJsonObject)
    ['{03958C4B-95FE-53A9-8470-6B98020A4CAC}']
    function GetTitle: string;
    function GetDescription: string;
    function GetStartParameter: string;
    function GetCurrency: string;
    function GetTotalAmount: Integer;
    /// <summary>Product name</summary>
    property Title: string read GetTitle;
    /// <summary>Product description</summary>
    property Description: string read GetDescription;
    /// <summary>
    ///   Unique bot deep-linking parameter that can be used to generate this invoice
    /// </summary>
    property StartParameter: string read GetStartParameter;
    /// <summary>
    ///   Three-letter ISO 4217 currency code, or “XTR” for payments in Telegram Stars
    /// </summary>
    property Currency: string read GetCurrency;
    /// <summary>
    ///   Total price in the smallest units of the currency (integer, not float/double). For
    ///   example, for a price of US$ 1.45 pass amount = 145. See the exp parameter in
    ///   currencies.json, it shows the number of digits past the decimal point for each currency (2
    ///   for the majority of currencies).
    /// </summary>
    property TotalAmount: Integer read GetTotalAmount;
  end;

  /// <summary>This object represents a shipping address.</summary>
  ITgShippingAddress = interface(ITgJsonObject)
    ['{FD8F0029-9F38-59A1-B46E-5810F4EFC0C6}']
    function GetCountryCode: string;
    function GetState: string;
    function GetCity: string;
    function GetStreetLine1: string;
    function GetStreetLine2: string;
    function GetPostCode: string;
    /// <summary>Two-letter ISO 3166-1 alpha-2 country code</summary>
    property CountryCode: string read GetCountryCode;
    /// <summary>State, if applicable</summary>
    property State: string read GetState;
    /// <summary>City</summary>
    property City: string read GetCity;
    /// <summary>First line for the address</summary>
    property StreetLine1: string read GetStreetLine1;
    /// <summary>Second line for the address</summary>
    property StreetLine2: string read GetStreetLine2;
    /// <summary>Address post code</summary>
    property PostCode: string read GetPostCode;
  end;

  /// <summary>This object represents information about an order.</summary>
  ITgOrderInfo = interface(ITgJsonObject)
    ['{D16FD0E2-2155-54AC-844D-0938575644A3}']
    function GetName: string;
    function GetPhoneNumber: string;
    function GetEmail: string;
    function GetShippingAddress: ITgShippingAddress;
    /// <summary>Optional. User name</summary>
    property Name: string read GetName;
    /// <summary>Optional. User's phone number</summary>
    property PhoneNumber: string read GetPhoneNumber;
    /// <summary>Optional. User email</summary>
    property Email: string read GetEmail;
    /// <summary>Optional. User shipping address</summary>
    property ShippingAddress: ITgShippingAddress read GetShippingAddress;
  end;

  /// <summary>This object represents one shipping option.</summary>
  ITgShippingOption = interface(ITgOutObject)
    ['{AAF3E1FD-3335-5F35-B84F-BD6B36B68C59}']
    /// <summary>Задаёт id: Shipping option identifier</summary>
    function WithId(const AValue: string): ITgShippingOption;
    /// <summary>Задаёт title: Option title</summary>
    function WithTitle(const AValue: string): ITgShippingOption;
    /// <summary>Задаёт prices: List of price portions</summary>
    function WithPrices(const AValue: array of ITgLabeledPrice): ITgShippingOption;
  end;

  /// <summary>
  ///   This object contains basic information about a successful payment. Note that if the buyer
  ///   initiates a chargeback with the relevant payment provider following this transaction, the
  ///   funds may be debited from your balance. This is outside of Telegram's control.
  /// </summary>
  ITgSuccessfulPayment = interface(ITgJsonObject)
    ['{2438FDF8-C7E4-5476-A8B0-D1AB188E5526}']
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
    /// <summary>
    ///   Three-letter ISO 4217 currency code, or “XTR” for payments in Telegram Stars
    /// </summary>
    property Currency: string read GetCurrency;
    /// <summary>
    ///   Total price in the smallest units of the currency (integer, not float/double). For
    ///   example, for a price of US$ 1.45 pass amount = 145. See the exp parameter in
    ///   currencies.json, it shows the number of digits past the decimal point for each currency (2
    ///   for the majority of currencies).
    /// </summary>
    property TotalAmount: Integer read GetTotalAmount;
    /// <summary>Bot-specified invoice payload</summary>
    property InvoicePayload: string read GetInvoicePayload;
    /// <summary>
    ///   Optional. Expiration date of the subscription, in Unix time; for recurring payments only
    /// </summary>
    property SubscriptionExpirationDate: Int64 read GetSubscriptionExpirationDate;
    /// <summary>Поле subscription_expiration_date присутствует.</summary>
    property HasSubscriptionExpirationDate: Boolean read GetHasSubscriptionExpirationDate;
    /// <summary>
    ///   Optional. True, if the payment is a recurring payment for a subscription
    /// </summary>
    property IsRecurring: Boolean read GetIsRecurring;
    /// <summary>
    ///   Optional. True, if the payment is the first payment for a subscription
    /// </summary>
    property IsFirstRecurring: Boolean read GetIsFirstRecurring;
    /// <summary>Optional. Identifier of the shipping option chosen by the user</summary>
    property ShippingOptionId: string read GetShippingOptionId;
    /// <summary>Optional. Order information provided by the user</summary>
    property OrderInfo: ITgOrderInfo read GetOrderInfo;
    /// <summary>Telegram payment identifier</summary>
    property TelegramPaymentChargeId: string read GetTelegramPaymentChargeId;
    /// <summary>Provider payment identifier</summary>
    property ProviderPaymentChargeId: string read GetProviderPaymentChargeId;
  end;

  /// <summary>This object contains basic information about a refunded payment.</summary>
  ITgRefundedPayment = interface(ITgJsonObject)
    ['{87799929-82D6-5E8E-A6AA-CAC251772D17}']
    function GetCurrency: string;
    function GetTotalAmount: Integer;
    function GetInvoicePayload: string;
    function GetTelegramPaymentChargeId: string;
    function GetProviderPaymentChargeId: string;
    /// <summary>
    ///   Three-letter ISO 4217 currency code, or “XTR” for payments in Telegram Stars. Currently,
    ///   always “XTR”.
    /// </summary>
    property Currency: string read GetCurrency;
    /// <summary>
    ///   Total refunded price in the smallest units of the currency (integer, not float/double).
    ///   For example, for a price of US$ 1.45, total_amount = 145. See the exp parameter in
    ///   currencies.json, it shows the number of digits past the decimal point for each currency (2
    ///   for the majority of currencies).
    /// </summary>
    property TotalAmount: Integer read GetTotalAmount;
    /// <summary>Bot-specified invoice payload</summary>
    property InvoicePayload: string read GetInvoicePayload;
    /// <summary>Telegram payment identifier</summary>
    property TelegramPaymentChargeId: string read GetTelegramPaymentChargeId;
    /// <summary>Optional. Provider payment identifier</summary>
    property ProviderPaymentChargeId: string read GetProviderPaymentChargeId;
  end;

  /// <summary>This object contains information about an incoming shipping query.</summary>
  ITgShippingQuery = interface(ITgJsonObject)
    ['{F0D3C9F0-B63E-5338-8646-5DF7CF4B8373}']
    function GetId: string;
    function GetFrom: ITgUser;
    function GetInvoicePayload: string;
    function GetShippingAddress: ITgShippingAddress;
    /// <summary>Unique query identifier</summary>
    property Id: string read GetId;
    /// <summary>User who sent the query</summary>
    property From: ITgUser read GetFrom;
    /// <summary>Bot-specified invoice payload</summary>
    property InvoicePayload: string read GetInvoicePayload;
    /// <summary>User specified shipping address</summary>
    property ShippingAddress: ITgShippingAddress read GetShippingAddress;
  end;

  /// <summary>
  ///   This object contains information about an incoming pre-checkout query.
  /// </summary>
  ITgPreCheckoutQuery = interface(ITgJsonObject)
    ['{5D2063B8-5259-5100-884C-FE6DC3E3AF85}']
    function GetId: string;
    function GetFrom: ITgUser;
    function GetCurrency: string;
    function GetTotalAmount: Integer;
    function GetInvoicePayload: string;
    function GetShippingOptionId: string;
    function GetOrderInfo: ITgOrderInfo;
    /// <summary>Unique query identifier</summary>
    property Id: string read GetId;
    /// <summary>User who sent the query</summary>
    property From: ITgUser read GetFrom;
    /// <summary>
    ///   Three-letter ISO 4217 currency code, or “XTR” for payments in Telegram Stars
    /// </summary>
    property Currency: string read GetCurrency;
    /// <summary>
    ///   Total price in the smallest units of the currency (integer, not float/double). For
    ///   example, for a price of US$ 1.45 pass amount = 145. See the exp parameter in
    ///   currencies.json, it shows the number of digits past the decimal point for each currency (2
    ///   for the majority of currencies).
    /// </summary>
    property TotalAmount: Integer read GetTotalAmount;
    /// <summary>Bot-specified invoice payload</summary>
    property InvoicePayload: string read GetInvoicePayload;
    /// <summary>Optional. Identifier of the shipping option chosen by the user</summary>
    property ShippingOptionId: string read GetShippingOptionId;
    /// <summary>Optional. Order information provided by the user</summary>
    property OrderInfo: ITgOrderInfo read GetOrderInfo;
  end;

  /// <summary>This object contains information about a paid media purchase.</summary>
  ITgPaidMediaPurchased = interface(ITgJsonObject)
    ['{68736B13-5D4B-556A-8AEB-F7957CEDE2EB}']
    function GetFrom: ITgUser;
    function GetPaidMediaPayload: string;
    /// <summary>User who purchased the media</summary>
    property From: ITgUser read GetFrom;
    /// <summary>Bot-specified paid media payload</summary>
    property PaidMediaPayload: string read GetPaidMediaPayload;
  end;

  /// <summary>
  ///   This object describes the state of a revenue withdrawal operation. Виды (Kind, As*):
  ///   ITgRevenueWithdrawalStatePending, ITgRevenueWithdrawalStateSucceeded,
  ///   ITgRevenueWithdrawalStateFailed.
  /// </summary>
  ITgRevenueWithdrawalState = interface(ITgJsonObject)
    ['{C9A11B86-8878-596E-80E8-E83EA47BA710}']
    function GetKind: TTgRevenueWithdrawalStateKind;
    function GetKindText: string;
    /// <summary>
    ///   ITgRevenueWithdrawalStatePending или nil, если объект другого вида.
    /// </summary>
    function AsPending: ITgRevenueWithdrawalStatePending;
    /// <summary>
    ///   ITgRevenueWithdrawalStateSucceeded или nil, если объект другого вида.
    /// </summary>
    function AsSucceeded: ITgRevenueWithdrawalStateSucceeded;
    /// <summary>
    ///   ITgRevenueWithdrawalStateFailed или nil, если объект другого вида.
    /// </summary>
    function AsFailed: ITgRevenueWithdrawalStateFailed;
    /// <summary>Вид объекта (Unknown — неизвестный этой версии библиотеки).</summary>
    property Kind: TTgRevenueWithdrawalStateKind read GetKind;
    /// <summary>
    ///   Значение поля type в JSON как есть (в т.ч. при Kind = Unknown); для вариантов-строк и
    ///   массивов — пустая строка.
    /// </summary>
    property KindText: string read GetKindText;
  end;

  /// <summary>The withdrawal is in progress.</summary>
  ITgRevenueWithdrawalStatePending = interface(ITgRevenueWithdrawalState)
    ['{FF78D1A8-0BC6-5F2A-B93D-6B48211BC174}']
  end;

  /// <summary>The withdrawal succeeded.</summary>
  ITgRevenueWithdrawalStateSucceeded = interface(ITgRevenueWithdrawalState)
    ['{A560BD22-890C-5032-B819-35F913F92F0E}']
    function GetDate: Int64;
    function GetUrl: string;
    /// <summary>Date the withdrawal was completed in Unix time</summary>
    property Date: Int64 read GetDate;
    /// <summary>An HTTPS URL that can be used to see transaction details</summary>
    property Url: string read GetUrl;
  end;

  /// <summary>The withdrawal failed and the transaction was refunded.</summary>
  ITgRevenueWithdrawalStateFailed = interface(ITgRevenueWithdrawalState)
    ['{C431375E-7811-5752-AEDB-6574C2D75BC8}']
  end;

  /// <summary>
  ///   Contains information about the affiliate that received a commission via this transaction.
  /// </summary>
  ITgAffiliateInfo = interface(ITgJsonObject)
    ['{84ABF5AA-8E6E-5481-BEC6-2BB520844009}']
    function GetAffiliateUser: ITgUser;
    function GetAffiliateChat: ITgChat;
    function GetCommissionPerMille: Integer;
    function GetAmount: Integer;
    function GetNanostarAmount: Integer;
    function GetHasNanostarAmount: Boolean;
    /// <summary>
    ///   Optional. The bot or the user that received an affiliate commission if it was received by
    ///   a bot or a user
    /// </summary>
    property AffiliateUser: ITgUser read GetAffiliateUser;
    /// <summary>
    ///   Optional. The chat that received an affiliate commission if it was received by a chat
    /// </summary>
    property AffiliateChat: ITgChat read GetAffiliateChat;
    /// <summary>
    ///   The number of Telegram Stars received by the affiliate for each 1000 Telegram Stars
    ///   received by the bot from referred users
    /// </summary>
    property CommissionPerMille: Integer read GetCommissionPerMille;
    /// <summary>
    ///   Integer amount of Telegram Stars received by the affiliate from the transaction, rounded
    ///   to 0; can be negative for refunds
    /// </summary>
    property Amount: Integer read GetAmount;
    /// <summary>
    ///   Optional. The number of 1/1000000000 shares of Telegram Stars received by the affiliate;
    ///   from -999999999 to 999999999; can be negative for refunds
    /// </summary>
    property NanostarAmount: Integer read GetNanostarAmount;
    /// <summary>Поле nanostar_amount присутствует.</summary>
    property HasNanostarAmount: Boolean read GetHasNanostarAmount;
  end;

  /// <summary>
  ///   This object describes the source of a transaction, or its recipient for outgoing
  ///   transactions. Виды (Kind, As*): ITgTransactionPartnerUser, ITgTransactionPartnerChat,
  ///   ITgTransactionPartnerAffiliateProgram, ITgTransactionPartnerFragment,
  ///   ITgTransactionPartnerTelegramAds, ITgTransactionPartnerTelegramApi,
  ///   ITgTransactionPartnerOther.
  /// </summary>
  ITgTransactionPartner = interface(ITgJsonObject)
    ['{7995A955-42FD-52C1-B5DC-2EC25354D0C4}']
    function GetKind: TTgTransactionPartnerKind;
    function GetKindText: string;
    /// <summary>ITgTransactionPartnerUser или nil, если объект другого вида.</summary>
    function AsUser: ITgTransactionPartnerUser;
    /// <summary>ITgTransactionPartnerChat или nil, если объект другого вида.</summary>
    function AsChat: ITgTransactionPartnerChat;
    /// <summary>
    ///   ITgTransactionPartnerAffiliateProgram или nil, если объект другого вида.
    /// </summary>
    function AsAffiliateProgram: ITgTransactionPartnerAffiliateProgram;
    /// <summary>ITgTransactionPartnerFragment или nil, если объект другого вида.</summary>
    function AsFragment: ITgTransactionPartnerFragment;
    /// <summary>
    ///   ITgTransactionPartnerTelegramAds или nil, если объект другого вида.
    /// </summary>
    function AsTelegramAds: ITgTransactionPartnerTelegramAds;
    /// <summary>
    ///   ITgTransactionPartnerTelegramApi или nil, если объект другого вида.
    /// </summary>
    function AsTelegramApi: ITgTransactionPartnerTelegramApi;
    /// <summary>ITgTransactionPartnerOther или nil, если объект другого вида.</summary>
    function AsOther: ITgTransactionPartnerOther;
    /// <summary>Вид объекта (Unknown — неизвестный этой версии библиотеки).</summary>
    property Kind: TTgTransactionPartnerKind read GetKind;
    /// <summary>
    ///   Значение поля type в JSON как есть (в т.ч. при Kind = Unknown); для вариантов-строк и
    ///   массивов — пустая строка.
    /// </summary>
    property KindText: string read GetKindText;
  end;

  /// <summary>Describes a transaction with a user.</summary>
  ITgTransactionPartnerUser = interface(ITgTransactionPartner)
    ['{F1BD3676-CF95-53A6-8388-4A4B8861103F}']
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
    /// <summary>
    ///   Type of the transaction, currently one of “invoice_payment” for payments via invoices,
    ///   “paid_media_payment” for payments for paid media, “gift_purchase” for gifts sent by the
    ///   bot, “premium_purchase” for Telegram Premium subscriptions gifted by the bot,
    ///   “business_account_transfer” for direct transfers from managed business accounts
    /// </summary>
    property TransactionType: string read GetTransactionType;
    /// <summary>Information about the user</summary>
    property User: ITgUser read GetUser;
    /// <summary>
    ///   Optional. Information about the affiliate that received a commission via this transaction.
    ///   Can be available only for “invoice_payment” and “paid_media_payment” transactions.
    /// </summary>
    property Affiliate: ITgAffiliateInfo read GetAffiliate;
    /// <summary>
    ///   Optional. Bot-specified invoice payload. Can be available only for “invoice_payment”
    ///   transactions.
    /// </summary>
    property InvoicePayload: string read GetInvoicePayload;
    /// <summary>
    ///   Optional. The duration of the paid subscription. Can be available only for
    ///   “invoice_payment” transactions.
    /// </summary>
    property SubscriptionPeriod: Integer read GetSubscriptionPeriod;
    /// <summary>Поле subscription_period присутствует.</summary>
    property HasSubscriptionPeriod: Boolean read GetHasSubscriptionPeriod;
    /// <summary>
    ///   Optional. Information about the paid media bought by the user; for “paid_media_payment”
    ///   transactions only
    /// </summary>
    property PaidMedia: TArray<ITgPaidMedia> read GetPaidMedia;
    /// <summary>
    ///   Optional. Bot-specified paid media payload. Can be available only for “paid_media_payment”
    ///   transactions.
    /// </summary>
    property PaidMediaPayload: string read GetPaidMediaPayload;
    /// <summary>
    ///   Optional. The gift sent to the user by the bot; for “gift_purchase” transactions only
    /// </summary>
    property Gift: ITgGift read GetGift;
    /// <summary>
    ///   Optional. Number of months the gifted Telegram Premium subscription will be active for;
    ///   for “premium_purchase” transactions only
    /// </summary>
    property PremiumSubscriptionDuration: Integer read GetPremiumSubscriptionDuration;
    /// <summary>Поле premium_subscription_duration присутствует.</summary>
    property HasPremiumSubscriptionDuration: Boolean read GetHasPremiumSubscriptionDuration;
  end;

  /// <summary>Describes a transaction with a chat.</summary>
  ITgTransactionPartnerChat = interface(ITgTransactionPartner)
    ['{626FB8F9-39D4-59B1-8743-96A9A6AF5BE2}']
    function GetChat: ITgChat;
    function GetGift: ITgGift;
    /// <summary>Information about the chat</summary>
    property Chat: ITgChat read GetChat;
    /// <summary>Optional. The gift sent to the chat by the bot</summary>
    property Gift: ITgGift read GetGift;
  end;

  /// <summary>
  ///   Describes the affiliate program that issued the affiliate commission received via this
  ///   transaction.
  /// </summary>
  ITgTransactionPartnerAffiliateProgram = interface(ITgTransactionPartner)
    ['{A5661E3A-AC8B-5818-8E3A-FCCFA255DB0B}']
    function GetSponsorUser: ITgUser;
    function GetCommissionPerMille: Integer;
    /// <summary>
    ///   Optional. Information about the bot that sponsored the affiliate program
    /// </summary>
    property SponsorUser: ITgUser read GetSponsorUser;
    /// <summary>
    ///   The number of Telegram Stars received by the bot for each 1000 Telegram Stars received by
    ///   the affiliate program sponsor from referred users
    /// </summary>
    property CommissionPerMille: Integer read GetCommissionPerMille;
  end;

  /// <summary>Describes a withdrawal transaction with Fragment.</summary>
  ITgTransactionPartnerFragment = interface(ITgTransactionPartner)
    ['{21D169FA-3989-59C9-98E0-552AD4B42D79}']
    function GetWithdrawalState: ITgRevenueWithdrawalState;
    /// <summary>Optional. State of the transaction if the transaction is outgoing</summary>
    property WithdrawalState: ITgRevenueWithdrawalState read GetWithdrawalState;
  end;

  /// <summary>Describes a withdrawal transaction to the Telegram Ads platform.</summary>
  ITgTransactionPartnerTelegramAds = interface(ITgTransactionPartner)
    ['{305591CD-463E-5504-A1A0-F7726CF5C6FD}']
  end;

  /// <summary>Describes a transaction with payment for paid broadcasting.</summary>
  ITgTransactionPartnerTelegramApi = interface(ITgTransactionPartner)
    ['{1D03166F-2C82-5D1C-9B01-E4C6600876EF}']
    function GetRequestCount: Integer;
    /// <summary>
    ///   The number of successful requests that exceeded regular limits and were therefore billed
    /// </summary>
    property RequestCount: Integer read GetRequestCount;
  end;

  /// <summary>Describes a transaction with an unknown source or recipient.</summary>
  ITgTransactionPartnerOther = interface(ITgTransactionPartner)
    ['{0B666CF5-5907-5582-B53C-6FEF59B02DAE}']
  end;

  /// <summary>
  ///   Describes a Telegram Star transaction. Note that if the buyer initiates a chargeback with
  ///   the payment provider from whom they acquired Stars (e.g., Apple, Google) following this
  ///   transaction, the refunded Stars will be deducted from the bot's balance. This is outside of
  ///   Telegram's control.
  /// </summary>
  ITgStarTransaction = interface(ITgJsonObject)
    ['{FB3C11FF-0DC8-57C2-BC95-4F8DFD5E27AD}']
    function GetId: string;
    function GetAmount: Integer;
    function GetNanostarAmount: Integer;
    function GetHasNanostarAmount: Boolean;
    function GetDate: Int64;
    function GetSource: ITgTransactionPartner;
    function GetReceiver: ITgTransactionPartner;
    /// <summary>
    ///   Unique identifier of the transaction. Coincides with the identifier of the original
    ///   transaction for refund transactions. Coincides with
    ///   SuccessfulPayment.telegram_payment_charge_id for successful incoming payments from users.
    /// </summary>
    property Id: string read GetId;
    /// <summary>Integer amount of Telegram Stars transferred by the transaction</summary>
    property Amount: Integer read GetAmount;
    /// <summary>
    ///   Optional. The number of 1/1000000000 shares of Telegram Stars transferred by the
    ///   transaction; from 0 to 999999999
    /// </summary>
    property NanostarAmount: Integer read GetNanostarAmount;
    /// <summary>Поле nanostar_amount присутствует.</summary>
    property HasNanostarAmount: Boolean read GetHasNanostarAmount;
    /// <summary>Date the transaction was created in Unix time</summary>
    property Date: Int64 read GetDate;
    /// <summary>
    ///   Optional. Source of an incoming transaction (e.g., a user purchasing goods or services,
    ///   Fragment refunding a failed withdrawal). Only for incoming transactions.
    /// </summary>
    property Source: ITgTransactionPartner read GetSource;
    /// <summary>
    ///   Optional. Receiver of an outgoing transaction (e.g., a user for a purchase refund,
    ///   Fragment for a withdrawal). Only for outgoing transactions.
    /// </summary>
    property Receiver: ITgTransactionPartner read GetReceiver;
  end;

  /// <summary>Contains a list of Telegram Star transactions.</summary>
  ITgStarTransactions = interface(ITgJsonObject)
    ['{CDAC026B-9378-585D-9900-1B877A1A0043}']
    function GetTransactions: TArray<ITgStarTransaction>;
    /// <summary>The list of transactions</summary>
    property Transactions: TArray<ITgStarTransaction> read GetTransactions;
  end;

  /// <summary>Describes Telegram Passport data shared with the bot by the user.</summary>
  ITgPassportData = interface(ITgJsonObject)
    ['{01B8A0AE-D855-5B74-A689-5F86B506A416}']
    function GetData: TArray<ITgEncryptedPassportElement>;
    function GetCredentials: ITgEncryptedCredentials;
    /// <summary>
    ///   Array with information about documents and other Telegram Passport elements that was
    ///   shared with the bot
    /// </summary>
    property Data: TArray<ITgEncryptedPassportElement> read GetData;
    /// <summary>Encrypted credentials required to decrypt the data</summary>
    property Credentials: ITgEncryptedCredentials read GetCredentials;
  end;

  /// <summary>
  ///   This object represents a file uploaded to Telegram Passport. Currently all Telegram Passport
  ///   files are in JPEG format when decrypted and don't exceed 10MB.
  /// </summary>
  ITgPassportFile = interface(ITgJsonObject)
    ['{FE3567DB-8C60-59A1-917F-A560D680108D}']
    function GetFileId: string;
    function GetFileUniqueId: string;
    function GetFileSize: Int64;
    function GetFileDate: Int64;
    /// <summary>
    ///   Identifier for this file, which can be used to download or reuse the file
    /// </summary>
    property FileId: string read GetFileId;
    /// <summary>
    ///   Unique identifier for this file, which is supposed to be the same over time and for
    ///   different bots. Can't be used to download or reuse the file.
    /// </summary>
    property FileUniqueId: string read GetFileUniqueId;
    /// <summary>File size in bytes</summary>
    property FileSize: Int64 read GetFileSize;
    /// <summary>Unix time when the file was uploaded</summary>
    property FileDate: Int64 read GetFileDate;
  end;

  /// <summary>
  ///   Describes documents or other Telegram Passport elements shared with the bot by the user.
  /// </summary>
  ITgEncryptedPassportElement = interface(ITgJsonObject)
    ['{9253EA0F-446C-5F6E-AE3E-EDE601EA1D55}']
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
    /// <summary>
    ///   Element type. One of “personal_details”, “passport”, “driver_license”, “identity_card”,
    ///   “internal_passport”, “address”, “utility_bill”, “bank_statement”, “rental_agreement”,
    ///   “passport_registration”, “temporary_registration”, “phone_number”, “email”.
    /// </summary>
    property EncryptedPassportElementType: string read GetEncryptedPassportElementType;
    /// <summary>
    ///   Optional. Base64-encoded encrypted Telegram Passport element data provided by the user;
    ///   available only for “personal_details”, “passport”, “driver_license”, “identity_card”,
    ///   “internal_passport” and “address” types. Can be decrypted and verified using the
    ///   accompanying EncryptedCredentials.
    /// </summary>
    property Data: string read GetData;
    /// <summary>
    ///   Optional. User's verified phone number; available only for “phone_number” type
    /// </summary>
    property PhoneNumber: string read GetPhoneNumber;
    /// <summary>
    ///   Optional. User's verified email address; available only for “email” type
    /// </summary>
    property Email: string read GetEmail;
    /// <summary>
    ///   Optional. Array of encrypted files with documents provided by the user; available only for
    ///   “utility_bill”, “bank_statement”, “rental_agreement”, “passport_registration” and
    ///   “temporary_registration” types. Files can be decrypted and verified using the accompanying
    ///   EncryptedCredentials.
    /// </summary>
    property Files: TArray<ITgPassportFile> read GetFiles;
    /// <summary>
    ///   Optional. Encrypted file with the front side of the document, provided by the user;
    ///   available only for “passport”, “driver_license”, “identity_card” and “internal_passport”.
    ///   The file can be decrypted and verified using the accompanying EncryptedCredentials.
    /// </summary>
    property FrontSide: ITgPassportFile read GetFrontSide;
    /// <summary>
    ///   Optional. Encrypted file with the reverse side of the document, provided by the user;
    ///   available only for “driver_license” and “identity_card”. The file can be decrypted and
    ///   verified using the accompanying EncryptedCredentials.
    /// </summary>
    property ReverseSide: ITgPassportFile read GetReverseSide;
    /// <summary>
    ///   Optional. Encrypted file with the selfie of the user holding a document, provided by the
    ///   user; available if requested for “passport”, “driver_license”, “identity_card” and
    ///   “internal_passport”. The file can be decrypted and verified using the accompanying
    ///   EncryptedCredentials.
    /// </summary>
    property Selfie: ITgPassportFile read GetSelfie;
    /// <summary>
    ///   Optional. Array of encrypted files with translated versions of documents provided by the
    ///   user; available if requested for “passport”, “driver_license”, “identity_card”,
    ///   “internal_passport”, “utility_bill”, “bank_statement”, “rental_agreement”,
    ///   “passport_registration” and “temporary_registration” types. Files can be decrypted and
    ///   verified using the accompanying EncryptedCredentials.
    /// </summary>
    property Translation: TArray<ITgPassportFile> read GetTranslation;
    /// <summary>
    ///   Base64-encoded element hash for using in PassportElementErrorUnspecified
    /// </summary>
    property Hash: string read GetHash;
  end;

  /// <summary>
  ///   Describes data required for decrypting and authenticating EncryptedPassportElement. See the
  ///   Telegram Passport Documentation for a complete description of the data decryption and
  ///   authentication processes.
  /// </summary>
  ITgEncryptedCredentials = interface(ITgJsonObject)
    ['{193487B6-CA2C-5D10-A068-102979B98468}']
    function GetData: string;
    function GetHash: string;
    function GetSecret: string;
    /// <summary>
    ///   Base64-encoded encrypted JSON-serialized data with unique user's payload, data hashes and
    ///   secrets required for EncryptedPassportElement decryption and authentication
    /// </summary>
    property Data: string read GetData;
    /// <summary>Base64-encoded data hash for data authentication</summary>
    property Hash: string read GetHash;
    /// <summary>
    ///   Base64-encoded secret, encrypted with the bot's public RSA key, required for data
    ///   decryption
    /// </summary>
    property Secret: string read GetSecret;
  end;

  /// <summary>
  ///   Represents an issue in one of the data fields that was provided by the user. The error is
  ///   considered resolved when the field's value changes.
  /// </summary>
  ITgPassportElementErrorDataField = interface(ITgOutObject)
    ['{4E8A748A-981D-5A01-92A0-D3256966D565}']
    /// <summary>
    ///   Задаёт type: The section of the user's Telegram Passport which has the error, one of
    ///   “personal_details”, “passport”, “driver_license”, “identity_card”, “internal_passport”,
    ///   “address”
    /// </summary>
    function WithPassportElementErrorDataFieldType(const AValue: string): ITgPassportElementErrorDataField;
    /// <summary>Задаёт field_name: Name of the data field which has the error</summary>
    function WithFieldName(const AValue: string): ITgPassportElementErrorDataField;
    /// <summary>Задаёт data_hash: Base64-encoded data hash</summary>
    function WithDataHash(const AValue: string): ITgPassportElementErrorDataField;
    /// <summary>Задаёт message: Error message</summary>
    function WithMessage(const AValue: string): ITgPassportElementErrorDataField;
  end;

  /// <summary>
  ///   Represents an issue with the front side of a document. The error is considered resolved when
  ///   the file with the front side of the document changes.
  /// </summary>
  ITgPassportElementErrorFrontSide = interface(ITgOutObject)
    ['{3BB6D0A3-B9E8-58BC-98E3-468A7BADABC4}']
    /// <summary>
    ///   Задаёт type: The section of the user's Telegram Passport which has the issue, one of
    ///   “passport”, “driver_license”, “identity_card”, “internal_passport”
    /// </summary>
    function WithPassportElementErrorFrontSideType(const AValue: string): ITgPassportElementErrorFrontSide;
    /// <summary>
    ///   Задаёт file_hash: Base64-encoded hash of the file with the front side of the document
    /// </summary>
    function WithFileHash(const AValue: string): ITgPassportElementErrorFrontSide;
    /// <summary>Задаёт message: Error message</summary>
    function WithMessage(const AValue: string): ITgPassportElementErrorFrontSide;
  end;

  /// <summary>
  ///   Represents an issue with the reverse side of a document. The error is considered resolved
  ///   when the file with reverse side of the document changes.
  /// </summary>
  ITgPassportElementErrorReverseSide = interface(ITgOutObject)
    ['{D1185E8A-D3C4-57E6-A5C9-7176D5580FA3}']
    /// <summary>
    ///   Задаёт type: The section of the user's Telegram Passport which has the issue, one of
    ///   “driver_license”, “identity_card”
    /// </summary>
    function WithPassportElementErrorReverseSideType(const AValue: string): ITgPassportElementErrorReverseSide;
    /// <summary>
    ///   Задаёт file_hash: Base64-encoded hash of the file with the reverse side of the document
    /// </summary>
    function WithFileHash(const AValue: string): ITgPassportElementErrorReverseSide;
    /// <summary>Задаёт message: Error message</summary>
    function WithMessage(const AValue: string): ITgPassportElementErrorReverseSide;
  end;

  /// <summary>
  ///   Represents an issue with the selfie with a document. The error is considered resolved when
  ///   the file with the selfie changes.
  /// </summary>
  ITgPassportElementErrorSelfie = interface(ITgOutObject)
    ['{200026B8-F476-59B6-9688-FABCEF8F72F3}']
    /// <summary>
    ///   Задаёт type: The section of the user's Telegram Passport which has the issue, one of
    ///   “passport”, “driver_license”, “identity_card”, “internal_passport”
    /// </summary>
    function WithPassportElementErrorSelfieType(const AValue: string): ITgPassportElementErrorSelfie;
    /// <summary>Задаёт file_hash: Base64-encoded hash of the file with the selfie</summary>
    function WithFileHash(const AValue: string): ITgPassportElementErrorSelfie;
    /// <summary>Задаёт message: Error message</summary>
    function WithMessage(const AValue: string): ITgPassportElementErrorSelfie;
  end;

  /// <summary>
  ///   Represents an issue with a document scan. The error is considered resolved when the file
  ///   with the document scan changes.
  /// </summary>
  ITgPassportElementErrorFile = interface(ITgOutObject)
    ['{05598088-3EC1-5B47-8DC5-CBA6978E5FF3}']
    /// <summary>
    ///   Задаёт type: The section of the user's Telegram Passport which has the issue, one of
    ///   “utility_bill”, “bank_statement”, “rental_agreement”, “passport_registration”,
    ///   “temporary_registration”
    /// </summary>
    function WithPassportElementErrorFileType(const AValue: string): ITgPassportElementErrorFile;
    /// <summary>Задаёт file_hash: Base64-encoded file hash</summary>
    function WithFileHash(const AValue: string): ITgPassportElementErrorFile;
    /// <summary>Задаёт message: Error message</summary>
    function WithMessage(const AValue: string): ITgPassportElementErrorFile;
  end;

  /// <summary>
  ///   Represents an issue with a list of scans. The error is considered resolved when the list of
  ///   files containing the scans changes.
  /// </summary>
  ITgPassportElementErrorFiles = interface(ITgOutObject)
    ['{93320F1A-EFCB-52EF-96A3-29B8F3F45C19}']
    /// <summary>
    ///   Задаёт type: The section of the user's Telegram Passport which has the issue, one of
    ///   “utility_bill”, “bank_statement”, “rental_agreement”, “passport_registration”,
    ///   “temporary_registration”
    /// </summary>
    function WithPassportElementErrorFilesType(const AValue: string): ITgPassportElementErrorFiles;
    /// <summary>Задаёт file_hashes: List of base64-encoded file hashes</summary>
    function WithFileHashes(const AValue: TArray<string>): ITgPassportElementErrorFiles;
    /// <summary>Задаёт message: Error message</summary>
    function WithMessage(const AValue: string): ITgPassportElementErrorFiles;
  end;

  /// <summary>
  ///   Represents an issue with one of the files that constitute the translation of a document. The
  ///   error is considered resolved when the file changes.
  /// </summary>
  ITgPassportElementErrorTranslationFile = interface(ITgOutObject)
    ['{A4CB55AD-B688-529D-A74C-E9E15D225495}']
    /// <summary>
    ///   Задаёт type: Type of element of the user's Telegram Passport which has the issue, one of
    ///   “passport”, “driver_license”, “identity_card”, “internal_passport”, “utility_bill”,
    ///   “bank_statement”, “rental_agreement”, “passport_registration”, “temporary_registration”
    /// </summary>
    function WithPassportElementErrorTranslationFileType(const AValue: string): ITgPassportElementErrorTranslationFile;
    /// <summary>Задаёт file_hash: Base64-encoded file hash</summary>
    function WithFileHash(const AValue: string): ITgPassportElementErrorTranslationFile;
    /// <summary>Задаёт message: Error message</summary>
    function WithMessage(const AValue: string): ITgPassportElementErrorTranslationFile;
  end;

  /// <summary>
  ///   Represents an issue with the translated version of a document. The error is considered
  ///   resolved when a file with the document translation change.
  /// </summary>
  ITgPassportElementErrorTranslationFiles = interface(ITgOutObject)
    ['{1008DADC-638B-534E-8721-5B698FE8D6C4}']
    /// <summary>
    ///   Задаёт type: Type of element of the user's Telegram Passport which has the issue, one of
    ///   “passport”, “driver_license”, “identity_card”, “internal_passport”, “utility_bill”,
    ///   “bank_statement”, “rental_agreement”, “passport_registration”, “temporary_registration”
    /// </summary>
    function WithPassportElementErrorTranslationFilesType(const AValue: string): ITgPassportElementErrorTranslationFiles;
    /// <summary>Задаёт file_hashes: List of base64-encoded file hashes</summary>
    function WithFileHashes(const AValue: TArray<string>): ITgPassportElementErrorTranslationFiles;
    /// <summary>Задаёт message: Error message</summary>
    function WithMessage(const AValue: string): ITgPassportElementErrorTranslationFiles;
  end;

  /// <summary>
  ///   Represents an issue in an unspecified place. The error is considered resolved when new data
  ///   is added.
  /// </summary>
  ITgPassportElementErrorUnspecified = interface(ITgOutObject)
    ['{C3B53B70-0EDC-5E35-8FEE-990AE45FEA5D}']
    /// <summary>
    ///   Задаёт type: Type of element of the user's Telegram Passport which has the issue
    /// </summary>
    function WithPassportElementErrorUnspecifiedType(const AValue: string): ITgPassportElementErrorUnspecified;
    /// <summary>Задаёт element_hash: Base64-encoded element hash</summary>
    function WithElementHash(const AValue: string): ITgPassportElementErrorUnspecified;
    /// <summary>Задаёт message: Error message</summary>
    function WithMessage(const AValue: string): ITgPassportElementErrorUnspecified;
  end;

  /// <summary>
  ///   This object represents a game. Use BotFather to create and edit games, their short names
  ///   will act as unique identifiers.
  /// </summary>
  ITgGame = interface(ITgJsonObject)
    ['{16E63CB2-62B6-545C-A8B7-4219DD7F0F67}']
    function GetTitle: string;
    function GetDescription: string;
    function GetPhoto: TArray<ITgPhotoSize>;
    function GetText: string;
    function GetTextEntities: TArray<ITgMessageEntity>;
    function GetAnimation: ITgAnimation;
    /// <summary>Title of the game</summary>
    property Title: string read GetTitle;
    /// <summary>Description of the game</summary>
    property Description: string read GetDescription;
    /// <summary>Photo that will be displayed in the game message in chats</summary>
    property Photo: TArray<ITgPhotoSize> read GetPhoto;
    /// <summary>
    ///   Optional. Brief description of the game or high scores included in the game message. Can
    ///   be automatically edited to include current high scores for the game when the bot calls
    ///   setGameScore, or manually edited using editMessageText. 0-4096 characters.
    /// </summary>
    property Text: string read GetText;
    /// <summary>
    ///   Optional. Special entities that appear in text, such as usernames, URLs, bot commands,
    ///   etc.
    /// </summary>
    property TextEntities: TArray<ITgMessageEntity> read GetTextEntities;
    /// <summary>
    ///   Optional. Animation that will be displayed in the game message in chats. Upload via
    ///   BotFather.
    /// </summary>
    property Animation: ITgAnimation read GetAnimation;
  end;

  /// <summary>
  ///   A placeholder, currently holds no information. Use BotFather to set up your game.
  /// </summary>
  ITgCallbackGame = interface(ITgJsonObject)
    ['{0EB407BB-C1DC-585A-B139-84B8634622F5}']
  end;

  /// <summary>
  ///   This object represents one row of the high scores table for a game. And that's about all
  ///   we've got for now. If you've got any questions, please check out our Bot FAQ »
  /// </summary>
  ITgGameHighScore = interface(ITgJsonObject)
    ['{4ABEF406-F454-5B0D-A480-98BAC6B4BC09}']
    function GetPosition: Integer;
    function GetUser: ITgUser;
    function GetScore: Integer;
    /// <summary>Position in high score table for the game</summary>
    property Position: Integer read GetPosition;
    /// <summary>User</summary>
    property User: ITgUser read GetUser;
    /// <summary>Score</summary>
    property Score: Integer read GetScore;
  end;

