package app

import (
	"app/internal/config"
	"app/internal/domain"
	"app/internal/handler"
	"app/internal/repository"
	"app/internal/service"
	"app/pkg/cloude"
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
		Param:       "Id INT, Name TEXT, Surname TEXT, Username TEXT,Age INT,Login TEXT,Password TEXT,Email TEXT, Ip TEXT",
	}

	store, err := stor.LoadStorage()
	if err != nil {
		fmt.Println(err)
		return
	}

	cloud := cloude.NewCloude(conf.CloudeAddress, conf.CloudePort)
	if (!cloud.IsDir(cloude.DirData{
		Name: "usr",
		Path: "",
	})) {
		cloud.CreateDir(cloude.DirData{
			Name: "usr",
			Path: "",
		})
	}

	repo := repository.NewRepository(store, cloud)

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
