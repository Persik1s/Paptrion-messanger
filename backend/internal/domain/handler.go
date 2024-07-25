package domain

import "net/http"

type HandlerFunction struct {
	Func        func(w http.ResponseWriter, r *http.Request)
	NameHandler string
}
