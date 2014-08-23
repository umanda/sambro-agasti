<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:b="urn:oasis:names:tc:emergency:cap:1.1" xmlns:php="http://php.net/xsl">
<!--XSL for Short to dlabel text type-->
<!-- From CAP Doc Short to SMS -->
<!-- to add linebreaks add the following <xsl:text></xsl:text> -->
  <xsl:output method="text"/>
  <xsl:template match="/">
         <xsl:apply-templates/>
  </xsl:template>
  <xsl:template match="b:alert">
	<xsl:value-of select="b:status"/>-<xsl:value-of select="b:msgType"/>, <xsl:value-of select="b:info/b:priority"/> priority: <xsl:value-of select="b:info/b:headline"/> for <xsl:value-of select="b:info/b:area/b:areaDesc"/> area, <xsl:value-of select="b:info/b:senderName"/>, <xsl:value-of select="b:info/b:effective"/>
<!-- Msg: <xsl:value-of select="b:identifier"/> sent on <xsl:value-of select="b:sent"/>.<xsl:text></xsl:text> -->
<!-- Desc: <xsl:value-of select="b:info/b:description"/><xsl:text></xsl:text> -->
<!-- More details <xsl:text></xsl:text>
Web: <xsl:value-of select="php:function('shn_msg_convert_tiny_url', b:info/b:web, b:identifier)"/><xsl:text></xsl:text>
call: <xsl:value-of select="b:info/b:contact"/> -->
  </xsl:template>
</xsl:stylesheet>
