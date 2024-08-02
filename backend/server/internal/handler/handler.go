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
		auth.GET("/get_list_chat", h.get_list_chat)

		auth.POST("/sign-up", h.signup)

	}
	chat := routs.Group("/chat")
	{
		chat.GET("/get_list_message", h.get_list_message)
		chat.POST("/send_message", h.send_message)
	}

	return routs
}
