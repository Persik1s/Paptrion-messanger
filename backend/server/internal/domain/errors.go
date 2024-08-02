package domain

import "errors"

type Error struct {
	Error  string `json:"Error"`
	Objcet error
}

var (
	ERROR_ALREADY_EXISTS   = errors.New("ERROR_ALREADY_EXISTS")
	ERROR_MEMBER_NOT_FOUND = errors.New("ERROR_MEMBER_NOT_FOUND")
	ERROR_BAD_PASSWORD     = errors.New("ERROR_BAD_PASSWORD")
)
