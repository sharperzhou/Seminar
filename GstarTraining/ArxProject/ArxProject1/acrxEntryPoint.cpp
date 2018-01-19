// (C) Copyright 2002-2012 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- acrxEntryPoint.cpp
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
#include "ArxProjectHelper.h"
#include "InsertBlkDlg.h"
#include "InsertTableDlg.h"
#include "Jig.h"
//-----------------------------------------------------------------------------
#define szRDS _RXST("MFG")
//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CArxProject1App : public AcRxArxApp {

public:
	CArxProject1App () : AcRxArxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		// TODO: Load dependencies here

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		
		// TODO: Add your initialization code here
        acedAlert(
            _T("MFGArxProject1.arx命令清单：\n")
            _T("ARX1：弹出消息框，显示Hello World；\n")
            _T("ARX2：指定圆心、半径、图层名、颜色索引值，绘制圆，并打印其句柄值；\n")
            _T("ARX3：选择实体，仅对TEST层上颜色值为4或颜色为ByLayer的圆半径扩大一倍；\n")
            _T("ARX4：打印当前图的所有图层、块、尺寸标注样式、组的名称；\n")
            _T("ARX5：选择俩实体，在交点处绘圆；\n")
            _T("ARX6：输入块名，属性名，生成属性块参照；\n")
            _T("ARX7：根据CGridCtrl控件中的内容在AutoCAD中绘制表格。")
            );

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		// TODO: Add your code here

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;

		// TODO: Unload dependencies here

		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
	}
	
    //----------------------------------------------------------
    // Summary:
    //    弹出对话框命令
    // Parameter:
    // Returns:
    //    void
    //----------------------------------------------------------
    static void MFGGroupARX1 () {
        acedAlert(_T("Hello World"));
	}

    //----------------------------------------------------------
    // Summary:
    //    绘制圆命令
    // Parameter:
    // Returns:
    //    void
    //----------------------------------------------------------
    static void MFGGroupARX2 () {
        AcGePoint3d ptCenter;
        ads_real radius = 0;
        ACHAR szLayerName[135] = {0}; //acedGetString最多获取133字符
        int colorIndex = 4;
        int rt;

        rt= acedGetString(Adesk::kFalse, _T("指定圆所在的图层名称 <TEST>: \n"), szLayerName);
        switch (rt) {
        case RTNORM:
            //如果用户直接按回车确认，赋予默认值
            if (_T('\0') ==szLayerName[0]) _tcscpy(szLayerName, _T("TEST"));
            break;
        default:
            return;
        }

        acedInitGet(RSG_NONEG, NULL);
        rt= acedGetInt(_T("指定圆的颜色索引值(0~256) <4>: \n"), &colorIndex);
        switch (rt) {
        case RTNONE:
            //如果用户直接按回车确认，赋予默认值
            colorIndex = 4; break;
        case RTNORM:
            if (colorIndex >256)
                acutPrintf(_T("警告: 输入的数值超过给定范围，颜色按默认显示\n"));
            break;
        default:
            return;
        }
        
        acedInitGet(RSG_NONULL, NULL);
        if (RTNORM != acedGetPoint(NULL, _T("指定圆的圆心: \n"), asDblArray(ptCenter)))
            return;

        CCircleJig circleJig(ptCenter, colorIndex);
        circleJig.setDispPrompt(_T("指定圆的半径: \n"));
        if (AcEdJig::kNormal != circleJig.drag())
            return;

        AcDbObjectId circleId = CArxProjectHelper::createCircle(ptCenter, circleJig.getRadius(), szLayerName, colorIndex);

        acutPrintf(_T("输出所画圆的句柄为: "));
        circleId.handle().print();
    }

    //----------------------------------------------------------
    // Summary:
    //    选择实体，将圆半径扩大一倍
    // Parameter:
    // Returns:
    //    void
    //----------------------------------------------------------
    static void MFGGroupARX3 ()
    {
        resbuf *rbFilter = NULL;
        ads_name ssname = {0};
        rbFilter = acutBuildList(RTDXF0, _T("CIRCLE")  //选择圆
            , 8, _T("TEST")                            //选择图层为TEST
            , -4, _T("<OR")                            //逻辑或开始
            , 62, 4                                    //颜色索引为4
            , 62, 256                                  //或颜色为ByLayer
            , -4, _T("OR>")                            //逻辑或结束
            , RTNONE);

        if (RTNORM == acedSSGet(NULL, NULL, NULL, rbFilter, ssname)) {
            long len = 0L;
            acedSSLength(ssname, &len);

            for (AdInt32 i = 0L; i < len; ++i) {
                //按索引获取选择集中的元素
                ads_name ent;
                acedSSName(ssname, i, ent);
                AcDbObjectId objId;
                acdbGetObjectId(objId, ent);
                AcDbEntity *pEntity = NULL;
                if (Acad::eOk != acdbOpenObject(pEntity, objId, AcDb::kForWrite))
                    continue;
            
                //获取圆心并将直径扩大一倍
                AcDbCircle *pCircle = AcDbCircle::cast(pEntity);
                if (pCircle) {
                    AcGeMatrix3d mat;
                    mat.setToScaling(2, pCircle->center());
                    pCircle->transformBy(mat);
                }
                pEntity->close();
            }
        }
        
        acutRelRb(rbFilter);
        acedSSFree(ssname);
    }

    //----------------------------------------------------------
    // Summary:
    //    打印所有图层名、块名、尺寸标注样式名、组名
    // Parameter:
    // Returns:
    //    void
    //----------------------------------------------------------
    static void MFGGroupARX4 ()
    {
        AcStringArray aOutputName;
        
        CArxProjectHelper::getSymbolRecord<AcDbBlockTable>(aOutputName);
        CArxProjectHelper::printSymbolRecord(_T("块表名称"), aOutputName);

        CArxProjectHelper::getSymbolRecord<AcDbLayerTable>(aOutputName);
        CArxProjectHelper::printSymbolRecord(_T("层表名称"), aOutputName);

        CArxProjectHelper::getSymbolRecord<AcDbDimStyleTable>(aOutputName);
        CArxProjectHelper::printSymbolRecord(_T("尺寸标注样式名称"), aOutputName);

        CArxProjectHelper::getGroupName(aOutputName);
        CArxProjectHelper::printSymbolRecord(_T("组名称"), aOutputName);
    }

    //----------------------------------------------------------
    // Summary:
    //    依次选择两个实体，在交点处绘制圆
    // Parameter:
    // Returns:
    //    void
    //----------------------------------------------------------
    static void MFGGroupARX5 ()
    {
        int rt; //选择实体返回值
        ads_name ent[2] = {0};  //第一、二实体名
        ads_point pt;  //选择第一、二实体时的坐标
        AcDbObjectId objId; //选择实体或当前图层的id
        AcDbEntity *pEnt[2] = {0};  //两个实体对象指针
        AcGePoint3dArray aPoint3d;  //返回两个实体的交点
        bool bCancel;  //退出选择过程条件
        //选择提示说明
        ACHAR *strDesc[2] = {_T("选择第一实体: \n"), _T("选择第二实体: \n")};

        for (int i = 0; i < 2; ++i) {
            bCancel = false;

            while (!bCancel) {
                rt = acedEntSel(strDesc[i], ent[i], pt);
                switch (rt) {
                case RTNORM:
                    {
                        acdbGetObjectId(objId, ent[i]);
                        acdbOpenObject(pEnt[i], objId, AcDb::kForRead);
                        if (pEnt[i]->isKindOf(AcDbLine::desc())
                            || pEnt[i]->isKindOf(AcDbCircle::desc())
                            || pEnt[i]->isKindOf(AcDbArc::desc())
                            || pEnt[i]->isKindOf(AcDbEllipse::desc())
                            || pEnt[i]->isKindOf(AcDbPolyline::desc()))
                        {
                            pEnt[i]->highlight(); //选择后高亮显示
                            bCancel = true;
                        }
                        else {
                            acutPrintf(_T("错误: 选择的实体只能为直线、圆、圆弧、椭圆和多段线\n"));
                        }
                    }
                    break;

                case RTERROR: //出错后重新选择
                    break;

                case RTCAN:  //当用户按下Esc后退出
                default:
                    goto CleanHandler;
                }
            }
        }

        //求交点
        pEnt[0]->intersectWith(pEnt[1], AcDb::kOnBothOperands, aPoint3d);

        //在当前图层上绘制半径为1的圆
        {
            AcString strCLayerName;
            if (!CArxProjectHelper::getCurrentLayerName(strCLayerName))
                goto CleanHandler;

            int len = aPoint3d.length();
            for (int i = 0; i < len; ++i) {
                CArxProjectHelper::createCircle(aPoint3d.at(i), 1, strCLayerName.kTCharPtr(), 1);
            }
        }

CleanHandler:
        for (int i = 0; i < 2; ++i) {
            if (!acdbNameNil(ent[i]))
                pEnt[i]->unhighlight(); //恢复未高亮状态
            if (pEnt[i]) pEnt[i]->close();
        }
    }

    //----------------------------------------------------------
    // Summary:
    //    在对话框中设置属性值，插入带属性的块参照
    // Parameter:
    // Returns:
    //    void
    //----------------------------------------------------------
    static void MFGGroupARX6 ()
    {
        CInsertBlkDlg dlg;
        if (IDOK == dlg.DoModal()) {
            CArxProjectHelper::createBlockReference(dlg.m_blkDefId, 0,
                AcGeScale3d(1), dlg.m_aBlkAttr); //旋转和放大系数设为默认
        }
    }

    //----------------------------------------------------------
    // Summary:
    //    根据CGridCtrl控件中的内容绘制表格
    // Parameter:
    // Returns:
    //    void
    //----------------------------------------------------------
    static void MFGGroupARX7 ()
    {
        CInsertTableDlg dlg;
        if (IDOK == dlg.DoModal()) {
            //创建表格
            AcDbObjectId tableId = CArxProjectHelper::createTable(dlg.getRowCount(),
                dlg.getColumnCount(), dlg.getCellAlignment());

            if (tableId.isValid()) { //设置表格属性
                CArxProjectHelper::fillTableContent(dlg.getTableContent(), tableId);
                CArxProjectHelper::setTableTextAttribute(dlg.getTextStyle(), dlg.getTextHeight(),
                    dlg.getTextWidthFactor(), dlg.getTextColor(), tableId);
                CArxProjectHelper::setTableLineAttribute(dlg.getLineWeight(), dlg.getLineType(),
                    dlg.getLineColor(), tableId);
            }
        }
    }
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CArxProject1App)

ACED_ARXCOMMAND_ENTRY_AUTO(CArxProject1App, MFGGroup, ARX1, ARX1, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CArxProject1App, MFGGroup, ARX2, ARX2, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CArxProject1App, MFGGroup, ARX3, ARX3, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CArxProject1App, MFGGroup, ARX4, ARX4, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CArxProject1App, MFGGroup, ARX5, ARX5, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CArxProject1App, MFGGroup, ARX6, ARX6, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CArxProject1App, MFGGroup, ARX7, ARX7, ACRX_CMD_MODAL, NULL)

