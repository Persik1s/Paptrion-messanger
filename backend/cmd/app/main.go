package main

import (
	"app/internal/server"
	"app/pkg/database"
	"fmt"
)

func main() {
	db := database.PostgreSqlBase{
		Ipv4Address: "localhost",
		Port:        "5432",
		NameTable:   "postgres",
	}
	fmt.Println(db.Connect())

	ser := server.Server{
		Ipv4Address: "127.0.0.1",
		Port:        "2000",
	}

	if err := ser.Run(); err != nil {
		fmt.Println("ERROR RUN SERVER -> {", ser.Ipv4Address+":"+ser.Port, "}")
	}
}
