package domain

type AccountData struct {
	Password string `json:"password"`
	Login    string `json:"login"`
}

type AccountInfo struct {
	User  Member      `json:"user"`
	Data  AccountData `json:"data"`
	Ip    string      `json:"ip"`
	Email string      `json:"email"`
}
