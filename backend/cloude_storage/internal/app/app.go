package app

import (
	"stor/internal/config"
	"stor/pkg/domain"
	"stor/pkg/handler"
	"stor/pkg/repository"
	"stor/pkg/service"
)

func Init() {
	conf, _ := config.LoadConfig()
	cloude := repository.NewCloude(conf.FilePath)
	service := service.NewService(cloude)
	handler := handler.NewHandler(service)

	server := domain.HttpServer{
		Ipv4Address: conf.Address,
		Port:        conf.Port,
		TimeOut:     conf.Timeout,
		IdleTimeout: conf.Iddle_timeout,
		Handler:     handler.InitRouts(),
	}
	server.Run()
}
