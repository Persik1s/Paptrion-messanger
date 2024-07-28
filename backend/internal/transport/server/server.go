package server

import (
	"app/internal/domain"
	"net/http"
)

type Server struct {
	Ipv4Address string
	Port        string
	HandlerFunc [2]domain.HandlerFunction
}

func (b *Server) Run() error {
	b.init()
	server := &http.Server{
		Addr: b.Ipv4Address + ":" + b.Port,
	}
	return server.ListenAndServe()
}
func (b *Server) init() {
	for i := range b.HandlerFunc {
		http.HandleFunc(b.HandlerFunc[i].NameHandler, b.HandlerFunc[i].Func)
	}
}
