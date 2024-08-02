package cloude

import (
	"app/internal/domain"
	"bytes"
	"encoding/json"
	"fmt"

	//"fmt"
	"net/http"
)

type FileData struct {
	Name   string `json:"name"`
	Format string `json:"format"`
	Path   string `json:"path"`
}
type DirData struct {
	Name string `json:"name"`
	Path string `json:"path"`
}

type WriteData struct {
	File FileData `json:"file"`
	Data string   `json:"data"`
}

type Cloude struct {
	Ipv4Address string
	Port        string
}

type IsExists struct {
	IsExists bool `json:"IsExists"`
}

type ResponeData struct {
	Data     string   `json:"data"`
	DataMass []string `json:"data_mass"`
}

type Location struct {
	Path string `json:"Path" `
}

func NewCloude(address string, port string) *Cloude {
	return &Cloude{Ipv4Address: address, Port: port}
}

func (c *Cloude) IsFile(data FileData) bool {
	byte_data, err := json.Marshal(data)
	if err != nil {
		fmt.Println(err)
		return false
	}
	client := http.Client{}
	req, err := http.NewRequest("GET", "http://"+c.Ipv4Address+":"+c.Port+"/cloude/is-file", bytes.NewBuffer(byte_data))
	req.Header.Set("Content-Type", "application/json")
	if err != nil {
		fmt.Println(err)
		return false
	}
	respone, _ := client.Do(req)
	var (
		exists IsExists
	)
	err = json.NewDecoder(respone.Body).Decode(&exists)
	if err != nil {
		fmt.Println(err)
		return false
	}

	respone.Body.Close()
	return exists.IsExists
}

func (c *Cloude) IsDir(data DirData) bool {
	byte_data, err := json.Marshal(data)
	if err != nil {
		fmt.Println(err)
		return false
	}
	client := http.Client{}
	req, err := http.NewRequest("GET", "http://"+c.Ipv4Address+":"+c.Port+"/cloude/is-dir", bytes.NewBuffer(byte_data))
	req.Header.Set("Content-Type", "application/json")

	respone, _ := client.Do(req)
	if err != nil {
		fmt.Println(err)
		return false
	}
	var (
		exists IsExists
	)
	err = json.NewDecoder(respone.Body).Decode(&exists)
	if err != nil {
		fmt.Println(err)
		return false
	}
	respone.Body.Close()
	return exists.IsExists
}

func (c *Cloude) CreateFile(data FileData) {
	byte_data, err := json.Marshal(data)
	if err != nil {
		fmt.Println(err)
		return
	}
	_, err = http.Post("http://"+c.Ipv4Address+":"+c.Port+"/cloude/create-file", "application/json", bytes.NewBuffer(byte_data))
	if err != nil {
		fmt.Println(err)
		return
	}
}

func (c *Cloude) CreateDir(data DirData) {
	byte_data, err := json.Marshal(data)
	if err != nil {
		fmt.Println(err)
		return
	}
	_, err = http.Post("http://"+c.Ipv4Address+":"+c.Port+"/cloude/create-dir", "application/json", bytes.NewBuffer(byte_data))
	if err != nil {
		fmt.Println(err)
		return
	}
}

func (c *Cloude) WriteFile(data WriteData) domain.Error {
	byte_data, err := json.Marshal(data)
	if err != nil {
		fmt.Println(err)
		return domain.Error{
			Error:  err.Error(),
			Objcet: err,
		}
	}
	_, err = http.Post("http://"+c.Ipv4Address+":"+c.Port+"/cloude/write-file", "application/json", bytes.NewBuffer(byte_data))
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

func (c *Cloude) ReadFile(data FileData) (string, domain.Error) {
	byte_data, err := json.Marshal(data)
	if err != nil {
		fmt.Println(err)
		return "", domain.Error{
			Error:  err.Error(),
			Objcet: err,
		}
	}
	client := http.Client{}
	req, err := http.NewRequest("GET", "http://"+c.Ipv4Address+":"+c.Port+"/cloude/read-file", bytes.NewBuffer(byte_data))
	req.Header.Set("Content-Type", "application/json")

	respone, _ := client.Do(req)
	if err != nil {
		fmt.Println(err)
		return "", domain.Error{
			Error:  err.Error(),
			Objcet: err,
		}
	}
	var (
		respone_data ResponeData
	)

	err = json.NewDecoder(respone.Body).Decode(&respone_data)
	if err != nil {
		fmt.Println(err)
		return "", domain.Error{
			Error:  err.Error(),
			Objcet: err,
		}
	}
	respone.Body.Close()
	return respone_data.Data, domain.Error{
		Error:  "Null",
		Objcet: nil,
	}
}

func (c *Cloude) DeleteFile(data FileData) domain.Error {
	byte_data, err := json.Marshal(data)
	if err != nil {
		fmt.Println(err)
		return domain.Error{
			Error:  err.Error(),
			Objcet: err,
		}
	}
	client := http.Client{}
	req, err := http.NewRequest("DELETE", "http://"+c.Ipv4Address+":"+c.Port+"/cloude/delete-file", bytes.NewBuffer(byte_data))
	req.Header.Set("Content-Type", "application/json")
	respone, _ := client.Do(req)
	respone.Body.Close()

	return domain.Error{
		Error:  "Null",
		Objcet: nil,
	}
}

func (c *Cloude) DeleteDir(data FileData) domain.Error {
	byte_data, err := json.Marshal(data)
	if err != nil {
		fmt.Println(err)
		return domain.Error{
			Error:  err.Error(),
			Objcet: err,
		}
	}
	client := http.Client{}
	req, err := http.NewRequest("DELETE", "http://"+c.Ipv4Address+":"+c.Port+"/cloude/delete-dir", bytes.NewBuffer(byte_data))
	req.Header.Set("Content-Type", "application/json")
	respone, _ := client.Do(req)
	respone.Body.Close()
	return domain.Error{
		Error:  err.Error(),
		Objcet: nil,
	}
}

func (c *Cloude) DirNameAll(path Location) []string {
	byte_data, err := json.Marshal(path)
	if err != nil {
		fmt.Println(err)
		return []string{}
	}

	client := http.Client{}
	req, _ := http.NewRequest("GET", "http://"+c.Ipv4Address+":"+c.Port+"/cloude/dir-name-all", bytes.NewBuffer(byte_data))
	req.Header.Set("Content-Type", "application/json")
	respone, err := client.Do(req)
	if err != nil {
		fmt.Println(err)
		return []string{}
	}

	var (
		string_data ResponeData
	)

	err = json.NewDecoder(respone.Body).Decode(&string_data)
	if err != nil {
		fmt.Println(err)
		return []string{}
	}
	return string_data.DataMass
}

func (c *Cloude) FileNameAll(path Location) []string {
	byte_data, err := json.Marshal(path)
	if err != nil {
		fmt.Println(err)
		return []string{}
	}

	client := http.Client{}
	req, _ := http.NewRequest("GET", "http://"+c.Ipv4Address+":"+c.Port+"/cloude/file-name-all", bytes.NewBuffer(byte_data))
	req.Header.Set("Content-Type", "application/json")
	respone, err := client.Do(req)
	if err != nil {
		fmt.Println(err)
		return []string{}
	}

	var (
		string_data ResponeData
	)

	err = json.NewDecoder(respone.Body).Decode(&string_data)
	if err != nil {
		fmt.Println(err)
		return []string{}
	}
	return string_data.DataMass
}
