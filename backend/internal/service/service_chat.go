package service

import (
	"app/internal/domain"
	"app/pkg/database"
	"encoding/json"
	"fmt"
	"io/ioutil"
	"os"
	"strconv"
)

type ChatService struct{}

func (b *ChatService) SendMessage(data domain.EventMessage) (bool, error) {
	recipient, err := database.Db.Select("Login", "Username", data.Recipient.Username)
	if err != nil {
		return false, domain.ERROR_ACCONUT_NOT_FOUND
	}
	author, err1 := database.Db.Select("Login", "Username", data.Author.Username)

	if err1 != nil {
		return false, domain.ERROR_ACCONUT_NOT_FOUND
	}

	_, err = os.Stat("../../../TestObejectStorge/" + author + "/chats/" + recipient)
	if os.IsNotExist(err) {
		os.Mkdir("../../../TestObejectStorge/"+author+"/chats/"+recipient, os.ModeDir)
		os.Create("../../../TestObejectStorge/" + author + "/chats/" + recipient + "/message.json")
	}
	_, err = os.Stat("../../../TestObejectStorge/" + recipient + "/chats/" + author)
	if os.IsNotExist(err) {
		os.Mkdir("../../../TestObejectStorge/"+recipient+"/chats/"+author, os.ModeDir)
		os.Create("../../../TestObejectStorge/" + recipient + "/chats/" + author + "/message.json")

	}
	bytes, _ := json.Marshal(data)
	os.WriteFile("../../../TestObejectStorge/"+recipient+"/chats/"+author+"/message.json", bytes, 0666)
	os.WriteFile("../../../TestObejectStorge/"+author+"/chats/"+recipient+"/message.json", bytes, 0666)

	return true, nil
}

func (b *ChatService) GetListChat(data domain.EventListChat) ([]domain.User, error) {
	fmt.Println(data)
	login, err := database.Db.Select("Login", "Username", data.Profile.Username)
	if err != nil {
		return []domain.User{}, domain.ERROR_ACCONUT_NOT_FOUND
	}
	list_files, err := ioutil.ReadDir("../../../TestObejectStorge/" + login + "/chats")
	if err != nil {
		return []domain.User{}, domain.ERROR_USER_NOT_FOUND_CHAT
	}
	mass_member := make([]domain.User, 0, 10)
	for i := range list_files {
		if list_files[i].IsDir() {

			name := list_files[i].Name()
			name_str, _ := database.Db.Select("Name", "Login", name)
			surname_str, _ := database.Db.Select("Surname", "Login", name)
			username_str, _ := database.Db.Select("Username", "Login", name)
			age_str, _ := database.Db.Select("Age", "Login", name)
			age, _ := strconv.Atoi(age_str)

			user := domain.User{
				Name:     name_str,
				Surname:  surname_str,
				Username: username_str,
				Age:      age,
			}
			mass_member = append(mass_member, user)
		}
	}
	return mass_member, nil
}
