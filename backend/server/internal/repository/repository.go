package repository

import (
	"app/internal/domain"
	"app/pkg/cloude"
	"app/pkg/storage"
	"encoding/json"
	"fmt"
	"io"
	"strconv"
	"strings"
)

type Auth interface {
	SignIn(data domain.AccountData) (domain.Member, domain.Error)
	SignUp(data domain.AccountInfo) domain.Error
	GetListMessage(data domain.MessageList) []domain.MessageData
}

type Repository struct {
	Auth

	Store  *storage.SqlBase
	Cloude *cloude.Cloude
}

func NewRepository(auth *storage.SqlBase, cloude *cloude.Cloude) *Repository {
	return &Repository{Store: auth, Cloude: cloude}
}
func (r Repository) SignIn(data domain.AccountData) (domain.Member, domain.Error) {

	if !r.IsLogin(data.Login) {
		return domain.Member{}, domain.Error{
			Error:  domain.ERROR_MEMBER_NOT_FOUND.Error(),
			Objcet: domain.ERROR_MEMBER_NOT_FOUND,
		}
	}
	if !r.IsPassword(data) {
		return domain.Member{}, domain.Error{
			Error:  domain.ERROR_BAD_PASSWORD.Error(),
			Objcet: domain.ERROR_BAD_PASSWORD,
		}
	}

	return r.GetMemberData(data.Login), domain.Error{
		Error:  "Null",
		Objcet: nil,
	}
}

func (r Repository) SignUp(data domain.AccountInfo) domain.Error {
	if r.IsLogin(data.Data.Login) {
		return domain.Error{
			Error:  domain.ERROR_ALREADY_EXISTS.Error(),
			Objcet: domain.ERROR_ALREADY_EXISTS,
		}
	}

	r.Cloude.CreateDir(cloude.DirData{
		Name: data.Data.Login,
		Path: "usr/",
	})
	r.Cloude.CreateDir(cloude.DirData{
		Name: "Profile",
		Path: "usr/" + data.Data.Login + "/",
	})

	r.Cloude.CreateFile(cloude.FileData{
		Name:   "Data",
		Format: "json",
		Path:   "usr/" + data.Data.Login + "/Profile/",
	})

	byte_data, _ := json.Marshal(data)
	r.Cloude.WriteFile(cloude.WriteData{
		File: cloude.FileData{
			Name:   "Data",
			Format: "json",
			Path:   "usr/" + data.Data.Login + "/Profile/",
		},
		Data: string(byte_data),
	})

	r.Cloude.CreateDir(cloude.DirData{
		Name: "Chats",
		Path: "usr/" + data.Data.Login + "/",
	})

	err := r.Store.Insert("Username,Name,Surname,Age,Password,Login,Email,Ip", "$1,$2,$3,$4,$5,$6,$7,$8", data.User.Username, data.User.Name, data.User.Surname, data.User.Age, data.Data.Password, data.Data.Login, data.Email, data.Ip)
	if err != nil {
		fmt.Println(err)
		return domain.Error{
			Error:  err.Error(),
			Objcet: err,
		}
	}

	return domain.Error{
		Error:  "Null",
		Objcet: nil,
	}

}

func (r *Repository) IsLogin(login string) bool {
	_, err := r.Store.Select("Login", "Login", login)
	return err == nil
}

func (r *Repository) IsPassword(data domain.AccountData) bool {
	password, _ := r.Store.Select("Password", "Login", data.Login)
	return password == data.Password
}

func (r *Repository) IsLoginForUsername(username string) bool {
	_, err := r.Store.Select("Login", "Username", username)
	return err == nil
}

func (r *Repository) GetLogin(data domain.Member) (string, domain.Error) {
	login, err := r.Store.Select("Login", "Username", data.Username)
	if err != nil {
		return "", domain.Error{
			Error:  err.Error(),
			Objcet: nil,
		}
	}
	return login, domain.Error{Objcet: nil}
}

func (r *Repository) GetMemberData(login string) domain.Member {
	age_str, err := r.Store.Select("Age", "Login", login)

	if err != nil {
		fmt.Println(domain.Error{Error: err.Error()})
		return domain.Member{}
	}

	age_int, _ := strconv.Atoi(age_str)
	name, _ := r.Store.Select("Name", "Login", login)
	surname, _ := r.Store.Select("Surname", "Login", login)
	username, _ := r.Store.Select("Username", "Login", login)
	return domain.Member{
		Name:     name,
		Surname:  surname,
		Age:      age_int,
		Username: username,
	}
}

func (r *Repository) GetListMessage(data domain.MessageList) []domain.MessageData {
	login_author, err := r.GetLogin(data.Author)
	if err.Objcet != nil {
		fmt.Println(err)
		return []domain.MessageData{}
	}
	login_recipient, err := r.GetLogin(data.Recipient)
	if err.Objcet != nil {
		fmt.Println(err)
		return []domain.MessageData{}
	}

	data_file, _ := r.Cloude.ReadFile(cloude.FileData{
		Name:   "message",
		Format: "json",
		Path:   "usr/" + login_author + "/Chats/" + login_recipient + "/",
	})
	var list []domain.MessageData

	decoder := json.NewDecoder(strings.NewReader(data_file))
	for {
		var message domain.MessageData
		err := decoder.Decode(&message)

		if err == io.EOF {
			break
		}
		if err != nil {
			return nil
		}

		list = append(list, message)
	}

	return list
}
