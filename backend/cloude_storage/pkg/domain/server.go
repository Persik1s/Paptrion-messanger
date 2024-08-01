package domain

import (
	"fmt"
	"net/http"
	"time"
)

type HttpServer struct {
	Ipv4Address string
	Port        string

	TimeOut     time.Duration
	IdleTimeout time.Duration
	Handler     http.Handler
}

func (h *HttpServer) Run() error {
	server := http.Server{
		Addr:         h.Ipv4Address + ":" + h.Port,
		ReadTimeout:  h.TimeOut,
		WriteTimeout: h.TimeOut,
		IdleTimeout:  h.IdleTimeout,
		Handler:      h.Handler,
	}
	if err := server.ListenAndServe(); err != nil {
		return fmt.Errorf("%s", "%w", "internal.domain.server", err)
	}

	return nil
}
