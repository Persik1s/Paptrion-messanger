package config

import (
	"app/internal/domain"

	"github.com/ilyakaznacheev/cleanenv"
	"time"
)

type Config struct {
	Env                string `yaml:"env"`
	ConfigHttpServer   `yaml:"http_server"`
	ConfigCloudeServer `yaml:"cloude_server"`
}

type ConfigHttpServer struct {
	ServerAddress string        `yaml:"ipv4_address"`
	ServerPort    string        `yaml:"port"`
	Timeout       time.Duration `yaml:"timeout"`
	Iddle_timeout time.Duration `yaml:"idle_timeout"`
}

type ConfigCloudeServer struct {
	CloudeAddress string `yaml:"ipv4_address"`
	CloudePort    string `yaml:"port"`
}

func LoadConfig() (*Config, domain.Error) {
	var conf Config

	if err := cleanenv.ReadConfig("../../config/conf.yaml", &conf); err != nil {
		return nil, domain.Error{
			Error:  err.Error(),
			Objcet: nil,
		}
	}

	return &conf, domain.Error{
		Error:  "Null",
		Objcet: nil,
	}
}
