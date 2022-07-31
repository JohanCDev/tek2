# Data Architecture

# Summary

Data saving design for MyTeams project

# Data Structure Design

## Teams

**As a single file at the root of data/**

```json
“teams”: [

    {

        “id”: string,

        “creator”: string,

        “creationDate”: string,

        “channels”: [

            “id”: string,

        ]

    }

]
```

## Channels

**As many files called** *`channel-UUID*.json` **at the root of data/channels/**

```json

“channels”: [

    {

        “id”: string,

        “creator”: string,

        “creationDate”: string,

        “threads”: [

            “id”: string,

        ]

    }

]
```

## Threads

**As many files called** *`thread-UUID*.json` **at the root of data/threads/**

```json

“threads”: [

    {

        “id”: string,

        “creator”: string,

        “creationDate”: string,

        “replies”: [

            “id”: string,

        ]

    }

]
```

## Replies

**As many files called** *`replies-UUID*.json` **at the root of data/replies**

```json
“replies”: [

    {

        “id”: string,

        “creator”: string,

        “creationDate”: string,

        “body”: string

    }

]
```

## Users

**As a single file called** `users.json` **at the root of data/**

```json
“users”: [

    {

        “id”: string,

        “lastConnection”: string,

    }

]
```

## Messages

**As many files called** *`userAUUID-userBUUID*.json` **at the root of data/messages/**

```json
“messages”: [

    {

        “creator”: string,

        “creationDate”: string,

        “body”: string,

    }

]
```
