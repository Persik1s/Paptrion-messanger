package service

import (
	"stor/pkg/domain"
	"stor/pkg/repository"
)

type CloudeInterface interface {
	NewDir(data domain.DirData) bool
	NewFile(data domain.FileData) bool

	WriteFile(data domain.WriteData) bool
	ReadFile(data domain.FileData) repository.ResponeData

	DeleteFile(data domain.FileData) bool
	DeleteDir(data domain.DirData) bool

	IsFile(data domain.FileData) bool
	IsDir(data domain.DirData) bool

	DirNameAll(path string) []string
	FileNameAll(path string) []string
}

type Service struct {
	CloudeInterface
	Cloude *repository.Cloude
}

func NewService(cloude *repository.Cloude) *Service {
	return &Service{Cloude: cloude}
}

func (s *Service) NewFile(data domain.FileData) bool {
	return s.Cloude.NewFile(data)
}

func (s *Service) NewDir(data domain.DirData) bool {
	return s.Cloude.NewDir(data)
}

func (s *Service) WriteFile(data domain.WriteData) bool {
	return s.Cloude.WriteFile(data)
}

func (s *Service) ReadFile(data domain.FileData) repository.ResponeData {
	return s.Cloude.ReadFile(data)
}

func (s *Service) DeleteFile(data domain.FileData) bool {
	return s.Cloude.DeleteFile(data)
}

func (s *Service) DeleteDir(data domain.DirData) bool {
	return s.Cloude.DeleteDir(data)
}

func (s *Service) IsFile(data domain.FileData) bool {
	return s.Cloude.IsFile(data)
}

func (s *Service) IsDir(data domain.DirData) bool {
	return s.Cloude.IsDir(data)
}

func (s *Service) FileNameAll(path string) []string {
	return s.Cloude.FileNameAll(path)
}

func (s *Service) DirNameAll(path string) []string {
	return s.Cloude.DirNameAll(path)
}
