package service

import (
	"app/internal/domain"
	"app/pkg/database"
	"encoding/json"
	"os"
	"strconv"
)

type AcconutService struct{}

func (b *AcconutService) SignUpAccount(data domain.EventSignUpAccount) (bool, error) {
	_, err := database.Db.Select("Login", "Login", data.Data.Login)
	if err == nil {
		return false, domain.ERROR_ACCOUNT_ALREADY_EXISTS
	}
	os.Mkdir("../../../TestObejectStorge/"+data.Data.Login, os.ModeDir)
	os.Mkdir("../../../TestObejectStorge/"+data.Data.Login+"/profile", os.ModeDir)
	os.Mkdir("../../../TestObejectStorge/"+data.Data.Login+"/chats", os.ModeDir)
	os.Mkdir("../../../TestObejectStorge/"+data.Data.Login+"/files", os.ModeDir)

	os.Create("../../../TestObejectStorge/" + data.Data.Login + "/profile/profile.json")
	byte_data, _ := json.Marshal(data)
	os.WriteFile("../../../TestObejectStorge/"+data.Data.Login+"/profile/profile.json", byte_data, 0666)

	err = database.Db.Insert(
		"Username,Name,Surname,Age,Login,Password", "$1,$2,$3,$4,$5,$6",
		data.DataUser.Username, data.DataUser.Name, data.DataUser.Surname, data.DataUser.Age, data.Data.Login, data.Data.Password)

	return err == nil, err
}

func (b *AcconutService) SignInAccount(data domain.EventSignInAccount) (domain.User, error) {
	_, err := database.Db.Select("Login", "Login", data.Data.Login)
	if err != nil {
		return domain.User{}, domain.ERROR_ACCONUT_NOT_FOUND
	}
	password, _ := database.Db.Select("Password", "Login", data.Data.Login)
	if password != data.Data.Password {
		return domain.User{}, domain.ERROR_PASSWORD
	}

	name_str, _ := database.Db.Select("Name", "Login", data.Data.Login)
	surname_str, _ := database.Db.Select("Surname", "Login", data.Data.Login)
	username_str, _ := database.Db.Select("Username", "Login", data.Data.Login)
	age_str, _ := database.Db.Select("Age", "Login", data.Data.Login)
	age, _ := strconv.Atoi(age_str)

	user := domain.User{
		Name:     name_str,
		Surname:  surname_str,
		Username: username_str,
		Age:      age,
	}

	return user, nil
}
