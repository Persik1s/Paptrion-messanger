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
		fmt.Println(err)
		c.JSON(http.StatusBadRequest, domain.Error{Error: "ERROR BIND JSON"})
		return
	}
	mem, _ := h.Service.SignIn(data)
	c.JSON(http.StatusOK, mem)
}

func (h *Handlers) signup(c *gin.Context) {
	var data domain.AccountInfo
	if err := c.BindJSON(&data); err != nil {
		c.JSON(http.StatusBadRequest, domain.Error{Error: "ERROR BIND JSON"})
		return
	}

	h.Service.SignUp(data)
}

func (h *Handlers) get_list_chat(c *gin.Context) {
	var (
		data domain.AccountData
	)
	if err := c.BindJSON(&data); err != nil {
		c.JSON(http.StatusBadRequest, domain.Error{Error: "ERROR BIND JSON"})
		return
	}

	list_member := h.Service.GetListChat(data)
	c.JSON(http.StatusOK, list_member)
}
