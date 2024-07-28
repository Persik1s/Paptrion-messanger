package domain

type Event struct {
	Event string `json:"Event"`
}

type EventListChat struct {
	Event   Event
	Profile User `json:"Profile"`
}

type EventMessage struct {
	Event     Event
	Recipient User
	Author    User
}

type EventSignInAccount struct {
	Event Event
	Data  AccountData
}

type EventSignUpAccount struct {
	Event    Event
	DataUser User
	Data     AccountData
}
