<?xml version="1.0" encoding="UTF-8"?>
<!--<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:b="urn:oasis:names:tc:emergency:cap:1.1"> -->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:b="urn:oasis:names:tc:emergency:cap:1.1" xmlns:php="http://php.net/xsl">
<!--XSL for Short to Tweet text type-->
<!-- to add linebreaks add the following <xsl:text></xsl:text> -->
  <xsl:output method="text"/>
  <xsl:template match="/">
         <xsl:apply-templates/>
  </xsl:template>
  <xsl:template match="b:alert">
<xsl:value-of select="b:status"/><xsl:text> </xsl:text><xsl:value-of select="b:msgType"/>
<xsl:text> </xsl:text><xsl:value-of select="b:info/b:event"/> in <xsl:value-of select="b:info/b:area/b:areaDesc"/>
<xsl:text> </xsl:text><xsl:value-of select="b:info/b:web"/><xsl:text> #disaster</xsl:text>
  </xsl:template>
</xsl:stylesheet>
