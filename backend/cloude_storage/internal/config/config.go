package config

import (
	"fmt"
	"time"

	"github.com/ilyakaznacheev/cleanenv"
)

type Config struct {
	Env              string `yaml:"env"`
	FilePath         string `yaml:"save_path"`
	ConfigHttpServer `yaml:"http_server"`
}

type ConfigHttpServer struct {
	Address       string        `yaml:"ipv4_address"`
	Port          string        `yaml:"port"`
	Timeout       time.Duration `yaml:"timeout"`
	Iddle_timeout time.Duration `yaml:"idle_timeout"`
}

func LoadConfig() (*Config, error) {
	var conf Config

	if err := cleanenv.ReadConfig("../config/conf.yaml", &conf); err != nil {
		return nil, fmt.Errorf("%s", "%w", "internal.config.config", err)
	}

	return &conf, nil
}
