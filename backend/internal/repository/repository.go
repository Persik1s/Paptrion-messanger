package repository

import (
	"app/internal/domain"
	"app/pkg/storage"
	"fmt"
	"strconv"
)

type Auth interface {
	SignIn(data domain.AccountData) (domain.Member, error)
	SignUp(data domain.AccountInfo) error
}

type Repository struct {
	Auth

	Store *storage.SqlBase
}

func NewRepository(auth *storage.SqlBase) *Repository {
	return &Repository{Store: auth}
}
func (r Repository) SignIn(data domain.AccountData) (domain.Member, error) {

	if !r.IsLogin(data.Login) {
		return domain.Member{}, domain.ERROR_MEMBER_NOT_FOUND
	}
	if !r.IsPassword(data) {
		return domain.Member{}, domain.ERROR_BAD_PASSWORD
	}

	age_str, err := r.Store.Select("Age", "Login", data.Login)
	if err != nil {
		return domain.Member{}, fmt.Errorf("%s", "%w", "interlanl.repository.repository.age", err)
	}
	age_int, _ := strconv.Atoi(age_str)
	name, _ := r.Store.Select("Name", "Login", data.Login)
	surname, _ := r.Store.Select("Surname", "Login", data.Login)

	return domain.Member{
		Age:     age_int,
		Name:    name,
		Surname: surname,
	}, nil
}

func (r Repository) SignUp(data domain.AccountInfo) error {
	if r.IsLogin(data.Data.Login) {
		return domain.ERROR_ALREADY_EXISTS
	}

	err := r.Store.Insert("Name,Surname,Age,Password,Login,Email", "$1,$2,$3,$4,$5,$6", data.User.Name, data.User.Surname, data.User.Age, data.Data.Password, data.Data.Login, data.Email)
	if err != nil {
		return fmt.Errorf("%s", "%w", "interlanl.repository.repository", err)
	}

	return nil

}

func (r *Repository) IsLogin(login string) bool {
	_, err := r.Store.Select("Login", "Login", login)
	return err == nil
}

func (r *Repository) IsPassword(data domain.AccountData) bool {
	password, _ := r.Store.Select("Password", "Login", data.Login)
	return password == data.Password
}
