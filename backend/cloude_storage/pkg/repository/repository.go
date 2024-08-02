package repository

import (
	"fmt"
	"os"
	"stor/pkg/domain"
)

type CloudeInterface interface {
	NewDir(data domain.DirData) bool
	NewFile(data domain.FileData) bool

	WriteFile(data domain.WriteData) bool
	ReadFile(data domain.FileData) ResponeData

	DeleteFile(data domain.FileData) bool
	DeleteDir(data domain.DirData) bool

	IsFile(data domain.FileData) bool
	IsDir(data domain.DirData) bool

	DirNameAll(path string) []string
	FileNameAll(path string) []string
}
type Cloude struct {
	CloudeInterface
	path string
}
type ResponeData struct {
	Data     string   `json:"data"`
	DataMass []string `json:"data_mass"`
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
		file.Close()
		return false
	}

	file.Write([]byte(data.Data))
	file.Close()
	return true
}

func (c *Cloude) ReadFile(data domain.FileData) ResponeData {
	bytes, err := os.ReadFile(c.path + data.Path + data.Name + "." + data.Format)

	if err != nil {
		fmt.Errorf("%s", "%w", "pkg.repository.repository")
		return ResponeData{Data: "Null"}
	}

	return ResponeData{Data: string(bytes)}
}

func (c *Cloude) DeleteFile(data domain.FileData) bool {
	err := os.Remove(c.path + data.Path + data.Name + "." + data.Format)
	return err == nil
}

func (c *Cloude) DeleteDir(data domain.DirData) bool {
	err := os.Remove(c.path + data.Path + data.Name)
	return err == nil
}

func (c *Cloude) IsFile(data domain.FileData) bool {
	_, err := os.Stat(c.path + data.Path + data.Name + "." + data.Format)
	return !os.IsNotExist(err)
}

func (c *Cloude) IsDir(data domain.DirData) bool {
	files, _ := os.ReadDir(c.path + data.Path)
	for i := range files {
		if files[i].IsDir() && files[i].Name() == data.Name {
			return true
		}
	}
	return false
}

func (c *Cloude) DirNameAll(path string) []string {

	files, _ := os.ReadDir(c.path + path)
	mass_name := make([]string, 0, 1)
	for i := range files {
		if files[i].IsDir() {
			mass_name = append(mass_name, files[i].Name())
		}
	}
	return mass_name

}

func (c *Cloude) FileNameAll(path string) []string {

	files, _ := os.ReadDir(c.path + path)
	mass_name := make([]string, 0, 1)
	for i := range files {
		if files[i].IsDir() {
			continue
		}

		mass_name = append(mass_name, files[i].Name())
	}
	return mass_name

}
