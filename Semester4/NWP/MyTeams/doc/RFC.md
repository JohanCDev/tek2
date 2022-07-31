# RFC

# Summary

Communication protocol for the MyTeams 💼 project 🚸

## General Information

`MAX_NAME_LENGTH` 32

`MAX_DESCRIPTION_LENGTH` 255

`MAX_BODY_LENGTH` 512

---

# Packets

Packets are identified by a common header made of:

- A [ULEB128](https://en.wikipedia.org/wiki/LEB128) encoded 32-bit type identifier, each packet type gets it's own id.binary buffer to string in c
- The size of the payload (not including this header), encoded as a [ULEB128](https://en.wikipedia.org/wiki/LEB128) 32-bit unsigned integer.

## Data Types

- `TYPE[LENGTH]` : sequence of exact size LENGTH of TYPE (e.g. Byte[16] is a sequence of 16 bytes)
- `TYPE[MIN : MAX]` : arbitrary sequence of length between MIN (inclusive) and MAX (inclusive) of elements of type TYPE.
- `{ name1: TYPE_1, name2: TYPE_2, ... }` : tuple. (e.g. `{ id: UUID, length: U32, name: Byte[length]}`)
- `U32` : a [ULEB128](https://en.wikipedia.org/wiki/LEB128) encoded 32-bit unsigned integer.
- `U64` : a [ULEB128](https://en.wikipedia.org/wiki/LEB128) encoded 64-bit unsigned integer.
- `Byte` : a byte.
- `UUID`  : a RFC-4122 compliant Universally Unique Identifier, encoded as 16 bytes. Same representation as `Byte[16]`
- `Timestamp`: seconds since the UNIX epoch, encoded as `U64`
- `Context`: encoded as `U32`, the valid values are:
    - 0: no context
    - 1: the user is inside a team
    - 2: the user is inside a channel
    - 3: the user is inside a thread

## Client to Server Packets

| Packet Id | Packet Name | Response Packet |
| --- | --- | --- |
| 0 | C2S_LOGIN | S2C_GENERIC, S2C_LOGIN |
| 1 | C2S_LOGOUT | S2C_GENERIC, S2C_LOGOUT |
| 2 | C2S_GET_USERS | S2C_GENERIC, S2C_USER_LIST |
| 3 | C2S_GET_USER_INFO | S2C_GENERIC, S2C_USER_INFO |
| 4 | C2S_SEND_MESSAGE | S2C_GENERIC, S2C_MESSAGE_CREATED |
| 5 | C2S_GET_MESSAGES | S2C_GENERIC, S2C_MESSAGE_LIST |
| 6 | C2S_SUBSCRIBE_TEAM | S2C_GENERIC, S2C_SUBSCRIBED |
| 7 | C2S_GET_SUBSCRIBED_TEAMS | S2C_GENERIC, S2C_TEAM_LIST |
| 8 | C2S_GET_TEAM_USERS | S2C_GENERIC, S2C_USER_LIST |
| 9 | C2S_UNSUBSCRIBE_TEAM | S2C_GENERIC, S2C_UNSUBSCRIBED |
| 10 | C2S_CREATE_ITEM | S2C_GENERIC, S2C_TEAM_CREATED, S2C_CHANNEL_CREATED, S2C_THREAD_CREATED, S2C_COMMENT_CREATED |
| 11 | C2S_GET_TEAMS | S2C_GENERIC, S2C_TEAM_LIST |
| 12 | C2S_GET_CHANNELS | S2C_GENERIC, S2C_CHANNEL_LIST |
| 13 | C2S_GET_THREADS | S2C_GENERIC, S2C_THREAD_LIST |
| 14 | C2S_GET_COMMENTS | S2C_GENERIC, S2C_COMMENT_LIST |
| 15 | C2S_GET_TEAM_INFO | S2C_GENERIC, S2C_TEAM_INFO |
| 16 | C2S_GET_CHANNEL_INFO | S2C_GENERIC, S2C_CHANNEL_INFO |
| 17 | C2S_GET_THREAD_INFO | S2C_GENERIC, S2C_THREAD_INFO |
| 18 | C2S_SET_CONTEXT | S2C_GENERIC, S2C_CONTEXT_UPDATE |

### C2S_CREATE_ITEM

Description: create a new Team, channel, thread, or comment.

Its description has either a maximum of `MAX_DESCRIPTION_LENGTH` (for the teams and channels) or a `MAX_BODY_LENGTH` (for the threads and comments).

Replied by: **S2C_GENERIC**, **S2C_TEAM_CREATED**, **S2C_CHANNEL_CREATED**, **S2C_THREAD_CREATED**, **S2C_COMMENT_CREATED**.

Format:

- type: `U32` = 10

- length: `U32`

- context_id: `UUID`

- name_length: `U32`

- name: `Byte[1 : MAX_NAME_LENGTH]`

- body: `Byte[1 : MAX_DESCRIPTION_LENGTH or MAX_BODY_LENGTH]`

- Where:

- - contextID is set to null UUID if there is no context

### C2S_GET_CHANNELS

Description: get the list of all channel names and ids of a team.

Replied by: **S2C_GENERIC**, **S2C_CHANNEL_LIST**

Format:

- type: `U32` = 12

- length: `U32`

- team: `UUID`

### C2S_GET_CHANNEL_INFO

Description: get information about a specific channel, such as the author, name, or description.

Replied by: **S2C_GENERIC**, **S2C_CHANNEL_INFO**

Format:

- type: `U32` = 16

- length: `U32`

- team: `UUID`

- channel: `UUID`

### C2S_GET_COMMENTS

Description: get the list of all comments of a thread.

Replied by: **S2C_GENERIC**, **S2C_COMMENT_LIST**

Format:

- type: `U32` = 14

- length: `U32`

- team: `UUID`

- channel: `UUID`

- channel: `UUID`

- thread: `UUID`

### C2S_GET_MESSAGES

Description: get the list of all private messages with a user.

Replied by: **S2C_GENERIC**, **S2C_MESSAGE_LIST**

Format:

- type: `U32` = 5

- length: `U32`

- user: `UUID`

### C2S_GET_SUBSCRIBED_TEAMS

Description: get the list of all team names and ids the current user is subscribed to.

Replied by: **S2C_GENERIC**, **S2C_TEAM_LIST**

Format:

- type: `U32` = 7

- length: `U32` = 0

### C2S_GET_TEAMS

Description: get the list of all team name and ids of the server.

Replied by: **S2C_GENERIC**, **S2C_TEAM_LIST**

Format:

- type: `U32` = 11

- length: `U32` = 0

### C2S_GET_TEAM_INFO

Description: get information about a specific team

Replied by: **S2C_GENERIC**, **S2C_TEAM_INFO**

Format:

- type: `U32` = 15

- length: `U32`

- team: `UUID`

### C2S_GET_TEAM_USERS

Replied by: **S2C_GENERIC**, **S2C_USER_LIST**

Format:

- type: `U32` = 8

- length: `U32`

- team: `UUID`

### C2S_GET_THREADS

Replied by: **S2C_GENERIC**, **S2C_THREAD_LIST**

Format:

- type: `U32` = 13

- length: `U32`

- team: `UUID`

- channel: `UUID`

### C2S_GET_THREAD_INFO

Replied by: **S2C_GENERIC**, **S2C_THREAD_INFO**

Format:

- type: `U32` = 17

- length: `U32`

- team: `UUID`

- channel: `UUID`

- thread: `UUID`

### C2S_GET_USER_INFO

Replied by: **S2C_GENERIC**, **S2C_USER_INFO**

Format:

- type: `U32` = 3

- length: `U32`

- user: `UUID`

### C2S_GET_USERS

Replied by: **S2C_GENERIC**, **S2C_USER_LIST**

Format:

- type: `U32` = 2

- length: `U32` = 0

### C2S_LOGIN

Replied by: **S2C_GENERIC**, **S2C_LOGIN**

Format:

- type: `U32` = 0

- length: `U32`

- name: `Byte[1 : MAX_NAME_LENGTH]`

### C2S_LOGOUT

Replied by: **S2C_GENERIC**

Format:

- type: `U32` = 1

- length: `U32`

### C2S_SEND_MESSAGE

Replied by: **S2C_GENERIC**, **S2C_MESSAGE_CREATED**

Format:

- type: `U32` = 4

- length: `U32`

- user: `UUID`

- message_body: `Byte[1 : MAX_BODY_LENGTH]`

### C2S_SUBSCRIBE_TEAM

Replied by: **S2C_GENERIC, S2C_SUBSCRIBED**

Format:

- type: `U32` = 6

- length: `U32` = 16

- team: `UUID`

### C2S_UNSUBSCRIBE_TEAM

Replied by: **S2C_GENERIC**, **S2C_UNSUBSCRIBED**

Format:

- type: `U32` = 9

- length: `U32` = 16

- team: `UUID`

### C2S_SET_CONTEXT

Replied by: **S2C_GENERIC**, **S2C_UNSUBSCRIBED**

Format:

- type: `U32` = 18

- length: `U32` = 0, 16, 24, or 32

- part_1: `UUID`

- part_2: `UUID`

- part_3: `UUID`

## Server to Client Packets

Each action that the client request (logging in, sending a message, ...) is *always* followed by a response from the server,
response packet are encoded as follows:

- The common packet header
- A HTTP-like status code (to be defined), encoded in ULEB128.

| Packet Id | Packet Name | Request Packet |
| --- | --- | --- |
| 0 | S2C_GENERIC | All packets |
| 1 | S2C_LOGIN | C2S_LOGIN |
| 2 | S2C_LOGOUT | C2S_LOGOUT |
| 3 | S2C_USER_LIST | C2S_GET_USERS, C2S_GET_TEAM_USERS |
| 4 | S2C_USER_INFO | C2S_GET_USER_INFO |
| 5 | S2C_MESSAGE_LIST | C2S_GET_MESSAGES |
| 6 | S2C_TEAM_LIST | C2S_GET_TEAMS, C2S_GET_SUBSCRIBED_TEAMS |
| 7 | S2C_CHANNEL_LIST | C2S_GET_CHANNELS |
| 8 | S2C_THREAD_LIST | C2S_GET_THREADS |
| 9 | S2C_COMMENT_LIST | C2S_GET_COMMENTS |
| 10 | S2C_TEAM_INFO | C2S_GET_TEAM_INFO |
| 11 | S2C_CHANNEL_INFO | C2S_GET_CHANNEL_INFO |
| 12 | S2C_THREAD_INFO | C2S_GET_THREAD_INFO |
| 13 | S2C_MESSAGE_CREATED | C2S_SEND_MESSAGE |
| 14 | S2C_TEAM_CREATED | C2S_CREATE_ITEM |
| 15 | S2C_CHANNEL_CREATED | C2S_CREATE_ITEM |
| 16 | S2C_THREAD_CREATED | C2S_CREATE_ITEM |
| 17 | S2C_COMMENT_CREATED | C2S_CREATE_ITEM |
| 18 | S2C_SUBSCRIBED | C2S_SUBSCRIBE_TEAM |
| 19 | S2C_UNSUBSCRIBED | C2S_UNSUBSCRIBE_TEAM |
| 20 | S2C_UNKNOWN_ITEM | C2S_CREATE_ITEM |
| 21 | S2C_CONTEXT_UPDATE | C2S_SET_CONTEXT |

### S2C_GENERIC

Triggered by: all client packets.

Format:

- type: `U32` = 0

- length: `U32`

- code: `ReplyCode`

- description: `Byte[0 : MAX_BODY_LENGTH]`

### S2C_LOGIN

Triggered by: **C2S_LOGIN,** and when any users logs in.

Format:

- type: `U32` = 1

- length: `U32`

- id: `UUID`

- name: `Byte[0 : MAX_NAME_LENGTH]`

### S2C_LOGOUT

Triggered by: **C2S_LOGOUT,** and when any users logs out.

Format:

- type: `U32` = 2

- length: `U32`

- id: `UUID`

- name: `Byte[0 : MAX_NAME_LENGTH]`

### S2C_USER_LIST

Triggered by: **C2S_GET_USERS, C2S_GET_TEAM_USERS**.

Format:

- type: `U32` = 3

- length: `U32`

- count: `U32`

- users: `{ id: UUID, name_length: U32, name: Byte[name_length], status: U32 }[count]`

### S2C_USER_INFO

Triggered by: **C2S_GET_USER_INFO.**

Format:

- type: `U32` = 4

- length: `U32`

- user_id: `UUID`

- creation_date: `Timestamp`

- status: `U32`

- name: `Byte[1 : MAX_NAME_LENGTH]`

- Where:

- - status is either the values 0 (not logged) or 1 (logged).

### S2C_MESSAGE_LIST

Triggered by: **C2S_GET_MESSAGES**.

Format:

- type: `U32` = 5

- length: `U32`

- count: `U32`

- messages: `{ author: UUID, creation_date: U64, body_length: U32, body: Byte[body_length] }[count]`

- Where:

- - messages[i].body_length is between 1 and MAX_BODY_LENGTH (inclusive), where i is an index.

### S2C_TEAM_LIST

Triggered by: **C2S_GET_TEAMS.**

Format:

- type: `U32` = 6

- length: `U32`

- count: `U32`

- teams: `{ id: UUID, name_length: U32, name: Byte[name_length], desc_length: U32, desc: Byte[desc_length] }[count]`

- Where:

- - teams[i].name_length is between 1 and MAX_NAME_LENGTH (inclusive), where i is an index.

- - teams[i].desc_length is between 1 and MAX_DESCRIPTION_LENGTH (inclusive), where i is an index.

### S2C_CHANNEL_LIST

Triggered by: **C2S_GET_CHANNELS**

Format:

- type: `U32` = 7

- length: `U32`

- count: `U32`

- channels: `{ id: UUID, name_length: U32, name: Byte[name_length], desc_length: U32, desc: Byte[desc_length] }[count]`

- Where:

- - channels[i].name_length is between 1 and MAX_NAME_LENGTH (inclusive), where i is an index.

- - channels[i].desc_length is between 1 and MAX_DESCRIPTION_LENGTH (inclusive), where i is an index.

### S2C_THREAD_LIST

Triggered by: **C2S_GET_THREADS**

Format:

- type: `U32` = 8

- length: `U32`

- count: `U32`

- threads: `{ id: UUID, creation_date: Timestamp, author: UUID, title_length: U32, title: Byte[title_length], body_length: U32, body: Byte[body_length] }[count]`

- Where:

- - threads[i].title_length is between 1 and MAX_NAME_LENGTH (inclusive), where i is an index.

- - threads[i].body_length is between 1 and MAX_BODY_LENGTH (inclusive), where i is an index.

### S2C_COMMENT_LIST

Triggered by: **C2S_GET_COMMENTS**

Format:

- type: `U32` = 9

- length: `U32`

- thread_id: `UUID`

- count: `U32`

- comments: `{ id: UUID, creation_date: Timestamp, author: UUID, body_length: U32, body: Byte[body_length] }[count]`

- Where:

- - comments[i].body_length is between 1 and MAX_BODY_LENGTH (inclusive), where i is an index.

### S2C_TEAM_INFO

Triggered by: **C2S_GET_TEAM_INFO**

Format:

- type: `U32` = 10

- length: `U32`

- id: `UUID`

- creation_date: `Timestamp`

- author: `UUID`

- name_length: `U32`

- name: `Byte[name_length]`

- description: `Byte[1 : MAX_DESCRIPTION_LENGTH]`

- Where:

- - name_length is between 1 and MAX_NAME_LENGTH (inclusive).

### S2C_CHANNEL_INFO

Triggered by: **C2S_GET_CHANNEL_INFO**

Format:

- type: `U32` = 11

- length: `U32`

- id: `UUID`

- creation_date: `Timestamp`

- author: `UUID`

- name_length: `U32`

- name: `Byte[name_length]`

- description: `Byte[1 : MAX_DESCRIPTION_LENGTH]`

- Where:

- - name_length is between 1 and MAX_NAME_LENGTH (inclusive).

### S2C_THREAD_INFO

Triggered by: **C2S_GET_THREAD_INFO**

Format:

- type: `U32` = 12

- length: `U32`

- creation_date: `Timestamp`

- author: `UUID`

- name: `Byte[1 : MAX_NAME_LENGTH]`

### S2C_MESSAGE_CREATED

Triggered by: **C2S_SEND_MESSAGE**, and when the client receives a message.

Format:

- type: `U32` = 13

- length: `U32`

- creation_date: `Timestamp`

- creator_id: `UUID`

- recipient_id: `UUID`

- body: `Byte[1 : MAX_BODY_LENGTH]`

### S2C_TEAM_CREATED

Triggered by: **C2S_CREATE_ITEM**, and when a team is created

Format:

- type: `U32` = 14

- length: `U32`

- creation_date: `Timestamp`

- creator_id: `UUID`

- id: `UUID`

- name_length: `U32`

- name: `Byte[name_length]`

- description: `Byte[1 : MAX_DESCRIPTION_LENGTH]`

- Where:

- - `name_length` is between 1 and MAX_NAME_LENGTH

### S2C_CHANNEL_CREATED

Triggered by: **C2S_CREATE_ITEM**, and when a channel is created in a team the user is subscribed to.

Format:

- type: `U32` = 15

- length: `U32`

- creation_date: `Timestamp`

- creator_id: `UUID`

- team_id:`UUID`

- channel_id: `UUID`

- name_length: `U32`

- name: `Byte[name_length]`

- description: `Byte[1 : MAX_DESCRIPTION_LENGTH]`

- Where:

- - `name_length` is between 1 and MAX_NAME_LENGTH

### S2C_THREAD_CREATED

Triggered by: **C2S_CREATE_ITEM**, and when a thread is created in a team the user is subscribed to.

Format:

- type: `U32` = 16

- length: `U32`

- creation_date: `Timestamp`

- creator_id: `UUID`

- team_id:`UUID`

- channel_id: `UUID`

- thread_id: `UUID`

- title_length: `UUID`

- title: `Byte[title_length]`

- body: `Byte[1 : MAX_BODY_LENGTH]`

- Where:

- - `name_length` is between 1 and MAX_TITLE_LENGTH

### S2C_COMMENT_CREATED

Triggered by: **C2S_CREATE_ITEM**, and when a reply is created in a team the user is subscribed to.

Format:

- type: `U32` = 17

- length: `U32`

- creation_date: `Timestamp`

- creator_id: `UUID`

- team_id:`UUID`

- channel_id: `UUID`

- thread_id: `UUID`

- comment_id: `UUID`

- body: `Byte[1 : MAX_BODY_LENGTH]`

### S2C_SUBSCRIBED

Triggered by: **C2S_SUBSCRIBE_TEAM**

Format:

- type: `U32` = 18

- length: `U32` = 16

- id: `UUID`

### S2C_UNSUBSCRIBED

Triggered by: **C2S_UNSUBSCRIBE_TEAM**

Format:

- type: `U32` = 19

- length: `U32` = 16

- id: `UUID`

### S2C_UNKNOWN_ITEM

Triggered by: **C2S_CREATE_ITEM**

Format:

- type: `U32` = 20

- length: `U32` = 16

- item_type: `U32`

- id: `UUID`

### S2C_CONTEXT_UPDATE

Triggered by: **C2S_SET_CONTEXT**

Format:

- type: `U32` = 21

- length: `U32`

- context: `Context`

- id: `UUID`