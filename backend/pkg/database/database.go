package database

import (
	"context"
	"fmt"

	"github.com/jackc/pgx/v5"
)

type PostgreSqlBase struct {
	Ipv4Address string
	Port        string
	NameBase    string

	NameTable string
	Param     string
	Point     *pgx.Conn
}

func (b *PostgreSqlBase) Connect() (bool, error) {
	p, err := pgx.Connect(context.Background(), "postgres://postgres:psql@"+b.Ipv4Address+":"+b.Port+"/"+b.NameBase+"?sslmode=disable")
	if err != nil {
		fmt.Println(err)
		return false, err
	}
	b.Point = p
	return true, nil
}

func (b *PostgreSqlBase) Close() bool {
	if b.Point == nil {
		return false
	}
	b.Point.Close(context.Background())
	return true
}

func (b *PostgreSqlBase) Init() bool {
	_, err := b.Point.Exec(context.Background(), "CREATE TABLE IF NOT EXISTS "+b.NameTable+" ("+b.Param+")")
	return err == nil
}

func (b *PostgreSqlBase) Select(param string, where string, argc ...any) (string, error) {
	rows := b.Point.QueryRow(context.Background(), "SELECT "+param+" FROM "+b.NameTable+" WHERE "+where+" = $1", argc...)

	var result string
	err := rows.Scan(&result)
	return result, err
}

func (b *PostgreSqlBase) Insert(param string, values string, argc ...any) error {
	_, err := b.Point.Exec(context.Background(), "INSERT INTO "+b.NameTable+" ( "+param+" ) VALUES ( "+values+" ) ", argc...)
	return err
}

var Db = PostgreSqlBase{
	Ipv4Address: "localhost",
	Port:        "5432",
	NameBase:    "users",
	NameTable:   "users",
	Param:       "Id INT, Name TEXT, Surname TEXT, Username TEXT,Age INT,Login TEXT,Password TEXT",
}
