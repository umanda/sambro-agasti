<?xml version="1.0" encoding="UTF-8"?>
<!--<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:b="urn:oasis:names:tc:emergency:cap:1.1"> -->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:b="urn:oasis:names:tc:emergency:cap:1.1" xmlns:php="http://php.net/xsl">
<!--XSL for Short to IVR text type-->
<!-- From CAP Doc Short to IVR -->
<!-- to add linebreaks add the following <xsl:text></xsl:text> -->
  <xsl:output method="text"/>
  <xsl:template match="/">
         <xsl:apply-templates/>
  </xsl:template>
  <xsl:template match="b:alert">
This is a(n) <xsl:value-of select="b:status"/><xsl:text> </xsl:text><xsl:value-of select="b:msgType"/><xsl:text> </xsl:text><xsl:text>
</xsl:text>
<xsl:value-of select="b:info/b:headline"/><xsl:text>
</xsl:text>
<xsl:value-of select="b:info/b:priority"/> priority <xsl:for-each select="b:info/b:category">
<xsl:value-of select="."/>
<xsl:if test="position() != last()">, </xsl:if>
</xsl:for-each> event is(are) effective for <xsl:value-of select="b:info/b:area/b:areaDesc"/>.<xsl:text>
</xsl:text>
The <xsl:for-each select="b:info/b:category">
<xsl:value-of select="."/>
<xsl:if test="position() != last()">, </xsl:if>
</xsl:for-each> event is(are) <xsl:value-of select="b:info/b:urgency"/> and is <xsl:value-of select="b:info/b:certainty"/>.<xsl:text>
</xsl:text>
Alert was issued by <xsl:value-of select="b:info/b:senderName"/><xsl:text>
</xsl:text>
It is <xsl:value-of select="b:scope"/> to <xsl:value-of select="b:restriction"/>.<xsl:text>
</xsl:text>
<xsl:value-of select="b:info/b:instruction"/>.<xsl:text>
</xsl:text>
Alert is effective from: <xsl:value-of select="b:info/b:effective"/> and will expire on: <xsl:value-of select="b:info/b:expires"/>.<xsl:text>
</xsl:text>
For more details call: <xsl:value-of select="b:info/b:contact"/>
  </xsl:template>
</xsl:stylesheet>
