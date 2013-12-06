<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:b="urn:oasis:names:tc:emergency:cap:1.1">
<!--XSL for Short to SMS text type-->
<xsl:output method="text"/>
  <xsl:template match="/">
         <xsl:apply-templates/>
  </xsl:template>
    <xsl:template match="b:alert">
     <xsl:value-of select="b:status"/>
  </xsl:template>
</xsl:stylesheet>