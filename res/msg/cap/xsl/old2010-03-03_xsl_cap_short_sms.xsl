<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:b="urn:oasis:names:tc:emergency:cap:1.1">
<!--XSL for Short to SMS text type-->
<!-- From CAP Doc Short to SMS
<info.headline>+” for ”+ <area.areaDesc> +”...“+
<info.valueName>+” “+ <info.value>+” “+<info.event> +”
issued by ”+<info.senderName> +”.
Msg:”+<alert.identifier>+” sent ”+<alert.sent>+” is a
“+<info.status>+” “+<info.type>+”. More info “+
<info.web>+” “+<info.contact>
-->
  <xsl:output method="text"/>
  <xsl:template match="/">
         <xsl:apply-templates/>
  </xsl:template>
  <xsl:template match="b:alert">
          <xsl:value-of select="b:info/b:headline"/> for <xsl:value-of select="b:info/b:area/b:areaDesc"/> ... <xsl:value-of select="b:info/b:senderName"/>. Msg: <xsl:value-of select="b:identifier"/> sent <xsl:value-of select="b:sent"/> is a <xsl:value-of select="b:status"/> <xsl:value-of select="b:msgType"/>. More info <xsl:value-of select="b:info/b:web"/> <xsl:value-of select="b:sender"/>
  </xsl:template>
</xsl:stylesheet>
