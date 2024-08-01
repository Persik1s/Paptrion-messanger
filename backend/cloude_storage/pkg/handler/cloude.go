package handler

import (
	"fmt"
	"net/http"
	"stor/pkg/domain"

	"github.com/gin-gonic/gin"
)

var ErrorBind = domain.Error{Error: "BindJson Error"}

func (h *Handler) HandlerWriteFile(c *gin.Context) {
	var (
		data domain.WriteData
	)
	if err := c.BindJSON(&data); err != nil {
		fmt.Errorf("%s", "%w", "pkg.handler.cloude", err)
		c.JSON(http.StatusBadRequest, ErrorBind)
		return
	}
	h.Service.WriteFile(data)
}

func (h *Handler) HandlerReadFile(c *gin.Context) {
	var (
		data domain.FileData
	)

	if err := c.BindJSON(&data); err != nil {
		fmt.Errorf("%s", "%w", "pkg.handler.cloude", err)
		c.JSON(http.StatusBadRequest, ErrorBind)
		return
	}

	str_data := h.Service.ReadFile(data)
	c.JSON(http.StatusOK, str_data)
}

func (h *Handler) HandlerCreateFile(c *gin.Context) {
	var (
		data domain.FileData
	)

	if err := c.BindJSON(&data); err != nil {
		fmt.Errorf("%s", "%w", "pkg.handler.cloude", err)
		c.JSON(http.StatusBadRequest, ErrorBind)
		return
	}

	h.Service.NewFile(data)
}
func (h *Handler) HandlerCreateDir(c *gin.Context) {
	var (
		data domain.DirData
	)

	if err := c.BindJSON(&data); err != nil {
		fmt.Errorf("%s", "%w", "pkg.handler.cloude", err)
		c.JSON(http.StatusBadRequest, ErrorBind)
		return
	}

	if !h.Service.NewDir(data) {
		c.JSON(http.StatusBadRequest, nil)
		return
	}

	c.AbortWithStatus(http.StatusOK)
}
func (h *Handler) HandlerDeleteFile(c *gin.Context) {
	var (
		data domain.FileData
	)

	if err := c.BindJSON(&data); err != nil {
		fmt.Errorf("%s", "%w", "pkg.handler.cloude", err)
		c.JSON(http.StatusBadRequest, domain.Error{Error: "Bind FileError {delete file}"})
		return
	}

	status := h.Service.DeleteFile(data)
	if !status {
		c.JSON(http.StatusBadRequest, domain.Error{Error: "Delete FileError"})
		return
	}
	c.JSON(http.StatusOK, nil)
}
func (h *Handler) HandlerDeleteDir(c *gin.Context) {
	var (
		data domain.DirData
	)

	if err := c.BindJSON(&data); err != nil {
		fmt.Errorf("%s", "%w", "pkg.handler.cloude", err)
		c.JSON(http.StatusBadRequest, ErrorBind)
		return
	}

	status := h.Service.DeleteDir(data)
	if !status {
		c.JSON(http.StatusBadRequest, domain.Error{Error: "Delete DirError"})
		return
	}
	c.JSON(http.StatusOK, nil)
}
