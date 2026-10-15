// Gen.Aliases.inc — псевдонимы типов TgBot.Types (interface модуля TgBot, type-блок).
// Сгенерировано TgBotGen по Telegram Bot API 10.3 (August 24, 2026). Не редактируйте вручную.

  { Интерфейсы объектов Bot API }

  /// <summary>This object represents an incoming update.</summary>
  ITgUpdate = TgBot.Types.ITgUpdate;
  /// <summary>Describes the current status of a webhook.</summary>
  ITgWebhookInfo = TgBot.Types.ITgWebhookInfo;
  /// <summary>This object represents a Telegram user or bot.</summary>
  ITgUser = TgBot.Types.ITgUser;
  /// <summary>This object represents a chat.</summary>
  ITgChat = TgBot.Types.ITgChat;
  /// <summary>This object contains full information about a chat.</summary>
  ITgChatFullInfo = TgBot.Types.ITgChatFullInfo;
  /// <summary>
  ///   This object describes a message that can be inaccessible to the bot.
  /// </summary>
  ITgMaybeInaccessibleMessage = TgBot.Types.ITgMaybeInaccessibleMessage;
  /// <summary>This object represents a message.</summary>
  ITgMessage = TgBot.Types.ITgMessage;
  /// <summary>This object represents a unique message identifier.</summary>
  ITgMessageId = TgBot.Types.ITgMessageId;
  /// <summary>
  ///   This object describes a message that was deleted or is otherwise inaccessible to the bot.
  /// </summary>
  ITgInaccessibleMessage = TgBot.Types.ITgInaccessibleMessage;
  /// <summary>This object represents one special entity in a text message.</summary>
  ITgMessageEntity = TgBot.Types.ITgMessageEntity;
  /// <summary>
  ///   This object contains information about the quoted part of a message that is replied to by
  ///   the given message.
  /// </summary>
  ITgTextQuote = TgBot.Types.ITgTextQuote;
  /// <summary>
  ///   This object contains information about a message that is being replied to, which may come
  ///   from another chat or forum topic.
  /// </summary>
  ITgExternalReplyInfo = TgBot.Types.ITgExternalReplyInfo;
  /// <summary>Describes reply parameters for the message that is being sent.</summary>
  ITgReplyParameters = TgBot.Types.ITgReplyParameters;
  ITgEphemeralMessageParameters = TgBot.Types.ITgEphemeralMessageParameters;
  /// <summary>This object describes the origin of a message.</summary>
  ITgMessageOrigin = TgBot.Types.ITgMessageOrigin;
  /// <summary>The message was originally sent by a known user.</summary>
  ITgMessageOriginUser = TgBot.Types.ITgMessageOriginUser;
  /// <summary>The message was originally sent by an unknown user.</summary>
  ITgMessageOriginHiddenUser = TgBot.Types.ITgMessageOriginHiddenUser;
  /// <summary>
  ///   The message was originally sent on behalf of a chat to a group chat.
  /// </summary>
  ITgMessageOriginChat = TgBot.Types.ITgMessageOriginChat;
  /// <summary>The message was originally sent to a channel chat.</summary>
  ITgMessageOriginChannel = TgBot.Types.ITgMessageOriginChannel;
  /// <summary>
  ///   This object represents one size of a photo or a file / sticker thumbnail.
  /// </summary>
  ITgPhotoSize = TgBot.Types.ITgPhotoSize;
  /// <summary>
  ///   This object represents an animation file (GIF or H.264/MPEG-4 AVC video without sound).
  /// </summary>
  ITgAnimation = TgBot.Types.ITgAnimation;
  /// <summary>
  ///   This object represents an audio file to be treated as music by the Telegram clients.
  /// </summary>
  ITgAudio = TgBot.Types.ITgAudio;
  /// <summary>
  ///   This object represents a general file (as opposed to photos, voice messages and audio
  ///   files).
  /// </summary>
  ITgDocument = TgBot.Types.ITgDocument;
  /// <summary>This object represents a live photo.</summary>
  ITgLivePhoto = TgBot.Types.ITgLivePhoto;
  /// <summary>This object represents a story.</summary>
  ITgStory = TgBot.Types.ITgStory;
  /// <summary>This object represents a video file of a specific quality.</summary>
  ITgVideoQuality = TgBot.Types.ITgVideoQuality;
  /// <summary>This object represents a video file.</summary>
  ITgVideo = TgBot.Types.ITgVideo;
  /// <summary>This object represents a video message.</summary>
  ITgVideoNote = TgBot.Types.ITgVideoNote;
  /// <summary>This object represents a voice note.</summary>
  ITgVoice = TgBot.Types.ITgVoice;
  /// <summary>Describes the paid media added to a message.</summary>
  ITgPaidMediaInfo = TgBot.Types.ITgPaidMediaInfo;
  /// <summary>This object describes paid media.</summary>
  ITgPaidMedia = TgBot.Types.ITgPaidMedia;
  /// <summary>The paid media is a live photo.</summary>
  ITgPaidMediaLivePhoto = TgBot.Types.ITgPaidMediaLivePhoto;
  /// <summary>The paid media is a photo.</summary>
  ITgPaidMediaPhoto = TgBot.Types.ITgPaidMediaPhoto;
  /// <summary>The paid media isn't available before the payment.</summary>
  ITgPaidMediaPreview = TgBot.Types.ITgPaidMediaPreview;
  /// <summary>The paid media is a video.</summary>
  ITgPaidMediaVideo = TgBot.Types.ITgPaidMediaVideo;
  /// <summary>This object represents a phone contact.</summary>
  ITgContact = TgBot.Types.ITgContact;
  /// <summary>
  ///   This object represents an animated emoji that displays a random value.
  /// </summary>
  ITgDice = TgBot.Types.ITgDice;
  /// <summary>Represents an HTTP link.</summary>
  ITgLink = TgBot.Types.ITgLink;
  /// <summary>
  ///   At most one of the optional fields can be present in any given object.
  /// </summary>
  ITgPollMedia = TgBot.Types.ITgPollMedia;
  /// <summary>This object contains information about one answer option in a poll.</summary>
  ITgPollOption = TgBot.Types.ITgPollOption;
  /// <summary>
  ///   This object contains information about one answer option in a poll to be sent.
  /// </summary>
  ITgInputPollOption = TgBot.Types.ITgInputPollOption;
  /// <summary>This object represents an answer of a user in a non-anonymous poll.</summary>
  ITgPollAnswer = TgBot.Types.ITgPollAnswer;
  /// <summary>This object contains information about a poll.</summary>
  ITgPoll = TgBot.Types.ITgPoll;
  /// <summary>Describes a task in a checklist.</summary>
  ITgChecklistTask = TgBot.Types.ITgChecklistTask;
  /// <summary>Describes a checklist.</summary>
  ITgChecklist = TgBot.Types.ITgChecklist;
  /// <summary>Describes a task to add to a checklist.</summary>
  ITgInputChecklistTask = TgBot.Types.ITgInputChecklistTask;
  /// <summary>Describes a checklist to create.</summary>
  ITgInputChecklist = TgBot.Types.ITgInputChecklist;
  /// <summary>This object represents a point on the map.</summary>
  ITgLocation = TgBot.Types.ITgLocation;
  /// <summary>This object represents a venue.</summary>
  ITgVenue = TgBot.Types.ITgVenue;
  /// <summary>Describes data sent from a Web App to the bot.</summary>
  ITgWebAppData = TgBot.Types.ITgWebAppData;
  /// <summary>
  ///   This object represents the content of a service message, sent whenever a user in the chat
  ///   triggers a proximity alert set by another user.
  /// </summary>
  ITgProximityAlertTriggered = TgBot.Types.ITgProximityAlertTriggered;
  /// <summary>
  ///   This object represents a service message about a change in auto-delete timer settings.
  /// </summary>
  ITgMessageAutoDeleteTimerChanged = TgBot.Types.ITgMessageAutoDeleteTimerChanged;
  /// <summary>
  ///   This object contains information about the bot that was created to be managed by the current
  ///   bot.
  /// </summary>
  ITgManagedBotCreated = TgBot.Types.ITgManagedBotCreated;
  /// <summary>
  ///   This object contains information about the creation, token update, or owner update of a bot
  ///   that is managed by the current bot.
  /// </summary>
  ITgManagedBotUpdated = TgBot.Types.ITgManagedBotUpdated;
  /// <summary>
  ///   This object contains information about changes to a user payment subscription toward the
  ///   current bot.
  /// </summary>
  ITgBotSubscriptionUpdated = TgBot.Types.ITgBotSubscriptionUpdated;
  /// <summary>
  ///   This object describes an update about a user stopping message generation.
  /// </summary>
  ITgMessageGenerationStopped = TgBot.Types.ITgMessageGenerationStopped;
  /// <summary>Describes a service message about an option added to a poll.</summary>
  ITgPollOptionAdded = TgBot.Types.ITgPollOptionAdded;
  /// <summary>Describes a service message about an option deleted from a poll.</summary>
  ITgPollOptionDeleted = TgBot.Types.ITgPollOptionDeleted;
  /// <summary>
  ///   This object represents a service message about a user boosting a chat.
  /// </summary>
  ITgChatBoostAdded = TgBot.Types.ITgChatBoostAdded;
  /// <summary>
  ///   This object describes the way a background is filled based on the selected colors.
  /// </summary>
  ITgBackgroundFill = TgBot.Types.ITgBackgroundFill;
  /// <summary>The background is filled using the selected color.</summary>
  ITgBackgroundFillSolid = TgBot.Types.ITgBackgroundFillSolid;
  /// <summary>The background is a gradient fill.</summary>
  ITgBackgroundFillGradient = TgBot.Types.ITgBackgroundFillGradient;
  /// <summary>
  ///   The background is a freeform gradient that rotates after every message in the chat.
  /// </summary>
  ITgBackgroundFillFreeformGradient = TgBot.Types.ITgBackgroundFillFreeformGradient;
  /// <summary>This object describes the type of a background.</summary>
  ITgBackgroundType = TgBot.Types.ITgBackgroundType;
  /// <summary>
  ///   The background is automatically filled based on the selected colors.
  /// </summary>
  ITgBackgroundTypeFill = TgBot.Types.ITgBackgroundTypeFill;
  /// <summary>The background is a wallpaper in the JPEG format.</summary>
  ITgBackgroundTypeWallpaper = TgBot.Types.ITgBackgroundTypeWallpaper;
  /// <summary>
  ///   The background is a .PNG or .TGV (gzipped subset of SVG with MIME type
  ///   “application/x-tgwallpattern”) pattern to be combined with the background fill chosen by the
  ///   user.
  /// </summary>
  ITgBackgroundTypePattern = TgBot.Types.ITgBackgroundTypePattern;
  /// <summary>The background is taken directly from a built-in chat theme.</summary>
  ITgBackgroundTypeChatTheme = TgBot.Types.ITgBackgroundTypeChatTheme;
  /// <summary>This object represents a chat background.</summary>
  ITgChatBackground = TgBot.Types.ITgChatBackground;
  /// <summary>
  ///   Describes a service message about checklist tasks marked as done or not done.
  /// </summary>
  ITgChecklistTasksDone = TgBot.Types.ITgChecklistTasksDone;
  /// <summary>Describes a service message about tasks added to a checklist.</summary>
  ITgChecklistTasksAdded = TgBot.Types.ITgChecklistTasksAdded;
  /// <summary>
  ///   Describes a service message about a chat or a bot being added to a community.
  /// </summary>
  ITgCommunityChatAdded = TgBot.Types.ITgCommunityChatAdded;
  /// <summary>
  ///   Describes a service message about a chat being joined by a user from a community.
  /// </summary>
  ITgCommunityChatJoined = TgBot.Types.ITgCommunityChatJoined;
  /// <summary>
  ///   Describes a service message about a chat or a bot being removed from a community.
  /// </summary>
  ITgCommunityChatRemoved = TgBot.Types.ITgCommunityChatRemoved;
  /// <summary>
  ///   This object represents a service message about a new forum topic created in the chat.
  /// </summary>
  ITgForumTopicCreated = TgBot.Types.ITgForumTopicCreated;
  /// <summary>
  ///   This object represents a service message about a forum topic closed in the chat.
  /// </summary>
  ITgForumTopicClosed = TgBot.Types.ITgForumTopicClosed;
  /// <summary>
  ///   This object represents a service message about an edited forum topic.
  /// </summary>
  ITgForumTopicEdited = TgBot.Types.ITgForumTopicEdited;
  /// <summary>
  ///   This object represents a service message about a forum topic reopened in the chat.
  /// </summary>
  ITgForumTopicReopened = TgBot.Types.ITgForumTopicReopened;
  /// <summary>
  ///   This object represents a service message about General forum topic hidden in the chat.
  /// </summary>
  ITgGeneralForumTopicHidden = TgBot.Types.ITgGeneralForumTopicHidden;
  /// <summary>
  ///   This object represents a service message about General forum topic unhidden in the chat.
  /// </summary>
  ITgGeneralForumTopicUnhidden = TgBot.Types.ITgGeneralForumTopicUnhidden;
  /// <summary>
  ///   This object contains information about a user that was shared with the bot using a
  ///   KeyboardButtonRequestUsers button.
  /// </summary>
  ITgSharedUser = TgBot.Types.ITgSharedUser;
  /// <summary>
  ///   This object contains information about the users whose identifiers were shared with the bot
  ///   using a KeyboardButtonRequestUsers button.
  /// </summary>
  ITgUsersShared = TgBot.Types.ITgUsersShared;
  /// <summary>
  ///   This object contains information about a chat that was shared with the bot using a
  ///   KeyboardButtonRequestChat button.
  /// </summary>
  ITgChatShared = TgBot.Types.ITgChatShared;
  /// <summary>
  ///   This object represents a service message about a user allowing a bot to write messages after
  ///   adding it to the attachment menu, launching a Web App from a link, or accepting an explicit
  ///   request from a Web App sent by the method requestWriteAccess.
  /// </summary>
  ITgWriteAccessAllowed = TgBot.Types.ITgWriteAccessAllowed;
  /// <summary>
  ///   This object represents a service message about a video chat scheduled in the chat.
  /// </summary>
  ITgVideoChatScheduled = TgBot.Types.ITgVideoChatScheduled;
  /// <summary>
  ///   This object represents a service message about a video chat started in the chat.
  /// </summary>
  ITgVideoChatStarted = TgBot.Types.ITgVideoChatStarted;
  /// <summary>
  ///   This object represents a service message about a video chat ended in the chat.
  /// </summary>
  ITgVideoChatEnded = TgBot.Types.ITgVideoChatEnded;
  /// <summary>
  ///   This object represents a service message about new members invited to a video chat.
  /// </summary>
  ITgVideoChatParticipantsInvited = TgBot.Types.ITgVideoChatParticipantsInvited;
  /// <summary>
  ///   Describes a service message about a change in the price of paid messages within a chat.
  /// </summary>
  ITgPaidMessagePriceChanged = TgBot.Types.ITgPaidMessagePriceChanged;
  /// <summary>
  ///   Describes a service message about a change in the price of direct messages sent to a channel
  ///   chat.
  /// </summary>
  ITgDirectMessagePriceChanged = TgBot.Types.ITgDirectMessagePriceChanged;
  /// <summary>Describes a service message about the approval of a suggested post.</summary>
  ITgSuggestedPostApproved = TgBot.Types.ITgSuggestedPostApproved;
  /// <summary>
  ///   Describes a service message about the failed approval of a suggested post.
  /// </summary>
  ITgSuggestedPostApprovalFailed = TgBot.Types.ITgSuggestedPostApprovalFailed;
  /// <summary>
  ///   Describes a service message about the rejection of a suggested post.
  /// </summary>
  ITgSuggestedPostDeclined = TgBot.Types.ITgSuggestedPostDeclined;
  /// <summary>
  ///   Describes a service message about a successful payment for a suggested post.
  /// </summary>
  ITgSuggestedPostPaid = TgBot.Types.ITgSuggestedPostPaid;
  /// <summary>
  ///   Describes a service message about a payment refund for a suggested post.
  /// </summary>
  ITgSuggestedPostRefunded = TgBot.Types.ITgSuggestedPostRefunded;
  /// <summary>
  ///   This object represents a service message about the creation of a scheduled giveaway.
  /// </summary>
  ITgGiveawayCreated = TgBot.Types.ITgGiveawayCreated;
  /// <summary>This object represents a message about a scheduled giveaway.</summary>
  ITgGiveaway = TgBot.Types.ITgGiveaway;
  /// <summary>
  ///   This object represents a message about the completion of a giveaway with public winners.
  /// </summary>
  ITgGiveawayWinners = TgBot.Types.ITgGiveawayWinners;
  /// <summary>
  ///   This object represents a service message about the completion of a giveaway without public
  ///   winners.
  /// </summary>
  ITgGiveawayCompleted = TgBot.Types.ITgGiveawayCompleted;
  /// <summary>Describes the options used for link preview generation.</summary>
  ITgLinkPreviewOptions = TgBot.Types.ITgLinkPreviewOptions;
  /// <summary>Describes the price of a suggested post.</summary>
  ITgSuggestedPostPrice = TgBot.Types.ITgSuggestedPostPrice;
  /// <summary>Contains information about a suggested post.</summary>
  ITgSuggestedPostInfo = TgBot.Types.ITgSuggestedPostInfo;
  /// <summary>Contains parameters of a post that is being suggested by the bot.</summary>
  ITgSuggestedPostParameters = TgBot.Types.ITgSuggestedPostParameters;
  /// <summary>Describes a topic of a direct messages chat.</summary>
  ITgDirectMessagesTopic = TgBot.Types.ITgDirectMessagesTopic;
  /// <summary>This object represent a user's profile pictures.</summary>
  ITgUserProfilePhotos = TgBot.Types.ITgUserProfilePhotos;
  /// <summary>This object represents the audios displayed on a user's profile.</summary>
  ITgUserProfileAudios = TgBot.Types.ITgUserProfileAudios;
  /// <summary>This object represents a file ready to be downloaded.</summary>
  ITgFile = TgBot.Types.ITgFile;
  /// <summary>Describes a Web App.</summary>
  ITgWebAppInfo = TgBot.Types.ITgWebAppInfo;
  /// <summary>
  ///   This object represents a custom keyboard with reply options (see Introduction to bots for
  ///   details and examples).
  /// </summary>
  ITgReplyKeyboardMarkup = TgBot.Types.ITgReplyKeyboardMarkup;
  /// <summary>This object represents one button of the reply keyboard.</summary>
  ITgKeyboardButton = TgBot.Types.ITgKeyboardButton;
  /// <summary>This object defines the criteria used to request suitable users.</summary>
  ITgKeyboardButtonRequestUsers = TgBot.Types.ITgKeyboardButtonRequestUsers;
  /// <summary>This object defines the criteria used to request a suitable chat.</summary>
  ITgKeyboardButtonRequestChat = TgBot.Types.ITgKeyboardButtonRequestChat;
  /// <summary>
  ///   This object defines the parameters for the creation of a managed bot.
  /// </summary>
  ITgKeyboardButtonRequestManagedBot = TgBot.Types.ITgKeyboardButtonRequestManagedBot;
  /// <summary>
  ///   This object represents type of a poll, which is allowed to be created and sent when the
  ///   corresponding button is pressed.
  /// </summary>
  ITgKeyboardButtonPollType = TgBot.Types.ITgKeyboardButtonPollType;
  /// <summary>
  ///   Upon receiving a message with this object, Telegram clients will remove the current custom
  ///   keyboard and display the default letter-keyboard.
  /// </summary>
  ITgReplyKeyboardRemove = TgBot.Types.ITgReplyKeyboardRemove;
  /// <summary>
  ///   This object represents an inline keyboard that appears right next to the message it belongs
  ///   to.
  /// </summary>
  ITgInlineKeyboardMarkup = TgBot.Types.ITgInlineKeyboardMarkup;
  /// <summary>This object represents one button of an inline keyboard.</summary>
  ITgInlineKeyboardButton = TgBot.Types.ITgInlineKeyboardButton;
  /// <summary>
  ///   This object represents a parameter of the inline keyboard button used to automatically
  ///   authorize a user.
  /// </summary>
  ITgLoginUrl = TgBot.Types.ITgLoginUrl;
  /// <summary>
  ///   This object represents an inline button that switches the current user to inline mode in a
  ///   chosen chat, with an optional default inline query.
  /// </summary>
  ITgSwitchInlineQueryChosenChat = TgBot.Types.ITgSwitchInlineQueryChosenChat;
  /// <summary>
  ///   This object represents an inline keyboard button that copies specified text to the
  ///   clipboard.
  /// </summary>
  ITgCopyTextButton = TgBot.Types.ITgCopyTextButton;
  /// <summary>This object represents a disabled button which does nothing.</summary>
  ITgDisabledButton = TgBot.Types.ITgDisabledButton;
  /// <summary>
  ///   This object represents an incoming callback query from a callback button in an inline
  ///   keyboard.
  /// </summary>
  ITgCallbackQuery = TgBot.Types.ITgCallbackQuery;
  /// <summary>
  ///   Upon receiving a message with this object, Telegram clients will display a reply interface
  ///   to the user (act as if the user has selected the bot's message and tapped 'Reply').
  /// </summary>
  ITgForceReply = TgBot.Types.ITgForceReply;
  /// <summary>Represents a community (a group of chats).</summary>
  ITgCommunity = TgBot.Types.ITgCommunity;
  /// <summary>This object represents a chat photo.</summary>
  ITgChatPhoto = TgBot.Types.ITgChatPhoto;
  /// <summary>Represents an invite link for a chat.</summary>
  ITgChatInviteLink = TgBot.Types.ITgChatInviteLink;
  /// <summary>Represents the rights of an administrator in a chat.</summary>
  ITgChatAdministratorRights = TgBot.Types.ITgChatAdministratorRights;
  /// <summary>This object represents changes in the status of a chat member.</summary>
  ITgChatMemberUpdated = TgBot.Types.ITgChatMemberUpdated;
  /// <summary>This object contains information about one member of a chat.</summary>
  ITgChatMember = TgBot.Types.ITgChatMember;
  /// <summary>
  ///   Represents a chat member that owns the chat and has all administrator privileges.
  /// </summary>
  ITgChatMemberOwner = TgBot.Types.ITgChatMemberOwner;
  /// <summary>Represents a chat member that has some additional privileges.</summary>
  ITgChatMemberAdministrator = TgBot.Types.ITgChatMemberAdministrator;
  /// <summary>
  ///   Represents a chat member that has no additional privileges or restrictions.
  /// </summary>
  ITgChatMemberMember = TgBot.Types.ITgChatMemberMember;
  /// <summary>
  ///   Represents a chat member that is under certain restrictions in the chat.
  /// </summary>
  ITgChatMemberRestricted = TgBot.Types.ITgChatMemberRestricted;
  /// <summary>
  ///   Represents a chat member that isn't currently a member of the chat, but may join it
  ///   themselves.
  /// </summary>
  ITgChatMemberLeft = TgBot.Types.ITgChatMemberLeft;
  /// <summary>
  ///   Represents a chat member that was banned in the chat and can't return to the chat or view
  ///   chat messages.
  /// </summary>
  ITgChatMemberBanned = TgBot.Types.ITgChatMemberBanned;
  /// <summary>Represents a join request sent to a chat.</summary>
  ITgChatJoinRequest = TgBot.Types.ITgChatJoinRequest;
  /// <summary>
  ///   Describes actions that a non-administrator user is allowed to take in a chat.
  /// </summary>
  ITgChatPermissions = TgBot.Types.ITgChatPermissions;
  /// <summary>Describes the birthdate of a user.</summary>
  ITgBirthdate = TgBot.Types.ITgBirthdate;
  /// <summary>
  ///   Contains information about the start page settings of a Telegram Business account.
  /// </summary>
  ITgBusinessIntro = TgBot.Types.ITgBusinessIntro;
  /// <summary>
  ///   Contains information about the location of a Telegram Business account.
  /// </summary>
  ITgBusinessLocation = TgBot.Types.ITgBusinessLocation;
  /// <summary>Describes an interval of time during which a business is open.</summary>
  ITgBusinessOpeningHoursInterval = TgBot.Types.ITgBusinessOpeningHoursInterval;
  /// <summary>Describes the opening hours of a business.</summary>
  ITgBusinessOpeningHours = TgBot.Types.ITgBusinessOpeningHours;
  /// <summary>
  ///   This object describes the rating of a user based on their Telegram Star spendings.
  /// </summary>
  ITgUserRating = TgBot.Types.ITgUserRating;
  /// <summary>Describes the position of a clickable area within a story.</summary>
  ITgStoryAreaPosition = TgBot.Types.ITgStoryAreaPosition;
  /// <summary>Describes the physical address of a location.</summary>
  ITgLocationAddress = TgBot.Types.ITgLocationAddress;
  /// <summary>Describes a story area pointing to a location.</summary>
  ITgStoryAreaTypeLocation = TgBot.Types.ITgStoryAreaTypeLocation;
  /// <summary>Describes a story area pointing to a suggested reaction.</summary>
  ITgStoryAreaTypeSuggestedReaction = TgBot.Types.ITgStoryAreaTypeSuggestedReaction;
  /// <summary>Describes a story area pointing to an HTTP or tg:// link.</summary>
  ITgStoryAreaTypeLink = TgBot.Types.ITgStoryAreaTypeLink;
  /// <summary>Describes a story area containing weather information.</summary>
  ITgStoryAreaTypeWeather = TgBot.Types.ITgStoryAreaTypeWeather;
  /// <summary>Describes a story area pointing to a unique gift.</summary>
  ITgStoryAreaTypeUniqueGift = TgBot.Types.ITgStoryAreaTypeUniqueGift;
  /// <summary>Describes a clickable area on a story media.</summary>
  ITgStoryArea = TgBot.Types.ITgStoryArea;
  /// <summary>Represents a location to which a chat is connected.</summary>
  ITgChatLocation = TgBot.Types.ITgChatLocation;
  /// <summary>This object describes the type of a reaction.</summary>
  ITgReactionType = TgBot.Types.ITgReactionType;
  /// <summary>The reaction is based on an emoji.</summary>
  ITgReactionTypeEmoji = TgBot.Types.ITgReactionTypeEmoji;
  /// <summary>The reaction is based on a custom emoji.</summary>
  ITgReactionTypeCustomEmoji = TgBot.Types.ITgReactionTypeCustomEmoji;
  /// <summary>The reaction is paid.</summary>
  ITgReactionTypePaid = TgBot.Types.ITgReactionTypePaid;
  /// <summary>
  ///   Represents a reaction added to a message along with the number of times it was added.
  /// </summary>
  ITgReactionCount = TgBot.Types.ITgReactionCount;
  /// <summary>
  ///   This object represents a change of a reaction on a message performed by a user.
  /// </summary>
  ITgMessageReactionUpdated = TgBot.Types.ITgMessageReactionUpdated;
  /// <summary>
  ///   This object represents reaction changes on a message with anonymous reactions.
  /// </summary>
  ITgMessageReactionCountUpdated = TgBot.Types.ITgMessageReactionCountUpdated;
  /// <summary>This object represents a forum topic.</summary>
  ITgForumTopic = TgBot.Types.ITgForumTopic;
  /// <summary>This object describes the background of a gift.</summary>
  ITgGiftBackground = TgBot.Types.ITgGiftBackground;
  /// <summary>This object represents a gift that can be sent by the bot.</summary>
  ITgGift = TgBot.Types.ITgGift;
  /// <summary>This object represent a list of gifts.</summary>
  ITgGifts = TgBot.Types.ITgGifts;
  /// <summary>This object describes the model of a unique gift.</summary>
  ITgUniqueGiftModel = TgBot.Types.ITgUniqueGiftModel;
  /// <summary>
  ///   This object describes the symbol shown on the pattern of a unique gift.
  /// </summary>
  ITgUniqueGiftSymbol = TgBot.Types.ITgUniqueGiftSymbol;
  /// <summary>This object describes the colors of the backdrop of a unique gift.</summary>
  ITgUniqueGiftBackdropColors = TgBot.Types.ITgUniqueGiftBackdropColors;
  /// <summary>This object describes the backdrop of a unique gift.</summary>
  ITgUniqueGiftBackdrop = TgBot.Types.ITgUniqueGiftBackdrop;
  /// <summary>
  ///   This object contains information about the color scheme for a user's name, message replies
  ///   and link previews based on a unique gift.
  /// </summary>
  ITgUniqueGiftColors = TgBot.Types.ITgUniqueGiftColors;
  /// <summary>
  ///   This object describes a unique gift that was upgraded from a regular gift.
  /// </summary>
  ITgUniqueGift = TgBot.Types.ITgUniqueGift;
  /// <summary>
  ///   Describes a service message about a regular gift that was sent or received.
  /// </summary>
  ITgGiftInfo = TgBot.Types.ITgGiftInfo;
  /// <summary>
  ///   Describes a service message about a unique gift that was sent or received.
  /// </summary>
  ITgUniqueGiftInfo = TgBot.Types.ITgUniqueGiftInfo;
  /// <summary>
  ///   This object describes a gift received and owned by a user or a chat.
  /// </summary>
  ITgOwnedGift = TgBot.Types.ITgOwnedGift;
  /// <summary>Describes a regular gift owned by a user or a chat.</summary>
  ITgOwnedGiftRegular = TgBot.Types.ITgOwnedGiftRegular;
  /// <summary>Describes a unique gift received and owned by a user or a chat.</summary>
  ITgOwnedGiftUnique = TgBot.Types.ITgOwnedGiftUnique;
  /// <summary>Contains the list of gifts received and owned by a user or a chat.</summary>
  ITgOwnedGifts = TgBot.Types.ITgOwnedGifts;
  /// <summary>This object describes the access settings of a bot.</summary>
  ITgBotAccessSettings = TgBot.Types.ITgBotAccessSettings;
  /// <summary>
  ///   This object describes the types of gifts that can be gifted to a user or a chat.
  /// </summary>
  ITgAcceptedGiftTypes = TgBot.Types.ITgAcceptedGiftTypes;
  /// <summary>Describes an amount of Telegram Stars.</summary>
  ITgStarAmount = TgBot.Types.ITgStarAmount;
  /// <summary>This object represents a bot command.</summary>
  ITgBotCommand = TgBot.Types.ITgBotCommand;
  /// <summary>Represents the default scope of bot commands.</summary>
  ITgBotCommandScopeDefault = TgBot.Types.ITgBotCommandScopeDefault;
  /// <summary>Represents the scope of bot commands, covering all private chats.</summary>
  ITgBotCommandScopeAllPrivateChats = TgBot.Types.ITgBotCommandScopeAllPrivateChats;
  /// <summary>
  ///   Represents the scope of bot commands, covering all group and supergroup chats.
  /// </summary>
  ITgBotCommandScopeAllGroupChats = TgBot.Types.ITgBotCommandScopeAllGroupChats;
  /// <summary>
  ///   Represents the scope of bot commands, covering all group and supergroup chat administrators.
  /// </summary>
  ITgBotCommandScopeAllChatAdministrators = TgBot.Types.ITgBotCommandScopeAllChatAdministrators;
  /// <summary>Represents the scope of bot commands, covering a specific chat.</summary>
  ITgBotCommandScopeChat = TgBot.Types.ITgBotCommandScopeChat;
  /// <summary>
  ///   Represents the scope of bot commands, covering all administrators of a specific group or
  ///   supergroup chat.
  /// </summary>
  ITgBotCommandScopeChatAdministrators = TgBot.Types.ITgBotCommandScopeChatAdministrators;
  /// <summary>
  ///   Represents the scope of bot commands, covering a specific member of a group or supergroup
  ///   chat.
  /// </summary>
  ITgBotCommandScopeChatMember = TgBot.Types.ITgBotCommandScopeChatMember;
  /// <summary>This object represents the bot's name.</summary>
  ITgBotName = TgBot.Types.ITgBotName;
  /// <summary>This object represents the bot's description.</summary>
  ITgBotDescription = TgBot.Types.ITgBotDescription;
  /// <summary>This object represents the bot's short description.</summary>
  ITgBotShortDescription = TgBot.Types.ITgBotShortDescription;
  /// <summary>This object describes the bot's menu button in a private chat.</summary>
  ITgMenuButton = TgBot.Types.ITgMenuButton;
  /// <summary>Represents a menu button, which opens the bot's list of commands.</summary>
  ITgMenuButtonCommands = TgBot.Types.ITgMenuButtonCommands;
  /// <summary>Represents a menu button, which launches a Web App.</summary>
  ITgMenuButtonWebApp = TgBot.Types.ITgMenuButtonWebApp;
  /// <summary>Describes that no specific value for the menu button was set.</summary>
  ITgMenuButtonDefault = TgBot.Types.ITgMenuButtonDefault;
  /// <summary>This object describes the source of a chat boost.</summary>
  ITgChatBoostSource = TgBot.Types.ITgChatBoostSource;
  /// <summary>
  ///   The boost was obtained by subscribing to Telegram Premium or by gifting a Telegram Premium
  ///   subscription to another user.
  /// </summary>
  ITgChatBoostSourcePremium = TgBot.Types.ITgChatBoostSourcePremium;
  /// <summary>
  ///   The boost was obtained by the creation of Telegram Premium gift codes to boost a chat.
  /// </summary>
  ITgChatBoostSourceGiftCode = TgBot.Types.ITgChatBoostSourceGiftCode;
  /// <summary>
  ///   The boost was obtained by the creation of a Telegram Premium or a Telegram Star giveaway.
  /// </summary>
  ITgChatBoostSourceGiveaway = TgBot.Types.ITgChatBoostSourceGiveaway;
  /// <summary>This object contains information about a chat boost.</summary>
  ITgChatBoost = TgBot.Types.ITgChatBoost;
  /// <summary>This object represents a boost added to a chat or changed.</summary>
  ITgChatBoostUpdated = TgBot.Types.ITgChatBoostUpdated;
  /// <summary>This object represents a boost removed from a chat.</summary>
  ITgChatBoostRemoved = TgBot.Types.ITgChatBoostRemoved;
  /// <summary>Describes a service message about the chat owner leaving the chat.</summary>
  ITgChatOwnerLeft = TgBot.Types.ITgChatOwnerLeft;
  /// <summary>Describes a service message about an ownership change in the chat.</summary>
  ITgChatOwnerChanged = TgBot.Types.ITgChatOwnerChanged;
  /// <summary>This object represents a list of boosts added to a chat by a user.</summary>
  ITgUserChatBoosts = TgBot.Types.ITgUserChatBoosts;
  /// <summary>Represents the rights of a business bot.</summary>
  ITgBusinessBotRights = TgBot.Types.ITgBusinessBotRights;
  /// <summary>Describes the connection of the bot with a business account.</summary>
  ITgBusinessConnection = TgBot.Types.ITgBusinessConnection;
  /// <summary>
  ///   This object is received when messages are deleted from a connected business account.
  /// </summary>
  ITgBusinessMessagesDeleted = TgBot.Types.ITgBusinessMessagesDeleted;
  /// <summary>Describes an inline message sent by a Web App on behalf of a user.</summary>
  ITgSentWebAppMessage = TgBot.Types.ITgSentWebAppMessage;
  /// <summary>Describes an inline message sent by a guest bot.</summary>
  ITgSentGuestMessage = TgBot.Types.ITgSentGuestMessage;
  /// <summary>Describes an inline message to be sent by a user of a Mini App.</summary>
  ITgPreparedInlineMessage = TgBot.Types.ITgPreparedInlineMessage;
  /// <summary>Describes a keyboard button to be used by a user of a Mini App.</summary>
  ITgPreparedKeyboardButton = TgBot.Types.ITgPreparedKeyboardButton;
  /// <summary>Describes why a request was unsuccessful.</summary>
  ITgResponseParameters = TgBot.Types.ITgResponseParameters;
  /// <summary>
  ///   Represents an animation file (GIF or H.264/MPEG-4 AVC video without sound) to be sent.
  /// </summary>
  ITgInputMediaAnimation = TgBot.Types.ITgInputMediaAnimation;
  /// <summary>Represents an audio file to be treated as music to be sent.</summary>
  ITgInputMediaAudio = TgBot.Types.ITgInputMediaAudio;
  /// <summary>Represents a general file to be sent.</summary>
  ITgInputMediaDocument = TgBot.Types.ITgInputMediaDocument;
  /// <summary>Represents an HTTP link to be sent.</summary>
  ITgInputMediaLink = TgBot.Types.ITgInputMediaLink;
  /// <summary>Represents a live photo to be sent.</summary>
  ITgInputMediaLivePhoto = TgBot.Types.ITgInputMediaLivePhoto;
  /// <summary>Represents a location to be sent.</summary>
  ITgInputMediaLocation = TgBot.Types.ITgInputMediaLocation;
  /// <summary>Represents a photo to be sent.</summary>
  ITgInputMediaPhoto = TgBot.Types.ITgInputMediaPhoto;
  /// <summary>Represents a sticker file to be sent.</summary>
  ITgInputMediaSticker = TgBot.Types.ITgInputMediaSticker;
  /// <summary>Represents a venue to be sent.</summary>
  ITgInputMediaVenue = TgBot.Types.ITgInputMediaVenue;
  /// <summary>Represents a video to be sent.</summary>
  ITgInputMediaVideo = TgBot.Types.ITgInputMediaVideo;
  /// <summary>Represents a voice message file to be sent.</summary>
  ITgInputMediaVoiceNote = TgBot.Types.ITgInputMediaVoiceNote;
  /// <summary>The paid media to send is a live photo.</summary>
  ITgInputPaidMediaLivePhoto = TgBot.Types.ITgInputPaidMediaLivePhoto;
  /// <summary>The paid media to send is a photo.</summary>
  ITgInputPaidMediaPhoto = TgBot.Types.ITgInputPaidMediaPhoto;
  /// <summary>The paid media to send is a video.</summary>
  ITgInputPaidMediaVideo = TgBot.Types.ITgInputPaidMediaVideo;
  /// <summary>A static profile photo in the .JPG format.</summary>
  ITgInputProfilePhotoStatic = TgBot.Types.ITgInputProfilePhotoStatic;
  /// <summary>An animated profile photo in the MPEG4 format.</summary>
  ITgInputProfilePhotoAnimated = TgBot.Types.ITgInputProfilePhotoAnimated;
  /// <summary>Describes a photo to post as a story.</summary>
  ITgInputStoryContentPhoto = TgBot.Types.ITgInputStoryContentPhoto;
  /// <summary>Describes a video to post as a story.</summary>
  ITgInputStoryContentVideo = TgBot.Types.ITgInputStoryContentVideo;
  /// <summary>This object represents a sticker.</summary>
  ITgSticker = TgBot.Types.ITgSticker;
  /// <summary>This object represents a sticker set.</summary>
  ITgStickerSet = TgBot.Types.ITgStickerSet;
  /// <summary>
  ///   This object describes the position on faces where a mask should be placed by default.
  /// </summary>
  ITgMaskPosition = TgBot.Types.ITgMaskPosition;
  /// <summary>This object describes a sticker to be added to a sticker set.</summary>
  ITgInputSticker = TgBot.Types.ITgInputSticker;
  /// <summary>Rich formatted message.</summary>
  ITgRichMessage = TgBot.Types.ITgRichMessage;
  /// <summary>Describes a rich message to be sent.</summary>
  ITgInputRichMessage = TgBot.Types.ITgInputRichMessage;
  /// <summary>Describes a media element embedded in an outgoing rich message.</summary>
  ITgInputRichMessageMedia = TgBot.Types.ITgInputRichMessageMedia;
  /// <summary>This object represents a button in a RichMessage.</summary>
  ITgRichMessageButton = TgBot.Types.ITgRichMessageButton;
  /// <summary>This object represents a rich formatted text.</summary>
  ITgRichText = TgBot.Types.ITgRichText;
  /// <summary>RichText: простой текст (JSON-строка).</summary>
  ITgRichTextPlain = TgBot.Types.ITgRichTextPlain;
  /// <summary>RichText: последовательность фрагментов (JSON-массив).</summary>
  ITgRichTextList = TgBot.Types.ITgRichTextList;
  /// <summary>A bold text.</summary>
  ITgRichTextBold = TgBot.Types.ITgRichTextBold;
  /// <summary>An italicized text.</summary>
  ITgRichTextItalic = TgBot.Types.ITgRichTextItalic;
  /// <summary>An underlined text.</summary>
  ITgRichTextUnderline = TgBot.Types.ITgRichTextUnderline;
  /// <summary>A strikethrough text.</summary>
  ITgRichTextStrikethrough = TgBot.Types.ITgRichTextStrikethrough;
  /// <summary>A text covered by a spoiler.</summary>
  ITgRichTextSpoiler = TgBot.Types.ITgRichTextSpoiler;
  /// <summary>Formatted date and time.</summary>
  ITgRichTextDateTime = TgBot.Types.ITgRichTextDateTime;
  /// <summary>A mention of a Telegram user by their identifier.</summary>
  ITgRichTextTextMention = TgBot.Types.ITgRichTextTextMention;
  /// <summary>A subscript text.</summary>
  ITgRichTextSubscript = TgBot.Types.ITgRichTextSubscript;
  /// <summary>A superscript text.</summary>
  ITgRichTextSuperscript = TgBot.Types.ITgRichTextSuperscript;
  /// <summary>A marked text.</summary>
  ITgRichTextMarked = TgBot.Types.ITgRichTextMarked;
  /// <summary>A monowidth text.</summary>
  ITgRichTextCode = TgBot.Types.ITgRichTextCode;
  /// <summary>A custom emoji.</summary>
  ITgRichTextCustomEmoji = TgBot.Types.ITgRichTextCustomEmoji;
  /// <summary>A mathematical expression.</summary>
  ITgRichTextMathematicalExpression = TgBot.Types.ITgRichTextMathematicalExpression;
  /// <summary>A text with a link.</summary>
  ITgRichTextUrl = TgBot.Types.ITgRichTextUrl;
  /// <summary>A text with an email address.</summary>
  ITgRichTextEmailAddress = TgBot.Types.ITgRichTextEmailAddress;
  /// <summary>A text with a phone number.</summary>
  ITgRichTextPhoneNumber = TgBot.Types.ITgRichTextPhoneNumber;
  /// <summary>A text with a bank card number.</summary>
  ITgRichTextBankCardNumber = TgBot.Types.ITgRichTextBankCardNumber;
  /// <summary>A mention by a username.</summary>
  ITgRichTextMention = TgBot.Types.ITgRichTextMention;
  /// <summary>A hashtag.</summary>
  ITgRichTextHashtag = TgBot.Types.ITgRichTextHashtag;
  /// <summary>A cashtag.</summary>
  ITgRichTextCashtag = TgBot.Types.ITgRichTextCashtag;
  /// <summary>A bot command.</summary>
  ITgRichTextBotCommand = TgBot.Types.ITgRichTextBotCommand;
  /// <summary>A button.</summary>
  ITgRichTextButton = TgBot.Types.ITgRichTextButton;
  /// <summary>An anchor.</summary>
  ITgRichTextAnchor = TgBot.Types.ITgRichTextAnchor;
  /// <summary>A link to an anchor.</summary>
  ITgRichTextAnchorLink = TgBot.Types.ITgRichTextAnchorLink;
  /// <summary>A reference.</summary>
  ITgRichTextReference = TgBot.Types.ITgRichTextReference;
  /// <summary>A link to a reference.</summary>
  ITgRichTextReferenceLink = TgBot.Types.ITgRichTextReferenceLink;
  /// <summary>Caption of a rich formatted block.</summary>
  ITgRichBlockCaption = TgBot.Types.ITgRichBlockCaption;
  /// <summary>Cell in a table.</summary>
  ITgRichBlockTableCell = TgBot.Types.ITgRichBlockTableCell;
  /// <summary>An item of a list.</summary>
  ITgRichBlockListItem = TgBot.Types.ITgRichBlockListItem;
  /// <summary>This object represents a block in a rich formatted message.</summary>
  ITgRichBlock = TgBot.Types.ITgRichBlock;
  /// <summary>A text paragraph, corresponding to the HTML tag &lt;p&gt;.</summary>
  ITgRichBlockParagraph = TgBot.Types.ITgRichBlockParagraph;
  /// <summary>
  ///   A section heading, corresponding to the HTML tags &lt;h1&gt;, &lt;h2&gt;, &lt;h3&gt;,
  ///   &lt;h4&gt;, &lt;h5&gt;, or &lt;h6&gt;.
  /// </summary>
  ITgRichBlockSectionHeading = TgBot.Types.ITgRichBlockSectionHeading;
  /// <summary>
  ///   A preformatted text block, corresponding to the nested HTML tags &lt;pre&gt; and
  ///   &lt;code&gt;.
  /// </summary>
  ITgRichBlockPreformatted = TgBot.Types.ITgRichBlockPreformatted;
  /// <summary>A footer, corresponding to the HTML tag &lt;footer&gt;.</summary>
  ITgRichBlockFooter = TgBot.Types.ITgRichBlockFooter;
  /// <summary>A divider, corresponding to the HTML tag &lt;hr/&gt;.</summary>
  ITgRichBlockDivider = TgBot.Types.ITgRichBlockDivider;
  /// <summary>
  ///   A block with a mathematical expression in LaTeX format, corresponding to the custom HTML tag
  ///   &lt;tg-math-block&gt;.
  /// </summary>
  ITgRichBlockMathematicalExpression = TgBot.Types.ITgRichBlockMathematicalExpression;
  /// <summary>
  ///   A block with an anchor, corresponding to the HTML tag &lt;a&gt; with the attribute name.
  /// </summary>
  ITgRichBlockAnchor = TgBot.Types.ITgRichBlockAnchor;
  /// <summary>
  ///   A list of blocks, corresponding to the HTML tag &lt;ul&gt; or &lt;ol&gt; with multiple
  ///   nested tags &lt;li&gt;.
  /// </summary>
  ITgRichBlockList = TgBot.Types.ITgRichBlockList;
  /// <summary>
  ///   A block quotation, corresponding to the HTML tag &lt;blockquote&gt;.
  /// </summary>
  ITgRichBlockBlockQuotation = TgBot.Types.ITgRichBlockBlockQuotation;
  /// <summary>
  ///   A block quotation, corresponding to the HTML tag &lt;blockquote&gt; with custom attribute
  ///   "expandable".
  /// </summary>
  ITgRichBlockExpandableBlockQuotation = TgBot.Types.ITgRichBlockExpandableBlockQuotation;
  /// <summary>
  ///   A quotation with centered text, loosely corresponding to the HTML tag &lt;aside&gt;.
  /// </summary>
  ITgRichBlockPullQuotation = TgBot.Types.ITgRichBlockPullQuotation;
  /// <summary>A collage, corresponding to the custom HTML tag &lt;tg-collage&gt;.</summary>
  ITgRichBlockCollage = TgBot.Types.ITgRichBlockCollage;
  /// <summary>
  ///   A slideshow, corresponding to the custom HTML tag &lt;tg-slideshow&gt;.
  /// </summary>
  ITgRichBlockSlideshow = TgBot.Types.ITgRichBlockSlideshow;
  /// <summary>A table, corresponding to the HTML tag &lt;table&gt;.</summary>
  ITgRichBlockTable = TgBot.Types.ITgRichBlockTable;
  /// <summary>
  ///   An expandable block for details disclosure, corresponding to the HTML tag &lt;details&gt;.
  /// </summary>
  ITgRichBlockDetails = TgBot.Types.ITgRichBlockDetails;
  /// <summary>
  ///   A block with a map, corresponding to the custom HTML tag &lt;tg-map&gt;.
  /// </summary>
  ITgRichBlockMap = TgBot.Types.ITgRichBlockMap;
  /// <summary>
  ///   A block containing a list of buttons that are shown in one row, corresponding to the custom
  ///   HTML tag &lt;tg-button-row&gt;.
  /// </summary>
  ITgRichBlockButtons = TgBot.Types.ITgRichBlockButtons;
  /// <summary>
  ///   A block with an animation, corresponding to the HTML tag &lt;video&gt;.
  /// </summary>
  ITgRichBlockAnimation = TgBot.Types.ITgRichBlockAnimation;
  /// <summary>
  ///   A block with a music file, corresponding to the HTML tag &lt;audio&gt;.
  /// </summary>
  ITgRichBlockAudio = TgBot.Types.ITgRichBlockAudio;
  /// <summary>
  ///   A block with a general file, corresponding to the custom HTML tag &lt;tg-document&gt;.
  /// </summary>
  ITgRichBlockDocument = TgBot.Types.ITgRichBlockDocument;
  /// <summary>A block with a photo, corresponding to the HTML tag &lt;img&gt;.</summary>
  ITgRichBlockPhoto = TgBot.Types.ITgRichBlockPhoto;
  /// <summary>A block with a video, corresponding to the HTML tag &lt;video&gt;.</summary>
  ITgRichBlockVideo = TgBot.Types.ITgRichBlockVideo;
  /// <summary>
  ///   A block with a voice note, corresponding to the HTML tag &lt;audio&gt;.
  /// </summary>
  ITgRichBlockVoiceNote = TgBot.Types.ITgRichBlockVoiceNote;
  /// <summary>
  ///   A block with a “Thinking…” placeholder, corresponding to the custom HTML tag
  ///   &lt;tg-thinking&gt;.
  /// </summary>
  ITgRichBlockThinking = TgBot.Types.ITgRichBlockThinking;
  /// <summary>An item of a list to be sent.</summary>
  ITgInputRichBlockListItem = TgBot.Types.ITgInputRichBlockListItem;
  /// <summary>A text paragraph, corresponding to the HTML tag &lt;p&gt;.</summary>
  ITgInputRichBlockParagraph = TgBot.Types.ITgInputRichBlockParagraph;
  /// <summary>
  ///   A section heading, corresponding to the HTML tags &lt;h1&gt;, &lt;h2&gt;, &lt;h3&gt;,
  ///   &lt;h4&gt;, &lt;h5&gt;, or &lt;h6&gt;.
  /// </summary>
  ITgInputRichBlockSectionHeading = TgBot.Types.ITgInputRichBlockSectionHeading;
  /// <summary>
  ///   A preformatted text block, corresponding to the nested HTML tags &lt;pre&gt; and
  ///   &lt;code&gt;.
  /// </summary>
  ITgInputRichBlockPreformatted = TgBot.Types.ITgInputRichBlockPreformatted;
  /// <summary>A footer, corresponding to the HTML tag &lt;footer&gt;.</summary>
  ITgInputRichBlockFooter = TgBot.Types.ITgInputRichBlockFooter;
  /// <summary>A divider, corresponding to the HTML tag &lt;hr/&gt;.</summary>
  ITgInputRichBlockDivider = TgBot.Types.ITgInputRichBlockDivider;
  /// <summary>
  ///   A block with a mathematical expression in LaTeX format, corresponding to the custom HTML tag
  ///   &lt;tg-math-block&gt;.
  /// </summary>
  ITgInputRichBlockMathematicalExpression = TgBot.Types.ITgInputRichBlockMathematicalExpression;
  /// <summary>
  ///   A block with an anchor, corresponding to the HTML tag &lt;a&gt; with the attribute name.
  /// </summary>
  ITgInputRichBlockAnchor = TgBot.Types.ITgInputRichBlockAnchor;
  /// <summary>
  ///   A list of blocks, corresponding to the HTML tag &lt;ul&gt; or &lt;ol&gt; with multiple
  ///   nested tags &lt;li&gt;.
  /// </summary>
  ITgInputRichBlockList = TgBot.Types.ITgInputRichBlockList;
  /// <summary>
  ///   A block quotation, corresponding to the HTML tag &lt;blockquote&gt;.
  /// </summary>
  ITgInputRichBlockBlockQuotation = TgBot.Types.ITgInputRichBlockBlockQuotation;
  /// <summary>
  ///   A block quotation, corresponding to the HTML tag &lt;blockquote&gt; with custom attribute
  ///   "expandable".
  /// </summary>
  ITgInputRichBlockExpandableBlockQuotation = TgBot.Types.ITgInputRichBlockExpandableBlockQuotation;
  /// <summary>
  ///   A quotation with centered text, loosely corresponding to the HTML tag &lt;aside&gt;.
  /// </summary>
  ITgInputRichBlockPullQuotation = TgBot.Types.ITgInputRichBlockPullQuotation;
  /// <summary>A collage, corresponding to the custom HTML tag &lt;tg-collage&gt;.</summary>
  ITgInputRichBlockCollage = TgBot.Types.ITgInputRichBlockCollage;
  /// <summary>
  ///   A slideshow, corresponding to the custom HTML tag &lt;tg-slideshow&gt;.
  /// </summary>
  ITgInputRichBlockSlideshow = TgBot.Types.ITgInputRichBlockSlideshow;
  /// <summary>A table, corresponding to the HTML tag &lt;table&gt;.</summary>
  ITgInputRichBlockTable = TgBot.Types.ITgInputRichBlockTable;
  /// <summary>
  ///   An expandable block for details disclosure, corresponding to the HTML tag &lt;details&gt;.
  /// </summary>
  ITgInputRichBlockDetails = TgBot.Types.ITgInputRichBlockDetails;
  /// <summary>
  ///   A block with a map, corresponding to the custom HTML tag &lt;tg-map&gt;.
  /// </summary>
  ITgInputRichBlockMap = TgBot.Types.ITgInputRichBlockMap;
  /// <summary>
  ///   A block containing a list of buttons that are shown in one row, corresponding to the custom
  ///   HTML tag &lt;tg-button-row&gt;.
  /// </summary>
  ITgInputRichBlockButtons = TgBot.Types.ITgInputRichBlockButtons;
  /// <summary>
  ///   A block with an animation, corresponding to the HTML tag &lt;video&gt;.
  /// </summary>
  ITgInputRichBlockAnimation = TgBot.Types.ITgInputRichBlockAnimation;
  /// <summary>
  ///   A block with a music file, corresponding to the HTML tag &lt;audio&gt;.
  /// </summary>
  ITgInputRichBlockAudio = TgBot.Types.ITgInputRichBlockAudio;
  /// <summary>
  ///   A block with a general file, corresponding to the custom HTML tag &lt;tg-document&gt;.
  /// </summary>
  ITgInputRichBlockDocument = TgBot.Types.ITgInputRichBlockDocument;
  /// <summary>A block with a photo, corresponding to the HTML tag &lt;img&gt;.</summary>
  ITgInputRichBlockPhoto = TgBot.Types.ITgInputRichBlockPhoto;
  /// <summary>A block with a video, corresponding to the HTML tag &lt;video&gt;.</summary>
  ITgInputRichBlockVideo = TgBot.Types.ITgInputRichBlockVideo;
  /// <summary>
  ///   A block with a voice note, corresponding to the HTML tag &lt;audio&gt;.
  /// </summary>
  ITgInputRichBlockVoiceNote = TgBot.Types.ITgInputRichBlockVoiceNote;
  /// <summary>
  ///   A block with a “Thinking…” placeholder, corresponding to the custom HTML tag
  ///   &lt;tg-thinking&gt;.
  /// </summary>
  ITgInputRichBlockThinking = TgBot.Types.ITgInputRichBlockThinking;
  /// <summary>This object represents an incoming inline query.</summary>
  ITgInlineQuery = TgBot.Types.ITgInlineQuery;
  /// <summary>
  ///   This object represents a button to be shown above inline query results.
  /// </summary>
  ITgInlineQueryResultsButton = TgBot.Types.ITgInlineQueryResultsButton;
  /// <summary>Represents a link to an article or web page.</summary>
  ITgInlineQueryResultArticle = TgBot.Types.ITgInlineQueryResultArticle;
  /// <summary>Represents a link to a photo.</summary>
  ITgInlineQueryResultPhoto = TgBot.Types.ITgInlineQueryResultPhoto;
  /// <summary>Represents a link to an animated GIF file.</summary>
  ITgInlineQueryResultGif = TgBot.Types.ITgInlineQueryResultGif;
  /// <summary>
  ///   Represents a link to a video animation (H.264/MPEG-4 AVC video without sound).
  /// </summary>
  ITgInlineQueryResultMpeg4Gif = TgBot.Types.ITgInlineQueryResultMpeg4Gif;
  /// <summary>
  ///   Represents a link to a page containing an embedded video player or a video file.
  /// </summary>
  ITgInlineQueryResultVideo = TgBot.Types.ITgInlineQueryResultVideo;
  /// <summary>Represents a link to an MP3 audio file.</summary>
  ITgInlineQueryResultAudio = TgBot.Types.ITgInlineQueryResultAudio;
  /// <summary>
  ///   Represents a link to a voice recording in an .OGG container encoded with OPUS.
  /// </summary>
  ITgInlineQueryResultVoice = TgBot.Types.ITgInlineQueryResultVoice;
  /// <summary>Represents a link to a file.</summary>
  ITgInlineQueryResultDocument = TgBot.Types.ITgInlineQueryResultDocument;
  /// <summary>Represents a location on a map.</summary>
  ITgInlineQueryResultLocation = TgBot.Types.ITgInlineQueryResultLocation;
  /// <summary>Represents a venue.</summary>
  ITgInlineQueryResultVenue = TgBot.Types.ITgInlineQueryResultVenue;
  /// <summary>Represents a contact with a phone number.</summary>
  ITgInlineQueryResultContact = TgBot.Types.ITgInlineQueryResultContact;
  /// <summary>Represents a Game.</summary>
  ITgInlineQueryResultGame = TgBot.Types.ITgInlineQueryResultGame;
  /// <summary>Represents a link to a photo stored on the Telegram servers.</summary>
  ITgInlineQueryResultCachedPhoto = TgBot.Types.ITgInlineQueryResultCachedPhoto;
  /// <summary>
  ///   Represents a link to an animated GIF file stored on the Telegram servers.
  /// </summary>
  ITgInlineQueryResultCachedGif = TgBot.Types.ITgInlineQueryResultCachedGif;
  /// <summary>
  ///   Represents a link to a video animation (H.264/MPEG-4 AVC video without sound) stored on the
  ///   Telegram servers.
  /// </summary>
  ITgInlineQueryResultCachedMpeg4Gif = TgBot.Types.ITgInlineQueryResultCachedMpeg4Gif;
  /// <summary>Represents a link to a sticker stored on the Telegram servers.</summary>
  ITgInlineQueryResultCachedSticker = TgBot.Types.ITgInlineQueryResultCachedSticker;
  /// <summary>Represents a link to a file stored on the Telegram servers.</summary>
  ITgInlineQueryResultCachedDocument = TgBot.Types.ITgInlineQueryResultCachedDocument;
  /// <summary>Represents a link to a video file stored on the Telegram servers.</summary>
  ITgInlineQueryResultCachedVideo = TgBot.Types.ITgInlineQueryResultCachedVideo;
  /// <summary>
  ///   Represents a link to a voice message stored on the Telegram servers.
  /// </summary>
  ITgInlineQueryResultCachedVoice = TgBot.Types.ITgInlineQueryResultCachedVoice;
  /// <summary>
  ///   Represents a link to an MP3 audio file stored on the Telegram servers.
  /// </summary>
  ITgInlineQueryResultCachedAudio = TgBot.Types.ITgInlineQueryResultCachedAudio;
  /// <summary>
  ///   Represents the content of a text message to be sent as the result of an inline query.
  /// </summary>
  ITgInputTextMessageContent = TgBot.Types.ITgInputTextMessageContent;
  /// <summary>
  ///   Represents the content of a rich message to be sent as the result of an inline query.
  /// </summary>
  ITgInputRichMessageContent = TgBot.Types.ITgInputRichMessageContent;
  /// <summary>
  ///   Represents the content of a location message to be sent as the result of an inline query.
  /// </summary>
  ITgInputLocationMessageContent = TgBot.Types.ITgInputLocationMessageContent;
  /// <summary>
  ///   Represents the content of a venue message to be sent as the result of an inline query.
  /// </summary>
  ITgInputVenueMessageContent = TgBot.Types.ITgInputVenueMessageContent;
  /// <summary>
  ///   Represents the content of a contact message to be sent as the result of an inline query.
  /// </summary>
  ITgInputContactMessageContent = TgBot.Types.ITgInputContactMessageContent;
  /// <summary>
  ///   Represents the content of an invoice message to be sent as the result of an inline query.
  /// </summary>
  ITgInputInvoiceMessageContent = TgBot.Types.ITgInputInvoiceMessageContent;
  /// <summary>
  ///   Represents a result of an inline query that was chosen by the user and sent to their chat
  ///   partner.
  /// </summary>
  ITgChosenInlineResult = TgBot.Types.ITgChosenInlineResult;
  /// <summary>
  ///   This object represents a portion of the price for goods or services.
  /// </summary>
  ITgLabeledPrice = TgBot.Types.ITgLabeledPrice;
  /// <summary>This object contains basic information about an invoice.</summary>
  ITgInvoice = TgBot.Types.ITgInvoice;
  /// <summary>This object represents a shipping address.</summary>
  ITgShippingAddress = TgBot.Types.ITgShippingAddress;
  /// <summary>This object represents information about an order.</summary>
  ITgOrderInfo = TgBot.Types.ITgOrderInfo;
  /// <summary>This object represents one shipping option.</summary>
  ITgShippingOption = TgBot.Types.ITgShippingOption;
  /// <summary>This object contains basic information about a successful payment.</summary>
  ITgSuccessfulPayment = TgBot.Types.ITgSuccessfulPayment;
  /// <summary>This object contains basic information about a refunded payment.</summary>
  ITgRefundedPayment = TgBot.Types.ITgRefundedPayment;
  /// <summary>This object contains information about an incoming shipping query.</summary>
  ITgShippingQuery = TgBot.Types.ITgShippingQuery;
  /// <summary>
  ///   This object contains information about an incoming pre-checkout query.
  /// </summary>
  ITgPreCheckoutQuery = TgBot.Types.ITgPreCheckoutQuery;
  /// <summary>This object contains information about a paid media purchase.</summary>
  ITgPaidMediaPurchased = TgBot.Types.ITgPaidMediaPurchased;
  /// <summary>This object describes the state of a revenue withdrawal operation.</summary>
  ITgRevenueWithdrawalState = TgBot.Types.ITgRevenueWithdrawalState;
  /// <summary>The withdrawal is in progress.</summary>
  ITgRevenueWithdrawalStatePending = TgBot.Types.ITgRevenueWithdrawalStatePending;
  /// <summary>The withdrawal succeeded.</summary>
  ITgRevenueWithdrawalStateSucceeded = TgBot.Types.ITgRevenueWithdrawalStateSucceeded;
  /// <summary>The withdrawal failed and the transaction was refunded.</summary>
  ITgRevenueWithdrawalStateFailed = TgBot.Types.ITgRevenueWithdrawalStateFailed;
  /// <summary>
  ///   Contains information about the affiliate that received a commission via this transaction.
  /// </summary>
  ITgAffiliateInfo = TgBot.Types.ITgAffiliateInfo;
  /// <summary>
  ///   This object describes the source of a transaction, or its recipient for outgoing
  ///   transactions.
  /// </summary>
  ITgTransactionPartner = TgBot.Types.ITgTransactionPartner;
  /// <summary>Describes a transaction with a user.</summary>
  ITgTransactionPartnerUser = TgBot.Types.ITgTransactionPartnerUser;
  /// <summary>Describes a transaction with a chat.</summary>
  ITgTransactionPartnerChat = TgBot.Types.ITgTransactionPartnerChat;
  /// <summary>
  ///   Describes the affiliate program that issued the affiliate commission received via this
  ///   transaction.
  /// </summary>
  ITgTransactionPartnerAffiliateProgram = TgBot.Types.ITgTransactionPartnerAffiliateProgram;
  /// <summary>Describes a withdrawal transaction with Fragment.</summary>
  ITgTransactionPartnerFragment = TgBot.Types.ITgTransactionPartnerFragment;
  /// <summary>Describes a withdrawal transaction to the Telegram Ads platform.</summary>
  ITgTransactionPartnerTelegramAds = TgBot.Types.ITgTransactionPartnerTelegramAds;
  /// <summary>Describes a transaction with payment for paid broadcasting.</summary>
  ITgTransactionPartnerTelegramApi = TgBot.Types.ITgTransactionPartnerTelegramApi;
  /// <summary>Describes a transaction with an unknown source or recipient.</summary>
  ITgTransactionPartnerOther = TgBot.Types.ITgTransactionPartnerOther;
  /// <summary>Describes a Telegram Star transaction.</summary>
  ITgStarTransaction = TgBot.Types.ITgStarTransaction;
  /// <summary>Contains a list of Telegram Star transactions.</summary>
  ITgStarTransactions = TgBot.Types.ITgStarTransactions;
  /// <summary>Describes Telegram Passport data shared with the bot by the user.</summary>
  ITgPassportData = TgBot.Types.ITgPassportData;
  /// <summary>This object represents a file uploaded to Telegram Passport.</summary>
  ITgPassportFile = TgBot.Types.ITgPassportFile;
  /// <summary>
  ///   Describes documents or other Telegram Passport elements shared with the bot by the user.
  /// </summary>
  ITgEncryptedPassportElement = TgBot.Types.ITgEncryptedPassportElement;
  /// <summary>
  ///   Describes data required for decrypting and authenticating EncryptedPassportElement.
  /// </summary>
  ITgEncryptedCredentials = TgBot.Types.ITgEncryptedCredentials;
  /// <summary>
  ///   Represents an issue in one of the data fields that was provided by the user.
  /// </summary>
  ITgPassportElementErrorDataField = TgBot.Types.ITgPassportElementErrorDataField;
  /// <summary>Represents an issue with the front side of a document.</summary>
  ITgPassportElementErrorFrontSide = TgBot.Types.ITgPassportElementErrorFrontSide;
  /// <summary>Represents an issue with the reverse side of a document.</summary>
  ITgPassportElementErrorReverseSide = TgBot.Types.ITgPassportElementErrorReverseSide;
  /// <summary>Represents an issue with the selfie with a document.</summary>
  ITgPassportElementErrorSelfie = TgBot.Types.ITgPassportElementErrorSelfie;
  /// <summary>Represents an issue with a document scan.</summary>
  ITgPassportElementErrorFile = TgBot.Types.ITgPassportElementErrorFile;
  /// <summary>Represents an issue with a list of scans.</summary>
  ITgPassportElementErrorFiles = TgBot.Types.ITgPassportElementErrorFiles;
  /// <summary>
  ///   Represents an issue with one of the files that constitute the translation of a document.
  /// </summary>
  ITgPassportElementErrorTranslationFile = TgBot.Types.ITgPassportElementErrorTranslationFile;
  /// <summary>Represents an issue with the translated version of a document.</summary>
  ITgPassportElementErrorTranslationFiles = TgBot.Types.ITgPassportElementErrorTranslationFiles;
  /// <summary>Represents an issue in an unspecified place.</summary>
  ITgPassportElementErrorUnspecified = TgBot.Types.ITgPassportElementErrorUnspecified;
  /// <summary>This object represents a game.</summary>
  ITgGame = TgBot.Types.ITgGame;
  /// <summary>A placeholder, currently holds no information.</summary>
  ITgCallbackGame = TgBot.Types.ITgCallbackGame;
  /// <summary>This object represents one row of the high scores table for a game.</summary>
  ITgGameHighScore = TgBot.Types.ITgGameHighScore;

  { Виды полиморфных типов (свойство Kind) }

  /// <summary>
  ///   Вид объекта MaybeInaccessibleMessage (свойство Kind интерфейса ITgMaybeInaccessibleMessage).
  /// </summary>
  TTgMaybeInaccessibleMessageKind = TgBot.Types.TTgMaybeInaccessibleMessageKind;
  /// <summary>
  ///   Вид объекта MessageOrigin (свойство Kind интерфейса ITgMessageOrigin).
  /// </summary>
  TTgMessageOriginKind = TgBot.Types.TTgMessageOriginKind;
  /// <summary>Вид объекта PaidMedia (свойство Kind интерфейса ITgPaidMedia).</summary>
  TTgPaidMediaKind = TgBot.Types.TTgPaidMediaKind;
  /// <summary>
  ///   Вид объекта BackgroundFill (свойство Kind интерфейса ITgBackgroundFill).
  /// </summary>
  TTgBackgroundFillKind = TgBot.Types.TTgBackgroundFillKind;
  /// <summary>
  ///   Вид объекта BackgroundType (свойство Kind интерфейса ITgBackgroundType).
  /// </summary>
  TTgBackgroundTypeKind = TgBot.Types.TTgBackgroundTypeKind;
  /// <summary>Вид объекта ChatMember (свойство Kind интерфейса ITgChatMember).</summary>
  TTgChatMemberKind = TgBot.Types.TTgChatMemberKind;
  /// <summary>
  ///   Вид объекта ReactionType (свойство Kind интерфейса ITgReactionType).
  /// </summary>
  TTgReactionTypeKind = TgBot.Types.TTgReactionTypeKind;
  /// <summary>Вид объекта OwnedGift (свойство Kind интерфейса ITgOwnedGift).</summary>
  TTgOwnedGiftKind = TgBot.Types.TTgOwnedGiftKind;
  /// <summary>Вид объекта MenuButton (свойство Kind интерфейса ITgMenuButton).</summary>
  TTgMenuButtonKind = TgBot.Types.TTgMenuButtonKind;
  /// <summary>
  ///   Вид объекта ChatBoostSource (свойство Kind интерфейса ITgChatBoostSource).
  /// </summary>
  TTgChatBoostSourceKind = TgBot.Types.TTgChatBoostSourceKind;
  /// <summary>Вид объекта RichText (свойство Kind интерфейса ITgRichText).</summary>
  TTgRichTextKind = TgBot.Types.TTgRichTextKind;
  /// <summary>Вид объекта RichBlock (свойство Kind интерфейса ITgRichBlock).</summary>
  TTgRichBlockKind = TgBot.Types.TTgRichBlockKind;
  /// <summary>
  ///   Вид объекта RevenueWithdrawalState (свойство Kind интерфейса ITgRevenueWithdrawalState).
  /// </summary>
  TTgRevenueWithdrawalStateKind = TgBot.Types.TTgRevenueWithdrawalStateKind;
  /// <summary>
  ///   Вид объекта TransactionPartner (свойство Kind интерфейса ITgTransactionPartner).
  /// </summary>
  TTgTransactionPartnerKind = TgBot.Types.TTgTransactionPartnerKind;

  { Записи констант }

  /// <summary>Режимы разметки текста (parse_mode).</summary>
  TTgParseMode = TgBot.Types.TTgParseMode;
  /// <summary>Типы чатов (Chat.type).</summary>
  TTgChatType = TgBot.Types.TTgChatType;
  /// <summary>Действия для sendChatAction.</summary>
  TTgChatAction = TgBot.Types.TTgChatAction;
  /// <summary>Типы сущностей сообщения (MessageEntity.type).</summary>
  TTgMessageEntityType = TgBot.Types.TTgMessageEntityType;
  /// <summary>Типы опросов (sendPoll.type, Poll.type).</summary>
  TTgPollType = TgBot.Types.TTgPollType;
  /// <summary>Типы стикеров (Sticker.type).</summary>
  TTgStickerType = TgBot.Types.TTgStickerType;
  /// <summary>Типы обновлений (значения allowed_updates), по полям Update.</summary>
  TTgUpdateType = TgBot.Types.TTgUpdateType;

  { Записи-объединения исходящих типов }

  /// <summary>
  ///   This object represents the content of a poll description or a quiz explanation to be sent.
  /// </summary>
  TTgInputPollMedia = TgBot.Types.TTgInputPollMedia;
  /// <summary>This object represents the content of a poll option to be sent.</summary>
  TTgInputPollOptionMedia = TgBot.Types.TTgInputPollOptionMedia;
  /// <summary>Describes the type of a clickable area on a story.</summary>
  TTgStoryAreaType = TgBot.Types.TTgStoryAreaType;
  /// <summary>This object represents the scope to which bot commands are applied.</summary>
  TTgBotCommandScope = TgBot.Types.TTgBotCommandScope;
  /// <summary>This object represents the content of a media message to be sent.</summary>
  TTgInputMedia = TgBot.Types.TTgInputMedia;
  /// <summary>This object describes the paid media to be sent.</summary>
  TTgInputPaidMedia = TgBot.Types.TTgInputPaidMedia;
  /// <summary>This object describes a profile photo to set.</summary>
  TTgInputProfilePhoto = TgBot.Types.TTgInputProfilePhoto;
  /// <summary>This object describes the content of a story to post.</summary>
  TTgInputStoryContent = TgBot.Types.TTgInputStoryContent;
  /// <summary>
  ///   This object represents a block in a rich formatted message to be sent.
  /// </summary>
  TTgInputRichBlock = TgBot.Types.TTgInputRichBlock;
  /// <summary>This object represents one result of an inline query.</summary>
  TTgInlineQueryResult = TgBot.Types.TTgInlineQueryResult;
  /// <summary>
  ///   This object represents the content of a message to be sent as a result of an inline query.
  /// </summary>
  TTgInputMessageContent = TgBot.Types.TTgInputMessageContent;
  /// <summary>
  ///   This object represents an error in the Telegram Passport element which was submitted that
  ///   should be resolved by the user.
  /// </summary>
  TTgPassportElementError = TgBot.Types.TTgPassportElementError;
  /// <summary>
  ///   Медиа rich-сообщения: анимация, аудио, документ, фото, видео или голосовое сообщение.
  /// </summary>
  TTgInputRichMedia = TgBot.Types.TTgInputRichMedia;
  /// <summary>
  ///   Разметка ответа: инлайн-клавиатура, обычная клавиатура, удаление клавиатуры или
  ///   принудительный ответ.
  /// </summary>
  TTgReplyMarkup = TgBot.Types.TTgReplyMarkup;
  /// <summary>
  ///   Элемент медиагруппы (sendMediaGroup): аудио, документ, live-фото, фото или видео.
  /// </summary>
  TTgMediaGroupItem = TgBot.Types.TTgMediaGroupItem;

  { Фабрики TTg<Name>: Create, FromJson }

  /// <summary>Создание ITgUpdate.</summary>
  TTgUpdate = TgBot.Types.TTgUpdate;
  /// <summary>Создание ITgWebhookInfo.</summary>
  TTgWebhookInfo = TgBot.Types.TTgWebhookInfo;
  /// <summary>Создание ITgUser.</summary>
  TTgUser = TgBot.Types.TTgUser;
  /// <summary>Создание ITgChat.</summary>
  TTgChat = TgBot.Types.TTgChat;
  /// <summary>Создание ITgChatFullInfo.</summary>
  TTgChatFullInfo = TgBot.Types.TTgChatFullInfo;
  /// <summary>Создание ITgMaybeInaccessibleMessage.</summary>
  TTgMaybeInaccessibleMessage = TgBot.Types.TTgMaybeInaccessibleMessage;
  /// <summary>Создание ITgMessage.</summary>
  TTgMessage = TgBot.Types.TTgMessage;
  /// <summary>Создание ITgMessageId.</summary>
  TTgMessageId = TgBot.Types.TTgMessageId;
  /// <summary>Создание ITgInaccessibleMessage.</summary>
  TTgInaccessibleMessage = TgBot.Types.TTgInaccessibleMessage;
  /// <summary>Создание ITgMessageEntity.</summary>
  TTgMessageEntity = TgBot.Types.TTgMessageEntity;
  /// <summary>Создание ITgTextQuote.</summary>
  TTgTextQuote = TgBot.Types.TTgTextQuote;
  /// <summary>Создание ITgExternalReplyInfo.</summary>
  TTgExternalReplyInfo = TgBot.Types.TTgExternalReplyInfo;
  /// <summary>Создание ITgReplyParameters.</summary>
  TTgReplyParameters = TgBot.Types.TTgReplyParameters;
  /// <summary>Создание ITgEphemeralMessageParameters.</summary>
  TTgEphemeralMessageParameters = TgBot.Types.TTgEphemeralMessageParameters;
  /// <summary>Создание ITgMessageOrigin.</summary>
  TTgMessageOrigin = TgBot.Types.TTgMessageOrigin;
  /// <summary>Создание ITgMessageOriginUser.</summary>
  TTgMessageOriginUser = TgBot.Types.TTgMessageOriginUser;
  /// <summary>Создание ITgMessageOriginHiddenUser.</summary>
  TTgMessageOriginHiddenUser = TgBot.Types.TTgMessageOriginHiddenUser;
  /// <summary>Создание ITgMessageOriginChat.</summary>
  TTgMessageOriginChat = TgBot.Types.TTgMessageOriginChat;
  /// <summary>Создание ITgMessageOriginChannel.</summary>
  TTgMessageOriginChannel = TgBot.Types.TTgMessageOriginChannel;
  /// <summary>Создание ITgPhotoSize.</summary>
  TTgPhotoSize = TgBot.Types.TTgPhotoSize;
  /// <summary>Создание ITgAnimation.</summary>
  TTgAnimation = TgBot.Types.TTgAnimation;
  /// <summary>Создание ITgAudio.</summary>
  TTgAudio = TgBot.Types.TTgAudio;
  /// <summary>Создание ITgDocument.</summary>
  TTgDocument = TgBot.Types.TTgDocument;
  /// <summary>Создание ITgLivePhoto.</summary>
  TTgLivePhoto = TgBot.Types.TTgLivePhoto;
  /// <summary>Создание ITgStory.</summary>
  TTgStory = TgBot.Types.TTgStory;
  /// <summary>Создание ITgVideoQuality.</summary>
  TTgVideoQuality = TgBot.Types.TTgVideoQuality;
  /// <summary>Создание ITgVideo.</summary>
  TTgVideo = TgBot.Types.TTgVideo;
  /// <summary>Создание ITgVideoNote.</summary>
  TTgVideoNote = TgBot.Types.TTgVideoNote;
  /// <summary>Создание ITgVoice.</summary>
  TTgVoice = TgBot.Types.TTgVoice;
  /// <summary>Создание ITgPaidMediaInfo.</summary>
  TTgPaidMediaInfo = TgBot.Types.TTgPaidMediaInfo;
  /// <summary>Создание ITgPaidMedia.</summary>
  TTgPaidMedia = TgBot.Types.TTgPaidMedia;
  /// <summary>Создание ITgPaidMediaLivePhoto.</summary>
  TTgPaidMediaLivePhoto = TgBot.Types.TTgPaidMediaLivePhoto;
  /// <summary>Создание ITgPaidMediaPhoto.</summary>
  TTgPaidMediaPhoto = TgBot.Types.TTgPaidMediaPhoto;
  /// <summary>Создание ITgPaidMediaPreview.</summary>
  TTgPaidMediaPreview = TgBot.Types.TTgPaidMediaPreview;
  /// <summary>Создание ITgPaidMediaVideo.</summary>
  TTgPaidMediaVideo = TgBot.Types.TTgPaidMediaVideo;
  /// <summary>Создание ITgContact.</summary>
  TTgContact = TgBot.Types.TTgContact;
  /// <summary>Создание ITgDice.</summary>
  TTgDice = TgBot.Types.TTgDice;
  /// <summary>Создание ITgLink.</summary>
  TTgLink = TgBot.Types.TTgLink;
  /// <summary>Создание ITgPollMedia.</summary>
  TTgPollMedia = TgBot.Types.TTgPollMedia;
  /// <summary>Создание ITgPollOption.</summary>
  TTgPollOption = TgBot.Types.TTgPollOption;
  /// <summary>Создание ITgInputPollOption.</summary>
  TTgInputPollOption = TgBot.Types.TTgInputPollOption;
  /// <summary>Создание ITgPollAnswer.</summary>
  TTgPollAnswer = TgBot.Types.TTgPollAnswer;
  /// <summary>Создание ITgPoll.</summary>
  TTgPoll = TgBot.Types.TTgPoll;
  /// <summary>Создание ITgChecklistTask.</summary>
  TTgChecklistTask = TgBot.Types.TTgChecklistTask;
  /// <summary>Создание ITgChecklist.</summary>
  TTgChecklist = TgBot.Types.TTgChecklist;
  /// <summary>Создание ITgInputChecklistTask.</summary>
  TTgInputChecklistTask = TgBot.Types.TTgInputChecklistTask;
  /// <summary>Создание ITgInputChecklist.</summary>
  TTgInputChecklist = TgBot.Types.TTgInputChecklist;
  /// <summary>Создание ITgLocation.</summary>
  TTgLocation = TgBot.Types.TTgLocation;
  /// <summary>Создание ITgVenue.</summary>
  TTgVenue = TgBot.Types.TTgVenue;
  /// <summary>Создание ITgWebAppData.</summary>
  TTgWebAppData = TgBot.Types.TTgWebAppData;
  /// <summary>Создание ITgProximityAlertTriggered.</summary>
  TTgProximityAlertTriggered = TgBot.Types.TTgProximityAlertTriggered;
  /// <summary>Создание ITgMessageAutoDeleteTimerChanged.</summary>
  TTgMessageAutoDeleteTimerChanged = TgBot.Types.TTgMessageAutoDeleteTimerChanged;
  /// <summary>Создание ITgManagedBotCreated.</summary>
  TTgManagedBotCreated = TgBot.Types.TTgManagedBotCreated;
  /// <summary>Создание ITgManagedBotUpdated.</summary>
  TTgManagedBotUpdated = TgBot.Types.TTgManagedBotUpdated;
  /// <summary>Создание ITgBotSubscriptionUpdated.</summary>
  TTgBotSubscriptionUpdated = TgBot.Types.TTgBotSubscriptionUpdated;
  /// <summary>Создание ITgMessageGenerationStopped.</summary>
  TTgMessageGenerationStopped = TgBot.Types.TTgMessageGenerationStopped;
  /// <summary>Создание ITgPollOptionAdded.</summary>
  TTgPollOptionAdded = TgBot.Types.TTgPollOptionAdded;
  /// <summary>Создание ITgPollOptionDeleted.</summary>
  TTgPollOptionDeleted = TgBot.Types.TTgPollOptionDeleted;
  /// <summary>Создание ITgChatBoostAdded.</summary>
  TTgChatBoostAdded = TgBot.Types.TTgChatBoostAdded;
  /// <summary>Создание ITgBackgroundFill.</summary>
  TTgBackgroundFill = TgBot.Types.TTgBackgroundFill;
  /// <summary>Создание ITgBackgroundFillSolid.</summary>
  TTgBackgroundFillSolid = TgBot.Types.TTgBackgroundFillSolid;
  /// <summary>Создание ITgBackgroundFillGradient.</summary>
  TTgBackgroundFillGradient = TgBot.Types.TTgBackgroundFillGradient;
  /// <summary>Создание ITgBackgroundFillFreeformGradient.</summary>
  TTgBackgroundFillFreeformGradient = TgBot.Types.TTgBackgroundFillFreeformGradient;
  /// <summary>Создание ITgBackgroundType.</summary>
  TTgBackgroundType = TgBot.Types.TTgBackgroundType;
  /// <summary>Создание ITgBackgroundTypeFill.</summary>
  TTgBackgroundTypeFill = TgBot.Types.TTgBackgroundTypeFill;
  /// <summary>Создание ITgBackgroundTypeWallpaper.</summary>
  TTgBackgroundTypeWallpaper = TgBot.Types.TTgBackgroundTypeWallpaper;
  /// <summary>Создание ITgBackgroundTypePattern.</summary>
  TTgBackgroundTypePattern = TgBot.Types.TTgBackgroundTypePattern;
  /// <summary>Создание ITgBackgroundTypeChatTheme.</summary>
  TTgBackgroundTypeChatTheme = TgBot.Types.TTgBackgroundTypeChatTheme;
  /// <summary>Создание ITgChatBackground.</summary>
  TTgChatBackground = TgBot.Types.TTgChatBackground;
  /// <summary>Создание ITgChecklistTasksDone.</summary>
  TTgChecklistTasksDone = TgBot.Types.TTgChecklistTasksDone;
  /// <summary>Создание ITgChecklistTasksAdded.</summary>
  TTgChecklistTasksAdded = TgBot.Types.TTgChecklistTasksAdded;
  /// <summary>Создание ITgCommunityChatAdded.</summary>
  TTgCommunityChatAdded = TgBot.Types.TTgCommunityChatAdded;
  /// <summary>Создание ITgCommunityChatJoined.</summary>
  TTgCommunityChatJoined = TgBot.Types.TTgCommunityChatJoined;
  /// <summary>Создание ITgCommunityChatRemoved.</summary>
  TTgCommunityChatRemoved = TgBot.Types.TTgCommunityChatRemoved;
  /// <summary>Создание ITgForumTopicCreated.</summary>
  TTgForumTopicCreated = TgBot.Types.TTgForumTopicCreated;
  /// <summary>Создание ITgForumTopicClosed.</summary>
  TTgForumTopicClosed = TgBot.Types.TTgForumTopicClosed;
  /// <summary>Создание ITgForumTopicEdited.</summary>
  TTgForumTopicEdited = TgBot.Types.TTgForumTopicEdited;
  /// <summary>Создание ITgForumTopicReopened.</summary>
  TTgForumTopicReopened = TgBot.Types.TTgForumTopicReopened;
  /// <summary>Создание ITgGeneralForumTopicHidden.</summary>
  TTgGeneralForumTopicHidden = TgBot.Types.TTgGeneralForumTopicHidden;
  /// <summary>Создание ITgGeneralForumTopicUnhidden.</summary>
  TTgGeneralForumTopicUnhidden = TgBot.Types.TTgGeneralForumTopicUnhidden;
  /// <summary>Создание ITgSharedUser.</summary>
  TTgSharedUser = TgBot.Types.TTgSharedUser;
  /// <summary>Создание ITgUsersShared.</summary>
  TTgUsersShared = TgBot.Types.TTgUsersShared;
  /// <summary>Создание ITgChatShared.</summary>
  TTgChatShared = TgBot.Types.TTgChatShared;
  /// <summary>Создание ITgWriteAccessAllowed.</summary>
  TTgWriteAccessAllowed = TgBot.Types.TTgWriteAccessAllowed;
  /// <summary>Создание ITgVideoChatScheduled.</summary>
  TTgVideoChatScheduled = TgBot.Types.TTgVideoChatScheduled;
  /// <summary>Создание ITgVideoChatStarted.</summary>
  TTgVideoChatStarted = TgBot.Types.TTgVideoChatStarted;
  /// <summary>Создание ITgVideoChatEnded.</summary>
  TTgVideoChatEnded = TgBot.Types.TTgVideoChatEnded;
  /// <summary>Создание ITgVideoChatParticipantsInvited.</summary>
  TTgVideoChatParticipantsInvited = TgBot.Types.TTgVideoChatParticipantsInvited;
  /// <summary>Создание ITgPaidMessagePriceChanged.</summary>
  TTgPaidMessagePriceChanged = TgBot.Types.TTgPaidMessagePriceChanged;
  /// <summary>Создание ITgDirectMessagePriceChanged.</summary>
  TTgDirectMessagePriceChanged = TgBot.Types.TTgDirectMessagePriceChanged;
  /// <summary>Создание ITgSuggestedPostApproved.</summary>
  TTgSuggestedPostApproved = TgBot.Types.TTgSuggestedPostApproved;
  /// <summary>Создание ITgSuggestedPostApprovalFailed.</summary>
  TTgSuggestedPostApprovalFailed = TgBot.Types.TTgSuggestedPostApprovalFailed;
  /// <summary>Создание ITgSuggestedPostDeclined.</summary>
  TTgSuggestedPostDeclined = TgBot.Types.TTgSuggestedPostDeclined;
  /// <summary>Создание ITgSuggestedPostPaid.</summary>
  TTgSuggestedPostPaid = TgBot.Types.TTgSuggestedPostPaid;
  /// <summary>Создание ITgSuggestedPostRefunded.</summary>
  TTgSuggestedPostRefunded = TgBot.Types.TTgSuggestedPostRefunded;
  /// <summary>Создание ITgGiveawayCreated.</summary>
  TTgGiveawayCreated = TgBot.Types.TTgGiveawayCreated;
  /// <summary>Создание ITgGiveaway.</summary>
  TTgGiveaway = TgBot.Types.TTgGiveaway;
  /// <summary>Создание ITgGiveawayWinners.</summary>
  TTgGiveawayWinners = TgBot.Types.TTgGiveawayWinners;
  /// <summary>Создание ITgGiveawayCompleted.</summary>
  TTgGiveawayCompleted = TgBot.Types.TTgGiveawayCompleted;
  /// <summary>Создание ITgLinkPreviewOptions.</summary>
  TTgLinkPreviewOptions = TgBot.Types.TTgLinkPreviewOptions;
  /// <summary>Создание ITgSuggestedPostPrice.</summary>
  TTgSuggestedPostPrice = TgBot.Types.TTgSuggestedPostPrice;
  /// <summary>Создание ITgSuggestedPostInfo.</summary>
  TTgSuggestedPostInfo = TgBot.Types.TTgSuggestedPostInfo;
  /// <summary>Создание ITgSuggestedPostParameters.</summary>
  TTgSuggestedPostParameters = TgBot.Types.TTgSuggestedPostParameters;
  /// <summary>Создание ITgDirectMessagesTopic.</summary>
  TTgDirectMessagesTopic = TgBot.Types.TTgDirectMessagesTopic;
  /// <summary>Создание ITgUserProfilePhotos.</summary>
  TTgUserProfilePhotos = TgBot.Types.TTgUserProfilePhotos;
  /// <summary>Создание ITgUserProfileAudios.</summary>
  TTgUserProfileAudios = TgBot.Types.TTgUserProfileAudios;
  /// <summary>Создание ITgFile.</summary>
  TTgFile = TgBot.Types.TTgFile;
  /// <summary>Создание ITgWebAppInfo.</summary>
  TTgWebAppInfo = TgBot.Types.TTgWebAppInfo;
  /// <summary>Создание ITgReplyKeyboardMarkup.</summary>
  TTgReplyKeyboardMarkup = TgBot.Types.TTgReplyKeyboardMarkup;
  /// <summary>Создание ITgKeyboardButton.</summary>
  TTgKeyboardButton = TgBot.Types.TTgKeyboardButton;
  /// <summary>Создание ITgKeyboardButtonRequestUsers.</summary>
  TTgKeyboardButtonRequestUsers = TgBot.Types.TTgKeyboardButtonRequestUsers;
  /// <summary>Создание ITgKeyboardButtonRequestChat.</summary>
  TTgKeyboardButtonRequestChat = TgBot.Types.TTgKeyboardButtonRequestChat;
  /// <summary>Создание ITgKeyboardButtonRequestManagedBot.</summary>
  TTgKeyboardButtonRequestManagedBot = TgBot.Types.TTgKeyboardButtonRequestManagedBot;
  /// <summary>Создание ITgKeyboardButtonPollType.</summary>
  TTgKeyboardButtonPollType = TgBot.Types.TTgKeyboardButtonPollType;
  /// <summary>Создание ITgReplyKeyboardRemove.</summary>
  TTgReplyKeyboardRemove = TgBot.Types.TTgReplyKeyboardRemove;
  /// <summary>Создание ITgInlineKeyboardMarkup.</summary>
  TTgInlineKeyboardMarkup = TgBot.Types.TTgInlineKeyboardMarkup;
  /// <summary>Создание ITgInlineKeyboardButton.</summary>
  TTgInlineKeyboardButton = TgBot.Types.TTgInlineKeyboardButton;
  /// <summary>Создание ITgLoginUrl.</summary>
  TTgLoginUrl = TgBot.Types.TTgLoginUrl;
  /// <summary>Создание ITgSwitchInlineQueryChosenChat.</summary>
  TTgSwitchInlineQueryChosenChat = TgBot.Types.TTgSwitchInlineQueryChosenChat;
  /// <summary>Создание ITgCopyTextButton.</summary>
  TTgCopyTextButton = TgBot.Types.TTgCopyTextButton;
  /// <summary>Создание ITgDisabledButton.</summary>
  TTgDisabledButton = TgBot.Types.TTgDisabledButton;
  /// <summary>Создание ITgCallbackQuery.</summary>
  TTgCallbackQuery = TgBot.Types.TTgCallbackQuery;
  /// <summary>Создание ITgForceReply.</summary>
  TTgForceReply = TgBot.Types.TTgForceReply;
  /// <summary>Создание ITgCommunity.</summary>
  TTgCommunity = TgBot.Types.TTgCommunity;
  /// <summary>Создание ITgChatPhoto.</summary>
  TTgChatPhoto = TgBot.Types.TTgChatPhoto;
  /// <summary>Создание ITgChatInviteLink.</summary>
  TTgChatInviteLink = TgBot.Types.TTgChatInviteLink;
  /// <summary>Создание ITgChatAdministratorRights.</summary>
  TTgChatAdministratorRights = TgBot.Types.TTgChatAdministratorRights;
  /// <summary>Создание ITgChatMemberUpdated.</summary>
  TTgChatMemberUpdated = TgBot.Types.TTgChatMemberUpdated;
  /// <summary>Создание ITgChatMember.</summary>
  TTgChatMember = TgBot.Types.TTgChatMember;
  /// <summary>Создание ITgChatMemberOwner.</summary>
  TTgChatMemberOwner = TgBot.Types.TTgChatMemberOwner;
  /// <summary>Создание ITgChatMemberAdministrator.</summary>
  TTgChatMemberAdministrator = TgBot.Types.TTgChatMemberAdministrator;
  /// <summary>Создание ITgChatMemberMember.</summary>
  TTgChatMemberMember = TgBot.Types.TTgChatMemberMember;
  /// <summary>Создание ITgChatMemberRestricted.</summary>
  TTgChatMemberRestricted = TgBot.Types.TTgChatMemberRestricted;
  /// <summary>Создание ITgChatMemberLeft.</summary>
  TTgChatMemberLeft = TgBot.Types.TTgChatMemberLeft;
  /// <summary>Создание ITgChatMemberBanned.</summary>
  TTgChatMemberBanned = TgBot.Types.TTgChatMemberBanned;
  /// <summary>Создание ITgChatJoinRequest.</summary>
  TTgChatJoinRequest = TgBot.Types.TTgChatJoinRequest;
  /// <summary>Создание ITgChatPermissions.</summary>
  TTgChatPermissions = TgBot.Types.TTgChatPermissions;
  /// <summary>Создание ITgBirthdate.</summary>
  TTgBirthdate = TgBot.Types.TTgBirthdate;
  /// <summary>Создание ITgBusinessIntro.</summary>
  TTgBusinessIntro = TgBot.Types.TTgBusinessIntro;
  /// <summary>Создание ITgBusinessLocation.</summary>
  TTgBusinessLocation = TgBot.Types.TTgBusinessLocation;
  /// <summary>Создание ITgBusinessOpeningHoursInterval.</summary>
  TTgBusinessOpeningHoursInterval = TgBot.Types.TTgBusinessOpeningHoursInterval;
  /// <summary>Создание ITgBusinessOpeningHours.</summary>
  TTgBusinessOpeningHours = TgBot.Types.TTgBusinessOpeningHours;
  /// <summary>Создание ITgUserRating.</summary>
  TTgUserRating = TgBot.Types.TTgUserRating;
  /// <summary>Создание ITgStoryAreaPosition.</summary>
  TTgStoryAreaPosition = TgBot.Types.TTgStoryAreaPosition;
  /// <summary>Создание ITgLocationAddress.</summary>
  TTgLocationAddress = TgBot.Types.TTgLocationAddress;
  /// <summary>Создание ITgStoryAreaTypeLocation.</summary>
  TTgStoryAreaTypeLocation = TgBot.Types.TTgStoryAreaTypeLocation;
  /// <summary>Создание ITgStoryAreaTypeSuggestedReaction.</summary>
  TTgStoryAreaTypeSuggestedReaction = TgBot.Types.TTgStoryAreaTypeSuggestedReaction;
  /// <summary>Создание ITgStoryAreaTypeLink.</summary>
  TTgStoryAreaTypeLink = TgBot.Types.TTgStoryAreaTypeLink;
  /// <summary>Создание ITgStoryAreaTypeWeather.</summary>
  TTgStoryAreaTypeWeather = TgBot.Types.TTgStoryAreaTypeWeather;
  /// <summary>Создание ITgStoryAreaTypeUniqueGift.</summary>
  TTgStoryAreaTypeUniqueGift = TgBot.Types.TTgStoryAreaTypeUniqueGift;
  /// <summary>Создание ITgStoryArea.</summary>
  TTgStoryArea = TgBot.Types.TTgStoryArea;
  /// <summary>Создание ITgChatLocation.</summary>
  TTgChatLocation = TgBot.Types.TTgChatLocation;
  /// <summary>Создание ITgReactionType.</summary>
  TTgReactionType = TgBot.Types.TTgReactionType;
  /// <summary>Создание ITgReactionTypeEmoji.</summary>
  TTgReactionTypeEmoji = TgBot.Types.TTgReactionTypeEmoji;
  /// <summary>Создание ITgReactionTypeCustomEmoji.</summary>
  TTgReactionTypeCustomEmoji = TgBot.Types.TTgReactionTypeCustomEmoji;
  /// <summary>Создание ITgReactionTypePaid.</summary>
  TTgReactionTypePaid = TgBot.Types.TTgReactionTypePaid;
  /// <summary>Создание ITgReactionCount.</summary>
  TTgReactionCount = TgBot.Types.TTgReactionCount;
  /// <summary>Создание ITgMessageReactionUpdated.</summary>
  TTgMessageReactionUpdated = TgBot.Types.TTgMessageReactionUpdated;
  /// <summary>Создание ITgMessageReactionCountUpdated.</summary>
  TTgMessageReactionCountUpdated = TgBot.Types.TTgMessageReactionCountUpdated;
  /// <summary>Создание ITgForumTopic.</summary>
  TTgForumTopic = TgBot.Types.TTgForumTopic;
  /// <summary>Создание ITgGiftBackground.</summary>
  TTgGiftBackground = TgBot.Types.TTgGiftBackground;
  /// <summary>Создание ITgGift.</summary>
  TTgGift = TgBot.Types.TTgGift;
  /// <summary>Создание ITgGifts.</summary>
  TTgGifts = TgBot.Types.TTgGifts;
  /// <summary>Создание ITgUniqueGiftModel.</summary>
  TTgUniqueGiftModel = TgBot.Types.TTgUniqueGiftModel;
  /// <summary>Создание ITgUniqueGiftSymbol.</summary>
  TTgUniqueGiftSymbol = TgBot.Types.TTgUniqueGiftSymbol;
  /// <summary>Создание ITgUniqueGiftBackdropColors.</summary>
  TTgUniqueGiftBackdropColors = TgBot.Types.TTgUniqueGiftBackdropColors;
  /// <summary>Создание ITgUniqueGiftBackdrop.</summary>
  TTgUniqueGiftBackdrop = TgBot.Types.TTgUniqueGiftBackdrop;
  /// <summary>Создание ITgUniqueGiftColors.</summary>
  TTgUniqueGiftColors = TgBot.Types.TTgUniqueGiftColors;
  /// <summary>Создание ITgUniqueGift.</summary>
  TTgUniqueGift = TgBot.Types.TTgUniqueGift;
  /// <summary>Создание ITgGiftInfo.</summary>
  TTgGiftInfo = TgBot.Types.TTgGiftInfo;
  /// <summary>Создание ITgUniqueGiftInfo.</summary>
  TTgUniqueGiftInfo = TgBot.Types.TTgUniqueGiftInfo;
  /// <summary>Создание ITgOwnedGift.</summary>
  TTgOwnedGift = TgBot.Types.TTgOwnedGift;
  /// <summary>Создание ITgOwnedGiftRegular.</summary>
  TTgOwnedGiftRegular = TgBot.Types.TTgOwnedGiftRegular;
  /// <summary>Создание ITgOwnedGiftUnique.</summary>
  TTgOwnedGiftUnique = TgBot.Types.TTgOwnedGiftUnique;
  /// <summary>Создание ITgOwnedGifts.</summary>
  TTgOwnedGifts = TgBot.Types.TTgOwnedGifts;
  /// <summary>Создание ITgBotAccessSettings.</summary>
  TTgBotAccessSettings = TgBot.Types.TTgBotAccessSettings;
  /// <summary>Создание ITgAcceptedGiftTypes.</summary>
  TTgAcceptedGiftTypes = TgBot.Types.TTgAcceptedGiftTypes;
  /// <summary>Создание ITgStarAmount.</summary>
  TTgStarAmount = TgBot.Types.TTgStarAmount;
  /// <summary>Создание ITgBotCommand.</summary>
  TTgBotCommand = TgBot.Types.TTgBotCommand;
  /// <summary>Создание ITgBotCommandScopeDefault.</summary>
  TTgBotCommandScopeDefault = TgBot.Types.TTgBotCommandScopeDefault;
  /// <summary>Создание ITgBotCommandScopeAllPrivateChats.</summary>
  TTgBotCommandScopeAllPrivateChats = TgBot.Types.TTgBotCommandScopeAllPrivateChats;
  /// <summary>Создание ITgBotCommandScopeAllGroupChats.</summary>
  TTgBotCommandScopeAllGroupChats = TgBot.Types.TTgBotCommandScopeAllGroupChats;
  /// <summary>Создание ITgBotCommandScopeAllChatAdministrators.</summary>
  TTgBotCommandScopeAllChatAdministrators = TgBot.Types.TTgBotCommandScopeAllChatAdministrators;
  /// <summary>Создание ITgBotCommandScopeChat.</summary>
  TTgBotCommandScopeChat = TgBot.Types.TTgBotCommandScopeChat;
  /// <summary>Создание ITgBotCommandScopeChatAdministrators.</summary>
  TTgBotCommandScopeChatAdministrators = TgBot.Types.TTgBotCommandScopeChatAdministrators;
  /// <summary>Создание ITgBotCommandScopeChatMember.</summary>
  TTgBotCommandScopeChatMember = TgBot.Types.TTgBotCommandScopeChatMember;
  /// <summary>Создание ITgBotName.</summary>
  TTgBotName = TgBot.Types.TTgBotName;
  /// <summary>Создание ITgBotDescription.</summary>
  TTgBotDescription = TgBot.Types.TTgBotDescription;
  /// <summary>Создание ITgBotShortDescription.</summary>
  TTgBotShortDescription = TgBot.Types.TTgBotShortDescription;
  /// <summary>Создание ITgMenuButton.</summary>
  TTgMenuButton = TgBot.Types.TTgMenuButton;
  /// <summary>Создание ITgMenuButtonCommands.</summary>
  TTgMenuButtonCommands = TgBot.Types.TTgMenuButtonCommands;
  /// <summary>Создание ITgMenuButtonWebApp.</summary>
  TTgMenuButtonWebApp = TgBot.Types.TTgMenuButtonWebApp;
  /// <summary>Создание ITgMenuButtonDefault.</summary>
  TTgMenuButtonDefault = TgBot.Types.TTgMenuButtonDefault;
  /// <summary>Создание ITgChatBoostSource.</summary>
  TTgChatBoostSource = TgBot.Types.TTgChatBoostSource;
  /// <summary>Создание ITgChatBoostSourcePremium.</summary>
  TTgChatBoostSourcePremium = TgBot.Types.TTgChatBoostSourcePremium;
  /// <summary>Создание ITgChatBoostSourceGiftCode.</summary>
  TTgChatBoostSourceGiftCode = TgBot.Types.TTgChatBoostSourceGiftCode;
  /// <summary>Создание ITgChatBoostSourceGiveaway.</summary>
  TTgChatBoostSourceGiveaway = TgBot.Types.TTgChatBoostSourceGiveaway;
  /// <summary>Создание ITgChatBoost.</summary>
  TTgChatBoost = TgBot.Types.TTgChatBoost;
  /// <summary>Создание ITgChatBoostUpdated.</summary>
  TTgChatBoostUpdated = TgBot.Types.TTgChatBoostUpdated;
  /// <summary>Создание ITgChatBoostRemoved.</summary>
  TTgChatBoostRemoved = TgBot.Types.TTgChatBoostRemoved;
  /// <summary>Создание ITgChatOwnerLeft.</summary>
  TTgChatOwnerLeft = TgBot.Types.TTgChatOwnerLeft;
  /// <summary>Создание ITgChatOwnerChanged.</summary>
  TTgChatOwnerChanged = TgBot.Types.TTgChatOwnerChanged;
  /// <summary>Создание ITgUserChatBoosts.</summary>
  TTgUserChatBoosts = TgBot.Types.TTgUserChatBoosts;
  /// <summary>Создание ITgBusinessBotRights.</summary>
  TTgBusinessBotRights = TgBot.Types.TTgBusinessBotRights;
  /// <summary>Создание ITgBusinessConnection.</summary>
  TTgBusinessConnection = TgBot.Types.TTgBusinessConnection;
  /// <summary>Создание ITgBusinessMessagesDeleted.</summary>
  TTgBusinessMessagesDeleted = TgBot.Types.TTgBusinessMessagesDeleted;
  /// <summary>Создание ITgSentWebAppMessage.</summary>
  TTgSentWebAppMessage = TgBot.Types.TTgSentWebAppMessage;
  /// <summary>Создание ITgSentGuestMessage.</summary>
  TTgSentGuestMessage = TgBot.Types.TTgSentGuestMessage;
  /// <summary>Создание ITgPreparedInlineMessage.</summary>
  TTgPreparedInlineMessage = TgBot.Types.TTgPreparedInlineMessage;
  /// <summary>Создание ITgPreparedKeyboardButton.</summary>
  TTgPreparedKeyboardButton = TgBot.Types.TTgPreparedKeyboardButton;
  /// <summary>Создание ITgResponseParameters.</summary>
  TTgResponseParameters = TgBot.Types.TTgResponseParameters;
  /// <summary>Создание ITgInputMediaAnimation.</summary>
  TTgInputMediaAnimation = TgBot.Types.TTgInputMediaAnimation;
  /// <summary>Создание ITgInputMediaAudio.</summary>
  TTgInputMediaAudio = TgBot.Types.TTgInputMediaAudio;
  /// <summary>Создание ITgInputMediaDocument.</summary>
  TTgInputMediaDocument = TgBot.Types.TTgInputMediaDocument;
  /// <summary>Создание ITgInputMediaLink.</summary>
  TTgInputMediaLink = TgBot.Types.TTgInputMediaLink;
  /// <summary>Создание ITgInputMediaLivePhoto.</summary>
  TTgInputMediaLivePhoto = TgBot.Types.TTgInputMediaLivePhoto;
  /// <summary>Создание ITgInputMediaLocation.</summary>
  TTgInputMediaLocation = TgBot.Types.TTgInputMediaLocation;
  /// <summary>Создание ITgInputMediaPhoto.</summary>
  TTgInputMediaPhoto = TgBot.Types.TTgInputMediaPhoto;
  /// <summary>Создание ITgInputMediaSticker.</summary>
  TTgInputMediaSticker = TgBot.Types.TTgInputMediaSticker;
  /// <summary>Создание ITgInputMediaVenue.</summary>
  TTgInputMediaVenue = TgBot.Types.TTgInputMediaVenue;
  /// <summary>Создание ITgInputMediaVideo.</summary>
  TTgInputMediaVideo = TgBot.Types.TTgInputMediaVideo;
  /// <summary>Создание ITgInputMediaVoiceNote.</summary>
  TTgInputMediaVoiceNote = TgBot.Types.TTgInputMediaVoiceNote;
  /// <summary>Создание ITgInputPaidMediaLivePhoto.</summary>
  TTgInputPaidMediaLivePhoto = TgBot.Types.TTgInputPaidMediaLivePhoto;
  /// <summary>Создание ITgInputPaidMediaPhoto.</summary>
  TTgInputPaidMediaPhoto = TgBot.Types.TTgInputPaidMediaPhoto;
  /// <summary>Создание ITgInputPaidMediaVideo.</summary>
  TTgInputPaidMediaVideo = TgBot.Types.TTgInputPaidMediaVideo;
  /// <summary>Создание ITgInputProfilePhotoStatic.</summary>
  TTgInputProfilePhotoStatic = TgBot.Types.TTgInputProfilePhotoStatic;
  /// <summary>Создание ITgInputProfilePhotoAnimated.</summary>
  TTgInputProfilePhotoAnimated = TgBot.Types.TTgInputProfilePhotoAnimated;
  /// <summary>Создание ITgInputStoryContentPhoto.</summary>
  TTgInputStoryContentPhoto = TgBot.Types.TTgInputStoryContentPhoto;
  /// <summary>Создание ITgInputStoryContentVideo.</summary>
  TTgInputStoryContentVideo = TgBot.Types.TTgInputStoryContentVideo;
  /// <summary>Создание ITgSticker.</summary>
  TTgSticker = TgBot.Types.TTgSticker;
  /// <summary>Создание ITgStickerSet.</summary>
  TTgStickerSet = TgBot.Types.TTgStickerSet;
  /// <summary>Создание ITgMaskPosition.</summary>
  TTgMaskPosition = TgBot.Types.TTgMaskPosition;
  /// <summary>Создание ITgInputSticker.</summary>
  TTgInputSticker = TgBot.Types.TTgInputSticker;
  /// <summary>Создание ITgRichMessage.</summary>
  TTgRichMessage = TgBot.Types.TTgRichMessage;
  /// <summary>Создание ITgInputRichMessage.</summary>
  TTgInputRichMessage = TgBot.Types.TTgInputRichMessage;
  /// <summary>Создание ITgInputRichMessageMedia.</summary>
  TTgInputRichMessageMedia = TgBot.Types.TTgInputRichMessageMedia;
  /// <summary>Создание ITgRichMessageButton.</summary>
  TTgRichMessageButton = TgBot.Types.TTgRichMessageButton;
  /// <summary>Создание ITgRichText.</summary>
  TTgRichText = TgBot.Types.TTgRichText;
  /// <summary>Создание ITgRichTextPlain.</summary>
  TTgRichTextPlain = TgBot.Types.TTgRichTextPlain;
  /// <summary>Создание ITgRichTextList.</summary>
  TTgRichTextList = TgBot.Types.TTgRichTextList;
  /// <summary>Создание ITgRichTextBold.</summary>
  TTgRichTextBold = TgBot.Types.TTgRichTextBold;
  /// <summary>Создание ITgRichTextItalic.</summary>
  TTgRichTextItalic = TgBot.Types.TTgRichTextItalic;
  /// <summary>Создание ITgRichTextUnderline.</summary>
  TTgRichTextUnderline = TgBot.Types.TTgRichTextUnderline;
  /// <summary>Создание ITgRichTextStrikethrough.</summary>
  TTgRichTextStrikethrough = TgBot.Types.TTgRichTextStrikethrough;
  /// <summary>Создание ITgRichTextSpoiler.</summary>
  TTgRichTextSpoiler = TgBot.Types.TTgRichTextSpoiler;
  /// <summary>Создание ITgRichTextDateTime.</summary>
  TTgRichTextDateTime = TgBot.Types.TTgRichTextDateTime;
  /// <summary>Создание ITgRichTextTextMention.</summary>
  TTgRichTextTextMention = TgBot.Types.TTgRichTextTextMention;
  /// <summary>Создание ITgRichTextSubscript.</summary>
  TTgRichTextSubscript = TgBot.Types.TTgRichTextSubscript;
  /// <summary>Создание ITgRichTextSuperscript.</summary>
  TTgRichTextSuperscript = TgBot.Types.TTgRichTextSuperscript;
  /// <summary>Создание ITgRichTextMarked.</summary>
  TTgRichTextMarked = TgBot.Types.TTgRichTextMarked;
  /// <summary>Создание ITgRichTextCode.</summary>
  TTgRichTextCode = TgBot.Types.TTgRichTextCode;
  /// <summary>Создание ITgRichTextCustomEmoji.</summary>
  TTgRichTextCustomEmoji = TgBot.Types.TTgRichTextCustomEmoji;
  /// <summary>Создание ITgRichTextMathematicalExpression.</summary>
  TTgRichTextMathematicalExpression = TgBot.Types.TTgRichTextMathematicalExpression;
  /// <summary>Создание ITgRichTextUrl.</summary>
  TTgRichTextUrl = TgBot.Types.TTgRichTextUrl;
  /// <summary>Создание ITgRichTextEmailAddress.</summary>
  TTgRichTextEmailAddress = TgBot.Types.TTgRichTextEmailAddress;
  /// <summary>Создание ITgRichTextPhoneNumber.</summary>
  TTgRichTextPhoneNumber = TgBot.Types.TTgRichTextPhoneNumber;
  /// <summary>Создание ITgRichTextBankCardNumber.</summary>
  TTgRichTextBankCardNumber = TgBot.Types.TTgRichTextBankCardNumber;
  /// <summary>Создание ITgRichTextMention.</summary>
  TTgRichTextMention = TgBot.Types.TTgRichTextMention;
  /// <summary>Создание ITgRichTextHashtag.</summary>
  TTgRichTextHashtag = TgBot.Types.TTgRichTextHashtag;
  /// <summary>Создание ITgRichTextCashtag.</summary>
  TTgRichTextCashtag = TgBot.Types.TTgRichTextCashtag;
  /// <summary>Создание ITgRichTextBotCommand.</summary>
  TTgRichTextBotCommand = TgBot.Types.TTgRichTextBotCommand;
  /// <summary>Создание ITgRichTextButton.</summary>
  TTgRichTextButton = TgBot.Types.TTgRichTextButton;
  /// <summary>Создание ITgRichTextAnchor.</summary>
  TTgRichTextAnchor = TgBot.Types.TTgRichTextAnchor;
  /// <summary>Создание ITgRichTextAnchorLink.</summary>
  TTgRichTextAnchorLink = TgBot.Types.TTgRichTextAnchorLink;
  /// <summary>Создание ITgRichTextReference.</summary>
  TTgRichTextReference = TgBot.Types.TTgRichTextReference;
  /// <summary>Создание ITgRichTextReferenceLink.</summary>
  TTgRichTextReferenceLink = TgBot.Types.TTgRichTextReferenceLink;
  /// <summary>Создание ITgRichBlockCaption.</summary>
  TTgRichBlockCaption = TgBot.Types.TTgRichBlockCaption;
  /// <summary>Создание ITgRichBlockTableCell.</summary>
  TTgRichBlockTableCell = TgBot.Types.TTgRichBlockTableCell;
  /// <summary>Создание ITgRichBlockListItem.</summary>
  TTgRichBlockListItem = TgBot.Types.TTgRichBlockListItem;
  /// <summary>Создание ITgRichBlock.</summary>
  TTgRichBlock = TgBot.Types.TTgRichBlock;
  /// <summary>Создание ITgRichBlockParagraph.</summary>
  TTgRichBlockParagraph = TgBot.Types.TTgRichBlockParagraph;
  /// <summary>Создание ITgRichBlockSectionHeading.</summary>
  TTgRichBlockSectionHeading = TgBot.Types.TTgRichBlockSectionHeading;
  /// <summary>Создание ITgRichBlockPreformatted.</summary>
  TTgRichBlockPreformatted = TgBot.Types.TTgRichBlockPreformatted;
  /// <summary>Создание ITgRichBlockFooter.</summary>
  TTgRichBlockFooter = TgBot.Types.TTgRichBlockFooter;
  /// <summary>Создание ITgRichBlockDivider.</summary>
  TTgRichBlockDivider = TgBot.Types.TTgRichBlockDivider;
  /// <summary>Создание ITgRichBlockMathematicalExpression.</summary>
  TTgRichBlockMathematicalExpression = TgBot.Types.TTgRichBlockMathematicalExpression;
  /// <summary>Создание ITgRichBlockAnchor.</summary>
  TTgRichBlockAnchor = TgBot.Types.TTgRichBlockAnchor;
  /// <summary>Создание ITgRichBlockList.</summary>
  TTgRichBlockList = TgBot.Types.TTgRichBlockList;
  /// <summary>Создание ITgRichBlockBlockQuotation.</summary>
  TTgRichBlockBlockQuotation = TgBot.Types.TTgRichBlockBlockQuotation;
  /// <summary>Создание ITgRichBlockExpandableBlockQuotation.</summary>
  TTgRichBlockExpandableBlockQuotation = TgBot.Types.TTgRichBlockExpandableBlockQuotation;
  /// <summary>Создание ITgRichBlockPullQuotation.</summary>
  TTgRichBlockPullQuotation = TgBot.Types.TTgRichBlockPullQuotation;
  /// <summary>Создание ITgRichBlockCollage.</summary>
  TTgRichBlockCollage = TgBot.Types.TTgRichBlockCollage;
  /// <summary>Создание ITgRichBlockSlideshow.</summary>
  TTgRichBlockSlideshow = TgBot.Types.TTgRichBlockSlideshow;
  /// <summary>Создание ITgRichBlockTable.</summary>
  TTgRichBlockTable = TgBot.Types.TTgRichBlockTable;
  /// <summary>Создание ITgRichBlockDetails.</summary>
  TTgRichBlockDetails = TgBot.Types.TTgRichBlockDetails;
  /// <summary>Создание ITgRichBlockMap.</summary>
  TTgRichBlockMap = TgBot.Types.TTgRichBlockMap;
  /// <summary>Создание ITgRichBlockButtons.</summary>
  TTgRichBlockButtons = TgBot.Types.TTgRichBlockButtons;
  /// <summary>Создание ITgRichBlockAnimation.</summary>
  TTgRichBlockAnimation = TgBot.Types.TTgRichBlockAnimation;
  /// <summary>Создание ITgRichBlockAudio.</summary>
  TTgRichBlockAudio = TgBot.Types.TTgRichBlockAudio;
  /// <summary>Создание ITgRichBlockDocument.</summary>
  TTgRichBlockDocument = TgBot.Types.TTgRichBlockDocument;
  /// <summary>Создание ITgRichBlockPhoto.</summary>
  TTgRichBlockPhoto = TgBot.Types.TTgRichBlockPhoto;
  /// <summary>Создание ITgRichBlockVideo.</summary>
  TTgRichBlockVideo = TgBot.Types.TTgRichBlockVideo;
  /// <summary>Создание ITgRichBlockVoiceNote.</summary>
  TTgRichBlockVoiceNote = TgBot.Types.TTgRichBlockVoiceNote;
  /// <summary>Создание ITgRichBlockThinking.</summary>
  TTgRichBlockThinking = TgBot.Types.TTgRichBlockThinking;
  /// <summary>Создание ITgInputRichBlockListItem.</summary>
  TTgInputRichBlockListItem = TgBot.Types.TTgInputRichBlockListItem;
  /// <summary>Создание ITgInputRichBlockParagraph.</summary>
  TTgInputRichBlockParagraph = TgBot.Types.TTgInputRichBlockParagraph;
  /// <summary>Создание ITgInputRichBlockSectionHeading.</summary>
  TTgInputRichBlockSectionHeading = TgBot.Types.TTgInputRichBlockSectionHeading;
  /// <summary>Создание ITgInputRichBlockPreformatted.</summary>
  TTgInputRichBlockPreformatted = TgBot.Types.TTgInputRichBlockPreformatted;
  /// <summary>Создание ITgInputRichBlockFooter.</summary>
  TTgInputRichBlockFooter = TgBot.Types.TTgInputRichBlockFooter;
  /// <summary>Создание ITgInputRichBlockDivider.</summary>
  TTgInputRichBlockDivider = TgBot.Types.TTgInputRichBlockDivider;
  /// <summary>Создание ITgInputRichBlockMathematicalExpression.</summary>
  TTgInputRichBlockMathematicalExpression = TgBot.Types.TTgInputRichBlockMathematicalExpression;
  /// <summary>Создание ITgInputRichBlockAnchor.</summary>
  TTgInputRichBlockAnchor = TgBot.Types.TTgInputRichBlockAnchor;
  /// <summary>Создание ITgInputRichBlockList.</summary>
  TTgInputRichBlockList = TgBot.Types.TTgInputRichBlockList;
  /// <summary>Создание ITgInputRichBlockBlockQuotation.</summary>
  TTgInputRichBlockBlockQuotation = TgBot.Types.TTgInputRichBlockBlockQuotation;
  /// <summary>Создание ITgInputRichBlockExpandableBlockQuotation.</summary>
  TTgInputRichBlockExpandableBlockQuotation = TgBot.Types.TTgInputRichBlockExpandableBlockQuotation;
  /// <summary>Создание ITgInputRichBlockPullQuotation.</summary>
  TTgInputRichBlockPullQuotation = TgBot.Types.TTgInputRichBlockPullQuotation;
  /// <summary>Создание ITgInputRichBlockCollage.</summary>
  TTgInputRichBlockCollage = TgBot.Types.TTgInputRichBlockCollage;
  /// <summary>Создание ITgInputRichBlockSlideshow.</summary>
  TTgInputRichBlockSlideshow = TgBot.Types.TTgInputRichBlockSlideshow;
  /// <summary>Создание ITgInputRichBlockTable.</summary>
  TTgInputRichBlockTable = TgBot.Types.TTgInputRichBlockTable;
  /// <summary>Создание ITgInputRichBlockDetails.</summary>
  TTgInputRichBlockDetails = TgBot.Types.TTgInputRichBlockDetails;
  /// <summary>Создание ITgInputRichBlockMap.</summary>
  TTgInputRichBlockMap = TgBot.Types.TTgInputRichBlockMap;
  /// <summary>Создание ITgInputRichBlockButtons.</summary>
  TTgInputRichBlockButtons = TgBot.Types.TTgInputRichBlockButtons;
  /// <summary>Создание ITgInputRichBlockAnimation.</summary>
  TTgInputRichBlockAnimation = TgBot.Types.TTgInputRichBlockAnimation;
  /// <summary>Создание ITgInputRichBlockAudio.</summary>
  TTgInputRichBlockAudio = TgBot.Types.TTgInputRichBlockAudio;
  /// <summary>Создание ITgInputRichBlockDocument.</summary>
  TTgInputRichBlockDocument = TgBot.Types.TTgInputRichBlockDocument;
  /// <summary>Создание ITgInputRichBlockPhoto.</summary>
  TTgInputRichBlockPhoto = TgBot.Types.TTgInputRichBlockPhoto;
  /// <summary>Создание ITgInputRichBlockVideo.</summary>
  TTgInputRichBlockVideo = TgBot.Types.TTgInputRichBlockVideo;
  /// <summary>Создание ITgInputRichBlockVoiceNote.</summary>
  TTgInputRichBlockVoiceNote = TgBot.Types.TTgInputRichBlockVoiceNote;
  /// <summary>Создание ITgInputRichBlockThinking.</summary>
  TTgInputRichBlockThinking = TgBot.Types.TTgInputRichBlockThinking;
  /// <summary>Создание ITgInlineQuery.</summary>
  TTgInlineQuery = TgBot.Types.TTgInlineQuery;
  /// <summary>Создание ITgInlineQueryResultsButton.</summary>
  TTgInlineQueryResultsButton = TgBot.Types.TTgInlineQueryResultsButton;
  /// <summary>Создание ITgInlineQueryResultArticle.</summary>
  TTgInlineQueryResultArticle = TgBot.Types.TTgInlineQueryResultArticle;
  /// <summary>Создание ITgInlineQueryResultPhoto.</summary>
  TTgInlineQueryResultPhoto = TgBot.Types.TTgInlineQueryResultPhoto;
  /// <summary>Создание ITgInlineQueryResultGif.</summary>
  TTgInlineQueryResultGif = TgBot.Types.TTgInlineQueryResultGif;
  /// <summary>Создание ITgInlineQueryResultMpeg4Gif.</summary>
  TTgInlineQueryResultMpeg4Gif = TgBot.Types.TTgInlineQueryResultMpeg4Gif;
  /// <summary>Создание ITgInlineQueryResultVideo.</summary>
  TTgInlineQueryResultVideo = TgBot.Types.TTgInlineQueryResultVideo;
  /// <summary>Создание ITgInlineQueryResultAudio.</summary>
  TTgInlineQueryResultAudio = TgBot.Types.TTgInlineQueryResultAudio;
  /// <summary>Создание ITgInlineQueryResultVoice.</summary>
  TTgInlineQueryResultVoice = TgBot.Types.TTgInlineQueryResultVoice;
  /// <summary>Создание ITgInlineQueryResultDocument.</summary>
  TTgInlineQueryResultDocument = TgBot.Types.TTgInlineQueryResultDocument;
  /// <summary>Создание ITgInlineQueryResultLocation.</summary>
  TTgInlineQueryResultLocation = TgBot.Types.TTgInlineQueryResultLocation;
  /// <summary>Создание ITgInlineQueryResultVenue.</summary>
  TTgInlineQueryResultVenue = TgBot.Types.TTgInlineQueryResultVenue;
  /// <summary>Создание ITgInlineQueryResultContact.</summary>
  TTgInlineQueryResultContact = TgBot.Types.TTgInlineQueryResultContact;
  /// <summary>Создание ITgInlineQueryResultGame.</summary>
  TTgInlineQueryResultGame = TgBot.Types.TTgInlineQueryResultGame;
  /// <summary>Создание ITgInlineQueryResultCachedPhoto.</summary>
  TTgInlineQueryResultCachedPhoto = TgBot.Types.TTgInlineQueryResultCachedPhoto;
  /// <summary>Создание ITgInlineQueryResultCachedGif.</summary>
  TTgInlineQueryResultCachedGif = TgBot.Types.TTgInlineQueryResultCachedGif;
  /// <summary>Создание ITgInlineQueryResultCachedMpeg4Gif.</summary>
  TTgInlineQueryResultCachedMpeg4Gif = TgBot.Types.TTgInlineQueryResultCachedMpeg4Gif;
  /// <summary>Создание ITgInlineQueryResultCachedSticker.</summary>
  TTgInlineQueryResultCachedSticker = TgBot.Types.TTgInlineQueryResultCachedSticker;
  /// <summary>Создание ITgInlineQueryResultCachedDocument.</summary>
  TTgInlineQueryResultCachedDocument = TgBot.Types.TTgInlineQueryResultCachedDocument;
  /// <summary>Создание ITgInlineQueryResultCachedVideo.</summary>
  TTgInlineQueryResultCachedVideo = TgBot.Types.TTgInlineQueryResultCachedVideo;
  /// <summary>Создание ITgInlineQueryResultCachedVoice.</summary>
  TTgInlineQueryResultCachedVoice = TgBot.Types.TTgInlineQueryResultCachedVoice;
  /// <summary>Создание ITgInlineQueryResultCachedAudio.</summary>
  TTgInlineQueryResultCachedAudio = TgBot.Types.TTgInlineQueryResultCachedAudio;
  /// <summary>Создание ITgInputTextMessageContent.</summary>
  TTgInputTextMessageContent = TgBot.Types.TTgInputTextMessageContent;
  /// <summary>Создание ITgInputRichMessageContent.</summary>
  TTgInputRichMessageContent = TgBot.Types.TTgInputRichMessageContent;
  /// <summary>Создание ITgInputLocationMessageContent.</summary>
  TTgInputLocationMessageContent = TgBot.Types.TTgInputLocationMessageContent;
  /// <summary>Создание ITgInputVenueMessageContent.</summary>
  TTgInputVenueMessageContent = TgBot.Types.TTgInputVenueMessageContent;
  /// <summary>Создание ITgInputContactMessageContent.</summary>
  TTgInputContactMessageContent = TgBot.Types.TTgInputContactMessageContent;
  /// <summary>Создание ITgInputInvoiceMessageContent.</summary>
  TTgInputInvoiceMessageContent = TgBot.Types.TTgInputInvoiceMessageContent;
  /// <summary>Создание ITgChosenInlineResult.</summary>
  TTgChosenInlineResult = TgBot.Types.TTgChosenInlineResult;
  /// <summary>Создание ITgLabeledPrice.</summary>
  TTgLabeledPrice = TgBot.Types.TTgLabeledPrice;
  /// <summary>Создание ITgInvoice.</summary>
  TTgInvoice = TgBot.Types.TTgInvoice;
  /// <summary>Создание ITgShippingAddress.</summary>
  TTgShippingAddress = TgBot.Types.TTgShippingAddress;
  /// <summary>Создание ITgOrderInfo.</summary>
  TTgOrderInfo = TgBot.Types.TTgOrderInfo;
  /// <summary>Создание ITgShippingOption.</summary>
  TTgShippingOption = TgBot.Types.TTgShippingOption;
  /// <summary>Создание ITgSuccessfulPayment.</summary>
  TTgSuccessfulPayment = TgBot.Types.TTgSuccessfulPayment;
  /// <summary>Создание ITgRefundedPayment.</summary>
  TTgRefundedPayment = TgBot.Types.TTgRefundedPayment;
  /// <summary>Создание ITgShippingQuery.</summary>
  TTgShippingQuery = TgBot.Types.TTgShippingQuery;
  /// <summary>Создание ITgPreCheckoutQuery.</summary>
  TTgPreCheckoutQuery = TgBot.Types.TTgPreCheckoutQuery;
  /// <summary>Создание ITgPaidMediaPurchased.</summary>
  TTgPaidMediaPurchased = TgBot.Types.TTgPaidMediaPurchased;
  /// <summary>Создание ITgRevenueWithdrawalState.</summary>
  TTgRevenueWithdrawalState = TgBot.Types.TTgRevenueWithdrawalState;
  /// <summary>Создание ITgRevenueWithdrawalStatePending.</summary>
  TTgRevenueWithdrawalStatePending = TgBot.Types.TTgRevenueWithdrawalStatePending;
  /// <summary>Создание ITgRevenueWithdrawalStateSucceeded.</summary>
  TTgRevenueWithdrawalStateSucceeded = TgBot.Types.TTgRevenueWithdrawalStateSucceeded;
  /// <summary>Создание ITgRevenueWithdrawalStateFailed.</summary>
  TTgRevenueWithdrawalStateFailed = TgBot.Types.TTgRevenueWithdrawalStateFailed;
  /// <summary>Создание ITgAffiliateInfo.</summary>
  TTgAffiliateInfo = TgBot.Types.TTgAffiliateInfo;
  /// <summary>Создание ITgTransactionPartner.</summary>
  TTgTransactionPartner = TgBot.Types.TTgTransactionPartner;
  /// <summary>Создание ITgTransactionPartnerUser.</summary>
  TTgTransactionPartnerUser = TgBot.Types.TTgTransactionPartnerUser;
  /// <summary>Создание ITgTransactionPartnerChat.</summary>
  TTgTransactionPartnerChat = TgBot.Types.TTgTransactionPartnerChat;
  /// <summary>Создание ITgTransactionPartnerAffiliateProgram.</summary>
  TTgTransactionPartnerAffiliateProgram = TgBot.Types.TTgTransactionPartnerAffiliateProgram;
  /// <summary>Создание ITgTransactionPartnerFragment.</summary>
  TTgTransactionPartnerFragment = TgBot.Types.TTgTransactionPartnerFragment;
  /// <summary>Создание ITgTransactionPartnerTelegramAds.</summary>
  TTgTransactionPartnerTelegramAds = TgBot.Types.TTgTransactionPartnerTelegramAds;
  /// <summary>Создание ITgTransactionPartnerTelegramApi.</summary>
  TTgTransactionPartnerTelegramApi = TgBot.Types.TTgTransactionPartnerTelegramApi;
  /// <summary>Создание ITgTransactionPartnerOther.</summary>
  TTgTransactionPartnerOther = TgBot.Types.TTgTransactionPartnerOther;
  /// <summary>Создание ITgStarTransaction.</summary>
  TTgStarTransaction = TgBot.Types.TTgStarTransaction;
  /// <summary>Создание ITgStarTransactions.</summary>
  TTgStarTransactions = TgBot.Types.TTgStarTransactions;
  /// <summary>Создание ITgPassportData.</summary>
  TTgPassportData = TgBot.Types.TTgPassportData;
  /// <summary>Создание ITgPassportFile.</summary>
  TTgPassportFile = TgBot.Types.TTgPassportFile;
  /// <summary>Создание ITgEncryptedPassportElement.</summary>
  TTgEncryptedPassportElement = TgBot.Types.TTgEncryptedPassportElement;
  /// <summary>Создание ITgEncryptedCredentials.</summary>
  TTgEncryptedCredentials = TgBot.Types.TTgEncryptedCredentials;
  /// <summary>Создание ITgPassportElementErrorDataField.</summary>
  TTgPassportElementErrorDataField = TgBot.Types.TTgPassportElementErrorDataField;
  /// <summary>Создание ITgPassportElementErrorFrontSide.</summary>
  TTgPassportElementErrorFrontSide = TgBot.Types.TTgPassportElementErrorFrontSide;
  /// <summary>Создание ITgPassportElementErrorReverseSide.</summary>
  TTgPassportElementErrorReverseSide = TgBot.Types.TTgPassportElementErrorReverseSide;
  /// <summary>Создание ITgPassportElementErrorSelfie.</summary>
  TTgPassportElementErrorSelfie = TgBot.Types.TTgPassportElementErrorSelfie;
  /// <summary>Создание ITgPassportElementErrorFile.</summary>
  TTgPassportElementErrorFile = TgBot.Types.TTgPassportElementErrorFile;
  /// <summary>Создание ITgPassportElementErrorFiles.</summary>
  TTgPassportElementErrorFiles = TgBot.Types.TTgPassportElementErrorFiles;
  /// <summary>Создание ITgPassportElementErrorTranslationFile.</summary>
  TTgPassportElementErrorTranslationFile = TgBot.Types.TTgPassportElementErrorTranslationFile;
  /// <summary>Создание ITgPassportElementErrorTranslationFiles.</summary>
  TTgPassportElementErrorTranslationFiles = TgBot.Types.TTgPassportElementErrorTranslationFiles;
  /// <summary>Создание ITgPassportElementErrorUnspecified.</summary>
  TTgPassportElementErrorUnspecified = TgBot.Types.TTgPassportElementErrorUnspecified;
  /// <summary>Создание ITgGame.</summary>
  TTgGame = TgBot.Types.TTgGame;
  /// <summary>Создание ITgCallbackGame.</summary>
  TTgCallbackGame = TgBot.Types.TTgCallbackGame;
  /// <summary>Создание ITgGameHighScore.</summary>
  TTgGameHighScore = TgBot.Types.TTgGameHighScore;

  { Необязательные параметры методов }

  /// <summary>Необязательные параметры getUpdates.</summary>
  TTgGetUpdatesOptions = TgBot.Types.TTgGetUpdatesOptions;
  /// <summary>Необязательные параметры setWebhook.</summary>
  TTgSetWebhookOptions = TgBot.Types.TTgSetWebhookOptions;
  /// <summary>Необязательные параметры deleteWebhook.</summary>
  TTgDeleteWebhookOptions = TgBot.Types.TTgDeleteWebhookOptions;
  /// <summary>Необязательные параметры sendMessage.</summary>
  TTgSendMessageOptions = TgBot.Types.TTgSendMessageOptions;
  /// <summary>Необязательные параметры forwardMessage.</summary>
  TTgForwardMessageOptions = TgBot.Types.TTgForwardMessageOptions;
  /// <summary>Необязательные параметры forwardMessages.</summary>
  TTgForwardMessagesOptions = TgBot.Types.TTgForwardMessagesOptions;
  /// <summary>Необязательные параметры copyMessage.</summary>
  TTgCopyMessageOptions = TgBot.Types.TTgCopyMessageOptions;
  /// <summary>Необязательные параметры copyMessages.</summary>
  TTgCopyMessagesOptions = TgBot.Types.TTgCopyMessagesOptions;
  /// <summary>Необязательные параметры sendPhoto.</summary>
  TTgSendPhotoOptions = TgBot.Types.TTgSendPhotoOptions;
  /// <summary>Необязательные параметры sendLivePhoto.</summary>
  TTgSendLivePhotoOptions = TgBot.Types.TTgSendLivePhotoOptions;
  /// <summary>Необязательные параметры sendAudio.</summary>
  TTgSendAudioOptions = TgBot.Types.TTgSendAudioOptions;
  /// <summary>Необязательные параметры sendDocument.</summary>
  TTgSendDocumentOptions = TgBot.Types.TTgSendDocumentOptions;
  /// <summary>Необязательные параметры sendVideo.</summary>
  TTgSendVideoOptions = TgBot.Types.TTgSendVideoOptions;
  /// <summary>Необязательные параметры sendAnimation.</summary>
  TTgSendAnimationOptions = TgBot.Types.TTgSendAnimationOptions;
  /// <summary>Необязательные параметры sendVoice.</summary>
  TTgSendVoiceOptions = TgBot.Types.TTgSendVoiceOptions;
  /// <summary>Необязательные параметры sendVideoNote.</summary>
  TTgSendVideoNoteOptions = TgBot.Types.TTgSendVideoNoteOptions;
  /// <summary>Необязательные параметры sendPaidMedia.</summary>
  TTgSendPaidMediaOptions = TgBot.Types.TTgSendPaidMediaOptions;
  /// <summary>Необязательные параметры sendMediaGroup.</summary>
  TTgSendMediaGroupOptions = TgBot.Types.TTgSendMediaGroupOptions;
  /// <summary>Необязательные параметры sendLocation.</summary>
  TTgSendLocationOptions = TgBot.Types.TTgSendLocationOptions;
  /// <summary>Необязательные параметры sendVenue.</summary>
  TTgSendVenueOptions = TgBot.Types.TTgSendVenueOptions;
  /// <summary>Необязательные параметры sendContact.</summary>
  TTgSendContactOptions = TgBot.Types.TTgSendContactOptions;
  /// <summary>Необязательные параметры sendPoll.</summary>
  TTgSendPollOptions = TgBot.Types.TTgSendPollOptions;
  /// <summary>Необязательные параметры sendChecklist.</summary>
  TTgSendChecklistOptions = TgBot.Types.TTgSendChecklistOptions;
  /// <summary>Необязательные параметры sendDice.</summary>
  TTgSendDiceOptions = TgBot.Types.TTgSendDiceOptions;
  /// <summary>Необязательные параметры sendMessageDraft.</summary>
  TTgSendMessageDraftOptions = TgBot.Types.TTgSendMessageDraftOptions;
  /// <summary>Необязательные параметры sendChatAction.</summary>
  TTgSendChatActionOptions = TgBot.Types.TTgSendChatActionOptions;
  /// <summary>Необязательные параметры setMessageReaction.</summary>
  TTgSetMessageReactionOptions = TgBot.Types.TTgSetMessageReactionOptions;
  /// <summary>Необязательные параметры getUserProfilePhotos.</summary>
  TTgGetUserProfilePhotosOptions = TgBot.Types.TTgGetUserProfilePhotosOptions;
  /// <summary>Необязательные параметры getUserProfileAudios.</summary>
  TTgGetUserProfileAudiosOptions = TgBot.Types.TTgGetUserProfileAudiosOptions;
  /// <summary>Необязательные параметры setUserEmojiStatus.</summary>
  TTgSetUserEmojiStatusOptions = TgBot.Types.TTgSetUserEmojiStatusOptions;
  /// <summary>Необязательные параметры banChatMember.</summary>
  TTgBanChatMemberOptions = TgBot.Types.TTgBanChatMemberOptions;
  /// <summary>Необязательные параметры unbanChatMember.</summary>
  TTgUnbanChatMemberOptions = TgBot.Types.TTgUnbanChatMemberOptions;
  /// <summary>Необязательные параметры restrictChatMember.</summary>
  TTgRestrictChatMemberOptions = TgBot.Types.TTgRestrictChatMemberOptions;
  /// <summary>Необязательные параметры promoteChatMember.</summary>
  TTgPromoteChatMemberOptions = TgBot.Types.TTgPromoteChatMemberOptions;
  /// <summary>Необязательные параметры setChatMemberTag.</summary>
  TTgSetChatMemberTagOptions = TgBot.Types.TTgSetChatMemberTagOptions;
  /// <summary>Необязательные параметры setChatPermissions.</summary>
  TTgSetChatPermissionsOptions = TgBot.Types.TTgSetChatPermissionsOptions;
  /// <summary>Необязательные параметры createChatInviteLink.</summary>
  TTgCreateChatInviteLinkOptions = TgBot.Types.TTgCreateChatInviteLinkOptions;
  /// <summary>Необязательные параметры editChatInviteLink.</summary>
  TTgEditChatInviteLinkOptions = TgBot.Types.TTgEditChatInviteLinkOptions;
  /// <summary>Необязательные параметры createChatSubscriptionInviteLink.</summary>
  TTgCreateChatSubscriptionInviteLinkOptions = TgBot.Types.TTgCreateChatSubscriptionInviteLinkOptions;
  /// <summary>Необязательные параметры editChatSubscriptionInviteLink.</summary>
  TTgEditChatSubscriptionInviteLinkOptions = TgBot.Types.TTgEditChatSubscriptionInviteLinkOptions;
  /// <summary>Необязательные параметры setChatDescription.</summary>
  TTgSetChatDescriptionOptions = TgBot.Types.TTgSetChatDescriptionOptions;
  /// <summary>Необязательные параметры pinChatMessage.</summary>
  TTgPinChatMessageOptions = TgBot.Types.TTgPinChatMessageOptions;
  /// <summary>Необязательные параметры unpinChatMessage.</summary>
  TTgUnpinChatMessageOptions = TgBot.Types.TTgUnpinChatMessageOptions;
  /// <summary>Необязательные параметры getChatAdministrators.</summary>
  TTgGetChatAdministratorsOptions = TgBot.Types.TTgGetChatAdministratorsOptions;
  /// <summary>Необязательные параметры createForumTopic.</summary>
  TTgCreateForumTopicOptions = TgBot.Types.TTgCreateForumTopicOptions;
  /// <summary>Необязательные параметры editForumTopic.</summary>
  TTgEditForumTopicOptions = TgBot.Types.TTgEditForumTopicOptions;
  /// <summary>Необязательные параметры answerCallbackQuery.</summary>
  TTgAnswerCallbackQueryOptions = TgBot.Types.TTgAnswerCallbackQueryOptions;
  /// <summary>Необязательные параметры setManagedBotAccessSettings.</summary>
  TTgSetManagedBotAccessSettingsOptions = TgBot.Types.TTgSetManagedBotAccessSettingsOptions;
  /// <summary>Необязательные параметры setMyCommands.</summary>
  TTgSetMyCommandsOptions = TgBot.Types.TTgSetMyCommandsOptions;
  /// <summary>Необязательные параметры deleteMyCommands.</summary>
  TTgDeleteMyCommandsOptions = TgBot.Types.TTgDeleteMyCommandsOptions;
  /// <summary>Необязательные параметры getMyCommands.</summary>
  TTgGetMyCommandsOptions = TgBot.Types.TTgGetMyCommandsOptions;
  /// <summary>Необязательные параметры setMyName.</summary>
  TTgSetMyNameOptions = TgBot.Types.TTgSetMyNameOptions;
  /// <summary>Необязательные параметры getMyName.</summary>
  TTgGetMyNameOptions = TgBot.Types.TTgGetMyNameOptions;
  /// <summary>Необязательные параметры setMyDescription.</summary>
  TTgSetMyDescriptionOptions = TgBot.Types.TTgSetMyDescriptionOptions;
  /// <summary>Необязательные параметры getMyDescription.</summary>
  TTgGetMyDescriptionOptions = TgBot.Types.TTgGetMyDescriptionOptions;
  /// <summary>Необязательные параметры setMyShortDescription.</summary>
  TTgSetMyShortDescriptionOptions = TgBot.Types.TTgSetMyShortDescriptionOptions;
  /// <summary>Необязательные параметры getMyShortDescription.</summary>
  TTgGetMyShortDescriptionOptions = TgBot.Types.TTgGetMyShortDescriptionOptions;
  /// <summary>Необязательные параметры setChatMenuButton.</summary>
  TTgSetChatMenuButtonOptions = TgBot.Types.TTgSetChatMenuButtonOptions;
  /// <summary>Необязательные параметры getChatMenuButton.</summary>
  TTgGetChatMenuButtonOptions = TgBot.Types.TTgGetChatMenuButtonOptions;
  /// <summary>Необязательные параметры setMyDefaultAdministratorRights.</summary>
  TTgSetMyDefaultAdministratorRightsOptions = TgBot.Types.TTgSetMyDefaultAdministratorRightsOptions;
  /// <summary>Необязательные параметры getMyDefaultAdministratorRights.</summary>
  TTgGetMyDefaultAdministratorRightsOptions = TgBot.Types.TTgGetMyDefaultAdministratorRightsOptions;
  /// <summary>Необязательные параметры sendGift.</summary>
  TTgSendGiftOptions = TgBot.Types.TTgSendGiftOptions;
  /// <summary>Необязательные параметры giftPremiumSubscription.</summary>
  TTgGiftPremiumSubscriptionOptions = TgBot.Types.TTgGiftPremiumSubscriptionOptions;
  /// <summary>Необязательные параметры verifyUser.</summary>
  TTgVerifyUserOptions = TgBot.Types.TTgVerifyUserOptions;
  /// <summary>Необязательные параметры verifyChat.</summary>
  TTgVerifyChatOptions = TgBot.Types.TTgVerifyChatOptions;
  /// <summary>Необязательные параметры setBusinessAccountName.</summary>
  TTgSetBusinessAccountNameOptions = TgBot.Types.TTgSetBusinessAccountNameOptions;
  /// <summary>Необязательные параметры setBusinessAccountUsername.</summary>
  TTgSetBusinessAccountUsernameOptions = TgBot.Types.TTgSetBusinessAccountUsernameOptions;
  /// <summary>Необязательные параметры setBusinessAccountBio.</summary>
  TTgSetBusinessAccountBioOptions = TgBot.Types.TTgSetBusinessAccountBioOptions;
  /// <summary>Необязательные параметры setBusinessAccountProfilePhoto.</summary>
  TTgSetBusinessAccountProfilePhotoOptions = TgBot.Types.TTgSetBusinessAccountProfilePhotoOptions;
  /// <summary>Необязательные параметры removeBusinessAccountProfilePhoto.</summary>
  TTgRemoveBusinessAccountProfilePhotoOptions = TgBot.Types.TTgRemoveBusinessAccountProfilePhotoOptions;
  /// <summary>Необязательные параметры getBusinessAccountGifts.</summary>
  TTgGetBusinessAccountGiftsOptions = TgBot.Types.TTgGetBusinessAccountGiftsOptions;
  /// <summary>Необязательные параметры getUserGifts.</summary>
  TTgGetUserGiftsOptions = TgBot.Types.TTgGetUserGiftsOptions;
  /// <summary>Необязательные параметры getChatGifts.</summary>
  TTgGetChatGiftsOptions = TgBot.Types.TTgGetChatGiftsOptions;
  /// <summary>Необязательные параметры upgradeGift.</summary>
  TTgUpgradeGiftOptions = TgBot.Types.TTgUpgradeGiftOptions;
  /// <summary>Необязательные параметры transferGift.</summary>
  TTgTransferGiftOptions = TgBot.Types.TTgTransferGiftOptions;
  /// <summary>Необязательные параметры postStory.</summary>
  TTgPostStoryOptions = TgBot.Types.TTgPostStoryOptions;
  /// <summary>Необязательные параметры repostStory.</summary>
  TTgRepostStoryOptions = TgBot.Types.TTgRepostStoryOptions;
  /// <summary>Необязательные параметры editStory.</summary>
  TTgEditStoryOptions = TgBot.Types.TTgEditStoryOptions;
  /// <summary>Необязательные параметры savePreparedInlineMessage.</summary>
  TTgSavePreparedInlineMessageOptions = TgBot.Types.TTgSavePreparedInlineMessageOptions;
  /// <summary>Необязательные параметры editMessageText.</summary>
  TTgEditMessageTextOptions = TgBot.Types.TTgEditMessageTextOptions;
  /// <summary>Необязательные параметры editMessageCaption.</summary>
  TTgEditMessageCaptionOptions = TgBot.Types.TTgEditMessageCaptionOptions;
  /// <summary>Необязательные параметры editMessageMedia.</summary>
  TTgEditMessageMediaOptions = TgBot.Types.TTgEditMessageMediaOptions;
  /// <summary>Необязательные параметры editMessageLiveLocation.</summary>
  TTgEditMessageLiveLocationOptions = TgBot.Types.TTgEditMessageLiveLocationOptions;
  /// <summary>Необязательные параметры stopMessageLiveLocation.</summary>
  TTgStopMessageLiveLocationOptions = TgBot.Types.TTgStopMessageLiveLocationOptions;
  /// <summary>Необязательные параметры editMessageChecklist.</summary>
  TTgEditMessageChecklistOptions = TgBot.Types.TTgEditMessageChecklistOptions;
  /// <summary>Необязательные параметры editMessageReplyMarkup.</summary>
  TTgEditMessageReplyMarkupOptions = TgBot.Types.TTgEditMessageReplyMarkupOptions;
  /// <summary>Необязательные параметры stopPoll.</summary>
  TTgStopPollOptions = TgBot.Types.TTgStopPollOptions;
  /// <summary>Необязательные параметры editEphemeralMessageText.</summary>
  TTgEditEphemeralMessageTextOptions = TgBot.Types.TTgEditEphemeralMessageTextOptions;
  /// <summary>Необязательные параметры editEphemeralMessageMedia.</summary>
  TTgEditEphemeralMessageMediaOptions = TgBot.Types.TTgEditEphemeralMessageMediaOptions;
  /// <summary>Необязательные параметры editEphemeralMessageCaption.</summary>
  TTgEditEphemeralMessageCaptionOptions = TgBot.Types.TTgEditEphemeralMessageCaptionOptions;
  /// <summary>Необязательные параметры editEphemeralMessageReplyMarkup.</summary>
  TTgEditEphemeralMessageReplyMarkupOptions = TgBot.Types.TTgEditEphemeralMessageReplyMarkupOptions;
  /// <summary>Необязательные параметры approveSuggestedPost.</summary>
  TTgApproveSuggestedPostOptions = TgBot.Types.TTgApproveSuggestedPostOptions;
  /// <summary>Необязательные параметры declineSuggestedPost.</summary>
  TTgDeclineSuggestedPostOptions = TgBot.Types.TTgDeclineSuggestedPostOptions;
  /// <summary>Необязательные параметры deleteMessageReaction.</summary>
  TTgDeleteMessageReactionOptions = TgBot.Types.TTgDeleteMessageReactionOptions;
  /// <summary>Необязательные параметры deleteAllMessageReactions.</summary>
  TTgDeleteAllMessageReactionsOptions = TgBot.Types.TTgDeleteAllMessageReactionsOptions;
  /// <summary>Необязательные параметры sendSticker.</summary>
  TTgSendStickerOptions = TgBot.Types.TTgSendStickerOptions;
  /// <summary>Необязательные параметры createNewStickerSet.</summary>
  TTgCreateNewStickerSetOptions = TgBot.Types.TTgCreateNewStickerSetOptions;
  /// <summary>Необязательные параметры setStickerKeywords.</summary>
  TTgSetStickerKeywordsOptions = TgBot.Types.TTgSetStickerKeywordsOptions;
  /// <summary>Необязательные параметры setStickerMaskPosition.</summary>
  TTgSetStickerMaskPositionOptions = TgBot.Types.TTgSetStickerMaskPositionOptions;
  /// <summary>Необязательные параметры setStickerSetThumbnail.</summary>
  TTgSetStickerSetThumbnailOptions = TgBot.Types.TTgSetStickerSetThumbnailOptions;
  /// <summary>Необязательные параметры setCustomEmojiStickerSetThumbnail.</summary>
  TTgSetCustomEmojiStickerSetThumbnailOptions = TgBot.Types.TTgSetCustomEmojiStickerSetThumbnailOptions;
  /// <summary>Необязательные параметры sendRichMessage.</summary>
  TTgSendRichMessageOptions = TgBot.Types.TTgSendRichMessageOptions;
  /// <summary>Необязательные параметры sendRichMessageDraft.</summary>
  TTgSendRichMessageDraftOptions = TgBot.Types.TTgSendRichMessageDraftOptions;
  /// <summary>Необязательные параметры answerInlineQuery.</summary>
  TTgAnswerInlineQueryOptions = TgBot.Types.TTgAnswerInlineQueryOptions;
  /// <summary>Необязательные параметры sendInvoice.</summary>
  TTgSendInvoiceOptions = TgBot.Types.TTgSendInvoiceOptions;
  /// <summary>Необязательные параметры createInvoiceLink.</summary>
  TTgCreateInvoiceLinkOptions = TgBot.Types.TTgCreateInvoiceLinkOptions;
  /// <summary>Необязательные параметры answerShippingQuery.</summary>
  TTgAnswerShippingQueryOptions = TgBot.Types.TTgAnswerShippingQueryOptions;
  /// <summary>Необязательные параметры answerPreCheckoutQuery.</summary>
  TTgAnswerPreCheckoutQueryOptions = TgBot.Types.TTgAnswerPreCheckoutQueryOptions;
  /// <summary>Необязательные параметры getStarTransactions.</summary>
  TTgGetStarTransactionsOptions = TgBot.Types.TTgGetStarTransactionsOptions;
  /// <summary>Необязательные параметры sendGame.</summary>
  TTgSendGameOptions = TgBot.Types.TTgSendGameOptions;
  /// <summary>Необязательные параметры setGameScore.</summary>
  TTgSetGameScoreOptions = TgBot.Types.TTgSetGameScoreOptions;
  /// <summary>Необязательные параметры getGameHighScores.</summary>
  TTgGetGameHighScoresOptions = TgBot.Types.TTgGetGameHighScoresOptions;

  { Клиент Bot API }

  /// <summary>
  ///   Клиент Telegram Bot API: для каждого метода синхронный вызов, Try* и *Async (описание —
  ///   TgBot.Types.TTgApi).
  /// </summary>
  TTgApi = TgBot.Types.TTgApi;
