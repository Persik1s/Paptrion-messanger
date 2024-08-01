package handler

import (
	"app/internal/service"

	"github.com/gin-gonic/gin"
)

type Handlers struct {
	Service *service.Service
}

func NewHandlers(serv *service.Service) *Handlers {
	return &Handlers{Service: serv}
}

func (h *Handlers) InitRouts() *gin.Engine {
	routs := gin.New()
	auth := routs.Group("/account")
	{
		auth.GET("/sign-in", h.signin)
		auth.POST("/sign-up", h.signup)
	}

	return routs
}
