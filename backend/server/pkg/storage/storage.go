package storage

import (
	"context"
	"fmt"

	"github.com/jackc/pgx/v5"
)

const (
	path = "pkg.repository.storage"
)

type SqlBase struct {
	Ipv4Address string
	Port        string
	NameBase    string

	NameTable string
	Param     string
	Point     *pgx.Conn
}

func (b *SqlBase) Connect() (bool, error) {
	p, err := pgx.Connect(context.Background(), "postgres://postgres:psql@"+b.Ipv4Address+":"+b.Port+"/"+b.NameBase+"?sslmode=disable")
	if err != nil {
		fmt.Println(err)
		return false, fmt.Errorf("%s", "%w", path, err)
	}
	b.Point = p
	return true, nil
}

func (b *SqlBase) LoadStorage() (*SqlBase, error) {
	if _, err := b.Connect(); err != nil {
		return nil, fmt.Errorf("%s", "%w", path, err)
	}

	b.Init()

	return b, nil
}

func (b *SqlBase) Close() bool {
	if b.Point == nil {
		return false
	}
	b.Point.Close(context.Background())
	return true
}

func (b *SqlBase) Init() bool {
	_, err := b.Point.Exec(context.Background(), "CREATE TABLE IF NOT EXISTS "+b.NameTable+" ("+b.Param+")")
	return err == nil
}

func (b *SqlBase) Select(param string, where string, argc ...any) (string, error) {
	rows := b.Point.QueryRow(context.Background(), "SELECT "+param+" FROM "+b.NameTable+" WHERE "+where+" = $1", argc...)

	var result string
	err := rows.Scan(&result)
	return result, err
}

func (b *SqlBase) Insert(param string, values string, argc ...any) error {
	_, err := b.Point.Exec(context.Background(), "INSERT INTO "+b.NameTable+" ( "+param+" ) VALUES ( "+values+" ) ", argc...)
	return err
}
