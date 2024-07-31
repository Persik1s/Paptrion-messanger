package handler

import (
	"app/internal/domain"
	"fmt"
	"net/http"

	"github.com/gin-gonic/gin"
)

func (h *Handlers) signin(c *gin.Context) {
	var data domain.AccountData
	if err := c.BindJSON(&data); err != nil {
		fmt.Errorf("%s", "%w", "internal.handler.authorization", err)
		c.AbortWithStatus(http.StatusBadRequest)
		return
	}
	mem, _ := h.Service.SignIn(data)
	c.JSON(http.StatusOK, mem)
}

func (h *Handlers) signup(c *gin.Context) {
	var data domain.AccountInfo
	if err := c.BindJSON(&data); err != nil {
		fmt.Errorf("%s", "%w", "internal.handler.authorization", err)
		c.AbortWithStatus(http.StatusBadRequest)
		return
	}

	h.Service.SignUp(data)
}
