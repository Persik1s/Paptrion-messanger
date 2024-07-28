package app

import (
	"app/internal/domain"
	"app/internal/transport/handlers"
	"app/internal/transport/server"
	"os"

	"app/pkg/database"

	"fmt"
)

func Init() {
	database.Db.Connect()
	database.Db.Init()

	os.Mkdir("../../../TestObejectStorge", os.ModeDir)

	ser := server.Server{
		Ipv4Address: "127.0.0.1",
		Port:        "2001",
	}
	ser.HandlerFunc[0] = domain.HandlerFunction{
		NameHandler: "/account_event",
		Func:        handlers.HandlerAccount,
	}

	ser.HandlerFunc[1] = domain.HandlerFunction{
		NameHandler: "/chat_event",
		Func:        handlers.HandlerChat,
	}

	if err := ser.Run(); err != nil {
		fmt.Println("ERROR RUN SERVER -> {", ser.Ipv4Address+":"+ser.Port, "}")
	}
}
