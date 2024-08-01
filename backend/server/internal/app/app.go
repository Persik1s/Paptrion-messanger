package app

import (
	"app/internal/config"
	"app/internal/domain"
	"app/internal/handler"
	"app/internal/repository"
	"app/internal/service"
	"app/pkg/storage"
	"fmt"
)

var stor storage.SqlBase

func Init() {
	conf, _ := config.LoadConfig()

	fmt.Println(conf)

	stor = storage.SqlBase{
		Ipv4Address: "localhost",
		Port:        "5432",
		NameBase:    "users",
		NameTable:   "users",
		Param:       "Id INT, Name TEXT, Surname TEXT, Username TEXT,Age INT,Login TEXT,Password TEXT,Email TEXT",
	}

	store, _ := stor.LoadStorage()
	repo := repository.NewRepository(store)
	service := service.NewService(repo)
	handler := handler.NewHandlers(service)

	serv := domain.HttpServer{
		Ipv4Address: conf.ServerAddress,
		Port:        conf.ServerPort,
		TimeOut:     conf.Timeout,
		IdleTimeout: conf.Iddle_timeout,
		Handler:     handler.InitRouts(),
	}

	serv.Run()
}
