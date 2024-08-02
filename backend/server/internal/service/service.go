package service

import (
	"app/internal/domain"
	"app/internal/repository"
	"app/pkg/cloude"
	"encoding/json"
)

type Auth interface {
	SignIn(data domain.AccountData) (domain.Member, domain.Error)
	SignUp(data domain.AccountInfo) domain.Error

	GetListMessage(data domain.MessageList) []domain.MessageData
}

type Service struct {
	Auth
	Repo *repository.Repository
}

func NewService(repo *repository.Repository) *Service {
	return &Service{Repo: repo}
}
func (s Service) SignIn(data domain.AccountData) (domain.Member, domain.Error) {
	return s.Repo.SignIn(data)
}
func (s Service) SignUp(data domain.AccountInfo) domain.Error {
	return s.Repo.SignUp(data)
}

func (s *Service) GetListChat(data domain.AccountData) []domain.Member {
	dirs := s.Repo.Cloude.DirNameAll(cloude.Location{Path: "usr/" + data.Login + "/Chats/"})
	member_mass := make([]domain.Member, 0, 1)
	for i := range dirs {
		member_mass = append(member_mass, s.Repo.GetMemberData(dirs[i]))
	}
	return member_mass
}

func (s *Service) SendMessage(data domain.MessageData) domain.Error {
	if !s.Repo.IsLoginForUsername(data.Author.Username) {
		return domain.Error{
			Error: domain.ERROR_MEMBER_NOT_FOUND.Error(),
		}
	}

	if !s.Repo.IsLoginForUsername(data.Recipient.Username) {
		return domain.Error{
			Error: domain.ERROR_MEMBER_NOT_FOUND.Error(),
		}
	}
	byte_data, _ := json.Marshal(data)
	login_author, err := s.Repo.GetLogin(data.Author)
	if err.Objcet != nil {
		return err
	}

	login_recipient, err := s.Repo.GetLogin(data.Recipient)
	if err.Objcet != nil {
		return err
	}

	if !s.Repo.Cloude.IsDir(cloude.DirData{
		Name: login_recipient,
		Path: "usr/" + login_author + "/Chats/",
	}) {

		s.Repo.Cloude.CreateDir(cloude.DirData{
			Name: login_recipient,
			Path: "usr/" + login_author + "/Chats/"})

		s.Repo.Cloude.CreateFile(cloude.FileData{
			Name:   "message",
			Format: "json",
			Path:   "usr/" + login_author + "/Chats/" + login_recipient + "/",
		})
	}

	if !s.Repo.Cloude.IsDir(cloude.DirData{
		Name: login_author,
		Path: "usr/" + login_recipient + "/Chats/",
	}) {

		s.Repo.Cloude.CreateDir(cloude.DirData{
			Name: login_author,
			Path: "usr/" + login_recipient + "/Chats/"})

		s.Repo.Cloude.CreateFile(cloude.FileData{
			Name:   "message",
			Format: "json",
			Path:   "usr/" + login_recipient + "/Chats/" + login_author + "/",
		})
	}

	s.Repo.Cloude.WriteFile(
		cloude.WriteData{
			File: cloude.FileData{
				Name:   "message",
				Format: "json",
				Path:   "usr/" + login_recipient + "/Chats/" + login_author + "/",
			},
			Data: string(byte_data),
		})

	s.Repo.Cloude.WriteFile(
		cloude.WriteData{
			File: cloude.FileData{
				Name:   "message",
				Format: "json",
				Path:   "usr/" + login_author + "/Chats/" + login_recipient + "/",
			},
			Data: string(byte_data),
		})

	return domain.Error{
		Error:  "Null",
		Objcet: nil,
	}
}

func (s *Service) GetListMessage(data domain.MessageList) []domain.MessageData {
	return s.Repo.GetListMessage(data)
}
