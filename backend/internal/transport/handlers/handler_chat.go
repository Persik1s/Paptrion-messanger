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
	ser_chat service.ChatService
)

func HandlerChat(w http.ResponseWriter, r *http.Request) {
	var (
		event domain.Event
	)

	body, _ := ioutil.ReadAll(r.Body)
	json.Unmarshal(body, &event)

	switch r.Method {
	case http.MethodPost:
		{
			switch event.Event {
			case "EVENT_SEND_MESSAGE":
				{
					var (
						data domain.EventMessage
					)
					json.Unmarshal(body, &data)
					fmt.Println(ser_chat.SendMessage(data))
				}
			}

		}
	case http.MethodGet:
		{
			switch event.Event {
			case "EVENT_GET_LIST_CHAT":
				{

					var (
						data domain.EventListChat
					)
					json.Unmarshal(body, &data)
					fmt.Println(ser_chat.GetListChat(data))

				}
			}
		}
	}
}
