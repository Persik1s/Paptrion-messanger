package domain

type Member struct {
	Username string `json:"username"`
	Name     string `json:"name"`
	Surname  string `json:"surname"`
	Age      int    `json:"age"`
}

type MessageData struct {
	Author    Member `json:"author"`
	Recipient Member `json:"recipient"`
	Message   string `json:"message"`
}
