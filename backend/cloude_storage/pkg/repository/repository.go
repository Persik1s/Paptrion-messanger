package repository

import (
	"fmt"
	"os"
	"stor/pkg/domain"
)

// type CloudeInterface interface {
// 	Read(path string) []byte
// 	Write(path string, b []byte) error
// 	CreateFile(path string, filename string) error
// 	CreateDir(path string, namedir string) error
// }

type CloudeInterface interface {
	NewDir(data domain.DirData) bool
	NewFile(data domain.FileData) bool

	WriteFile(data domain.WriteData) bool
	ReadFile(data domain.FileData) []byte

	DeleteFile(data domain.FileData) bool
	DeleteDir(data domain.DirData) bool
}
type Cloude struct {
	CloudeInterface
	path string
}

func NewCloude(path string) *Cloude {
	return &Cloude{path: path}
}

func (c *Cloude) NewDir(data domain.DirData) bool {
	err := os.Mkdir(c.path+data.Path+data.Name, os.ModeDir)
	return err == nil
}

func (c *Cloude) NewFile(data domain.FileData) bool {
	_, err := os.Create(c.path + data.Path + "/" + data.Name + "." + data.Format)
	return err == nil
}

func (c *Cloude) WriteFile(data domain.WriteData) bool {
	file, err := os.OpenFile(c.path+data.File.Path+data.File.Name+"."+data.File.Format, os.O_APPEND|os.O_WRONLY, 0644)

	if err != nil {
		fmt.Errorf("%s", "%w", "pkg.repository.repository")
		return false
	}

	file.Write([]byte(data.Data))

	return true
}

func (c *Cloude) ReadFile(data domain.FileData) []byte {
	bytes, err := os.ReadFile(c.path + data.Path + data.Name + "." + data.Format)

	if err != nil {
		fmt.Errorf("%s", "%w", "pkg.repository.repository")
		return []byte{}
	}

	return bytes
}

func (c *Cloude) DeleteFile(data domain.FileData) bool {
	err := os.Remove(c.path + data.Path + data.Name + "." + data.Format)
	return err == nil
}

func (c *Cloude) DeleteDir(data domain.DirData) bool {
	err := os.Remove(c.path + data.Path + data.Name)
	return err == nil
}
