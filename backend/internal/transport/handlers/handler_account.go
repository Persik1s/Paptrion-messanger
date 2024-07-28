package handlers

import (
	"app/internal/domain"
	"app/internal/service"

	"encoding/json"
	"fmt"
	"io/ioutil"
	"net/http"
)

var (
	ser service.AcconutService
)

func HandlerAccount(w http.ResponseWriter, r *http.Request) {
	switch r.Method {
	case http.MethodPost:
		{
			var (
				event domain.Event
			)
			body, _ := ioutil.ReadAll(r.Body)
			json.Unmarshal(body, &event)
			switch event.Event {
			case "EVENT_SIGNUP_ACCOUNT":
				var (
					data domain.EventSignUpAccount
				)
				json.Unmarshal(body, &data)
				fmt.Println(ser.SignUpAccount(data))

			}
		}
	case http.MethodGet:
		{
			var (
				event domain.Event
			)
			body, _ := ioutil.ReadAll(r.Body)
			json.Unmarshal(body, &event)
			switch event.Event {
			case "EVENT_SIGNIN_ACCOUNT":
				var (
					data domain.EventSignInAccount
				)
				json.Unmarshal(body, &data)
				fmt.Println(ser.SignInAccount(data))
			}
		}
	default:
		w.WriteHeader(http.StatusBadRequest)
	}
}
