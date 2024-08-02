package handler

import (
	"app/internal/domain"
	"net/http"

	"github.com/gin-gonic/gin"
)

func (h *Handlers) send_message(c *gin.Context) {
	var (
		data domain.MessageData
	)

	if err := c.BindJSON(&data); err != nil {
		c.JSON(http.StatusBadRequest, domain.Error{Error: "ERROR BIND JSON"})
		return
	}
	h.Service.SendMessage(data)
	c.JSON(http.StatusOK, nil)
}
