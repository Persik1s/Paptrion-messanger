package domain

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
type Location struct {
	Path string `json:"Path" `
}

type IsExists struct {
	IsExists bool `json:"IsExists"`
}
