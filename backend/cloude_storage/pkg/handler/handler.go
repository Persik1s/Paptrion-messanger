package handler

import (
	"stor/pkg/service"

	"github.com/gin-gonic/gin"
)

type Handler struct {
	Service *service.Service
}

func NewHandler(serv *service.Service) *Handler {
	return &Handler{Service: serv}
}

func (h *Handler) InitRouts() *gin.Engine {
	routs := gin.New()
	cloude := routs.Group("/cloude")
	{
		cloude.DELETE("/delete-file", h.HandlerDeleteFile)
		cloude.DELETE("/delete-dir", h.HandlerDeleteDir)

		cloude.POST("/create-file", h.HandlerCreateFile)
		cloude.POST("/create-dir", h.HandlerCreateDir)
		cloude.POST("/write-file", h.HandlerWriteFile)

		cloude.GET("/read-file", h.HandlerReadFile)

		cloude.GET("/is-dir", h.HandlerIsDir)
		cloude.GET("/is-file", h.HandlerIsFile)
	}
	return routs
}
