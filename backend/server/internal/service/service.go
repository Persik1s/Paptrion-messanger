package service

import (
	"app/internal/domain"
	"app/internal/repository"
)

type Auth interface {
	SignIn(data domain.AccountData) (domain.Member, error)
	SignUp(data domain.AccountInfo) error
}

type Service struct {
	Auth
	Repo *repository.Repository
}

func NewService(repo *repository.Repository) *Service {
	return &Service{Repo: repo}
}
func (s Service) SignIn(data domain.AccountData) (domain.Member, error) {
	return s.Repo.SignIn(data)
}
func (s Service) SignUp(data domain.AccountInfo) error {
	return s.Repo.SignUp(data)
}
