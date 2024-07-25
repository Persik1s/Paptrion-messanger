package database

import (
	"context"
	"fmt"

	"github.com/jackc/pgx/v5"
)

type PostgreSqlBase struct {
	Ipv4Address string
	Port        string
	NameTable   string
}

func (b *PostgreSqlBase) Connect() (bool, error) {
	con, err := pgx.Connect(context.Background(), "postgres://postgres:psql@"+b.Ipv4Address+":"+b.Port+"/"+b.NameTable)

	if err != nil {
		fmt.Println(err)
		return false, err
	}

	con.Close(context.Background())
	return true, nil
}
